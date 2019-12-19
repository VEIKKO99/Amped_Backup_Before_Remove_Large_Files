/*
  ==============================================================================

    AmpLookAndFeel.h
    Created: 14 Sep 2019 6:44:13pm
    Author:  Veikko Tapaninen

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "UIConsts.h"
#include "AdminSettingsUtil.h"
#pragma once

class AmpLookAndFeelBase: public LookAndFeel_V4 {

protected:
    inline std::string getKnobResourceFilename(float sliderPos, std::string prefix)
    {
        std::ostringstream fileName;
        fileName << prefix;
        // Create two digit postfix for file name:
        fileName << std::setw(2) << std::setfill('0') << (int)(sliderPos*Constants::AmpButtonMax);
        fileName << "_png";
        return fileName.str();
    }

    void drawRotaryS(const Graphics &g, const std::string &fileName) const {
        int dataSize;
        auto* data = BinaryData::getNamedResource (fileName.c_str(), dataSize);

        Image myStrip = ImageCache::getFromMemory (data, dataSize);
        g.drawImageAt (myStrip, 0, 0);
    }
};

class EffectsLookAndFeel : public AmpLookAndFeelBase {

    void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
            const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override
    {
        std::string fileName = getKnobResourceFilename(sliderPos, "amped_knob_pedal_00");
        drawRotaryS(g, fileName);
    }

    void drawToggleButton (Graphics& g,
            ToggleButton& button,
            bool isMouseOverButton,
            bool isButtonDown) override
    {
    }
};

class ThreeWaySwitchSliderLookAndFeel : public AmpLookAndFeelBase {
    void drawLinearSlider (Graphics& g, int x, int y, int width, int height,
            float sliderPos, float minSliderPos, float maxSliderPos,
            const Slider::SliderStyle style, Slider& slider) override
    {
        AmpLookAndFeelBase::drawLinearSlider(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
        Logger::getCurrentLogger()->writeToLog("Draw sliderPos:" + String(sliderPos) + "min:" + String(minSliderPos) + " maxSliderPos:" + String(maxSliderPos));

     //   std::string fileName;
     //   if (sliderPos < 1.0)
     //       fileName = "amped_switch62_0000_png";
     //   else if (sliderPos >= 1.0 && sliderPos < 2.0)
     //       fileName = "amped_switch62_0010_png";
     //   else
     //       fileName = "amped_switch62_0020_png";

     //   drawRotaryS(g, fileName);
    }
};

class AmpLookAndFeel : public AmpLookAndFeelBase
{
public:
    AmpLookAndFeel(ISoundSettingsChanged* settings)
    {
        this->settings = settings;
     //   setColour (Slider::thumbColourId, Colours::red);
    }

    void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
                           const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override
    {
        std::string fileName = getKnobResourceFilename(sliderPos, settings->getCurrentSettings()->uiSettings.getCurrentKnobName().toStdString());
        drawRotaryS(g, fileName);
    }

    void drawToggleButton (Graphics& g,
                           ToggleButton& button,
                           bool isMouseOverButton,
                           bool isButtonDown) override 
    {
        if (button.hasKeyboardFocus (true))
        {
            g.setColour (button.findColour (TextEditor::focusedOutlineColourId));
            g.drawRect (0, 0, button.getWidth(), button.getHeight());
        }
        
        std::string fileName = "";
        
        if (button.getToggleState()) {
             fileName = "amped_switch62_0020_png";
        }
        else {
            fileName = "amped_switch62_0000_png";
        }
        
        int dataSize;
        auto* data = BinaryData::getNamedResource (fileName.c_str(), dataSize);
        
        Image myStrip = ImageCache::getFromMemory (data, dataSize);
        g.drawImageAt (myStrip, 0, 0);
        
        
    /*    const int tickWidth = jmin (20, button.getHeight() - 4);
        
        drawTickBox (g, button, 4.0f, (button.getHeight() - tickWidth) * 0.5f,
                     (float) tickWidth, (float) tickWidth,
                     button.getToggleState(),
                     button.isEnabled(),
                     isMouseOverButton,
                     isButtonDown);
        
        g.setColour (button.findColour (ToggleButton::textColourId));
        g.setFont (jmin (15.0f, button.getHeight() * 0.6f));
        
        if (! button.isEnabled())
            g.setOpacity (0.5f);
        
        const int textX = tickWidth + 5;
        
        g.drawFittedText (button.getButtonText(),
                          textX, 4,
                          button.getWidth() - textX - 2, button.getHeight() - 8,
                          Justification::centredLeft, 10);
    
     */
     }

private:
    ISoundSettingsChanged* settings;
    
};
