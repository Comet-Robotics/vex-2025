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
inline constexpr AutonMode MODE = AutonMode::TEST;

void autonomousTest()
{
    // drivebase->calibrateChassis(true);

    // set position to x:0, y:0, heading:0
    drivebase->setPose(0, 0, 0);

    pros::delay(100);
    lcd::print(0, "X: %f", drivebase->getPose().x);
    lcd::print(1, "Y: %f", drivebase->getPose().y);
    lcd::print(2, "Theta: %f", drivebase->getPose().theta);
    lcd::print(3, "Rotation Sensor: %i", constants::drivebase::VERTICAL_ROTATION.get_position());

    
    drivebase->moveToPoint(0, 48, DEFAULT_TIMEOUT, {}, false);
    // drivebase->turnToHeading(270, DEFAULT_TIMEOUT, {}, false);

    pros::delay(500);

    lcd::print(0, "X: %f", drivebase->getPose().x);
    lcd::print(1, "Y: %f", drivebase->getPose().y);
    lcd::print(2, "Theta: %f", drivebase->getPose().theta);
    lcd::print(3, "Rotation Sensor: %i", constants::drivebase::VERTICAL_ROTATION.get_position());
}

ASSET(avoidTower_txt)
void autonomousSkills()
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


void autonomousVS(){
    drivebase->setPose(-60, -12, 0);
    clamp->unclamp();

    // grab first ring and put on alliance wall stake
    intake->forward();
    drivebase->moveToPoint(-60, 0, DEFAULT_TIMEOUT);
    drivebase->turnThenMoveToPoint(-66, 0, DEFAULT_TIMEOUT, {.forwards = false}, {.forwards = false}, false);
    elevator->forward();
    pros::delay(1000);

    // grab mobile goal
    drivebase->moveToPoint(-60, 0, DEFAULT_TIMEOUT);
    drivebase->turnThenMoveToPoint(-48, 0, DEFAULT_TIMEOUT, {.forwards = false}, {.forwards = false}, false);
    clamp->clamp();
    
    // grab ring from blue/red stack
    drivebase->turnThenMoveToPoint(-48, -48);
    intake->stop();
    drivebase->turnThenMoveToPoint(-48, -58);
    drivebase->turnThenMoveToPoint(-48, -48, DEFAULT_TIMEOUT, {.forwards = false}, {.forwards = false});
    intake->forward();
    drivebase->turnThenMoveToPoint(-24, -48);
    pros::delay(500);
    elevator->stop();

    // grab ring from red/blue stack (make sure to spit out bottom blue ring)
    drivebase->turnToHeading(-45, DEFAULT_TIMEOUT, {}, false);
    intake->reverse();
    pros::delay(500);
    intake->forward();
    elevator->forward();
    drivebase->turnThenMoveToPoint(-18, -48);

    drivebase->turnThenMoveToPoint(-48, -48, DEFAULT_TIMEOUT, {.forwards = false}, {.forwards = false});

    // corner intake
    drivebase->turnThenMoveToPoint(-64, -64);
    intake->reverse();
    drivebase->waitUntilStationary();
    intake->forward();
    pros::delay(4000); // TODO: tune
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