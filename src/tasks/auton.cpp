#include "tasks/auton.h"
#include "subsystems.h"

void autonomous_initialize()
{
    drivebase->calibrate();
}

void autonomous()
{
    drivebase->moveToPose(10, 10, 90, 4000, false); // move the chassis to (10, 10, 90)
}