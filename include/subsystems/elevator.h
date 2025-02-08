#ifndef __SUBSYSTEMS_ELEVATOR_H__
#define __SUBSYSTEMS_ELEVATOR_H__

#include "pros/motor_group.hpp"
#include "constants.h"

using namespace constants::elevator;

enum class ElevatorState
{
    STOPPED,
    REVERSE,
    FORWARD,
};

class Elevator : public pros::MotorGroup
{
public:
    Elevator() : pros::MotorGroup({ELEVATOR_PORTS[0], ELEVATOR_PORTS[1]}) {}

    inline void forward() { this->move_voltage(ELEVATOR_VOLTAGE); }

    inline void reverse() { this->move_voltage(-ELEVATOR_VOLTAGE); }

    inline void stop() { this->move_voltage(0); }

    void toggleForward() {
        if (state == ElevatorState::FORWARD) {
            state = ElevatorState::STOPPED;
        } else {
            state = ElevatorState::FORWARD;
        }
    }

    void toggleReverse() {
        if (state == ElevatorState::REVERSE) {
            state = ElevatorState::STOPPED;
        } else {
            state = ElevatorState::REVERSE;
        }
    }

    void periodic() {
        switch (state) {
            case ElevatorState::STOPPED:  return stop();
            case ElevatorState::FORWARD:  return forward();
            case ElevatorState::REVERSE:  return reverse();
        }
    }

private:
    ElevatorState state = ElevatorState::STOPPED;
};

#endif