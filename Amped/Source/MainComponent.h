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
#ifdef AMPED_DEBUG
#include "AdminSettingsUtil.h"
#endif

//==============================================================================
/*
*/

#include "AdminSettingsWindow.h"
#include "PluginProcessor.h"

class MainComponent    : public Component
                        #ifdef AMPED_DEBUG
                            ,public Button::Listener
                        #endif
{
public:
    MainComponent(AudioProcessorValueTreeState& vts, AmpedAudioProcessor& p);
    ~MainComponent();

    void paint (Graphics&) override;
    void resized() override;

#ifdef AMPED_DEBUG
    void buttonClicked (Button* button) override;
#endif
    
private:
    AudioProcessorValueTreeState& valueTreeState;
    AmpButtonBar ampButtonBar;
    AmpedAudioProcessor& processor;
    AmpLookAndFeel ampLookAndFeel;


#ifdef AMPED_DEBUG
    TextButton adminUIButton;
    std::unique_ptr<AmpedAdminSettingsWindowOverride> adminUIWindow;

#endif

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
