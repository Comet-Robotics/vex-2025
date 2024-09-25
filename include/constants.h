#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "pros/abstract_motor.hpp"
#include <array>
#include <cstdint>

namespace constants
{
    using namespace pros;
    inline constexpr bool USE_TANK = false;

    namespace drivebase
    {
        // front, middle, back, top
        inline constexpr std::array<int8_t, 4> LEFT_PORTS = {
            0,
            0,
            0,
            0
        };
        inline constexpr std::array<int8_t, 4> RIGHT_PORTS = {
            0,
            0,
            0,
            0
        };

        inline constexpr double DRIVETRAIN_WIDTH = 11.292; //this is CAD based and will require tuning
        inline constexpr int8_t IMU_PORT = 0;

        inline constexpr auto CHASSIS_INTERNAL_GEARSET = pros::v5::MotorGears::blue;
    }

    namespace intake
    {
        // left, right
        inline constexpr std::array<int8_t, 2> PORTS = {
            0,
            0
        };

        // uses basic motors, which doesn't requre gearset to be configured in code
    }

    inline constexpr double TELEOP_POLL_TIME = 10.0; // ms

}
#endif