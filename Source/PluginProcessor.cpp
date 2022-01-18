/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h" 

//==============================================================================
BasssynthAudioProcessor::BasssynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts (*this, nullptr, "Parameters", createParams())
#endif
{
   synth.addSound(new SynthSound());
   synth.addVoice(new SynthVoice());
}

BasssynthAudioProcessor::~BasssynthAudioProcessor()
{
}

//==============================================================================
const juce::String BasssynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool BasssynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool BasssynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool BasssynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double BasssynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int BasssynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int BasssynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void BasssynthAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String BasssynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void BasssynthAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void BasssynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synth.setCurrentPlaybackSampleRate(sampleRate);

    for (int i = 0; i < synth.getNumVoices(); i++)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            voice->prepareToPlay(sampleRate, samplesPerBlock);
        }
    }
}

void BasssynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool BasssynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void BasssynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (int i = 0; i < synth.getNumVoices(); i++)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            //auto& fWaveshape = *apvts.getRawParameterValue("fUNDWAVESHAPE");
            auto& fundGain = *apvts.getRawParameterValue("FUNDGAIN");
            auto& subGain = *apvts.getRawParameterValue("SUBGAIN");

            auto& attack = *apvts.getRawParameterValue("ATTACK");
            auto& decay = *apvts.getRawParameterValue("DECAY");
            auto& sustain = *apvts.getRawParameterValue("SUSTAIN");
            auto& release = *apvts.getRawParameterValue("RELEASE");
            auto& gain = *apvts.getRawParameterValue("GAIN");

            voice->update(false, fundGain, subGain, attack, decay, sustain, release, gain);


        }
    }


    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }

    for (int i = 0; i < synth.getNumVoices(); i++)
    {
        if (auto voice = dynamic_cast<juce::SynthesiserVoice*>(synth.getVoice(i)))
        {
            //controls
        }

    }

    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool BasssynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* BasssynthAudioProcessor::createEditor()
{
    return new BasssynthAudioProcessorEditor (*this);
}

//==============================================================================
void BasssynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void BasssynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BasssynthAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout BasssynthAudioProcessor::createParams()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    //oscillator controls
    //params.push_back(std::make_unique<juce::AudioParameterBool>("fUNDWAVESHAPE", "fundWaveshape", false));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FUNDGAIN", "FundamentalGain", juce::NormalisableRange<float> { 0.001f, 1.0f, 0.001f, 0.3f }, 0.2f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("SUBGAIN", "subGain", juce::NormalisableRange<float> { 0.001f, 1.0f, 0.001f, 0.3f }, 0.2f));

    //adsr controls
    params.push_back(std::make_unique<juce::AudioParameterFloat>("ATTACK", "Attack", juce::NormalisableRange<float> { 0.0f, 1.0f, 0.001f, 0.5f }, 0.01f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DECAY", "decay", juce::NormalisableRange<float> { 0.01f, 1.0f, 0.001f, 0.6f }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("SUSTAIN", "sustain", juce::NormalisableRange<float> { 0.0f, 1.0f, 0.001f, 0.7f }, 0.3f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("RELEASE", "release", juce::NormalisableRange<float> { 0.0f, 2.0f, 0.001f, 0.5f }, 0.2f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("GAIN", "gain", juce::NormalisableRange<float> { 0.01f, 1.0f, 0.001f, 0.5f }, 0.3f));
        return { params.begin(), params.end() };
}
