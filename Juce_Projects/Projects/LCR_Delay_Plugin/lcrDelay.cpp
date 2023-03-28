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
    // DelayArrP[2].incrementDelay();
    // std::cout << "THIS IS THE cOutput: " << cOutput << std::endl;
    return LorRoutput + cOutput;
}

//void LcrDelay::changeDelayLine( float drywetL,float drywetR, float drywetC, float feedbackL,float feedbackR,float feedbackC, float delaytimeL, float delaytimeR,float delaytimeC )
//{
//    // set the delay parameters for left and right
//    DelayArrP[0].setDryWet(drywetL);
//    DelayArrP[1].setDryWet(drywetR);
//    DelayArrP[2].setDryWet(drywetC);
//
//    DelayArrP[0].setFeedback(feedbackL);
//    DelayArrP[1].setFeedback(feedbackR);
//    DelayArrP[2].setFeedback(feedbackC);
//
//    DelayArrP[0].setDelayTime(delaytimeL);
//    DelayArrP[1].setDelayTime(delaytimeR);
//    DelayArrP[2].setDelayTime(delaytimeC);
//}

void LcrDelay::changeDelayLine(int ch, int delaytime, float feedback, float drywet)
{
    delayTimesLCR[ch] = delaytime;
    DelayArrP[ch].resetDelayTime(delaytime);

    feedbackLCR[ch] = feedback;
    DelayArrP[ch].setFeedback(feedback);

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
