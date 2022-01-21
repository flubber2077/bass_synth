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
    sawGainAttachment = std::make_unique<SliderAttachment>(apvts, "SAWGAIN", sawGainSlider);
    subGainAttachment = std::make_unique<SliderAttachment>(apvts, "SUBGAIN", subGainSlider);
    waveshapeAttachment = std::make_unique< juce::AudioProcessorValueTreeState::ButtonAttachment>(apvts, "FWAVESHAPE", waveshapeButton);

    setSliderParams(fundGainSlider);
    setSliderParams(sawGainSlider);
    setSliderParams(subGainSlider);

    addAndMakeVisible(waveshapeButton);
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
    auto sliderHeight = bounds.getHeight() * 9/10;
    auto sliderStartX = padding;
    auto sliderStartY = 0;

    fundGainSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    sawGainSlider.setBounds(fundGainSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    subGainSlider.setBounds(sawGainSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    waveshapeButton.setBounds(sliderStartX+(sliderWidth/2)-12, sliderStartY +  sliderHeight + padding, 25, 25);
}

void OscComponent::setSliderParams(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    slider.setColour(juce::Slider::thumbColourId, juce::Colours::mediumseagreen);

    addAndMakeVisible(slider);
}
