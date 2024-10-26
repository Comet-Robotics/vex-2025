#ifndef __SUBSYSTEMS_INTAKE_H__
#define __SUBSYSTEMS_INTAKE_H__

#include "pros/motor_group.hpp"
#include "constants.h"

using namespace constants::intake;

enum class IntakeState
{
    STOPPED,
    REVERSE,
    FORWARD,
};

class Intake : public pros::MotorGroup
{
public:
    Intake() : pros::MotorGroup({PORTS[0], PORTS[1]}) {}

    inline void forward() { this->move_voltage(INTAKE_VOLTAGE); }

    inline void reverse() { this->move_voltage(-INTAKE_VOLTAGE); }

    inline void stop() { this->move_voltage(0); }

    void toggleForward() {
        if (state == IntakeState::FORWARD) {
            state = IntakeState::STOPPED;
        } else {
            state = IntakeState::FORWARD;
        }
    }

    void toggleReverse() {
        if (state == IntakeState::REVERSE) {
            state = IntakeState::STOPPED;
        } else {
            state = IntakeState::REVERSE;
        }
    }

    void periodic() {
        switch (state) {
            case IntakeState::STOPPED:  return stop();
            case IntakeState::FORWARD:  return forward();
            case IntakeState::REVERSE:  return reverse();
        }
    }

private:
    IntakeState state = IntakeState::STOPPED;
};

#endif