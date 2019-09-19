/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "original_hornet/TubeAmp.h"
//==============================================================================
AmpedAudioProcessor::AmpedAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

AmpedAudioProcessor::~AmpedAudioProcessor()
{
}

//==============================================================================
const String AmpedAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool AmpedAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool AmpedAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool AmpedAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double AmpedAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int AmpedAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int AmpedAudioProcessor::getCurrentProgram()
{
    return 0;
}

void AmpedAudioProcessor::setCurrentProgram (int index)
{
}

const String AmpedAudioProcessor::getProgramName (int index)
{
    return {};
}

void AmpedAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void AmpedAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    
   /*
    Demo delay plugin code below:
    
    const double smoothTime = 1e-3;
    //paramDelayTime.reset (sampleRate, smoothTime);
    //paramFeedback.reset (sampleRate, smoothTime);
    //paramMix.reset (sampleRate, smoothTime);
    
    //======================================
    
    float maxDelayTime = 2.0;
    delayBufferSamples = (int)(maxDelayTime * (float)sampleRate) + 1;
    if (delayBufferSamples < 1)
        delayBufferSamples = 1;
    
    delayBufferChannels = getTotalNumInputChannels();
    delayBuffer.setSize (delayBufferChannels, delayBufferSamples);
    delayBuffer.clear();
    
    delayWritePosition = 0;
    */

}

void AmpedAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool AmpedAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void AmpedAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
     ScopedNoDenormals noDenormals;
     auto totalNumInputChannels  = getTotalNumInputChannels();
     auto totalNumOutputChannels = getTotalNumOutputChannels();
     
     // In case we have more outputs than inputs, this code clears any output
     // channels that didn't contain input data, (because these aren't
     // guaranteed to be empty - they may contain garbage).
     // This is here to avoid people getting screaming feedback
     // when they first compile a plugin, but obviously you don't need to keep
     // this code if your algorithm always overwrites all the output channels.
     for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
     buffer.clear (i, 0, buffer.getNumSamples());
     
     // This is the place where you'd normally do the guts of your plugin's
     // audio processing...
     // Make sure to reset the state if your inner loop is processing
     // the samples and the outer loop is handling the channels.
     // Alternatively, you can process the samples with the channels
     // interleaved by keeping the same state.
     for (int channel = 0; channel < totalNumInputChannels; ++channel)
     {
     auto* channelData = buffer.getWritePointer (channel);
     
     // ..do something to the data...
     }
    
    
    
    /*
     
     https://github.com/juandagilc/Audio-Effects/blob/master/Delay/Source/PluginProcessor.h
     
     
     Demo delay plugin code below:
    ScopedNoDenormals noDenormals;
    
    const int numInputChannels = getTotalNumInputChannels();
    const int numOutputChannels = getTotalNumOutputChannels();
    const int numSamples = buffer.getNumSamples();
    
    //======================================
    
    float currentDelayTime = 0.5 * (float)getSampleRate();
    float currentFeedback = 0.5;
    float currentMix = 0.5;
    
    int localWritePosition;
    
    for (int channel = 0; channel < numInputChannels; ++channel) {
        float* channelData = buffer.getWritePointer (channel);
        float* delayData = delayBuffer.getWritePointer (channel);
        localWritePosition = delayWritePosition;
        
        for (int sample = 0; sample < numSamples; ++sample) {
            const float in = channelData[sample];
            float out = 0.0f;
            
            float readPosition =
            fmodf ((float)localWritePosition - currentDelayTime + (float)delayBufferSamples, delayBufferSamples);
            int localReadPosition = floorf (readPosition);
            
            if (localReadPosition != localWritePosition) {
                float fraction = readPosition - (float)localReadPosition;
                float delayed1 = delayData[(localReadPosition + 0)];
                float delayed2 = delayData[(localReadPosition + 1) % delayBufferSamples];
                out = delayed1 + fraction * (delayed2 - delayed1);
                
                channelData[sample] = in + currentMix * (out - in);
                delayData[localWritePosition] = in + out * currentFeedback;
            }
            
            if (++localWritePosition >= delayBufferSamples)
                localWritePosition -= delayBufferSamples;
        }
    }
    
    delayWritePosition = localWritePosition;
    
    //======================================
    
    for (int channel = numInputChannels; channel < numOutputChannels; ++channel)
        buffer.clear (channel, 0, numSamples);
     
     */
    
    
    
    

}

//==============================================================================
bool AmpedAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* AmpedAudioProcessor::createEditor()
{
    return new AmpedAudioProcessorEditor (*this);
}

//==============================================================================
void AmpedAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void AmpedAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AmpedAudioProcessor();
}
