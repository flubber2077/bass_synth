/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/ADSRComponent.h"

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
    ADSRComponent adsr;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BasssynthAudioProcessorEditor)
};
