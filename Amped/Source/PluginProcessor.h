/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "original_hornet/TubeAmp.h"

//==============================================================================
/**
*/
class AmpedAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    AmpedAudioProcessor();
    ~AmpedAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;
    
    void processBlock (AudioBuffer<double>& buffer,
                               MidiBuffer& midiMessages) override;
    
    virtual bool supportsDoublePrecisionProcessing() const override;


    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    
    // Delay plugin 
  //  AudioSampleBuffer delayBuffer;
  //  int delayBufferSamples;
  //  int delayBufferChannels;
  //  int delayWritePosition;
    
    //======================================
    
    //PluginParametersManager parameters;
    
   // PluginParameterLinSlider paramDelayTime;
   // PluginParameterLinSlider paramFeedback;
   // PluginParameterLinSlider paramMix;
    
    
    static void interleaveSamples (double** source, double* dest, int numSamples, int numChannels);
    
    static void deinterleaveSamples (double* source, double** dest, int numSamples, int numChannels);

private:
    //==============================================================================
    
    void setupAmp();
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AmpedAudioProcessor)
    
    TubeAmp tubeAmp;
    AudioProcessorValueTreeState parameters;
    
    float* inputParameter = nullptr;
    float* fxParameter = nullptr;
    
    float* driveParameter = nullptr;
    float* bassParameter = nullptr;
    float* middleParameter = nullptr;
    float* trebleParameter = nullptr;
    float* presenceParameter = nullptr;
    float* masterParameter = nullptr;
    float* irParameter = nullptr;
    float* outputParameter = nullptr;
};
