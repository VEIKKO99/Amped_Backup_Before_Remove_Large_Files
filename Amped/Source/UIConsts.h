/*
  ==============================================================================

    UIConsts.h
    Created: 14 Sep 2019 1:32:10pm
    Author:  Veikko Tapaninen

  ==============================================================================
*/

#pragma once

class Constants
{
#ifdef JUCE_DEBUG
   #define AMPED_DEBUG
#else
//   #define AMPED_DEBUG
#endif

#define AMPED_FREE

public:
    static const int AmpButtonBarX = 166;
    static const int AmpButtonBarY = 430;
#ifndef AMPED_DEBUG
    static const int AmpButtonBarW = 1000;
#else
    static const int AmpButtonBarW = 1000;
#endif

    static const Font& getAmpedFont()
    {
        static Font font (Font (Typeface::createSystemTypefaceFor (BinaryData::WorkSansRegular_ttf,
                BinaryData::WorkSansRegular_ttfSize)));
        return font;
    }

    static const int AmpButtonBarH = 90;

    constexpr static const double AmpButtonMax = 59.0;
    constexpr static const double AmpButtonMin = 0.0;
    constexpr static const double AmpButtonInterval = 1.0;

    static const int ampButtonsY = 8;
    
    static const int ampButtonsWidth = 60;//AmpButtonBarW / 10; // 10 = Amount of buttons
    static const int ampButtonsHeight = AmpButtonBarH;
    
    static const int ampCompInputX = 4;
    static const int AmpCtrlSwitchX = ampCompInputX + ampButtonsWidth + 30;
    static const int AmpCtrlDriveX = AmpCtrlSwitchX + ampButtonsWidth + 10;
    static const int AmpCtrlBassX = AmpCtrlDriveX + ampButtonsWidth + 20;
    static const int AmpCtrlMiddleX = AmpCtrlBassX + ampButtonsWidth + 20;
    static const int AmpCtrlTrebbleX = AmpCtrlMiddleX + ampButtonsWidth + 20;
    static const int AmpCtrlPresenceX = AmpCtrlTrebbleX + ampButtonsWidth + 96;
    static const int AmpCtrlMasterX = AmpCtrlPresenceX + ampButtonsWidth +20;
    static const int AmpCtrlCabSimX = AmpCtrlMasterX + ampButtonsWidth +30;
    static const int AmpCtrlOutputX = AmpCtrlCabSimX + ampButtonsWidth +12;
};

