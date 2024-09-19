#ifndef __SUBSYSTEMS_DRIVEBASE_H__
#define __SUBSYSTEMS_DRIVEBASE_H__

#include "comets/vendor.h"
#include "constants.h"
#include <memory>

class Drivebase
{
public:
    Drivebase();
    lemlib::Pose getPose();
    void tank(double left, double right, bool disableDriveCurve = false);
    void setPose(float x, float y, float theta, bool radians = false);
    void moveToPose(float x, float y, float theta, int timeout, bool async = true, lemlib::MoveToPoseParams params = {});
    void turnToHeading(float theta, int timeout, lemlib::TurnToHeadingParams params = {}, bool async = true);
    void calibrate(bool calibrateIMU = true);
    pros::IMU getIMU();
    bool isInMotion();
};

#endif
