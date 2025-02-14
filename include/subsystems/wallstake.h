//same as intake.h but with arm
//two motors rotating in one direction (one clockwise, one counter-clockwise)
    //other motion for reverse

#ifndef __SUBSYSTEMS_INTAKE_H__
#define __SUBSYSTEMS_INTAKE_H__

#include "pros/motor_group.hpp"
#include "constants.h"

using namespace constants::wallstake;

enum class WallstakeState
{
    STOPPED,
    REVERSE,
    FORWARD,
};

class Wallstake : public pros::MotorGroup
{
public:
    Wallstake() : pros::MotorGroup({WALLSTAKE_PORTS[0], WALLSTAKE_PORTS[1]}) {}

    inline void forward() { this->move_voltage(WALLSTAKE_VOLTAGE); }

    inline void reverse() { this->move_voltage(-WALLSTAKE_VOLTAGE); }

    inline void stop() { this->move_voltage(0); }

    //toggle = button start / stop, not press and hold

private:    
    WallstakeState state = WallstakeState::STOPPED;
};



#endif