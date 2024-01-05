#pragma once

#include "settings.h"
#include "eye.h"
#include "jaw.h"

#ifndef _FACE_H
#define _FACE_H

class Face
{
private:
    Eye *leftEye;
    Eye *rightEye;
    Jaw *jaw;
public:
    Face();
    ~Face();
    void initialize();

    void closeEyes();
    void openEyes();

    void lookLeft();
    void lookRight();
    
    void lookAhead();

    void closeMouth();
    void openMouth();
};
#endif