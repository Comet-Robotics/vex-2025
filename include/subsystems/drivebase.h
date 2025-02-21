#ifndef __SUBSYSTEMS_DRIVEBASE_H__
#define __SUBSYSTEMS_DRIVEBASE_H__

#include "constants.h"
#include "pros/motors.h"
#include <cmath>

using namespace constants::drivebase;
class Drivebase : public lemlib::Chassis
{
  public:
    Drivebase() : lemlib::Chassis(DRIVETRAIN, LATERAL_CONTROLLER, ANGULAR_CONTROLLER, SENSORS) {}

    void calibrateChassis(bool useIMU)
    {
        this->calibrate(useIMU);
        while (IMU.is_calibrating())
        {
            pros::delay(10);
        }
    }

    pros::IMU getIMU() { return IMU; }

    void errorDrive(float drive, float turn)
    {
        drive /= 127.0;
        turn /= 127.0;

        turn /= ((drive < 0.5) ? 1.5 : 1.2);

        // int driveSign = ((drive >= 0)? 1 : -1);
        // int turnSign  = ((turn >= 0)?  1 : -1);

        // drive = driveSign * pow(drive, 2);
        // turn = turnSign * pow(turn, 2);

        LEFT_MOTORS.move_voltage((drive + turn) * 12000);
        RIGHT_MOTORS.move_voltage((drive - turn) * 12000);
    }

    void turnThenMoveToPoint(double x, double y, int timeout = DEFAULT_TIMEOUT, lemlib::TurnToPointParams turnParams = {}, lemlib::MoveToPointParams moveParams = {}, bool async = true)
    {
        turnToPoint(x, y, timeout, turnParams, async);
        moveToPoint(x, y, timeout, moveParams, async);
    }

    void turnThenMoveToPoint(double x, double y, bool async)
    {
        turnToPoint(x, y, DEFAULT_TIMEOUT, {}, async);
        moveToPoint(x, y, DEFAULT_TIMEOUT, {}, async);
    }

    void waitUntilStationary(uint32_t interval = 20 /*ms*/) {
      while (isInMotion()) {
        pros::delay(20);
      }
    }
  private:
};

#endif