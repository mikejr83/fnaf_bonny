#pragma once

#include <ArduinoLog.h>

#define THREAD_INTERVAL 5

#define OSCILLATOR_FREQUENCY 25000000
#define SERVOMIN 150  // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 600  // This is the 'maximum' pulse length count (out of 4096)
#define USMIN 600     // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX 2400    // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

#define LOG_LEVEL LOG_LEVEL_INFO
// #define DISABLE_LOGGING 
