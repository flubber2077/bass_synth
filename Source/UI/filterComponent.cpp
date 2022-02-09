/*
  ==============================================================================

    filterComponent.cpp
    Created: 19 Jan 2022 2:10:53pm
    Author:  Dylan

  ==============================================================================
*/

#include <JuceHeader.h>
#include "filterComponent.h"

//==============================================================================
filterComponent::filterComponent(juce::AudioProcessorValueTreeState& apvts)
{
    keyboardTrackingAttachment = std::make_unique<SliderAttachment>(apvts, "KEYBOARDTRACKING", keyboardTrackingSlider);
    cutoffAttachment = std::make_unique<SliderAttachment>(apvts, "CUTOFF", cutoffSlider);
    resonanceAttachment = std::make_unique<SliderAttachment>(apvts, "RESONANCE", resonanceSlider);
    filterEnvAttachment = std::make_unique<SliderAttachment>(apvts, "FILTERENV", filterEnvSlider);


    setSliderParams(keyboardTrackingSlider);
    setSliderParams(cutoffSlider);
    setSliderParams(resonanceSlider);
    setSliderParams(filterEnvSlider);
}

filterComponent::~filterComponent()
{
}

void filterComponent::paint (juce::Graphics& g)
{
    auto box = getLocalBounds();
    box = box.withTop(box.getBottom() - 40);

    const auto width = box.getWidth() / numSliders;

    g.setColour(juce::Colours::white);
    g.setFont(16);

    g.drawFittedText(TRANS("KBD->Filter"), box.removeFromLeft(width), juce::Justification::centred, 1);
    g.drawFittedText(TRANS("Env Amt"), box.removeFromLeft(width), juce::Justification::centred, 1);
    g.drawFittedText(TRANS("Cutoff"), box.removeFromLeft(width), juce::Justification::centred, 1);
    g.drawFittedText(TRANS("Resonance"), box.removeFromLeft(width), juce::Justification::centred, 1);
}

void filterComponent::resized()
{
    auto box = getLocalBounds();
    box.removeFromBottom(40);
    //box.removeFromBottom(5);

    const int width = box.getWidth() / numSliders;
    const int padding = 5;

    filterEnvSlider.setBounds(box.removeFromLeft(width).reduced(padding));
    keyboardTrackingSlider.setBounds(box.removeFromLeft(width).reduced(padding));
    cutoffSlider.setBounds(box.removeFromLeft(width).reduced(padding));
    resonanceSlider.setBounds(box.removeFromLeft(width).reduced(padding));
}

void filterComponent::setSliderParams(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);

    addAndMakeVisible(slider);
}

