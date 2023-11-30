#pragma once

#include <ServoEasing.h>

#include "ear.h"
#include "eye.h"

class Face
{
private:
    Eye *leftEye;
    Eye *rightEye;

    Ear *leftEar;
    Ear *rightEar;

    int currentState = 0;
public:
    Face();

    bool update();
};