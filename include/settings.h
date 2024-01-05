#pragma once

#include <ArduinoLog.h>

#define USE_PCA9685_SERVO_EXPANDER
#define SUPPRESS_HPP_WARNING
#define DISABLE_COMPLEX_FUNCTIONS  

#define THREAD_INTERVAL 1000

#define OSCILLATOR_FREQUENCY 25200000
#define SERVOMIN 296  // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 815  // This is the 'maximum' pulse length count (out of 4096)
#define USMIN 800     // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX 2200    // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 90 // Analog servos run at ~50 Hz updates

#define LEFT_EYE_PITCH_PIN   1
#define LEFT_EYE_YAW_PIN     0
#define LEFT_EYE_UPPER_PIN   2
#define LEFT_EYE_LOWER_PIN   3

#define RIGHT_EYE_PITCH_PIN  5
#define RIGHT_EYE_YAW_PIN    4
#define RIGHT_EYE_UPPER_PIN  6
#define RIGHT_EYE_LOWER_PIN  7

#define JAW_PIN              8

#define LEFT_EAR_PIN         9
#define RIGHT_EAR_PIN       10


////////////////////////////////////////////////////////////////////////////////
// Define the servo positions
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
// LEFT EYE
////////////////////////////////////////
/*
    Left Eye - Lower Lid Closed Position
*/
#define LOWER_L_CLOSED 1200
/*
    Left Eye - Lower Lid Opened Position
*/
#define LOWER_L_OPENED 1800
/*
    Left Eye - Upper Lid Closed Position
*/
#define UPPER_L_CLOSED 1400 // higher number seems to make it close less
/*
    Left Eye - Upper Lid Opened Position
*/
#define UPPER_L_OPENED 1775

////////////////////////////////////////
// RIGHT EYE
////////////////////////////////////////
/*
    Right Eye - Lower Lid Closed Position
*/
#define LOWER_R_CLOSED 1200
/*
    Right Eye - Lower Lid Opened Position
*/
#define LOWER_R_OPENED 1600
/*
    Right Eye - Upper Lid Closed Position
*/
#define UPPER_R_CLOSED 1490
/*
    Right Eye - Upper Lid Opened Position
*/
#define UPPER_R_OPENED 1900

////////////////////////////////////////
// Jaw
////////////////////////////////////////
#define JAW_OPEN 1400
#define JAW_CLOSED 1875

////////////////////////////////////////////////////////////////////////////////
// Testing Parameters
////////////////////////////////////////////////////////////////////////////////
#define RUN_NORMAL
#ifndef RUN_NORMAL
#define TEST_BLINK
#endif

////////////////////////////////////////////////////////////////////////////////
// Define performance and speed.
////////////////////////////////////////////////////////////////////////////////
/*
Amount of time to delay between small movements. Used in delay() command.
*/
#define DELAY_BETWEEN_SMALL_MOVEMENTS 1000


#define LOG_LEVEL LOG_LEVEL_TRACE
// #define LOG_LEVEL LOG_LEVEL_NOTICE
// #define LOG_LEVEL LOG_LEVEL_INFO
// #define DISABLE_LOGGING 

const char SERVO_ERROR[] PROGMEM = "Error attaching servo";