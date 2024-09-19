#include "subsystems/drivebase.h"
#include "constants.h"

pros::MotorGroup left_wheels(
    {constants::drivebase::LEFT_PORTS[0],
     constants::drivebase::LEFT_PORTS[1],
     constants::drivebase::LEFT_PORTS[2]}, // left motor ports
    constants::drivebase::CARTRIDGE        // cartridge
);
pros::MotorGroup right_wheels(
    {constants::drivebase::RIGHT_PORTS[0],
     constants::drivebase::RIGHT_PORTS[1],
     constants::drivebase::RIGHT_PORTS[2]}, // right motor ports
    constants::drivebase::CARTRIDGE         // cartridge
);

lemlib::Drivetrain drivetrain(
    &left_wheels,                          // left motor group
    &right_wheels,                         // right motor group
    constants::drivebase::TRACK_WIDTH,     // track width
    constants::drivebase::WHEEL,           // wheel size
    constants::drivebase::DRIVETRAIN_RPM,  // drivetrain RPM
    constants::drivebase::HORIZONTAL_DRIFT // horizontal drift
);

pros::Imu imu(constants::drivebase::IMU_PORT);

lemlib::OdomSensors sensors( // all of these should be pointers
    nullptr,                 // vertical tracking wheel 1
    nullptr,                 // vertical tracking wheel 2
    nullptr,                 // horizontal tracking wheel 1
    nullptr,                 // horizontal tracking wheel 2
    &imu                     // inertial sensor
);

// lateral PID controller
lemlib::ControllerSettings lateral_controller(
    10,  // proportional gain (kP)
    0,   // integral gain (kI)
    3,   // derivative gain (kD)
    3,   // anti windup
    1,   // small error range, in inches
    100, // small error range timeout, in milliseconds
    3,   // large error range, in inches
    500, // large error range timeout, in milliseconds
    20   // maximum acceleration (slew)
);

// angular PID controller
lemlib::ControllerSettings angular_controller(
    2.5, // proportional gain (kP)
    0,   // integral gain (kI)
    10,  // derivative gain (kD)
    5,   // anti windup
    1,   // small error range, in degrees
    100, // small error range timeout, in milliseconds
    3,   // large error range, in degrees
    500, // large error range timeout, in milliseconds
    0    // maximum acceleration (slew)
);

// create the chassis
lemlib::Chassis chassis(
    drivetrain,         // drivetrain settings
    lateral_controller, // lateral PID settings
    angular_controller, // angular PID settings
    sensors             // sensors
);

Drivebase::Drivebase()
{
    static_assert(constants::drivebase::LEFT_PORTS.size() == 3 && constants::drivebase::RIGHT_PORTS.size() == 3,
                  "number of motors on drivebase has changed without consulting drivebase.cpp");
}

lemlib::Pose Drivebase::getPose()
{
    return chassis.getPose();
}

void Drivebase::tank(double left, double right, bool disableDriveCurve)
{
    chassis.tank(left, right, disableDriveCurve);
}

void Drivebase::setPose(float x, float y, float theta, bool radians)
{
    chassis.setPose(x, y, theta, radians);
}

void Drivebase::moveToPose(float x, float y, float theta, int timeout, bool async, lemlib::MoveToPoseParams params)
{
    chassis.moveToPose(x, y, theta, timeout, params, async);
}

void Drivebase::turnToHeading(float theta, int timeout, lemlib::TurnToHeadingParams params, bool async)
{
    chassis.turnToHeading(theta, timeout, params, async);
}

void Drivebase::calibrate(bool calibrateIMU)
{
    chassis.calibrate(calibrateIMU);
    while (imu.is_calibrating())
    {
        pros::delay(10);
    }
}

pros::IMU Drivebase::getIMU()
{
    return imu;
}

bool Drivebase::isInMotion()
{
    return chassis.isInMotion();
}