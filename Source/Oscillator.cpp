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
}


float Oscillator::processSample()
{
    currentPhase += deltaPhase;
    if (currentPhase > 1.0f)
    {
        currentPhase-= 1.0f;
        subWave = -subWave;
    }
    /*returns an approximation of sine from 0-1.
     Either a cubic approximation with sin(nx)/x^3, like a second interpolation of saw
     or a piecwise quadratic approximation with similar spectral response, but only odd harmonics*/
    float fundamentalWave;
    switch (fundamentalType) {
    case 0:
        fundamentalWave = 20.784f * currentPhase * (currentPhase - .5f) * (currentPhase - 1.0f);
        break;
    case 1:
        if (currentPhase < .5f)
        {
            fundamentalWave = -16.0f * currentPhase * (currentPhase - 0.5f);
        }
        else
        {
            fundamentalWave = 16.0f * (currentPhase - 0.5f) * (currentPhase - 1.0f);
        }
        break;
    }

    return (fundamentalWave * fundamentalGain) + (subWave * subGain);
}

void Oscillator::processBlock(juce::AudioBuffer< float >& buffer)
{
    float* bufferPointerL = buffer.getWritePointer(0);
    float* bufferPointerR = buffer.getWritePointer(1);
    for (int sample = 0; sample< buffer.getNumSamples(); sample++)
    {
        bufferPointerL[sample] = processSample();
        bufferPointerR[sample] = bufferPointerL[sample];
    }
}

void Oscillator::updateControls(bool waveType, float fundGain, float subOscGain)
{
    fundamentalType = waveType;
    fundamentalGain = fundGain;
    subGain = subOscGain;
}
