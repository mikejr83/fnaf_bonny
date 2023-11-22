#include "eye.h"

Eye::Eye(int pitchPin, int yawPin, int upperLidPin, int lowerLidPin)
{
    this->lowerLid.attach(lowerLidPin);
    this->pitch.attach(pitchPin);
    this->upperLid.attach(upperLidPin);
    this->yaw.attach(yawPin);

    this->lowerLid.writeMicroseconds(1500);
    this->pitch.writeMicroseconds(1500);
    this->upperLid.writeMicroseconds(1500);
    this->yaw.writeMicroseconds(1500);

    this->isMoving = false;
}

void Eye::closeEyes()
{
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

void Eye::openEyes()
{
}
