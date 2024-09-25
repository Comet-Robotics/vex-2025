#include "subsystems/drivebase.h"
#include "constants.h"
#include "lemlib/api.hpp"

pros::MotorGroup m_groupl ({
    constants::drivebase::LEFT_PORTS[0],
    constants::drivebase::LEFT_PORTS[1],
    constants::drivebase::LEFT_PORTS[2],
    constants::drivebase::LEFT_PORTS[3]},
    constants::drivebase::CHASSIS_INTERNAL_GEARSET);
pros::MotorGroup m_groupr ({
    constants::drivebase::RIGHT_PORTS[0],
    constants::drivebase::RIGHT_PORTS[1],
    constants::drivebase::RIGHT_PORTS[2],
    constants::drivebase::RIGHT_PORTS[3]},
    constants::drivebase::CHASSIS_INTERNAL_GEARSET);

pros::Imu imu(constants::drivebase::IMU_PORT);

// drivetrain settings
lemlib::Drivetrain drivetrain(
    &m_groupl, // left motor group
    &m_groupr, // right motor group
    constants::drivebase::DRIVETRAIN_WIDTH, // 10 inch track width
    lemlib::Omniwheel::NEW_325, // using new 3.25" omnis
    360, // drivetrain rpm is 360
    2 // horizontal drift is 2 (for now)
);

lemlib::OdomSensors sensors(nullptr, // vertical tracking wheel 1, set to null
                        nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                        nullptr, // horizontal tracking wheel 1
                        nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                        &imu // inertial sensor
);

// lateral PID controller
lemlib::ControllerSettings lateral_controller(0, // proportional gain (kP)
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
lemlib::ControllerSettings angular_controller(0, // proportional gain (kP)
                                            0, // integral gain (kI)
                                            0, // derivative gain (kD)
                                            0, //3, // anti windup
                                            0, //1, // small error range, in degrees
                                            0, //100, // small error range timeout, in milliseconds
                                            0, //3, // large error range, in degrees
                                            0, //500, // large error range timeout, in milliseconds
                                            0 // maximum acceleration (slew)
);

lemlib::Chassis chassis(drivetrain, // drivetrain settings
                    lateral_controller, // lateral PID settings
                    angular_controller, // angular PID settings
                    sensors // odometry sensors
);

Drivebase::Drivebase()
{

    static_assert(constants::drivebase::LEFT_PORTS.size() == 4 && constants::drivebase::RIGHT_PORTS.size() == 4,
                  "number of motors on drivebase has changed without consulting drivebase.cpp");

}

void Drivebase::calibrateChassis(bool useIMU) {
    chassis.calibrate(useIMU);
    while(imu.is_calibrating()) {
        pros::delay(10);
    }
}

pros::IMU Drivebase::getIMU() {
    return imu;
}

void Drivebase::tankDrive(float left, float right) {
    chassis.tank(left, right);
}

void Drivebase::arcadeDrive(float drive, float turn) {
    chassis.arcade(drive, turn);
}

void Drivebase::errorDrive(float drive, float turn) {
    drive /= 127.0;
    turn /= 127.0;
    if (drive < 0.5) {
        turn /= 1.4;
    } else {
        turn /= 1.2;
    }
    m_groupl.move_voltage((drive + turn)*12000);
    m_groupr.move_voltage((drive - turn)*12000);
}

void Drivebase::turnToHeading(float theta, int timeout, lemlib::TurnToHeadingParams params, bool async) {
    chassis.turnToHeading(theta, timeout, params, async);
}

void Drivebase::turnToPoint(float x, float y, int timeout, lemlib::TurnToPointParams params, bool async) {
    chassis.turnToPoint(x, y, timeout, params, async);
}

void Drivebase::cancelAllMotions() {
    chassis.cancelAllMotions();
}

void Drivebase::cancelMotion() {
    chassis.cancelMotion();
}

void Drivebase::curvature(int throttle, int turn, bool disableDriveCurve) {
    chassis.curvature(throttle, turn, disableDriveCurve);
}

void Drivebase::follow(const asset &path, float lookahead, int timeout, bool forwards, bool async) {
    chassis.follow(path, lookahead, timeout, forwards, async);
}

lemlib::Pose Drivebase::getPose(bool radians, bool standardPos) {
    return chassis.getPose(radians, standardPos);
}

bool Drivebase::isInMotion() {
    return chassis.isInMotion();
}

void Drivebase::moveToPoint(float x, float y, int timeout, lemlib::MoveToPointParams params, bool async) {
    chassis.moveToPoint(x, y, timeout, params, async);
}

void Drivebase::moveToPose(float x, float y, float theta, int timeout, lemlib::MoveToPoseParams params, bool async) {
    chassis.moveToPose(x, y, theta, timeout);
}

void Drivebase::resetLocalPosition() {
    chassis.resetLocalPosition();
}

void Drivebase::setBrakeMode(pros::motor_brake_mode_e mode) {
    chassis.setBrakeMode(mode);
}

void Drivebase::setPose(lemlib::Pose pose, bool radians) {
    chassis.setPose(pose, radians);
}

void Drivebase::swingToHeading(float theta, DriveSide lockedSide, int timeout, lemlib::SwingToHeadingParams params, bool async) {
    chassis.swingToHeading(theta, lockedSide, timeout, params, async);
}

void Drivebase::swingToPoint(float x, float y, DriveSide lockedSide, int timeout, lemlib::SwingToPointParams params, bool async) {
    chassis.swingToPoint(x, y, lockedSide, timeout);
}

void Drivebase::waitUntil(float dist) {
    chassis.waitUntil(dist);
}

void Drivebase::waitUntilDone() {
    chassis.waitUntilDone();
}
