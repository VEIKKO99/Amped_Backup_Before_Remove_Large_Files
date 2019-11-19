/*
  ==============================================================================

    MainComponent.cpp
    Created: 14 Sep 2019 10:44:06am
    Author:  Veikko Tapaninen

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "MainComponent.h"
#include "UIConsts.h"
#include "PluginProcessor.h"

//==============================================================================
MainComponent::MainComponent(AudioProcessorValueTreeState& vts,
                             AmpedAudioProcessor& p) : ampLookAndFeel(&p), valueTreeState(vts), ampButtonBar(vts, ampLookAndFeel), processor(p), effectsBar(vts)
{
    setLookAndFeel(&ampLookAndFeel);

    addAndMakeVisible(ampButtonBar);
#ifdef AMPED_DEBUG
    addAndMakeVisible(adminUIButton);
    adminUIButton.addListener(this);
    addAndMakeVisible (versionLabel);
#endif

    addAndMakeVisible(effectsButton);
    addAndMakeVisible(effectsBar);
    effectsBar.setVisible(false);
    effectsButton.addListener(this);
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
}

MainComponent::~MainComponent()
{
    setLookAndFeel(nullptr);
}


void MainComponent::buttonClicked (Button* button)
{
    if (button == &effectsButton) {

    }

#ifdef AMPED_DEBUG
    if (button == &adminUIButton) {
        if (adminUIWindow == nullptr) {
            adminUIWindow.reset(new AmpedAdminSettingsWindowOverride());
            adminUIWindow->setUsingNativeTitleBar(false);
            adminUIWindow->setCentrePosition(400, 400);
            adminUIWindow->setResizable(false, false);
            adminUIWindow->setContentOwned(new AdminSettingsWindow(&processor), true);
        }
        adminUIWindow->setVisible(true);
    }
    if (button == &effectsButton) {
        effectsBar.setVisible(!effectsBar.isVisible());
    }
#endif

}

void MainComponent::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    //g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background
    Image background;
    if (processor.getCurrentSettings()->uiSettings.mainBackgroundImageFileName.length() > 0) {
        File imageFile(processor.getCurrentSettings()->uiSettings.mainBackgroundImageFileName);
        background = ImageCache::getFromFile(imageFile);
    }
    else {
        background = ImageCache::getFromMemory (BinaryData::full_bg_png, BinaryData::full_bg_pngSize);
    }
    g.drawImageAt (background, 0, 0);
}

void MainComponent::resized()
{
    ampButtonBar.setBounds(Constants::AmpButtonBarX, Constants::AmpButtonBarY,
                           Constants::AmpButtonBarW, Constants::AmpButtonBarH);
    
    
#ifdef AMPED_DEBUG
    adminUIButton.setBounds(80, 80, 100, 40);
    adminUIButton.setButtonText("Admin");
    versionLabel.setBounds(620, 90, 200, 30);
    String date (__DATE__);
    String time (__TIME__);
    versionLabel.setText(date + " - " + time, dontSendNotification);
    versionLabel.setColour (Label::textColourId, Colours::lightgreen);
#endif
    effectsButton.setButtonText("Effects");
    effectsButton.setBounds(600, 24, 240, 54);
    effectsBar.setBounds(0, 140, 1200, 289);
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
