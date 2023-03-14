#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FlangerAudioProcessor::FlangerAudioProcessor()
:
// giving the Audio value tree state to the constructor and calling the createParameters function for all parameters, nullptr for undo manager so it won't be used.
    AudioProcessor (BusesProperties()
                   .withInput  ("Input",  juce::AudioChannelSet::mono(), true)
                   .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                   ), apvts(*this, nullptr,"Parameters", createParameters())
{
}

FlangerAudioProcessor::~FlangerAudioProcessor()
{
}

//==============================================================================
const juce::String FlangerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FlangerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FlangerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool FlangerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double FlangerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FlangerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FlangerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FlangerAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String FlangerAudioProcessor::getProgramName (int index)
{
    return {};
}

void FlangerAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void FlangerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    for (Flanger& flanger : flangers)
    {
       flanger.prepareToPlay(sampleRate);
    }
}

void FlangerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FlangerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void FlangerAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // getting all parameters in an atomic float
    auto dw = apvts.getRawParameterValue("drywet");
    auto fb = apvts.getRawParameterValue("feedback");
    auto rl = apvts.getRawParameterValue("rateL");
    auto rr = apvts.getRawParameterValue("rateR");
    auto dl = apvts.getRawParameterValue("depthL");
    auto dr = apvts.getRawParameterValue("depthR");
    auto i = apvts.getRawParameterValue("intensity");

    dryWet = dw->load();
    feedback = fb->load();
    rateL = rl->load();
    rateR = rr->load();
    depthL = dl->load();
    depthR = dr->load();
    intensity = i->load();

    for (Flanger& flanger : flangers)
    {
        flanger.setDryWet(dryWet);
        flanger.setFeedback(feedback);
        flanger.setRate(rateL,rateR);
        flanger.setampDepth(depthL,depthR);
        flanger.setIntensity(intensity);
    }

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // process the audio
        for(int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            channelData[sample] = flangers[channel].output(buffer.getSample(channel,sample),channel);
        }
    }
}

//==============================================================================
bool FlangerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* FlangerAudioProcessor::createEditor()
{
    return new FlangerAudioProcessorEditor (*this);
}

//==============================================================================
void FlangerAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void FlangerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FlangerAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout FlangerAudioProcessor::createParameters()
{
    // creating a vector for all parameters
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    // creating every parameter that is going to be controlled, id to identify, actual name, range and default value
    params.push_back (std::make_unique<juce::AudioParameterFloat>("drywet", "Dry-Wet", 0.0f, 1.0f,1.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("feedback", "Feedback", 0.0f, 0.90f,0.5f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("rateL", "Rate-L", 0.0f, 5.0f,1.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("rateR", "Rate-R", 0.0f, 5.0f,1.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("depthL", "Depth-L", 0.0f, 4.0f,0.3f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("depthR", "Depth-R", 0.0f, 4.0f,0.3f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("intensity", "Intensity", 0.0f, 20.0f,1));
    // returning the whole vector with parameters
    return {params.begin(), params.end()};
}