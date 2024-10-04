#ifndef __SUBSYSTEMS_H__
#define __SUBSYSTEMS_H__

#include <memory>

#include "subsystems/drivebase.h"
#include "subsystems/intake.h"


extern Drivebase* drivebase;
extern Intake* intake;

void subsystems_initialize() {
	drivebase = new Drivebase();
	intake = new Intake();
}

#endif