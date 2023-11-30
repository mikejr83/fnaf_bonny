#include "settings.h"

#include <Arduino.h>

#include <ArduinoLog.h>
#include <ServoEasing.hpp>

ServoEasing *servoEasing;

void setup()
{
  Serial.begin(115200);

  #ifndef DISABLE_LOGGING
  Log.begin(LOG_LEVEL, &Serial);
  #endif

  servoEasing = new ServoEasing()
}

void loop()
{
  
}