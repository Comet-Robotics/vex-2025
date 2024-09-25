#include "subsystems/intake.h"
#include "constants.h"
#include "pros/motor_group.hpp"

using namespace constants::intake;

pros::MotorGroup i_motors({
    PORTS[0],
    PORTS[1]}
);

Intake::Intake() {}

void Intake::forward() {
    i_motors.move_voltage(8000);
}

void Intake::reverse() {
    i_motors.move_voltage(-8000);
}

void Intake::stop() {
    i_motors.move_voltage(0);
}