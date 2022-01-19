/*
  ==============================================================================

    SynthVoice.cpp
    Created: 17 Dec 2021 8:49:58pm
    Author:  Dylan

  ==============================================================================
*/

#include "SynthVoice.h"

bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    osc.updateFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    adsr.noteOn();
}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    adsr.noteOff();

    if (! allowTailOff || ! adsr.isActive())
    {
        clearCurrentNote();
    }
}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{

}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{
    //converts pitchWheel to range of -1 to 1
    float amount = (newPitchWheelValue - 8192) / 8192.0f;
    //converts to cents, assuming  major second range, -200 to 200 cents
    float cent = 200.0f * amount;
    //uses piecewise linear function pulled from wikipedia page on cents to apply pitch shift
    osc.updateFrequency(juce::MidiMessage::getMidiNoteInHertz(getCurrentlyPlayingNote()) * ( 1 + (.0005946 * cent)));
}

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels)
{
    osc.reset();
    adsr.setSampleRate(sampleRate);
    osc.updateSamplerate(sampleRate);
    filter.prepareToPlay(numChannels, sampleRate);
}

void SynthVoice::update(const float fundType, const float fundGain, const float sawGain, const float subGain, const float cutoffFreq, const float attack, const float decay, const float sustain, const float release, const float volume)
{
    adsr.updateADSR(attack, decay, sustain, release);
    gain = volume;
    filter.updateCutoff(cutoffFreq);
    osc.updateControls(fundType, fundGain, sawGain, subGain);
}

void SynthVoice::renderNextBlock(juce::AudioBuffer< float >& outputBuffer, int startSample, int numSamples)
{
    if (!isVoiceActive())
    {
        return;
    }
    //the set size and addfrom in this function make the plugin functionally monophonic
    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);


    synthBuffer.clear();

    osc.processBlock(synthBuffer);
    filter.processBlock(synthBuffer);
    adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());
    synthBuffer.applyGain(0, synthBuffer.getNumSamples(), gain);

    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
    {
        outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0 , numSamples);

        if (! adsr.isActive())
        {
            clearCurrentNote();
        }
    }
}
 
