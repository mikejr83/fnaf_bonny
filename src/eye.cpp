
#include "settings.h"
#include "eye.h"
#include "led_ops.h"

#include <ServoEasing.h>

Eye::Eye(const char *name,
         int pitchPin,
         int yawPin,
         int upperPin,
         int lowerPin,
         int lookLeftPosition,
         int lookRightPosition,
         int upperClosedPosition,
         int upperOpenPosition,
         int lowerClosedPosition,
         int lowerOpenPosition) : name(name),
                                  lookLeftPosition(lookLeftPosition),
                                  lookRightPosition(lookRightPosition),
                                  upperClosedPosition(upperClosedPosition),
                                  upperOpenPosition(upperOpenPosition),
                                  lowerClosedPosition(lowerClosedPosition),
                                  lowerOpenPosition(lowerOpenPosition)
{
    pitch = new ServoEasing(PCA9685_DEFAULT_ADDRESS);
    if (pitch->InitializeAndCheckI2CConnection(&Serial))
    {
        while (true)
        {
            blinkLED();
        }
    }
    if (pitch->attach(pitchPin, 1600) == INVALID_SERVO)
    {
        Log.errorln(F("%S - Pitch pin %d is invalid"), name, pitchPin);
    }
    pitch->setMaxConstraint(2200);
    pitch->setMinConstraint(800);

    yaw = new ServoEasing(PCA9685_DEFAULT_ADDRESS);
    yaw->InitializeAndCheckI2CConnection(&Serial);
    if (yaw->attach(yawPin, 1600) == INVALID_SERVO)
    {
        Log.errorln(F("Yaw pin %d is invalid"), yawPin);
    }
    yaw->setMaxConstraint(2200);
    yaw->setMinConstraint(800);

    upper = new ServoEasing(PCA9685_DEFAULT_ADDRESS);
    upper->InitializeAndCheckI2CConnection(&Serial);
    if (upper->attach(upperPin, upperOpenPosition) == INVALID_SERVO)
    {
        Log.errorln(F("Upper eye lid pin %d is invalid"), upperPin);
    }
    upper->setMaxConstraint(2200);
    upper->setMinConstraint(800);

    lower = new ServoEasing(PCA9685_DEFAULT_ADDRESS);
    lower->InitializeAndCheckI2CConnection(&Serial);
    if (lower->attach(lowerPin, lowerOpenPosition) == INVALID_SERVO)
    {
        Log.errorln(F("Lower eye lid pin %d is invalid"), lowerPin);
    }
    lower->setMaxConstraint(2200);
    lower->setMinConstraint(800);
}

Eye::~Eye()
{
    delete pitch;
    delete yaw;
    delete upper;
    delete lower;
}

void Eye::closeEyes()
{
    Log.traceln("%s - closeEyes() - start", name);

    Log.noticeln("%s - Lower to: %d - Upper to %d", name, lowerClosedPosition, upperClosedPosition);

    lower->startEaseTo(lowerClosedPosition, 50);
    upper->startEaseTo(upperClosedPosition, 50);

    Log.traceln("%s - closeEyes() - end", name);
}

void Eye::openEyes()
{
    Log.traceln("%s - openEyes() - start", name);

    Log.noticeln("%s - Lower to: %d - Upper to %d", name, lowerOpenPosition, upperOpenPosition);

    lower->startEaseTo(lowerOpenPosition, 75);
    upper->startEaseTo(upperOpenPosition, 75);

    Log.traceln("%s - openEyes() - end", name);
}

void Eye::lookLeft()
{
    Log.traceln("%s - lookLeft() - start", name);

    Log.noticeln("%s - Pitch to: %d", name, lookLeftPosition);

    yaw->startEaseTo(lookLeftPosition, 30);

    Log.traceln("%s - lookLeft() - end", name);
}

void Eye::lookRight()
{
    Log.traceln("%s - lookRight() - start", name);

    Log.noticeln("%s - Pitch to: %d", name, lookRightPosition);

    yaw->startEaseTo(lookRightPosition, 30);

    Log.traceln("%s - lookRight() - end", name);
}

void Eye::lookAhead()
{
    Log.traceln("%s - lookAhead() - start", name);

    Log.noticeln("%s - Pitch to: %d - yaw to %d", name, 1500, 1500);

    pitch->startEaseTo(1500, 30);
    yaw->startEaseTo(1500, 30);

    Log.traceln("%s - lookAhead() - end", name);
}