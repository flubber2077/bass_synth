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
    void reset();
    void advanceFilter(float &sample);
    void advanceFilter(float &sample, int channel);
    void updateSampleRate(float sampleRate);
    void updateCutoff(float frequency);
    void processBlock(juce::AudioBuffer< float >& buffer);

private:
    void updateCutoff();
    float cutoffFrequency;
    float trueCutoff;
    float keyboardTracking;
    float state1;
    float sampleTime;
    float avg;

    std::vector<float> state;
};

