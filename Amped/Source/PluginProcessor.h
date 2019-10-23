/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "original_hornet/TubeAmp.h"
#include "UIConsts.h"
#include "AdminSettingsUtil.h"
using AudioGraphIOProcessor = AudioProcessorGraph::AudioGraphIOProcessor;
using Node = AudioProcessorGraph::Node;


//==============================================================================
/**
*/
class AmpedAudioProcessor  : public AudioProcessor, public ISoundSettingsChanged
{
public:
    //==============================================================================
    AmpedAudioProcessor();
    ~AmpedAudioProcessor();

    void extracted(double sampleRate, int samplesPerBlock);
    
    void extracted(const char *data, double sampleRate, int samplesPerBlock, int size);
    
//==============================================================================
    void prepareToPlay_temp (double sampleRate, int samplesPerBlock);
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;

    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    
    void processBlock_temp (AudioBuffer<double>& buffer,
                            MidiBuffer& midiMessages);
    
    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;
    
   // void processBlock (AudioBuffer<double>& buffer,
   //                            MidiBuffer& midiMessages) override;
    
    //virtual bool supportsDoublePrecisionProcessing() const override;


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

    void settingChanged() override;
    std::shared_ptr<SoundSettings> getCurrentSettings() override;

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
    void initInternalAmpSettings();
    void updateGraph();

    static void interleaveSamples (double** source, double* dest, int numSamples, int numChannels);
    
    static void deinterleaveSamples (double* source, double** dest, int numSamples, int numChannels);
    void initialiseGraph();

    void connectAudioNodes();
    void connectMidiNodes();
    
    void initEq(Node::Ptr& eq, const char *lowPotImpulseData, int lowPotImpulseDataSize,
                               const char *highPotImpulseData, int highPotImpulseDataSize,
                float* parameter, float makeupGain);


private:
    //==============================================================================
    
    void setupAmp();

    std::unique_ptr<AudioProcessorGraph> mainProcessor;
    void initProcessor(Node::Ptr processor);
    
    //TubeAmp tubeAmp;
    AudioProcessorValueTreeState parameters;
    
    float* inputParameter = nullptr;
    float* fxParameter = nullptr;
    
    float* driveParameter = nullptr;
    float* bassParameter = nullptr;
    float* middleParameter = nullptr;
    float* trebleParameter = nullptr;
    float* presenceParameter = nullptr;
    float* masterParameter = nullptr;
    float* cabSimSwitch = nullptr;
    float* outputParameter = nullptr;
    
#ifdef AMPED_DEBUG
    float* ampSimSwitch = nullptr;
#endif
    

//    juce::dsp::Convolution cabSim;
//    juce::dsp::Convolution ampSim;
    
    Node::Ptr audioInputNode;
    Node::Ptr audioOutputNode;
    Node::Ptr midiInputNode;
    Node::Ptr midiOutputNode;
    
    Node::Ptr gainProcessor;
    Node::Ptr ampProcessor;
    
    Node::Ptr bassEq;
    Node::Ptr middleEq;
    Node::Ptr trebleEq;
    
    Node::Ptr ampSimIR;
    Node::Ptr cabSimIR;
    
    Node::Ptr outputGainProcessor;
    
    ReferenceCountedArray<Node> audioProcessors;
    
    std::shared_ptr<SoundSettings> soundSettings = std::make_shared<SoundSettings>();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AmpedAudioProcessor)

  //  juce::dsp::ProcessorChain<juce::dsp::Convolution> fxChain;
};
