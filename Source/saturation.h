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
    void prepareToPlay(int channel);
    void processSample(float& sample, int channel);
    void processBlock(juce::AudioBuffer< float >& buffer);
    
    float antiderivativeFunction(float sample);
    
private:
    std::vector<float> lastSample;
    std::vector<float> lastAntiderivative;
};
