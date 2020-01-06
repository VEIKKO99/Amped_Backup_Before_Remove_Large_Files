/*
  ==============================================================================

    AmpButtonBar.cpp
    Created: 14 Sep 2019 12:21:50pm
    Author:  Veikko Tapaninen

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "AmpButtonBar.h"
#include "UIConsts.h"
#include "PluginEditor.h"
#include "Consts.h"

//==============================================================================
AmpButtonBar::AmpButtonBar(AudioProcessorValueTreeState& vts, AmpLookAndFeel& lookAndFeel, AmpedAudioProcessor& processor) : valueTreeState(vts), ampedProcessor(processor)
{
   // setLookAndFeel(&lookAndFeel);

    initSliderComponent(inputSlider, VTS_INPUT, inputAttachment);
    addAndMakeVisible(fxSwitch);
    fxAttachment.reset (new ButtonAttachment (valueTreeState, VTS_FX, fxSwitch));
    fxSwitch.setWantsKeyboardFocus(false);
    initSliderComponent(driveSlider, VTS_DRIVE, driveAttachment);
    initSliderComponent(bassSlider, VTS_BASS, bassAttachment);
    initSliderComponent(middleSlider, VTS_MIDDLE, middleAttachment);
    initSliderComponent(trebleSlider,  VTS_TREBBLE, trebleAttachment);
    initSliderComponent(presenceSlider, VTS_PRESENCE, presenceAttachment);
    initSliderComponent(masterSlider, VTS_MASTER, masterAttachment);

    addAndMakeVisible(cabSimSwitch);
    cabSimSwitch.addListener(this);
    updateCabSimValueFromVTS(*valueTreeState.getRawParameterValue(VTS_CAB_SIM_TYPE));
    vts.addParameterListener(VTS_CAB_SIM_TYPE, this);

    initSliderComponent(outputSlider, VTS_OUTPUT, outputAttachment);
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
    
#ifdef AMPED_DEBUG
    addAndMakeVisible(matchIRSwitch);
    matchAttachment.reset (new ButtonAttachment (valueTreeState, "ampSim", matchIRSwitch));
    matchIRSwitch.setWantsKeyboardFocus(false);
#endif

    inputClipLed.setMeterSource(&processor.getMeterSource());
    addAndMakeVisible(inputClipLed);
    inputClipLed.setVisible(false);
}

AmpButtonBar::~AmpButtonBar()
{
   // setLookAndFeel(nullptr);
   cabSimSwitch.setLookAndFeel(nullptr);
   valueTreeState.removeParameterListener(VTS_CAB_SIM_TYPE, this);
}

void AmpButtonBar::initSliderComponent(Slider& slider, String vtsName, std::unique_ptr<SliderAttachment>& attachment)
{
    slider.setRange(Constants::AmpButtonMin,
                    Constants::AmpButtonMax,
                    Constants::AmpButtonInterval);
    
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle (Slider::NoTextBox, false,0,0);
    attachment.reset (new SliderAttachment (valueTreeState, vtsName, slider));

    addAndMakeVisible(slider);
}

void AmpButtonBar::stateChanged (ThreeWayIRFileSwitch*) {

    auto cabSimStatus = cabSimSwitch.getCurrentStatus();
   // auto irSettings = ampedProcessor.getCurrentSettings()->ampSettings.cabIr;

    if (cabSimStatus == ThreeWayIRFileSwitch::IRCustomUserFile)
    {
        ampedProcessor.getCurrentSettings()->ampSettings.cabIr.overridingIrFileName = cabSimSwitch.getCustomIrFilePath();
        RangedAudioParameter* param = valueTreeState.getParameter(VTS_CAB_SIM_TYPE);
        param->setValueNotifyingHost(0.5);
        ampedProcessor.settingChanged();
    }
    else
    {
        valueTreeState.getParameter(VTS_CAB_SIM_TYPE)->setValueNotifyingHost(cabSimStatus);
        // If we have been using custom (user defined) ir file, remove it:
        if (ampedProcessor.getCurrentSettings()->ampSettings.cabIr.overridingIrFileName.length() > 0) {
            ampedProcessor.getCurrentSettings()->ampSettings.cabIr.overridingIrFileName = "";
            ampedProcessor.settingChanged();
        }
    }
}

// This is only used to get callbacks to our custom Cab IR switch status:
void AmpButtonBar::parameterChanged (const String& parameterID, float newValue) {
    updateCabSimValueFromVTS(newValue);
}

void AmpButtonBar::paint (Graphics& g)
{}

void AmpButtonBar::setAmpComponentBounds(Component& component, int xCoord) {
     component.setBounds(xCoord,
                         Constants::ampButtonsY,
                         Constants::ampButtonsWidth,
                         Constants::ampButtonsHeight);
}

void AmpButtonBar::resized()
{
    setAmpComponentBounds(inputSlider, Constants::ampCompInputX);
    setAmpComponentBounds(fxSwitch, Constants::AmpCtrlSwitchX);
    setAmpComponentBounds(driveSlider, Constants::AmpCtrlDriveX);
    setAmpComponentBounds(bassSlider, Constants::AmpCtrlBassX);
    setAmpComponentBounds(middleSlider, Constants::AmpCtrlMiddleX);
    setAmpComponentBounds(trebleSlider, Constants::AmpCtrlTrebbleX);
    setAmpComponentBounds(presenceSlider, Constants::AmpCtrlPresenceX);
    setAmpComponentBounds(masterSlider, Constants::AmpCtrlMasterX);
    setAmpComponentBounds(outputSlider, Constants::AmpCtrlOutputX);
#ifdef AMPED_DEBUG
    setAmpComponentBounds(matchIRSwitch, Constants::AmpCtrlOutputX + 65);
#endif
    inputClipLed.setBounds(50,6, 22, 22);
    cabSimSwitch.setBounds(Constants::AmpCtrlCabSimX, Constants::ampButtonsY, 90, Constants::ampButtonsHeight);
}

void AmpButtonBar::updateCabSimValueFromVTS(float newValue) {
    int switchStatus = (int) newValue;
    cabSimSwitch.setCurrentStatus(static_cast<ThreeWayIRFileSwitch::SwitchStatus>(switchStatus), false);
}
