/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/
#include <type_traits>

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "original_hornet/TubeAmp.h"
#include "AmpedAudioProcessorBase.h"
#include "UIConsts.h"

//==============================================================================
AmpedAudioProcessor::AmpedAudioProcessor() :
#ifndef JucePlugin_PreferredChannelConfigurations
      AudioProcessor (BusesProperties()
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                       .withOutput ("Output", AudioChannelSet::stereo(), true)),
                        mainProcessor  (new AmpedMonoAudioGraph()),
                        preEffectsProcessor  (new AmpedMonoAudioGraph()),

                    parameters (*this, nullptr, Identifier ("AmpedV100"),
                    {
                        std::make_unique<AudioParameterFloat>( VTS_INPUT,            // parameterID
                                                               "Input",            // parameter name
                                                               .0f,              // minimum value
                                                               1.0f,              // maximum value
                                                               0.5f),             // default value
                        std::make_unique<AudioParameterBool> (VTS_FX,               // parameterID
                                                              "FX",                // parameter name
                                                              false),              // default value
                        std::make_unique<AudioParameterFloat> (VTS_DRIVE, "Drive", 0.0f, 1.0f, 0.5f),
                        std::make_unique<AudioParameterFloat> (VTS_BASS,"Bass", 0.0f, 1.0f, 0.5f),
                        std::make_unique<AudioParameterFloat> (VTS_MIDDLE, "Middle", 0.0f, 1.0f, 0.5f),
                        std::make_unique<AudioParameterFloat> (VTS_TREBBLE, "Trebble", 0.0f, 1.0f, 0.5f),
                        std::make_unique<AudioParameterFloat> (VTS_DEPTH, "Depth", 0.0f, 1.0f, 0.5f),
                        std::make_unique<AudioParameterFloat> (VTS_PRESENCE, "Presence", 0.0f,  1.0f, 0.5f),
                        std::make_unique<AudioParameterFloat> (VTS_MASTER, "Master", 0.0f, 1.0f, 0.5f),
                        std::make_unique<AudioParameterFloat> (VTS_CAB_SIM_TYPE, "Cab Sim", 0.0, 2, (float)ThreeWayIRFileSwitch::SwitchStatus::IRDefault),
                        std::make_unique<AudioParameterFloat> (VTS_OUTPUT, "Output", 0.0f, 1.0f, 0.5f),
                        std::make_unique<AudioParameterFloat> (VTS_EF_OD_DRIVE, "OD Drive", 0.0f, 1.0f, 0.5f),
                        std::make_unique<AudioParameterFloat> (VTS_EF_OD_TONE, "OD Tone", 0.0f, 1.0f, 0.5f),
                        std::make_unique<AudioParameterFloat> (VTS_EF_OD_LEVEL, "OD Level", 0.0f, 1.0f, 0.5f),
                        std::make_unique<AudioParameterBool> (VTS_EF_OD_ON, "OD on", false),
                        std::make_unique<AudioParameterBool> (VTS_EF_NG_ON, "NG on", false),
                        std::make_unique<AudioParameterBool> (VTS_LEFT_RIGHT_INPUT_SWITCH, "Input L/R", false),
                        std::make_unique<AudioParameterFloat> (VTS_EF_NG_THRESHOLD, "NG Threshold", .0f, 1.0f, 0.5f),
                        std::make_unique<AudioParameterBool> (VTS_EF_DLY_ON, "Delay On", false),
                        std::make_unique<AudioParameterFloat> (VTS_EF_DLY_TIME, "Delay Time", .0f, 1.0f, 0.5f),
                        std::make_unique<AudioParameterFloat> (VTS_EF_DLY_FEEDBACK, "Delay Feedback", .0f, 1.0f, 0.5f),
                        std::make_unique<AudioParameterFloat> (VTS_EF_DLY_MIX, "Delay Mix", .0f, 1.0f, 0.5f),
                        std::make_unique<AudioParameterBool> (VTS_EF_REVB_ON, "Reverb On", false),
                        std::make_unique<AudioParameterFloat> (VTS_EF_REVB_SIZE, "Reverb Time", .0f, 1.0f, 0.5f),
                        std::make_unique<AudioParameterBool> (VTS_BRIGHT, "Bright", false),

                        std::make_unique<AudioParameterFloat> (VTS_EF_REVB_TONE, "Reverb Tone", .0f, 1.0f, 0.5f),
                        std::make_unique<AudioParameterFloat> (VTS_EF_REVB_MIX, "Reverb Mix", .0f, 1.0f, 0.5f)

#ifdef AMPED_DEBUG
                        ,std::make_unique<AudioParameterBool> ("ampSim", "ampSim", false)
                        #endif
                    })
#endif
{
    mainProcessor->setProcessingPrecision(ProcessingPrecision::singlePrecision);
    preEffectsProcessor->setProcessingPrecision(ProcessingPrecision::singlePrecision);

    inputParameter = parameters.getRawParameterValue (VTS_INPUT);
    fxParameter = parameters.getRawParameterValue (VTS_FX);
    driveParameter = parameters.getRawParameterValue (VTS_DRIVE);
    bassParameter = parameters.getRawParameterValue (VTS_BASS);
    middleParameter = parameters.getRawParameterValue (VTS_MIDDLE);
    trebleParameter = parameters.getRawParameterValue (VTS_TREBBLE);
    depthParameter = parameters.getRawParameterValue (VTS_DEPTH);
    presenceParameter = parameters.getRawParameterValue (VTS_PRESENCE);
    masterParameter = parameters.getRawParameterValue (VTS_MASTER);
    cabSimSwitch = parameters.getRawParameterValue(VTS_CAB_SIM_TYPE);
    outputParameter = parameters.getRawParameterValue (VTS_OUTPUT);
    effects_od_switch = parameters.getRawParameterValue(VTS_EF_OD_ON);
    effects_ng_switch = parameters.getRawParameterValue(VTS_EF_NG_ON);
    leftRightInputSwitch = parameters.getRawParameterValue(VTS_LEFT_RIGHT_INPUT_SWITCH);
    bright = parameters.getRawParameterValue(VTS_BRIGHT);
    
    reverbOnOffParameter = parameters.getRawParameterValue(VTS_EF_REVB_ON);
    reverbSizeParameter = parameters.getRawParameterValue(VTS_EF_REVB_SIZE);
    reverbToneParameter = parameters.getRawParameterValue(VTS_EF_REVB_TONE);
    reverbMixParameter = parameters.getRawParameterValue(VTS_EF_REVB_MIX);
    
    dlyMixParameter = parameters.getRawParameterValue(VTS_EF_DLY_MIX);
    dlyFeedbackParameter = parameters.getRawParameterValue(VTS_EF_DLY_FEEDBACK);
    dlyTimeParameter = parameters.getRawParameterValue(VTS_EF_DLY_TIME);
    dlyOnOffParameter = parameters.getRawParameterValue(VTS_EF_DLY_ON);

    presetChanged();
#ifdef AMPED_DEBUG
    ampSimSwitch = parameters.getRawParameterValue ("ampSim");
#endif
}

AmpedAudioProcessor::~AmpedAudioProcessor()
{
    LicenceTools::deleteInstance();
}

void AmpedAudioProcessor::settingChanged(bool dontUpdatePreset)
{
    for (auto node : mainAudioProcessors) {
        ((AmpedAudioProcessorBase*)node->getProcessor())->updateInternalSettings(getCurrentSettings());
    }
    auto editor = getActiveEditor();
    if (editor != nullptr)
    {
        if (!dontUpdatePreset)
            presetChanged();
        editor->repaint();
        //((AmpedAudioProcessorEditor*)editor)->updateAmpPresetUi();
    }
}

void AmpedAudioProcessor::presetChanged()
{
   auto preset = soundSettingsModel.getCurrentSetting()->getCurrentPreset();
   auto copyCurrent = parameters.copyState();
   if (preset != nullptr && preset->xml->hasTagName (parameters.state.getType())) {
       auto presetState = ValueTree::fromXml(*preset->xml);
       if (presetState.isValid()) {
          // Copy existing input and output values to new setup:
           auto inputParamElement = presetState.getChildWithProperty("id", String(VTS_INPUT));
           if (inputParamElement.isValid()) {
               inputParamElement.setProperty(Identifier("value"), *parameters.getRawParameterValue (VTS_INPUT), nullptr);
           }
           auto outputParamElement = presetState.getChildWithProperty("id", String(VTS_OUTPUT));
           if (outputParamElement.isValid()) {
               outputParamElement.setProperty(Identifier("value"), *parameters.getRawParameterValue (VTS_OUTPUT), nullptr);
           }
           auto leftRightElement = presetState.getChildWithProperty("id", String(VTS_LEFT_RIGHT_INPUT_SWITCH));
           if (leftRightElement.isValid()) {
               leftRightElement.setProperty(Identifier("value"), *parameters.getRawParameterValue (VTS_LEFT_RIGHT_INPUT_SWITCH), nullptr);
           }
       }
       parameters.replaceState(presetState);
   }
    auto editor = getActiveEditor();
    if (editor != nullptr)
    {
        ((AmpedAudioProcessorEditor*)editor)->updateAmpPresetUi();
    }
}

std::shared_ptr<SoundSettings> AmpedAudioProcessor::getCurrentSettings() {
    return soundSettingsModel.getCurrentSetting();
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


/**
 * Saved code to convert double samples to floats and vice versa...
 *
 float** samples = new float*[buffer.getNumChannels()];
 for(int i = 0; i < buffer.getNumChannels(); ++i)
 {
    samples[i] = new float[buffer.getNumSamples()];
    double* buf = buffer.getWritePointer(i);
    for (int j = 0; j < buffer.getNumSamples(); j++)
    {
        samples[i][j] = static_cast<float> (buf[j]);
    }
 }

 dsp::AudioBlock<float> block (samples, buffer.getNumChannels(), buffer.getNumSamples());
 dsp::ProcessContextReplacing<float> context (block);
 //   context.isBypassed = *middleParameter > 0.5;
 context.isBypassed = false;

 ampSim.process(context);
 cabSim.process(context);

 for(int i = 0; i < buffer.getNumChannels(); ++i)
 {
    double* buf = buffer.getWritePointer(i);

    for (int j = 0; j < buffer.getNumSamples(); j++)
    {
        buf[j] = samples[i][j];
    }
    delete [] samples[i];
 }
 delete [] samples;
*/

void AmpedAudioProcessor::initEq(Node::Ptr& eq, String lowBinFileName,
                                                String highBinFileName,
                                                float* parameter,
                                                float makeupGain = .0f, EQType type = EQType::kBassEq)
{
//    int lowDataSize = 0;
//    auto* lowData = getBinaryDataWithOriginalFileName (lowBinFileName, lowDataSize);

//    int highDataSize = 0;
//    auto* highData = getBinaryDataWithOriginalFileName (highBinFileName, highDataSize);

    eq = mainProcessor->addNode(std::make_unique<EQWithIR>(soundSettingsModel.getCurrentSetting(), makeupGain, type));

    EQWithIR* eqIr = (EQWithIR*) eq->getProcessor();
    eqIr->eqValue = parameter;
    mainAudioProcessors.add(eq);
}

void AmpedAudioProcessor::initProcessor(Node::Ptr processor) {
    processor->getProcessor()->setPlayConfigDetails (AMPED_MONO_CHANNEL,
                                             AMPED_MONO_CHANNEL,
                                            getSampleRate(), getBlockSize());
}

void AmpedAudioProcessor::initialisePreEffectsGraph() {
    preEffectsProcessor->clear();
    preEffectsAudioProcessors.clear();

    audioInputPreEffectsNode  = preEffectsProcessor->addNode (std::make_unique<AudioGraphIOProcessor> (AudioGraphIOProcessor::audioInputNode));
    audioOutputPreEffectsNode = preEffectsProcessor->addNode (std::make_unique<AudioGraphIOProcessor> (AudioGraphIOProcessor::audioOutputNode));
    preEffectsMidiInputNode = preEffectsProcessor->addNode (std::make_unique<AudioGraphIOProcessor> (AudioGraphIOProcessor::midiInputNode));
    preEffectsMidiOutputNode  = preEffectsProcessor->addNode (std::make_unique<AudioGraphIOProcessor> (AudioGraphIOProcessor::midiOutputNode));

    noiseGateNode = preEffectsProcessor->addNode (std::make_unique<EffectsNGProcessor>(soundSettingsModel.getCurrentSetting()));
    EffectsNGProcessor* ngProcessor = (EffectsNGProcessor*) noiseGateNode->getProcessor();
    ngProcessor->thresholdParam = parameters.getRawParameterValue (VTS_EF_NG_THRESHOLD);
    preEffectsAudioProcessors.add(noiseGateNode);

    overdriveNode = preEffectsProcessor->addNode (std::make_unique<EffectsODProcessor>(soundSettingsModel.getCurrentSetting()));
    EffectsODProcessor* processor = (EffectsODProcessor*) overdriveNode->getProcessor();
    processor->driveParameter = parameters.getRawParameterValue (VTS_EF_OD_DRIVE);
    processor->toneParameter = parameters.getRawParameterValue (VTS_EF_OD_TONE);
    processor->levelParameter = parameters.getRawParameterValue (VTS_EF_OD_LEVEL);
    preEffectsAudioProcessors.add(overdriveNode);

    for (auto node : preEffectsAudioProcessors)
    {
        initProcessor(node);
    }

    connectPreEffectsMidiNodes();
    connectPreEffectsAudioNodes();

    for (auto node : preEffectsProcessor->getNodes())
        node->getProcessor()->enableAllBuses();
}

void AmpedAudioProcessor::connectPreEffectsAudioNodes()
{
    for (auto connection : preEffectsProcessor->getConnections())
        preEffectsProcessor->removeConnection (connection);

    for (int channel = 0; channel < AMPED_MONO_CHANNEL; ++channel) {
        preEffectsProcessor->addConnection ({ { audioInputPreEffectsNode->nodeID,  channel },
                { noiseGateNode->nodeID, channel } });
        preEffectsProcessor->addConnection ({ { noiseGateNode->nodeID,  channel },
                { overdriveNode->nodeID, channel } });
        preEffectsProcessor->addConnection ({ { overdriveNode->nodeID,  channel },
                { audioOutputPreEffectsNode->nodeID, channel } });
    }
}

FFAU::LevelMeterSource& AmpedAudioProcessor::getMeterSource()
{
    return meterSource;
}

void AmpedAudioProcessor::initialiseMainGraph() {
    auto curSetting = soundSettingsModel.getCurrentSetting();

    mainProcessor->clear();
    mainAudioProcessors.clear();

    audioInputNode  = mainProcessor->addNode (std::make_unique<AudioGraphIOProcessor> (AudioGraphIOProcessor::audioInputNode));
    audioOutputNode = mainProcessor->addNode (std::make_unique<AudioGraphIOProcessor> (AudioGraphIOProcessor::audioOutputNode));
    midiInputNode   = mainProcessor->addNode (std::make_unique<AudioGraphIOProcessor> (AudioGraphIOProcessor::midiInputNode));
    midiOutputNode  = mainProcessor->addNode (std::make_unique<AudioGraphIOProcessor> (AudioGraphIOProcessor::midiOutputNode));

    // Input gain:
  //  gainProcessor = mainProcessor->addNode (std::make_unique<GainProcessor>(soundSettings, GainProcessorId::InputGain));
  //  ((GainProcessor*)gainProcessor->getProcessor())->gainValue = inputParameter;
  //  mainAudioProcessors.add(gainProcessor);

    driveProcessor = mainProcessor->addNode (std::make_unique<GainProcessor>(soundSettingsModel.getCurrentSetting(), GainProcessorId::DriveGain));
    ((GainProcessor*)driveProcessor->getProcessor())->gainValue = driveParameter;
    mainAudioProcessors.add(driveProcessor);

    // Tube amp:
    ampProcessor = mainProcessor->addNode(std::make_unique<AmpProcessor>(soundSettingsModel.getCurrentSetting()));

    AmpProcessor* amp = (AmpProcessor*) ampProcessor->getProcessor();
    amp->masterParameter = masterParameter;
    amp->gainParameter = driveParameter;
    mainAudioProcessors.add(ampProcessor);

    // Bass eq:
    initEq(bassEq, curSetting->ampSettings.eqs[EQType::kBassEq].lowIrFileName,
                   curSetting->ampSettings.eqs[EQType::kBassEq].highIrFileName,
                   bassParameter, 6.50f, EQType::kBassEq);

    // Middle eq:
    initEq(middleEq, curSetting->ampSettings.eqs[EQType::kMiddleEq].lowIrFileName,
                     curSetting->ampSettings.eqs[EQType::kMiddleEq].highIrFileName,
            middleParameter, 6.5f, EQType::kMiddleEq);

    // Treble eq:
    initEq(trebleEq, curSetting->ampSettings.eqs[EQType::kTrebleEq].lowIrFileName,
            curSetting->ampSettings.eqs[EQType::kTrebleEq].highIrFileName,
            trebleParameter, 6.5f, EQType::kTrebleEq);
    
    // Depth eq:
   initEq(depthEq, curSetting->ampSettings.eqs[EQType::kDepthEq].lowIrFileName,
               curSetting->ampSettings.eqs[EQType::kDepthEq].highIrFileName,
               depthParameter, 6.5f, EQType::kDepthEq);

    // Presence eq:
    initEq(presenceEq,curSetting->ampSettings.eqs[EQType::kPresence].lowIrFileName,
            curSetting->ampSettings.eqs[EQType::kPresence].lowIrFileName,
            presenceParameter, 6.5f, EQType::kPresence);
    
    brightIR = mainProcessor->addNode(std::make_unique<BrightIR>(soundSettingsModel.getCurrentSetting()));
    mainAudioProcessors.add(brightIR);

    // Amp sim:
    ampSimIR = mainProcessor->addNode(std::make_unique<AmpIr>(soundSettingsModel.getCurrentSetting(), soundSettingsModel.getCurrentSetting()->ampSettings.ampIr.gain));
    mainAudioProcessors.add(ampSimIR);

    // Cab sim:
    cabSimIR = mainProcessor->addNode(std::make_unique<CabSimIr>(soundSettingsModel.getCurrentSetting(), soundSettingsModel.getCurrentSetting()->ampSettings.cabIr.gain));
    mainAudioProcessors.add(cabSimIR);

    outputGainProcessor = mainProcessor->addNode (std::make_unique<GainProcessor>(soundSettingsModel.getCurrentSetting(), GainProcessorId::OutputGain));
    ((GainProcessor*)outputGainProcessor->getProcessor())->gainValue = outputParameter;
    mainAudioProcessors.add(outputGainProcessor);
    
    for (auto node : mainAudioProcessors)
    {
        initProcessor(node);
    }

    connectMainAudioNodes();
    connectMidiNodes();



   // BusesLayout monoLayout;
   // monoLayout.inputBuses.add(AudioChannelSet::mono());
   // monoLayout.outputBuses.add(AudioChannelSet::mono());

   // mainProcessor->removeBus(true);
   // mainProcessor->removeBus(false);



   // mainProcessor->setBusesLayout(monoLayout);
    for (auto node : mainProcessor->getNodes())
        node->getProcessor()->enableAllBuses();
}

void AmpedAudioProcessor::connectMainAudioNodes()
{
    for (auto connection : mainProcessor->getConnections())
        mainProcessor->removeConnection (connection);

    for (int channel = 0; channel < AMPED_MONO_CHANNEL; ++channel) {
        mainProcessor->addConnection ({ { audioInputNode->nodeID,  channel },
            { driveProcessor->nodeID, channel } });
        mainProcessor->addConnection ({ { driveProcessor->nodeID,  channel },
            { ampProcessor->nodeID, channel } });
        mainProcessor->addConnection ({ { ampProcessor->nodeID,  channel },
            { ampSimIR->nodeID, channel } });
        mainProcessor->addConnection ({ { ampSimIR->nodeID,  channel },
            { bassEq->nodeID, channel } });
        mainProcessor->addConnection ({ { bassEq->nodeID,  channel },
            { middleEq->nodeID, channel } });
        mainProcessor->addConnection ({ { middleEq->nodeID,  channel },
            { trebleEq->nodeID, channel } });
        mainProcessor->addConnection ({ { trebleEq->nodeID,  channel },
            { depthEq->nodeID, channel } });
        mainProcessor->addConnection ({ { depthEq->nodeID,  channel },
           { presenceEq->nodeID, channel } });
        mainProcessor->addConnection ({ { presenceEq->nodeID,  channel },
            { brightIR->nodeID, channel } });
        mainProcessor->addConnection ({ { brightIR->nodeID,  channel },
              { cabSimIR->nodeID, channel } });
        mainProcessor->addConnection ({ { cabSimIR->nodeID,  channel },
            { outputGainProcessor->nodeID, channel } });
        mainProcessor->addConnection ({ { outputGainProcessor->nodeID,  channel },
            { audioOutputNode->nodeID, channel } });
    }
}

SoundSettingsModel& AmpedAudioProcessor::getSoundSettingsModel()
{
    return soundSettingsModel;
}

void AmpedAudioProcessor::connectMidiNodes()
{
    mainProcessor->addConnection ({ { midiInputNode->nodeID,  AudioProcessorGraph::midiChannelIndex },
        { midiOutputNode->nodeID, AudioProcessorGraph::midiChannelIndex } });
}

void AmpedAudioProcessor::connectPreEffectsMidiNodes()
{
    preEffectsProcessor->addConnection ({ { preEffectsMidiInputNode->nodeID,  AudioProcessorGraph::midiChannelIndex },
            { preEffectsMidiOutputNode->nodeID, AudioProcessorGraph::midiChannelIndex } });
}

void AmpedAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
  //  Logger::getCurrentLogger()->writeToLog("prepareToPlay in  UPDATE:  " + String(getTotalNumInputChannels()) + " out:" + String(getTotalNumOutputChannels()));



    if (previousPrepareSampleRate != (int) sampleRate ||
        previousPrepareSamplesPerBlock != samplesPerBlock)
    {
        previousPrepareSampleRate = (int) sampleRate;
        previousPrepareSamplesPerBlock = samplesPerBlock;
      //  Logger::getCurrentLogger()->writeToLog("prepareToPlay   ");
        if (getTotalNumInputChannels() < 1) {
            return;
        }
        preEffectsProcessor->setPlayConfigDetails (AMPED_MONO_CHANNEL,
                AMPED_MONO_CHANNEL,
                sampleRate, samplesPerBlock);

        mainProcessor->setPlayConfigDetails (AMPED_MONO_CHANNEL,
                AMPED_MONO_CHANNEL,
                sampleRate, samplesPerBlock);

        preEffectsProcessor->prepareToPlay (sampleRate, samplesPerBlock);
        mainProcessor->prepareToPlay (sampleRate, samplesPerBlock);

        initialisePreEffectsGraph();
        initialiseMainGraph();

        for (auto node : mainAudioProcessors) {
            ((AmpedAudioProcessorBase*)node->getProcessor())->updateInternalSettings(getCurrentSettings());
        }
    }
    initReverb(sampleRate);
    delay.prepareToPlay(sampleRate, samplesPerBlock, getTotalNumInputChannels(), getTotalNumOutputChannels());
}

void AmpedAudioProcessor::initReverb(const double sampleRate)
{
    reverb.reset();
    reverb.setSampleRate(sampleRate);
    reverbParams.width = 1.0;
}



//==============================================================================
void AmpedAudioProcessor::prepareToPlay_temp (double sampleRate, int samplesPerBlock)
{
  //  Logger::getCurrentLogger()->writeToLog("prepareToPlay   ");

    mainProcessor->setPlayConfigDetails (AMPED_MONO_CHANNEL,
                                         AMPED_MONO_CHANNEL,
                                         sampleRate, samplesPerBlock);

    mainProcessor->prepareToPlay (sampleRate, samplesPerBlock);
    initialiseMainGraph();




 //   void HoRNetGuitarKit::Reset()
 //   {
 //       TRACE;
     //   IMutexLock lock(this);

/*    tubeAmp.setSampleRate(sampleRate);
    tubeAmp.setOversample(1);
    tubeAmp.init();
    tubeAmp.setNumChans(2);





   // tubeAmp.setHighGainStageActive(true);
    tubeAmp.setInputType(PreAmp::EInputType::kGuitarKit);
    tubeAmp.setTubeType(0, TUBE_TABLE_12AX7_68k);
    tubeAmp.setTubeType(1, TUBE_TABLE_12AX7_68k);

    tubeAmp.setPowerAmpTubeType(TUBE_TABLE_6L6CG_68k );*/
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

    // Amp sim:
   // initInpulseResponseProcessor(BinaryData::MATCH_IR_FILTERED_wav, sampleRate, samplesPerBlock, BinaryData::MATCH_IR_FILTERED_wavSize, ampSim);

    // Cab sim:
   // initInpulseResponseProcessor(BinaryData::CAB_IR_FILTERED_wav, sampleRate, samplesPerBlock, BinaryData::CAB_IR_FILTERED_wavSize, cabSim);
}


void AmpedAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool AmpedAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    //Logger::getCurrentLogger()->writeToLog("isBusesLayoutSupported " + String((int)layouts.getMainInputChannelSet()) + " out:" + String((int)layouts.getMainOutputChannelSet()));

    if (layouts.getMainInputChannelSet()  == AudioChannelSet::disabled()
        || layouts.getMainOutputChannelSet() == AudioChannelSet::disabled())
        return false;

    if (layouts.getMainInputChannelSet() == AudioChannelSet::stereo()
            && layouts.getMainOutputChannelSet() == AudioChannelSet::stereo())
        return true;

    if (layouts.getMainInputChannelSet() == AudioChannelSet::mono()
            && layouts.getMainOutputChannelSet() == AudioChannelSet::stereo())
        return true;

    if (layouts.getMainInputChannelSet() == AudioChannelSet::mono()
            && layouts.getMainOutputChannelSet() == AudioChannelSet::mono())
        return true;

    return false;


 //   if (layouts.getMainInputChannelSet() == AudioChannelSet::mono() &&
 //       layouts.getMainOutputChannelSet() == AudioChannelSet::mono()) {
 //           return true;
 //   }

    // Support mono in and mono or stereo out only:
  /*  if (layouts.getMainInputChannelSet() == AudioChannelSet::mono() &&
        (layouts.getMainOutputChannelSet() == AudioChannelSet::mono() ||
         layouts.getMainOutputChannelSet() == AudioChannelSet::stereo())){
        return true;
    }*/
    return false;
/*  #if JucePlugin_IsMidiEffect
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
 */
}
#endif

inline void AmpedAudioProcessor::processInputGain(AudioBuffer<float>& buffer) {

    MaxMin maxMin = soundSettingsModel.getCurrentSetting()->gainSettings[InputGain];
    float scaledGain = (maxMin.max - maxMin.min) * *inputParameter + maxMin.min;
    float inputGainInDb = Decibels::decibelsToGain<float>(scaledGain,  maxMin.min);
  //  Logger::getCurrentLogger()->writeToLog("Scaled: " + String(scaledGain) + "gainInDb: " + String(inputGainInDb));
    buffer.applyGain(inputGainInDb);
}

void AmpedAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
   // Logger::getCurrentLogger()->writeToLog("EQ: B:" +  String(*bassParameter) + " M: "+String(*middleParameter) + " T:"+String(*trebleParameter) + " PR:" + String(*presenceParameter));

    // If we have more outputchannels than input channels we must clear them, they might contain garbage.
    for (int i = getTotalNumInputChannels(); i < getTotalNumOutputChannels(); ++i)
    {
        buffer.clear (i, 0, buffer.getNumSamples());
    }

    float* monoPointer[1];

    auto switchToRightInput = *leftRightInputSwitch > 0.5 && buffer.getNumChannels() > 1;
    // Here we do the switch between left / right on standalone version
    if (switchToRightInput)
    {
        monoPointer[0] = buffer.getWritePointer(1);
    }
    else
    {
        monoPointer[0] = buffer.getWritePointer(0);
    }

    AudioBuffer<float> monoBuffer(monoPointer, 1, buffer.getNumSamples());

    processInputGain(monoBuffer);
    meterSource.measureBlock (monoBuffer);

    noiseGateNode->setBypassed(*effects_ng_switch < .5);
    overdriveNode->setBypassed(*effects_od_switch < .5);

   // cabSimIR->setBypassed(*cabSimSwitch > .5);

  //  Logger::getCurrentLogger()->writeToLog("Status: " +  String(*cabSimSwitch));
    cabSimIR->setBypassed(((int)*cabSimSwitch) == ThreeWayIRFileSwitch::SwitchStatus::IROff);


#ifdef AMPED_DEBUG
    ampSimIR->setBypassed(*ampSimSwitch > .5);
#endif

    brightIR->setBypassed(*bright > .5);
    
    
    if (copyProtection) buffer.clear();

    if (*fxParameter < 0.5) {
        preEffectsProcessor->processBlock(monoBuffer, midiMessages);
        if (copyProtection) buffer.clear();
    }
    mainProcessor->processBlock (monoBuffer, midiMessages);

    // We copy the mono (left) channel to right channel also:
    if (buffer.getNumChannels() > 1) {
        if (switchToRightInput) {
            buffer.copyFrom (0, 0, monoBuffer.getReadPointer(0), monoBuffer.getNumSamples());
        }
        buffer.copyFrom (1, 0, monoBuffer.getReadPointer(0), monoBuffer.getNumSamples());
    }
    
    if (*dlyOnOffParameter < 0.5) {
        delay.mMix = dlyMixParameter;
        delay.mFeedback = dlyFeedbackParameter;
        delay.mTime = dlyTimeParameter;

        delay.processBlock(buffer);
    }
    
    if (*fxParameter < 0.5) {
        processReverb(buffer);
    }

    if (copyProtection) buffer.clear();
    /*
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
*/


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

void AmpedAudioProcessor::processReverb(AudioBuffer<float>& buffer)
{
    if (*reverbOnOffParameter > .5)
    {
        reverbParams.damping = fabs(*reverbToneParameter - 1.0f);
        reverbParams.roomSize = *reverbSizeParameter;
        // Make scale to 0 to 0.5 scale:
        reverbParams.wetLevel = *reverbMixParameter * 0.5f;
        reverbParams.dryLevel = 0.5f - reverbParams.wetLevel;

        // Logger::getCurrentLogger()->writeToLog("processReverb WLev " + String(reverbParams.wetLevel) + " DLev:" + String(reverbParams.dryLevel));

        reverb.setParameters(reverbParams);

        if (buffer.getNumChannels() > 1) {
            reverb.processStereo(buffer.getWritePointer(0), buffer.getWritePointer(1),buffer.getNumSamples());
        }
        else {
            reverb.processMono(buffer.getWritePointer(0),buffer.getNumSamples());
        }
    }
}

// You should use this method to store your parameters in the memory block.
// You could do that either as raw data, or use the XML or ValueTree classes
// as intermediaries to make it easy to save and load complex data.
void AmpedAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    auto state = parameters.copyState();
    std::unique_ptr<XmlElement> xml (state.createXml());

    int ampNr = soundSettingsModel.currentSettingIndex();
    xml->setAttribute("AmpNr", ampNr);

    int presetNr = soundSettingsModel.getCurrentSetting()->getCurrentPresetIndex();
    xml->setAttribute("presetNr", presetNr);

    xml->deleteAllChildElementsWithTagName("CustomCabIr");
    if (getCurrentSettings()->ampSettings.cabIr.overridingIrFileName.length() > 0) {
        xml->createNewChildElement("CustomCabIr")->setAttribute("fileName", getCurrentSettings()->ampSettings.cabIr.overridingIrFileName);
    }
    copyXmlToBinary (*xml, destData);
}

// You should use this method to restore your parameters from this memory block,
// whose contents will have been created by the getStateInformation() call.
void AmpedAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
 //   Logger::getCurrentLogger()->writeToLog("setStateInformation");

    std::unique_ptr<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    if (xmlState.get() != nullptr)
    {
        if (xmlState->hasAttribute("AmpNr")) {
            int ampIndex = xmlState->getIntAttribute("AmpNr", 0);
            if (! LicenceTools::getInstance()->isValidLicence())
            {
                ampIndex = 0;
            }

            int presetIndex = -1;
            if (xmlState->hasAttribute("presetNr")) {
                presetIndex = xmlState->getIntAttribute("presetNr", -1);
            }

            soundSettingsModel.selectSettingWithIndex(ampIndex);
            if (presetIndex != -1)
                soundSettingsModel.getCurrentSetting()->setCurrentPresetWithIndex(presetIndex);
        }

        if (xmlState->hasTagName (parameters.state.getType()))
            parameters.replaceState (ValueTree::fromXml (*xmlState));

        auto element = xmlState->getChildByName("CustomCabIr");
        if (element != nullptr)
        {
            auto fileName = xmlState->getChildByName("CustomCabIr")->getStringAttribute("fileName", "");
            if (!File(fileName).exists()) {
                AlertWindow::showMessageBox(AlertWindow::AlertIconType::WarningIcon,"File not found", "Cabinet IR file. Using default instead." + fileName + " not found.", "OK", nullptr);
            }
            else {
                getCurrentSettings()->ampSettings.cabIr.overridingIrFileName = fileName;
            }
        }
    }
    auto editor = getActiveEditor();
    if (editor != nullptr)
       {
           ((AmpedAudioProcessorEditor*)editor)->updateAmpPresetUi();
           editor->repaint();
       }
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

void AmpedAudioProcessor::nextSetting()
{
    soundSettingsModel.nextSetting();
    settingChanged();
}

void AmpedAudioProcessor::prevSetting()
{
    soundSettingsModel.prevSetting();
    settingChanged();
}

void AmpedAudioProcessor::selectSettingWithId(int ampIndex) {
    soundSettingsModel.selectSettingWithIndex(ampIndex);
    settingChanged();
}

void AmpedAudioProcessor::selectPresetWithId(int index) {
    soundSettingsModel.getCurrentSetting()->setCurrentPresetWithIndex(index);
    presetChanged();
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AmpedAudioProcessor();
}


/*

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
*/
