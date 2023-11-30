#pragma once

#include <ServoEasing.h>

#include "mover.h"

class Eye : public Mover
{
private:
    int pitchPin,
        yawPin,
        upperPin,
        lowerPin;
    int currentPitch,
        currentYaw,
        currentUpperLid,
        currentLowerLid;

protected:
    ServoEasing *pitchServo;
    ServoEasing *yawServo;
    ServoEasing *upperServo;
    ServoEasing *lowerServo;

public:
    int upperLidClosedPosition = 2200,
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

    Eye(String name,
        int pitchPin,
        int yawPin,
        int upperPin,
        int lowerPin);

    bool lookLeft();
    bool lookRight();

    void lookUp();
    void lookDown();

    bool closeEyes();
    bool openEyes();
};