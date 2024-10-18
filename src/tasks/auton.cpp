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

    drivebase->setPose(-60, 0, 90);
    
    drivebase->turnToPoint(-48, -48, 5000);
    drivebase->moveToPoint(-48, -48, 5000);
}

//port whichever over to the other bot later whenever we code that
void autonomousSkillsRed()
{
    drivebase->setPose(-61, 4, 90);
    
    intake->forward();
    drivebase->moveToPoint(-47, 47, DEFAULT_TIMEOUT, {}, false);
    intake->stop();

    drivebase->turnToHeading(270, DEFAULT_TIMEOUT);
    drivebase->moveToPoint(-37, 47, DEFAULT_TIMEOUT, {}, false);
    clamp->toggle();

    drivebase->turnToPoint(-23.5, 23.5, DEFAULT_TIMEOUT, {}, false);
    intake->forward();
    drivebase->moveToPoint(-23.5, 23.5, DEFAULT_TIMEOUT, {}, false);
    intake->stop();

    drivebase->turnToPoint(0, 47, DEFAULT_TIMEOUT, {}, false);
    intake->forward();
    drivebase->moveToPoint(0, 47, DEFAULT_TIMEOUT, {}, false);
    intake->stop();

}

void autonomousSkillsBlue()
{
    drivebase->setPose(-60, 0, 90);
    
    // score
    drivebase->moveToPoint(-48, 0, DEFAULT_TIMEOUT);

    drivebase->turnToPoint(-24, -48, DEFAULT_TIMEOUT, {false});
    drivebase->moveToPoint(-24, -48, DEFAULT_TIMEOUT, {false}, false);
    // clamp

    drivebase->turnToPoint(0, -48, DEFAULT_TIMEOUT);
    drivebase->moveToPoint(0, -48, DEFAULT_TIMEOUT);

    drivebase->turnToPoint(0, -60, DEFAULT_TIMEOUT);
    drivebase->moveToPoint(0, -60, DEFAULT_TIMEOUT);

    drivebase->turnToPoint(-24, -24, DEFAULT_TIMEOUT);
    drivebase->moveToPoint(-24, -24, DEFAULT_TIMEOUT);

    drivebase->turnToPoint(-60, -60, DEFAULT_TIMEOUT);
    drivebase->moveToPoint(-60, -60, DEFAULT_TIMEOUT);

    


    // purple section
    
    drivebase->turnToPoint(23.5, -23.5, DEFAULT_TIMEOUT, {false});
    drivebase->moveToPoint(23.5, -23.5, DEFAULT_TIMEOUT, {false});

    // clamp goal

    drivebase->turnToPoint(23.5, -47.5, DEFAULT_TIMEOUT);
    drivebase->moveToPoint(23.5, -47.5, DEFAULT_TIMEOUT); // intake ring
    
    drivebase->turnToPoint(47.5, -47.5, DEFAULT_TIMEOUT);
    drivebase->moveToPoint(47.5, -47.5, DEFAULT_TIMEOUT); // intake ring

    drivebase->turnToPoint(47.5, -23.5, DEFAULT_TIMEOUT);
    drivebase->moveToPoint(47.5, -23.5, DEFAULT_TIMEOUT); // intake ring

    drivebase->turnToPoint(66.5, -66.5, DEFAULT_TIMEOUT);
    drivebase->moveToPoint(66.5, -66.5, DEFAULT_TIMEOUT); // put goal in corner

    // finished!

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
};