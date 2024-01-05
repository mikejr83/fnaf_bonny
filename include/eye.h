#pragma once

#include <ArduinoLog.h>
#include <ServoEasing.h>

#ifndef _EYE_H
#define _EYE_H

class Eye
{
private:
    const char *name;
    int lookLeftPosition,
        lookRightPosition,
        upperClosedPosition,
        upperOpenPosition,
        lowerClosedPosition,
        lowerOpenPosition;

public:
    ServoEasing *pitch;
    ServoEasing *yaw;
    ServoEasing *upper;
    ServoEasing *lower;

    Eye(const char *name,
        int pitchPin,
        int yawPin,
        int upperPin,
        int lowerPin,
        int lookLeftPosition,
        int lookRightPosition,
        int upperClosedPosition,
        int upperOpenPosition,
        int lowerClosedPosition,
        int lowerOpenPosition);

    ~Eye();

    void lookLeft();
    void lookRight();

    void lookUp();
    void lookDown();

    void closeEyes();
    void openEyes();

    void lookAhead();
};

#endif