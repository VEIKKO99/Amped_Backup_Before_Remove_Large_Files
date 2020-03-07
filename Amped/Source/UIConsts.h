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
  // #define AMPED_DEBUG
#else
 //  #define AMPED_DEBUG
#endif

#define AMPED_FREE

public:
    static const int AmpButtonBarX = 290;
    static const int AmpButtonBarY = 453;
#ifndef AMPED_DEBUG
    static const int AmpButtonBarW = 620;
#else
    static const int AmpButtonBarW = 880;
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
    static const int AmpCtrlSwitchX = ampCompInputX + ampButtonsWidth + 5;
    static const int AmpCtrlDriveX = AmpCtrlSwitchX + ampButtonsWidth - 1;
    static const int AmpCtrlBassX = AmpCtrlDriveX + ampButtonsWidth;
    static const int AmpCtrlMiddleX = AmpCtrlBassX + ampButtonsWidth -1;
    static const int AmpCtrlTrebbleX = AmpCtrlMiddleX + ampButtonsWidth -1;
    static const int AmpCtrlPresenceX = AmpCtrlTrebbleX + ampButtonsWidth -4;
    static const int AmpCtrlMasterX = AmpCtrlPresenceX + ampButtonsWidth;
    static const int AmpCtrlCabSimX = AmpCtrlMasterX + ampButtonsWidth -2;
    static const int AmpCtrlOutputX = AmpCtrlCabSimX + ampButtonsWidth +2;
};

