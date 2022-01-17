/*
  ==============================================================================

    ADSRdata.cpp
    Created: 16 Jan 2022 9:59:13pm
    Author:  Dylan

  ==============================================================================
*/

#include "ADSRdata.h"

void adsrData::updateADSR(float attack, float decay, float sustain, float release)
{
    adsrParameters.attack = attack;
    adsrParameters.decay = decay;
    adsrParameters.sustain = sustain;
    adsrParameters.release = release;
    setParameters(adsrParameters);
}