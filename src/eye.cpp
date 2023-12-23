
#include "settings.h"
#include "eye.h"

#include <ServoEasing.h>

Eye::Eye(int pitchPin,
         int yawPin,
         int upperPin,
         int lowerPin,
         int lookLeftPosition,
         int lookRightPosition,
         int upperClosedPosition,
         int upperOpenPosition,
         int lowerClosedPosition,
         int lowerOpenPosition) : lookLeftPosition(lookLeftPosition),
                                  lookRightPosition(lookRightPosition),
                                  upperClosedPosition(upperClosedPosition),
                                  upperOpenPosition(upperOpenPosition),
                                  lowerClosedPosition(lowerClosedPosition),
                                  lowerOpenPosition(lowerOpenPosition)
{
    pitch = new ServoEasing(PCA9685_DEFAULT_ADDRESS);
    pitch->InitializeAndCheckI2CConnection(&Serial);
    pitch->attach(pitchPin, 1600);
    pitch->setMaxConstraint(2200);
    pitch->setMinConstraint(800);

    yaw = new ServoEasing(PCA9685_DEFAULT_ADDRESS);
    yaw->InitializeAndCheckI2CConnection(&Serial);
    yaw->attach(yawPin, 1600);
    yaw->setMaxConstraint(2200);
    yaw->setMinConstraint(800);

    upper = new ServoEasing(PCA9685_DEFAULT_ADDRESS);
    upper->InitializeAndCheckI2CConnection(&Serial);
    upper->attach(upperPin, upperClosedPosition);
    upper->setMaxConstraint(2200);
    upper->setMinConstraint(800);

    lower = new ServoEasing(PCA9685_DEFAULT_ADDRESS);
    lower->InitializeAndCheckI2CConnection(&Serial);
    lower->attach(lowerPin, lowerClosedPosition);
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
    Log.verboseln("closeEyes()");

    Log.traceln("Lower to: %d - Upper to %d", lowerClosedPosition, upperClosedPosition);

    lower->startEaseTo(lowerClosedPosition, 50);
    upper->startEaseTo(upperClosedPosition, 50);
}

void Eye::openEyes()
{
    Log.verboseln("openEyes()");

    Log.traceln("Lower to: %d - Upper to %d", lowerOpenPosition, upperOpenPosition);

    lower->startEaseTo(lowerOpenPosition, 75);
    upper->startEaseTo(upperOpenPosition, 75);
}

void Eye::lookLeft()
{
    Log.verboseln("lookLeft()");
    pitch->startEaseTo(lookLeftPosition, 30);
}

void Eye::lookRight()
{
    Log.verboseln("lookRight()");
    pitch->startEaseTo(lookRightPosition, 30);
}

void Eye::lookAhead()
{
    Log.verboseln("lookAhead()");
    pitch->startEaseTo(1500, 30);
    yaw->startEaseTo(1500, 30);
}