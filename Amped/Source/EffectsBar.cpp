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

    // Reverb:

    initSliderComponent(reverbSizeSlider,VTS_EF_REVB_SIZE, reverbSizeAttachment);
    initSliderComponent(reverbToneSlider,VTS_EF_REVB_TONE, reverbToneAttachment);
    initSliderComponent(reverbMixSlider,VTS_EF_REVB_MIX, reverbMixAttachment);
    revbOnOffButton.addListener(this);

    revbOnOffButtonAttachment.reset (new ButtonAttachment (valueTreeState,VTS_EF_REVB_ON, revbOnOffButton));
    addAndMakeVisible(revbOnOffButton);
    addAndMakeVisible(reverbLed);
    reverbLed.setOn(revbOnOffButton.getToggleState());
    
    // Delay:
    initSliderComponent(dlyMixSlider,VTS_EF_DLY_MIX, dlyMixAttachment);
    initSliderComponent(dlyFeedbackSlider,VTS_EF_DLY_FEEDBACK, dlyFeedBackttachment);
    initSliderComponent(dlyTimeSlider,VTS_EF_DLY_TIME, dlyTimeAttachment);
    dlyOnOffButton.addListener(this);
    dlyOnOffButtonAttachment.reset (new ButtonAttachment (valueTreeState,VTS_EF_DLY_ON, dlyOnOffButton));
    addAndMakeVisible(dlyOnOffButton);
    addAndMakeVisible(delayLed);
    delayLed.setOn(dlyOnOffButton.getToggleState());

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
    else if(button == &revbOnOffButton)
    {
        reverbLed.setOn(button->getToggleState());
    }
    else if (button == &dlyOnOffButton)
    {
        delayLed.setOn(button->getToggleState());
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
    Image background;
    background = ImageCache::getFromMemory (BinaryData::_2020_4_pedals_png, BinaryData::_2020_4_pedals_pngSize);
    g.drawImageAt(background, 0, 0);
}

void EffectsBar::resized()
{
    // Noise gate:
    int driveYOffset = 48;
    int ngXOffset = 42;
    int ngYOffset = driveYOffset;
    
    ngOnOffButton.setBounds(ngXOffset -10,  ngYOffset + 135, 120, 75);
    ngThreshold.setBounds(ngXOffset + 28, ngYOffset + 8, 40, 40);
    ngLed.setBounds(ngXOffset + 35, ngYOffset + 81 ,22, 22);

    // Overdrive:
    int driveXOffset = 160;
    onOffButton.setBounds(driveXOffset, driveYOffset + 135, 120, 75);
    driveSlider.setBounds(driveXOffset, driveYOffset + 8, 40, 40);
    toneSlider.setBounds(driveXOffset + 40, driveYOffset +8, 40, 40);
    levelSlider.setBounds(driveXOffset + 78, driveYOffset +8, 40, 40);
    odLed.setBounds(driveXOffset + 47, driveYOffset + 81, 22, 22);

    // Delay:
    int dlyXOffset = 290;
    int dlyYOffset = driveYOffset;
    dlyOnOffButton.setBounds(dlyXOffset, dlyYOffset + 135, 120, 75);
    dlyTimeSlider.setBounds(dlyXOffset , dlyYOffset + 8, 40, 40);
    dlyFeedbackSlider.setBounds(dlyXOffset + 40, dlyYOffset + 8, 40, 40);
    dlyMixSlider.setBounds(dlyXOffset + 78, dlyYOffset + 8, 40, 40);
    delayLed.setBounds(dlyXOffset + 48, dlyYOffset + 81, 22,22);
    
    // Reverb:
    int revbXOffset = 420;
    int revYOffset = driveYOffset;
    revbOnOffButton.setBounds(revbXOffset, revYOffset + 135, 120, 75);
    reverbSizeSlider.setBounds(revbXOffset, revYOffset + 8, 40, 40);
    reverbToneSlider.setBounds(revbXOffset + 40, revYOffset + 8, 40, 40);
    reverbMixSlider.setBounds(revbXOffset + 80, revYOffset + 8, 40, 40);
    reverbLed.setBounds(revbXOffset + 50, revYOffset + 81, 22,22);
}
