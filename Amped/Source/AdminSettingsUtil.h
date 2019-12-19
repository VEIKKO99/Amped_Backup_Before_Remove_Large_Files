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

inline String getLocalFilename(String fileName, String rootFilePath) {
    // Windows style path:
    String name = fileName.substring (fileName.lastIndexOfChar ('\\') + 1);
    if (name.length() == 0) {
        // OS X path:
        name = fileName.substring (fileName.lastIndexOfChar ('/') + 1);
    }
    String nameWithPath = rootFilePath + name;
    Logger::getCurrentLogger()->writeToLog("Full local path: " + nameWithPath);
    return nameWithPath;
}

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

    void readFromXml(XmlElement* root) {
       // auto element = root->getChildByName("TubeSetting");
        this->vPlus = root->getDoubleAttribute("vPlus", 250.0);
        this->rk = root->getDoubleAttribute("rk", 2700.0);
        this->vk0 = root->getDoubleAttribute("vk0", 2.5);
        this->rp = root->getDoubleAttribute("rp",  100000.00);
        this->lowPassFbk = root->getDoubleAttribute("lowPassFbk", 0.0);
        this->tubeType = root->getIntAttribute("tubeType", 0);
    }
};

class IRSettings
{
public:
    String irFileName = "";
    String overridingIrFileName = "";
    float gain = 6.0;

    XmlElement* serializeToXml() {
        XmlElement* settings = new XmlElement ("IRSetting");
        settings->setAttribute("irFileName", irFileName);
        settings->setAttribute("overridingIrFileName", overridingIrFileName);
        settings->setAttribute("gain", gain);
        return settings;
    }

    void readFromXml(XmlElement* root, String rootFilePath) {
        auto element = root->getChildByName("IRSetting");
        this->irFileName = getLocalFilename(element->getStringAttribute("irFileName"), rootFilePath);
        this->overridingIrFileName = element->getStringAttribute("overridingIrFileName");
        this->gain = static_cast<float>(element->getDoubleAttribute("gain", 6.0));
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

    void readFromXml(XmlElement* element, String rootFilePath) {
        this->lowIrFileName = getLocalFilename(element->getStringAttribute("lowIrFileName"), rootFilePath);
        this->highIrFileName = getLocalFilename(element->getStringAttribute("highIrFileName"), rootFilePath);

        this->gain = static_cast<float>(element->getDoubleAttribute("gain"));
        this->realisticGain = static_cast<float>(element->getDoubleAttribute("realisticGain"));
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

    void readFromXml(XmlElement* element, String rootFilePath) {
        auto uiSettingsElement = element->getChildByName("UISettings");
        this->selectedKnob = uiSettingsElement->getIntAttribute("selectedKnob", 0);
        this->mainBackgroundImageFileName = getLocalFilename(uiSettingsElement->getStringAttribute("mainBackgroundImageFileName"), rootFilePath);
    }
};

#define MAX_AMOUNT_OF_PREAMP_TUBES 4

class InternalAmpSettings {
public:

    PreAmp::EInputType inputType = PreAmp::EInputType::kGuitarKit;
    TubeSettings preAmpTubes[MAX_AMOUNT_OF_PREAMP_TUBES];
    // Please note that tis power amp tube is duplicated on hornet side.
    TubeSettings powerAmpTube;

    float hornetDrive = 0.5f;
    float hornetPresence = 0.5f;

    IRSettings cabIr;
    IRSettings ampIr;

    // Not read or write to xml:
    int overSample = 4;

    int amountOfPreAmpTubes = 1;

    EQSettings eqs[kEQSize];
    
public:
    InternalAmpSettings() {
        /*
        preAmpTubes[0].tubeType = TUBE_TABLE_12AX7_68k;
        preAmpTubes[1].tubeType = TUBE_TABLE_12AX7_68k;

        // Please note that tis power amp tube is duplicated on hornet side.
        powerAmpTube.tubeType = TUBE_TABLE_6L6CG_68k;
        powerAmpTube.vPlus = 468;
        powerAmpTube.rk = 0.;
        powerAmpTube.rp = 3.4e3;
        powerAmpTube.vk0 = 0;
        powerAmpTube.lowPassFbk = 338.;
         */
    }

    XmlElement* serializeToXml() {
        XmlElement* settings = new XmlElement ("InternalAmpSettings");

        // Tube Settings:
        XmlElement* tubeSettings = settings->createNewChildElement ("TubeSettings");
        tubeSettings->setAttribute("amountOfPreampTubes", amountOfPreAmpTubes);
        XmlElement* preTubes = tubeSettings->createNewChildElement("PreAmpTubes");
        for (int i = 0; i < amountOfPreAmpTubes; i++) {
            preTubes->addChildElement(preAmpTubes[i].serializeToXml());
        }
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

    void readFromXml(XmlElement* root, String rootFilePath) {
        XmlElement* element = root->getChildByName("InternalAmpSettings");

        this->inputType = static_cast<PreAmp::EInputType>(element->getIntAttribute("inputType", 0));
        this->hornetDrive = static_cast<float>(element->getDoubleAttribute("hornetDrive", 0.5));
        this->hornetPresence = static_cast<float>(element->getDoubleAttribute("hornetPresence", 0.5));

        XmlElement* tubeSettings = element->getChildByName("TubeSettings");
        this->amountOfPreAmpTubes = tubeSettings->getIntAttribute("amountOfPreampTubes", 1);

        XmlElement* preTubeSettings = tubeSettings->getChildByName("PreAmpTubes");
        if (preTubeSettings != nullptr) {
            int numOfTubes = preTubeSettings->getNumChildElements();
            for (int i = 0; i < numOfTubes; i++) {
                if (i < MAX_AMOUNT_OF_PREAMP_TUBES) {
                    preAmpTubes[i].readFromXml(preTubeSettings->getChildElement(i));
                }
            }
        }
        powerAmpTube.readFromXml(tubeSettings->getChildByName("PowerAmpTube")->getChildByName("TubeSetting"));

        XmlElement* irElements = element->getChildByName("IRSettings");
        cabIr.readFromXml(irElements->getChildByName("CabIr"), rootFilePath);
        ampIr.readFromXml(irElements->getChildByName("AmpIr"), rootFilePath);

        XmlElement* eqSettings = element->getChildByName("EQSettings");
        for (int i = 0; i < eqSettings->getNumChildElements(); i++) {
            if (i < kEQSize) {
                eqs[i].readFromXml(eqSettings->getChildElement(i), rootFilePath);
            }
        }
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

    void readFromXml(XmlElement* element) {
        this->min = (float)element->getDoubleAttribute("min", -10.0);
        this->max = (float)element->getDoubleAttribute("max", 10.0);
    }
};

class SoundSettings {
public:
    SoundSettings() {
        gainSettings[GainProcessorId::InputGain].min = -24;
        gainSettings[GainProcessorId::InputGain].max = 24;
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

    void readFromXml(XmlElement* root, String rootFilePath) {
        auto minMaxElements = root->getChildByName("MaxMinSettings");
        uiSettings.readFromXml(root, rootFilePath);
        for (int i = 0; i < minMaxElements->getNumChildElements(); i++) {
            if (i < GainProcessorId::SIZE) {
                gainSettings[i].readFromXml(minMaxElements->getChildElement(i));
            }
        }
        ampSettings.readFromXml(root, rootFilePath);
    }
};

class ISoundSettingsChanged
{
public:
    virtual ~ISoundSettingsChanged() {}
    virtual void settingChanged() = 0;
    virtual std::shared_ptr<SoundSettings> getCurrentSettings() = 0;
};


