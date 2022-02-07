/*
  ==============================================================================

    Oscillator.h
    Created: 20 Dec 2021 4:24:41pm
    Author:  Dylan

  ==============================================================================
*/

#pragma once

//A simple Numerically Controlled Oscillator, that natively mixes various waveshapes.

class Oscillator {
public:

    void updateFrequency(float frequency);
    void updateSamplerate(float sampleRate);
    void reset();
    float processSample();
    float fundamental(float phase);
    void processBlock(float* bufferPointer, int numSamples);
    void updateControls(bool fundamentalType, float fundamentalGain, float sawGain, float subGain);

private:
    float deltaPhase;
    float currentPhase;
    float subWave = 1.0f;
    float frequency;
    float sampleRate;
    bool fundamentalType;
    float fundamentalGain;
    float sawGain;
    float subGain;
    void updateDelta() { deltaPhase = frequency / sampleRate; }
};
