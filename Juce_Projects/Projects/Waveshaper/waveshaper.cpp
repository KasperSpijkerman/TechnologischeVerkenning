// based on code from example
#include "waveshaper.h"

WaveShaper::WaveShaper() {}

WaveShaper::~WaveShaper() 
{
    delete[] buffer;
}

void WaveShaper::prepareToPlay(double samplerate) 
{
	buffer = new float[bufferSize];
    // setting drive
    setDrive(10.0f);
    // setting dry wet
    setDryWet(1);
}

float WaveShaper::output(float input)
{
	float index = (input + 1.0f) * (bufferSize * 0.5f);
    int i = (int) trunc (index);
    float indexDecimal = index - (float) i;
    // returning shaped signal and dry signal 
	return (Util::linearMap (indexDecimal, buffer[i], buffer[i + 1])*wet) + input*dry;
}

void WaveShaper::setDrive(float k)
{
  // fill buffer using arc-tan function
    for (int i = 0; i < bufferSize; ++i) 
	{
        float x = Util::mapInRange (i, 0.0f, bufferSize, -1.0f, 1.0f);
        buffer[i] = tanh (k * x) / tanh (k);
        //formula for different distortion.
        //atan (k * x) / atan (k);
	}	
}

// TODO create bypass
void WaveShaper::bypass (bool bypass)
{

}