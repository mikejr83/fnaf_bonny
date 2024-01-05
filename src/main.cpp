
#include "settings.h"

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

#include <ArduinoLog.h>
#include <Adafruit_PWMServoDriver.h>

#include "head.h"
#include "led_ops.h"

void (*resetFunc)(void) = 0;

Head *head;
uint32_t cycle = 0;

void setup()
{
  Serial.begin(115200);
#if defined(__AVR_ATmega32U4__) || defined(SERIAL_PORT_USBVIRTUAL) || defined(SERIAL_USB) /*stm32duino*/ || defined(USBCON) /*STM32_stm32*/ || defined(SERIALUSB_PID) || defined(ARDUINO_attiny3217)
  delay(4000); // To be able to connect Serial monitor after reset or power up and before first print out. Do not wait for an attached Serial Monitor!
#endif

#ifndef DISABLE_LOGGING
  Log.begin(LOG_LEVEL, &Serial);
#endif

  head = new Head();
  head->initialize();

  head->lookAhead();
  updateAndWaitForAllServosToStop();

  Log.infoln(F("Set-up complete"));
  Serial.flush();
}

void initialize()
{
  Log.noticeln(F("Starting at initial state: Open eyes, look ahead, and closed mouth"));
  head->openEyes();
  head->lookAhead();
  head->closeMouth();

  
  while (ServoEasing::areInterruptsActive())
  {
    blinkLED();
  }

  // updateAndWaitForAllServosToStop();

  Log.traceln(F("Completed moving to initial state; delaying for %dms"), DELAY_BETWEEN_SMALL_MOVEMENTS);

  delay(DELAY_BETWEEN_SMALL_MOVEMENTS);
}

void standardLoop()
{
  initialize();

  Log.noticeln(F("Starting look left"));
  head->lookLeft();

  while (ServoEasing::areInterruptsActive())
  {
    blinkLED();
  }

  // updateAndWaitForAllServosToStop();

  Log.traceln(F("Completed looking left; delaying for %dms"), DELAY_BETWEEN_SMALL_MOVEMENTS);
  delay(DELAY_BETWEEN_SMALL_MOVEMENTS);

  Log.noticeln(F("Starting look right"));
  head->lookRight();

  while (ServoEasing::areInterruptsActive())
  {
    blinkLED();
  }

  // updateAndWaitForAllServosToStop();

  Log.traceln(F("Completed looking right; delaying for %dms"), DELAY_BETWEEN_SMALL_MOVEMENTS);
  delay(DELAY_BETWEEN_SMALL_MOVEMENTS);

  Log.noticeln("Starting look ahead");
  head->lookAhead();

  while (ServoEasing::areInterruptsActive())
  {
    blinkLED();
  }

  // updateAndWaitForAllServosToStop();

  Log.traceln(F("Completed looking ahead; delaying for %dms"), DELAY_BETWEEN_SMALL_MOVEMENTS);
  delay(DELAY_BETWEEN_SMALL_MOVEMENTS);

  // delay(1000);
  // Log.infoln("closing eyes");
  // left->closeEyes();
  // right->closeEyes();

  while (ServoEasing::areInterruptsActive())
  {
    blinkLED();
  }

  // updateAndWaitForAllServosToStop();
  Log.noticeln(F("Starting close eyes and open mouth movement"));
  head->closeEyes();
  head->openMouth();

  while (ServoEasing::areInterruptsActive())
  {
    blinkLED();
  }

  // updateAndWaitForAllServosToStop();
  Log.traceln(F("Completed closing eyes and opening mouth"));
}

void testBlink()
{
  initialize();

  Log.noticeln(F("Starting close eyes and open mouth movement"));
  head->closeEyes();

  while (ServoEasing::areInterruptsActive())
  {
    blinkLED();
  }

  // updateAndWaitForAllServosToStop();
  Log.traceln(F("Completed closing eyes and opening mouth"));

  delay(500);
}

void loop()
{
#ifdef RUN_NORMAL
  standardLoop();
#elif defined(TEST_BLINK)
  testBlink();
#endif
}