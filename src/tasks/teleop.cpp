#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "tasks/teleop.h"
#include "constants.h"
#include "subsystems.h"

using namespace pros;

void opcontrol_initialize() {}

static void drivebase_controls(Controller &controller) {
    if constexpr (constants::drivebase::USE_TANK) {
        drivebase->tank(
            controller.get_analog(E_CONTROLLER_ANALOG_LEFT_Y),
            controller.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y));
    } else {
        drivebase->errorDrive(
            controller.get_analog(E_CONTROLLER_ANALOG_LEFT_Y),
            controller.get_analog(E_CONTROLLER_ANALOG_RIGHT_X));
    }
}

static void intake_controls(Controller &controller) {
    if constexpr (constants::intake::USE_TOGGLE) {
        if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_L1)) {
            intake->toggleForward();
        }
        else if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_L2)) {
            intake->toggleReverse();
        }

        intake->periodic();
    } else {
        if (controller.get_digital(E_CONTROLLER_DIGITAL_L1)) {
            intake->forward();
        } else if (controller.get_digital(E_CONTROLLER_DIGITAL_L2)) {
            intake->reverse();
        } else {
            intake->stop();
        }
    }
}

static void elevator_controls(Controller &controller) {
    if constexpr (constants::elevator::USE_TOGGLE) {
        if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_L1)) {
            elevator->toggleForward();
        }
        else if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_L2)) {
            elevator->toggleReverse();
        }

        elevator->periodic();
    } else {
        if (controller.get_digital(E_CONTROLLER_DIGITAL_L1)) {
            elevator->forward();
        } else if (controller.get_digital(E_CONTROLLER_DIGITAL_L2)) {
            elevator->reverse();
        } else {
            elevator->stop();
        }
    }
}

static void arm_controls(Controller &controller) {
    if constexpr (constants::elevator::USE_TOGGLE) {
        if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_UP)) {
            arm->toggleForward();
        }
        else if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_DOWN)) {
            arm->toggleReverse();
        }

        arm->periodic();
    } else {
        if (controller.get_digital(E_CONTROLLER_DIGITAL_UP)) {
            arm->forward();
        } else if (controller.get_digital(E_CONTROLLER_DIGITAL_DOWN)) {
            arm->reverse();
        } else {
            arm->stop();
        }
    }
}

static void clamp_controls(Controller &controller) {
    if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_R1)) {
        clamp->toggle();
    }
}

void trackWidthTuner() {
    Controller controller(pros::E_CONTROLLER_MASTER);
    drivebase->setPose(0, 0, 0);
    float highestDist = 0;
    pros::lcd::print(0, "Battery: %2.3f V", pros::battery::get_voltage() / 1000.0f);

    // drivebase_controls(controller);
    // intake_controls(controller);
    // elevator_controls(controller);
    // clamp_controls(controller);
    // arm_controls(controller);

    int startTime = pros::millis();
    while (pros::millis() - startTime < 3000) {
        drivebase->arcade(0, 63);
        pros::lcd::print(1, "Rotation Sensor: %i", constants::drivebase::VERTICAL_ROTATION.get_position());
        pros::lcd::print(2, "TW: %.2f", DRIVETRAIN_WIDTH);
        pros::lcd::print(3, "TopDist: %.3f", highestDist);

        float currentDist = sqrt(pow(drivebase->getPose().x, 2) + pow(drivebase->getPose().y, 2));
        if (currentDist > highestDist) {
            highestDist = currentDist;
        }

        pros::delay(constants::TELEOP_POLL_TIME);
    }

    drivebase->arcade(0, 0);

        // if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
        //     drivebase->setPose(0, 0, 0);
        // }

    while (true) {
        pros::lcd::print(1, "Rotation Sensor: %i", constants::drivebase::VERTICAL_ROTATION.get_position());
        pros::lcd::print(2, "TW: %.2f", DRIVETRAIN_WIDTH);
        pros::lcd::print(3, "TopDist: %.3f", highestDist);

        pros::delay(constants::TELEOP_POLL_TIME);
    }
}

void driverControl() {
    Controller controller(pros::E_CONTROLLER_MASTER);
    // drivebase->setPose(0, 0, 0);

    while (true) {
        pros::lcd::print(0, "Battery: %2.3f V", pros::battery::get_voltage() / 1000.0f);

        drivebase_controls(controller);
        intake_controls(controller);
        elevator_controls(controller);
        clamp_controls(controller);
        arm_controls(controller);

        // pros::lcd::print(1, "Rotation Sensor: %i", constants::drivebase::VERTICAL_ROTATION.get_position());
        // controller.clear();
        // pros::delay(50);
        // controller.print(0, 0, "X: %f", drivebase->getPose().x);
        // pros::delay(50);
        // controller.print(1, 0, "Y: %f", drivebase->getPose().y);
        // pros::delay(50);
        // controller.print(2, 0, "Theta: %f", drivebase->getPose().theta);
        // pros::delay(50);

        
        pros::lcd::print(1, "X: %f", drivebase->getPose().x);
        pros::lcd::print(2, "Y: %f", drivebase->getPose().y);
        pros::lcd::print(3, "Theta: %f", drivebase->getPose().theta);
        pros::lcd::print(4, "Elev Eff: %d", elevator->getEfficiency());

        pros::delay(constants::TELEOP_POLL_TIME);
    }
}


/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
    // trackWidthTuner();
    driverControl();
}
