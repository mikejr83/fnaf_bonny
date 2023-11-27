#pragma once

#include <Adafruit_PWMServoDriver.h>
class Ear
{
private:
    Adafruit_PWMServoDriver *driver;
    uint8_t driverPosition;
public:
    Ear(Adafruit_PWMServoDriver *driver, uint8_t driverPosition);
};