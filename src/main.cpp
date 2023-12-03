
#include "settings.h"

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

#include <ArduinoLog.h>
#include <Adafruit_PWMServoDriver.h>
#include <ServoEasing.hpp>

void (*resetFunc)(void) = 0;

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
      int lowerOpenPosition) : lookLeftPosition(lookLeftPosition),
                               lookRightPosition(lookRightPosition),
                               upperClosedPosition(upperClosedPosition),
                               upperOpenPosition(upperOpenPosition),
                               lowerClosedPosition(lowerClosedPosition),
                               lowerOpenPosition(lowerOpenPosition)
  {
    pitch = new ServoEasing(PCA9685_DEFAULT_ADDRESS);
    pitch->InitializeAndCheckI2CConnection(&Serial);
    pitch->attach(pitchPin, 1600);
    pitch->setMaxConstraint(2200);
    pitch->setMinConstraint(800);

    yaw = new ServoEasing(PCA9685_DEFAULT_ADDRESS);
    yaw->InitializeAndCheckI2CConnection(&Serial);
    yaw->attach(yawPin, 1600);
    yaw->setMaxConstraint(2200);
    yaw->setMinConstraint(800);

    upper = new ServoEasing(PCA9685_DEFAULT_ADDRESS);
    upper->InitializeAndCheckI2CConnection(&Serial);
    upper->attach(upperPin, upperClosedPosition);
    upper->setMaxConstraint(2200);
    upper->setMinConstraint(800);

    lower = new ServoEasing(PCA9685_DEFAULT_ADDRESS);
    lower->InitializeAndCheckI2CConnection(&Serial);
    lower->attach(lowerPin, lowerClosedPosition);
    lower->setMaxConstraint(2200);
    lower->setMinConstraint(800);
  }

  ~Eye()
  {
    delete pitch;
    delete yaw;
    delete upper;
    delete lower;
  }

  void closeEyes()
  {
    Log.verboseln("closeEyes()");

    Log.traceln("Lower to: %d - Upper to %d", lowerClosedPosition, upperClosedPosition);

    lower->startEaseTo(lowerClosedPosition, 50);
    upper->startEaseTo(upperClosedPosition, 50);
  }

  void openEyes()
  {
    Log.verboseln("openEyes()");

    Log.traceln("Lower to: %d - Upper to %d", lowerOpenPosition, upperOpenPosition);

    lower->startEaseTo(lowerOpenPosition, 75);
    upper->startEaseTo(upperOpenPosition, 75);
  }

  bool lookLeft()
  {
    Log.verboseln("lookLeft()");
    pitch->startEaseTo(lookLeftPosition, 30);
  }

  bool lookRight()
  {
    Log.verboseln("lookRight()");
    pitch->startEaseTo(lookRightPosition, 30);
  }

  bool lookAhead()
  {
    Log.verboseln("lookAhead()");
    pitch->startEaseTo(1500, 30);
    yaw->startEaseTo(1500, 30);
  }
};

Eye *left;
Eye *right;
uint32_t cycle = 0;

void initializeEyes()
{
  right = new Eye(4,
                  5,
                  6,
                  7,
                  1100,
                  1800,
                  UPPER_R_CLOSED,
                  UPPER_R_OPENED,
                  LOWER_R_CLOSED,
                  LOWER_R_OPENED);
  left = new Eye(0,
                 1,
                 2,
                 3,
                 1000,
                 2000,
                 UPPER_L_CLOSED,
                 UPPER_L_OPENED,
                 LOWER_L_CLOSED,
                 LOWER_L_OPENED);

  setSpeedForAllServos(80);
  setEasingTypeForAllServos(EASE_CUBIC_OUT);
}

void setup()
{
  Serial.begin(115200);

#ifndef DISABLE_LOGGING
  Log.begin(LOG_LEVEL, &Serial);
#endif

  initializeEyes();

  updateAndWaitForAllServosToStop();

  Log.infoln("Done initializing eyes");

  delay(4000);
}

void loop()
{

  Log.infoln("opening eyes");
  left->openEyes();
  right->openEyes();

  updateAndWaitForAllServosToStop();
  Log.infoln("done opening eyes");

  delay(4000);

  cycle++;
  Log.infoln("Starting cycle %d", cycle);

  delay(1000);
  Log.infoln("look left");
  left->lookLeft();
  right->lookLeft();

  updateAndWaitForAllServosToStop();

  delay(1000);

  Log.infoln("look right");
  left->lookRight();
  right->lookRight();

  updateAndWaitForAllServosToStop();

  delay(1000);

  Log.infoln("look ahead");
  left->lookAhead();
  right->lookAhead();

  updateAndWaitForAllServosToStop();

  delay(1000);
  Log.infoln("closing eyes");
  left->closeEyes();
  right->closeEyes();

  updateAndWaitForAllServosToStop();

  delay(100);
}