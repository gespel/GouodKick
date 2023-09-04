/*
  ==============================================================================

    GouodKick.cpp
    Created: 27 Aug 2023 11:14:30pm
    Author:  stenh

  ==============================================================================
*/

#include "GouodKick.h"

GouodKick::GouodKick(int sampleRate, int bufferSize) {
    this->bufferSize = bufferSize;
    this->sampleRate = sampleRate;
    this->filterL11.reset();
    this->filterL12.reset();
    this->filterL21.reset();
    this->filterL22.reset();
    this->filterR11.reset();
    this->filterR12.reset();
    this->filterR21.reset();
    this->filterR22.reset();

    this->filterL11.coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(this->sampleRate, 100.0);
    this->filterL12.coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(this->sampleRate, 20.0);
    this->filterR11.coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(this->sampleRate, 100.0);
    this->filterR12.coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(this->sampleRate, 20.0);

    this->filterL21.coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(this->sampleRate, 8000);
    this->filterL22.coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(this->sampleRate, 1000.0);
    this->filterR21.coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(this->sampleRate, 8000);
    this->filterR22.coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(this->sampleRate, 1000.0);
}

void GouodKick::processBuffer(juce::AudioBuffer<float> buffer) {
    auto* channelInputL = buffer.getReadPointer(0);
    auto* channelInputR = buffer.getReadPointer(1);

    juce::AudioBuffer<float> effectBuffer1(2, this->bufferSize);
    auto* eb1InL = effectBuffer1.getWritePointer(0);
    auto* eb1InR = effectBuffer1.getWritePointer(1);
    auto* eb1OutL = effectBuffer1.getReadPointer(0);
    auto* eb1OutR = effectBuffer1.getReadPointer(1);

    juce::AudioBuffer<float> effectBuffer2(2, this->bufferSize);
    auto* eb2InL = effectBuffer2.getWritePointer(0);
    auto* eb2InR = effectBuffer2.getWritePointer(1);
    auto* eb2OutL = effectBuffer2.getReadPointer(0);
    auto* eb2OutR = effectBuffer2.getReadPointer(1);

    auto* channelOutputL = buffer.getWritePointer(0);
    auto* channelOutputR = buffer.getWritePointer(1);


    for (int sample = 0; sample < this->bufferSize; sample++) {
        eb1InL[sample] = channelInputL[sample];
        eb1InR[sample] = channelInputR[sample];
        eb2InL[sample] = channelInputL[sample];
        eb2InR[sample] = channelInputR[sample];

        eb1InL[sample] = filterL11.processSample(eb1InL[sample]);
        eb1InL[sample] = filterL12.processSample(eb1InL[sample]);
        eb1InR[sample] = filterR11.processSample(eb1InL[sample]);
        eb1InR[sample] = filterR12.processSample(eb1InL[sample]);
        eb1InL[sample] = 2 / 3.14159265359 * atan(eb1InL[sample] * 100);
        eb1InR[sample] = 2 / 3.14159265359 * atan(eb1InR[sample] * 100);


        eb2InL[sample] = filterL21.processSample(eb1InL[sample]);
        eb2InL[sample] = filterL22.processSample(eb1InL[sample]);
        eb2InR[sample] = filterR21.processSample(eb1InL[sample]);
        eb2InR[sample] = filterR22.processSample(eb1InL[sample]);
        eb2InL[sample] = 2 / 3.14159265359 * atan(eb2InL[sample] * 100);
        eb2InR[sample] = 2 / 3.14159265359 * atan(eb2InR[sample] * 100);

        channelOutputL[sample] = (channelInputL[sample] + (eb1OutL[sample] + eb2OutL[sample]) / 2) / 2;
        channelOutputR[sample] = (channelInputR[sample] + (eb1OutR[sample] + eb2OutR[sample]) / 2) / 2;
    }
}
