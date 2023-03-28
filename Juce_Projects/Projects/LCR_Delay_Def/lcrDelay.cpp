#include "lcrDelay.h"

//constructor
LcrDelay::LcrDelay()
{

}

//destructor
LcrDelay::~LcrDelay()
{

}

void LcrDelay::lcrDelayPrepareToPlay(double samplerate){
    DelayArrP = new Delay[3];
    onepole.setCoefficient(0.98);
//initialise the delays
    for(uint i = 0; i < 3; i++){
        //set all delaylines using the values in the array for each parameter
        setDelayLine(i,delayTimesLCR[i],feedbackLCR[i],drywetLCR[i]);
        DelayArrP[i].prepareToPlay(samplerate);
    };

}

float LcrDelay::lcrDelayOutput(float input, uint ch){
//variables for all the delaylines
    float LorRoutput;
    float cOutput;
//calculating all the values ch 0 = L, 1 = R and 2 = C
    LorRoutput = DelayArrP[ch].output(input);
//getting the output for the C delayline but not increment it, the increment happens in the main.cpp
    cOutput = onepole.output(DelayArrP[2].outputNoIncrement(input));
    return LorRoutput + cOutput;
}


void LcrDelay::changeDelayLine(int ch, int delaytime, float feedback, float drywet)
{
    distChange = true;
    delayTimesLCR[ch] = delaytime;
    DelayArrP[ch].setDelayTime(delaytime);
    feedbackLCR[ch] = 0;
    distChange = false;

    if (distChange == false)
    {
        feedbackLCR[ch] = feedback;
        DelayArrP[ch].setFeedback(feedback);
    }


    drywetLCR[ch] = drywet;
    DelayArrP[ch].setDryWet(drywet);
}


void LcrDelay::setDelayLine(int ch, int delaytime, float feedback, float drywet){
    delayTimesLCR[ch] = delaytime;
    DelayArrP[ch].setDelayTime(delaytime);
//    DelayArrP[ch].resetDelayTime(delaytime);

    feedbackLCR[ch] = feedback;
    DelayArrP[ch].setFeedback(feedback);

    drywetLCR[ch] = drywet;
    DelayArrP[ch].setDryWet(drywet);
}

void LcrDelay::lcrIncrementC()
{
    DelayArrP[2].incrementDelay();
}
