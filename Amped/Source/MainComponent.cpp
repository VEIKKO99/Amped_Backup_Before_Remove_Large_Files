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

//==============================================================================
MainComponent::MainComponent(AudioProcessorValueTreeState& vts) : valueTreeState(vts), ampButtonBar(vts)
{
    
    addAndMakeVisible(ampButtonBar);
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
}

MainComponent::~MainComponent()
{
}

void MainComponent::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    //g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background
    
    Image background = ImageCache::getFromMemory (BinaryData::full_bg_png, BinaryData::full_bg_pngSize);
    g.drawImageAt (background, 0, 0);
}

void MainComponent::resized()
{
    ampButtonBar.setBounds(Constants::AmpButtonBarX, Constants::AmpButtonBarY,
                           Constants::AmpButtonBarW, Constants::AmpButtonBarH);
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
