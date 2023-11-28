#include "settings.h"

#include <ArduinoLog.h>

#include "ear.h"
#include "eye.h"
#include "face.h"

Face::Face() : driver(new Adafruit_PWMServoDriver())
{
    this->driver->begin();
    /*
     * In theory the internal oscillator (clock) is 25MHz but it really isn't
     * that precise. You can 'calibrate' this by tweaking this number until
     * you get the PWM update frequency you're expecting!
     * The int.osc. for the PCA9685 chip is a range between about 23-27MHz and
     * is used for calculating things like writeMicroseconds()
     * Analog servos run at ~50 Hz updates, It is importaint to use an
     * oscilloscope in setting the int.osc frequency for the I2C PCA9685 chip.
     * 1) Attach the oscilloscope to one of the PWM signal pins and ground on
     *    the I2C PCA9685 chip you are setting the value for.
     * 2) Adjust setOscillatorFrequency() until the PWM update frequency is the
     *    expected value (50Hz for most ESCs)
     * Setting the value here is specific to each individual I2C PCA9685 chip and
     * affects the calculations for the PWM update frequency.
     * Failure to correctly set the int.osc value will cause unexpected PWM results
     */
    this->driver->setOscillatorFrequency(OSCILLATOR_FREQUENCY);
    this->driver->setPWMFreq(SERVO_FREQ); // Analog servos run at ~50 Hz updates

    this->leftEye = new Eye(this->driver, 0, 1, 2, 3);
    this->leftEye->name = "Left Eye";
    this->rightEye = new Eye(this->driver, 4, 5, 6, 7);
    this->rightEye->name = "Right Eye";

    this->leftEar = new Ear(this->driver, 8);
    this->rightEar = new Ear(this->driver, 9);
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

        Log.traceln("Left eye result: %T - Right eye result: %T", leftEyeClosedResult, rightEyeClosedResult);

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

        Log.traceln("Left eye result: %T - Right eye result: %T", leftEyeOpenedResult, rightEyeOpenedResult);

        bool opened = !leftEyeOpenedResult && !rightEyeOpenedResult;

        if (opened)
        {
            Log.infoln("Open eye state completed for blinking");
            // move the the open state
            this->currentState = 2;
        }
        break;
    }
    default:
    {
        Log.warningln("No handler for the state %d", this->currentState);
        break;
    }
    }

    return false;
}