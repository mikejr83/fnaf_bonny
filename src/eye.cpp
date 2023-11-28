#include "settings.h"

#include <Adafruit_PWMServoDriver.h>
#include <ArduinoLog.h>

#include "eye.h"

Eye::Eye(Adafruit_PWMServoDriver *driver,
         uint8_t pitchDriverPosition,
         uint8_t yawDriverPosition,
         uint8_t upperDriverLidPosition,
         uint8_t lowerDriverLidPosition) : Mover(driver),
                                           pitchDriverPosition(pitchDriverPosition),
                                           yawDriverPosition(upperDriverLidPosition),
                                           upperDriverLidPosition(pitchDriverPosition),
                                           lowerDriverLidPosition(lowerDriverLidPosition),
                                           currentPitch(1500),
                                           currentYaw(1500),
                                           currentUpperLid(1500),
                                           currentLowerLid(1500)
{
    this->driver->writeMicroseconds(this->pitchDriverPosition, this->currentPitch);
    this->driver->writeMicroseconds(this->yawDriverPosition, this->currentYaw);
    this->driver->writeMicroseconds(this->upperDriverLidPosition, this->currentUpperLid);
    this->driver->writeMicroseconds(this->lowerDriverLidPosition, this->currentLowerLid);
}

bool Eye::closeEyes()
{
    Log.verboseln("\"Eye::closeEyes()\"");
    uint8_t stepSize = 100;
    bool moveUpper = true,
         moveLower = true;

    this->moveTo(this->lowerDriverLidPosition, this->lowerLidClosedPosition);
    this->moveTo(this->upperDriverLidPosition, this->upperLidClosedPosition);

    if (this->currentUpperLid >= this->upperLidClosedPosition)
    {
        Log.infoln("%s has moved to its end position for closing eyes",
                   this->name.c_str());
        moveUpper = false;
    }
    if (this->currentLowerLid >= this->lowerLidClosedPosition)
    {
        Log.infoln("%s has moved to its end position for closing eyes",
                   this->name.c_str());

        moveUpper = false;
    }

    if (this->isMoving)
    {
        Log.traceln("%s is still moving. The current upper lid position is %d and the current lower lid position is %d",
                    this->name.c_str(),
                    this->currentUpperLid,
                    this->currentLowerLid);
        if (moveLower)
        {
            this->currentLowerLid += stepSize;
            this->driver->writeMicroseconds(this->lowerDriverLidPosition, this->currentLowerLid);
        }
        if (moveUpper)
        {
            this->currentUpperLid += stepSize;
            this->driver->writeMicroseconds(this->upperDriverLidPosition, this->currentUpperLid);
        }
    }
    else
    {
        Log.infoln("%s is starting closing eyes. The upper current position is %d and the current lower position is %d",
                   this->name.c_str(),
                   this->currentUpperLid,
                   this->currentLowerLid);
        this->isMoving = true;
    }

    this->isMoving = moveUpper && moveLower;

    return this->isMoving;
}

void Eye::lookDown()
{
    if (this->isMoving)
    {
    }

    this->isMoving = true;
}

bool Eye::lookLeft()
{
    if (this->isMoving)
    {
        return false;
    }

    this->isMoving = true;

    return this->isMoving;
}

bool Eye::lookRight()
{
    return false;
}

void Eye::lookUp()
{
}

bool Eye::openEyes()
{
    Log.verboseln("\"Eye::closeEyes()\"");

    this->moveTo(this->lowerDriverLidPosition, this->lowerLidClosedPosition);
    this->moveTo(this->upperDriverLidPosition, this->upperLidClosedPosition);

    uint8_t stepSize = 100;
    bool moveUpper = true,
         moveLower = true;

    if (this->currentUpperLid <= this->upperLidOpenPosition)
    {
        Log.infoln("%s has moved to its end position for closing eyes",
                   this->name.c_str());

        moveUpper = false;
    }
    if (this->currentLowerLid <= this->lowerLidOpenPosition)
    {
        Log.infoln("%s has moved to its end position for closing eyes",
                   this->name.c_str());

        moveUpper = false;
    }

    if (this->isMoving)
    {
        Log.traceln("%s is still moving. The current upper lid position is %d and the current lower lid position is %d",
                    this->name.c_str(),
                    this->currentUpperLid,
                    this->currentLowerLid);
        if (moveLower)
        {
            this->currentLowerLid -= stepSize;
            // this->moveTo(this->lowerDriverLidPosition, this->lowerLidOpenPosition);
            this->driver->writeMicroseconds(this->lowerDriverLidPosition, this->currentLowerLid);
        }
        if (moveUpper)
        {
            this->currentUpperLid -= stepSize;
            this->driver->writeMicroseconds(this->upperDriverLidPosition, this->currentUpperLid);
        }
    }
    else
    {
        Log.infoln("%s is starting closing eyes. The upper current position is %d and the current lower position is %d",
                   this->name.c_str(),
                   this->currentUpperLid,
                   this->currentLowerLid);
        this->isMoving = true;
    }

    this->isMoving = moveUpper && moveLower;

    return this->isMoving;
}
