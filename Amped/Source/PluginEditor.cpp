/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AmpedAudioProcessorEditor::AmpedAudioProcessorEditor (AmpedAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), processor (p), mainContainer(vts,p), valueTreeState(vts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    addAndMakeVisible(mainContainer);

    setSize (1200, 600);
}

AmpedAudioProcessorEditor::~AmpedAudioProcessorEditor()
{
}

void AmpedAudioProcessorEditor::updateAmpPresetUi()
{
    mainContainer.updateAmpPresetUi();
}

//==============================================================================
void AmpedAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    //g.fillAll (Colours::blue);

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void AmpedAudioProcessorEditor::resized()
{
    mainContainer.setBounds (getLocalBounds());
    
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
