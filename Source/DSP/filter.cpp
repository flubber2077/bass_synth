/*
  ==============================================================================

    filter.cpp
    Created: 19 Jan 2022 12:35:36pm
    Author:  Dylan

  ==============================================================================
*/

#include "filter.h"

void filter::prepareToPlay(int numChannels, float sampleRate)
{
    updateSampleRate(sampleRate);
    state.resize(numChannels);
    reset();
}


void filter::reset()
{
    avg = 0.0f;
    cutoffFrequency = 300.0f;
    updateCutoff();
}

void filter::advanceFilter(float &sample)
{
    float input = (sample - avg) * trueCutoff;
    sample = input + avg;
    avg = sample + input;
}

void filter::advanceFilter(float &sample, int channel)
{
    float input = (sample - state[channel]) * trueCutoff;
    sample = input + state[channel];
    state[channel] = sample + input;
}

void filter::updateSampleRate(float sampleRate)
{
    sampleTime = 1.0f / sampleRate;
    updateCutoff();
}

void filter::updateCutoff(float frequency)
{
    frequency = cutoffFrequency;
    updateCutoff();
}

void filter::processBlock(juce::AudioBuffer< float >& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        float* bufferPointer = buffer.getWritePointer(channel);
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            advanceFilter(bufferPointer[sample], channel);
        }
    }
}

void filter::updateCutoff()
{
    float cutoffDigital = 2.0f * M_PI * cutoffFrequency;
    float cutoffAnalog = (2.0f / sampleTime) * tan(cutoffDigital * sampleTime / 2.0f);
    float g = (cutoffAnalog * sampleTime) / 2.0f;
    trueCutoff = g / (1.0f + g);
}