/*
  ==============================================================================

    Oscillator.h
    Created: 20 Dec 2021 4:24:41pm
    Author:  Dylan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
//so far, don't need these but keeping for now as they could become necessary at any time
//#define USE_MATH_DEFINES //annoyingly necessary for microsoft
//#include <math.h>

class Oscillator {
public:

    void updateFrequency(float frequency);
    void updateSamplerate(float sampleRate);
    void reset();
    float processSample();
    void processBlock(juce::AudioBuffer< float >& buffer);
    void updateControls(bool fundamentalType, float fundamentalGain, float sawGain, float subGain);

private:
    float deltaPhase;
    float currentPhase;
    float subWave = 1.0f;
    float frequency;
    float sampleRate;
    bool fundamentalType = true;
    float fundamentalGain = 1.0f;
    float sawGain = 0.0f;
    float subGain = 0.0f;
    void updateDelta() {
        deltaPhase = frequency / (sampleRate * 2.0f);
    }
};