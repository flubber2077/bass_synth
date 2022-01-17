/*
  ==============================================================================

    ADSRdata.cpp
    Created: 16 Jan 2022 9:59:13pm
    Author:  Dylan

  ==============================================================================
*/

#include "ADSRdata.h"

void adsrData::updateADSR(float attack)
{
    adsrParameters.attack = attack;
    setParameters(adsrParameters);
}