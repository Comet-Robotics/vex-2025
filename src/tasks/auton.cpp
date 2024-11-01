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
    // once we create seperate code for each robot, their code will go here
}

// port whichever over to the other bot later whenever we code that
void autonomousSkillsRed()
{
    
    drivebase->setPose(-64, 47, 90);

    // Move to the first ring
    intake->forward();
    drivebase->moveToPoint(-47, 47, DEFAULT_TIMEOUT, {}, false);
    intake->stop();

    // Go get the mobile goal
    drivebase->turnThenMoveToPoint(-29, 47, DEFAULT_TIMEOUT, {.forwards = false}, {.forwards = false}, false);
    clamp->clamp();
    intake->forward(); // Once we have the mobile goal, put the ring onto it
    
    // Go get the next rings in sequence
    drivebase->turnThenMoveToPoint(-47, 47);
    drivebase->turnThenMoveToPoint(0, 47);
    drivebase->turnThenMoveToPoint(0, 59);

    // Get back to edge of map from blue ring
    drivebase->turnThenMoveToPoint(-64, 40);
    
    // Hopefully it goes to deposit
    drivebase->turnThenMoveToPoint(-60, -60);

    // Deposit the mobile goal
    drivebase->turnToHeading(135, DEFAULT_TIMEOUT, {.direction = lemlib::AngularDirection::CCW_COUNTERCLOCKWISE}, false);
    clamp->unclamp();
    intake->stop();

    // ---- SECOND HALF/ORANGE CIRCLE ---- //


    // Grab the next mobile goal
    drivebase->turnThenMoveToPoint(24, 24,  DEFAULT_TIMEOUT, {.forwards = false}, {}, false);
    clamp->clamp();
    intake->forward();

    // Go get the 4 rings in the middle
    drivebase->turnThenMoveToPoint(3.6, 3.6);
    drivebase->turnThenMoveToPoint(0, 3.6);
    drivebase->turnThenMoveToPoint(-1.8, -1.8);
    drivebase->turnThenMoveToPoint(1.8, -1.8); // might be able to just be turn to point



    // Get the other two rings
    drivebase->turnThenMoveToPoint(24, 48);

    // fucked shit to knock the stupid ass blue ring away from corner + half intake the red bcs no room on mobile goal
    // (force mech team to put a fucking bar on a piston and it works probably)

    // Intake the corner red ring
    drivebase->turnThenMoveToPoint(66.5, 66.5, DEFAULT_TIMEOUT, {}, {}, false);
    pros::delay(300);
    intake->stop();

    // move backwards, turn around, and then deposit the mobile goal
    drivebase->turnThenMoveToPoint(48, 48, DEFAULT_TIMEOUT, {.forwards = false}, {.forwards = false});
    drivebase->turnThenMoveToPoint(66.5, 66.5, DEFAULT_TIMEOUT, {.forwards = false}, {.forwards = false}, false);
    clamp->unclamp();
    
    // grab final mobile goal and place all remaining red rings except one onto it
    // place final red ring on blue alliance wall stake
    
    // Grab final mobile goal
    drivebase->turnThenMoveToPoint(24, 24);
    drivebase->turnThenMoveToPoint(44, 4, DEFAULT_TIMEOUT, {.forwards = false}, {.forwards = false}, false);
    clamp->clamp();
    intake->forward();

    // Go get the ring we passed, place it and the held ring onto the mobile goal
    // TODO: After testing that everything works, go further to also get blue ring
    drivebase->turnThenMoveToPoint(48, 24, false);


    // Go get the remaining ring (dropping the mobile goal on the way) and score it onto the wall stake
    drivebase->turnThenMoveToPoint(60, 0);
    pros::delay(500);
    clamp->unclamp();
    drivebase->turnThenMoveToPoint(66.5, 0, DEFAULT_TIMEOUT, {.forwards = false}, {.forwards = false});
    intake->stop();
    drivebase->waitUntilStationary();
    intake->forward();
}

void autonomousSkillsBlue()
{
    drivebase->setPose(-60, 0, 90);
    
    intake->forward();
    pros::delay(500);
    drivebase->moveToPoint(-48, 0, DEFAULT_TIMEOUT);
    
    // wait some more amount of time? although probably better to use sensor here
    intake->stop();

    drivebase->turnThenMoveToPoint(-24, -48, DEFAULT_TIMEOUT, {.forwards = false}, {.forwards = false}, false);
    clamp->clamp();
    pros::delay(300);

    drivebase->turnThenMoveToPoint(0, -48);
    intake->forward();

    drivebase->turnThenMoveToPoint(0, -60);
    drivebase->turnThenMoveToPoint(-24, -24);
    drivebase->turnThenMoveToPoint(-60, -60);

    // purple section
    
    // go get far mobile goal
    drivebase->turnThenMoveToPoint(-23.5, -23.5, DEFAULT_TIMEOUT, {.forwards = false}, {.forwards = false}, false);
    clamp->clamp();

    // go get rings in sequence
    drivebase->turnThenMoveToPoint(23.5, -47.5); // intake ring
    drivebase->turnThenMoveToPoint(47.5, -47.5); // intake ring
    drivebase->turnThenMoveToPoint(47.5, -23.5); // intake ring

    // move to corner backwards and drop goal
    drivebase->turnThenMoveToPoint(-66.5, -66.5, DEFAULT_TIMEOUT, {.forwards = false}, {.forwards = false}, false); // put goal in corner
    clamp->unclamp();

    // finished!

    
    drivebase->turnThenMoveToPoint(23.5, -28);

    clamp->clamp();

    
    drivebase->turnThenMoveToPoint(66.5, -66.5);
    
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