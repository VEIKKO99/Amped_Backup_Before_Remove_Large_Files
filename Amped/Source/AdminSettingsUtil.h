/*
  ==============================================================================

    AdminSettingsUtil.h
    Created: 19 Oct 2019 12:46:32pm
    Author:  Veikko Tapaninen

  ==============================================================================
*/

#pragma once
#include "original_hornet/TubeAmp.h"

class AmpedAdminSettingsWindowOverride  : public DialogWindow {
    
public:
    
    AmpedAdminSettingsWindowOverride() :
                        DialogWindow( "Admin", Colours::lime, DocumentWindow::TitleBarButtons::closeButton)
    {
        
    }
    
    void closeButtonPressed() override
    {
        setVisible(false);
    }
};

class ISoundSettingsChanged
{
    public:
        virtual ~ISoundSettingsChanged() {}
        virtual void settingChanged() = 0;
};

class TubeSettings
{
    double vPlus = 250.0;
    double rk = 2700.0;
    double vk0 = 2.5;
    double rp = 100000.0;
    double lowPassFbk = 0.0;
};

class InternalAmpSettings {
    PreAmp::EInputType inputType;
    TubeSettings preAmpTubes[4];
};

class SoundSettings
{
    InternalAmpSettings ampSettings;
};
