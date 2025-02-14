#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "lemlib/chassis/trackingWheel.hpp"
#include "pros/abstract_motor.hpp"
#include "pros/rotation.hpp"
#include <array>
#include <cstdint>
#include "lemlib/chassis/chassis.hpp"

namespace constants
{
    // using namespace pros;

    namespace drivebase
    {
        inline constexpr bool USE_TANK = false;
        // front, back, top front, top back
        inline constexpr std::array<int8_t, 4> LEFT_PORTS = {
            8,
            14,
            -7,
            -9
        };

        // front, back, top front, top back
        inline constexpr std::array<int8_t, 4> RIGHT_PORTS = {
            -18,
            -20,
            17,
            19
        };

        inline constexpr double DRIVETRAIN_WIDTH = 11.25; //tune this 
        inline constexpr int8_t IMU_PORT = 5;

        inline constexpr auto CHASSIS_INTERNAL_GEARSET = pros::v5::MotorGears::blue;

        // lateral PID controller
        inline const lemlib::ControllerSettings LATERAL_CONTROLLER(
            0,   // proportional gain (kP)
            0,   // integral gain (kI)
            0,   // derivative gain (kD)
            0,   // anti windup
            0,   // small error range, in inches
            0, // small error range timeout, in milliseconds
            0,   // large error range, in inches
            0, // large error range timeout, in milliseconds
            0   // maximum acceleration (slew)
        );

        // angular PID controller
        inline const lemlib::ControllerSettings ANGULAR_CONTROLLER(
            0, // proportional gain (kP)
            0,// integral gain (kI)
            0,// derivative gain (kD)
            0, // anti windup
            0, // small error range, in degrees
            0, // small error range timeout, in milliseconds
            0, // large error range, in degrees
            0, // large error range timeout, in milliseconds
            0// maximum acceleration (slew)
        );

        inline pros::MotorGroup LEFT_MOTORS({LEFT_PORTS[0],
                                             LEFT_PORTS[1],
                                             LEFT_PORTS[2],
                                             LEFT_PORTS[3]},
                                            CHASSIS_INTERNAL_GEARSET);

        inline pros::MotorGroup RIGHT_MOTORS({RIGHT_PORTS[0],
                                              RIGHT_PORTS[1],
                                              RIGHT_PORTS[2],
                                              RIGHT_PORTS[3]},
                                             CHASSIS_INTERNAL_GEARSET);

        inline pros::Imu IMU(IMU_PORT);

        // drivetrain settings
        inline lemlib::Drivetrain DRIVETRAIN(
            &LEFT_MOTORS,               // left motor group
            &RIGHT_MOTORS,              // right motor group
            DRIVETRAIN_WIDTH,           // 10 inch track width
            lemlib::Omniwheel::NEW_325, // using new 3.25" omnis
            360,                        // drivetrain rpm is 360
            2                           // horizontal drift is 2 (for now)
        );

        inline pros::Rotation VERTICAL_ROTATION( 0 );
    
        inline lemlib::TrackingWheel VERTICAL_TRACKING (
            &VERTICAL_ROTATION, // rotation sensor
            lemlib::Omniwheel::NEW_2, // wheel diameter
            0 // distance from center of rotation
        );

        inline lemlib::OdomSensors SENSORS(
            &VERTICAL_TRACKING, // vertical tracking wheel 1
            nullptr,
            nullptr, // horizontal tracking wheel 1
            nullptr,
            &IMU     // inertial sensor
        );

        inline constexpr int DEFAULT_TIMEOUT = 5000;
    }

    namespace intake
    {
        inline constexpr std::array<int8_t, 2> INTAKE_PORTS = {
            -15, // left
            4 // right
        };

        inline const bool USE_TOGGLE = false;

        inline constexpr int INTAKE_VOLTAGE = 12000; // mV
        // uses basic motors, which doesn't requre gearset to be configured in code
    }

    namespace elevator
    {
        inline constexpr std::array<int8_t, 2> ELEVATOR_PORTS = {
            6, // left
            -16 // right
        };

        inline const bool USE_TOGGLE = false;

        inline constexpr int ELEVATOR_VOLTAGE = 8000; // mV
        // uses basic motors, which doesn't requre gearset to be configured in code
    }

    namespace clamp
    {
        inline constexpr char PORT = 'A';
    }

    namespace arm
    {
        inline constexpr std::array<int8_t, 2> ARM_PORTS = {
            -10, // left
            2 // right
        };

        inline const bool USE_TOGGLE = true;
        inline const pros::motor_brake_mode_e BRAKE_MODE = pros::E_MOTOR_BRAKE_BRAKE;

        inline constexpr int ARM_VOLTAGE = 12000; // mV
    }

    inline constexpr double TELEOP_POLL_TIME = 10.0; // ms

    
    namespace wallstake
    {
        inline constexpr std::array<int8_t, 2> WALLSTAKE_PORTS = {
            //TODO change these to be correct
            0, // left
            0 // right
        };

        // inline const bool USE_TOGGLE = true;

        inline constexpr int WALLSTAKE_VOLTAGE = 12000; // mV
        // uses basic motors, which doesn't requre gearset to be configured in code
    }
}
#endif