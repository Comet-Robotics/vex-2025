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
inline constexpr AutonMode MODE = AutonMode::SKILLS;

void autonomousTest()
{
    drivebase->calibrateChassis(true);

    // set position to x:0, y:0, heading:0
    drivebase->setPose(0, 0, 0);

    pros::delay(100);
    lcd::print(0, "X: %f", drivebase->getPose().x);
    lcd::print(1, "Y: %f", drivebase->getPose().y);
    lcd::print(2, "Theta: %f", drivebase->getPose().theta);
    lcd::print(3, "Rotation Sensor: %i", constants::drivebase::VERTICAL_ROTATION.get_position());

    pros::delay(3000);

    drivebase->moveToPoint(0, -48, 5000, {.forwards = false}, true);

    lcd::print(0, "X: %f", drivebase->getPose().x);
    lcd::print(1, "Y: %f", drivebase->getPose().y);
    lcd::print(2, "Theta: %f", drivebase->getPose().theta);
    lcd::print(3, "Rotation Sensor: %i", constants::drivebase::VERTICAL_ROTATION.get_position());
}

ASSET(avoidTowerRed_txt)
// port whichever over to the other bot later whenever we code that
void autonomousSkillsRed()
{
    drivebase->setPose(-64, 32, -90);

    // -- RED SECTION --

    // drive to first mobile goal and grab it
    drivebase->turnThenMoveToPoint(-48, 32, DEFAULT_TIMEOUT, {.forwards = false}, {.forwards = false});
    drivebase->turnThenMoveToPoint(-24, 48, DEFAULT_TIMEOUT, {.forwards = false}, {.forwards = false}, false);
    clamp->clamp();
    pros::delay(100);
    intake->forward();
    elevator->forward();

    // Go get the 1 ring on diagonal and 4 rings in the middle
    drivebase->turnThenMoveToPoint(-24, -24);
    drivebase->turnThenMoveToPoint(-3, -3);
    drivebase->turnThenMoveToPoint(6, 3);
    drivebase->turnThenMoveToPoint(3, -6);
    drivebase->turnThenMoveToPoint(-6, -6);

    // Go to corner
    drivebase->turnThenMoveToPoint(-12, 12);
    drivebase->turnThenMoveToPoint(-64, 64, DEFAULT_TIMEOUT, {}, {}, false);
    elevator->stop();
    
    // Back up then turn around and deposit the mobile goal
    drivebase->turnThenMoveToPoint(-50, 50, DEFAULT_TIMEOUT, {.forwards = false}, {.forwards = false});
    drivebase->turnThenMoveToPoint(-60, 60, DEFAULT_TIMEOUT, {.forwards = false}, {.forwards = false}, false);
    clamp->unclamp();


    // -- ORANGE SECTION --

    // Go to and grab mobile goal
    drivebase->turnThenMoveToPoint(0, 0);
    drivebase->turnThenMoveToPoint(24, 24, DEFAULT_TIMEOUT, {.forwards = false}, {.forwards = false}, false);
    clamp->clamp();
    pros::delay(100);

    // Get rings
    drivebase->turnThenMoveToPoint(0, 48);
    drivebase->turnThenMoveToPoint(0, 56);
}
ASSET(avoidTower_txt)
void autonomousSkillsBlue()
{
    drivebase->setPose(-64, 0, 90);
    
    intake->forward();
    drivebase->moveToPoint(-48, 0, DEFAULT_TIMEOUT);
    drivebase->moveToPoint(-65, 0, DEFAULT_TIMEOUT, {.forwards = false}, false); // consider making async and adding small delay if needed
    elevator->forward();
    pros::delay(1000);

    drivebase->moveToPoint(-60, 0, DEFAULT_TIMEOUT);
    drivebase->turnThenMoveToPoint(-24, -48, DEFAULT_TIMEOUT, {.forwards = false}, {.forwards = false}, false);
    clamp->clamp();
    intake->forward();
    pros::delay(300);

    drivebase->turnThenMoveToPoint(0, -47);

    drivebase->turnThenMoveToPoint(0, -60);
    drivebase->turnThenMoveToPoint(-24, -24);
    drivebase->turnThenMoveToPoint(-60, -60); // Make sure it actually intakes/goes without hitting wall
    drivebase->moveToPoint(-50, -50, DEFAULT_TIMEOUT, {.forwards=false}); // Tune exact value later
    drivebase->turnThenMoveToPoint(-60, -60, DEFAULT_TIMEOUT, {.forwards = false}, {.forwards = false}, false);
    clamp->unclamp();

    elevator->stop();

    // purple section
    
    // go get far mobile goal
    drivebase->moveToPoint(-50, -50, DEFAULT_TIMEOUT); // back up from corner
    
    // avoid tower (choose either of these)
    // drivebase->follow(avoidTower_txt, 15, DEFAULT_TIMEOUT, false);
    drivebase->turnThenMoveToPoint(0, -47);
    drivebase->turnThenMoveToPoint(23.5, -23.5, DEFAULT_TIMEOUT, {.forwards = false}, {.forwards = false}, false);
    
    clamp->clamp();
    pros::delay(300);
    elevator->forward();

    // go get rings in sequence
    drivebase->turnThenMoveToPoint(23.5, -47.5); // intake ring
    drivebase->turnThenMoveToPoint(47.5, -47.5); // intake ring
    drivebase->turnThenMoveToPoint(47.5, -23.5); // intake ring, go a little forward more

    drivebase->turnThenMoveToPoint(60, -60, DEFAULT_TIMEOUT, {}, {}, false);

    drivebase->turnThenMoveToPoint(50, -50, DEFAULT_TIMEOUT, {.forwards = false}, {.forwards = false}, false);
    
    // move to corner backwards and drop goal
    drivebase->turnThenMoveToPoint(60, -60, DEFAULT_TIMEOUT, {.forwards = false}, {.forwards = false}, false); // put goal in corner
    clamp->unclamp();
    //go to the tower and climb
    // finished!

    // Consider partner climbing in auton for points
    drivebase->turnThenMoveToPoint(23.5, -28);

    clamp->clamp();

    
    drivebase->turnThenMoveToPoint(66.5, -66.5);
    
}

void autonomousSkills()
{
    // once we create seperate code for each robot, their code will go here
    autonomousSkillsRed();
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