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


    setSliderParams(keyboardTrackingSlider);
    setSliderParams(cutoffSlider);
    setSliderParams(resonanceSlider);
}

filterComponent::~filterComponent()
{
}

void filterComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
}

void filterComponent::resized()
{
    auto bounds = getLocalBounds().reduced(10);
    auto padding = 10;
    auto numSliders = 3;
    auto sliderWidth = bounds.getWidth() / numSliders - padding;
    auto sliderHeight = bounds.getHeight();
    auto sliderStartX = padding;
    auto sliderStartY = 0;

    keyboardTrackingSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    cutoffSlider.setBounds(keyboardTrackingSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    resonanceSlider.setBounds(cutoffSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
}

void filterComponent::setSliderParams(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);

    addAndMakeVisible(slider);
}

