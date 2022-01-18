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
    subGainAttachment = std::make_unique<SliderAttachment>(apvts, "SUBGAIN", subGainSlider);
    sawGainAttachment = std::make_unique<SliderAttachment>(apvts, "SAWGAIN", sawGainSlider);

    setSliderParams(fundGainSlider);
    setSliderParams(subGainSlider);
    setSliderParams(sawGainSlider);
}

OscComponent::~OscComponent()
{
}

void OscComponent::paint (juce::Graphics& g)
{

}

void OscComponent::resized()
{
    auto bounds = getLocalBounds().reduced(10);
    auto padding = 10;
    auto numSliders = 3;
    auto sliderWidth = bounds.getWidth() / numSliders - padding;
    auto sliderHeight = bounds.getHeight() - (padding / 2);
    auto sliderStartX = padding;
    auto sliderStartY = bounds.getHeight() / 2 - ((sliderHeight - padding) / 2);

    fundGainSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    subGainSlider.setBounds(fundGainSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    sawGainSlider.setBounds(subGainSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
}

void OscComponent::setSliderParams(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);

    addAndMakeVisible(slider);
}
