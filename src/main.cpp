#include "settings.h"

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

#include <ArduinoLog.h>
#include <Adafruit_PWMServoDriver.h>
#include <ServoEasing.hpp>

#include "face.h"

Face *face;

void setup()
{
  Serial.begin(9600);
#ifndef DISABLE_LOGGING
  Serial.begin(9600);
#if defined(__AVR_ATmega32U4__) || defined(SERIAL_PORT_USBVIRTUAL) || defined(SERIAL_USB) /*stm32duino*/ || defined(USBCON) /*STM32_stm32*/ || defined(SERIALUSB_PID) || defined(ARDUINO_attiny3217)
  delay(4000); // To be able to connect Serial monitor after reset or power up and before first print out. Do not wait for an attached Serial Monitor!
#endif
  Log.begin(LOG_LEVEL, &Serial);
#endif

  face = new Face();

  delay(4000);
}

void loop()
{
  face->update();
  delay(50);
}