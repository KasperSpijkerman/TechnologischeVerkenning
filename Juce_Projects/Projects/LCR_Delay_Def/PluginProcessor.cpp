#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LCRdelayAudioProcessor::LCRdelayAudioProcessor()
:
// giving the Audio value tree state to the constructor and calling the createParameters function for all parameters, nullptr for undo manager so it won't be used.
    AudioProcessor (BusesProperties()
                   .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                   .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                   ), apvts(*this, nullptr,"Parameters", createParameters())
{
    // getting the parametervalues and storing them.
     dryWetL = apvts.getRawParameterValue("drywetL");
     dryWetR = apvts.getRawParameterValue("drywetR");
     dryWetC = apvts.getRawParameterValue("drywetC");
     feedbackL = apvts.getRawParameterValue("feedbackL");
     feedbackR = apvts.getRawParameterValue("feedbackR");
     feedbackC = apvts.getRawParameterValue("feedbackC");
     delayTimeL = apvts.getRawParameterValue("delaytimeL");
     delayTimeR = apvts.getRawParameterValue("delaytimeR");
     delayTimeC = apvts.getRawParameterValue("delaytimeC");

}

LCRdelayAudioProcessor::~LCRdelayAudioProcessor()
{
}

//==============================================================================
const juce::String LCRdelayAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool LCRdelayAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool LCRdelayAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool LCRdelayAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double LCRdelayAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int LCRdelayAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int LCRdelayAudioProcessor::getCurrentProgram()
{
    return 0;
}

void LCRdelayAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String LCRdelayAudioProcessor::getProgramName (int index)
{
    return {};
}

void LCRdelayAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void LCRdelayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
//    for (LCRdelay& LCRdelay : LCRdelays)
//    {
//
//    }
    lcrDelay.lcrDelayPrepareToPlay(sampleRate);

    // setting the time for the ramp of adjusting the values
    previousdryWetL.reset(sampleRate,0.0000005);
    previousdryWetR.reset(sampleRate,0.0000005);
    previousdryWetC.reset(sampleRate,0.00000005);
    previousfeedbackL.reset(sampleRate,0.00000005);
    previousfeedbackR.reset(sampleRate,0.00000005);
    previousfeedbackC.reset(sampleRate,0.00000005);
    previousdelayTimeL.reset(sampleRate,0.00000000000000005);
    previousdelayTimeR.reset(sampleRate,0.00000000000000005);
    previousdelayTimeC.reset(sampleRate,0.00000000000000005);
}

void LCRdelayAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool LCRdelayAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void LCRdelayAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();


    // retrieving the current values in realtime
    auto currentDryWetL = *dryWetL * 1.0f;
    auto currentDryWetR = *dryWetR * 1.0f;
    auto currentDryWetC = *dryWetC * 1.0f;
    auto currentFeedbackL = *feedbackL * 1.0f;
    auto currentFeedbackR = *feedbackR * 1.0f;
    auto currentFeedbackC = *feedbackC * 1.0f;
    auto currentdelayTimeL = *delayTimeL * 1.0f;
    auto currentdelayTimeR = *delayTimeR * 1.0f;
    auto currentdelayTimeC = *delayTimeC * 1.0f;

    // setting the current values targets to climb to smoothly
    previousdryWetL.setTargetValue(currentDryWetL);
    previousdryWetR.setTargetValue(currentDryWetR);
    previousdryWetC.setTargetValue(currentDryWetC);
    previousfeedbackL.setTargetValue(currentFeedbackL);
    previousfeedbackR.setTargetValue(currentFeedbackR);
    previousfeedbackC.setTargetValue(currentFeedbackC);
    previousdelayTimeL.setTargetValue(currentdelayTimeL);
    previousdelayTimeR.setTargetValue(currentdelayTimeR);
    previousdelayTimeC.setTargetValue(currentdelayTimeC);

    // setting the values of delay
    lcrDelay.changeDelayLine(0,previousdelayTimeL.getNextValue(),previousfeedbackL.getNextValue(),previousdryWetL.getNextValue());
    lcrDelay.changeDelayLine(1,previousdelayTimeR.getNextValue(),previousfeedbackR.getNextValue(),previousdryWetR.getNextValue());
    lcrDelay.changeDelayLine(2,previousdelayTimeC.getNextValue(),previousfeedbackC.getNextValue(),previousdryWetC.getNextValue());
     //setting delay parameters for different channels.

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

        // process the audio
        for(int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            for (int channel = 0; channel < totalNumInputChannels; ++channel) {
                auto* channelData = buffer.getWritePointer (channel);
                channelData[sample] = lcrDelay.lcrDelayOutput(buffer.getSample(channel, sample), channel) * mainVolume;
            }
            lcrDelay.lcrIncrementC();
        }


}

//==============================================================================
bool LCRdelayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* LCRdelayAudioProcessor::createEditor()
{
    return new LCRdelayAudioProcessorEditor (*this,apvts);
}

//==============================================================================
void LCRdelayAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

// keeping the state of the parameters
void LCRdelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));

    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName (apvts.state.getType()))
            apvts.replaceState (juce::ValueTree::fromXml (*xmlState));
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new LCRdelayAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout LCRdelayAudioProcessor::createParameters()
{
    // creating a vector for all parameters
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    // creating every parameter that is going to be controlled, id to identify, actual name, range and default value
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "drywetL", 1 }, "Dry-Wet-L", 0.0f, 1.0f,0.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "drywetR", 2 }, "Dry-Wet-R", 0.0f, 1.0f,0.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "drywetC", 3 }, "Dry-Wet-C", 0.0f, 1.0f,1.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"feedbackL",4}, "Feedback-L", 0.0f, 0.99f,0.5f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"feedbackR",5}, "Feedback-R", 0.0f, 0.99f,0.5f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"feedbackC",6}, "Feedback-C", 0.0f, 0.99f,0.5f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"delaytimeL",7}, "Delaytime-L", 0.0f, 3000.0f,100.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"delaytimeR",8}, "Delaytime-R", 0.0f, 3000.0f,100.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"delaytimeC",9}, "Delaytime-C", 0.0f, 3000.0f,100.0f));

    // returning the whole vector with parameters
    return {params.begin(), params.end()};
}