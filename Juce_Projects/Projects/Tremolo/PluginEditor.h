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
class SuperTramAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                              public SuperTramAudioProcessor
{
public:
    SuperTramAudioProcessorEditor (SuperTramAudioProcessor&);
    ~SuperTramAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SuperTramAudioProcessor& audioProcessor;

    //creating the sliders with labels for tremolo rate and depth
    juce::Slider rateSlider;
    juce::Label  rateLabel;
    juce::Slider depthSlider;
    juce::Label  depthLabel;
    juce::TextEditor Title;

    // linking the slider
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> rateSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> depthSliderAttachment;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SuperTramAudioProcessorEditor)
};
