/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include <iostream>

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


    void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override {
        Image knob = ImageCache::getFromMemory(BinaryData::KNOB_V10_png, BinaryData::KNOB_V10_pngSize);
        int radius = jmin(width, height);
        int centreX = int(width / 2);
        int centreY = int(height / 2) + 5;
        float ventilCentreX = float(knob.getWidth()) * .5f;
        float ventilCentreY = float(knob.getHeight()) * .5f;
        float rotation = (MathConstants<float>::twoPi * sliderPos);

        //knob = knob.rescaled(radius, radius, Graphics::ResamplingQuality::highResamplingQuality);

        AffineTransform transform;
        float centreImage = float(centreX) - ventilCentreX;
        transform = transform.rotation(rotation, ventilCentreX, ventilCentreY).translated(centreImage,0);
        g.drawImageTransformed(knob, transform, false);
    }

    void drawLinearSlider (Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, Slider::SliderStyle, Slider &) override {
        Image sliderKnob = ImageCache::getFromMemory (BinaryData::FADER_SHADOW_png, BinaryData::FADER_SHADOW_pngSize);
        float mid = height/2;
        //200 - 50 / 2 + 50 = 125
        //100 - 20 / 2 + 20 = 60 

        // 60 - 20 / 100 - 20a
        std::cout << "SliderPos: " << sliderPos << " MinSliderPos: " << minSliderPos << " MaxSliderPos: " << maxSliderPos << std::endl;
        if(mid < sliderPos) {
            g.setColour(juce::Colours::grey);
            g.fillRect(x + 19.0f, y + 15.0f + (height/2.0f) * 0.85, 6.0f, 15.0f + (sliderPos-mid) * 0.85);            
        }
        else {
            g.setColour(juce::Colours::grey);
            g.fillRect(x + 19.0f, 15.f + sliderPos * 0.85, 6.f, 15.0f + (mid-sliderPos) * 0.85);
        }
        g.drawImageAt (sliderKnob.rescaled(sliderKnob.getWidth()/4, sliderKnob.getHeight()/4, Graphics::mediumResamplingQuality), x, (y + sliderPos - 5) * 0.85);
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

    juce::Slider dryWetSlider;
    juce::Slider gainSlider;
    

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    GouodKickAudioProcessor& audioProcessor;
    GouodKickLookAndFeel gouodKickLookAndFeel;

    void sliderValueChanged(juce::Slider* slider) override;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GouodKickAudioProcessorEditor)

};


