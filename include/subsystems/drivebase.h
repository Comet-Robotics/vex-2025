#ifndef __SUBSYSTEMS_DRIVEBASE_H__
#define __SUBSYSTEMS_DRIVEBASE_H__

#include "lemlib/api.hpp"

class Drivebase {
    public:
        Drivebase();

        void calibrateChassis(bool useIMU);
        pros::IMU getIMU();
        void tankDrive(float left, float right);
        void arcadeDrive(float drive, float turn);
        void errorDrive(float drive, float turn);
        void turnToHeading(float theta, int timeout, lemlib::TurnToHeadingParams params = {}, bool async = true);
        void turnToPoint(float x, float y, int timeout, lemlib::TurnToPointParams params = {}, bool async = true);
        void cancelAllMotions();
        void cancelMotion();
        void curvature(int throttle, int turn, bool disableDriveCurve = false);
        void follow(const asset &path, float lookahead, int timeout, bool forwards = true, bool async = true);
        lemlib::Pose getPose(bool radians = false, bool standardPos = false);
        bool isInMotion();
        void moveToPoint(float x, float y, int timeout, lemlib::MoveToPointParams params = {}, bool async = true);
        void moveToPose(float x, float y, float theta, int timeout, lemlib::MoveToPoseParams = {}, bool async = true);
        void resetLocalPosition();
        void setBrakeMode(pros::motor_brake_mode_e mode);
        void setPose(lemlib::Pose pose, bool radians = false);
        void swingToHeading(float theta, DriveSide lockedSide, int timeout, lemlib::SwingToHeadingParams params = {}, bool async = true);
        void swingToPoint(float x, float y, DriveSide lockedSide, int timeout, lemlib::SwingToPointParams params = {}, bool async = true);
        void waitUntil(float dist);
        void waitUntilDone();

    private:

};

#endif