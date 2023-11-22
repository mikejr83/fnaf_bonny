#pragma once

#include <Servo.h>

#include "mover.h"

class Eye: public Mover
{
private:
    Servo pitch, yaw, upperLid, lowerLid;
    int currentPitch, currentYaw, currentUpperLid, currentLowerLid;
    
public:
    Eye(int pitchPin, int yawPin, int upperLidPin, int lowerLidPin);

    bool lookLeft();
    bool lookRight();

    void lookUp();
    void lookDown();

    void closeEyes();
    void openEyes();
};