#ifndef __SUBSYSTEMS_H__
#define __SUBSYSTEMS_H__

#include <memory>
#include "subsystems/drivebase.h"

extern std::unique_ptr<Drivebase> drivebase;

void subsystems_initialize();

#endif