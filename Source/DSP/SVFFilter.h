/*
  ==============================================================================

    SVFFilter.h
    Created: 22 Jan 2022 12:56:41pm
    Author:  Dylan

  ==============================================================================
*/

#pragma once

#pragma once

#include <JuceHeader.h>
#include <cmath>
#define _USE_MATH_DEFINES //annoyingly necessary for microsoft
#include <math.h>
//Zavalishin's 1 pole lowpass filter (direct form II trapezoidal filter)

class SVFFilter
{
public:
    void prepareToPlay(int numChannels, float sampleRate);
    void reset();
    void processSample(float& sample);
    float advanceFilter(float sample);
    void processSample(float& sample, int channel);
    void updateSampleRate(float sampleRate);
    void updateCutoff(float frequency);
    void updateResonance(float resonance);
    void processBlock(juce::AudioBuffer< float >& buffer);

private:
    void updateCutoff();
    void updateDamping();
    float cutoffFrequency;
    float trueCutoff;
    float damping; //oscillates at 0, do not allow to become 0 unless clipping is implemented
    float trueDamping;
    float keyboardTracking;
    float sampleTime;
    float avg1;
    float avg2;

    //could make this into a single 2d vector, but i think that would be harder to read and not necessarily any faster
    std::vector<float> state1;
    std::vector<float> state2;
};

