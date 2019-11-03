/*
  ==============================================================================

    AmpedAudioProcessorBase.h
    Created: 3 Oct 2019 2:27:21pm
    Author:  Veikko Tapaninen

  ==============================================================================
*/

#include "AmpedDsp.h"
#include "AdminSettingsUtil.h"

#pragma once

using Convolution = juce::dsp::Convolution;

enum GainProcessorId { InputGain = 0, OutputGain, DriveGain, SIZE};

//==============================================================================
class AmpedAudioProcessorBase  : public AudioProcessor
{
public:
    //==============================================================================
    AmpedAudioProcessorBase(std::shared_ptr<SoundSettings   > settings)  {
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
    
    //==============================================================================
    void getStateInformation (MemoryBlock&) override       {}
    void setStateInformation (const void*, int) override   {}
    
    virtual void updateInternalSettings() {}
    
protected:
    
    std::shared_ptr<SoundSettings> soundSettings = nullptr;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AmpedAudioProcessorBase)
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
        int numOfChannels = getTotalNumInputChannels();
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
    
    void updateInternalSettings() override {
        gainMin = soundSettings->gainSettings[processorId].min;
        gainMax = soundSettings->gainSettings[processorId].max;
    }


    const String getName() const override { return "Input Gain"; }
    
public:
    float* gainValue = NULL;
    float gainMin = -10;
    float gainMax = 10;

private:
    dsp::Gain<float> gain;
    GainProcessorId processorId;
   
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GainProcessor)
};

class IRProcessor : public AmpedAudioProcessorBase
{
public:
    IRProcessor(const char *impulseData, int impulseDataSize,
                std::shared_ptr<SoundSettings> settings, float makeupGain = .0f):
                AmpedAudioProcessorBase(settings)
    {
        this->impulseData = impulseData;
        this->impulseDataSize = impulseDataSize;
        this->makeupGain = makeupGain;
    }
    
    void prepareToPlay (double sampleRate, int samplesPerBlock) override
    {
        initInpulseResponseProcessor(impulseData, impulseDataSize, sampleRate, samplesPerBlock);
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

    void loadIRFile(String irFile) {
        File irData(irFile);
        convolutionDsp.loadImpulseResponse(irData, false, false, 0);
    }
    
private:
    void initInpulseResponseProcessor(const char *data, int dataSize, double sampleRate, int samplesPerBlock)
    {
        int numOfChannels = getTotalNumInputChannels();
        dsp::ProcessSpec spec { sampleRate, static_cast<uint32> (samplesPerBlock), static_cast<uint32>(numOfChannels)};
        convolutionDsp.prepare(spec);
        convolutionDsp.loadImpulseResponse(data, dataSize, false, false, 0);
    }
    
protected:
    
    float makeupGain = .0f;
    
private:
//    dsp::Gain<float> gain;
    Convolution convolutionDsp;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IRProcessor)
    
    const char *impulseData = nullptr;
    int impulseDataSize = 0;
};


class CabSimIr : public IRProcessor
{
public:
    CabSimIr(const char *impulseData, int impulseDataSize,
            std::shared_ptr<SoundSettings> settings, float makeupGain = .0f):
            IRProcessor(impulseData, impulseDataSize, settings, makeupGain)
    {}

    void updateInternalSettings() override {
        if (soundSettings->ampSettings.cabIr.irFileName.length() > 0) {
            loadIRFile(soundSettings->ampSettings.cabIr.irFileName);
            makeupGain = soundSettings->ampSettings.cabIr.gain;
        }
    }
};

class AmpSimIr : public IRProcessor
{
public:
    AmpSimIr(const char *impulseData, int impulseDataSize,
            std::shared_ptr<SoundSettings> settings, float makeupGain = .0f):
            IRProcessor(impulseData, impulseDataSize, settings, makeupGain)
    {}

    void updateInternalSettings() override {
        loadIRFile(soundSettings->ampSettings.ampIr.irFileName);
        makeupGain = soundSettings->ampSettings.ampIr.gain;

    }
};

class AmpProcessor  : public AmpedAudioProcessorBase
{
    static const int INTERLEAVED_DEFAULT_SIZE = 8192 * 2; // Two channels, 8192 samples
    
public:
    AmpProcessor(std::shared_ptr<SoundSettings> settings): AmpedAudioProcessorBase(settings), interleavedBuffer(new double[INTERLEAVED_DEFAULT_SIZE])
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

    void updateTubeSettings(TubeSettings& source, TubeStage& destination)
    {
        destination.setRK(source.rk);
        destination.setVk0(source.vk0);
        destination.setVPlus(source.vPlus);
        destination.setLowPassFbk(source.lowPassFbk);
        destination.setRP(source.rp);
    }

    void updateInternalSettings() override {
        // Input type (mesa, marshall etc)
        tubeAmp.setInputType(soundSettings->ampSettings.inputType);

        // Power amp:
        tubeAmp.setPowerAmpTubeType(soundSettings->ampSettings.powerAmpTube.tubeType); // This will set the type for both tubes.
        updateTubeSettings(soundSettings->ampSettings.powerAmpTube, tubeAmp.mPowerAmp[0]);
        updateTubeSettings(soundSettings->ampSettings.powerAmpTube, tubeAmp.mPowerAmp[1]);

        updateTubeSettings(soundSettings->ampSettings.preAmpTubes[0], tubeAmp.mPreAmp.tubeStage[0]);
        tubeAmp.setTubeType(0, soundSettings->ampSettings.preAmpTubes[0].tubeType);

        updateTubeSettings(soundSettings->ampSettings.preAmpTubes[1], tubeAmp.mPreAmp.tubeStage[1]);
        tubeAmp.setTubeType(1, soundSettings->ampSettings.preAmpTubes[1].tubeType);

        drive = soundSettings->ampSettings.hornetDrive;
        presence = soundSettings->ampSettings.hornetPresence;

        setupAmp();
    }



    void prepareAmp(double sampleRate, int numOfChannels)
    {
        tubeAmp.setSampleRate(sampleRate);
        tubeAmp.setOversample(1);
        tubeAmp.init();
        tubeAmp.setNumChans(2);
        
        updateInternalSettings();
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
    }
    
    void processBlock (AudioSampleBuffer& buffer, MidiBuffer&) override
    {
        int numOfSamples = buffer.getNumSamples();
        int numOfChannels = buffer.getNumChannels();
        
        interleaveAndConvertSamples(buffer.getArrayOfWritePointers(), interleavedBuffer.get(), numOfSamples, numOfChannels);

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
    
    // 8192 should be enough
    std::unique_ptr<double[]> interleavedBuffer;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AmpProcessor)

};

class EQWithIR: public AmpedAudioProcessorBase
{
public:
    
    EQWithIR(const char *lowPotImpulseData, int lowPotImpulseDataSize,
             const char *highPotImpulseData, int highPotImpulseDataSize,
             std::shared_ptr<SoundSettings> settings,
             float makeupGain = .0f,
             EQType eqType = kBassEq) : AmpedAudioProcessorBase(settings)
    {
        this->eqType = eqType;
        this->loImpulseData = lowPotImpulseData;
        this->loImpulseDataSize = lowPotImpulseDataSize;
        
        this->hiImpulseData = highPotImpulseData;
        this->hiImpulseDataSize = highPotImpulseDataSize;
        this->makeupGain = makeupGain;
    }
    ~EQWithIR() = default;

    void loadIRFile(String irFile, Convolution& convolution) {
        File irData(irFile);
        convolution.loadImpulseResponse(irData, false, false, 0);
    }

    void updateInternalSettings() override {
        EQSettings& eqSettings = soundSettings->ampSettings.eqs[eqType];

        if (eqSettings.highIrFileName.length()  > 0) {
            loadIRFile(eqSettings.highIrFileName, higherPotValues);
        }
        if (eqSettings.lowIrFileName.length() > 0) {
            loadIRFile(eqSettings.lowIrFileName, lowerPotValues);
        }
        makeupGain = eqSettings.gain;
        realisticEqGain = eqSettings.realisticGain;

    }

    void prepareToPlay(double sampleRate, int samplesPerBlock) override
    {
        int numOfChannels = getTotalNumInputChannels();
        dsp::ProcessSpec spec { sampleRate, static_cast<uint32> (samplesPerBlock), static_cast<uint32>(numOfChannels)};
        dryWet.prepare(spec);
        
        initInpulseResponseProcessor(loImpulseData, loImpulseDataSize, sampleRate, samplesPerBlock, lowerPotValues );
        initInpulseResponseProcessor(hiImpulseData, hiImpulseDataSize, sampleRate, samplesPerBlock, higherPotValues );
    }
    
    void processBlock (AudioSampleBuffer& buffer, MidiBuffer&) override
    {

        dryWet.setDryBuffer(buffer);
        dsp::AudioBlock<float> block(buffer);
        dsp::ProcessContextReplacing<float> context (block);
        float dryWetValue = fabs(*eqValue * 2 - 1);
        dryWet.dryGainParam = dryWetValue;
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
    void initInpulseResponseProcessor(const char *data, int dataSize, double sampleRate, int samplesPerBlock, Convolution& convolution )
    {
        int numOfChannels = getTotalNumInputChannels();
        dsp::ProcessSpec spec { sampleRate, static_cast<uint32> (samplesPerBlock), static_cast<uint32>(numOfChannels)};
        convolution.prepare(spec);
        convolution.loadImpulseResponse(data, dataSize, false, false, 0, true);
    }
    
public:
    float* eqValue = nullptr;

private:
    DryWetDsp dryWet;
    Convolution lowerPotValues;
    Convolution higherPotValues;
    
    const char *hiImpulseData = nullptr;
    int hiImpulseDataSize = 0;
    
    const char *loImpulseData = nullptr;
    int loImpulseDataSize = 0;

    float makeupGain = .0f;
    float realisticEqGain = .0f;

    EQType eqType;
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

