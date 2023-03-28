/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <iostream>

//==============================================================================
WaveshaperAudioProcessorEditor::WaveshaperAudioProcessorEditor (WaveshaperAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    Title.setText ("This is a text editor.");
    addAndMakeVisible (Title);
    driveSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    driveSlider.setTextBoxStyle(juce::Slider::TextBoxBelow,true,200,25);
    driveSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "drive",driveSlider);
    driveSlider.setTextValueSuffix (" Drive");
    // labels for text attachted to slider
    driveLabel.setText ("Drive", juce::dontSendNotification);
    driveLabel.attachToComponent (&driveSlider, true);
    driveLabel.setJustificationType(juce::Justification::topLeft);
    // adding the actual slider
    addAndMakeVisible(driveSlider);

    drywetSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    drywetSlider.setTextBoxStyle(juce::Slider::TextBoxBelow,true,200,25);
    drywetSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "drywet",drywetSlider);
    drywetSlider.setTextValueSuffix (" %");
    // labels for text attachted to slider
    drywetLabel.setText ("Drywet", juce::dontSendNotification);
    drywetLabel.attachToComponent (&drywetSlider, true);
    drywetLabel.setJustificationType(juce::Justification::topLeft);
    // adding the actual slider
    addAndMakeVisible(drywetSlider);
    setSize (800, 800);
}

WaveshaperAudioProcessorEditor::~WaveshaperAudioProcessorEditor()
{
}

//==============================================================================
void WaveshaperAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::purple);
    g.setFont(juce::Font (100));
    g.setColour(juce::Colours::orange);
    g.drawText("Waveshaper",getLocalBounds(),juce::Justification::centredTop/1.4);



}


void WaveshaperAudioProcessorEditor::resized()
{
    // layout sliders
    driveSlider.setBounds(getWidth()/5-100,getHeight()/2-50,200,100);
    drywetSlider.setBounds(getWidth()/1.3-100,getHeight()/2-50,200,100);
    //
    getLookAndFeel().setColour (juce::Slider::thumbColourId, juce::Colours::red);
}

