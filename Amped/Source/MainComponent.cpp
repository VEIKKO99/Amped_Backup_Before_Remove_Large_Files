/*
  ==============================================================================

    MainComponent.cpp
    Created: 14 Sep 2019 10:44:06am
    Author:  Veikko Tapaninen

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "MainComponent.h"
#include "AmpTopBar.h"
#include "UIConsts.h"
#include "PluginProcessor.h"
#include "Consts.h"
#include "LicenceTools.h"

//==============================================================================
MainComponent::MainComponent(AudioProcessorValueTreeState& vts,
                             AmpedAudioProcessor& p) : ampLookAndFeel(&p), valueTreeState(vts), ampButtonBar(vts, ampLookAndFeel, p), processor(p), effectsBar(vts)
{
    setLookAndFeel(&ampLookAndFeel);

    addAndMakeVisible(ampButtonBar);
#ifdef AMPED_DEBUG
    addAndMakeVisible(adminUIButton);
    adminUIButton.addListener(this);
    addAndMakeVisible (versionLabel);
    addAndMakeVisible(nextAmp);
    addAndMakeVisible(prevAmp);
    nextAmp.setButtonText(">");
    prevAmp.setButtonText("<");
    nextAmp.addListener(this);
    prevAmp.addListener(this);
#endif
    topBar.reset (new AmpTopBar());
    topBar->mainComponent = this;
    topBar->setProcessor(&processor);
    addAndMakeVisible (topBar.get());

    addAndMakeVisible(effectsBar);
    effectsBar.setVisible(false);

    auto&& licenceTools = LicenceTools::getInstance();
    licenceTools->isValidLicence();
    auto challenge = papupata::licensing::Challenge(true).toString();
    Logger::getCurrentLogger()->writeToLog("Challenge: " + challenge);



//    initInputClipMeter();


    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
}

MainComponent::~MainComponent()
{
    setLookAndFeel(nullptr);
}

void MainComponent::initInputClipMeter() {
    lnf = new FFAU::LevelMeterLookAndFeel();
    // adjust the colours to how you like them, e.g.
 //   lnf->setColour (FFAU::LevelMeter::lmMeterGradientLowColour, juce::Colours::green);
    lnf->setupDefaultMeterColours();
    meter = new FFAU::LevelMeter(); // See FFAU::LevelMeter::MeterFlags for options
    meter->setLookAndFeel (lnf);
    meter->setMeterSource (&processor.getMeterSource());
    addAndMakeVisible (meter);
}

void MainComponent::toggleEffectsBar() {
    effectsBar.setVisible(!effectsBar.isVisible());
}

void MainComponent::buttonClicked (Button* button)
{
  /*  if (button == &effectsButton) {
        effectsBar.setVisible(!effectsBar.isVisible());
    }*/

#ifdef AMPED_DEBUG
    if (button == &adminUIButton) {
        if (adminUIWindow == nullptr) {
            adminUIWindow.reset(new AmpedAdminSettingsWindowOverride());
            adminUIWindow->setUsingNativeTitleBar(false);
            adminUIWindow->setCentrePosition(400, 400);
            adminUIWindow->setResizable(false, false);
            adminUIWindow->setContentOwned(new AdminSettingsWindow(&processor, &valueTreeState), true);
        }
        adminUIWindow->setVisible(true);
    }

    if (button == &nextAmp) {
        processor.nextSetting();
    }
    if (button == &prevAmp) {
        processor.prevSetting();
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

    if (processor.getCurrentSettings()->uiSettings.mainBackgroundImageFileName.length() > 0) {
        String bgImageName = processor.getCurrentSettings()->uiSettings.mainBackgroundImageFileName;
        if (bgImageName.startsWith("memory:")) {
            int dataSize = 0;
            auto bgImageData = getBinaryDataWithOriginalFileName(bgImageName, dataSize);
            Image background = ImageCache::getFromMemory(bgImageData, dataSize);
            g.drawImageAt (background, 0, 0);
        }
        else {
            File imageFile(processor.getCurrentSettings()->uiSettings.mainBackgroundImageFileName);
            Image background = ImageCache::getFromFile(imageFile);
            g.drawImageAt (background, 0, 0);
        }
    }
}

void MainComponent::resized()
{
    ampButtonBar.setBounds(Constants::AmpButtonBarX, Constants::AmpButtonBarY,
                           Constants::AmpButtonBarW, Constants::AmpButtonBarH);

    topBar->setBounds (0, 0, 1200, 300);

#ifdef AMPED_DEBUG
    adminUIButton.setBounds(80, 480, 100, 40);
    adminUIButton.setButtonText("Admin");
    versionLabel.setBounds(620, 130, 200, 30);
    String date (__DATE__);
    String time (__TIME__);
    versionLabel.setText(date + " - " + time, dontSendNotification);
    versionLabel.setColour (Label::textColourId, Colours::lightgreen);

    prevAmp.setBounds(1000, 480, 40,40);
    nextAmp.setBounds(1050, 480, 40,40);

#endif
    effectsBar.setBounds(0, 140, 1200, 289);

    // This method is where you should set the bounds of any child
    // components that your component contains..

  //ga  meter->setBounds(10, 10, 400, 400);

}

void MainComponent::updateAmpPresetUi() {
    topBar->updateAmpPresetUi();
}
