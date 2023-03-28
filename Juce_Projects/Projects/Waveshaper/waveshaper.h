#pragma once
#include "utilities.h"
#include "effect.h"
#include <cmath>

using uint = unsigned int;

class WaveShaper : public Effect
{
public:
    WaveShaper ();
    ~WaveShaper();

    float output (float input);
    void prepareToPlay(double samplerate);
    void bypass (bool bypass);
    
    // setters 
    void setDrive (float k);
private:
    uint bufferSize { 512 };
    float* buffer;
};