#ifndef __SUBSYSTEMS_H__
#define __SUBSYSTEMS_H__

#include "subsystems/drivebase.h"
#include "subsystems/intake.h"
#include "subsystems/clamp.h"
#include "subsystems/elevator.h"

inline Drivebase *drivebase = nullptr;
inline Intake *intake = nullptr;
inline Clamp *clamp = nullptr;
inline Elevator *elevator = nullptr;

// Initialize the subsystems
inline void subsystems_initialize()
{
    drivebase = new Drivebase();
    drivebase->calibrateChassis(false);
    intake = new Intake();
    elevator = new Elevator();
    clamp = new Clamp();
}

#endif
