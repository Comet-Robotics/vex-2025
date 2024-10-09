#include "pros/misc.h"
#include "pros/misc.hpp"
#include "subsystems.h"
#include "tasks/auton.h"

pros::Controller controller(pros::E_CONTROLLER_MASTER);
ASSET(path_txt)

enum class AutonMode
{
    VS,
    SKILLS,
    TEST
};

/*
 *  VS is 2v2 auton
 *  SKILLS is self explanitory
 *  TEST is testing any autons or tuning
 */
inline constexpr AutonMode MODE = AutonMode::TEST;

void autonomousTest()
{
    // drivebase->turnToHeading(90, 100000);
    // drivebase->moveToPoint(0, 10, 100000);
    drivebase->follow(path_txt, 2000, 15);

    controller.print(0, 0, "X: %f", drivebase->getPose().x);
    controller.print(1, 0, "Y: %f", drivebase->getPose().y);
    controller.print(2, 0, "Theta: %f", drivebase->getPose().theta);
}

void autonomousSkills()
{
}

void autonomousVS()
{
}

void autonomous()
{
    switch (MODE)
    {
    case AutonMode::TEST:
        return autonomousTest();
    case AutonMode::SKILLS:
        return autonomousSkills();
    case AutonMode::VS:
        return autonomousVS();
    default:
        break;
    }
};

void autonomous_initialize()
{
    drivebase->calibrateChassis(true);
};