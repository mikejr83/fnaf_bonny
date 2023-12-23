
#include "settings.h"
#include "jaw.h"

#include <ServoEasing.h>

Jaw::Jaw(int jawPin) : jawPin(jawPin)
{
    servo = new ServoEasing(PCA9685_DEFAULT_ADDRESS);
    servo->InitializeAndCheckI2CConnection(&Serial);
    servo->attach(jawPin, 1600);
    servo->setMaxConstraint(2200);
    servo->setMinConstraint(800);
}

void Jaw::closeJaw()
{
    Log.verboseln("closeJaw()");

    // Log.traceln("Lower to: %d - Upper to %d", lowerClosedPosition, upperClosedPosition);

    servo->startEaseTo(JAW_CLOSED, 50);
}

void Jaw::openJaw()
{
    Log.verboseln("openJaw()");

    // Log.traceln("Lower to: %d - Upper to %d", lowerClosedPosition, upperClosedPosition);

    servo->startEaseTo(JAW_OPEN, 50);
}