/*
  ==============================================================================

    AmpLookAndFeel.h
    Created: 14 Sep 2019 6:44:13pm
    Author:  Veikko Tapaninen

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "UIConsts.h"

#pragma once

class AmpLookAndFeel : public LookAndFeel_V4
{
public:
    AmpLookAndFeel()
    {
     //   setColour (Slider::thumbColourId, Colours::red);
    }
    
    inline std::string getKnobResourceFilename(float sliderPos, std::string prefix)
    {
        std::ostringstream fileName;
        fileName << prefix;
        // Create two digit postfix for file name:
        fileName << std::setw(2) << std::setfill('0') << (int)(sliderPos*Constants::AmpButtonMax);
        fileName << "_png";
        return fileName.str();
    }
    
    
    void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
                           const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override
    {
//        g.fillAll(Colours::red);
        
        std::string fileName = getKnobResourceFilename(sliderPos, "amped_knob62_rectob_00");
        int dataSize;
        auto* data = BinaryData::getNamedResource (fileName.c_str(), dataSize);
        
        Image myStrip = ImageCache::getFromMemory (data, dataSize);
        g.drawImageAt (myStrip, 0, 0);
    }
};
