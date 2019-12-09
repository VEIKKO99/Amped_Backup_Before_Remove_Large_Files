/*
  ==============================================================================

    AmpButtonBar.h
    Created: 14 Sep 2019 12:21:50pm
    Author:  Veikko Tapaninen

  ==============================================================================
*/

#pragma once

#include "OnOffLeds.h"
#include "PluginProcessor.h"
#include "../JuceLibraryCode/JuceHeader.h"
#include "AmpLookAndFeel.h"
#include "UIConsts.h"

//==============================================================================
/*
*/
class AmpButtonBar    : public Component
{
    typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    typedef AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;
    
public:
    AmpButtonBar(AudioProcessorValueTreeState& vts,  AmpLookAndFeel& lookAndFeel, AmpedAudioProcessor& processor);
    ~AmpButtonBar();

    void paint (Graphics&) override;
    void resized() override;

private:
    void initSliderComponent(Slider& slider, String vtsName, std::unique_ptr<SliderAttachment>& attachment);
    void setAmpComponentBounds(Component& component, int xCoord);
    
private:
    
    Slider inputSlider;
    std::unique_ptr<SliderAttachment> inputAttachment;

    ToggleButton fxSwitch;
    std::unique_ptr<ButtonAttachment> fxAttachment;

    Slider driveSlider;
    std::unique_ptr<SliderAttachment> driveAttachment;

    Slider bassSlider;
    std::unique_ptr<SliderAttachment> bassAttachment;

    Slider middleSlider;
    std::unique_ptr<SliderAttachment> middleAttachment;

    Slider trebleSlider;
    std::unique_ptr<SliderAttachment> trebleAttachment;

    Slider presenceSlider;
    std::unique_ptr<SliderAttachment> presenceAttachment;

    Slider masterSlider;
    std::unique_ptr<SliderAttachment> masterAttachment;

    ToggleButton cabSimSwitch;
    std::unique_ptr<ButtonAttachment> cabSimAttachment;

    Slider outputSlider;
    std::unique_ptr<SliderAttachment> outputAttachment;

    ClipLed inputClipLed;

#ifdef AMPED_DEBUG
    ToggleButton matchIRSwitch;
    std::unique_ptr<ButtonAttachment> matchAttachment;
#endif

    AudioProcessorValueTreeState& valueTreeState;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AmpButtonBar)
    
};
