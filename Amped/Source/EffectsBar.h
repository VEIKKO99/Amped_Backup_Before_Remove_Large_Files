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

typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
typedef AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;

//==============================================================================
/*
*/
class EffectsBar    : public Component
{
public:
    EffectsBar(AudioProcessorValueTreeState& vts);
    ~EffectsBar();

    void paint (Graphics&) override;
    void resized() override;

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

    AudioProcessorValueTreeState& valueTreeState;

    EffectsLookAndFeel effectsLookAndFeel;

};
