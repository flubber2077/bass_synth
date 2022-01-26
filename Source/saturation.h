/*
  ==============================================================================

    saturation.h
    Created: 26 Jan 2022 10:20:07am
    Author:  Dylan Jordan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <cmath>

class Saturation
{
public:
    void processSample(float& sample);
    void processBlock(juce::AudioBuffer< float >& buffer);
    
};
