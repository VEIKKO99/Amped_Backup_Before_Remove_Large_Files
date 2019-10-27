/*
  ==============================================================================

    AdminSettingsUtil.h
    Created: 19 Oct 2019 12:46:32pm
    Author:  Veikko Tapaninen

  ==============================================================================
*/

#pragma once
#include "original_hornet/TubeAmp.h"
#include "../JuceLibraryCode/JuceHeader.h"


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

class IRSettings
{
public:
    String irFileName = "";
    float gain = 6.0;
};

enum EQType {
    kBassEq,
    kMiddleEq,
    kTrebleEq,
    kEQSize
};

class UISettings {
    std::string knobFileNames[9] = {"amped_knob62_chknw_00",
            "amped_knob62_chknb_00",
            "amped_knob62_dizl_000",
            "amped_knob62_frmn_00",
            "amped_knob62_mars_00",
            "amped_knob62_marss_00",
            "amped_knob62_mega_00",
            "amped_knob62_recto_00",
            "amped_knob62_rectob_00"};

public:
    String getCurrentKnobName()
    {
        return knobFileNames[selectedKnob];
    }
    int selectedKnob = 0;

    String mainBackgroundImageFileName = "";
};

class InternalAmpSettings {
public:
    
    PreAmp::EInputType inputType = PreAmp::EInputType::kGuitarKit;
    TubeSettings preAmpTubes[2];
    // Please note that tis power amp tube is duplicated on hornet side.
    TubeSettings powerAmpTube;

    float eqGain = .0f;

    IRSettings cabIr;
    IRSettings ampIr;

    IRSettings eqs[kEQSize];
    
public:
    InternalAmpSettings() {
        preAmpTubes[0].tubeType = TUBE_TABLE_12AX7_68k;
        preAmpTubes[1].tubeType = TUBE_TABLE_12AX7_68k;

        // Please note that tis power amp tube is duplicated on hornet side.
        powerAmpTube.tubeType = TUBE_TABLE_6L6CG_68k;
        powerAmpTube.vPlus = 468;
        powerAmpTube.rk = 0.;
        powerAmpTube.rp = 3.4e3;
        powerAmpTube.vk0 = 0;
        powerAmpTube.lowPassFbk = 338.;

    }
};

class MaxMin
{
public:
    float min = -10.0;
    float max = 10.0;
};

class SoundSettings {
public:
    SoundSettings() {
    }

    InternalAmpSettings ampSettings;

    // Gain settings:
    MaxMin gainSettings[3];

    UISettings uiSettings;
};

class ISoundSettingsChanged
{
public:
    virtual ~ISoundSettingsChanged() {}
    virtual void settingChanged() = 0;
    virtual std::shared_ptr<SoundSettings> getCurrentSettings() = 0;
};


