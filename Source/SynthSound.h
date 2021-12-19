/*
  ==============================================================================

    SynthSound.h
    Created: 17 Dec 2021 8:50:09pm
    Author:  Dylan

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote(int midiNoteNumber) override { return true; }
    bool appliesToChannel(int midiChannel) override { return true; }
};