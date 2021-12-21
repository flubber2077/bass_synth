/*
  ==============================================================================

    Oscillator.h
    Created: 20 Dec 2021 4:24:41pm
    Author:  Dylan

  ==============================================================================
*/

#pragma once
#include <limits.h>

class Oscillator {
public:

    void updateFrequency(float frequency);
    void updateSamplerate(float sampleRate);
    void reset();
    float processSample();

private:

    unsigned int deltaPhase;
    unsigned int currentPhase;
    float frequency;
    float sampleRate;
    void updateDelta() { deltaPhase = frequency * UINT_MAX / sampleRate; }
};