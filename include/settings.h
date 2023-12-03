#pragma once

#include <ArduinoLog.h>

#define USE_PCA9685_SERVO_EXPANDER

#define THREAD_INTERVAL 1000

#define OSCILLATOR_FREQUENCY 25200000
#define SERVOMIN 296  // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 815  // This is the 'maximum' pulse length count (out of 4096)
#define USMIN 800     // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX 2200    // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 90 // Analog servos run at ~50 Hz updates

#define LOWER_L_CLOSED 1900
#define LOWER_L_OPENED 1150
#define UPPER_L_CLOSED 1050
#define UPPER_L_OPENED 1800

#define LOWER_R_CLOSED 1100
#define LOWER_R_OPENED 1600
#define UPPER_R_CLOSED 1600
#define UPPER_R_OPENED 2000



// #define LOG_LEVEL LOG_LEVEL_TRACE
// #define LOG_LEVEL LOG_LEVEL_VERBOSE
#define LOG_LEVEL LOG_LEVEL_INFO
// #define DISABLE_LOGGING 
