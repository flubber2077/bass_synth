/*
  ==============================================================================

    ADSRComponent.cpp
    Created: 16 Jan 2022 9:58:53pm
    Author:  Dylan

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ADSRComponent.h"

//==============================================================================
ADSRComponent::ADSRComponent(juce::AudioProcessorValueTreeState& apvts)
{
    attackAttachment = std::make_unique<SliderAttachment>(apvts, "ATTACK", attackSlider);
    decayAttachment = std::make_unique<SliderAttachment>(apvts, "DECAY", decaySlider);
    sustainAttachment = std::make_unique<SliderAttachment>(apvts, "SUSTAIN", sustainSlider);
    releaseAttachment = std::make_unique<SliderAttachment>(apvts, "RELEASE", releaseSlider);
    gainAttachment = std::make_unique<SliderAttachment>(apvts, "GAIN", gainSlider);

    setSliderParams(attackSlider);
    setSliderParams(decaySlider);
    setSliderParams(sustainSlider);
    setSliderParams(releaseSlider);
    setSliderParams(gainSlider);
    gainSlider.setColour(juce::Slider::thumbColourId, juce::Colours::whitesmoke);

}

ADSRComponent::~ADSRComponent()
{
}

void ADSRComponent::paint (juce::Graphics& g)
{
    auto box = getLocalBounds();
    box = box.withTop(box.getBottom() - 40);

    const auto width = box.getWidth() / numSliders;
    
    g.setColour(juce::Colours::white);
    g.setFont(16);

    g.drawFittedText(TRANS("Attack"), box.removeFromLeft(width), juce::Justification::centred, 1);
    g.drawFittedText(TRANS("Decay"), box.removeFromLeft(width), juce::Justification::centred, 1);
    g.drawFittedText(TRANS("Sustain"), box.removeFromLeft(width), juce::Justification::centred, 1);
    g.drawFittedText(TRANS("Release"), box.removeFromLeft(width), juce::Justification::centred, 1);
    g.drawFittedText(TRANS("Volume"), box.removeFromLeft(width), juce::Justification::centred, 1);
}

void ADSRComponent::resized()
{
    auto box = getLocalBounds();
    box.removeFromBottom(40);
    //box.removeFromBottom(5);

    const int width = box.getWidth() / numSliders;
    const int padding = 5;

    attackSlider.setBounds(box.removeFromLeft (width).reduced (padding));
    decaySlider.setBounds(box.removeFromLeft(width).reduced(padding));
    sustainSlider.setBounds(box.removeFromLeft(width).reduced(padding));
    releaseSlider.setBounds(box.removeFromLeft(width).reduced(padding));
    gainSlider.setBounds(box.removeFromLeft(width).reduced(padding));
}

void ADSRComponent::setSliderParams(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    slider.setColour(juce::Slider::thumbColourId, juce::Colours::mediumslateblue);

    addAndMakeVisible(slider);
}