/*
  ==============================================================================

    OscComponent.h
    Created: 17 Jan 2022 6:20:09pm
    Author:  Dylan

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class OscComponent  : public juce::Component
{
public:
    OscComponent(juce::AudioProcessorValueTreeState& apvts);
    ~OscComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    void setSliderParams(juce::Slider& slider);
    void updateThumb(juce::Slider& slider);

    juce::Slider glideSlider;
    juce::Slider fundGainSlider;
    juce::Slider sawGainSlider;
    juce::Slider subGainSlider;
    
    juce::ToggleButton waveshapeButton;

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    std::unique_ptr<SliderAttachment> glideAttachment;
    std::unique_ptr<SliderAttachment> fundGainAttachment;
    std::unique_ptr<SliderAttachment> sawGainAttachment;
    std::unique_ptr<SliderAttachment> subGainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> waveshapeAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)
};
