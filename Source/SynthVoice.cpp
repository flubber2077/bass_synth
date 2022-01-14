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

    if (!allowTailOff || !adsr.isActive())
    {
        clearCurrentNote();
    }
}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{

}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{

}

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    osc.reset();
    adsr.setSampleRate(sampleRate);
    osc.updateSamplerate(sampleRate);
    adsr.setParameters(adsrParameters);
}

void SynthVoice::renderNextBlock(juce::AudioBuffer< float >& outputBuffer, int startSample, int numSamples)
{
    if (!isVoiceActive())
    {
        return;
    }
    //the set size and addfrom in this function make the plugin functionally monophonic
    synthBuffer.setSize(1, numSamples, false, false, true);
    synthBuffer.clear();

    osc.processBlock(synthBuffer);
    adsr.applyEnvelopeToBuffer(synthBuffer, startSample, numSamples);
    synthBuffer.applyGain(startSample, numSamples, .2f);

    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
    {
        outputBuffer.addFrom(channel, startSample, synthBuffer, 1, 0, numSamples);

        if (!adsr.isActive())
        {
            clearCurrentNote();
        }
    }
}
 
