#pragma once

#include "JuceLibraryCode/JuceHeader.h"
#include "flanger.h"

class FlangerAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    FlangerAudioProcessor();
    ~FlangerAudioProcessor() override;

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
    // creating 2 flanger objects for stereo-flanger
    std::array<Flanger, 2> flangers;

    // variables for the parameters that are going to be changed.
    float dryWet;
    float feedback;
    float rateL;
    float rateR;
    float depthL;
    float depthR;
    float intensity;

private:
    juce::AudioProcessorValueTreeState::ParameterLayout createParameters();
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FlangerAudioProcessor)
};
