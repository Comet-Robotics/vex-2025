#ifndef __SUBSYSTEMS_INTAKE_H__
#define __SUBSYSTEMS_INTAKE_H__

#include "pros/motor_group.hpp"
#include "constants.h"

using namespace constants::intake;
class Intake : public pros::MotorGroup
{
public:
    Intake() : pros::MotorGroup({PORTS[0], PORTS[1]}) {}

    void forward()
    {
        this->move_voltage(8000);
    }

    void reverse()
    {
        this->move_voltage(-8000);
    }

    void stop()
    {
        this->move_voltage(0);
    }

private:
};

#endif