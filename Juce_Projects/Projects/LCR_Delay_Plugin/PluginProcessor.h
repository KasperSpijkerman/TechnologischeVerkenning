/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "lcrDelay.h"
//==============================================================================
/**
*/
class LCRDelayAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    LCRDelayAudioProcessor();
    ~LCRDelayAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    // creating a Value Tree State object for controlling parameters.
    juce::AudioProcessorValueTreeState apvts;
    // creating 2 LCRDelay objects for stereo-LCRDelay
    //std::array<LcrDelay, 2> LcrDelays;
    LcrDelay LcrDelay;



private:
    // creating smoothed values for every parameter
    juce::SmoothedValue<float> previousdryWetL {0.0f};
    juce::SmoothedValue<float> previousdryWetR {0.0f};
    juce::SmoothedValue<float> previousdryWetC {0.0f};
    juce::SmoothedValue<float>  previousfeedbackL {0.0f};
    juce::SmoothedValue<float>  previousfeedbackR {0.0f};
    juce::SmoothedValue<float>  previousfeedbackC {0.0f};
    juce::SmoothedValue<float>  previousdelayTimeL {0.0f};
    juce::SmoothedValue<float>  previousdelayTimeR {0.0f};
    juce::SmoothedValue<float>  previousdelayTimeC {0.0f};

    // the actual realtime atomic float values of parameters, init with nullpointer for protection
    std::atomic<float>* dryWetL = nullptr;
    std::atomic<float>* dryWetR = nullptr;
    std::atomic<float>* dryWetC = nullptr;
    std::atomic<float>* feedbackL  = nullptr;
    std::atomic<float>* feedbackR  = nullptr;
    std::atomic<float>* feedbackC  = nullptr;
    std::atomic<float>* delayTimeL  = nullptr;
    std::atomic<float>* delayTimeR  = nullptr;
    std::atomic<float>* delayTimeC  = nullptr;


    // mainvolume variabele
    float mainVolume = 0.8f;

    juce::AudioProcessorValueTreeState::ParameterLayout createParameters();
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LCRDelayAudioProcessor)
};
