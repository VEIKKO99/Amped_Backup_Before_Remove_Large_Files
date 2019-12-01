/*
  ==============================================================================

    EffectsBar.cpp
    Created: 17 Nov 2019 3:52:37pm
    Author:  Veikko Tapaninen

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "EffectsBar.h"

//==============================================================================
EffectsBar::EffectsBar(AudioProcessorValueTreeState& vts) : valueTreeState(vts)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    setLookAndFeel(&effectsLookAndFeel);
    addAndMakeVisible(onOffButton);
    onOffButtonAttachment.reset (new ButtonAttachment (valueTreeState, "effects_od_on", onOffButton));
    initSliderComponent(driveSlider,"effects_od_drive", driveAttachment);
    initSliderComponent(toneSlider,"effects_od_tone", toneAttachment);
    initSliderComponent(levelSlider,"effects_od_level", levelAttachment);

}

void EffectsBar::initSliderComponent(Slider& slider, String vtsName, std::unique_ptr<SliderAttachment>& attachment)
{
    slider.setRange(0.0,
            1.0,
            0.005);

    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle (Slider::NoTextBox, false,0,0);
    attachment.reset (new SliderAttachment (valueTreeState, vtsName, slider));

    addAndMakeVisible(slider);
}
EffectsBar::~EffectsBar()
{
}

void EffectsBar::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
    Image background;
    background = ImageCache::getFromMemory (BinaryData::_1200x289pedals_png, BinaryData::_1200x289pedals_pngSize);
    g.drawImageAt(background, 0, 0);


  /*  g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::white);
    g.setFont (14.0f);
    g.drawText ("EffectsBar", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
                */
}

void EffectsBar::resized()
{
    onOffButton.setBounds(470, 160, 100, 100);
    driveSlider.setBounds(430, 30, 60, 60);
    toneSlider.setBounds(470, 30, 60, 60);
    levelSlider.setBounds(510, 30, 60, 60);

    // This method is where you should set the bounds of any child
    // components that your component contains..

}
