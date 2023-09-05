/*
  ==============================================================================

    GouodKick.h
    Created: 27 Aug 2023 11:14:30pm
    Author:  stenh

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"

class GouodKick {
public:
    GouodKick(int sampleRate, int bufferSize);
    void processBuffer(juce::AudioBuffer<float> buffer);
    void setFilterFactor(float filterFactor);
private:
    int sampleRate;
    int bufferSize;
	float filterFactor;

    juce::dsp::IIR::Filter<float> filterLowL1;
    juce::dsp::IIR::Filter<float> filterLowL2;
    juce::dsp::IIR::Filter<float> filterLowR1;
    juce::dsp::IIR::Filter<float> filterLowR2;

    juce::dsp::IIR::Filter<float> filterHighL1;
    juce::dsp::IIR::Filter<float> filterHighL2;
    juce::dsp::IIR::Filter<float> filterHighR1;
    juce::dsp::IIR::Filter<float> filterHighR2;

    void setupFilter();
};
