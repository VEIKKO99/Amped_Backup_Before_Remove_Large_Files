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
public:
    static const int AmpButtonBarX = 290;
    static const int AmpButtonBarY = 453;
    static const int AmpButtonBarW = 620;
    static const int AmpButtonBarH = 90;
    
    constexpr static const double AmpButtonMax = 59.0;
    constexpr static const double AmpButtonMin = 0.0;
    constexpr static const double AmpButtonInterval = 1.0;

    static const int ampButtonsY = 8;
    
    static const int ampButtonsWidth = 60;//AmpButtonBarW / 10; // 10 = Amount of buttons
    static const int ampButtonsHeight = AmpButtonBarH;
    
    static const int ampCompInputX = 4;
    static const int AmpCtrlSwitchX = ampCompInputX + ampButtonsWidth;
    static const int AmpCtrlDriveX = AmpCtrlSwitchX + ampButtonsWidth +2;
    static const int AmpCtrlBassX = AmpCtrlDriveX + ampButtonsWidth;
    static const int AmpCtrlMiddleX = AmpCtrlBassX + ampButtonsWidth;
    static const int AmpCtrlTrebbleX = AmpCtrlMiddleX + ampButtonsWidth;
    static const int AmpCtrlPresenceX = AmpCtrlTrebbleX + ampButtonsWidth -2;
    static const int AmpCtrlMasterX = AmpCtrlPresenceX + ampButtonsWidth;
    static const int AmpCtrlCabSimX = AmpCtrlMasterX + ampButtonsWidth;
    static const int AmpCtrlOutputX = AmpCtrlCabSimX + ampButtonsWidth;
};

