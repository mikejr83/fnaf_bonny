
#include "settings.h"

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

#include <ArduinoLog.h>
#include <Adafruit_PWMServoDriver.h>
#include <ServoEasing.hpp>

#include "eye.h"
#include "jaw.h"

void (*resetFunc)(void) = 0;

Eye *left;
Eye *right;
Jaw *jaw;
uint32_t cycle = 0;

void initializeEyes()
{
  jaw = new Jaw(8);
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

  // delay(4000);

  // cycle++;
  // Log.infoln("Starting cycle %d", cycle);

  // delay(1000);
  // Log.infoln("look left");
  // left->lookLeft();
  // right->lookLeft();

  // updateAndWaitForAllServosToStop();

  // delay(1000);

  // Log.infoln("look right");
  // left->lookRight();
  // right->lookRight();

  // updateAndWaitForAllServosToStop();

  // delay(1000);

  // face->openJaw();
  // Log.infoln("look ahead");
  // left->lookAhead();
  // right->lookAhead();

  // updateAndWaitForAllServosToStop();

  // delay(1000);
  // Log.infoln("closing eyes");
  // left->closeEyes();
  // right->closeEyes();

  // updateAndWaitForAllServosToStop();

  // delay(100);
  Log.infoln("closing jaw");
  jaw->closeJaw();
  updateAndWaitForAllServosToStop();
  delay(4000);
  Log.infoln("opening jaw");
  jaw->openJaw();
  updateAndWaitForAllServosToStop();
  delay(4000);
}