/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <iostream>

//==============================================================================
SuperTramAudioProcessorEditor::SuperTramAudioProcessorEditor (SuperTramAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    Title.setText ("This is a text editor.");
    addAndMakeVisible (Title);
    rateSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    rateSlider.setTextBoxStyle(juce::Slider::TextBoxBelow,true,200,25);
    rateSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "rate",rateSlider);
    rateSlider.setTextValueSuffix (" Hz");
    // labels for text attachted to slider
    rateLabel.setText ("Rate", juce::dontSendNotification);
    rateLabel.attachToComponent (&rateSlider, true);
    rateLabel.setJustificationType(juce::Justification::topLeft);
    // adding the actual slider
    addAndMakeVisible(rateSlider);

    depthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    depthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow,true,200,25);
    depthSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "depth",depthSlider);
    depthSlider.setTextValueSuffix (" depth");
    // labels for text attachted to slider
    depthLabel.setText ("Depth", juce::dontSendNotification);
    depthLabel.attachToComponent (&depthSlider, true);
    depthLabel.setJustificationType(juce::Justification::topLeft);
    // adding the actual slider
    addAndMakeVisible(depthSlider);
    setSize (800, 800);
}

SuperTramAudioProcessorEditor::~SuperTramAudioProcessorEditor()
{
}

//==============================================================================
void SuperTramAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::purple);
    g.setFont(juce::Font (100));
    g.setColour(juce::Colours::orange);
    g.drawText("SuperTram",getLocalBounds(),juce::Justification::centredTop/1.4);



}


void SuperTramAudioProcessorEditor::resized()
{
    // layout sliders
    rateSlider.setBounds(getWidth()/5-100,getHeight()/2-50,200,100);
    depthSlider.setBounds(getWidth()/1.3-100,getHeight()/2-50,200,100);
    //
    getLookAndFeel().setColour (juce::Slider::thumbColourId, juce::Colours::red);
}

