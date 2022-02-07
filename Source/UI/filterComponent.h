/*
  ==============================================================================

    filterComponent.h
    Created: 19 Jan 2022 2:10:53pm
    Author:  Dylan

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class filterComponent  : public juce::Component
{
public:
    filterComponent(juce::AudioProcessorValueTreeState& apvts);
    ~filterComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    void setSliderParams(juce::Slider& slider);

    juce::Slider keyboardTrackingSlider;
    juce::Slider cutoffSlider;
    juce::Slider resonanceSlider;
    juce::Slider filterEnvSlider;

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    std::unique_ptr<SliderAttachment> keyboardTrackingAttachment;
    std::unique_ptr<SliderAttachment> cutoffAttachment;
    std::unique_ptr<SliderAttachment> resonanceAttachment;
    std::unique_ptr<SliderAttachment> filterEnvAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (filterComponent)
};
