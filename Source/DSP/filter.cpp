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

void filter::processSample(float &sample)
{
    float input = (sample - avg) * cutoffCoeff;
    sample = input + avg;
    avg = sample + input;
}

float filter::advanceFilter(float sample)
{
    float input = (sample - avg) * cutoffCoeff;
    float output = input + avg;
    avg = output + input;
    return output;
}

void filter::processSample(float &sample, int channel)
{
    float input = (sample - state[channel]) * cutoffCoeff;
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
    cutoffFrequency = frequency;
    updateCutoff();
    void updateTimeConstant(float seconds);
}

void filter::updateTimeConstant(float seconds)
{
    cutoffFrequency = 1.0f/(2.0f * M_PI * seconds);
    updateCutoff();
}

void filter::processBlock(juce::AudioBuffer< float >& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        float* bufferPointer = buffer.getWritePointer(channel);
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            processSample(bufferPointer[sample], channel);
        }
    }
}

void filter::updateCutoff()
{
    //i am praying that compiling takes care of this. There is a lot of cleanup that could happen here
    //but then the variables would have a lot less meaning
    float wd = 2.0f * M_PI * cutoffFrequency;
    float prewarpCutoff = (2.0f / sampleTime) * tan(wd * sampleTime / 2.0f);
    float g = prewarpCutoff * sampleTime / 2.0f;
    cutoffCoeff = g / (1.0f + g);
}
