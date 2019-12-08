/*
  ==============================================================================

    OnOffLeds.h
    Created: 7 Dec 2019 6:02:58pm
    Author:  Veikko Tapaninen

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "UIConsts.h"

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

class ClipLed : public OnOffLed, private Timer {
public:
    ClipLed(): OnOffLed() {
        setOn(true);
   //     startTimerHz(10);
    }

    void startTimerHz(int hz) {
        startTimer(1000 / hz);
    }

    void paint(Graphics& g) override {
        OnOffLed::paint(g);

    //    drawMaxNumber(g, meterType, maxNum, source->getMaxOverallLevel (channel));
    //    g.drawText(<#const String& text#>, <#Rectangle<int> area#>, <#Justification justificationType#>, <#bool useEllipsesIfTooBig#>)

     //  const float maxDb = juce::Decibels::gainToDecibels (source->getMaxOverallLevel(0));
     //   if (maxDb > -6.0) {
     //   }
     //   else {
     //       animator.cancelAnimation(this, false);
     //       animator.fadeOut(this, 1000);
     //   }
#ifdef AMPED_DEBUG
          //  g.drawText("l: " + String(maxDb), getLocalBounds(), Justification::centred, true);
          //  source->clearMaxNum(0);
#endif
    }

    void timerCallback() override {
        if ((source && source->checkNewDataFlag())) {
            if (source) {
                const float maxDb = juce::Decibels::gainToDecibels(source->getMaxOverallLevel(0));
                source->clearMaxNum(0);
                if (maxDb > -6.0) {
                    animator.cancelAnimation(this, false);
                    this->setVisible(true);
                    this->setAlpha(1.0);
                    animator.fadeOut(this, 2000);
                }
                source->resetNewDataFlag();
            }
        //    repaint();
        }
    }

      /*
        if (fadedIn == false) {
            fadedIn = true;
            animator.fadeOut(this, 500);
        }
        else {
            fadedIn = false;
            animator.fadeIn(this, 50);
        }
    }*/

    void setMeterSource (FFAU::LevelMeterSource* source) {
        this->source = source;
    }

private:
    ComponentAnimator animator;
    bool fadedIn = false;

    juce::WeakReference<FFAU::LevelMeterSource> source;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ClipLed)

};