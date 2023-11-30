#pragma once

#include <ServoEasing.h>

#include "mover.h"

class Ear
{
private:
    ServoEasing *driver;
    uint8_t driverPin;
public:
    Ear(uint8_t driverPin);
};