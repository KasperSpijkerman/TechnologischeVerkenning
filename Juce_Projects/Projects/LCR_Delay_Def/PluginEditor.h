/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "utilities.h"
//==============================================================================
/**
*/

// class with inheritance from OSCreceiver
class LCRdelayAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                              public LCRdelayAudioProcessor,
                                              private juce::OSCReceiver, // [1]
                                              private juce::OSCReceiver::ListenerWithOSCAddress<juce::OSCReceiver::MessageLoopCallback> // [2]
{

public:
    LCRdelayAudioProcessorEditor (LCRdelayAudioProcessor&,juce::AudioProcessorValueTreeState&);
    ~LCRdelayAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:

    // value treestate for parameters.
    juce::AudioProcessorValueTreeState& valueTreeState;
    // short
    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    //creating the sliders with labels for parameter control
    // dry wet L
    juce::Slider drywetLSlider;
    juce::Label  drywetLLabel;
    std::unique_ptr<SliderAttachment> drywetLSliderAttachment;
    // dry wet R
    juce::Slider drywetRSlider;
    juce::Label  drywetRLabel;
    std::unique_ptr<SliderAttachment> drywetRSliderAttachment;
    // dry wet C
    juce::Slider drywetCSlider;
    juce::Label  drywetCLabel;
    std::unique_ptr<SliderAttachment> drywetCSliderAttachment;
    // feedback L
    juce::Slider feedbackLSlider;
    juce::Label  feedbackLLabel;
    std::unique_ptr<SliderAttachment> feedbackLSliderAttachment;
    // feedback R
    juce::Slider feedbackRSlider;
    juce::Label  feedbackRLabel;
    std::unique_ptr<SliderAttachment> feedbackRSliderAttachment;
    // feedback C
    juce::Slider feedbackCSlider;
    juce::Label  feedbackCLabel;
    std::unique_ptr<SliderAttachment> feedbackCSliderAttachment;
    // delaytime L
    juce::Slider delayTimeLSlider;
    juce::Label  delayTimeLLabel;
    std::unique_ptr<SliderAttachment> delayTimeLSliderAttachment;
    // delaytime R
    juce::Slider delayTimeRSlider;
    juce::Label  delayTimeRLabel;
    std::unique_ptr<SliderAttachment> delayTimeRSliderAttachment;
    // delaytime C
    juce::Slider delayTimeCSlider;
    juce::Label  delayTimeCLabel;
    std::unique_ptr<SliderAttachment> delayTimeCSliderAttachment;

    // osc receiver
    juce::OSCReceiver oscReceiver;

    // utilities
    Util util;

    // compass counter, rotations
    bool tippingpoint{false};
    int compassRotations {0};
    int rotationFactor {0};

    // Functions OSC
    void oscMessageReceived (const juce::OSCMessage& message) override;
    void showConnectionErrorMessage (const juce::String& messageText);
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    LCRdelayAudioProcessor& audioProcessor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LCRdelayAudioProcessorEditor)
};
