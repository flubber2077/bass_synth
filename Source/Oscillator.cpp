/*
  ==============================================================================

    Oscillator.cpp
    Created: 20 Dec 2021 4:24:41pm
    Author:  Dylan

  ==============================================================================
*/

#include "Oscillator.h"

void Oscillator::updateFrequency(float frequency)
{
    Oscillator::frequency = frequency;
}

void Oscillator::updateSamplerate(float sampleRate)
{
    Oscillator::sampleRate = sampleRate;
}

void Oscillator::reset()
{
    deltaPhase = 0;
    currentPhase = 0;
}

float Oscillator::processSample()
{
    return 0.f;
}