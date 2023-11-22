#include "ear.h"

Ear::Ear(int pin)
{
    this->servo.attach(pin);

    this->servo.writeMicroseconds(1500);
}