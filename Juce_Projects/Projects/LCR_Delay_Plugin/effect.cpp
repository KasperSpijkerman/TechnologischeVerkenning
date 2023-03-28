#include "effect.h"

Effect::Effect(){

}

Effect::~Effect(){

}

void Effect::setDryWet(float wetSig){
    if(wetSig>1.0){
        wetSig = 1.0;
    }
    wet = wetSig;
    dry = 1 - wetSig;
}

void Effect::setInputChannels(int amount){
    inputChannels = amount;
}

void Effect::setOutputChannels(int amount){
    outputChannels = amount;
}

float Effect::msToSamples(float ms, int sampleRate){
    return(float) ( ( (double) ms) * sampleRate/1000.0);
}
