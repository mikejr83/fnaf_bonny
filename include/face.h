#pragma once

#include <Adafruit_PWMServoDriver.h>

#include "ear.h"
#include "eye.h"

class Face
{
private:
    Adafruit_PWMServoDriver *driver;
    Eye *leftEye;
    Eye *rightEye;

    Ear *leftEar;
    Ear *rightEar;

    int currentState = 0;
public:
    Face();

    bool update();
};