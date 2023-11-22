#include <Servo.h>
#include <Arduino.h>

#include "eye.h"
#include "ear.h"

unsigned long currentMillis;
long previousMillis = 0; // set up timers
long interval = 5;       // time constant for timer

int stepFlag = 0;
long previousStepMillis = 0;

Eye *leftEye;
Eye *rightEye;

Ear *leftEar;
Ear *rightEar;

void setup()
{

  leftEye = new Eye(1, 2, 3, 4);
  rightEye = new Eye(5, 6, 7, 8);

  leftEar = new Ear(9);
  rightEar = new Ear(10);
}

void loop()
{
  currentMillis = millis();

  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
  }
}