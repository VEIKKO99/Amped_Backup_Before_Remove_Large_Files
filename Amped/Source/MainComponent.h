/*
  ==============================================================================

    MainComponent.h
    Created: 14 Sep 2019 10:44:06am
    Author:  Veikko Tapaninen

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "AmpButtonBar.h"
//==============================================================================
/*
*/
class MainComponent    : public Component
{
public:
    MainComponent(AudioProcessorValueTreeState& vts);
    ~MainComponent();

    void paint (Graphics&) override;
    void resized() override;

private:
    AudioProcessorValueTreeState& valueTreeState;
    AmpButtonBar ampButtonBar;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
