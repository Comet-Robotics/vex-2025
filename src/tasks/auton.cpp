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
    // drivebase->calibrateChassis(true);

    // set position to x:0, y:0, heading:0
    drivebase->setPose(0, 0, 0);

    pros::delay(100);
    lcd::print(0, "X: %f", drivebase->getPose().x);
    lcd::print(1, "Y: %f", drivebase->getPose().y);
    lcd::print(2, "Theta: %f", drivebase->getPose().theta);
    lcd::print(3, "Rotation Sensor: %i", constants::drivebase::VERTICAL_ROTATION.get_position());

    
    drivebase->moveToPoint(0, 48, DEFAULT_TIMEOUT, {}, false);
    // drivebase->turnToHeading(180, DEFAULT_TIMEOUT, {}, false);

    pros::delay(500);

    lcd::print(0, "X: %f", drivebase->getPose().x);
    lcd::print(1, "Y: %f", drivebase->getPose().y);
    lcd::print(2, "Theta: %f", drivebase->getPose().theta);
    lcd::print(3, "Rotation Sensor: %i", constants::drivebase::VERTICAL_ROTATION.get_position());
}

ASSET(avoidTower_txt)
void autonomousSkills()
{
    drivebase->setPose(-60, 0, 90);
    
    intake->forward();
    drivebase->moveToPoint(-48, 0, DEFAULT_TIMEOUT);

    drivebase->turnThenMoveToPoint(-24, -48, DEFAULT_TIMEOUT, {.forwards = false}, {.forwards = false, .maxSpeed = 63}, false);
    clamp->clamp();
    pros::delay(300);
    elevator->forward();

    drivebase->turnThenMoveToPoint(0, -47);

    drivebase->turnThenMoveToPoint(0, -60);
    drivebase->turnThenMoveToPoint(-24, -24);
    drivebase->turnThenMoveToPoint(-63, -63, 2000); // Make sure it actually intakes/goes without hitting wall
    drivebase->moveToPoint(-50, -50, DEFAULT_TIMEOUT, {.forwards=false}); // Tune exact value later
    elevator->reverse();
    pros::delay(500);
    elevator->forward();
    drivebase->turnThenMoveToPoint(-62, -62, 2000, {.forwards = false}, {.forwards = false}, false);
    elevator->reverse();

    clamp->unclamp();

    pros::delay(300);

    elevator->stop();

    // purple section
    
    // go get far mobile goal
    drivebase->moveToPoint(-50, -50, DEFAULT_TIMEOUT); // back up from corner
    
    /*
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
    */
    
}


void autonomousVS(){
    drivebase->setPose(-55.5, -31.5, 180);
    clamp->unclamp();


    // grab mobile goal
    drivebase->moveToPoint(-48, -24, DEFAULT_TIMEOUT, {.forwards = false, .maxSpeed = 80});
    drivebase->moveToPoint(-48, 0, DEFAULT_TIMEOUT, {.forwards = false, .maxSpeed = 80}, false);
    clamp->clamp();
    pros::delay(200);

    intake->forward();
    elevator->forward();

    drivebase->turnThenMoveToPoint(-58, 0, DEFAULT_TIMEOUT);

    
    // grab ring from blue/red stack
    drivebase->turnThenMoveToPoint(-48, -48);
    intake->stop();
    drivebase->turnThenMoveToPoint(-48, -58);
    drivebase->turnThenMoveToPoint(-48, -48, DEFAULT_TIMEOUT, {.forwards = false}, {.forwards = false});
    intake->forward();
    drivebase->turnThenMoveToPoint(-28, -48);
    pros::delay(500);
    elevator->stop();
    

    // grab ring from red/blue stack (make sure to spit out bottom blue ring)
    drivebase->turnThenMoveToPoint(-36, -48, DEFAULT_TIMEOUT, {.forwards = false}, {.forwards = false});
    drivebase->turnToHeading(-45, DEFAULT_TIMEOUT, {}, false);
    drivebase->moveToPoint(-48, -36, DEFAULT_TIMEOUT);
    drivebase->moveToPoint(-24, -48, DEFAULT_TIMEOUT, {.forwards = false});
    intake->reverse();
    pros::delay(500);
    intake->forward();
    elevator->forward();
    drivebase->turnThenMoveToPoint(-12, -48);

    drivebase->turnThenMoveToPoint(-48, -48, DEFAULT_TIMEOUT, {.forwards = false}, {.forwards = false});

    // corner intake
    drivebase->turnThenMoveToPoint(-64, -64, 2000);
    intake->reverse();
    drivebase->waitUntilStationary();
    intake->forward();
    pros::delay(4000); // TODO: tune

    drivebase->turnThenMoveToPoint(-50, -50, DEFAULT_TIMEOUT, {.forwards = false}, {.forwards = false});
    drivebase->turnThenMoveToPoint(-64, -64, 2000, {.forwards = false}, {.forwards = false}, false);
    clamp->unclamp();

    drivebase->turnThenMoveToPoint(-50, -50);
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