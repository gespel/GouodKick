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
    setSize (472, 670);
    setLookAndFeel(&gouodKickLookAndFeel);

    highFrequencySlider.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
    highFrequencySlider.setRange(0.0, 2.0, 0.1);
    //highFrequencySlider.setTextValueSuffix(" High Part");
    highFrequencySlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    highFrequencySlider.setValue(p.gk->getHighFilterFactor());
    highFrequencySlider.addListener(this);
    addAndMakeVisible(&highFrequencySlider);

    lowFrequencySlider.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
    lowFrequencySlider.setRange(0.0, 3.0, 0.1);
    //lowFrequencySlider.setTextValueSuffix(" Low Part");
    lowFrequencySlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    lowFrequencySlider.setValue(p.gk->getLowFilterFactor());
    lowFrequencySlider.addListener(this);
    addAndMakeVisible(&lowFrequencySlider);

    lowGainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
    lowGainSlider.setRange(0.0, 100.0, 0.1);
    //lowGainSlider.setTextValueSuffix(" Low Gain");
    lowGainSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    lowGainSlider.setValue(p.gk->getLowGain());
    lowGainSlider.addListener(this);
    addAndMakeVisible(&lowGainSlider);

    highGainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
    highGainSlider.setRange(0.0, 100.0, 0.1);
    //highGainSlider.setTextValueSuffix(" High Gain");
    highGainSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    highGainSlider.setValue(p.gk->getHighGain());
    highGainSlider.addListener(this);
    addAndMakeVisible(&highGainSlider);

    dryWetSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    dryWetSlider.setRange(0.0, 100.0, 1.0);
    dryWetSlider.setValue(p.gk->getDryWet());
    dryWetSlider.addListener(this);
    dryWetSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    addAndMakeVisible(&dryWetSlider);

    gainSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    gainSlider.setRange(0.0, 10.0, 1.0);
    gainSlider.setValue(p.gk->getOutGain());
    gainSlider.addListener(this);
    gainSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    addAndMakeVisible(&gainSlider);

}

GouodKickAudioProcessorEditor::~GouodKickAudioProcessorEditor()
{
}

//==============================================================================
void GouodKickAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    Image background = ImageCache::getFromMemory (BinaryData::KICKTATOR_V6_BG_png, BinaryData::KICKTATOR_V6_BG_pngSize);
    g.drawImageAt (background, 0, 0);

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Made by Gouod Labs", getLocalBounds(), juce::Justification::bottomRight, 1);

    // 0 1 2
    //0
    //1
    //2

    g.fillRect(48, 221 - (lowGainSlider.getValue()/lowGainSlider.getMaximum()) * 122, 39, (lowGainSlider.getValue()/lowGainSlider.getMaximum()) * 122 );
    g.fillRect(144, 221 - (lowFrequencySlider.getValue()/lowFrequencySlider.getMaximum()) * 122, 39, (lowFrequencySlider.getValue()/lowFrequencySlider.getMaximum()) * 122 );
    g.fillRect(292, 221 - (highGainSlider.getValue()/highGainSlider.getMaximum()) * 122, 39, (highGainSlider.getValue()/highGainSlider.getMaximum()) * 122 );
    g.fillRect(388, 221 - (highFrequencySlider.getValue()/highFrequencySlider.getMaximum()) * 122, 39, (highFrequencySlider.getValue()/highFrequencySlider.getMaximum()) * 122 );
}

void GouodKickAudioProcessorEditor::resized()
{
    highFrequencySlider.setValue(audioProcessor.gk->getHighFilterFactor());

    const int border = 20;
    const int dialWidth = getWidth() / 2 - border;
    const int dialHight = getHeight() - border - 100;

    
    lowGainSlider.setBounds(43, 334, 48, 310);
    lowFrequencySlider.setBounds(141, 334, 48, 310);

    highGainSlider.setBounds(290, 336, 48, 310);
    highFrequencySlider.setBounds(307 + 114 - 33, 334, 48, 310);

    dryWetSlider.setBounds(195, 362, 90, 90);
    gainSlider.setBounds(195, 515, 90, 90);
}

void GouodKickAudioProcessorEditor::sliderValueChanged(juce::Slider* slider) {
    this->audioProcessor.updateParameters(
        lowFrequencySlider.getValue(),
        highFrequencySlider.getValue(),
        lowGainSlider.getValue(),
        highGainSlider.getValue(),
        gainSlider.getValue(),
        dryWetSlider.getValue()
    );
    repaint();
}
