
#include "settings.h"

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

#include <ArduinoLog.h>
#include <Adafruit_PWMServoDriver.h>
#include <ServoEasing.hpp>

void MovementReachedHandler(ServoEasing *aServoEasingInstance);

class Eye
{
public:
  ServoEasing *pitch;
  ServoEasing *yaw;
  ServoEasing *upper;
  ServoEasing *lower;

  Eye(ServoEasing *driver, int pitchPin, int yawPin, int upperPin, int lowerPin)
  {
    uint8_t position = driver->attach(pitchPin, 1500);
    Log.infoln("Pitch %d", position);
    pitch = ServoEasing::ServoEasingArray[position];
    pitch->setMaxConstraint(2200);
    pitch->setMinConstraint(800);

    position = driver->attach(yawPin, 1500);
    Log.infoln("Yaw %d", position);
    yaw = ServoEasing::ServoEasingArray[position];
    yaw->setMaxConstraint(2200);
    yaw->setMinConstraint(800);

    position = driver->attach(upperPin, 1500);
    Log.infoln("Upper %d", position);
    upper = ServoEasing::ServoEasingArray[position];
    upper->setMaxConstraint(2200);
    upper->setMinConstraint(800);

    position = driver->attach(lowerPin, 1500);
    Log.infoln("Lower %d", position);
    lower = ServoEasing::ServoEasingArray[position];
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

  bool closeEyes()
  {
    Log.verboseln("closeEyes()");

    Log.infoln("lower %X", &lower);
    Log.infoln("upper %X", &upper);

    lower->print(&Serial, false);
    upper->print(&Serial, false);

    lower->startEaseTo(2200, 50);
    lower->startEaseTo(2200, 50, DO_NOT_START_UPDATE_BY_INTERRUPT);
    upper->startEaseTo(2200, 50);
    upper->startEaseTo(2200, 50, DO_NOT_START_UPDATE_BY_INTERRUPT);

    lower->print(&Serial, false);
    upper->print(&Serial, false);

    return false;
  }
};

ServoEasing servoEasing(PCA9685_DEFAULT_ADDRESS);

Eye *left;
Eye *right;

void setup()
{
  Serial.begin(115200);

#ifndef DISABLE_LOGGING
  Log.begin(LOG_LEVEL, &Serial);
#endif

  if (servoEasing.InitializeAndCheckI2CConnection(&Serial))
  {
  }

  
  right = new Eye(&servoEasing, 4, 5, 6, 7);
  left = new Eye(&servoEasing, 0, 1, 2, 3);

  setSpeedForAllServos(80);
  setEasingTypeForAllServos(EASE_CUBIC_OUT);

  delay(4000);

  // servoEasing.setTargetPositionReachedHandler(MovementReachedHandler);
  // left->closeEyes();
}

void loop()
{
  left->closeEyes();

  do {
    Log.infoln("hi");
        // here you can call your own program
        delay(REFRESH_INTERVAL_MILLIS); // optional 20ms delay
    } while (!updateAllServos());
  
  delay(2000);
}

void MovementReachedHandler(ServoEasing *aServoEasingInstance)
{
  Log.infoln("hi");
  // aServoEasingInstance->startEaseTo(1000);
  aServoEasingInstance->print(&Serial, false);
}