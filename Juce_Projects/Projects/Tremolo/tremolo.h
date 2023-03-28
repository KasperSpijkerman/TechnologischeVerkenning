#pragma once
#include "effect.h"
#include "sine.h"
#include <iostream>

class Tremolo : public Effect
{
public:    
    // functions that tremolo uses from effects
    void prepareToPlay (double sampleRate);
    float output (float input);
    
    // setters
    void setAmplitude(float amplitude);
    void setSpeed(float newSpeed);
private:
    Sine tremSine;
    float amp {1.0f};

};