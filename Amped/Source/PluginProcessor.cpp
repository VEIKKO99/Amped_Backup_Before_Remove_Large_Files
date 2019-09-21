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
AmpedAudioProcessor::AmpedAudioProcessor() :
#ifndef JucePlugin_PreferredChannelConfigurations
      AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
        parameters (*this, nullptr, Identifier ("AmpedV100"),
                    {
                        std::make_unique<AudioParameterFloat> ("input",            // parameterID
                                                               "Input",            // parameter name
                                                               0.0f,              // minimum value
                                                               1.0f,              // maximum value
                                                               0.5f),             // default value
                        std::make_unique<AudioParameterBool> ("fx",               // parameterID
                                                              "FX",                // parameter name
                                                              false),              // default value
                        std::make_unique<AudioParameterFloat> ("drive", "Drive", 0.0f, 1.0f, 0.5f),
                        std::make_unique<AudioParameterFloat> ("bass","Bass", 0.0f, 1.0f, 0.5f),             
                        std::make_unique<AudioParameterFloat> ("middle", "Middle", 0.0f, 1.0f, 0.5f),
                        std::make_unique<AudioParameterFloat> ("trebble", "Trebble", 0.0f, 1.0f, 0.5f),
                        std::make_unique<AudioParameterFloat> ("presence", "Presence", 0.0f,  1.0f, 0.5f),
                        std::make_unique<AudioParameterFloat> ("master", "Master", 0.0f, 1.0f, 0.5f),
                        std::make_unique<AudioParameterBool> ("ir", "IR", false),
                        std::make_unique<AudioParameterFloat> ("output", "Output", 0.0f, 1.0f, 0.5f) })
#endif
{
    Logger::getCurrentLogger()->writeToLog("AmpedAudioProcessor - Constructor");
    inputParameter = parameters.getRawParameterValue ("input");
    fxParameter = parameters.getRawParameterValue ("fx");
    driveParameter = parameters.getRawParameterValue ("dirve");
    bassParameter = parameters.getRawParameterValue ("bass");
    middleParameter = parameters.getRawParameterValue ("middle");
    trebleParameter = parameters.getRawParameterValue ("trebble");
    presenceParameter = parameters.getRawParameterValue ("presence");
    masterParameter = parameters.getRawParameterValue ("master");
    irParameter = parameters.getRawParameterValue ("ir");
    outputParameter = parameters.getRawParameterValue ("output");


    driveParameter = parameters.getRawParameterValue ("drive");
    
    
  //  tubeAmp.setNumChans(2);
  //  tubeAmp.setSampleRate(48000);
  //  tubeAmp.init();
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

void AmpedAudioProcessor::processBlock (AudioBuffer<double>& buffer,
                                                MidiBuffer& midiMessages)
{
    
    double* interleavedBuffer = new double[buffer.getNumChannels() * buffer.getNumSamples()];
    
    AmpedAudioProcessor::interleaveSamples(buffer.getArrayOfWritePointers(), interleavedBuffer, buffer.getNumSamples(), buffer.getNumChannels());
    
    tubeAmp.process(interleavedBuffer, buffer.getNumSamples());
    
    AmpedAudioProcessor::deinterleaveSamples(interleavedBuffer, buffer.getArrayOfWritePointers(),
                                             buffer.getNumSamples(), buffer.getNumChannels());
    
    delete[] interleavedBuffer;
    
    
    
    
  //  for (int i = 0; i < buffer.getNumChannels(); ++i)
  //  {
    //    double* chanbuf = buffer.getWritePointer(1);
        
    //    tubeAmp.process(chanbuf, buffer.getNumSamples());
        //for (int j = 0; j < bufferIn.getNumSamples(); ++j)
        //{
        //    chanbuf[j] = getNextSample(chanbuf[j]);
        //}
   // }
    
}



bool AmpedAudioProcessor::supportsDoublePrecisionProcessing() const
{
    return true;
}

//==============================================================================
void AmpedAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    Logger::getCurrentLogger()->writeToLog("prepareToPlay   ");

 //   void HoRNetGuitarKit::Reset()
 //   {
 //       TRACE;
     //   IMutexLock lock(this);
        
        tubeAmp.setSampleRate(sampleRate);
        tubeAmp.setOversample(1);
        tubeAmp.init();
        tubeAmp.setNumChans(2);
    tubeAmp.setPreGain(1.0);
    tubeAmp.setDryWet(1.0);
    tubeAmp.setMasterVolume(1.0);
    tubeAmp.setTubeType(5, 8);
   // tubeAmp.setHighGainStageActive(true);
    tubeAmp.setInputType(PreAmp::EInputType::kMarshall);
    tubeAmp.setToneStackActive(false);
    tubeAmp.setPowerAmpTubeType(TUBE_TABLE_EL34_68k);
        //mCabSim.setSampleRate(GetSampleRate())tubeAmp
        //tubeAmp.init();
        //tubeAmp.setOversample(1);
        //tubeAmp.setNumChans(1);
        
        //mMicSim.setSampleRate(GetSampleRate());
        //mMicSim.init();
        //mMicSim.setOversample(1);
        //mMicSim.setNumChans(1);
        
       // for (int i = 0; i < kNumParams; i++) {
       //     OnParamChange(i, false);
       // }
        
  //  }
    
    
  //  AudioProcessor::ProcessingPrecision precision = getProcessingPrecision();

    
    
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
    Logger::getCurrentLogger()->writeToLog("float process block");


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
    return new AmpedAudioProcessorEditor (*this, parameters);
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


//==============================================================================
void AmpedAudioProcessor::interleaveSamples (double** source, double* dest, int numSamples, int numChannels)
{
    for (int chan = 0; chan < numChannels; ++chan)
    {
        auto i = chan;
        auto src = source [chan];
        
        for (int j = 0; j < numSamples; ++j)
        {
            dest [i] = src [j];
            i += numChannels;
        }
    }
}

void AmpedAudioProcessor::deinterleaveSamples (double* source, double** dest, int numSamples, int numChannels)
{
    for (int chan = 0; chan < numChannels; ++chan)
    {
        auto i = chan;
        auto dst = dest [chan];
        
        for (int j = 0; j < numSamples; ++j)
        {
            dst [j] = source [i];
            i += numChannels;
        }
    }
}
