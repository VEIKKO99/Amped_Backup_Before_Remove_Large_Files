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

// Current size 22x22
class OnOffLed : public Component {

public:
    OnOffLed()
    {

    }
    ~OnOffLed()
    {

    }

    void paint(Graphics& g) override
    {
        if (on) {
            Image onOffLed;
            onOffLed = ImageCache::getFromMemory(BinaryData::pedalledon_png, BinaryData::pedalledon_pngSize);
            g.drawImageAt(onOffLed, 0, 0);
        }
        else {

        }
    }

    void setOn(bool on)
    {
        if (this->on != on) {
            this->on = on;
            repaint();
        }
    }

private:
    bool on = false;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OnOffLed)
};

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

    AudioProcessorValueTreeState& valueTreeState;

    EffectsLookAndFeel effectsLookAndFeel;

};
