/*
  ==============================================================================

    saturation.cpp
    Created: 26 Jan 2022 10:20:07am
    Author:  Dylan Jordan

  ==============================================================================
*/

#include "saturation.h"

void Saturation::processSample(float& sample)
{
    //finding out an appropriate function may be kind of hellish and tedious. might also want to just group them all here and comment them out.
    //using for now as it should be much faster than other functions, as well as having a soft knee before I have some anti-aliasing scheme
    //sample = sample/(1+fabsf(sample));
    if (fabsf(sample) < 1.0f)
    {
        sample = 0.5f *(3.0f * sample - sample * sample * sample);
    } else {
        sample = copysignf(1.0f, sample);
    }
}

void Saturation::processBlock(juce::AudioBuffer< float >& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        float* bufferPointer = buffer.getWritePointer(channel);
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            processSample(bufferPointer[sample]);
        }
    }
}
