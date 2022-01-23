/*
  ==============================================================================

    filter.h
    Created: 19 Jan 2022 12:35:36pm
    Author:  Dylan

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <cmath>
#define _USE_MATH_DEFINES //annoyingly necessary for microsoft
#include <math.h>
//Zavalishin's 1 pole lowpass filter (direct form II trapezoidal filter)

class filter
{
public:
    void prepareToPlay(int numChannels, float sampleRate);
    void reset();
    void processSample(float &sample);
    float advanceFilter(float sample);
    void processSample(float &sample, int channel);
    void updateSampleRate(float sampleRate);
    void updateCutoff(float frequency);
    void processBlock(juce::AudioBuffer< float >& buffer);

private:
    void updateCutoff();
    float cutoffFrequency;
    float cutoffCoeff;
    float keyboardTracking;
    float sampleTime;
    float avg;

    std::vector<float> state;
};

