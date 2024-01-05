#include <Arduino.h>

#include "settings.h"
#include "jaw.h"
#include "led_ops.h"

#include <ServoEasing.h>

Jaw::Jaw(int jawPin) : jawPin(jawPin)
{
    servo = new ServoEasing(PCA9685_DEFAULT_ADDRESS);
    if (servo->InitializeAndCheckI2CConnection(&Serial))
    {
        Log.errorln(SERVO_ERROR);
        while (true)
        {
            blinkLED();
        }
    }
    if (servo->attach(jawPin, 1600) == INVALID_SERVO)
    {
        Log.errorln(F("Invalid pin for jaw"));
    }
    servo->setMaxConstraint(1850);
    servo->setMinConstraint(1400);
}

void Jaw::closeJaw()
{
    Log.traceln(F("closeJaw() - start"));

    Log.noticeln("Moving jaw to: %d", JAW_CLOSED);

    servo->startEaseTo(JAW_CLOSED, 50);

    Log.traceln(F("closeJaw() - end"));
}

void Jaw::openJaw()
{
    Log.traceln(F("openJaw() - start"));

    Log.noticeln("Moving jaw to: %d", JAW_OPEN);

    servo->startEaseTo(JAW_OPEN, 50);

    Log.traceln(F("openJaw() - end"));
}