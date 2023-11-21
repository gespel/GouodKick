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
    void setLowFilterFactor(float filterFactor);
    void setHighFilterFactor(float filterFactor);
    void setLowGain(float gain);
    void setHighGain(float gain);
    void setDryWet(int dw);
    void setOutGain(float gain);

private:
    int sampleRate;
    int bufferSize;
	
    juce::dsp::IIR::Filter<float> filterLowL1;
    juce::dsp::IIR::Filter<float> filterLowL2;
    juce::dsp::IIR::Filter<float> filterLowR1;
    juce::dsp::IIR::Filter<float> filterLowR2;

    juce::dsp::IIR::Filter<float> filterHighL1;
    juce::dsp::IIR::Filter<float> filterHighL2;
    juce::dsp::IIR::Filter<float> filterHighR1;
    juce::dsp::IIR::Filter<float> filterHighR2;

    float lowGain = 1.0f;
    float highGain = 1.0f;
    float outGain = 1.0f;
    float dryWet = 100;
    float lowFilterFactor = 1.0f;
    float highFilterFactor = 1.0f;

    void setupFilter();

};
