#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LowpassHighpassFilterAudioProcessorEditor::LowpassHighpassFilterAudioProcessorEditor (LowpassHighpassFilterAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), processorRef (p)
{
    addAndMakeVisible(cutoffFrequencySlider);
    cutoffFrequencySlider.setSliderStyle(
            juce::Slider::SliderStyle::LinearVertical);
    cutoffFrequencyAttachment.reset(
            new juce::AudioProcessorValueTreeState::SliderAttachment(
                    vts,"cutoff_frequency", cutoffFrequencySlider));

    addAndMakeVisible(cutoffFrequencyLabel);
    cutoffFrequencyLabel.setText("Cutoff Frequency", juce::dontSendNotification);

    addAndMakeVisible(highpassButton);
    highpassAttachment.reset(
            new juce::AudioProcessorValueTreeState::ButtonAttachment(vts,"highpass",highpassButton));

    setSize (200, 400);
}

LowpassHighpassFilterAudioProcessorEditor::~LowpassHighpassFilterAudioProcessorEditor()
{
}

//==============================================================================
void LowpassHighpassFilterAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
}

void LowpassHighpassFilterAudioProcessorEditor::resized()
{
    cutoffFrequencySlider.setBounds({15,35,100,300});
    cutoffFrequencyLabel.setBounds({cutoffFrequencySlider.getX()+30,cutoffFrequencySlider.getY()-30,200,50});

    highpassButton.setBounds({cutoffFrequencySlider.getX() , cutoffFrequencySlider.getY() + cutoffFrequencySlider.getHeight() + 15, 30, 50});
    highpassButtonLabel.setBounds({cutoffFrequencySlider.getX() + highpassButton.getWidth()+15,
                                   cutoffFrequencySlider.getY(),
                                   cutoffFrequencySlider.getWidth() - highpassButton.getWidth(),
                                   highpassButton.getHeight()});
}
