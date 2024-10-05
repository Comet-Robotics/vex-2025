#ifndef __SUBSYSTEMS_H__
#define __SUBSYSTEMS_H__

#include "subsystems/drivebase.h"
#include "subsystems/intake.h"


inline Drivebase* drivebase = nullptr;  
inline Intake* intake = nullptr;        

// Initialize the subsystems
inline void subsystems_initialize() {
    drivebase = new Drivebase();
    intake = new Intake();
}

#endif
