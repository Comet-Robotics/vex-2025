#ifndef __SUBSYSTEMS_CLAMP_H__
#define __SUBSYSTEMS_CLAMP_H__

#include "constants.h"
#include "pros/adi.hpp"

using namespace constants::clamp;
class Clamp : public pros::adi::DigitalOut
{

public:
    bool isToggled = false;
    Clamp() : pros::adi::DigitalOut(PORT, false) {}

    void toggle()
    {
        isToggled = !isToggled;
        this->set_value(isToggled);
    }

    void clamp()
    {
        isToggled = true;
        this->set_value(isToggled);
    }

    void unclamp()
    {
        isToggled = false;
        this->set_value(isToggled);
    }

private:
};

#endif