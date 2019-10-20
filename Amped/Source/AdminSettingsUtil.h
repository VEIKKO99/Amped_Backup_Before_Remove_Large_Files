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

class TubeSettings
{
public:
    double vPlus = 250.0;
    double rk = 2700.0;
    double vk0 = 2.5;
    double rp = 100000.0;
    double lowPassFbk = 0.0;
    int tubeType = 0;
};

class InternalAmpSettings {
public:
    
    PreAmp::EInputType inputType = PreAmp::EInputType::kGuitarKit;
    TubeSettings preAmpTubes[2];
    
public:
    InternalAmpSettings() {
        preAmpTubes[0].tubeType = TUBE_TABLE_12AX7_68k;
        preAmpTubes[1].tubeType = TUBE_TABLE_12AX7_68k;
    }
};

class SoundSettings
{
public:
    SoundSettings() {}
    InternalAmpSettings ampSettings;
};

class ISoundSettingsChanged
{
public:
    virtual ~ISoundSettingsChanged() {}
    virtual void settingChanged() = 0;
    virtual std::shared_ptr<SoundSettings> getCurrentSettings() = 0;
};


