#include "tasks/teleop.h"
#include "comets/vendor.h"
#include "subsystems.h"

void opcontrol_initialize()
{
    drivebase->calibrate();
}

void opcontrol()
{
    pros::Controller controller(pros::E_CONTROLLER_MASTER);

    while (true)
    {
        // get left y and right y positions
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightY = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

        // move the robot
        drivebase->tank(leftY, rightY, true);

        // print robot location to the brain screen
        pros::lcd::print(0, "X: %f", drivebase->getPose().x);                          // x
        pros::lcd::print(1, "Y: %f", drivebase->getPose().y);                          // y
        pros::lcd::print(2, "Theta: %f", drivebase->getPose().theta);                  // heading
        pros::lcd::print(3, "IMU Theta: %f %f %f", drivebase->getIMU().get_heading()); // heading from IMU

        // delay to save resources
        pros::delay(20);
    }
}