#ifndef __SUBSYSTEMS_ARM_H__
#define __SUBSYSTEMS_ARM_H__

#include "pros/motor_group.hpp"
#include "constants.h"

using namespace constants::arm;

enum class ArmState
{
    STOPPED,
    REVERSE,
    FORWARD,
};

class Arm : public pros::MotorGroup
{
public:
    Arm() : pros::MotorGroup({ARM_PORTS[0], ARM_PORTS[1]}) {
        // this->set_brake_mode(BRAKE_MODE);
    }

    inline void forward() { this->move_voltage(ARM_VOLTAGE); }

    inline void reverse() { this->move_voltage(-ARM_VOLTAGE); }

    inline void stop() { this->move_voltage(0); }

    void toggleForward() {
        if (state == ArmState::FORWARD) {
            state = ArmState::STOPPED;
        } else {
            state = ArmState::FORWARD;
        }
    }

    void toggleReverse() {
        if (state == ArmState::REVERSE) {
            state = ArmState::STOPPED;
        } else {
            state = ArmState::REVERSE;
        }
    }

    void periodic() {
        switch (state) {
            case ArmState::STOPPED:  return stop();
            case ArmState::FORWARD:  return forward();
            case ArmState::REVERSE:  return reverse();
        }
    }

private:
    ArmState state = ArmState::STOPPED;
};

#endif