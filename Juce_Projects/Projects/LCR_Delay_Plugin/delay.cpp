#include "delay.h"
#include <iostream>

Delay::Delay()
{

}

Delay::~Delay(){
    delete buffer;
}

void Delay::prepareToPlay(double sampleRate){

    sampleRateDelay = sampleRate;
    //calculate the delay in samples to make a buffer and distance with the correct size
    currentDelaySamples = msToSamples(currentDelayMs,sampleRate);
    //ms to samples
    //make a buffer as big as the delaytime in samples
    buffer = new CircBuffer(currentDelaySamples+1); //declare a buffer object to the empty buffer pointer
    buffer -> setDistance(currentDelaySamples); //set the distance of the delay in samples
}

float Delay::output(float input){
    buffer -> input(input+(outputBuffer*feedbackAmount)); //input the input to the buffer + output from the sample before * feedback amount to implement feedback
    outputBuffer = buffer -> output();//safe the output of the buffer to add it to the next input
    buffer -> incrementHeads();
    return (outputBuffer*wet) + (input*dry); //implement wet and dry
}

void Delay::setDelayTime(int MsDelay){
    currentDelayMs = MsDelay; //set the delay time in ms
//    float newDelaySamples = msToSamples(currentDelayMs,sampleRateDelay); //calculate the amount of delay in samples according to the delay in ms
//    resetDelayTime(currentDelayMs);
}

void Delay::resetDelayTime(int ms)
{
    currentDelaySamples = msToSamples(ms,sampleRateDelay);
    buffer -> getResetSize(currentDelaySamples+1); //resetting the size of the buffer according to the delaytime in samples
}

void Delay::setFeedback(float feedback){
    if(feedback>0 && feedback<0.99){ //check if feedback is the right amount
        feedbackAmount = feedback;
    } else { //feedback is not okay, due to safety it is set to 0, can use some upgrades when GUI is implemented.
        feedbackAmount = 0;
    }
}

float Delay::outputNoIncrement(float input){
    buffer -> input(input+(outputBuffer*feedbackAmount)); //input the input to the buffer + output from the sample before * feedback amount to implement feedback
    outputBuffer = buffer -> output();//safe the output of the buffer to add it to the next input
    return (outputBuffer*wet) + (input*dry); //implement wet and dry
}

void Delay::incrementDelay()
{
    buffer -> incrementHeads();
}