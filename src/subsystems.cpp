#include "subsystems.h"

std::unique_ptr<Drivebase> drivebase = nullptr;

void subsystems_initialize()
{
    drivebase = std::make_unique<Drivebase>();
}