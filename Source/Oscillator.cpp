/*
  ==============================================================================

    Oscillator.cpp
    Created: 20 Dec 2021 4:24:41pm
    Author:  Dylan

  ==============================================================================
*/

#include "Oscillator.h"
#include <JuceHeader.h>
void Oscillator::updateFrequency(float frequency)
{
    Oscillator::frequency = frequency;
    updateDelta();
}

void Oscillator::updateSamplerate(float sampleRate)
{
    Oscillator::sampleRate = sampleRate;
    updateDelta();
}

void Oscillator::reset()
{
    deltaPhase = 0;
    currentPhase = 0;
    subWave = 1.0f;
}


float Oscillator::processSample()
{
    currentPhase += deltaPhase;
    float sawWave = 2.0f * currentPhase - 1.0f;
    float subOut = subWave;

    if (currentPhase > 1.0f)
    {
        currentPhase -= 1.0f;
        subWave = -subWave;
        subOut = subWave;
        sawWave -= 2.0f;

        //polyBlep implementation
        float t = currentPhase / deltaPhase;
        float polyBlep = t + t - t * t - 1.0f;
        sawWave -= polyBlep;
        subOut *= 1.0f + polyBlep;
    }
    else if (currentPhase > 1.0f - deltaPhase) {
        float t = (currentPhase - 1.0f) / deltaPhase;
        float polyBlep = t * t + t + t + 1.0f;
        sawWave -= polyBlep;
        subOut *= 1.0f - polyBlep;
    }

    float fundamentalWave = fundamental(currentPhase);

    return (fundamentalWave * fundamentalGain) + (subOut * subGain) + (sawWave * sawGain);
}

void Oscillator::processBlock(juce::AudioBuffer< float >& buffer)
{
    float* bufferPointer = buffer.getWritePointer(0);
    for (int sample = 0; sample < buffer.getNumSamples(); sample++)
    {
        bufferPointer[sample] = processSample();
    }

    for (int channel = 1; channel < buffer.getNumChannels(); channel++)
    {
        buffer.addFrom(channel, 0, buffer, 0, 0, buffer.getNumSamples());
    }
}

void Oscillator::updateControls(bool waveType, float fundGain, float sawOscGain, float subOscGain)
{
    fundamentalType = waveType;
    fundamentalGain = fundGain;
    sawGain = sawOscGain;
    subGain = subOscGain;
}

float Oscillator::fundamental(float phase)
{
    /*returns an approximation of sine from 0-1. Contains a pleasant amount of harmonics*/
    if (fundamentalType == 0)
    {
        //return -20.784f * phase * (phase - .5f) * (phase - 1.0f);
        return 22.555f * phase * (phase + 0.5f) * (phase - 0.5f) * (phase - 1.0f) * (phase - 1.5f);
    } else {
        if (phase < .5f)
        {
            return 16.0f * phase * (phase - 0.5f);
        }
        else
        {
            return -16.0f * (phase - 0.5f) * (phase - 1.0f);
        }
    }
}
