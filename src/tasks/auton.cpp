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
    //once we create seperate code for each robot, their code will go here
}

//port whichever over to the other bot later whenever we code that
void autonomousSkillsRed()
{
    drivebase->setPose(-64, 47, 90);

    // Move to the first ring
    intake->forward();
    drivebase->moveToPoint(-47, 47, DEFAULT_TIMEOUT, {}, false);
    intake->stop();

    // Go get the mobile goal
    drivebase->turnAndMoveToPoint(-29, 47, DEFAULT_TIMEOUT, {.forwards = false}, {.forwards = false}, false);
    clamp->clamp();
    intake->forward(); // Once we have the mobile goal, put the ring onto it
    
    // Go get the next rings in sequence
    drivebase->turnAndMoveToPoint(-47, 47, DEFAULT_TIMEOUT);
    drivebase->turnAndMoveToPoint(0, 47, DEFAULT_TIMEOUT);
    drivebase->turnAndMoveToPoint(0, 59, DEFAULT_TIMEOUT);

    // Get back to edge of map from blue ring
    drivebase->turnAndMoveToPoint(-64, 40, DEFAULT_TIMEOUT);
    
    //Hopefully it goes to deposit
    drivebase->turnToPoint(-60, 60, DEFAULT_TIMEOUT);
    drivebase->moveToPoint(-60, -60, DEFAULT_TIMEOUT);
    
    // Deposit the mobile goal
    drivebase->turnToHeading(135, DEFAULT_TIMEOUT, {.direction = lemlib::AngularDirection::CCW_COUNTERCLOCKWISE});
    intake->stop();

    // ---- SECOND HALF/ORANGE CIRCLE ---- //


    // Grab the next mobile goal
    drivebase->moveToPoint(24, 24, DEFAULT_TIMEOUT);
    clamp->clamp();
    intake->forward();


    // Go get the 4 rings in the middle


    // Get the other two rings


    // fucked shit to knock the stupid ass blue ring away from corner + half intake the red bcs no room on mobile goal
    // (force mech team to put a fucking bar on a piston and it works probably)
    
    
    // grab final mobile goal and place all remaining red rings except one onto it
    // place final red ring on blue alliance wall stake

    
}

void autonomousSkillsBlue()
{
    drivebase->setPose(-60, 0, 90);
    
    intake->forward();
    // wait some amount of time?
    drivebase->moveToPoint(-48, 0, DEFAULT_TIMEOUT);
    
    // wait some more amount of time? although probably better to use sensor here
    intake->stop();

    drivebase->turnAndMoveToPoint(-24, -48, DEFAULT_TIMEOUT, {false}, {false}, false);
    clamp->clamp();
    pros::delay(300);

    drivebase->turnAndMoveToPoint(0, -48, DEFAULT_TIMEOUT);
    intake->forward();

    drivebase->turnAndMoveToPoint(0, -60, DEFAULT_TIMEOUT);
    drivebase->turnAndMoveToPoint(-24, -24, DEFAULT_TIMEOUT);
    drivebase->turnAndMoveToPoint(-60, -60, DEFAULT_TIMEOUT);

    // purple section
    
    drivebase->turnAndMoveToPoint(-23.5, -23.5, DEFAULT_TIMEOUT, {false}, {false}, false);
    clamp->clamp();

    drivebase->turnAndMoveToPoint(23.5, -47.5, DEFAULT_TIMEOUT); // intake ring
    drivebase->turnAndMoveToPoint(47.5, -47.5, DEFAULT_TIMEOUT); // intake ring
    drivebase->turnAndMoveToPoint(47.5, -23.5, DEFAULT_TIMEOUT); // intake ring
    drivebase->turnAndMoveToPoint(-66.5, -66.5, DEFAULT_TIMEOUT); // put goal in corner
    clamp->unclamp();

    // finished!

    
    drivebase->turnAndMoveToPoint(23.5, -28, DEFAULT_TIMEOUT);
    drivebase->turnAndMoveToPoint(23.5, -50, DEFAULT_TIMEOUT);
    
    clamp->clamp();

    // drivebase->turnAndMoveToPoint(48, -48, DE
    // clamp->clamp();
    // drivebase->turnAndMoveToPoint(48, -
    // clamp->clamp();
    
    drivebase->turnAndMoveToPoint(66.5, -66.5, DEFAULT_TIMEOUT);
    
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