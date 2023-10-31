/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GouodKickAudioProcessorEditor::GouodKickAudioProcessorEditor (GouodKickAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (500, 300);

    highFrequencySlider.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
    highFrequencySlider.setRange(0.0, 2.0, 0.1);
    highFrequencySlider.setTextValueSuffix(" High Part");
    highFrequencySlider.setValue(1.0f);
    highFrequencySlider.addListener(this);
    addAndMakeVisible(&highFrequencySlider);

    lowFrequencySlider.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
    lowFrequencySlider.setRange(0.0, 3.0, 0.1);
    lowFrequencySlider.setTextValueSuffix(" Low Part");
    lowFrequencySlider.setValue(1.0f);
    lowFrequencySlider.addListener(this);
    addAndMakeVisible(&lowFrequencySlider);

    lowGainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
    lowGainSlider.setRange(0.0, 100.0, 0.1);
    lowGainSlider.setTextValueSuffix(" Low Gain");
    lowGainSlider.setValue(1.0f);
    lowGainSlider.addListener(this);
    addAndMakeVisible(&lowGainSlider);

    highGainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
    highGainSlider.setRange(0.0, 100.0, 0.1);
    highGainSlider.setTextValueSuffix(" High Gain");
    highGainSlider.setValue(1.0f);
    highGainSlider.addListener(this);
    addAndMakeVisible(&highGainSlider);

}

GouodKickAudioProcessorEditor::~GouodKickAudioProcessorEditor()
{
}

//==============================================================================
void GouodKickAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Made by Gouod Labs", getLocalBounds(), juce::Justification::bottomRight, 1);
}

void GouodKickAudioProcessorEditor::resized()
{
    const int border = 20;
    const int dialWidth = getWidth() / 2 - border;
    const int dialHight = getHeight() - border - 100;

    highFrequencySlider.setBounds(border, border, 100, 260);
    lowFrequencySlider.setBounds(2 * border + 100, border, 100, 260);
    lowGainSlider.setBounds(3 * border + 2 * 100, border, 100, 260);
    highGainSlider.setBounds(4 * border + 3 * 100, border, 100, 260);
}

void GouodKickAudioProcessorEditor::sliderValueChanged(juce::Slider* slider) {
    this->audioProcessor.updateParameters(
        lowFrequencySlider.getValue(),
        highFrequencySlider.getValue(),
        lowGainSlider.getValue(),
        highGainSlider.getValue()
    );
}
