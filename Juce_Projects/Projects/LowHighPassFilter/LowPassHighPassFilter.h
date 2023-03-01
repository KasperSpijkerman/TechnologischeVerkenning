#pragma once
#include <vector>
#include <math.h>
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_basics/juce_audio_basics.h>
class LowpassHighpassFilter
{
public:
    void setHighpass(bool highpass);
    void setCutoffFrequency(float cutoffFrequency);
    void setSamplingrate(float samplingRate);

    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&);
private:
    bool highpass;
    float cutoffFrequency;
    float samplingRate;
    std::vector<float> dnBuffer;
};
