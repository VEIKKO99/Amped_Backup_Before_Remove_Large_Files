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
        gain.setGainDecibels (-6.0f);
    }
    
    void prepareToPlay (double sampleRate, int samplesPerBlock) override
    {
        dsp::ProcessSpec spec { sampleRate, static_cast<uint32> (samplesPerBlock), 1 };
        gain.prepare (spec);
    }
    
    void processBlock (AudioSampleBuffer& buffer, MidiBuffer&) override
    {
        dsp::AudioBlock<float> block (buffer);
        dsp::ProcessContextReplacing<float> context (block);
        gain.process (context);
    }
    
    void reset() override
    {
        gain.reset();
    }
    
    const String getName() const override { return "Gain"; }
    
private:
    dsp::Gain<float> gain;
};


