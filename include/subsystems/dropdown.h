#ifndef __SUBSYSTEMS_DROPDOWN_H__
#define __SUBSYSTEMS_DROPDOWN_H__

#include "constants.h"
#include "pros/adi.hpp"

using namespace constants::dropdown;
class Dropdown : public pros::adi::DigitalOut
{

public:
    bool isToggled = false;
    Dropdown() : pros::adi::DigitalOut(DROPDOWN_PORT, false) {}

    void dropdown()
    {
        isToggled = true;
        this->set_value(isToggled);
    }

    void reset()
    {
        isToggled = false;
        this->set_value(isToggled);
    }

private:
};

#endif