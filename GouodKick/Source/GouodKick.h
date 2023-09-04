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
private:
    int sampleRate;
    int bufferSize;

    juce::dsp::IIR::Filter<float> filterL11;
    juce::dsp::IIR::Filter<float> filterL12;
    juce::dsp::IIR::Filter<float> filterR11;
    juce::dsp::IIR::Filter<float> filterR12;

    juce::dsp::IIR::Filter<float> filterL21;
    juce::dsp::IIR::Filter<float> filterL22;
    juce::dsp::IIR::Filter<float> filterR21;
    juce::dsp::IIR::Filter<float> filterR22;

};
