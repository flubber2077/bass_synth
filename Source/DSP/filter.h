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

//Zavalishin's 1 pole lowpass filter (direct form II trapezoidal filter) from VA Filter Design

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
    void updateTimeConstant(float seconds);
    void processBlock(juce::AudioBuffer< float >& buffer);

private:
    float twoPi = 6.28318530718f;
    void updateCutoff();
    float cutoffFrequency;
    float cutoffCoeff;
    float keyboardTracking;
    float sampleTime;
    float avg;

    std::vector<float> state;
};

