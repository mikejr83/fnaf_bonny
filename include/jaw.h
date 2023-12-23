#pragma once

#include <ArduinoLog.h>
#include <ServoEasing.h>

class Jaw
{
private:
    int jawPin;

    ServoEasing *servo;

public:
    Jaw(int jawPin);

    void openJaw();
    void closeJaw();
};