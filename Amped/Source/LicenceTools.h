

/*
  ==============================================================================

    LicenceTools.h
    Created: 19 Jan 2020 4:18:53pm
    Author:  Veikko Tapaninen

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class LicenceTools {

public:

    LicenceTools();

    virtual ~LicenceTools();

    bool isValidLicence();

    JUCE_DECLARE_SINGLETON(LicenceTools, false)


private:
    std::unique_ptr<papupata::licensing::LicenseFile> licenceFile;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LicenceTools)


};





