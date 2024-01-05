#pragma once

#ifndef _JAW_H
#define _JAW_H

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
#endif