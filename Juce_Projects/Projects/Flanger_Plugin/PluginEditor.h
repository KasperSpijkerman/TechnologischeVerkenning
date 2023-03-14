#pragma once

#include "JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class FlangerAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                              public FlangerAudioProcessor
{
public:
    FlangerAudioProcessorEditor (FlangerAudioProcessor&);
    ~FlangerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    FlangerAudioProcessor& audioProcessor;

    //creating the sliders with labels for parameter control

    // dry wet
    juce::Slider drywetSlider;
    juce::Label  drywetLabel;
    // feedback
    juce::Slider feedbackSlider;
    juce::Label  feedbackLabel;
    // rate L
    juce::Slider rateLSlider;
    juce::Label  rateLLabel;
    // rate R
    juce::Slider rateRSlider;
    juce::Label  rateRLabel;
    // depth L
    juce::Slider depthLSlider;
    juce::Label  depthLLabel;
    // depth R
    juce::Slider depthRSlider;
    juce::Label  depthRLabel;
    // intensity
    juce::Slider intensitySlider;
    juce::Label  intensityLabel;


    // linking the sliders to the parameters
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> drywetSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> feedbackSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> rateLSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> rateRSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> depthLSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> depthRSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> intensitySliderAttachment;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FlangerAudioProcessorEditor)
};
