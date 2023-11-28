#include "settings.h"

#include <Adafruit_PWMServoDriver.h>
#include <ArduinoLog.h>

#include "eye.h"

Eye::Eye(Adafruit_PWMServoDriver *driver,
         uint8_t pitchDriverPosition,
         uint8_t yawDriverPosition,
         uint8_t upperDriverLidPosition,
         uint8_t lowerDriverLidPosition) : Mover(driver, 50),
                                           pitchDriverPosition(pitchDriverPosition),
                                           yawDriverPosition(upperDriverLidPosition),
                                           upperDriverLidPosition(pitchDriverPosition),
                                           lowerDriverLidPosition(lowerDriverLidPosition),

                                           currentPitch(1500),
                                           currentYaw(1500),
                                           currentUpperLid(1500),
                                           currentLowerLid(1500),

                                           upperLidClosedPosition(2200),
                                           upperLidOpenPosition(1000),
                                           lowerLidClosedPosition(2200),
                                           lowerLidOpenPosition(1000),
                                           leftEndPosition(2000),
                                           rightEndPosition(800),
                                           upEndPosition(2000),
                                           downEndPosition(1000)
{
    this->driver->writeMicroseconds(this->pitchDriverPosition, this->currentPitch);
    this->driver->writeMicroseconds(this->yawDriverPosition, this->currentYaw);
    this->driver->writeMicroseconds(this->upperDriverLidPosition, this->currentUpperLid);
    this->driver->writeMicroseconds(this->lowerDriverLidPosition, this->currentLowerLid);
}

bool Eye::closeEyes()
{
    Log.verboseln("\"Eye::closeEyes()\"");

    bool lowerIsAtClosedPosition =
        this->moveTo(this->lowerDriverLidPosition, this->lowerLidClosedPosition);
    bool upperIsAtClosedPosition =
        this->moveTo(this->upperDriverLidPosition, this->upperLidClosedPosition);

    if (lowerIsAtClosedPosition)
    {
        Log.infoln("%s lower lid has moved to its end position for closing eyes",
                   this->name.c_str());
    }
    if (upperIsAtClosedPosition)
    {
        Log.infoln("%s upper lid has moved to its end position for closing eyes",
                   this->name.c_str());
    }

    this->isMoving = !lowerIsAtClosedPosition && !upperIsAtClosedPosition;

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

    bool lowerIsAtOpenPosition =
        this->moveTo(this->lowerDriverLidPosition, this->lowerLidOpenPosition);
    bool upperIsAtOpenPosition =
        this->moveTo(this->upperDriverLidPosition, this->upperLidOpenPosition);

    if (lowerIsAtOpenPosition)
    {
        Log.infoln("%s lower lid has moved to its end position for opening eyes",
                   this->name.c_str());
    }
    if (upperIsAtOpenPosition)
    {
        Log.infoln("%s upper lid has moved to its end position for opening eyes",
                   this->name.c_str());
    }

    this->isMoving = !lowerIsAtOpenPosition && !upperIsAtOpenPosition;

    return this->isMoving;
}