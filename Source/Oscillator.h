/*
  ==============================================================================

    Oscillator.h
    Created: 20 Dec 2021 4:24:41pm
    Author:  Dylan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#define _USE_MATH_DEFINES //annoyingly necessary for microsoft
#include <math.h>

class Oscillator {
public:

    void updateFrequency(float frequency);
    void updateSamplerate(float sampleRate);
    void reset();
    float processSample();
    void processBlock(juce::AudioBuffer< float >& buffer);

private:
    float deltaPhase;
    float currentPhase;
    float frequency;
    float sampleRate;
    bool fundamentalType;
    float fundementalGain;
    float subGain;
    void updateDelta() {
        deltaPhase = frequency / (sampleRate * 2.0f);
    }
};