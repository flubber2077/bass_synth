/*
  ==============================================================================

    saturation.cpp
    Created: 26 Jan 2022 10:20:07am
    Author:  Dylan Jordan

  ==============================================================================
*/

#include "saturation.h"

void Saturation::prepareToPlay(int numChannels)
{
    lastSample.resize(numChannels);
    lastAntiderivative.resize(numChannels);
}

void Saturation::processSample(float& sample, int channel)
{
    float currentAntiderivative = antiderivativeFunction(sample);
    float output = (currentAntiderivative - lastAntiderivative[channel]) / (sample - lastSample[channel]);
    lastAntiderivative[channel] = currentAntiderivative;
    lastSample[channel] = sample;
    sample = output;
}

void Saturation::processBlock(juce::AudioBuffer< float >& buffer)
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

float Saturation::antiderivativeFunction(float sample)
{
    return (logf(coshf(sample))); //antiderivative of tan(x)
    //transcendentals are not exactly efficient functions
    //but look how clean this is and how I can just move on with my life
}

//finding out an appropriate function may be kind of hellish and tedious. might also want to just group them all here and comment them out.

//tan(x)

//sample = sample/(1+fabsf(sample));

/*if (fabsf(sample) < 1.0f)
 {
 sample = 0.5f *(3.0f * sample - sample * sample * sample);
 } else {
 sample = copysignf(1.0f, sample);
 }*/
