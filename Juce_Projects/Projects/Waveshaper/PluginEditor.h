/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class WaveshaperAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                              public WaveshaperAudioProcessor
{
public:
    WaveshaperAudioProcessorEditor (WaveshaperAudioProcessor&);
    ~WaveshaperAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    WaveshaperAudioProcessor& audioProcessor;

    //creating the sliders with labels for tremolo rate and depth
    juce::Slider driveSlider;
    juce::Label  driveLabel;
    juce::Slider drywetSlider;
    juce::Label  drywetLabel;
    juce::TextEditor Title;

    // linking the slider
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> driveSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> drywetSliderAttachment;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveshaperAudioProcessorEditor)
};
