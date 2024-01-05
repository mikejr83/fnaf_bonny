#pragma once

#include "settings.h"
#include "face.h"

#ifndef _HEAD_H
#define _HEAD_H

class Head
{
private:
    Face *face;

public:
    Head();
    ~Head();
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