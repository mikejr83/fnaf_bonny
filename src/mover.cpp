#include "settings.h"

#include "mover.h"

#include <Adafruit_PWMServoDriver.h>
#include <ArduinoLog.h>

Mover::Mover(Adafruit_PWMServoDriver *driver) :isMoving(false), driver(driver)
{
}

bool Mover::get_isMoving()
{
    return this->isMoving;
}

bool Mover::moveTo(uint8_t dirverPosition, uint16_t stopPosition)
{
    Log.verboseln("Eye::moveTo()");

    uint16_t currentPWM = this->driver->getPWM(dirverPosition, true);
    long currentPosition = map(currentPWM, SERVOMIN, SERVOMAX, USMIN, USMAX);

    Log.traceln("The current position of the servo at pin %d is %d and is moving to %d",
                  dirverPosition,
                  currentPosition,
                  stopPosition);

    

    return false;
}