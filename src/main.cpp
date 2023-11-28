#include "settings.h"

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

#include <Adafruit_PWMServoDriver.h>
#include <ArduinoLog.h>
#include <Thread.h>
#include <ThreadController.h>

#include "face.h"


Face *face;
Thread *faceThread;
ThreadController *threadController;

void faceThreadCallback()
{
  Log.verboseln("\"faceThreadCallback()\" executing");
  face->update();
}

void setup()
{
  #ifndef DISABLE_LOGGING
  Serial.begin(9600);
  Log.begin(LOG_LEVEL, &Serial);
  #endif

  face = new Face();

  faceThread = new Thread(faceThreadCallback);
  faceThread->enabled = true;
  faceThread->setInterval(THREAD_INTERVAL);

  delay(500);
}

// You can use this function if you'd like to set the pulse length in seconds
// e.g. setServoPulse(0, 0.001) is a ~1 millisecond pulse width. It's not precise!
// void setServoPulse(uint8_t n, double pulse) {
//   double pulselength;

//   pulselength = 1000000;   // 1,000,000 us per second
//   pulselength /= SERVO_FREQ;   // Analog servos run at ~60 Hz updates
//   Serial.print(pulselength); Serial.println(" us per period");
//   pulselength /= 4096;  // 12 bits of resolution
//   Serial.print(pulselength); Serial.println(" us per bit");
//   pulse *= 1000000;  // convert input seconds to us
//   pulse /= pulselength;
//   Serial.println(pulse);
//   pwm.setPWM(n, 0, pulse);
// }

void loop()
{
  if (faceThread->shouldRun())
  {
    faceThread->run();
  }
  // Drive each servo one at a time using setPWM()
  // Serial.println(servonum);
}