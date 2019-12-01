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
        return settings[0];
    }

private:
    void initModel() {
        auto s = String::createStringFromData(BinaryData::Fluff_5034_apd, BinaryData::Fluff_5034_apdSize);
        auto oneSound = std::make_shared<SoundSettings>();
        XmlDocument xmlDocument(s);
        auto xmlElement = xmlDocument.getDocumentElement();
        oneSound->readFromXml(xmlElement.get(), "");
        settings.push_back(oneSound);
    }

    std::vector<std::shared_ptr<SoundSettings>> settings;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SoundSettingsModel)
};

