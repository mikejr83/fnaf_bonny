#pragma once

#include "mover.h"

class Eye: public Mover
{
private:
    Adafruit_PWMServoDriver *driver;
    uint8_t pitchDriverPosition, 
        yawDriverPosition, 
        upperDriverLidPosition, 
        lowerDriverLidPosition;
    uint16_t currentPitch, 
        currentYaw,
        currentUpperLid,
        currentLowerLid;
public:
    Eye(Adafruit_PWMServoDriver *driver,
        uint8_t pitchDriverPosition, 
        uint8_t yawDriverPosition, 
        uint8_t upperDriverLidPosition, 
        uint8_t lowerDriverLidPosition);

    String name = "Eye";

    bool lookLeft();
    bool lookRight();

    void lookUp();
    void lookDown();

    bool closeEyes();
    bool openEyes();
};