/*
  ==============================================================================

    Delay.h
    Created: 3 May 2020 7:44:10pm
    Author:  Veikko Tapaninen

  ==============================================================================
*/

#pragma once

#define MAX_DELAY_TIME_IN_MS 1000

using Convolution = juce::dsp::Convolution;

class Delay
{
public:
    void prepareToPlay (double sampleRate, int samplesPerBlock, int numOfInputChannels, int numOfOutputChannels)
    {
        mSampleRate = sampleRate;
        mNumOfInputChannels = numOfInputChannels;
        mNumOfOutputChannels = numOfOutputChannels;

        mDelayBuffer.setSize (mNumOfInputChannels, MAX_DELAY_TIME_IN_MS / 1000 * (samplesPerBlock + sampleRate), false, false);
        mDelayBuffer.clear();
        mWorkBuffer.setSize (mNumOfInputChannels, samplesPerBlock, false, false);
        mWorkBuffer.clear();
        mLofiBuffer.setSize (mNumOfInputChannels, samplesPerBlock, false, false);
        mLofiBuffer.clear();
        
        dsp::ProcessSpec spec { sampleRate, static_cast<uint32> (samplesPerBlock), 1};
        convolutionDspFirst.prepare(spec);
        convolutionDspFirst.loadImpulseResponse(BinaryData::ARK_LB_10_Q_wav, BinaryData::ARK_LB_10_Q_wavSize, false, false, 0);
        convolutionDspFirst.reset();
        
        convolutionDspFeedback.prepare(spec);
        convolutionDspFeedback.loadImpulseResponse(BinaryData::ARK_LB_10_Q_wav, BinaryData::ARK_LB_10_Q_wavSize, false, false, 0);
        convolutionDspFeedback.reset();
        
        mExpectedReadPos = -1;
    }
    
    void processBlock (AudioBuffer<float>& buffer)
    {
        const float time = *mTime * MAX_DELAY_TIME_IN_MS;
        const float feedback = *mFeedback * 0.95f; //Decibels::decibelsTo    (*mFeedback);

        for (int i = 0; i < buffer.getNumChannels(); i++) {
            if (i < mWorkBuffer.getNumChannels()) {
                mWorkBuffer.copyFrom(i, 0, buffer, i, 0, buffer.getNumSamples());
            }
        }
  
        // write original to delay
        for (int i=0; i < mDelayBuffer.getNumChannels(); ++i)
        {
            const int inputChannelNum = i; //inputBus->getChannelIndexInProcessBlockBuffer (std::min (i, inputBus->getNumberOfChannels()));
            writeToDelayBuffer (mWorkBuffer, inputChannelNum, i, mWritePos, 1.0f, 1.0f, true);
        }

        // read delayed signal
        auto readPos = roundToInt (mWritePos - (mSampleRate * time / 1000.0));
        if (readPos < 0)
            readPos += mDelayBuffer.getNumSamples();

        // if has run before
        if (mExpectedReadPos >= 0)
        {
            // fade out if readPos is off
            auto endGain = (readPos == mExpectedReadPos) ? 1.0f : 0.0f;
            for (int i=0; i < mNumOfOutputChannels; ++i)
            {
                const int outputChannelNum = i; //outputBus->getChannelIndexInProcessBlockBuffer (i);
                readFromDelayBuffer (mWorkBuffer, i, outputChannelNum, mExpectedReadPos, 1.0, endGain, true);
            }
        }

        // fade in at new position
        if (readPos != mExpectedReadPos)
        {
            for (int i=0; i < mNumOfOutputChannels; ++i)
            {
                const int outputChannelNum = i; //outputBus->getChannelIndexInProcessBlockBuffer (i);
                readFromDelayBuffer (mWorkBuffer, i, outputChannelNum, readPos, 0.0, 1.0, true);
            }
        }
    
        // add feedback to delay
        for (int i=0; i < mNumOfInputChannels; ++i)
        {
            const int outputChannelNum = i; //inputBus->getChannelIndexInProcessBlockBuffer (i);
            writeToDelayBuffer (mWorkBuffer, outputChannelNum, i, mWritePos, mLastFeedbackGain, feedback, false);
        }
        mLastFeedbackGain = feedback;

        // advance positions
        mWritePos += mWorkBuffer.getNumSamples();
        if (mWritePos >= mDelayBuffer.getNumSamples())
            mWritePos -= mDelayBuffer.getNumSamples();

        mExpectedReadPos = readPos + mWorkBuffer.getNumSamples();
        if (mExpectedReadPos >= mDelayBuffer.getNumSamples())
            mExpectedReadPos -= mDelayBuffer.getNumSamples();
  
        for (int i = 0 ; i < mNumOfInputChannels; ++i) {
            buffer.addFrom(i, 0, mWorkBuffer, i, 0, buffer.getNumSamples(), *mMix);
        }
    }

    void writeToDelayBuffer (AudioSampleBuffer& buffer,
                             const int channelIn, const int channelOut,
                             const int writePos,
                             float startGain, float endGain,
                             bool replacing)
    {
        mLofiBuffer.clear();
        dsp::AudioBlock<float> block(mLofiBuffer);
        dsp::AudioBlock<float> block2(buffer);

        dsp::ProcessContextNonReplacing<float> context (block2, block);

        if (replacing) {
            convolutionDspFirst.process(context);
        }
        else {
            convolutionDspFeedback.process(context);
        }
        
        mLofiBuffer.applyGain(Decibels::decibelsToGain(9.0f));
        
        if (writePos + mLofiBuffer.getNumSamples() <= mDelayBuffer.getNumSamples())
        {
            if (replacing)
                mDelayBuffer.copyFromWithRamp (channelOut, writePos, mLofiBuffer.getReadPointer (channelIn), mLofiBuffer.getNumSamples(), startGain, endGain);
            else
                mDelayBuffer.addFromWithRamp (channelOut, writePos, mLofiBuffer.getReadPointer (channelIn), mLofiBuffer.getNumSamples(), startGain, endGain);
        }
        else
        {
            const auto midPos  = mDelayBuffer.getNumSamples() - writePos;
            const auto midGain = jmap (float (midPos) / mLofiBuffer.getNumSamples(), startGain, endGain);
            if (replacing)
            {
                mDelayBuffer.copyFromWithRamp (channelOut, writePos, mLofiBuffer.getReadPointer (channelIn),         midPos, startGain, midGain);
                mDelayBuffer.copyFromWithRamp (channelOut, 0,        mLofiBuffer.getReadPointer (channelIn, midPos), mLofiBuffer.getNumSamples() - midPos, midGain, endGain);
            }
            else
            {
                mDelayBuffer.addFromWithRamp (channelOut, writePos, mLofiBuffer.getReadPointer (channelIn),         midPos, mLastInputGain, midGain);
                mDelayBuffer.addFromWithRamp (channelOut, 0,        mLofiBuffer.getReadPointer (channelIn, midPos), mLofiBuffer.getNumSamples() - midPos, midGain, endGain);
            }
        }
    }

    void readFromDelayBuffer (AudioSampleBuffer& buffer,
                              const int channelIn, const int channelOut,
                              const int readPos,
                              float startGain, float endGain,
                              bool replacing)
    {
        if (readPos + buffer.getNumSamples() <= mDelayBuffer.getNumSamples())
        {
            if (replacing)
                buffer.copyFromWithRamp (channelOut, 0, mDelayBuffer.getReadPointer (channelIn, readPos), buffer.getNumSamples(), startGain, endGain);
            else
                buffer.addFromWithRamp (channelOut, 0, mDelayBuffer.getReadPointer (channelIn, readPos), buffer.getNumSamples(), startGain, endGain);
        }
        else
        {
            const auto midPos  = mDelayBuffer.getNumSamples() - readPos;
            const auto midGain = jmap (float (midPos) / buffer.getNumSamples(), startGain, endGain);
            if (replacing)
            {
                buffer.copyFromWithRamp (channelOut, 0,      mDelayBuffer.getReadPointer (channelIn, readPos), midPos, startGain, midGain);
                buffer.copyFromWithRamp (channelOut, midPos, mDelayBuffer.getReadPointer (channelIn), buffer.getNumSamples() - midPos, midGain, endGain);
            }
            else
            {
                buffer.addFromWithRamp (channelOut, 0,      mDelayBuffer.getReadPointer (channelIn, readPos), midPos, startGain, midGain * *mMix);
                buffer.addFromWithRamp (channelOut, midPos, mDelayBuffer.getReadPointer (channelIn), buffer.getNumSamples() - midPos, midGain, endGain);
            }
        }
    }
    
// Live parameters
   float* mFeedback;
   float* mTime;
   float* mMix;
    
private:
    int mWritePos {0};
    int mExpectedReadPos{-1};
    double mSampleRate{44100};
    AudioBuffer<float> mDelayBuffer;
    AudioBuffer<float> mWorkBuffer;
    AudioBuffer<float> mLofiBuffer;

    int mNumOfInputChannels{0};
    int mNumOfOutputChannels{0};
    float mLastInputGain{0.0f};
    float mLastFeedbackGain{0.0f};
    
    Convolution convolutionDspFirst;
    Convolution convolutionDspFeedback;
};
