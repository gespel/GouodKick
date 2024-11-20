/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GouodKickAudioProcessor::GouodKickAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
        parameters(*this, nullptr, juce::Identifier("Kicktator"),
            {
                std::make_unique<juce::AudioParameterFloat>("lowgain", "Low Gain", 0.0f, 100.0f, 0.5f),
                std::make_unique<juce::AudioParameterFloat>("highgain", "High Gain", 0.0f, 100.0f, 0.5f),
                std::make_unique<juce::AudioParameterFloat>("lowamount", "Low Amount", 0.0f, 3.0f, 0.5f),
                std::make_unique<juce::AudioParameterFloat>("highamount", "High Amount", 0.0f, 2.0f, 0.5f),
                std::make_unique<juce::AudioParameterFloat>("wet", "Dry Wet", 0.0f, 100.0f, 0.5f),
                std::make_unique<juce::AudioParameterFloat>("gain", "Gain", 0.0f, 10.0f, 0.5f)
            }
        )
#endif
{
}

GouodKickAudioProcessor::~GouodKickAudioProcessor()
{
}

//==============================================================================
const juce::String GouodKickAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool GouodKickAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool GouodKickAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool GouodKickAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}


double GouodKickAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int GouodKickAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int GouodKickAudioProcessor::getCurrentProgram()
{
    return 0;
}

void GouodKickAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String GouodKickAudioProcessor::getProgramName (int index)
{
    return {};
}

void GouodKickAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void GouodKickAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    gainParameter = parameters.getRawParameterValue("gain");
    lowGainParameter = parameters.getRawParameterValue("lowgain");
    highGainParameter = parameters.getRawParameterValue("highgain");
    dryWet = parameters.getRawParameterValue("wet");
    lFF = parameters.getRawParameterValue("lowamount");
    hFF = parameters.getRawParameterValue("highamount");

    this->gk = new GouodKick(sampleRate, samplesPerBlock);
    this->gk->setHighFilterFactor(*hFF);
    this->gk->setLowFilterFactor(*lFF);
    this->gk->setHighGain(*highGainParameter);
    this->gk->setLowGain(*lowGainParameter);
    this->gk->setDryWet(*dryWet);
    this->gk->setOutGain(*gainParameter);
}

void GouodKickAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool GouodKickAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void GouodKickAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
   
    gk->processBuffer(buffer);



}

//==============================================================================
bool GouodKickAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* GouodKickAudioProcessor::createEditor()
{
    return new GouodKickAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void GouodKickAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void GouodKickAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(parameters.state.getType()))
            parameters.replaceState(juce::ValueTree::fromXml(*xmlState));
}

void GouodKickAudioProcessor::updateParameters(float lowFilterFactor, float highFilterFactor, float lowGain, float highGain, float gain, int dw) {
    gk->setLowFilterFactor(lowFilterFactor);
    gk->setHighFilterFactor(highFilterFactor);
    gk->setLowGain(lowGain);
    gk->setHighGain(highGain);
    gk->setOutGain(gain);
    gk->setDryWet(dw);

}


//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GouodKickAudioProcessor();
}
