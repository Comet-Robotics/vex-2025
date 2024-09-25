#include "subsystems.h"

std::unique_ptr<Drivebase> drivebase = nullptr;
std::unique_ptr<Intake> intake = nullptr;

void subsystems_initialize() {
	drivebase = std::make_unique<Drivebase>();
    intake = std::make_unique<Intake>();
}
