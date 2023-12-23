#pragma once

#include <ArduinoLog.h>

#define USE_PCA9685_SERVO_EXPANDER
#define SUPPRESS_HPP_WARNING

#define THREAD_INTERVAL 1000

#define OSCILLATOR_FREQUENCY 25200000
#define SERVOMIN 296  // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 815  // This is the 'maximum' pulse length count (out of 4096)
#define USMIN 800     // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX 2200    // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 90 // Analog servos run at ~50 Hz updates

/*
Define the servo positions
*/
//Eyes - Lef
#define LOWER_L_CLOSED 1800
#define LOWER_L_OPENED 1150
#define UPPER_L_CLOSED 1100
#define UPPER_L_OPENED 1800
//Eyes - Right
#define LOWER_R_CLOSED 1200
#define LOWER_R_OPENED 1600
#define UPPER_R_CLOSED 1600
#define UPPER_R_OPENED 1900
//Jaw
#define JAW_OPEN 1400
#define JAW_CLOSED 1875


// #define LOG_LEVEL LOG_LEVEL_TRACE
// #define LOG_LEVEL LOG_LEVEL_VERBOSE
#define LOG_LEVEL LOG_LEVEL_INFO
// #define DISABLE_LOGGING 
