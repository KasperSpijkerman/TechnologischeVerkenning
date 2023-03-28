#include "tremolo.h"

void Tremolo::prepareToPlay (double sampleRate)
{
   tremSine.setSamplerate(sampleRate);
   tremSine.setFrequency(1);
}


float Tremolo::output (float input) 
{
   auto tremSignal = tremSine.getSample();
   tremSine.tick();
   tremSignal *= amp;
   tremSignal += 1.0f - amp;
   return input * tremSignal;
}

void Tremolo::setAmplitude(float amplitude)
{
   this->amp = amplitude;
}
    
void Tremolo::setSpeed(float newSpeed)
{
    tremSine.setFrequency(newSpeed);
}

