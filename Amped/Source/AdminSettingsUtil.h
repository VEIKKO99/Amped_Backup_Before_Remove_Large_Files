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
#include "Consts.h"

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

    XmlElement* serializeToXml() {
        XmlElement* settings = new XmlElement ("TubeSetting");
        settings->setAttribute("vPlus", vPlus);
        settings->setAttribute("rk", rk);
        settings->setAttribute("vk0", vk0);
        settings->setAttribute("rp", rp);
        settings->setAttribute("lowPassFbk", lowPassFbk);
        settings->setAttribute("tubeType", tubeType);

        return settings;
    }

    void readFromXml(XmlElement& element) {
        this->vPlus = element.getDoubleAttribute("vPlus", 250.0);
        this->rk = element.getDoubleAttribute("rk", 2700.0);
        this->vk0 = element.getDoubleAttribute("vk0", 2.5);
        this->rp = element.getDoubleAttribute("rp",  100000.00);
        this->lowPassFbk = element.getDoubleAttribute("lowPassFbk", 0.0);
        this->tubeType = element.getIntAttribute("tubeType", 0);
    }

};

class IRSettings
{
public:
    String irFileName = "";
    float gain = 6.0;

    XmlElement* serializeToXml() {
        XmlElement* settings = new XmlElement ("IRSetting");
        settings->setAttribute("irFileName", irFileName);
        settings->setAttribute("gain", gain);
        return settings;
    }

    void readFromXml(XmlElement& element) {
        this->irFileName = element.getStringAttribute("irFileName");
        this->gain = static_cast<float>(element.getDoubleAttribute("gain", 6.0));
    }
};

class EQSettings
{
public:
    String lowIrFileName = "";
    String highIrFileName = "";
    float gain = 6.0;
    float realisticGain = 1.0;

    XmlElement* serializeToXml() {
        XmlElement* settings = new XmlElement ("EQSettings");
        settings->setAttribute("lowIrFileName", lowIrFileName);
        settings->setAttribute("highIrFileName", highIrFileName);

        settings->setAttribute("gain", gain);
        settings->setAttribute("realisticGain", realisticGain);
        return settings;
    }

    void readFromXml(XmlElement& element) {
        this->lowIrFileName = element.getStringAttribute("lowIrFileName");
        this->highIrFileName = element.getStringAttribute("highIrFileName");

        this->gain = static_cast<float>(element.getDoubleAttribute("gain"));
        this->realisticGain = static_cast<float>(element.getDoubleAttribute("realisticGain"));
    }
};

enum EQType {
    kBassEq,
    kMiddleEq,
    kTrebleEq,
    kPresence,
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

    XmlElement* serializeToXml() {
        XmlElement* settings = new XmlElement ("UISettings");
        settings->setAttribute("konbFilename", getCurrentKnobName());
        settings->setAttribute("mainBackgroundImageFileName", mainBackgroundImageFileName);
        settings->setAttribute("selectedKnob", selectedKnob);
        return settings;
    }

    void readFromXml(XmlElement& element) {
        this->selectedKnob = element.getIntAttribute("selectedKnob", 0);
        this->mainBackgroundImageFileName = element.getStringAttribute(mainBackgroundImageFileName);
    }
};

class InternalAmpSettings {
public:
    
    PreAmp::EInputType inputType = PreAmp::EInputType::kGuitarKit;
    TubeSettings preAmpTubes[2];
    // Please note that tis power amp tube is duplicated on hornet side.
    TubeSettings powerAmpTube;

    float hornetDrive = 0.5f;
    float hornetPresence = 0.5f;

    IRSettings cabIr;
    IRSettings ampIr;

    EQSettings eqs[kEQSize];
    
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

    XmlElement* serializeToXml() {
        XmlElement* settings = new XmlElement ("InternalAmpSettings");

        // Tube Settings:
        XmlElement* tubeSettings = settings->createNewChildElement ("TubeSettings");
        XmlElement* preTube1 = tubeSettings->createNewChildElement ("PreAmpTube_1");
        preTube1->addChildElement(preAmpTubes[0].serializeToXml());
        XmlElement* preTube2 = tubeSettings->createNewChildElement ("PreAmpTube_2");
        preTube2->addChildElement(preAmpTubes[1].serializeToXml());
        XmlElement* pAmpTube = tubeSettings->createNewChildElement ("PowerAmpTube");
        pAmpTube->addChildElement(powerAmpTube.serializeToXml());

        settings->setAttribute("inputType", inputType);
        settings->setAttribute("hornetDrive", hornetDrive);
        settings->setAttribute("hornetPresence", hornetPresence);

        // Ir Settings:
        XmlElement* irsettings = settings->createNewChildElement("IRSettings");
        irsettings->createNewChildElement("CabIr")->addChildElement(cabIr.serializeToXml());
        irsettings->createNewChildElement("AmpIr")->addChildElement(ampIr.serializeToXml());

        // Eq Settings:
        XmlElement* eqSettings = settings->createNewChildElement("EQSettings");
        for (int i = 0; i < kEQSize; i++) {
            eqSettings->addChildElement(eqs[i].serializeToXml());
        }

        return settings;
    }

    void readFromXml(XmlElement& element) {
        this->inputType = static_cast<PreAmp::EInputType>(element.getIntAttribute("inputType", 0));
        this->hornetDrive = static_cast<float>(element.getDoubleAttribute("hornetDrive", 0.5));
        this->hornetPresence = static_cast<float>(element.getDoubleAttribute("hornetPresence", 0.5));

        XmlElement* tubeSettings = element.getChildByName("TubeSettings");
        preAmpTubes[0].readFromXml(*tubeSettings->getChildByName("PreAmpTube_1"));
        preAmpTubes[1].readFromXml(*tubeSettings->getChildByName("PreAmpTube_2"));
        powerAmpTube.readFromXml(*tubeSettings->getChildByName("PowerAmpTube"));
    }
};

class MaxMin
{
public:
    float min = -10.0;
    float max = 10.0;

    XmlElement* serializeToXml() {
        XmlElement* settings = new XmlElement ("MaxMin");
        settings->setAttribute("min", min);
        settings->setAttribute("max", max);
        return settings;
    }

    void readFromXml(XmlElement& element) {
        this->min = (float)element.getDoubleAttribute("min", -10.0);
        this->max = (float)element.getDoubleAttribute("max", 10.0);
    }
};

class SoundSettings {
public:
    SoundSettings() {
    }

    InternalAmpSettings ampSettings;

    // Gain settings:
    MaxMin gainSettings[GainProcessorId::SIZE];
    UISettings uiSettings;

    std::shared_ptr<XmlElement> serializeToXml() {
       auto rootElement = std::make_shared<XmlElement>("SoundSettings");
       rootElement->addChildElement(uiSettings.serializeToXml());
       XmlElement* minMaxElement = new XmlElement("MaxMinSettings");
       rootElement->addChildElement(minMaxElement);
       for (int i = 0; i < GainProcessorId::SIZE; i++) {
           minMaxElement->addChildElement(gainSettings[i].serializeToXml());
       }
       rootElement->addChildElement(ampSettings.serializeToXml());
       return rootElement;
    }
};

class ISoundSettingsChanged
{
public:
    virtual ~ISoundSettingsChanged() {}
    virtual void settingChanged() = 0;
    virtual std::shared_ptr<SoundSettings> getCurrentSettings() = 0;
};


