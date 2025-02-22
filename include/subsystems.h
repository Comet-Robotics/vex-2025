#ifndef __SUBSYSTEMS_H__
#define __SUBSYSTEMS_H__

#include "constants.h"
#include "subsystems/drivebase.h"
#include "subsystems/intake.h"
#include "subsystems/clamp.h"
#include "subsystems/elevator.h"
#include "subsystems/arm.h"
#include "subsystems/dropdown.h"

inline Drivebase *drivebase = nullptr;
inline Intake *intake = nullptr;
inline Clamp *clamp = nullptr;
inline Elevator *elevator = nullptr;
inline Arm *arm = nullptr;
inline Dropdown *dropdown = nullptr;

// Initialize the subsystems
inline void subsystems_initialize()
{
    drivebase = new Drivebase();
    intake = new Intake();
    elevator = new Elevator();
    clamp = new Clamp();
    arm = new Arm();
    dropdown = new Dropdown();

    drivebase->calibrateChassis(true);
    drivebase->setBrakeMode(constants::drivebase::DRIVE_BRAKE_MODE);
    arm->set_brake_mode(constants::arm::ARM_BRAKE_MODE);
}

#endif
