#include "liblvgl/llemu.hpp"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/llemu.hpp"
#include "subsystems.h"
#include "tasks/auton.h"
#include "constants.h"

using namespace pros;

pros::Controller controller(pros::E_CONTROLLER_MASTER);


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
inline constexpr AutonMode MODE = AutonMode::VS;

void autonomousTest()
{
    // set position to x:0, y:0, heading:0
    drivebase->setPose(0, 0, 0);

    pros::delay(100);
    lcd::print(0, "X: %f", drivebase->getPose().x);
    lcd::print(1, "Y: %f", drivebase->getPose().y);
    lcd::print(2, "Theta: %f", drivebase->getPose().theta);
    lcd::print(3, "Rotation Sensor: %i", constants::drivebase::VERTICAL_ROTATION.get_position());

    pros::delay(3000);

    drivebase->moveToPoint(0, -48, 5000, {.forwards = false});

    pros::delay(3000);
    lcd::print(0, "X: %f", drivebase->getPose().x);
    lcd::print(1, "Y: %f", drivebase->getPose().y);
    lcd::print(2, "Theta: %f", drivebase->getPose().theta);
    lcd::print(3, "Rotation Sensor: %i", constants::drivebase::VERTICAL_ROTATION.get_position());
}

ASSET(avoidTowerRed_txt)
// port whichever over to the other bot later whenever we code that
void autonomousSkillsRed()
{
    
    drivebase->setPose(-58.5, 48, 90);
    clamp->unclamp();

    // Move to the first ring
    intake->forward();
    drivebase->turnThenMoveToPoint(-48, 48, DEFAULT_TIMEOUT);

    // Go get the mobile goal
    drivebase->turnThenMoveToPoint(-20, 48, DEFAULT_TIMEOUT, {.forwards = false}, {.forwards = false, .maxSpeed = 63}, false);
    clamp->clamp();
    pros::delay(200);
    elevator->forward(); // score ring from field

    // Go get the next rings in sequence
    drivebase->turnThenMoveToPoint(-24, 24);
    drivebase->turnThenMoveToPoint(0, 47);
    drivebase->turnThenMoveToPoint(0, 59);

    // why does this work
    // drivebase->setPose(drivebase->getPose().x + 6, drivebase->getPose().y, drivebase->getPose().theta);
    
    // Get the ring in the corner
    drivebase->turnThenMoveToPoint(-59, 59, false);
    
    // Back up
    drivebase->turnThenMoveToPoint(-50, 50, DEFAULT_TIMEOUT, {.forwards = false}, {.forwards = false});

    // turn around and deposit the mobile goal
    drivebase->turnThenMoveToPoint(-60, 60, DEFAULT_TIMEOUT, {.forwards = false}, {.forwards = false}, false);
    clamp->unclamp();
    intake->stop();
    elevator->stop();

    // ---- SECOND HALF/ORANGE CIRCLE ---- //

    // Move out of the corner 
    drivebase->turnThenMoveToPoint(-48, 48);
    
    //avoid the middle while going to the next mobile goal (choose between these)
    // drivebase->follow(avoidTowerRed_txt, 15, DEFAULT_TIMEOUT, false); 
    drivebase->turnThenMoveToPoint(-16, 48);
    drivebase->turnToPoint(-16, 63, DEFAULT_TIMEOUT, {.forwards = false}, false);
    drivebase->arcade(-63, 0);
    pros::delay(1500);
    drivebase->setHeading(180);
    drivebase->moveToPoint(-16, 60, DEFAULT_TIMEOUT, {.forwards = false});
    drivebase->turnThenMoveToPoint(26, 22,  DEFAULT_TIMEOUT, {.forwards = false}, {.forwards = false, .maxSpeed = 40}, false);
    
    // Clamp mobile goal
    clamp->clamp();
    pros::delay(200);
    intake->forward();
    elevator->forward();

    // Go get the 4 rings in the middle
    drivebase->turnThenMoveToPoint(3, 3);
    drivebase->turnThenMoveToPoint(-6, 3);
    drivebase->turnThenMoveToPoint(-3, -6);
    drivebase->turnThenMoveToPoint(6, -6); // might be able to just be turn to point

    // Get the other two rings
    drivebase->turnThenMoveToPoint(24, 48);
    drivebase->turnThenMoveToPoint(48, 48);

    // fucked shit to knock the stupid ass blue ring away from corner + half intake the red bcs no room on mobile goal
    // (force mech team to put a fucking bar on a piston and it works probably)

    // Intake the corner red ring DONT PUT ON MOGO
    drivebase->turnThenMoveToPoint(60, 60, DEFAULT_TIMEOUT, {}, {}, false);
    pros::delay(300);
    intake->stop();
    elevator->stop();

    // move backwards, turn around, and then deposit the mobile goal
    drivebase->turnThenMoveToPoint(50, 50, DEFAULT_TIMEOUT, {.forwards = false}, {.forwards = false});
    drivebase->turnThenMoveToPoint(60, 60, DEFAULT_TIMEOUT, {.forwards = false}, {.forwards = false}, false);
    clamp->unclamp();
    
    // grab final mobile goal and place all remaining red rings except one onto it
    // place final red ring on blue alliance wall stake
    
    // Grab final mobile goal
    drivebase->turnThenMoveToPoint(24, 24);
    drivebase->turnThenMoveToPoint(44, 4, DEFAULT_TIMEOUT, {.forwards = false}, {.forwards = false}, false);
    clamp->clamp();
    pros::delay(200);
    elevator->forward();
    intake->forward();

    // Go get the ring we passed, place it and the held ring onto the mobile goal
    // TODO: After testing that everything works, go further to also get blue ring
    drivebase->turnThenMoveToPoint(48, 24);
    drivebase->turnThenMoveToPoint(48, 27);
    // maybe go a little further to get blue ring (pushed off) after red ring


    // Go get the remaining ring (dropping the mobile goal on the way) and score it onto the wall stake
    drivebase->turnThenMoveToPoint(60, 0);
    pros::delay(500);
    clamp->unclamp();
    drivebase->turnThenMoveToPoint(66.5, 0, DEFAULT_TIMEOUT, {.forwards = false}, {.forwards = false}, false);
    elevator->stop();
    drivebase->waitUntilStationary();
    //score wallstake
    elevator->forward();
    pros::delay(2000);
    intake->stop();
    elevator->stop();
}

void autonomousSkills()
{
    // once we create seperate code for each robot, their code will go here
    autonomousSkillsRed();
}


void autonomousVS()
{
    drivebase->setPose(-56, 12, -90);
    clamp->unclamp();

    // drive to middle mobile goal and clamp
    drivebase->moveToPoint(-20.78, 12, DEFAULT_TIMEOUT, {.forwards = false});
    drivebase->turnThenMoveToPoint(-5.19, 3, DEFAULT_TIMEOUT, {.forwards = false}, {.forwards = false, .maxSpeed = 41}, false);
    clamp->clamp();
    pros::delay(200);

    // drive to red/blue goal stack
    drivebase->moveToPoint(-10, 5, DEFAULT_TIMEOUT);
    intake->forward();
    drivebase->turnThenMoveToPoint(-24, 48);

    // spit out blue ring and grab red ring
    drivebase->turnToHeading(90, DEFAULT_TIMEOUT, {}, false);
    intake->reverse();
    pros::delay(500);
    intake->forward();
    elevator->forward();
    drivebase->turnThenMoveToPoint(-28, 58);
    
    // drive to blue/red goal stack and grab red ring
    drivebase->turnThenMoveToPoint(-48, 48);

    // corner intaking!
    // enter corner with intake reversed, then once in corner, put intake forward
    drivebase->turnThenMoveToPoint(-64, 64);
    intake->reverse();
    drivebase->waitUntilStationary();
    intake->forward();
    pros::delay(2000); // TODO: tune

    drivebase->turnThenMoveToPoint(-60, 60, DEFAULT_TIMEOUT, {.forwards = false}, {.forwards = false});
    intake->stop();
    elevator->stop();
    drivebase->turnThenMoveToPoint(-36, -36, DEFAULT_TIMEOUT, {.forwards = false}, {.forwards = false});
    drivebase->turnThenMoveToPoint(-12, -36);
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
    // drivebase->calibrateChassis(true);
};