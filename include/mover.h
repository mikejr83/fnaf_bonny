#pragma once

#include <Adafruit_PWMServoDriver.h>

class Mover
{
protected:
    // Properties
    bool isMoving = false;
    Adafruit_PWMServoDriver *driver;

    // Methods
    bool moveTo(uint8_t dirverPosition, uint16_t stopPosition);

public:
    bool get_isMoving();

    // Constructor
    Mover(Adafruit_PWMServoDriver *driver);
};