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
    //do i just override this code when i build more complex oscillators? its not a ton of code but that seems kind of wise. or maybe just build a simpler processPhase function that other stuff can use? who is to say.
    currentPhase += deltaPhase;
    if (currentPhase > 1.0f)
    {currentPhase-= 1.0f;}
    /*returns a cubic approximation of sine, appropriate from 0-1.
     a piece-wise quadratic approximation has less harmonics weirdly, but this may sound better.
     trying out avoiding true sine waves, i dont think they are interesting or sound good.
     this will eventually be replaced/bolstered by more robust waveshaping
     this has the harmonic series of sin(nx)/n^3, as if it was the second interpolation of a saw, the way a triangle is the first interpolation of a square.*/
    
    return 20.784f * currentPhase * (currentPhase - .5f) * (currentPhase - 1.0f);
}
