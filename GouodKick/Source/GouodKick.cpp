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
    
    this->setupFilter();
}

void GouodKick::setLowFilterFactor(float filterFactor) {
	this->lowFilterFactor = filterFactor;
    this->setupFilter();
}

void GouodKick::setHighFilterFactor(float filterFactor) {
    this->highFilterFactor = filterFactor;
    this->setupFilter();
}

void GouodKick::setLowGain(float gain) {
    this->lowGain = gain;
}

void GouodKick::setHighGain(float gain) {
    this->highGain = gain;
}

void GouodKick::processBuffer(juce::AudioBuffer<float> buffer) {
    auto* channelInputL = buffer.getReadPointer(0);
    auto* channelInputR = buffer.getReadPointer(1);


    // ------ Setting up the low frequency buffer
    juce::AudioBuffer<float> effectBufferLow(2, this->bufferSize);
    auto* ebLowInL = effectBufferLow.getWritePointer(0);
    auto* ebLowInR = effectBufferLow.getWritePointer(1);
    auto* ebLowOutL = effectBufferLow.getReadPointer(0);
    auto* ebLowOutR = effectBufferLow.getReadPointer(1);
    // ------------------------------------------

    // ------ Setting up the high frequency buffer
    juce::AudioBuffer<float> effectBufferHigh(2, this->bufferSize);
    auto* ebHighInL = effectBufferHigh.getWritePointer(0);
    auto* ebHighInR = effectBufferHigh.getWritePointer(1);
    auto* ebHighOutL = effectBufferHigh.getReadPointer(0);
    auto* ebHighOutR = effectBufferHigh.getReadPointer(1);
    // ------------------------------------------


    auto* channelOutputL = buffer.getWritePointer(0);
    auto* channelOutputR = buffer.getWritePointer(1);


    for (int sample = 0; sample < this->bufferSize; sample++) {
        ebLowInL[sample] = channelInputL[sample];
        ebLowInR[sample] = channelInputR[sample];

        ebHighInL[sample] = channelInputL[sample];
        ebHighInR[sample] = channelInputR[sample];

        ebLowInL[sample] = filterLowL1.processSample(ebLowInL[sample]);
        ebLowInL[sample] = filterLowL2.processSample(ebLowInL[sample]);
        ebLowInR[sample] = filterLowR1.processSample(ebLowInL[sample]);
        ebLowInR[sample] = filterLowR2.processSample(ebLowInL[sample]);

        ebLowInL[sample] = 2 / 3.14159265359 * atan(ebLowInL[sample] * this->lowGain);
        ebLowInR[sample] = 2 / 3.14159265359 * atan(ebLowInR[sample] * this->lowGain);


        ebHighInL[sample] = filterHighL1.processSample(ebHighInL[sample]);
        ebHighInL[sample] = filterHighL2.processSample(ebHighInL[sample]);
        ebHighInR[sample] = filterHighR1.processSample(ebHighInR[sample]);
        ebHighInR[sample] = filterHighR2.processSample(ebHighInR[sample]);

        ebHighInL[sample] = 2 / 3.14159265359 * atan(ebHighInL[sample] * this->highGain);
        ebHighInR[sample] = 2 / 3.14159265359 * atan(ebHighInR[sample] * this->highGain);

        channelOutputL[sample] = (/*channelInputL[sample] + */(ebLowOutL[sample] + ebHighOutL[sample]) / 2) / 2;
        channelOutputR[sample] = (/*channelInputR[sample] + */(ebLowOutR[sample] + ebHighOutR[sample]) / 2) / 2;
    }
}

void GouodKick::setupFilter() {
    this->filterLowL1.reset();
    this->filterLowL2.reset();
    this->filterHighL1.reset();
    this->filterHighL2.reset();
    this->filterLowR1.reset();
    this->filterLowR2.reset();
    this->filterHighR1.reset();
    this->filterHighR2.reset();

    this->filterLowL1.coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(this->sampleRate, 100.0 * this->lowFilterFactor);
    this->filterLowL2.coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(this->sampleRate, 20.0 * this->lowFilterFactor);
    this->filterLowR1.coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(this->sampleRate, 100.0 * this->lowFilterFactor);
    this->filterLowR2.coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(this->sampleRate, 20.0 * this->lowFilterFactor);

    this->filterHighL1.coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(this->sampleRate, 8000 * this->highFilterFactor);
    this->filterHighL2.coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(this->sampleRate, 1000.0 * this->highFilterFactor);
    this->filterHighR1.coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(this->sampleRate, 8000 * this->highFilterFactor);
    this->filterHighR2.coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(this->sampleRate, 1000.0 * this->highFilterFactor);
}
