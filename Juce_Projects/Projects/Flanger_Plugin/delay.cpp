#include "delay.h"


Delay::Delay() 
{
}
Delay::~Delay() 
{
    delete delayBuffer;
}

void Delay::prepareToPlay(double samplerate)
{
	// setting the effect samplerate equal to given samplerate
	samplerateFX = samplerate;
	// create delaybuffer with a size 
	delayBuffer = new CircBuffer(44100*20);
	setDryWet(1);
}

float Delay::output(float input)
{
	// giving the input to writehead with feedback 
    delayBuffer->input(input +(outputDelay*delayFeedback));
	// reading output and store in variable
	outputDelay = delayBuffer->output();
	// incrementing heads
	delayBuffer->incrementHeads();
	// return the input and output based on dry wet 
	return (outputDelay*wet) + (input*dry);
}

void Delay::setDelayTime(float delayMs) {
	// setting the variable to input 
	delayTimeMs = delayMs;
	// converting to samples
	delaySamples = msToSamp(delayTimeMs,samplerateFX);
	// using the samples to the distance for the readhead
	delayBuffer->setDistance(delaySamples);
}


float Delay::msToSamp(float ms, double samplerateFX)
{
	// amount of samples calculated based on miliseconds and samplerate
	float samples = ms * samplerateFX/1000;
	return samples;
}

void Delay::setFeedback(float feedback) 
{
	// make sure feedback goes not out of range
	if(feedback > 0.99) 
	{
		delayFeedback = 0.99;
	} 
	else if(feedback < 0) 
	{
		delayFeedback = 0;
	}
	else 
	{
		delayFeedback = feedback;
	}
}


// TODO create bypass
void Delay::bypass (bool bypass) 
{

}