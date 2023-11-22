#pragma once

#include <Servo.h>

class Ear
{
private:
    Servo servo;
public:
    Ear(int pin);
};