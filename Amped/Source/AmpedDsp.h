/*
  ==============================================================================

    AmpedDsp.h
    Created: 9 Oct 2019 5:35:37pm
    Author:  Veikko Tapaninen

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class DryWetDsp: dsp::ProcessorBase
{
    
public:
    void prepare(const dsp::ProcessSpec& spec) override
    {
        cachedDryBuffer.setSize(spec.numChannels, spec.maximumBlockSize);
    }
    
    void setDryBuffer(const AudioBuffer<float>& buffer)
    {
        cachedDryBuffer.makeCopyOf(buffer, true);
    }
    
    void process(const dsp::ProcessContextReplacing<float>& context) override
    {
        wetDsp.setGainLinear(dryGainParam);
        dryDsp.setGainLinear(1.0f - dryGainParam);
        
        wetDsp.process(context);
        
        dsp::AudioBlock<float> dryAudioBlock(cachedDryBuffer);
        dsp::ProcessContextReplacing<float> dryContext(dryAudioBlock);
        dryDsp.process(dryContext);
        
        context.getOutputBlock().add(dryAudioBlock);
    }
    
    void reset() override
    {
        wetDsp.reset();
        dryDsp.reset();
    }
    
public:
    float dryGainParam = .5f;
    
private:
    AudioBuffer<float> cachedDryBuffer;
    dsp::Gain<float> wetDsp;
    dsp::Gain<float> dryDsp;
    
};
