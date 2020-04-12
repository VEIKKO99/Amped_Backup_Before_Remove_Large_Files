/*
  ==============================================================================

    EffectsBar.h
    Created: 17 Nov 2019 3:52:37pm
    Author:  Veikko Tapaninen

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "AmpLookAndFeel.h"
#include "OnOffLeds.h"
typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
typedef AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;



//==============================================================================
/*
*/
class EffectsBar    : public Component,
                      public Button::Listener
{
public:
    EffectsBar(AudioProcessorValueTreeState& vts);
    ~EffectsBar();

    void paint (Graphics&) override;
    void resized() override;
    void buttonClicked (Button* button) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EffectsBar)

    void initSliderComponent(Slider& slider, String vtsName, std::unique_ptr<SliderAttachment>& attachment);

    Slider driveSlider;
    std::unique_ptr<SliderAttachment> driveAttachment;

    Slider toneSlider;
    std::unique_ptr<SliderAttachment> toneAttachment;

    Slider levelSlider;
    std::unique_ptr<SliderAttachment> levelAttachment;

    ToggleButton onOffButton;
    std::unique_ptr<ButtonAttachment> onOffButtonAttachment;

    Slider ngThreshold;
    std::unique_ptr<SliderAttachment> ngThresholdAttachment;

    ToggleButton ngOnOffButton;
    std::unique_ptr<ButtonAttachment> ngOnOffButtonAttachment;

    OnOffLed ngLed;
    OnOffLed odLed;


    // Reverbdemo:

    OnOffLed revbLed;

    ToggleButton revbOnOffButton;
    std::unique_ptr<ButtonAttachment> revbOnOffButtonAttachment;

    Slider revbRoom;
    std::unique_ptr<SliderAttachment> revbRoomAttachment;

    Slider revbDamping;
    std::unique_ptr<SliderAttachment> revbDampingAttachment;

    Slider revbWLev;
    std::unique_ptr<SliderAttachment> revbWLevAttachment;

    Slider revbDLev;
    std::unique_ptr<SliderAttachment> revbDLevAttachment;

    Slider revbWidth;
    std::unique_ptr<SliderAttachment> revbWidthAttachment;

    Slider revbFreeze;
    std::unique_ptr<SliderAttachment> revbFreezeAttachment;




    AudioProcessorValueTreeState& valueTreeState;

    EffectsLookAndFeel effectsLookAndFeel;

};
