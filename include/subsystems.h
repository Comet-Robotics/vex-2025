#ifndef __SUBSYSTEMS_H__
#define __SUBSYSTEMS_H__

#include "subsystems/drivebase.h"
#include "subsystems/intake.h"
#include "subsystems/clamp.h";


inline Drivebase* drivebase = nullptr;  
inline Intake* intake = nullptr;  
inline Clamp* clamp = nullptr;      

// Initialize the subsystems
inline void subsystems_initialize() {
    drivebase = new Drivebase();
    intake = new Intake();
	clamp = new Clamp();
}

#endif
