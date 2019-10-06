/*
  ==============================================================================

    AmpedAudioProcessorBase.h
    Created: 3 Oct 2019 2:27:21pm
    Author:  Veikko Tapaninen

  ==============================================================================
*/

#pragma once
//==============================================================================
class AmpedAudioProcessorBase  : public AudioProcessor
{
public:
    //==============================================================================
    AmpedAudioProcessorBase()  {}
    
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
    
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AmpedAudioProcessorBase)
};

//==============================================================================
class GainProcessor  : public AmpedAudioProcessorBase
{
public:
    GainProcessor()
    {
        gain.setGainDecibels (.0f);
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
        gain.setGainDecibels(*gainValue);
        gain.process (context);
    }
    
    void reset() override
    {
        gain.reset();
    }
    
    const String getName() const override { return "Input Gain"; }
    
public:
    float* gainValue = NULL;
    
private:
    dsp::Gain<float> gain;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GainProcessor)
};

class IRProcessor  : public AmpedAudioProcessorBase
{
public:
    IRProcessor(const char *impulseData, int impulseDataSize)
    {
        this->impulseData = impulseData;
        this->impulseDataSize = impulseDataSize;
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
    }
    
    void reset() override
    {
//        gain.reset();
    }
    
    const String getName() const override { return "IR"; }
    
private:
    void initInpulseResponseProcessor(const char *data, int dataSize, double sampleRate, int samplesPerBlock)
    {
        int numOfChannels = getTotalNumInputChannels();
        dsp::ProcessSpec spec { sampleRate, static_cast<uint32> (samplesPerBlock), static_cast<uint32>(numOfChannels)};
        convolutionDsp.prepare(spec);
        convolutionDsp.loadImpulseResponse(data, dataSize, true, false, 0);
    }
    
public:
    
private:
//    dsp::Gain<float> gain;
    juce::dsp::Convolution convolutionDsp;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IRProcessor)
    
    const char *impulseData = nullptr;
    int impulseDataSize = 0;
    
};

class AmpProcessor  : public AmpedAudioProcessorBase
{
    static const int INTERLEAVED_DEFAULT_SIZE = 8192 * 2; // Two channels, 8192 samples
    
public:
    AmpProcessor() :  interleavedBuffer(new double[INTERLEAVED_DEFAULT_SIZE])
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
    
    void prepareAmp(double sampleRate, int numOfChannels)
    {
        tubeAmp.setSampleRate(sampleRate);
        tubeAmp.setOversample(1);
        tubeAmp.init();
        tubeAmp.setNumChans(2);
        
        tubeAmp.setInputType(PreAmp::EInputType::kGuitarKit);
        tubeAmp.setTubeType(0, TUBE_TABLE_12AX7_68k);
        tubeAmp.setTubeType(1, TUBE_TABLE_12AX7_68k);
        
        tubeAmp.setPowerAmpTubeType(TUBE_TABLE_6L6CG_68k);
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
        tubeAmp.setPreGain(*driveParameter);
        tubeAmp.setMasterVolume(*masterParameter);
        tubeAmp.setPresence(*presenceParameter);
        
        tubeAmp.setDryWet(1.0);
        tubeAmp.setToneStackActive(false);
        tubeAmp.setHighGainStageActive(true);
    }
    
    void processBlock (AudioSampleBuffer& buffer, MidiBuffer&) override
    {
        int numOfSamples = buffer.getNumSamples();
        int numOfChannels = buffer.getNumChannels();
        
        interleaveAndConvertSamples(buffer.getArrayOfWritePointers(), interleavedBuffer.get(), numOfSamples, numOfChannels);
        
        setupAmp();
        
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
    float* driveParameter = nullptr;
    float* presenceParameter = nullptr;
    float* masterParameter = nullptr;
    float* outputParameter = nullptr;
    
private:
    
    TubeAmp tubeAmp;
    
    // 8192 should be enough
    std::unique_ptr<double[]> interleavedBuffer;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AmpProcessor)

};


