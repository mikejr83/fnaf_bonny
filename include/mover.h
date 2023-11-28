#pragma once

#include <Adafruit_PWMServoDriver.h>

class Mover
{
protected:
    // Properties
    bool isMoving = false;
    uint8_t stepSize = 50;
    Adafruit_PWMServoDriver *driver;

    // Methods
    bool moveTo(uint8_t driverPin, uint16_t stopPosition);
public:
    static uint16_t getCurrentPosition(Adafruit_PWMServoDriver *driver, uint8_t driverPin);
    bool get_isMoving();

    // Constructor
    Mover(Adafruit_PWMServoDriver *driver, uint8_t stepSize);
};