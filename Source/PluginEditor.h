/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

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

    void setSliderParams(juce::Slider& slider);

    juce::Slider attackSlider;

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    std::unique_ptr<SliderAttachment> attackAttachment;


    BasssynthAudioProcessor& audioProcessor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BasssynthAudioProcessorEditor)
};
