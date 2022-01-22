/*
  ==============================================================================

    SynthVoice.h
    Created: 17 Dec 2021 8:49:58pm
    Author:  Dylan

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"
#include "Oscillator.h"
#include "ADSRdata.h"
#include "DSP/filter.h"
#include "DSP/SVFFilter.h"
#include <math.h>

class SynthVoice : public juce::SynthesiserVoice
{
public:
	bool canPlaySound(juce::SynthesiserSound* sound) override;
	void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
	void stopNote(float velocity, bool allowTailOff) override;
	void controllerMoved(int controllerNumber, int newControllerValue) override;
	void pitchWheelMoved(int newPitchWheelValue) override;
	void prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels);
	void update(const float glide, const float fundType, const float fundGain, const float sawGain, const float subGain, const float cutoffFreq, const float attack, const float decay, const float sustain, const float release, const float volume);
	void renderNextBlock(juce::AudioBuffer< float >& outputBuffer, int startSample, int numSamples) override;
	 
private:
	float calculatePitchbend(int pitchwheelPosition);

	float gain;
	adsrData adsr;
	juce::AudioBuffer<float> synthBuffer;
	filter filter;
	SVFFilter svfFilter;
	Oscillator osc;

}; 
