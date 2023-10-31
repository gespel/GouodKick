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

using namespace juce;
class GouodKickAudioProcessorEditor  : public juce::AudioProcessorEditor,public Slider::Listener
{
public:
    GouodKickAudioProcessorEditor (GouodKickAudioProcessor&);
    ~GouodKickAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    juce::Slider highGainSlider;
    juce::Slider lowGainSlider;

    juce::Slider highFrequencySlider;
    juce::Slider lowFrequencySlider;
    
    juce::Slider volume;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    GouodKickAudioProcessor& audioProcessor;

    void sliderValueChanged(juce::Slider* slider) override;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GouodKickAudioProcessorEditor)

};


