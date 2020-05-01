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
    background = ImageCache::getFromMemory (BinaryData::_1200x289pedals_png, BinaryData::_1200x289pedals_pngSize);
    g.drawImageAt(background, 0, 0);
}

void EffectsBar::resized()
{
    // Overdrive:
    int driveXOffset = 238;
    int driveYOffset = 26;
    onOffButton.setBounds(driveXOffset + 10, driveYOffset + 143, 120, 80);
    driveSlider.setBounds(driveXOffset, driveYOffset + 8, 60, 60);
    toneSlider.setBounds(driveXOffset + 40, driveYOffset +8, 60, 60);
    levelSlider.setBounds(driveXOffset + 80, driveYOffset +8, 60, 60);
    odLed.setBounds(driveXOffset + 59, driveYOffset, 22, 22);

    // Noise gate:
    int ngXOffset = 49;
    int ngYOffset = 26;
    ngOnOffButton.setBounds(ngXOffset,  ngYOffset + 143, 120, 80);
    ngThreshold.setBounds(ngXOffset + 28, ngYOffset + 8, 60, 60);
    ngLed.setBounds(ngXOffset + 48, ngYOffset ,22, 22);

    // Reverb:
    int revbXOffset = 1032;
    int revYOffset = 26;
    revbOnOffButton.setBounds(revbXOffset + 10, revYOffset + 143, 120, 80);
    reverbSizeSlider.setBounds(revbXOffset -2, revYOffset + 8, 60, 60);
    reverbToneSlider.setBounds(revbXOffset + 40, revYOffset + 8, 60, 60);
    reverbMixSlider.setBounds(revbXOffset + 80, revYOffset + 8, 60, 60);
    reverbLed.setBounds(revbXOffset + 58, revYOffset, 22,22);
    
    // Reverb:
    int dlyXOffset = 838;
    int dlyYOffset = 96;
    dlyOnOffButton.setBounds(dlyXOffset + 10, dlyYOffset + 100, 120, 80);
    dlyTimeSlider.setBounds(dlyXOffset -2, dlyYOffset + 8, 60, 60);
    dlyFeedbackSlider.setBounds(dlyXOffset + 40, dlyYOffset + 8, 60, 60);
    dlyMixSlider.setBounds(dlyXOffset + 80, dlyYOffset + 8, 60, 60);
    delayLed.setBounds(dlyXOffset + 58, dlyYOffset - 40, 22,22);
}
