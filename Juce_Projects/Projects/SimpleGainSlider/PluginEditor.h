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
class SimpleGainSliderAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                              public juce::Slider::Listener
{
public:
    SimpleGainSliderAudioProcessorEditor (SimpleGainSliderAudioProcessor&);
    ~SimpleGainSliderAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(juce::Slider* slider) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SimpleGainSliderAudioProcessor& audioProcessor;

    //creating the slider
    juce::Slider gainSlider;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleGainSliderAudioProcessorEditor)
};
