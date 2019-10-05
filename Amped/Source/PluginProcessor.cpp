/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "original_hornet/TubeAmp.h"
#include "AmpedAudioProcessorBase.h"
//==============================================================================
AmpedAudioProcessor::AmpedAudioProcessor() :
#ifndef JucePlugin_PreferredChannelConfigurations
      AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
        mainProcessor  (new AudioProcessorGraph()),
        parameters (*this, nullptr, Identifier ("AmpedV100"),
                    {
                        std::make_unique<AudioParameterFloat> ("input",            // parameterID
                                                               "Input",            // parameter name
                                                               0.0f,              // minimum value
                                                               1.0f,              // maximum value
                                                               0.5f),             // default value
                        std::make_unique<AudioParameterBool> ("fx",               // parameterID
                                                              "FX",                // parameter name
                                                              false),              // default value
                        std::make_unique<AudioParameterFloat> ("drive", "Drive", 0.0f, 1.0f, 0.5f),
                        std::make_unique<AudioParameterFloat> ("bass","Bass", 0.0f, 1.0f, 0.5f),             
                        std::make_unique<AudioParameterFloat> ("middle", "Middle", 0.0f, 1.0f, 0.5f),
                        std::make_unique<AudioParameterFloat> ("trebble", "Trebble", 0.0f, 1.0f, 0.5f),
                        std::make_unique<AudioParameterFloat> ("presence", "Presence", 0.0f,  1.0f, 0.5f),
                        std::make_unique<AudioParameterFloat> ("master", "Master", 0.0f, 1.0f, 0.5f),
                        std::make_unique<AudioParameterBool> ("cabSim", "IR", false),
                        std::make_unique<AudioParameterFloat> ("output", "Output", 0.0f, 1.0f, 0.5f) })
#endif
{
    Logger::getCurrentLogger()->writeToLog("AmpedAudioProcessor - Constructor");
    mainProcessor->setProcessingPrecision(ProcessingPrecision::doublePrecision);
    inputParameter = parameters.getRawParameterValue ("input");
    fxParameter = parameters.getRawParameterValue ("fx");
    driveParameter = parameters.getRawParameterValue ("dirve");
    bassParameter = parameters.getRawParameterValue ("bass");
    middleParameter = parameters.getRawParameterValue ("middle");
    trebleParameter = parameters.getRawParameterValue ("trebble");
    presenceParameter = parameters.getRawParameterValue ("presence");
    masterParameter = parameters.getRawParameterValue ("master");
    irParameter = parameters.getRawParameterValue ("cabSim");
    outputParameter = parameters.getRawParameterValue ("output");


    driveParameter = parameters.getRawParameterValue ("drive");
    
    
  //  tubeAmp.setNumChans(2);
  //  tubeAmp.setSampleRate(48000);
  //  tubeAmp.init();
}

AmpedAudioProcessor::~AmpedAudioProcessor()
{
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

void AmpedAudioProcessor::setupAmp() {
    tubeAmp.setPreGain(*driveParameter);
    tubeAmp.setDryWet(1.0);
    tubeAmp.setMasterVolume(*masterParameter);
    tubeAmp.setToneStackActive(false);
    tubeAmp.setToneStackLow(*bassParameter);
    tubeAmp.setToneStackMid(*middleParameter);
    tubeAmp.setToneStackHigh(*trebleParameter);
    tubeAmp.setHighGainStageActive(true);
    tubeAmp.setPresence(*presenceParameter);
    
    
    
}

void AmpedAudioProcessor::updateGraph()
{
    bool hasChanged = true;
    
   // Array<AudioParameterChoice*> choices { processorSlot1,
   //     processorSlot2,
   //     processorSlot3 };
    
   // Array<AudioParameterBool*> bypasses { bypassSlot1,
   //     bypassSlot2,
   //     bypassSlot3 };
    
    //ReferenceCountedArray<Node> slots;
    //slots.add (slot1Node);
    //slots.add (slot2Node);
    //slots.add (slot3Node);
    
//    for (int i = 0; i < 3; ++i)
//    {
//        auto& choice = choices.getReference (i);
//        auto  slot   = slots  .getUnchecked (i);
//
//        if (choice->getIndex() == 0)
//        {
//            if (slot != nullptr)
//            {
//                mainProcessor->removeNode (slot.get());
//                slots.set (i, nullptr);
//                hasChanged = true;
//            }
//        }
//        else if (choice->getIndex() == 1)
//        {
//            if (slot != nullptr)
//            {
//                if (slot->getProcessor()->getName() == "Oscillator")
//                    continue;
//
//                mainProcessor->removeNode (slot.get());
//            }
//
//            slots.set (i, mainProcessor->addNode (std::make_unique<OscillatorProcessor>()));
//            hasChanged = true;
//        }
//        else if (choice->getIndex() == 2)
//        {
//            if (slot != nullptr)
//            {
//                if (slot->getProcessor()->getName() == "Gain")
//                    continue;
//
//                mainProcessor->removeNode (slot.get());
//            }
//
//            slots.set (i, mainProcessor->addNode (std::make_unique<GainProcessor>()));
//            hasChanged = true;
//        }
//        else if (choice->getIndex() == 3)
//        {
//            if (slot != nullptr)
//            {
//                if (slot->getProcessor()->getName() == "Filter")
//                    continue;
//
//                mainProcessor->removeNode (slot.get());
//            }
//
//            slots.set (i, mainProcessor->addNode (std::make_unique<FilterProcessor>()));
//            hasChanged = true;
//        }
//    }
    //bool hasChanged = true;
    if (hasChanged)
    {
        for (auto connection : mainProcessor->getConnections())
            mainProcessor->removeConnection (connection);
        
  //      ReferenceCountedArray<Node> activeSlots;
        
//        for (auto slot : slots)
//        {
//            if (slot != nullptr)
//            {
//                activeSlots.add (slot);
//
//                slot->getProcessor()->setPlayConfigDetails (getMainBusNumInputChannels(),
//                                                            getMainBusNumOutputChannels(),
//                                                            getSampleRate(), getBlockSize());
//            }
//        }
        
  //      if (activeSlots.isEmpty())
  //      {
            connectAudioNodes();
  //      }
 //       else
 //       {
 //           for (int i = 0; i < activeSlots.size() - 1; ++i)
 //           {
 //               for (int channel = 0; channel < 2; ++channel)
 //                   mainProcessor->addConnection ({ { activeSlots.getUnchecked (i)->nodeID,      channel },
//                        { activeSlots.getUnchecked (i + 1)->nodeID,  channel } });
//            }
            
     //       for (int channel = 0; channel < 2; ++channel)
     //       {
     //           mainProcessor->addConnection ({ { audioInputNode->nodeID,         channel },
     //               { activeSlots.getFirst()->nodeID, channel } });
     //           mainProcessor->addConnection ({ { activeSlots.getLast()->nodeID,  channel },
     //               { audioOutputNode->nodeID,        channel } });
     //       }
     //   }
        
        connectMidiNodes();
        
        for (auto node : mainProcessor->getNodes())
            node->getProcessor()->enableAllBuses();
    }
    
//    for (int i = 0; i < 3; ++i)
//    {
//        auto  slot   = slots   .getUnchecked (i);
//        auto& bypass = bypasses.getReference (i);
//
//        if (slot != nullptr)
//            slot->setBypassed (bypass->get());
//    }
//
//    audioInputNode->setBypassed (muteInput->get());
//
//    slot1Node = slots.getUnchecked (0);
//    slot2Node = slots.getUnchecked (1);
//    slot3Node = slots.getUnchecked (2);
}

void AmpedAudioProcessor::processBlock (AudioBuffer<double>& buffer,
                                                MidiBuffer& midiMessages)
{
    for (int i = getTotalNumInputChannels(); i < getTotalNumOutputChannels(); ++i)
    {
        buffer.clear (i, 0, buffer.getNumSamples());
    }

    updateGraph();
    mainProcessor->processBlock (buffer, midiMessages);

    
    
    
    buffer.applyGain(*inputParameter);
    double* interleavedBuffer = new double[buffer.getNumChannels() * buffer.getNumSamples()];
    
    AmpedAudioProcessor::interleaveSamples(buffer.getArrayOfWritePointers(), interleavedBuffer, buffer.getNumSamples(), buffer.getNumChannels());
    
    setupAmp();
    
    tubeAmp.process(interleavedBuffer, buffer.getNumSamples());
    
    AmpedAudioProcessor::deinterleaveSamples(interleavedBuffer, buffer.getArrayOfWritePointers(),
                                             buffer.getNumSamples(), buffer.getNumChannels());
    
    delete[] interleavedBuffer;
 
    
   // float* floatAudioBufffer = new float[buffer.getNumSamples()];
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

    for(int i = 0; i < buffer.getNumChannels(); ++i) {
        double* buf = buffer.getWritePointer(i);

        for (int j = 0; j < buffer.getNumSamples(); j++)
        {
            buf[j] = samples[i][j];
        }
        delete [] samples[i];
    }
    delete [] samples;
//     dsp::AudioBlock<float> block (buffer);
//     dsp::ProcessContextReplacing<float> context (block);
//     cabSim.process (context);
    
//    dsp::AudioBlock<float> block
    
    //double *samples = new int[buffer.getNumChannels() * buffer.getNumSamples()];
    
    
    
  /*  for (int i = 0; i < buffer.getNumChannels(); i++)
    {
        double* buf = buffer.getWritePointer(i);
        for (int j = 0; j < buffer.getNumSamples(); j++)
        {
            floatAudioBufffer[j] = static_cast<float> (buf[j]);
        }
        
        
        
        
       // dsp::AudioBlock<float> block (buffer);
       // dsp::ProcessContextReplacing<float> context (block);
       // filter.process (context);
        
        
        for (int j = 0; j < buffer.getNumSamples(); j++)
        {
            buf[j] = floatAudioBufffer[j];
        }
    }
    
    delete[] floatAudioBufffer;*/
    
    
    
    
    buffer.applyGain(*outputParameter);

    
    
  //  for (int i = 0; i < buffer.getNumChannels(); ++i)
  //  {
    //    double* chanbuf = buffer.getWritePointer(1);
        
    //    tubeAmp.process(chanbuf, buffer.getNumSamples());
        //for (int j = 0; j < bufferIn.getNumSamples(); ++j)
        //{
        //    chanbuf[j] = getNextSample(chanbuf[j]);
        //}
   // }
    
}



bool AmpedAudioProcessor::supportsDoublePrecisionProcessing() const
{
    return true;
}

void AmpedAudioProcessor::initInpulseResponseProcessor(const char *data, double sampleRate, int samplesPerBlock, int size, juce::dsp::Convolution& convolution) {
    dsp::ProcessSpec spec { sampleRate, static_cast<uint32> (samplesPerBlock), 2 };
    convolution.prepare (spec);
    
    
    // BinaryData::getNamedResource(BinaryData::CABIR_wav, size);
    cabSim.loadImpulseResponse(data, size, true, false, 0);
}

void AmpedAudioProcessor::initialiseGraph() {
    mainProcessor->clear();
    audioInputNode  = mainProcessor->addNode (std::make_unique<AudioGraphIOProcessor> (AudioGraphIOProcessor::audioInputNode));
    audioOutputNode = mainProcessor->addNode (std::make_unique<AudioGraphIOProcessor> (AudioGraphIOProcessor::audioOutputNode));
    midiInputNode   = mainProcessor->addNode (std::make_unique<AudioGraphIOProcessor> (AudioGraphIOProcessor::midiInputNode));
    midiOutputNode  = mainProcessor->addNode (std::make_unique<AudioGraphIOProcessor> (AudioGraphIOProcessor::midiOutputNode));
    
    connectAudioNodes();
    connectMidiNodes();

    //gainProcessor = mainProcessor->addNode (std::make_unique<GainProcessor>());
  //  connectAudioNodes();
    
   // mainProcessor->addConnection ({ { audioInputNode->nodeID,  2 },
   //          { audioOutputNode->nodeID,        2 } });
   // mainProcessor->addConnection ({ { audioInputNode->nodeID,         2 },
   //     { gainProcessor->nodeID, 2 } });
   // mainProcessor->addConnection ({ { gainProcessor->nodeID,  2 },
   //     { audioOutputNode->nodeID,        2 } });
    
}

void AmpedAudioProcessor::connectAudioNodes()
{
    for (int channel = 0; channel < 2; ++channel)
        mainProcessor->addConnection ({ { audioInputNode->nodeID,  channel },
            { audioOutputNode->nodeID, channel } });
}

void AmpedAudioProcessor::connectMidiNodes()
{
    mainProcessor->addConnection ({ { midiInputNode->nodeID,  AudioProcessorGraph::midiChannelIndex },
        { midiOutputNode->nodeID, AudioProcessorGraph::midiChannelIndex } });
}


//==============================================================================
void AmpedAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    Logger::getCurrentLogger()->writeToLog("prepareToPlay   ");

    mainProcessor->setPlayConfigDetails (getMainBusNumInputChannels(),
                                         getMainBusNumOutputChannels(),
                                         sampleRate, samplesPerBlock);
    
    mainProcessor->prepareToPlay (sampleRate, samplesPerBlock);
    initialiseGraph();

    
    
    
 //   void HoRNetGuitarKit::Reset()
 //   {
 //       TRACE;
     //   IMutexLock lock(this);
        
    tubeAmp.setSampleRate(sampleRate);
    tubeAmp.setOversample(1);
    tubeAmp.init();
    tubeAmp.setNumChans(2);
    
    
    


   // tubeAmp.setHighGainStageActive(true);
    tubeAmp.setInputType(PreAmp::EInputType::kGuitarKit);
    tubeAmp.setTubeType(0, TUBE_TABLE_12AX7_68k);
    tubeAmp.setTubeType(1, TUBE_TABLE_12AX7_68k);

    tubeAmp.setPowerAmpTubeType(TUBE_TABLE_6L6CG_68k );
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
    initInpulseResponseProcessor(BinaryData::MATCH_IR_FILTERED_wav, sampleRate, samplesPerBlock, BinaryData::MATCH_IR_FILTERED_wavSize, ampSim);

    // Cab sim:
    initInpulseResponseProcessor(BinaryData::CAB_IR_FILTERED_wav, sampleRate, samplesPerBlock, BinaryData::CAB_IR_FILTERED_wavSize, cabSim);
}


void AmpedAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool AmpedAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    if (layouts.getMainInputChannelSet()  == AudioChannelSet::disabled()
        || layouts.getMainOutputChannelSet() == AudioChannelSet::disabled())
        return false;
    
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;
    
    return layouts.getMainInputChannelSet() == layouts.getMainOutputChannelSet();
    
    
    // Support mono in and mono or stereo out only:
  /*  if ((layouts.getMainInputChannelSet() == AudioChannelSet::mono() ||
         layouts.getMainInputChannelSet() == AudioChannelSet::stereo()) &&
        (layouts.getMainOutputChannelSet() == AudioChannelSet::mono() ||
         layouts.getMainOutputChannelSet() == AudioChannelSet::stereo())){
        return true;
    }
    return false;*/
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


void AmpedAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
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

//==============================================================================
bool AmpedAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* AmpedAudioProcessor::createEditor()
{
    return new AmpedAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void AmpedAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void AmpedAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AmpedAudioProcessor();
}



//==============================================================================
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
