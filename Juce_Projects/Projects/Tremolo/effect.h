#pragma once
#include <iostream>

class Effect {
public:    
    virtual void prepareToPlay (double sampleRate) = 0;
    virtual float output (float input) = 0;
};