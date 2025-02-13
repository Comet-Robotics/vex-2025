#ifndef __SUBSYSTEMS_H__
#define __SUBSYSTEMS_H__

#include "subsystems/drivebase.h"
#include "subsystems/intake.h"
#include "subsystems/clamp.h"
#include "subsystems/elevator.h"
#include "subsystems/arm.h"

inline Drivebase *drivebase = nullptr;
inline Intake *intake = nullptr;
inline Clamp *clamp = nullptr;
inline Elevator *elevator = nullptr;
inline Arm *arm = nullptr;

// Initialize the subsystems
inline void subsystems_initialize()
{
    drivebase = new Drivebase();
    drivebase->calibrateChassis(false);
    intake = new Intake();
    elevator = new Elevator();
    clamp = new Clamp();
    arm = new Arm();
}

#endif
