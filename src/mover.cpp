#include "settings.h"

#include "mover.h"

#include <Adafruit_PWMServoDriver.h>
#include <ArduinoLog.h>

Mover::Mover(Adafruit_PWMServoDriver *driver, uint8_t stepSize) : isMoving(false), stepSize(stepSize), driver(driver)
{
}

// static implementation
uint16_t Mover::getCurrentPosition(Adafruit_PWMServoDriver *driver, uint8_t driverPin)
{
    uint16_t currentPWM = driver->getPWM(driverPin, true);
    long currentPosition = map(currentPWM, SERVOMIN, SERVOMAX, USMIN, USMAX);
    return currentPosition;
}

bool Mover::get_isMoving()
{
    return this->isMoving;
}

bool Mover::moveTo(uint8_t driverPin, uint16_t stopPosition)
{
    Log.verboseln("Mover::moveTo(%d, %d)", driverPin, stopPosition);

    uint16_t currentPosition = Mover::getCurrentPosition(driver, driverPin);

    Log.traceln("The current position of the servo at pin %d is %d",
                driverPin,
                currentPosition);

    uint16_t positionToMoveTo = currentPosition;

    if (abs(currentPosition - stopPosition) < this->stepSize)
    {
        positionToMoveTo = currentPosition;
    }
    else if (stopPosition > currentPosition)
    {
        positionToMoveTo += this->stepSize;
    }
    else if (stopPosition < currentPosition)
    {
        positionToMoveTo -= this->stepSize;
    }
    else
    {
        positionToMoveTo = currentPosition;
    }

    Log.traceln("Moving the servo at pin %d from %d to %d",
                driverPin,
                currentPosition,
                positionToMoveTo);

    this->driver->writeMicroseconds(driverPin, positionToMoveTo);

    return currentPosition == positionToMoveTo;
}