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
   //     Logger::getCurrentLogger()->writeToLog("Draw sliderPos:" + String(sliderPos) + "min:" + String(minSliderPos) + " maxSliderPos:" + String(maxSliderPos));

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

    Font getTextButtonFont (TextButton&, int buttonHeight) override {
        auto font = Constants::getAmpedFont();
        font.setHeight(20.0);
        return font;
    }

    Font getComboBoxFont(ComboBox& comboBox) override
    {
        auto font = Constants::getAmpedFont();
        font.setHeight(20.0);
        return font;
    }

    void drawComboBox(Graphics & g,
        int width, int height,
        bool isButtonDown,
        int buttonX, int buttonY, int buttonW, int buttonH,
        ComboBox & comboBox) override
    {
        auto buttonArea = comboBox.getLocalBounds();

        g.setColour (isButtonDown ? Colour(0xFF111111).withAlpha(0.5f) : Colour(0xFF111111));
        g.fillRect (buttonArea);
    }

    // This is taken from the super class, used currently with
    // Combobox. Modified to remove check mark.
    void drawMenuBarBackground (Graphics& g, int width, int height,
            bool, MenuBarComponent& menuBar) override
    {
        auto area = menuBar.getLocalBounds();

        g.setColour (Colour(0xFF111111));
        g.fillRect (area);

      /*  auto colour = menuBar.findColour (TextButton::buttonColourId).withAlpha (0.4f);

        Rectangle<int> r (width, height);

        g.setColour (colour.contrasting (0.15f));
        g.fillRect  (r.removeFromTop (1));
        g.fillRect  (r.removeFromBottom (1));

        g.setGradientFill (ColourGradient::vertical (colour, 0, colour.darker (0.2f), (float) height));
        g.fillRect (r);*/
    }

    // This is taken from the super class, used currently with
    // Combobox. Modified to remove check mark.
    void drawPopupMenuItem (Graphics& g, const Rectangle<int>& area,
            const bool isSeparator, const bool isActive,
            const bool isHighlighted, const bool isTicked,
            const bool hasSubMenu, const String& text,
            const String& shortcutKeyText,
            const Drawable* icon, const Colour* const textColourToUse) override
    {
        if (isSeparator)
        {
            auto r  = area.reduced (5, 0);
            r.removeFromTop (roundToInt ((r.getHeight() * 0.5f) - 0.5f));

            g.setColour (findColour (PopupMenu::textColourId).withAlpha (0.3f));
            g.fillRect (r.removeFromTop (1));
        }
        else
        {
            auto textColour = (textColourToUse == nullptr ? findColour (PopupMenu::textColourId)
                    : *textColourToUse);

            auto r  = area.reduced (1);

            if (isHighlighted && isActive)
            {
                g.setColour (findColour (PopupMenu::highlightedBackgroundColourId));
                g.fillRect (r);

                g.setColour (findColour (PopupMenu::highlightedTextColourId));
            }
            else
            {
                g.setColour (textColour.withMultipliedAlpha (isActive ? 1.0f : 0.5f));
            }

//            r.reduce (jmin (5, area.getWidth() / 20), 0);

            auto font = getPopupMenuFont();

            auto maxFontHeight = r.getHeight() / 1.3f;

            if (font.getHeight() > maxFontHeight)
                font.setHeight (maxFontHeight);

            g.setFont (font);

//            auto iconArea = r.removeFromLeft (roundToInt (maxFontHeight)).toFloat();

      /*      if (icon != nullptr)
            {
                icon->drawWithin (g, iconArea, RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize, 1.0f);
                r.removeFromLeft (roundToInt (maxFontHeight * 0.5f));
            }
            else if (isTicked)
            {
                auto tick = getTickShape (1.0f);
                g.fillPath (tick, tick.getTransformToScaleToFit (iconArea.reduced (iconArea.getWidth() / 5, 0).toFloat(), true));
            }*/

            if (hasSubMenu)
            {
                auto arrowH = 0.6f * getPopupMenuFont().getAscent();

                auto x = static_cast<float> (r.removeFromRight ((int) arrowH).getX());
                auto halfH = static_cast<float> (r.getCentreY());

                Path path;
                path.startNewSubPath (x, halfH - arrowH * 0.5f);
                path.lineTo (x + arrowH * 0.6f, halfH);
                path.lineTo (x, halfH + arrowH * 0.5f);

                g.strokePath (path, PathStrokeType (2.0f));
            }

            r.removeFromRight (3);
            g.drawFittedText (text, r, Justification::centred, 1);

            if (shortcutKeyText.isNotEmpty())
            {
                auto f2 = font;
                f2.setHeight (f2.getHeight() * 0.75f);
                f2.setHorizontalScale (0.95f);
                g.setFont (f2);

                g.drawText (shortcutKeyText, r, Justification::centredRight, true);
            }
        }
    }

    void positionComboBoxText (ComboBox& box, Label& label) override
    {
        label.setBounds (1, 1,
                box.getWidth(),
                box.getHeight() - 2);

        label.setFont (getComboBoxFont (box));
    }

    void drawButtonBackground (Graphics& g, Button& button, const Colour& backgroundColour,
            bool isMouseOverButton, bool isButtonDown) override
    {
        auto buttonArea = button.getLocalBounds();

        g.setColour (isButtonDown ? backgroundColour.withAlpha(0.5f) : backgroundColour);
        g.fillRect (buttonArea);
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
