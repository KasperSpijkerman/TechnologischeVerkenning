#pragma once
#include <iostream>

class Effect 
{
public:    
    virtual void prepareToPlay (double sampleRate) = 0;
    virtual float output (float input) = 0;
    virtual void bypass (bool bypass) = 0;
    // set dry wet
    void setDryWet(float dryWet);
protected: 
    // dry and wet for every effect
    float dry { 0 };
    float wet { 0 };
    // empty samplerate var for every effect, will be overwritten by actual samplerate
    double samplerateFX { 0 };
};