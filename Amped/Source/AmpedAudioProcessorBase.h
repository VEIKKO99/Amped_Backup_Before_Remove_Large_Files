/*
  ==============================================================================

    AmpedAudioProcessorBase.h
    Created: 3 Oct 2019 2:27:21pm
    Author:  Veikko Tapaninen

  ==============================================================================
*/

#include "AmpedDsp.h"
#include "AdminSettingsUtil.h"
#include "Consts.h"
#include "Effects/HTS9/TS9.h"
#include "Effects/CompExp/CompExp.h"

#pragma once

using Convolution = juce::dsp::Convolution;

class AmpedMonoAudioGraph : public AudioProcessorGraph {
public:
    AmpedMonoAudioGraph() : AudioProcessorGraph() {
        BusesLayout defaultLayout = getBusesLayout();
    //    defaultLayout.outputBuses[0] = AudioChannelSet::mono();
    //    defaultLayout.inputBuses[0] = AudioChannelSet::mono();
    //    defaultLayout.
    //    defaultLayout.inputBuses.clear();
    //    defaultLayout.outputBuses.clear();
    //    defaultLayout.inputBuses.add(AudioChannelSet::mono());
    //    defaultLayout.outputBuses.add(AudioChannelSet::mono());

        /*
        busArrangement.inputBuses.clear();
        busArrangement.outputBuses.clear();
        if (type == audioOutputNode)
            busArrangement.inputBuses.add  (AudioProcessorBus ("Input",  AudioChannelSet::canonicalChannelSet(numOuts) ));
        if (type == audioInputNode)
            busArrangement.outputBuses.add (AudioProcessorBus ("Output", AudioChannelSet::canonicalChannelSet(numIns) ));
            */
    }
/*
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override {
        if (layouts.getMainInputChannelSet() == AudioChannelSet::disabled()
                || layouts.getMainOutputChannelSet() == AudioChannelSet::disabled())
            return false;

        if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono())
            return false;

        return layouts.getMainInputChannelSet() == layouts.getMainOutputChannelSet();
    }*/
};

//==============================================================================
class AmpedAudioProcessorBase  : public AudioProcessor
{
public:
    //==============================================================================
    AmpedAudioProcessorBase(std::shared_ptr<SoundSettings> settings) : AudioProcessor (BusesProperties()
                                                                 .withInput("Input", AudioChannelSet::mono(), false)
                                                                 .withOutput ("Output", AudioChannelSet::mono(), true))
    {
        this->soundSettings = settings;
    }
    
//==============================================================================
    void prepareToPlay (double, int) override {}
    void releaseResources() override {}
    void processBlock (AudioSampleBuffer&, MidiBuffer&) override {}
    
    //==============================================================================
    AudioProcessorEditor* createEditor() override          { return nullptr; }
    bool hasEditor() const override                        { return false; }
    
    //==============================================================================
    const String getName() const override                  { return {}; }
    bool acceptsMidi() const override                      { return false; }
    bool producesMidi() const override                     { return false; }
    double getTailLengthSeconds() const override           { return 0; }
    
    //==============================================================================
    int getNumPrograms() override                          { return 0; }
    int getCurrentProgram() override                       { return 0; }
    void setCurrentProgram (int) override                  {}
    const String getProgramName (int) override             { return {}; }
    void changeProgramName (int, const String&) override   {}


    bool isBusesLayoutSupported (const BusesLayout& layouts) const override {
     //   if (layouts.getMainInputChannelSet() == AudioChannelSet::disabled()
     //           || layouts.getMainOutputChannelSet() == AudioChannelSet::disabled())
     //       return false;

 //       if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono())
 //           return false;

 //       return layouts.getMainInputChannelSet() == layouts.getMainOutputChannelSet();
      /*  juce::Logger::getCurrentLogger()->writeToLog("##### printing layouts #####");

        for (auto input: layouts.inputBuses) {
            juce::Logger::getCurrentLogger()->writeToLog("INPUT: "+ input.getDescription());
        }
        for (auto input: layouts.outputBuses) {
            juce::Logger::getCurrentLogger()->writeToLog("OUTPUT: "+ input.getDescription());
        }*/

 return true;
    }

        //==============================================================================
    void getStateInformation (MemoryBlock&) override       {}
    void setStateInformation (const void*, int) override   {}
    
    virtual void updateInternalSettings(std::shared_ptr<SoundSettings> settings) {
        this->soundSettings = settings;
    }

    // THis method returns the 1 because we want to process the signal
    // as mono signal as long as possible to save resources.

    int getAmpedInputChannelCount() {
     //   juce::Logger::getCurrentLogger()->writeToLog("processor graph: getTotalNumInputChannels: " + String(getTotalNumInputChannels()));

        if (getTotalNumInputChannels() > 0) {
            return 1;
        }
        return getTotalNumInputChannels();
    }

protected:
    
    std::shared_ptr<SoundSettings> soundSettings = nullptr;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AmpedAudioProcessorBase)
};

class AmpSimWrapperBase  : public AmpedAudioProcessorBase {

protected:

    AmpSimWrapperBase(std::shared_ptr<SoundSettings> settings): AmpedAudioProcessorBase(settings),
                                                                interleavedBuffer(new double[INTERLEAVED_DEFAULT_SIZE])
    {
    }

    void interleaveAndConvertSamples (float** source, double* dest, int numSamples, int numChannels)
    {
        for (int chan = 0; chan < numChannels; ++chan)
        {
            auto i = chan;
            auto src = source [chan];

            for (int j = 0; j < numSamples; ++j)
            {
                dest [i] = (double)src [j];
                i += numChannels;
            }
        }
    }

    void deinterleaveAndConvertSamples (double* source, float** dest, int numSamples, int numChannels)
    {
        for (int chan = 0; chan < numChannels; ++chan)
        {
            auto i = chan;
            auto dst = dest [chan];

            for (int j = 0; j < numSamples; ++j)
            {
                dst [j] = static_cast<float>(source [i]);
                i += numChannels;
            }
        }
    }

    // 8192 should be enough
    std::unique_ptr<double[]> interleavedBuffer;
    static const int INTERLEAVED_DEFAULT_SIZE = 8192 * 2; // Two channels, 8192 samples

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AmpSimWrapperBase)

};


class EffectsNGProcessor  : public AmpSimWrapperBase {

public:
    EffectsNGProcessor(std::shared_ptr<SoundSettings> settings) : AmpSimWrapperBase(settings) {
    }

    void updateInternalSettings(std::shared_ptr<SoundSettings> settings) override {
        AmpSimWrapperBase::updateInternalSettings(settings);
    }

    void prepareToPlay (double sampleRate, int samplesPerBlock) override
    {
        int numOfChannels = getTotalNumInputChannels();

        // If 8192 *"  samples are not enough, re-init the buffer.
        // Todo: This might not be thread safe.
        if (samplesPerBlock * getTotalNumInputChannels() > INTERLEAVED_DEFAULT_SIZE)
        {
            interleavedBuffer.reset(new double[samplesPerBlock * getTotalNumInputChannels()]);
        }
        effect.init(sampleRate);
        effect.SetMode(CompExp::ECompMode::kExp);
        effect.SetAttack(1.0);
        effect.SetRelease(50.0);
    }

    void processBlock (AudioSampleBuffer& buffer, MidiBuffer&) override
    {
        int numOfSamples = buffer.getNumSamples();
        int numOfChannels = buffer.getNumChannels();

        interleaveAndConvertSamples(buffer.getArrayOfWritePointers(), interleavedBuffer.get(), numOfSamples, numOfChannels);

        // Values from 1 to 5
        effect.SetRatio(1 + (*thresholdParam * 4));
        effect.Process(interleavedBuffer.get(), numOfSamples);
        //  tubeAmp.process(interleavedBuffer.get(), numOfSamples);

        deinterleaveAndConvertSamples(interleavedBuffer.get(), buffer.getArrayOfWritePointers(),
                numOfSamples, numOfChannels);
    }

public:
    float* thresholdParam = nullptr;

private:
    CompExp effect;

    // TubeAmp tubeAmp;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EffectsNGProcessor)
};

class EffectsODProcessor  : public AmpSimWrapperBase
{

public:
    EffectsODProcessor(std::shared_ptr<SoundSettings> settings): AmpSimWrapperBase(settings)
    {
    }

    void updateInternalSettings(std::shared_ptr<SoundSettings> settings) override {
        AmpSimWrapperBase::updateInternalSettings(settings);
    }

    void prepareToPlay (double sampleRate, int samplesPerBlock) override
    {
        int numOfChannels = getTotalNumInputChannels();

        // If 8192 *"  samples are not enough, re-init the buffer.
        // Todo: This might not be thread safe.
        if (samplesPerBlock * getTotalNumInputChannels() > INTERLEAVED_DEFAULT_SIZE)
        {
            interleavedBuffer.reset(new double[samplesPerBlock * getTotalNumInputChannels()]);
        }
        effect.setSampleRate(sampleRate);
        effect.setNumChans(getTotalNumInputChannels());
        effect.setHiss(false);
    }

    void processBlock (AudioSampleBuffer& buffer, MidiBuffer&) override
    {
        int numOfSamples = buffer.getNumSamples();
        int numOfChannels = buffer.getNumChannels();

        interleaveAndConvertSamples(buffer.getArrayOfWritePointers(), interleavedBuffer.get(), numOfSamples, numOfChannels);

        effect.setTone(*toneParameter);
        effect.setLevel((*levelParameter) / 10.0f);
        effect.setDistAmp(*driveParameter);

        effect.process(interleavedBuffer.get(), numOfSamples);
      //  tubeAmp.process(interleavedBuffer.get(), numOfSamples);

        deinterleaveAndConvertSamples(interleavedBuffer.get(), buffer.getArrayOfWritePointers(),
                numOfSamples, numOfChannels);
    }

    void reset() override
    {
    }

    const String getName() const override { return "Effects_OD"; }

public:

    float* driveParameter = nullptr;
    float* toneParameter = nullptr;
    float* levelParameter = nullptr;

private:

    ts9 effect;
   // TubeAmp tubeAmp;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EffectsODProcessor)

};


//==============================================================================
class GainProcessor  : public AmpedAudioProcessorBase
{
public:
    GainProcessor(std::shared_ptr<SoundSettings> settings, GainProcessorId id) : AmpedAudioProcessorBase(settings)
    {
        gain.setGainDecibels (.0f);
        processorId = id;
    }
    
    void prepareToPlay (double sampleRate, int samplesPerBlock) override
    {
        int numOfChannels = getAmpedInputChannelCount();
        dsp::ProcessSpec spec { sampleRate, static_cast<uint32> (samplesPerBlock),  static_cast<uint32>(numOfChannels)};
        gain.prepare (spec);
    }
    
    void processBlock (AudioSampleBuffer& buffer, MidiBuffer&) override
    {
        dsp::AudioBlock<float> block (buffer);
        dsp::ProcessContextReplacing<float> context (block);
       
        float scaledGain = (gainMax - gainMin) * *gainValue + gainMin;
        
        gain.setGainDecibels(scaledGain);
        gain.process (context);
    }
    
    void reset() override
    {
        gain.reset();
    }

    void updateInternalSettings(std::shared_ptr<SoundSettings> settings) override {
        AmpedAudioProcessorBase::updateInternalSettings(settings);
        gainMin = soundSettings->gainSettings[processorId].min;
        gainMax = soundSettings->gainSettings[processorId].max;
    }

    const String getName() const override { return "Input Gain"; }
    
public:
    float* gainValue = NULL;
    float gainMin = -24;
    float gainMax = 24;

private:
    dsp::Gain<float> gain;
    GainProcessorId processorId;
   
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GainProcessor)
};

class IRProcessor : public AmpedAudioProcessorBase
{
public:
    IRProcessor(std::shared_ptr<SoundSettings> settings, float makeupGain = .0f):
                AmpedAudioProcessorBase(settings)
    {
        this->makeupGain = makeupGain;
    }
    
    void prepareToPlay (double sampleRate, int samplesPerBlock) override
    {
        Logger::getCurrentLogger()->writeToLog("IRProcessor prepareToPlay");
        lastKnownSampleRate = sampleRate;
        // Sometime Juce AudioGraph calls this method with 0 samplerate.
        if ((int)lastKnownSampleRate  > 0)
            initInpulseResponseProcessor(sampleRate, samplesPerBlock);
    }
    
    void processBlock (AudioSampleBuffer& buffer, MidiBuffer&) override
    {
        dsp::AudioBlock<float> block(buffer);
        dsp::ProcessContextReplacing<float> context (block);
//        context.isBypassed = false;
        convolutionDsp.process(context);
        buffer.applyGain(makeupGain + 1.0f);
    }
    
    void reset() override
    {
        convolutionDsp.reset();
    }
    
    const String getName() const override { return "IR"; }

    void loadIRFile() {
        // Load only if sample rate is valid:
        if ((int)lastKnownSampleRate  <= 0) return;
        if (usedIR.startsWith("memory:")) {
            int dataSize = 0;
            auto data = getBinaryDataWithOriginalFileName(usedIR, dataSize, lastKnownSampleRate);
            convolutionDsp.loadImpulseResponse(data, dataSize, false, false, 0);
            convolutionDsp.reset();
        }
        else {
            File irData(usedIR);
            
            // Just to check if file input stream is valid. Juce convolution goes crazy (forever loop) if
            // Stream is not ok (For example no permission in OS X)
            auto stream = new FileInputStream(irData);
            auto isOk = stream->openedOk();
            delete stream;

            if (isOk) {
                convolutionDsp.loadImpulseResponse(irData, false, false, 0);
                if (initDone) convolutionDsp.reset();
            }
        }
    }
    
private:
    void initInpulseResponseProcessor(double sampleRate, int samplesPerBlock)
    {
        int numOfChannels = getTotalNumInputChannels();
        dsp::ProcessSpec spec { sampleRate, static_cast<uint32> (samplesPerBlock), static_cast<uint32>(numOfChannels)};
        convolutionDsp.prepare(spec);
        loadIRFile();
        convolutionDsp.reset();
        initDone = true;
    }
    
protected:
    
    float makeupGain = .0f;
    
protected:
    String usedIR;

private:
    Convolution convolutionDsp;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IRProcessor)
    bool initDone = false;
    double lastKnownSampleRate = 0.0;
};


class CabSimIr : public IRProcessor
{
public:
    CabSimIr(std::shared_ptr<SoundSettings> settings, float makeupGain = .0f):
            IRProcessor(settings, makeupGain)
    {
        setupCabIRFile();
    }

    void updateInternalSettings(std::shared_ptr<SoundSettings> settings) override {
        IRProcessor::updateInternalSettings(settings);
        setupCabIRFile();
        makeupGain = soundSettings->ampSettings.cabIr.gain;
    }

    void setupCabIRFile() {
        if (soundSettings->ampSettings.cabIr.overridingIrFileName.length() > 0) {
            usedIR = soundSettings->ampSettings.cabIr.overridingIrFileName;
            loadIRFile();
           // loadIRFile(soundSettings->ampSettings.cabIr.overridingIrFileName);
            //Logger::getCurrentLogger()->writeToLog("setupCabIRFile: " +  soundSettings->ampSettings.cabIr.overridingIrFileName);
        }
        else {
            usedIR = soundSettings->ampSettings.cabIr.irFileName;
            loadIRFile();
        //    Logger::getCurrentLogger()->writeToLog("setupCabIRFile: " +  soundSettings->ampSettings.cabIr.irFileName);
            //loadIRFile(soundSettings->ampSettings.cabIr.irFileName);
        }
    }
};

class AmpSimIr : public IRProcessor
{
public:
    AmpSimIr(std::shared_ptr<SoundSettings> settings, float makeupGain = .0f):
            IRProcessor(settings, makeupGain)
    {
        loadIRFile();
    }

    void updateInternalSettings(std::shared_ptr<SoundSettings> settings) override {
        IRProcessor::updateInternalSettings(settings);
        usedIR = soundSettings->ampSettings.ampIr.irFileName;
        loadIRFile();
       // loadIRFile(soundSettings->ampSettings.ampIr.irFileName);
        makeupGain = soundSettings->ampSettings.ampIr.gain;
    }
};



class AmpProcessor  : public AmpSimWrapperBase
{

public:
    AmpProcessor(std::shared_ptr<SoundSettings> settings): AmpSimWrapperBase(settings)
    {
    }

    void updateTubeSettings(TubeSettings& source, TubeStage& destination)
    {
        destination.setRK(source.rk);
        destination.setVk0(source.vk0);
        destination.setVPlus(source.vPlus);
        destination.setLowPassFbk(source.lowPassFbk);
        destination.setRP(source.rp);
    }

    void updateInternalSettings(std::shared_ptr<SoundSettings> settings) override {
        AmpSimWrapperBase::updateInternalSettings(settings);
        // Input type (mesa, marshall etc)
        tubeAmp.setInputType(soundSettings->ampSettings.inputType);

        // Power amp:
        tubeAmp.setPowerAmpTubeType(soundSettings->ampSettings.powerAmpTube.tubeType); // This will set the type for both tubes.
        updateTubeSettings(soundSettings->ampSettings.powerAmpTube, tubeAmp.mPowerAmp[0]);
        updateTubeSettings(soundSettings->ampSettings.powerAmpTube, tubeAmp.mPowerAmp[1]);

        for (int i = 0; i < soundSettings->ampSettings.amountOfPreAmpTubes; i++) {
            updateTubeSettings(soundSettings->ampSettings.preAmpTubes[i], tubeAmp.mPreAmp.tubeStage[i]);
            tubeAmp.setTubeType(0, soundSettings->ampSettings.preAmpTubes[i].tubeType);
        }
        tubeAmp.setAmountOfPreampTubesInUse(soundSettings->ampSettings.amountOfPreAmpTubes);

        //tubeAmp.setOversample(soundSettings->ampSettings.overSample);
        drive = soundSettings->ampSettings.hornetDrive;
        presence = soundSettings->ampSettings.hornetPresence;

        setupAmp();
    }

  //  int mPrevSampleRate = -1;
    void prepareAmp(double sampleRate, int numOfChannels)
    {
            tubeAmp.setSampleRate(sampleRate);

            // We don't want to oversample higher samplerates so much...
            double oversampleMultiplier = 1.0;
            if (sampleRate <= 96000.0 && sampleRate > 48000.0) oversampleMultiplier = 0.5;
            if (sampleRate > 96000.0) oversampleMultiplier = 0.25;

            //Logger::getCurrentLogger()->writeToLog("setting oversample to: " + String(soundSettings->ampSettings.overSample * oversampleMultiplier));

            tubeAmp.setOversample(soundSettings->ampSettings.overSample * oversampleMultiplier);
            tubeAmp.init();
            tubeAmp.setNumChans(1);

            updateInternalSettings(soundSettings);
    }
    
    void prepareToPlay (double sampleRate, int samplesPerBlock) override
    {
        int numOfChannels = getTotalNumInputChannels();
        
        // If 8192 *"  samples are not enough, re-init the buffer.
        // Todo: This might not be thread safe.
        if (samplesPerBlock * getTotalNumInputChannels() > INTERLEAVED_DEFAULT_SIZE)
        {
            interleavedBuffer.reset(new double[samplesPerBlock * getTotalNumInputChannels()]);
        }
        prepareAmp(sampleRate, numOfChannels);
    }
    
    void setupAmp() {

   //     float gainMax = soundSettings->gainSettings[GainProcessorId::DriveGain].max;
   //     float gainMin = soundSettings->gainSettings[GainProcessorId::DriveGain].min;

    //    float scaledDrive = (gainMax - gainMin) * *driveParameter + gainMin;

        tubeAmp.setPreGain(drive);
        tubeAmp.setMasterVolume(*masterParameter);
        tubeAmp.setPresence(presence);
        
        tubeAmp.setDryWet(1.0);
        tubeAmp.setToneStackActive(false);
        tubeAmp.setHighGainStageActive(true);
      //  tubeAmp.setOversample(8);
    }
    
    void processBlock (AudioSampleBuffer& buffer, MidiBuffer&) override
    {
        int numOfSamples = buffer.getNumSamples();
        int numOfChannels = buffer.getNumChannels();
        
        interleaveAndConvertSamples(buffer.getArrayOfWritePointers(), interleavedBuffer.get(), numOfSamples, numOfChannels);

        tubeAmp.setMasterVolume(*masterParameter * soundSettings->ampSettings.masterVolumeMultiplier);
        tubeAmp.process(interleavedBuffer.get(), numOfSamples);
        
        deinterleaveAndConvertSamples(interleavedBuffer.get(), buffer.getArrayOfWritePointers(),
                                                 numOfSamples, numOfChannels);
    }
    
    void reset() override
    {
    }
    
    const String getName() const override { return "Amp"; }
    
public:
    
    float* fxParameter = nullptr;
    float drive = 0.5f;
    float presence = 0.5f;
    float* masterParameter = nullptr;
    float* outputParameter = nullptr;

private:
    
    TubeAmp tubeAmp;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AmpProcessor)

};

class EQWithIR: public AmpedAudioProcessorBase
{
public:
    
    EQWithIR(/*const char *lowPotImpulseData, int lowPotImpulseDataSize,
             const char *highPotImpulseData, int highPotImpulseDataSize,*/
             std::shared_ptr<SoundSettings> settings,
             float makeupGain = .0f,
             EQType eqType = kBassEq) : AmpedAudioProcessorBase(settings)
    {
        this->eqType = eqType;
     /*   this->loImpulseData = lowPotImpulseData;
        this->loImpulseDataSize = lowPotImpulseDataSize;
        
        this->hiImpulseData = highPotImpulseData;
        this->hiImpulseDataSize = highPotImpulseDataSize;*/
        this->makeupGain = makeupGain;
    }
    ~EQWithIR() = default;

    void loadIRFile(String irFile, Convolution& convolution) {
        if (irFile.startsWith("memory:")) {
            int dataSize = 0;
            //auto data = getBinaryDataWithOriginalFileName(irFile, dataSize);
            auto data = getBinaryDataWithOriginalFileName(irFile, dataSize, lastKnownSampleRate);
            if (data != nullptr) {
                convolution.loadImpulseResponse(data, dataSize, false, false, 0);
            }
            else {
                 Logger::getCurrentLogger()->writeToLog("ERROR in EQ settings");
            }
        }
        else {
            File irData(irFile);
            convolution.loadImpulseResponse(irData, false, false, 0);
        }
        convolution.reset();
    }

    void updateInternalSettings(std::shared_ptr<SoundSettings> settings) override {
        AmpedAudioProcessorBase::updateInternalSettings(settings);
        EQSettings& eqSettings = soundSettings->ampSettings.eqs[eqType];

        if (initDone) {
            if (eqSettings.highIrFileName.length()  > 0) {
                loadIRFile(eqSettings.highIrFileName, higherPotValues);
            }
            if (eqSettings.lowIrFileName.length() > 0) {
                loadIRFile(eqSettings.lowIrFileName, lowerPotValues);
            }
        }
        makeupGain = eqSettings.gain;
        realisticEqGain = eqSettings.realisticGain;
    }

    void prepareToPlay(double sampleRate, int samplesPerBlock) override
    {
        lastKnownSampleRate = sampleRate;
        int numOfChannels = getTotalNumInputChannels();
        dsp::ProcessSpec spec { sampleRate, static_cast<uint32> (samplesPerBlock), static_cast<uint32>(numOfChannels)};
        dryWet.prepare(spec);
        
        EQSettings& eqSettings = soundSettings->ampSettings.eqs[eqType];
        initInpulseResponseProcessor(eqSettings.lowIrFileName, sampleRate, samplesPerBlock, lowerPotValues );
        initInpulseResponseProcessor(eqSettings.highIrFileName, sampleRate, samplesPerBlock, higherPotValues );
    }
    
    void processBlock (AudioSampleBuffer& buffer, MidiBuffer&) override
    {
        dryWet.setDryBuffer(buffer);
        dsp::AudioBlock<float> block(buffer);
        dsp::ProcessContextReplacing<float> context (block);
        float dryWetValue = fabs(*eqValue * 2 - 1);
        dryWet.dryGainParam = dryWetValue;
    //    Logger::getCurrentLogger()->writeToLog("DryWetValue: " +  String(dryWetValue));
        if (*eqValue < 0.5)
            lowerPotValues.process(context);
        else
            higherPotValues.process(context);
        buffer.applyGain(makeupGain + *eqValue * realisticEqGain);
        
        dryWet.process(context);
    }
    
    void reset() override
    {
        dryWet.reset();
        lowerPotValues.reset();
        higherPotValues.reset();
    }

private:
    void initInpulseResponseProcessor(String irFileName, double sampleRate, int samplesPerBlock, Convolution& convolution )
    {
        int numOfChannels = getTotalNumInputChannels();
        dsp::ProcessSpec spec { sampleRate, static_cast<uint32> (samplesPerBlock), static_cast<uint32>(numOfChannels)};
        convolution.prepare(spec);
        initDone = true;
        //convolution.loadImpulseResponse(data, dataSize, false, false, 0, true);
        loadIRFile(irFileName, convolution);
        convolution.reset();
    }
    
public:
    float* eqValue = nullptr;

private:
    DryWetDsp dryWet;
    Convolution lowerPotValues;
    Convolution higherPotValues;
    
  //  const char *hiImpulseData = nullptr;
  //  int hiImpulseDataSize = 0;
    
  //  const char *loImpulseData = nullptr;
  //  int loImpulseDataSize = 0;

    float makeupGain = .0f;
    float realisticEqGain = .0f;
    
    double lastKnownSampleRate = 0.0;

    EQType eqType;
    bool initDone = false;
};

//
//class EQWithIR :public AmpedAudioProcessorBase
//{
//public:
//
//    EQWithIR()
//    {
//        impulseResponseBuffer.setSize (1, maxIRSampleSize, false, false, true);
//    };
//    ~EQWithIR() = default;
//
//    void prepareToPlay (double sampleRate, int samplesPerBlock) override
//    {
//        int numOfChannels = getTotalNumInputChannels();
//        dsp::ProcessSpec spec { sampleRate, static_cast<uint32> (samplesPerBlock), static_cast<uint32>(numOfChannels)};
//        dryWet.prepare(spec);
//   //     lowPotFIR.state = dsp::IIR::Coefficients<float>::makeHighPass(sampleRate, 5000.0);
//
//        lowPotFIR.prepare(spec);
//        highPotFIR.prepare(spec);
//
//
//        //BinaryData::MATCHIR_wav, BinaryData::MATCHIR_wavSize
//
//
//        if (! (copyAudioStreamInAudioBuffer (new MemoryInputStream (BinaryData::MATCHIR_wav, /*(size_t)*/ BinaryData::MATCHIR_wavSize, false))))
//        {
//            Logger::getCurrentLogger()->writeToLog("EQWithIR::copyAudioStreamInAudioBuffer fails");
//        }
//
//    }
//
//
//    /** Converts the data from an audio file into a stereo audio buffer of floats, and
//     performs resampling if necessary.
//     */
//    bool copyAudioStreamInAudioBuffer (InputStream* stream)
//    {
//        AudioFormatManager manager;
//        manager.registerBasicFormats();
//
//        std::unique_ptr<AudioFormatReader> formatReader (manager.createReaderFor(stream));
//        if (formatReader != nullptr)
//        {
//            int numOfChannels = formatReader->numChannels;
//            if (numOfChannels != 1) {
//                Logger::getCurrentLogger()->writeToLog("EQWithIR::copyAudioStreamInAudioBuffer impulse file has channel count != 1");
//            }
//          //  int sampleRate = formatReader->sampleRate;
//
//            // Tässä voi lyhentää samplejen määrää johonkin pienempään mitä impulssifilessä ois.
//            // currentInfo.originalSize = static_cast<int> (jmin (maximumTimeInSamples, formatReader->lengthInSamples));
//
//            int64 originalSize = formatReader->lengthInSamples;
//            formatReader->read (&(impulseResponseBuffer), 0, (int) originalSize, 0, true, false);
//
//            //using NumericType = typename SampleTypeHelpers::ElementType<SampleType>::Type;
//
//            /*lowPotFIR.state*/
//            //dsp::IIR::Coefficients(impulseResponseBuffer.getReadPointer(0), 1048);
//            //lowPotFIR.state = dsp::FIR::Coefficients<float>(impulseResponseBuffer.getReadPointer(0), 1048);
//
//
//            std::make_unique< dsp::FIR::Coefficients<float>>(impulseResponseBuffer.getReadPointer(0), 1048);
//
//
//     //       dsp::FIR::Filter<float> filter(std::make_unique< dsp::FIR::Coefficients<float>>(impulseResponseBuffer.getReadPointer(0), 1048));
//
//
//
//
//      //      FIR::Filter<float>::Filter(Coefficients< NumericType > * CoefficientsToUse)
//
//
//
//
//
//            return true;
//        }
//
//        return false;
//
//       /* AudioFormatManager manager;
//        manager.registerBasicFormats();
//        std::unique_ptr<AudioFormatReader> formatReader (manager.createReaderFor (stream));
//
//        if (formatReader != nullptr)
//        {
//            currentInfo.originalNumChannels = formatReader->numChannels > 1 ? 2 : 1;
//            currentInfo.originalSampleRate = formatReader->sampleRate;
//            currentInfo.originalSize = static_cast<int> (jmin (maximumTimeInSamples, formatReader->lengthInSamples));
//
//            impulseResponseOriginal.clear();
//            formatReader->read (&(impulseResponseOriginal), 0, (int) currentInfo.originalSize, 0, true, currentInfo.originalNumChannels > 1);
//
//            return true;
//        }
//
//        return false;*/
//    }
//
//    void processBlock (AudioSampleBuffer& buffer, MidiBuffer&) override
//    {
//        dryWet.setDryBuffer(buffer);
//        dryWet.dryGainParam = *eqValue;
//        dsp::AudioBlock<float> block(buffer);
//        dsp::ProcessContextReplacing<float> context (block);
//
//        lowPotFIR.process(context);
//        dryWet.process(context);
//
//
//      /*  dsp::AudioBlock<float> block (buffer);
//        dsp::ProcessContextReplacing<float> context (block);
//
//        wetGain.setGainLinear(wetDry);
//        dryGain.setGainLinear(1.0f - wetDry);
//
//        wetGain.process(context);
//
//        dsp::AudioBlock<float> dryBlock(dryBuffer);
//        dsp::ProcessContextReplacing<float> dryContext(dryBlock);
//        dryGain.process(dryContext);
//
//        context.getOutputBlock().add(dryBlock);*/
//    }
//   /* void process(const dsp::ProcessContextReplacing<float>& context) noexcept override
//    {
//        wetGain.params->gain = params->wetDry;
//        dryGain.params->gain = 1.0f - params->wetDry;
//
//        wetGain.process(context);
//
//        dsp::AudioBlock<float> dryBlock(dryBuffer);
//        dsp::ProcessContextReplacing<float> dryContext(dryBlock);
//        dryGain.process(dryContext);
//
//        context.getOutputBlock().add(dryBlock);
//    }
//    */
//    void reset() noexcept override
//    {
//
//    }
//
//    float* eqValue = nullptr;
//
//
//
//
//private:
//
//    using AMPEQ = dsp::ProcessorDuplicator<dsp::FIR::Filter<float>, dsp::FIR::Coefficients<float>>;
//
//    AMPEQ lowPotFIR;
//    AMPEQ highPotFIR;
//    //dsp::ProcessorDuplicator<dsp::IIR::Filter<float>,dsp::ProcessorState> lowPotFIR;
//    //dsp::ProcessorDuplicator<dsp::IIR::Filter<float>,dsp::ProcessorState> highPotFIR;
//
//   // lowPotFIR = dsp::ProcessorDuplicator<dsp::FIR::Filter<float>>;
//   // highPotFIR = dsp::ProcessorDuplicator<dsp::FIR::Filter<float>>;
//
//    DryWetDsp dryWet;
//
//    AudioBuffer<float> impulseResponseBuffer;
//    int maxIRSampleSize = 10 * 48000;
//};

