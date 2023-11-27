#include "ear.h"

Ear::Ear(Adafruit_PWMServoDriver *driver, uint8_t driverPosition)
{
    this->driver = driver;
    this->driverPosition = driverPosition;
}