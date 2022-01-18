/*
  ==============================================================================

    OscComponent.cpp
    Created: 17 Jan 2022 6:20:09pm
    Author:  Dylan

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscComponent.h"

//==============================================================================
OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts)
{
    fundGainAttachment = std::make_unique<SliderAttachment>(apvts, "FUNDGAIN", fundGainSlider);

    setSliderParams(fundGainSlider);
}

OscComponent::~OscComponent()
{
}

void OscComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
}

void OscComponent::resized()
{
    auto bounds = getLocalBounds().reduced(10);
    auto padding = 10;
    auto numSliders = 1;
    auto sliderWidth = bounds.getWidth() / numSliders - padding;
    auto sliderHeight = bounds.getHeight() - (padding / 2);
    auto sliderStartX = padding;
    auto sliderStartY = bounds.getHeight() / 2 - ((sliderHeight - padding) / 2);

    fundGainSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
}

void OscComponent::setSliderParams(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);

    addAndMakeVisible(slider);
}
