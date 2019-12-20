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
#include "EffectsBar.h"
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

    void buttonClicked (Button* button) override;

private:

    void initInputClipMeter();

    AudioProcessorValueTreeState& valueTreeState;
    AmpButtonBar ampButtonBar;
    AmpedAudioProcessor& processor;
    AmpLookAndFeel ampLookAndFeel;
    TextButton effectsButton;
    EffectsBar effectsBar;

#ifdef AMPED_DEBUG
    TextButton adminUIButton;
    std::unique_ptr<AmpedAdminSettingsWindowOverride> adminUIWindow;
    Label versionLabel;

    TextButton nextAmp;
    TextButton prevAmp;
#endif
    ScopedPointer<FFAU::LevelMeter> meter;
    ScopedPointer<FFAU::LevelMeterLookAndFeel> lnf;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
