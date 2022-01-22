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
    osc.updateFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber) * (calculatePitchbend(currentPitchWheelPosition)));
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
    osc.updateFrequency(juce::MidiMessage::getMidiNoteInHertz(getCurrentlyPlayingNote()) * calculatePitchbend(newPitchWheelValue));
}

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels)
{
    osc.reset();
    adsr.setSampleRate(sampleRate);
    osc.updateSamplerate(sampleRate);
    filter.prepareToPlay(numChannels, sampleRate);
    svfFilter.prepareToPlay(numChannels, sampleRate);
}

void SynthVoice::update(const float glide, const float fundType, const float fundGain, const float sawGain, const float subGain, const float cutoffFreq, const float attack, const float decay, const float sustain, const float release, const float volume)
{
    adsr.updateADSR(attack, decay, sustain, release);
    gain = volume;
    filter.updateCutoff(cutoffFreq);
    svfFilter.updateCutoff(cutoffFreq);
    osc.updateControls(fundType, fundGain, sawGain, subGain);
    osc.updateGlide(glide);
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
    svfFilter.processBlock(synthBuffer);
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
 
float SynthVoice::calculatePitchbend(int pitchwheelPosition)
{
    //using math.h, if replaced, delete math.h probably
    //converts pitchWheel to cents, range -200 to 200, change the constant to a variable if a user selectable variable is needed.
    float centBend = (pitchwheelPosition - 8192) * 200 / 8192.0f;
    //returns the needed ratio change, i.e. 1200 cents = 1 octave, returns 2 for twice the frequency
    return powf(2.0f, (centBend / 1200.0f));
}