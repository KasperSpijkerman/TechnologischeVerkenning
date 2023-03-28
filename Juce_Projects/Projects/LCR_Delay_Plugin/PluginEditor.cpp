/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <iostream>

//==============================================================================
LCRDelayAudioProcessorEditor::LCRDelayAudioProcessorEditor (LCRDelayAudioProcessor& p,juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), valueTreeState (vts), audioProcessor (p)
{

    // dry wet slider and label L
    drywetLSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    drywetLSlider.setTextBoxStyle(juce::Slider::TextBoxBelow,true,200,25);
    drywetLSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "drywetL",drywetLSlider);
    drywetLSlider.setTextValueSuffix (" Dry-wet-L");
    // labels for text attached to slider
    drywetLLabel.setText ("Dry-Wet-L", juce::dontSendNotification);
    drywetLLabel.attachToComponent (&drywetLSlider, true);
    drywetLLabel.setJustificationType(juce::Justification::topLeft);
    // adding the actual slider
    addAndMakeVisible(drywetLSlider);

    // dry wet slider and label R
    drywetRSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    drywetRSlider.setTextBoxStyle(juce::Slider::TextBoxBelow,true,200,25);
    drywetRSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "drywetR",drywetRSlider);
    drywetRSlider.setTextValueSuffix (" Dry-wet-R");
    // labels for text attached to slider
    drywetRLabel.setText ("Dry-Wet-R", juce::dontSendNotification);
    drywetRLabel.attachToComponent (&drywetRSlider, true);
    drywetRLabel.setJustificationType(juce::Justification::topLeft);
    // adding the actual slider
    addAndMakeVisible(drywetRSlider);

    // dry wet slider and label C
    drywetCSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    drywetCSlider.setTextBoxStyle(juce::Slider::TextBoxBelow,true,200,25);
    drywetCSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "drywetC",drywetCSlider);
    drywetCSlider.setTextValueSuffix (" Dry-wet-C");
    // labels for text attached to slider
    drywetCLabel.setText ("Dry-Wet-C", juce::dontSendNotification);
    drywetCLabel.attachToComponent (&drywetCSlider, true);
    drywetCLabel.setJustificationType(juce::Justification::topLeft);
    // adding the actual slider
    addAndMakeVisible(drywetCSlider);

    // feedback slider and label L
    feedbackLSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    feedbackLSlider.setTextBoxStyle(juce::Slider::TextBoxBelow,true,200,25);
    feedbackLSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "feedbackL",feedbackLSlider);
    feedbackLSlider.setTextValueSuffix (" Feedback-L");
    // labels for text attached to slider
    feedbackLLabel.setText ("Feedback-L", juce::dontSendNotification);
    feedbackLLabel.attachToComponent (&feedbackLSlider, true);
    feedbackLLabel.setJustificationType(juce::Justification::topLeft);
    // adding the actual slider
    addAndMakeVisible(feedbackLSlider);

    // feedback slider and label R
    feedbackRSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    feedbackRSlider.setTextBoxStyle(juce::Slider::TextBoxBelow,true,200,25);
    feedbackRSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "feedbackR",feedbackRSlider);
    feedbackRSlider.setTextValueSuffix (" Feedback-R");
    // labels for text attached to slider
    feedbackRLabel.setText ("Feedback-R", juce::dontSendNotification);
    feedbackRLabel.attachToComponent (&feedbackRSlider, true);
    feedbackRLabel.setJustificationType(juce::Justification::topLeft);
    // adding the actual slider
    addAndMakeVisible(feedbackRSlider);

    // feedback slider and label C
    feedbackCSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    feedbackCSlider.setTextBoxStyle(juce::Slider::TextBoxBelow,true,200,25);
    feedbackCSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "feedbackC",feedbackCSlider);
    feedbackCSlider.setTextValueSuffix (" Feedback-C");
    // labels for text attached to slider
    feedbackCLabel.setText ("Feedback-C", juce::dontSendNotification);
    feedbackCLabel.attachToComponent (&feedbackCSlider, true);
    feedbackCLabel.setJustificationType(juce::Justification::topLeft);
    // adding the actual slider
    addAndMakeVisible(feedbackCSlider);

    // delaytime slider and label L
    delayTimeLSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    delayTimeLSlider.setTextBoxStyle(juce::Slider::TextBoxBelow,true,200,25);
    delayTimeLSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "delaytimeL",delayTimeLSlider);
    delayTimeLSlider.setTextValueSuffix (" DT-L");
    // labels for text attached to slider
    delayTimeLLabel.setText ("DT-L", juce::dontSendNotification);
    delayTimeLLabel.attachToComponent (&delayTimeLSlider, true);
    delayTimeLLabel.setJustificationType(juce::Justification::topLeft);
    // adding the actual slider
    addAndMakeVisible(delayTimeLSlider);


    // delaytime slider and label R
    delayTimeRSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    delayTimeRSlider.setTextBoxStyle(juce::Slider::TextBoxBelow,true,200,25);
    delayTimeRSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "delaytimeR",delayTimeRSlider);
    delayTimeRSlider.setTextValueSuffix (" DT-R");
    // labels for text attached to slider
    delayTimeRLabel.setText ("DT-R", juce::dontSendNotification);
    delayTimeRLabel.attachToComponent (&delayTimeRSlider, true);
    delayTimeRLabel.setJustificationType(juce::Justification::topLeft);
    // adding the actual slider
    addAndMakeVisible(delayTimeRSlider);

    // delaytime slider and label C
    delayTimeCSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    delayTimeCSlider.setTextBoxStyle(juce::Slider::TextBoxBelow,true,200,25);
    delayTimeCSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "delaytimeC",delayTimeCSlider);
    delayTimeCSlider.setTextValueSuffix (" DT-C");
    // labels for text attached to slider
    delayTimeCLabel.setText ("DT-C", juce::dontSendNotification);
    delayTimeCLabel.attachToComponent (&delayTimeCSlider, true);
    delayTimeCLabel.setJustificationType(juce::Justification::topLeft);
    // adding the actual slider
    addAndMakeVisible(delayTimeCSlider);

    // OSC Port
    if (! connect (7778))
    {
        // showing error if it is not connected
        showConnectionErrorMessage ("Error: could not connect to UDP port 7778.");
    }
    // adding listeners for the parameters.
    juce::OSCReceiver::addListener(this, "/ZIGSIM/1234/compass");
    //juce::OSCReceiver::addListener(this, "/juce/feedback");
    // setting size of canvas.
    setSize (800, 800);

}

LCRDelayAudioProcessorEditor::~LCRDelayAudioProcessorEditor()
{}

//==============================================================================
void LCRDelayAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::darkviolet);
    g.setFont (juce::Font ("New Times Roman", 83.0f, juce::Font::bold));
    g.setColour(juce::Colours::orange);
    g.drawText("LCRDelay",160,50,500,100,juce::Justification::centred);
    g.setFont (juce::Font ("New Times Roman", 80.0f, juce::Font::bold));
    g.setColour(juce::Colours::deepskyblue);
    g.drawText("LCRDelay",160,50,500,100,juce::Justification::centred);



}


void LCRDelayAudioProcessorEditor::resized()
{
    // layout sliders
    drywetLSlider.setBounds(getWidth() / 8.2, getHeight() / 1.4, 200, 100);
    drywetRSlider.setBounds(getWidth() / 1.4, getHeight() / 1.4, 200, 100);
    drywetCSlider.setBounds(getWidth() / 2, getHeight() / 1.4, 200, 100);
    feedbackLSlider.setBounds(getWidth() / 8.2, getHeight() / 2.0, 200, 100);
    feedbackRSlider.setBounds(getWidth() / 1.4, getHeight() / 2.0, 200, 100);
    feedbackCSlider.setBounds(getWidth() / 2, getHeight() / 2.0, 200, 100);
    delayTimeLSlider.setBounds(getWidth() / 8.2, getHeight() / 5.0, 200, 100);
    delayTimeRSlider.setBounds(getWidth() / 1.4, getHeight() / 5.0, 200, 100);
    delayTimeCSlider.setBounds(getWidth() / 2, getHeight() / 5.0, 200, 100);


    // set the color to red
    getLookAndFeel().setColour (juce::Slider::thumbColourId, juce::Colours::blue);
}

// Function for receiving OSC and getting the messages.
void LCRDelayAudioProcessorEditor::oscMessageReceived (const juce::OSCMessage& message)
{
    if (message.size() == 2 && message[0].isFloat32())   {}
    OSCAddressPattern drywetPattern("/ZIGSIM/1234/compass");
    //OSCAddressPattern feedbackPattern("/juce/feedback");

    OSCAddress messageAddress(message.getAddressPattern().toString());

    if (drywetPattern.matches(messageAddress))
    {

    }

//    else if (feedbackPattern.matches(messageAddress))
//    {
//        feedbackSlider.setValue (juce::jlimit (0.0f, 0.90f, message[0].getFloat32()));
//    }
}

// debug OSC connection
void LCRDelayAudioProcessorEditor::showConnectionErrorMessage (const juce::String& messageText)
{
    juce::AlertWindow::showMessageBoxAsync (juce::AlertWindow::WarningIcon,
                                            "Connection error",
                                            messageText,
                                            "OK");
}