#pragma once

#include "mover.h"

class Eye: public Mover
{
private:
    uint8_t pitchDriverPosition, 
        yawDriverPosition, 
        upperDriverLidPosition, 
        lowerDriverLidPosition;
    uint16_t currentPitch, 
        currentYaw,
        currentUpperLid,
        currentLowerLid;
protected:

public:
    Eye(Adafruit_PWMServoDriver *driver,
        uint8_t pitchDriverPosition, 
        uint8_t yawDriverPosition, 
        uint8_t upperDriverLidPosition, 
        uint8_t lowerDriverLidPosition);

    String name = "Eye";

    uint16_t upperLidClosedPosition = 2200,
        upperLidOpenPosition = 1000,
        lowerLidClosedPosition = 2200,
        lowerLidOpenPosition = 1000,
        leftEndPosition = 2000,
        rightEndPosition = 1000,
        upEndPosition = 2000,
        downEndPosition = 1000;

    bool invertUpper = false,
        invertLower = false,
        invertYaw = false,
        invertPitch = false;

    bool lookLeft();
    bool lookRight();

    void lookUp();
    void lookDown();

    bool closeEyes();
    bool openEyes();
};