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
#include "LicenceDialog.h"
#ifdef AMPED_DEBUG
#include "AdminSettingsUtil.h"
#endif

//==============================================================================
/*
*/

#include "AdminSettingsWindow.h"
#include "PluginProcessor.h"
class AmpTopBar;

class MainComponent    : public Component, public Button::Listener, private Timer
{
public:
    MainComponent(AudioProcessorValueTreeState& vts, AmpedAudioProcessor& p);
    ~MainComponent();

    void paint (Graphics&) override;
    void resized() override;

    void buttonClicked (Button* button) override;
    void toggleEffectsBar();

    void updateAmpPresetUi();

    void openLicenseDialog();


private:

    void initInputClipMeter();
    int getTimerTime();

    AudioProcessorValueTreeState& valueTreeState;
    AmpButtonBar ampButtonBar;
    AmpedAudioProcessor& processor;
    AmpLookAndFeel ampLookAndFeel;
    LeftRightSwitchLookAndFeel lRLookAndFeel;

    EffectsBar effectsBar;

    std::unique_ptr<AmpTopBar> topBar;

    ToggleButton leftRightSwitch;
    std::unique_ptr<ButtonAttachment> leftRightAttachment;

    void timerCallback() override;

#ifdef AMPED_DEBUG
    TextButton adminUIButton;
    std::unique_ptr<AmpedAdminSettingsWindowOverride> adminUIWindow;
    Label versionLabel;

    TextButton nextAmp;
    TextButton prevAmp;
#endif
    std::unique_ptr<LicenceDialog> licenceDialog;
    ScopedPointer<FFAU::LevelMeter> meter;
    ScopedPointer<FFAU::LevelMeterLookAndFeel> lnf;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)

    void doCheck();

    inline void stopA();
};
