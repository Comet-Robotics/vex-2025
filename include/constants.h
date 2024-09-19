#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <map>
#include "comets/vendor.h"
#include "comets/types.h"

namespace constants
{
    namespace drivebase
    {
        inline constexpr std::array<int8_t, 3> LEFT_PORTS = {
            7,
            -2,
            11,
        };
        inline constexpr std::array<int8_t, 3> RIGHT_PORTS = {
            -6,
            17,
            -8,
        };
        inline constexpr auto IMU_PORT = 5;

        inline constexpr auto CARTRIDGE = pros::MotorGearset::blue;
        inline constexpr auto WHEEL = lemlib::Omniwheel::NEW_325;
        inline constexpr auto TRACK_WIDTH = 12.5; // in inches
        inline constexpr auto DRIVETRAIN_RPM = 360;
        inline constexpr auto HORIZONTAL_DRIFT = 2;
    }

    inline constexpr double TELEOP_POLL_TIME = 10.0; // ms
}
#endif