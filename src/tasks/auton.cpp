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
    
    drivebase->setPose(-64, 47, 90);

    // Move to the first ring
    intake->forward();
    drivebase->turnThenMoveToPoint(-47, 47, DEFAULT_TIMEOUT);

    // Go get the mobile goal
    drivebase->turnThenMoveToPoint(-29, 47, DEFAULT_TIMEOUT, {.forwards = false}, {.forwards = false}, false);
    clamp->clamp();
    pros::delay(200);
    elevator->forward(); // score ring from field
    

    // Go get the next rings in sequence
    drivebase->turnThenMoveToPoint(-24, 24);
    drivebase->turnThenMoveToPoint(0, 47);
    drivebase->turnThenMoveToPoint(0, 59);
    
    // Get the ring in the corner
    drivebase->turnThenMoveToPoint(-62, 62);
    
    // Back up
    drivebase->turnThenMoveToPoint(-50, 50, DEFAULT_TIMEOUT, {.forwards = false}, {.forwards = false});

    // turn around and deposit the mobile goal
    drivebase->turnThenMoveToPoint(-60, 60, DEFAULT_TIMEOUT, {.forwards = false}, {.forwards = false}, false);
    clamp->unclamp();
    intake->stop();
    elevator->stop();

    // ---- SECOND HALF/ORANGE CIRCLE ---- //

    // Move out of the corner 
    drivebase->turnThenMoveToPoint(-50, 50);
    
    //avoid the middle while going to the next mobile goal (choose between these)
    // drivebase->follow(avoidTowerRed_txt, 15, DEFAULT_TIMEOUT, false); 
    drivebase->turnThenMoveToPoint(0, 47);
    drivebase->turnThenMoveToPoint(24, 24,  DEFAULT_TIMEOUT, {.forwards = false}, {.forwards = false}, false);
    
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
    elevator->forward();
    intake->forward();

    // Go get the ring we passed, place it and the held ring onto the mobile goal
    // TODO: After testing that everything works, go further to also get blue ring
    drivebase->turnThenMoveToPoint(48, 27, false);
    // maybe go a little further to get blue ring (pushed off) after red ring


    // Go get the remaining ring (dropping the mobile goal on the way) and score it onto the wall stake
    drivebase->turnThenMoveToPoint(60, 0);
    pros::delay(500);
    clamp->unclamp();
    drivebase->turnThenMoveToPoint(66.5, 0, DEFAULT_TIMEOUT, {}, {}, false);
    intake->stop();
    drivebase->waitUntilStationary();
    //score wallstake
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