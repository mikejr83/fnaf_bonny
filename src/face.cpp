#include "settings.h"

#include <ServoEasing.h>

#include "ear.h"
#include "eye.h"
#include "face.h"

Face::Face() : currentState(0)
{
    this->leftEye = new Eye("Left Eye", 0, 1, 2, 3);
    this->rightEye = new Eye("Right Eye", 4, 5, 6, 7);

    this->leftEar = new Ear(8);
    this->rightEar = new Ear(9);
}

bool Face::update()
{
    Log.verboseln("Face::update() - Current state: %d", this->currentState);
    switch (this->currentState)
    {
    /*
     * CASE 0
     * Starting blinking. This state is the progress of closing the eyes.
     */
    case 0:
    {
        Log.traceln("In blinking state - closing");
        bool leftEyeClosedResult = this->leftEye->closeEyes();
        bool rightEyeClosedResult = this->rightEye->closeEyes();

        Log.traceln("Blinking - Closing - Left eye result: %T - Right eye result: %T", leftEyeClosedResult, rightEyeClosedResult);

        bool closed = !leftEyeClosedResult && !rightEyeClosedResult;

        if (closed)
        {
            Log.infoln("Close eye state completed for blinking");
            // move the the open state
            this->currentState = 1;
        }

        break;
    }
    /*
     * Ending blinking. This state is the progress of opening the eyes.
     */
    case 1:
    {
        Log.traceln("In blinking state - opening");
        bool leftEyeOpenedResult = this->leftEye->openEyes();
        bool rightEyeOpenedResult = this->rightEye->openEyes();

        Log.traceln("Blinking - Opening - Left eye result: %T - Right eye result: %T", leftEyeOpenedResult, rightEyeOpenedResult);

        bool opened = !leftEyeOpenedResult && !rightEyeOpenedResult;

        if (opened)
        {
            Log.infoln("Open eye state completed for blinking");
            // move the the open state
            delay(4000);
            this->currentState = 2;
        }
        break;
    }
    case 2: 
    {
        Log.traceln("Looking left");
        bool leftEyeLeftResult = this->leftEye->lookLeft();
        bool rightEyeLeftResult = this->rightEye->lookLeft();

        Log.traceln("Looking left - Left eye result: %T - Right eye result: %T", leftEyeLeftResult, rightEyeLeftResult);

        bool left = !leftEyeLeftResult && !rightEyeLeftResult;

        // if (this->leftEye->lookLeft() && !this->rightEye->lookLeft())
        // {
        //     Log.infoln("Look left completed");
        //     // move the the open state
            
        //     this->currentState = 3;
        // }

        Log.infoln("Look left completed");

        // delay(4000);
    }
    case 3: 
    {
        Log.traceln("Looking right");
        bool leftEyeRightResult = this->leftEye->lookRight();
        bool rightEyeRightResult = this->rightEye->lookRight();

        Log.traceln("Left eye result: %T - Right eye result: %T", leftEyeRightResult, rightEyeRightResult);

        bool right = !leftEyeRightResult && !rightEyeRightResult;

        if (right)
        {
            Log.infoln("Look right completed");
            // move the the open state
            delay(4000);
            this->currentState = 0;
        }
    }
    default:
    {
        Log.warningln("No handler for the state %d", this->currentState);
        break;
    }
    } // end-switch

    // this->driver->update();

    return false;
}

