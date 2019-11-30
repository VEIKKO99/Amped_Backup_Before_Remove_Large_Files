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
#include "UIConsts.h"

//==============================================================================
AmpButtonBar::AmpButtonBar(AudioProcessorValueTreeState& vts, AmpLookAndFeel& lookAndFeel) : valueTreeState(vts)
{
   // setLookAndFeel(&lookAndFeel);

    initSliderComponent(inputSlider, "input", inputAttachment);
    addAndMakeVisible(fxSwitch);
    fxAttachment.reset (new ButtonAttachment (valueTreeState, "fx", fxSwitch));
    fxSwitch.setWantsKeyboardFocus(false);
    initSliderComponent(driveSlider,"drive", driveAttachment);
    initSliderComponent(bassSlider, "bass", bassAttachment);
    initSliderComponent(middleSlider, "middle", middleAttachment);
    initSliderComponent(trebleSlider, "trebble", trebleAttachment);
    initSliderComponent(presenceSlider, "presence", presenceAttachment);
    initSliderComponent(masterSlider, "master", masterAttachment);
    addAndMakeVisible(cabSimSwitch);
    cabSimSwitch.setWantsKeyboardFocus(false);
    cabSimAttachment.reset (new ButtonAttachment (valueTreeState, "cabSim", cabSimSwitch));
    initSliderComponent(outputSlider, "output", outputAttachment);
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
    
#ifdef AMPED_DEBUG
    addAndMakeVisible(matchIRSwitch);
    matchAttachment.reset (new ButtonAttachment (valueTreeState, "ampSim", matchIRSwitch));
    matchIRSwitch.setWantsKeyboardFocus(false);
#endif
}

AmpButtonBar::~AmpButtonBar()
{
   // setLookAndFeel(nullptr);
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
    setAmpComponentBounds(cabSimSwitch, Constants::AmpCtrlCabSimX);
    setAmpComponentBounds(outputSlider, Constants::AmpCtrlOutputX);
#ifdef AMPED_DEBUG
    setAmpComponentBounds(matchIRSwitch, Constants::AmpCtrlOutputX + 65);
#endif
}
