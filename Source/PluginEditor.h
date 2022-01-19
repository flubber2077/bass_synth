/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/ADSRComponent.h"
#include "UI/OscComponent.h"
#include "UI/filterComponent.h"

//==============================================================================
/**
*/
class BasssynthAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    BasssynthAudioProcessorEditor (BasssynthAudioProcessor&);
    ~BasssynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    BasssynthAudioProcessor& audioProcessor;
    OscComponent osc;
    ADSRComponent adsr;
    filterComponent filter;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BasssynthAudioProcessorEditor)
};
