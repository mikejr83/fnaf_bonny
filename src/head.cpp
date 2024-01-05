#include "settings.h"

#include <ArduinoLog.h>
#include <ServoEasing.hpp>

#include "face.h"
#include "head.h"

Head::Head()
{
}

Head::~Head()
{
    delete face;
}

void Head::initialize()
{
    face = new Face();

    face->initialize();

    setSpeedForAllServos(80);
    setEasingTypeForAllServos(EASE_CUBIC_OUT);

    updateAndWaitForAllServosToStop();

    Log.infoln(F("Done initializing"));
}

void Head::closeEyes()
{
    face->closeEyes();
}

void Head::openEyes()
{
    face->openEyes();
}

void Head::lookLeft()
{
    face->lookLeft();
}

void Head::lookRight()
{
    face->lookRight();
}

void Head::lookAhead()
{
    face->lookAhead();
}

void Head::closeMouth()
{
    face->closeMouth();
}

void Head::openMouth()
{
    face->openMouth();
}