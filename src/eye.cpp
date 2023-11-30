#include "settings.h"

#include <ServoEasing.h>

#include "eye.h"
#include "mover.h"

#ifndef EYE_EASING_TYPE
#define EYE_EASING_TYPE EASE_CUBIC_OUT
#endif

Eye::Eye(String name,
         int pitchPin,
         int yawPin,
         int upperPin,
         int lowerPin) : Mover(name),

                         pitchPin(pitchPin),
                         yawPin(yawPin),
                         upperPin(upperPin),
                         lowerPin(lowerPin),

                         currentPitch(1500),
                         currentYaw(1500),
                         currentUpperLid(1500),
                         currentLowerLid(1500),

                         upperLidClosedPosition(2200),
                         upperLidOpenPosition(800),
                         lowerLidClosedPosition(2200),
                         lowerLidOpenPosition(800),
                         leftEndPosition(2000),
                         rightEndPosition(800),
                         upEndPosition(2000),
                         downEndPosition(1000)
{
    this->pitchServo = new ServoEasing(PCA9685_DEFAULT_ADDRESS);
    this->yawServo = new ServoEasing(PCA9685_DEFAULT_ADDRESS);
    this->upperServo = new ServoEasing(PCA9685_DEFAULT_ADDRESS);
    this->lowerServo = new ServoEasing(PCA9685_DEFAULT_ADDRESS);

    this->pitchServo->setSpeed(80);
    this->yawServo->setSpeed(80);
    this->upperServo->setSpeed(80);
    this->lowerServo->setSpeed(80);

    this->pitchServo->setMaxConstraint(2200);
    this->yawServo->setMaxConstraint(2200);
    this->upperServo->setMaxConstraint(2200);
    this->lowerServo->setMaxConstraint(2200);

    this->pitchServo->setMinConstraint(800);
    this->yawServo->setMinConstraint(800);
    this->upperServo->setMinConstraint(800);
    this->lowerServo->setMinConstraint(800);

    this->pitchServo->setEasingType(EYE_EASING_TYPE);
    this->yawServo->setEasingType(EYE_EASING_TYPE);
    this->upperServo->setEasingType(EYE_EASING_TYPE);
    this->lowerServo->setEasingType(EYE_EASING_TYPE);

    if (this->pitchServo->InitializeAndCheckI2CConnection(&Serial))
    {
        Log.error("Cannot communicate withthe PCA9685 board!");
    }
    else
    {
        Log.verboseln("Driver is initialized on I2C.");
    }

    this->pitchServo->attach(this->pitchPin, this->currentPitch);
    this->yawServo->attach(this->yawPin, this->currentYaw);
    this->upperServo->attach(this->upperPin, this->currentUpperLid);
    this->lowerServo->attach(this->lowerPin, this->currentLowerLid);

    updateAndWaitForAllServosToStop();
}

bool Eye::closeEyes()
{
    Log.verboseln("\"Eye::closeEyes()\"");

    this->lowerServo->startEaseTo(this->lowerLidClosedPosition, 50);
    this->upperServo->startEaseTo(this->upperLidClosedPosition, 50);

    return !(this->lowerServo->update() && this->upperServo->update());
}

void Eye::lookDown()
{
}

bool Eye::lookLeft()
{
    Log.verboseln("%s - \"Eye::lookLeft()\"", this->name.c_str());

    this->yawServo->startEaseTo(2000, 50);
    bool leftCompleted = !this->yawServo->update();

    Log.traceln("%s - Is moving %T - !update %T - current %d going to 2000", 
        this->name.c_str(), 
        this->yawServo->isMoving(), 
        leftCompleted,
        this->yawServo->getCurrentMicroseconds());

    return leftCompleted;
}

bool Eye::lookRight()
{
    Log.verboseln("%s - \"Eye::lookRight()\"", this->name.c_str());

    this->yawServo->startEaseTo(1000, 50);

    Log.traceln("%s - Is moving %T", this->name.c_str(), this->yawServo->isMoving());

    // bool same = this->lowerServo->getCurrentMicroseconds() == this->lowerLidOpenPosition &&
    //             this->upperServo->getCurrentMicroseconds() == this->upperLidOpenPosition;

    // Log.traceln("%s - Upper: %d - Lower: %d - Are same? %T", this->name.c_str(), this->lowerServo->getCurrentMicroseconds(), this->upperServo->getCurrentMicroseconds(), same);

    return !(this->yawServo->update());
}

void Eye::lookUp()
{
}

bool Eye::openEyes()
{
    Log.verboseln("%s - \"Eye::openEyes()\"", this->name.c_str());

    this->lowerServo->startEaseTo(this->lowerLidOpenPosition);
    this->upperServo->startEaseTo(this->upperLidOpenPosition);

    Log.traceln("%s - Is moving %T", this->name.c_str(), this->lowerServo->isMoving());

    // bool same = this->lowerServo->getCurrentMicroseconds() == this->lowerLidOpenPosition &&
    //             this->upperServo->getCurrentMicroseconds() == this->upperLidOpenPosition;

    // Log.traceln("%s - Upper: %d - Lower: %d - Are same? %T", this->name.c_str(), this->lowerServo->getCurrentMicroseconds(), this->upperServo->getCurrentMicroseconds(), same);

    return !(this->lowerServo->update() && this->upperServo->update());
}