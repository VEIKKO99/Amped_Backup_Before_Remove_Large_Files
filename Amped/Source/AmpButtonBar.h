/*
  ==============================================================================

    AmpButtonBar.h
    Created: 14 Sep 2019 12:21:50pm
    Author:  Veikko Tapaninen

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "AmpLookAndFeel.h"

//==============================================================================
/*
*/
class AmpButtonBar    : public Component
{
public:
    AmpButtonBar();
    ~AmpButtonBar();

    void paint (Graphics&) override;
    void resized() override;

private:
    void initSliderComponent(Slider& slider);
    void setAmpComponentBounds(Component& component, int xCoord);
    
private:
    
    Slider inputSlider;
    ToggleButton fxSwitch;
    Slider driveSlider;
    Slider bassSlider;
    Slider middleSlider;
    Slider trebleSlider;
    Slider presenceSlider;
    Slider masterSlider;
    ToggleButton cabSimSwitch;
    Slider outputSlider;
    
    AmpLookAndFeel ampLookAndFeel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AmpButtonBar)
    
};
