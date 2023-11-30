#pragma once

#include <ArduinoLog.h>

#define USE_PCA9685_SERVO_EXPANDER

#define PCA9685_ACTUAL_CLOCK_FREQUENCY 25200000
#define SERVOMIN 296  // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 815  // This is the 'maximum' pulse length count (out of 4096)
#define USMIN 800     // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX 2200    // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 90 // Analog servos run at ~50 Hz updates

#define DEBUG_LOCAL
// #define DEBUG_ALL

#if defined(DEBUG_LOCAL) || defined(DEBUGALL)
#define LOG_LEVEL LOG_LEVEL_TRACE
// #define LOG_LEVEL LOG_LEVEL_VERBOSE
#endif

#ifdef DEBUG_ALL
#define DEBUG
#endif

#ifndef DEBUG_LOCAL
#define DISABLE_LOGGING 
#endif