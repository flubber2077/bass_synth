/*
  ==============================================================================

    ADSRdata.h
    Created: 16 Jan 2022 9:59:13pm
    Author:  Dylan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class adsrData : public juce::ADSR
{
public:
    void updateADSR(float attack, float decay, float sustain, float release);

private:
    juce::ADSR::Parameters adsrParameters;
};