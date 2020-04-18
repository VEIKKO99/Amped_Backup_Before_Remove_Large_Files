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
#include "AmpedAudioProcessorBase.h"
#include "SoundSettingsModel.h"

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

    void settingChanged(bool dontUpdatePreset = false) override;
    void presetChanged() override;

    std::shared_ptr<SoundSettings> getCurrentSettings() override;

    FFAU::LevelMeterSource& getMeterSource();

    void nextSetting();
    void prevSetting();

    SoundSettingsModel& getSoundSettingsModel();

    bool copyProtection = false;
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


    void selectSettingWithId(int ampIndex);

    void selectPresetWithId(int index);

private:

    void updateGraph();

    void initialiseMainGraph();
    void initialisePreEffectsGraph();

    void connectPreEffectsAudioNodes();

    void connectMainAudioNodes();
    void connectMidiNodes();

    inline void processInputGain(AudioBuffer<float>& buffer);


    void connectPreEffectsMidiNodes();

    void initEq(Node::Ptr& eq, String lowBinFileName, String highBinFileName,
                float* parameter, float makeupGain, EQType type);


    void initReverb(const double sampleRate);
    void processReverb(AudioBuffer<float> &buffer);

private:
    //==============================================================================

    void setupAmp();

    std::unique_ptr<AmpedMonoAudioGraph> preEffectsProcessor;
    std::unique_ptr<AmpedMonoAudioGraph> mainProcessor;
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

    float* effects_od_switch = nullptr;
    float* effects_ng_switch = nullptr;

    // L/R Switch:
    float* leftRightInputSwitch = nullptr;

    // Reverb:
    float* reverbOnOffParameter = nullptr;
    float* reverbSizeParameter = nullptr;
    float* reverbToneParameter = nullptr;
    float* reverbMixParameter = nullptr;

#ifdef AMPED_DEBUG
    float* ampSimSwitch = nullptr;
#endif

    Node::Ptr audioInputPreEffectsNode;
    Node::Ptr audioOutputPreEffectsNode;
    Node::Ptr preEffectsMidiInputNode;
    Node::Ptr preEffectsMidiOutputNode;
    Node::Ptr overdriveNode;
    Node::Ptr noiseGateNode;


    Node::Ptr audioInputNode;
    Node::Ptr audioOutputNode;
    Node::Ptr midiInputNode;
    Node::Ptr midiOutputNode;

    Node::Ptr gainProcessor;
    Node::Ptr driveProcessor;

    Node::Ptr ampProcessor;

    Node::Ptr bassEq;
    Node::Ptr middleEq;
    Node::Ptr trebleEq;

    Node::Ptr presenceEq;

    Node::Ptr ampSimIR;
    Node::Ptr cabSimIR;

    Node::Ptr outputGainProcessor;

    ReferenceCountedArray<Node> mainAudioProcessors;
    ReferenceCountedArray<Node> preEffectsAudioProcessors;

   // std::shared_ptr<SoundSettings> soundSettings = std::make_shared<SoundSettings>();

    SoundSettingsModel soundSettingsModel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AmpedAudioProcessor)

    FFAU::LevelMeterSource meterSource;

    // Reverb:
    Reverb reverb;
    Reverb::Parameters reverbParams;

    int previousPrepareSampleRate;
    int previousPrepareSamplesPerBlock;
};
