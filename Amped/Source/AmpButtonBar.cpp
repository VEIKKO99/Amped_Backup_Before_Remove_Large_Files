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

//==============================================================================
AmpButtonBar::AmpButtonBar()
{
    setLookAndFeel(&ampLookAndFeel);
    
    initSliderComponent(inputSlider);
    initSliderComponent(inputSlider);
    addAndMakeVisible(fxSwitch);
    initSliderComponent(driveSlider);
    initSliderComponent(bassSlider);
    initSliderComponent(middleSlider);
    initSliderComponent(trebleSlider);
    initSliderComponent(presenceSlider);
    initSliderComponent(masterSlider);
    addAndMakeVisible(cabSimSwitch);
    initSliderComponent(outputSlider);

    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

void AmpButtonBar::initSliderComponent(Slider& slider)
{
    slider.setRange(Constants::AmpButtonMin,
                    Constants::AmpButtonMax,
                    Constants::AmpButtonInterval);
    
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle (Slider::NoTextBox, false,0,0);
    addAndMakeVisible(slider);
}



AmpButtonBar::~AmpButtonBar()
{
}

void AmpButtonBar::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (Colours::transparentBlack);   // clear the background
    
    g.setColour (Colours::white);
    g.drawRect (getLocalBounds(), 3);   // draw an outline around the component
    
    g.setColour (Colours::white);
    g.setFont (14.0f);
    g.drawText ("AmpButtonBar", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
}

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
}
