#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "pros/abstract_motor.hpp"
#include <array>
#include <cstdint>
#include "lemlib/api.hpp"

namespace constants
{
    // using namespace pros;
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

        // front, middle, back, top
        inline constexpr std::array<int8_t, 4> RIGHT_PORTS = {
            0,
            0,
            0,
            0
        };

        inline constexpr double DRIVETRAIN_WIDTH = 11.292; //this is CAD based and will require tuning
        inline constexpr int8_t IMU_PORT = 0;

        inline constexpr auto CHASSIS_INTERNAL_GEARSET = pros::v5::MotorGears::blue;



        // lateral PID controller
        inline const lemlib::ControllerSettings lateral_controller(
            0, // proportional gain (kP)
            0, // integral gain (kI)
            0, // derivative gain (kD)
            3, // anti windup
            1, // small error range, in inches
            100, // small error range timeout, in milliseconds
            3, // large error range, in inches
            500, // large error range timeout, in milliseconds
            20 // maximum acceleration (slew)
        );

        // angular PID controller
        inline const lemlib::ControllerSettings angular_controller(
            0, // proportional gain (kP)
            0, // integral gain (kI)
            0, // derivative gain (kD)
            0, //3, // anti windup
            0, //1, // small error range, in degrees
            0, //100, // small error range timeout, in milliseconds
            0, //3, // large error range, in degrees
            0, //500, // large error range timeout, in milliseconds
            0 // maximum acceleration (slew)
        );


        inline pros::MotorGroup LEFT_MOTORS ({
            LEFT_PORTS[0],
            LEFT_PORTS[1],
            LEFT_PORTS[2],
            LEFT_PORTS[3]},
            CHASSIS_INTERNAL_GEARSET);
            
        inline pros::MotorGroup RIGHT_MOTORS ({
            RIGHT_PORTS[0],
            RIGHT_PORTS[1],
            RIGHT_PORTS[2],
            RIGHT_PORTS[3]},
            CHASSIS_INTERNAL_GEARSET);

        inline pros::Imu IMU(IMU_PORT);

        // drivetrain settings
        inline lemlib::Drivetrain DRIVETRAIN(
            &LEFT_MOTORS, // left motor group
            &RIGHT_MOTORS, // right motor group
            DRIVETRAIN_WIDTH, // 10 inch track width
            lemlib::Omniwheel::NEW_325, // using new 3.25" omnis
            360, // drivetrain rpm is 360
            2 // horizontal drift is 2 (for now)
        );

        inline lemlib::OdomSensors SENSORS(
            nullptr, // vertical tracking wheel 1
            nullptr, // vertical tracking wheel 2, set to nullptr as we are using two wheel
            nullptr, // horizontal tracking wheel 1
            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
            &IMU // inertial sensor
        );
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

    namespace clamp
    {
        inline constexpr char PORT = 'F';
    }

    inline constexpr double TELEOP_POLL_TIME = 10.0; // ms

}
#endif