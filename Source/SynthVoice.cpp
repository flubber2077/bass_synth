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
    updatePitchbend(currentPitchWheelPosition);
    targetFrequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    currentFrequency = pitchbendRatio * glideFilter.advanceFilter(targetFrequency);
    
    osc.updateFrequency(currentFrequency * pitchbendRatio);
    updateTrackingRatio();
    svfFilter.updateCutoff(cutoff * trackingRatio * pitchbendRatio);
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
    updatePitchbend(newPitchWheelValue);
    osc.updateFrequency(currentFrequency * pitchbendRatio);
    svfFilter.updateCutoff(cutoff * trackingRatio * pitchbendRatio);
}

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels)
{
    osc.reset();
    adsr.setSampleRate(sampleRate);
    osc.updateSamplerate(sampleRate);
    glideFilter.prepareToPlay(0, sampleRate/samplesPerBlock);
    svfFilter.prepareToPlay(numChannels, sampleRate);
}

void SynthVoice::update(const float glide, const float fundType, const float fundGain, const float sawGain, const float subGain, const float keyboardTracking, const float cutoffFreq, const float resonance, const float attack, const float decay, const float sustain, const float release, const float volume)
{
    glideFilter.updateCutoff(glide);
    SynthVoice::keyboardTracking = keyboardTracking;
    SynthVoice::cutoff = cutoffFreq;
    currentFrequency = glideFilter.advanceFilter(targetFrequency);
    updateTrackingRatio();

    adsr.updateADSR(attack, decay, sustain, release);
    gain = volume;
    svfFilter.updateCutoff(cutoffFreq * trackingRatio);
    svfFilter.updateResonance(resonance);
    osc.updateControls(fundType, fundGain, sawGain, subGain);
    osc.updateFrequency(currentFrequency);
}

void SynthVoice::renderNextBlock(juce::AudioBuffer< float >& outputBuffer, int startSample, int numSamples)
{
    if (!isVoiceActive())
    {
        return;
    }
    
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
 
void SynthVoice::updatePitchbend(int pitchwheelPosition)
{
    //using math.h, if replaced, delete math.h probably
    //converts pitchWheel to cents, range -200 to 200
    int bendRange = 200; //in cents
    //input is a 14 bit number, as per MIDI spec
    float centBend = (pitchwheelPosition - 8192) * bendRange / 8192.0f; //8192 is halfway of the 14 bit number supplied
    //returns the needed ratio change, i.e. 1200 cents = 1 octave, returns 2 for twice the frequency
    pitchbendRatio = powf(2.0f, (centBend / 1200.0f));
}

void SynthVoice::updateTrackingRatio()
{
    float referenceFrequency = 300.0f; //pivot point of tracking, should be made variable later
    trackingRatio = (keyboardTracking * currentFrequency / referenceFrequency) + 1.0f -keyboardTracking;
}
