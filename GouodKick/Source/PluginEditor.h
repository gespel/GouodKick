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


class GouodKickLookAndFeel : public juce::LookAndFeel_V4 {
public:
    GouodKickLookAndFeel()
    {
        setColour (juce::Slider::thumbColourId, juce::Colours::red);
    }
    void drawLinearSlider (Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, Slider::SliderStyle, Slider &) override {
        Image sliderKnob = ImageCache::getFromMemory (BinaryData::FADER_SHADOW_png, BinaryData::FADER_SHADOW_pngSize);
        float mid = height/2;
        //200 - 50 / 2 + 50 = 125
        //100 - 20 / 2 + 20 = 60 

        // 60 - 20 / 100 - 20
        if(mid < (sliderPos - minSliderPos)/(maxSliderPos - minSliderPos) * height) {
            g.setColour(juce::Colours::grey);
            g.fillRect(x + 20 * 1.0, y + (height/2) * 1.0, 10 * 1.0, (sliderPos - minSliderPos)/(maxSliderPos - minSliderPos) * height * 0.5f);
        }
        g.drawImageAt (sliderKnob.rescaled(sliderKnob.getWidth()/4, sliderKnob.getHeight()/4, Graphics::mediumResamplingQuality), x, (y + sliderPos - 40) * 0.95);
    }

private:

};

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
    GouodKickLookAndFeel gouodKickLookAndFeel;

    void sliderValueChanged(juce::Slider* slider) override;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GouodKickAudioProcessorEditor)

};


