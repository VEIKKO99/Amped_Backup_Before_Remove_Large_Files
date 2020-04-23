/*
  ==============================================================================

    SoundSettingsModel.h
    Created: 30 Nov 2019 8:40:37pm
    Author:  Veikko Tapaninen

  ==============================================================================
*/

#pragma once

#include <LicenceTools.h>
#include "../JuceLibraryCode/JuceHeader.h"
#include "AdminSettingsUtil.h"

class SoundSettingsModel {

public:
    SoundSettingsModel() {
        Logger::getCurrentLogger()->writeToLog("SoundSettingsModel INIT");
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
        auto current = currentSound + 1;
        if (current >= settings.size())
            current = 0;
        selectSettingWithIndex(current);
    }

    int currentSettingIndex()
    {
        return currentSound;
    }

    void prevSetting()
    {
       auto current = currentSound - 1;
       if (current <= 0)
           current = settings.size() -1;
        selectSettingWithIndex(current);
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
            if (settingIndex > 0 && !LicenceTools::getInstance()->isValidLicence()) settingIndex = 0;
            currentSound = settingIndex;
        }
    }

private:

    int currentSound = 0;

    static String decodeString (BlowFish& blowfish, MemoryBlock mb)
    {
        blowfish.decrypt (mb);
        return mb.toString();
    }

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

               String key = "<color=\"white\"/>";
               BlowFish blowFish (key.toUTF8(), (int) key.getNumBytesAsUTF8());
               MemoryBlock memoryBlock;
               memoryBlock.fromBase64Encoding (s);
               auto decoded = decodeString(blowFish, memoryBlock);
               XmlDocument xmlDocument(decoded);
               auto xmlElement = xmlDocument.getDocumentElement();
               if (xmlElement != nullptr) {
                   auto oneSound = std::make_shared<SoundSettings>();
                   oneSound->readFromXml(xmlElement.get(), "");
                   settings.push_back(oneSound);
               }
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

