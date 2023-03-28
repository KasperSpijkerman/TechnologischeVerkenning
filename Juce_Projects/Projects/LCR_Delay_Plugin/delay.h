#ifndef _DELAY_H_
#define _DELAY_H_

#pragma once

#include "effect.h"
#include "circ_buff.h"
#include "utilities.h"

class Delay : public Effect {

public:
    //construcor and destructor
    Delay();
    ~Delay();

    //functions
    void prepareToPlay(double sampleRate) override;
    float output(float input) override;
    float outputNoIncrement(float input);
    void incrementDelay();
    void setDelayTime(int MsDelay);
    void setFeedback(float feedback);
    void resetDelayTime(int ms);

    int currentDelayMs { 0 };
    float currentDelaySamples { 0 };
    int sampleRateDelay { 0 };
    float feedbackAmount { 0 };
    float outputBuffer { 0 };

    CircBuffer *buffer; //empty pointer of the type CircBuffer
};


#endif