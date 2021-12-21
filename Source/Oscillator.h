/*
  ==============================================================================

    Oscillator.h
    Created: 20 Dec 2021 4:24:41pm
    Author:  Dylan

  ==============================================================================
*/

#pragma once

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
    //there should probably be a 2 or pi in this equation somewhere but im going to figure that out empirically when its out of tune and two octaves out :°)
    void updateDelta() { deltaPhase = frequency/ sampleRate; }
};
