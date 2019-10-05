/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "original_hornet/TubeAmp.h"

using AudioGraphIOProcessor = AudioProcessorGraph::AudioGraphIOProcessor;
using Node = AudioProcessorGraph::Node;


//==============================================================================
/**
*/
class AmpedAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    AmpedAudioProcessor();
    ~AmpedAudioProcessor();

    void extracted(double sampleRate, int samplesPerBlock);
    
    void extracted(const char *data, double sampleRate, int samplesPerBlock, int size);
    
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
    
    
private:
    
    void initInpulseResponseProcessor(const char *data, double sampleRate, int samplesPerBlock, int size, juce::dsp::Convolution& convolution);
    
    void updateGraph();

    static void interleaveSamples (double** source, double* dest, int numSamples, int numChannels);
    
    static void deinterleaveSamples (double* source, double** dest, int numSamples, int numChannels);
    void initialiseGraph();

    void connectAudioNodes();
    void connectMidiNodes();


private:
    //==============================================================================
    
    void setupAmp();

    std::unique_ptr<AudioProcessorGraph> mainProcessor;

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
    

    juce::dsp::Convolution cabSim;
    juce::dsp::Convolution ampSim;
    
    Node::Ptr audioInputNode;
    Node::Ptr audioOutputNode;
    Node::Ptr midiInputNode;
    Node::Ptr midiOutputNode;
    
  //  Node::Ptr gainProcessor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AmpedAudioProcessor)

  //  juce::dsp::ProcessorChain<juce::dsp::Convolution> fxChain;
};
