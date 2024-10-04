#ifndef __SUBSYSTEMS_DRIVEBASE_H__
#define __SUBSYSTEMS_DRIVEBASE_H__

#include "lemlib/api.hpp"
#include "constants.h"


using namespace constants::drivebase;
class Drivebase : public lemlib::Chassis {
    public:
        Drivebase() : lemlib::Chassis(DRIVETRAIN, LATERAL_CONTROLLER, ANGULAR_CONTROLLER, SENSORS) {}

        void calibrateChassis(bool useIMU) {
            this->calibrate(useIMU);
            while(IMU.is_calibrating()) {
                pros::delay(10);
            }
        }

        pros::IMU getIMU() {
            return IMU;
        }

        void errorDrive(float drive, float turn) {
            drive /= 127.0;
            turn /= 127.0;
            if (drive < 0.5) {
                turn /= 1.4;
            } else {
                turn /= 1.2;
            }
            LEFT_MOTORS.move_voltage((drive + turn)*12000);
            RIGHT_MOTORS.move_voltage((drive - turn)*12000);
        }

    private:

};

#endif