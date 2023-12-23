#pragma once

#include <ArduinoLog.h>
#include <ServoEasing.h>

class Eye
{
private:
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

    Eye(int pitchPin,
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