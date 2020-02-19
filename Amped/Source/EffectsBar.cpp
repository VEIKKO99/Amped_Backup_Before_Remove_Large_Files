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
    onOffButtonAttachment.reset (new ButtonAttachment (valueTreeState,VTS_EF_OD_ON, onOffButton));
    addAndMakeVisible(onOffButton);
    initSliderComponent(driveSlider,VTS_EF_OD_DRIVE, driveAttachment);
    initSliderComponent(toneSlider,VTS_EF_OD_TONE, toneAttachment);
    initSliderComponent(levelSlider,VTS_EF_OD_LEVEL, levelAttachment);

    initSliderComponent(ngThreshold,VTS_EF_NG_THRESHOLD, ngThresholdAttachment);
    addAndMakeVisible(ngOnOffButton);
    ngOnOffButtonAttachment.reset (new ButtonAttachment (valueTreeState, VTS_EF_NG_ON, ngOnOffButton));

    addAndMakeVisible(ngOnOffButton);
    addAndMakeVisible(ngLed);
    addAndMakeVisible(odLed);
    ngOnOffButton.addListener(this);
    onOffButton.addListener(this);

    odLed.setOn(onOffButton.getToggleState());
    ngLed.setOn(ngOnOffButton.getToggleState());
}

void EffectsBar::buttonClicked (Button* button)
{
    if (button == &onOffButton)
    {
        odLed.setOn(button->getToggleState());
    }
    else if(button == &ngOnOffButton)
    {
        ngLed.setOn(button->getToggleState());
    }
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
    setLookAndFeel(nullptr);
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
    int driveXOffset = 238;
    int driveYOffset = 26;
    onOffButton.setBounds(driveXOffset + 10, driveYOffset + 143, 120, 80);
    driveSlider.setBounds(driveXOffset, driveYOffset + 8, 60, 60);
    toneSlider.setBounds(driveXOffset + 40, driveYOffset +8, 60, 60);
    levelSlider.setBounds(driveXOffset + 80, driveYOffset +8, 60, 60);
    odLed.setBounds(driveXOffset + 59, driveYOffset, 22, 22);

    int ngXOffset = 49;
    int ngYOffset = 26;
    ngOnOffButton.setBounds(ngXOffset,  ngYOffset + 143, 120, 80);
    ngThreshold.setBounds(ngXOffset + 28, ngYOffset + 8, 60, 60);
    ngLed.setBounds(ngXOffset + 48, ngYOffset ,22, 22);

    // This method is where you should set the bounds of any child
    // components that your component contains..

}
