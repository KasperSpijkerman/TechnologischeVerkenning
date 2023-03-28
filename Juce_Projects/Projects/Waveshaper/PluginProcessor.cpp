#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
WaveshaperAudioProcessor::WaveshaperAudioProcessor()
:
// giving the Audio value tree state to the constructor and calling the createParameters function for all parameters, nullptr for undo manager so it won't be used.
    AudioProcessor (BusesProperties()
                   .withInput  ("Input",  juce::AudioChannelSet::mono(), true)
                   .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                   ), apvts(*this, nullptr,"Parameters", createParameters())
{
}

WaveshaperAudioProcessor::~WaveshaperAudioProcessor()
{
}

//==============================================================================
const juce::String WaveshaperAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool WaveshaperAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool WaveshaperAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool WaveshaperAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double WaveshaperAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int WaveshaperAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int WaveshaperAudioProcessor::getCurrentProgram()
{
    return 0;
}

void WaveshaperAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String WaveshaperAudioProcessor::getProgramName (int index)
{
    return {};
}

void WaveshaperAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void WaveshaperAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    for (WaveShaper& waveshaper : waveshapers)
        waveshaper.prepareToPlay(sampleRate);
}

void WaveshaperAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool WaveshaperAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void WaveshaperAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // getting
    auto s = apvts.getRawParameterValue("drive");
    // setting rate according to value from
    drive = s->load();
    auto a = apvts.getRawParameterValue("drywet");
    drywet = a->load();
    // setting drive and drywet per waveshaper
    for (WaveShaper& waveshaper : waveshapers)
    {
        waveshaper.setDrive(drive);
        waveshaper.setDryWet(drywet);
    }

    // clear buffer
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // process the audio
        for(int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            channelData[sample] = waveshapers[channel].output(buffer.getSample(channel,sample)) ;
        }
    }
}

//==============================================================================
bool WaveshaperAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* WaveshaperAudioProcessor::createEditor()
{
    return new WaveshaperAudioProcessorEditor (*this);
}

//==============================================================================
void WaveshaperAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void WaveshaperAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new WaveshaperAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout WaveshaperAudioProcessor::createParameters()
{
    // all parameters
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    params.push_back (std::make_unique<juce::AudioParameterFloat>("drive", "Drive", 0.0f, 200.0f,3));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("drywet", "Drywet", 0.0f, 1.0f,3));
    return {params.begin(), params.end()};
}