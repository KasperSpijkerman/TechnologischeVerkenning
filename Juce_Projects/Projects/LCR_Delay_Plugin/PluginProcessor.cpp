#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LCRDelayAudioProcessor::LCRDelayAudioProcessor()
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

LCRDelayAudioProcessor::~LCRDelayAudioProcessor()
{
}

//==============================================================================
const juce::String LCRDelayAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool LCRDelayAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool LCRDelayAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool LCRDelayAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double LCRDelayAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int LCRDelayAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int LCRDelayAudioProcessor::getCurrentProgram()
{
    return 0;
}

void LCRDelayAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String LCRDelayAudioProcessor::getProgramName (int index)
{
    return {};
}

void LCRDelayAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void LCRDelayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
//    for (LcrDelay& LcrDelay : LcrDelays)
//    {
//
//    }
    LcrDelay.lcrDelayPrepareToPlay(sampleRate);

    // setting the time for the ramp of adjusting the values
    previousdryWetL.reset(sampleRate,0.005);
    previousdryWetR.reset(sampleRate,0.005);
    previousdryWetC.reset(sampleRate,0.005);
    previousfeedbackL.reset(sampleRate,0.005);
    previousfeedbackR.reset(sampleRate,0.005);
    previousfeedbackC.reset(sampleRate,0.005);
    previousdelayTimeL.reset(sampleRate,0.005);
    previousdelayTimeR.reset(sampleRate,0.005);
    previousdelayTimeC.reset(sampleRate,0.005);
}

void LCRDelayAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool LCRDelayAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void LCRDelayAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
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
    LcrDelay.changeDelayLine(0,previousdelayTimeL.getNextValue(),previousfeedbackL.getNextValue(),previousdryWetL.getNextValue());
    LcrDelay.changeDelayLine(1,previousdelayTimeR.getNextValue(),previousfeedbackR.getNextValue(),previousdryWetR.getNextValue());
    LcrDelay.changeDelayLine(2,previousdelayTimeC.getNextValue(),previousfeedbackC.getNextValue(),previousdryWetC.getNextValue());
     //setting delay parameters for different channels.

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

        // process the audio
        for(int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            for (int channel = 0; channel < totalNumInputChannels; ++channel) {
                auto* channelData = buffer.getWritePointer (channel);
                channelData[sample] = LcrDelay.lcrDelayOutput(buffer.getSample(channel, sample), channel) * mainVolume;
            }
            LcrDelay.lcrIncrementC();
        }


}

//==============================================================================
bool LCRDelayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* LCRDelayAudioProcessor::createEditor()
{
    return new LCRDelayAudioProcessorEditor (*this,apvts);
}

//==============================================================================
void LCRDelayAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

// keeping the state of the parameters
void LCRDelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
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
    return new LCRDelayAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout LCRDelayAudioProcessor::createParameters()
{
    // creating a vector for all parameters
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    // creating every parameter that is going to be controlled, id to identify, actual name, range and default value
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "drywetL", 1 }, "Dry-Wet-L", 0.0f, 1.0f,1.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "drywetR", 2 }, "Dry-Wet-R", 0.0f, 1.0f,1.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "drywetC", 3 }, "Dry-Wet-C", 0.0f, 1.0f,1.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"feedbackL",4}, "Feedback-L", 0.0f, 0.90f,0.5f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"feedbackR",5}, "Feedback-R", 0.0f, 0.90f,0.5f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"feedbackC",6}, "Feedback-C", 0.0f, 0.90f,0.5f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"delaytimeL",7}, "Delaytime-L", 0.0f, 3000.0f,100.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"delaytimeR",8}, "Delaytime-R", 0.0f, 3000.0f,100.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"delaytimeC",9}, "Delaytime-C", 0.0f, 3000.0f,100.0f));

    // returning the whole vector with parameters
    return {params.begin(), params.end()};
}