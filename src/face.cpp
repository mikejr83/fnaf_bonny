#include "settings.h"

#include <ArduinoLog.h>
#include <ServoEasing.h>

#include "face.h"
#include "jaw.h"

Face::Face()
{
}

Face::~Face()
{
    delete jaw;
    delete leftEye;
    delete rightEye;
}

void Face::initialize()
{
    jaw = new Jaw(8);
    leftEye = new Eye("left",
                      LEFT_EYE_PITCH_PIN,
                      LEFT_EYE_YAW_PIN,
                      LEFT_EYE_UPPER_PIN,
                      LEFT_EYE_LOWER_PIN,
                      1000,
                      2000,
                      UPPER_L_CLOSED,
                      UPPER_L_OPENED,
                      LOWER_L_CLOSED,
                      LOWER_L_OPENED);
    rightEye = new Eye("right",
                       RIGHT_EYE_PITCH_PIN,
                       RIGHT_EYE_YAW_PIN,
                       RIGHT_EYE_UPPER_PIN,
                       RIGHT_EYE_LOWER_PIN,
                       1100,
                       1800,
                       UPPER_R_CLOSED,
                       UPPER_R_OPENED,
                       LOWER_R_CLOSED,
                       LOWER_R_OPENED);

    Log.infoln(F("Face has been initialized"));
}

void Face::closeEyes()
{
    leftEye->closeEyes();
    rightEye->closeEyes();
}

void Face::openEyes()
{
    leftEye->openEyes();
    rightEye->openEyes();
}

void Face::lookLeft()
{
    leftEye->lookLeft();
    rightEye->lookLeft();
}

void Face::lookRight()
{
    leftEye->lookRight();
    rightEye->lookRight();
}

void Face::lookAhead()
{
    leftEye->lookAhead();
    rightEye->lookAhead();
}

void Face::closeMouth()
{
    jaw->closeJaw();
}

void Face::openMouth()
{
    jaw->openJaw();
}