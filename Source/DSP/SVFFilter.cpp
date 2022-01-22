/*
  ==============================================================================

    SVFFilter.cpp
    Created: 22 Jan 2022 12:56:41pm
    Author:  Dylan

  ==============================================================================
*/
#include "SVFFilter.h"

void SVFFilter::prepareToPlay(int numChannels, float sampleRate)
{
    updateSampleRate(sampleRate);
    state1.resize(numChannels);
    state2.resize(numChannels);
    reset();
}

void SVFFilter::reset()
{
    avg1 = 0.0f;
    avg2 = 0.0f;
    cutoffFrequency = 300.0f;
    updateResonance(1.0f);
    updateCutoff();
}

void SVFFilter::processSample(float& sample)
{
    float bandPass = (trueCutoff * (sample - avg2) + avg1)* damping;
    float v1 = bandPass - avg1;
    avg1 = bandPass + v1;
    float v2 = trueCutoff * bandPass;
    sample = v2 + avg2;
    avg2 = sample + avg2;
}

float SVFFilter::advanceFilter(float sample)
{
    float bandPass = (trueCutoff * (sample - avg2) + avg1) * damping;
    float v1 = bandPass - avg1;
    avg1 = bandPass + v1;
    float v2 = trueCutoff * bandPass;
    sample = v2 + avg2;
    avg2 = sample + avg2;
    return sample;
}

void SVFFilter::processSample(float& sample, int channel)
{
    float bandPass = (trueCutoff * (sample - state2[channel]) + state1[channel]) * damping;
    float v1 = bandPass - state1[channel];
    state1[channel] = bandPass + v1;
    float v2 = trueCutoff * bandPass;
    sample = v2 + state2[channel];
    avg2 = sample + state2[channel];
}

void SVFFilter::updateSampleRate(float sampleRate)
{
    sampleTime = 1.0f / sampleRate;
    updateCutoff();
}

void SVFFilter::updateCutoff(float frequency)
{
    cutoffFrequency = frequency;
    updateCutoff();
    updateResonance();
}

void SVFFilter::updateResonance(float resonance)
{
    SVFFilter::damping = resonance;
    updateResonance();
}

void SVFFilter::processBlock(juce::AudioBuffer< float >& buffer)
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

void SVFFilter::updateCutoff()
{
        float cutoffDigital = 2.0f * M_PI * cutoffFrequency;
        float cutoffAnalog = (2.0f / sampleTime) * tan(cutoffDigital * sampleTime / 2.0f);
        float g = (cutoffAnalog * sampleTime) / 2.0f;
        trueCutoff = g / (1.0f + g);
}

void SVFFilter::updateResonance()
{
    trueDamping = 1.0f / (1.0f + 2.0f * damping * trueCutoff + trueCutoff * trueCutoff);
}