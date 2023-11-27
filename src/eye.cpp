#include "settings.h"

#include <Adafruit_PWMServoDriver.h>
#include <ArduinoLog.h>

#include "eye.h"

Eye::Eye(Adafruit_PWMServoDriver *driver,
         uint8_t pitchDriverPosition,
         uint8_t yawPosition,
         uint8_t upperLidPosition,
         uint8_t lowerLidPosition)
{
    this->driver = driver;

    this->currentLowerLid = 1500;
    this->currentPitch = 1500;
    this->currentUpperLid = 1500;
    this->currentYaw = 1500;

    this->pitchDriverPosition = pitchDriverPosition;
    this->yawDriverPosition = yawDriverPosition;
    this->upperDriverLidPosition = upperDriverLidPosition;
    this->lowerDriverLidPosition = lowerDriverLidPosition;

    this->driver->writeMicroseconds(this->pitchDriverPosition, this->currentPitch);
    this->driver->writeMicroseconds(this->yawDriverPosition, this->currentYaw);
    this->driver->writeMicroseconds(this->upperDriverLidPosition, this->currentUpperLid);
    this->driver->writeMicroseconds(this->lowerDriverLidPosition, this->currentLowerLid);

    this->isMoving = false;
}

bool Eye::closeEyes()
{
    Log.verboseln("\"Eye::closeEyes()\"");

    if (this->isMoving)
    {
        Log.traceln("%s is still moving. The current upper lid position is %d and the current lower lid position is %d", 
            this->name.c_str(), 
            this->currentUpperLid,
            this->currentLowerLid);
        this->currentUpperLid += 50;
        this->currentLowerLid += 50;
        this->driver->writeMicroseconds(this->upperDriverLidPosition, this->currentUpperLid);
        this->driver->writeMicroseconds(this->lowerDriverLidPosition, this->currentLowerLid);
    }
    else
    {
        Log.infoln("%s is starting closing eyes. The upper current position is %d and the current lower position is %d", 
            this->name.c_str(),
            this->currentUpperLid,
            this->currentLowerLid);
        this->isMoving = true;
    }

    if (this->currentUpperLid >= 2000)
    {
        Log.infoln("%s has moved to its end position for closing eyes",
            this->name.c_str());

        this->isMoving = false;
    }

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
}
