/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BasssynthAudioProcessorEditor::BasssynthAudioProcessorEditor (BasssynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), osc(audioProcessor.apvts), adsr (audioProcessor.apvts), filter( audioProcessor.apvts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 300);

    addAndMakeVisible(adsr);
    addAndMakeVisible(osc);
    addAndMakeVisible(filter);
}

BasssynthAudioProcessorEditor::~BasssynthAudioProcessorEditor()
{
}

//==============================================================================
void BasssynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("gnarly", getLocalBounds(), juce::Justification::centred, 1);
}

void BasssynthAudioProcessorEditor::resized()
{
    int width = getWidth();
    int height = getHeight();
    adsr.setBounds(width / 2, 0 , width / 2, height);
    osc.setBounds(0, 0, width / 2, height / 2);
    filter.setBounds(0, height / 2, width / 2, height / 2);
}
