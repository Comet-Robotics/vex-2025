#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "tasks/teleop.h"
#include "constants.h"
#include "subsystems.h"

using namespace pros;


void opcontrol_initialize(){}

static void drivebase_controls(Controller &controller)
{
    if constexpr (constants::USE_TANK)
    {
        drivebase->tank(
            controller.get_analog(E_CONTROLLER_ANALOG_LEFT_Y),
            controller.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y));
    }
    else
    {
        drivebase->errorDrive(
            controller.get_analog(E_CONTROLLER_ANALOG_LEFT_Y),
            controller.get_analog(E_CONTROLLER_ANALOG_RIGHT_X));
    }
}

static void intake_controls(Controller &controller) {
    if(controller.get_digital(E_CONTROLLER_DIGITAL_L2)) {
        intake->forward();
    } else if (controller.get_digital(E_CONTROLLER_DIGITAL_L1)) {
        intake->reverse();
    } else {
        intake->stop();
    }
}

static void clamp_controls(Controller &controller) {
    if(controller.get_digital_new_press(E_CONTROLLER_DIGITAL_R1)) {
        clamp->toggle();
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
    Controller controller(pros::E_CONTROLLER_MASTER);

    while (true)
    {
        pros::lcd::print(0, "Battery: %2.3f V", pros::battery::get_voltage() / 1000.0f);

        drivebase_controls(controller);
        intake_controls(controller);
        clamp_controls(controller);

        pros::delay(constants::TELEOP_POLL_TIME);
    }
}





