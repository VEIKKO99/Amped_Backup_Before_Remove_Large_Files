/*
  ==============================================================================

    SoundSettingsModel.h
    Created: 30 Nov 2019 8:40:37pm
    Author:  Veikko Tapaninen

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "AdminSettingsUtil.h"

class SoundSettingsModel {

public:
    SoundSettingsModel() {
         initModel();
    }

    std::shared_ptr<SoundSettings> getCurrentSetting() {
        if (currentSound < settings.size())
            return settings[currentSound];
        else if (settings.size() > 0)
            return settings[0];
        else
            return nullptr;
    }

    void nextSetting()
    {
        currentSound++;
        if (currentSound >= settings.size())
            currentSound = 0;
    }

    int currentSettingIndex()
    {
        return currentSound;
    }

    void prevSetting()
    {
       currentSound--;
       if (currentSound <= 0)
           currentSound = settings.size() -1;
    }

    int getSize() {
        return settings.size();
    }

    std::shared_ptr<SoundSettings> getSettingsWithIndex(int index)
    {
        return settings[index];
    }

    void selectSettingWithIndex(int settingIndex)
    {
        if (settingIndex >=0 && settingIndex < settings.size())
        {
            currentSound = settingIndex;
        }
    }

private:

    int currentSound = 0;

    void initModel() {
       auto amps = String::createStringFromData(BinaryData::amps_xml, BinaryData::amps_xmlSize);
       XmlDocument xmlDocument(amps);
       auto root = xmlDocument.getDocumentElement();
       auto ampElement = root->getFirstChildElement();
       while (ampElement != nullptr) {
           if (!ampElement->getTagName().compare("Amp")) {
               auto oneAmpFileName = ampElement->getStringAttribute("fileName");
               int oneAmpDataSize = 0;
               auto oneAmpData = getBinaryDataWithOriginalFileName(oneAmpFileName, oneAmpDataSize);
               auto s = String::createStringFromData(oneAmpData, oneAmpDataSize);
               XmlDocument xmlDocument(s);
               auto xmlElement = xmlDocument.getDocumentElement();
               auto oneSound = std::make_shared<SoundSettings>();
               oneSound->readFromXml(xmlElement.get(), "");
               settings.push_back(oneSound);
           }
           ampElement = ampElement->getNextElement();
       }
       // auto s = String::createStringFromData(BinaryData::Fluff_5034_apd, BinaryData::Fluff_5034_apdSize);
       // auto oneSound = std::make_shared<SoundSettings>();
       // XmlDocument xmlDocument(s);
       // auto xmlElement = xmlDocument.getDocumentElement();
       // oneSound->readFromXml(xmlElement.get(), "");
       // settings.push_back(oneSound);
    }

    std::vector<std::shared_ptr<SoundSettings>> settings;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SoundSettingsModel)
};

