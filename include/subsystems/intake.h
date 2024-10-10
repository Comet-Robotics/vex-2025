#ifndef __SUBSYSTEMS_INTAKE_H__
#define __SUBSYSTEMS_INTAKE_H__

#include "pros/motor_group.hpp"
#include "constants.h"

using namespace constants::intake;

enum class IntakeState
{
    IDLE,
    REVERSE,
    FORWARD,
};

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

    void toggleForward()
    {
        if (state == IntakeState::FORWARD)
        {
            state = IntakeState::IDLE;
        }
        else
        {
            state = IntakeState::FORWARD;
        }
    }

    void toggleReverse()
    {
        if (state == IntakeState::REVERSE)
        {
            state = IntakeState::IDLE;
        }
        else
        {
            state = IntakeState::REVERSE;
        }
    }

    void stop()
    {
        this->move_voltage(0);
    }

    void periodic()
    {
        switch (state)
        {
        case IntakeState::IDLE:
        {
            stop();
            break;
        }
        case IntakeState::FORWARD:
        {
            forward();
            break;
        }
        case IntakeState::REVERSE:
        {
            reverse();
            break;
        }
        }
    }

private:
    IntakeState state = IntakeState::IDLE;
};

#endif