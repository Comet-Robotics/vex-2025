#include "main.h"

#include "liblvgl/llemu.hpp"
#include "subsystems.h"
#include "tasks/auton.h"
#include "tasks/teleop.h"

#include "cmdlib/commandPtr.h"
// #include "cmdlib/commandScheduler.h"
// #include "cmdlib/parallelCommandGroup.h"
// #include "cmdlib/sequentialCommandGroup.h"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	subsystems_initialize();
	autonomous_initialize();
	opcontrol_initialize();
}

void disabled() {}
void competition_initialize() {}