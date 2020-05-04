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

    OnOffLed reverbLed;
    OnOffLed delayLed;

    
    ToggleButton revbOnOffButton;
    std::unique_ptr<ButtonAttachment> revbOnOffButtonAttachment;

    Slider reverbSizeSlider;
    std::unique_ptr<SliderAttachment> reverbSizeAttachment;

    Slider reverbToneSlider;
    std::unique_ptr<SliderAttachment> reverbToneAttachment;

    Slider reverbMixSlider;
    std::unique_ptr<SliderAttachment> reverbMixAttachment;

    ToggleButton dlyOnOffButton;
    std::unique_ptr<ButtonAttachment> dlyOnOffButtonAttachment;

    Slider dlyTimeSlider;
    std::unique_ptr<SliderAttachment> dlyTimeAttachment;

    Slider dlyFeedbackSlider;
    std::unique_ptr<SliderAttachment> dlyFeedBackttachment;

    Slider dlyMixSlider;
    std::unique_ptr<SliderAttachment> dlyMixAttachment;
    
    
    AudioProcessorValueTreeState& valueTreeState;

    EffectsLookAndFeel effectsLookAndFeel;

};
