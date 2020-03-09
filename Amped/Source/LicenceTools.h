

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


    /**
     * Install a license.
     * Validates the license before storing it.
     * \retval true if the license was successfully validated and installed.
     */
    bool installLicense(const juce::String &license)
    {
        juce::OwnedArray<papupata::licensing::Challenge> challenges(papupata::licensing::Challenge::generateChallenges());
        std::unique_ptr<papupata::licensing::License> lic(new papupata::licensing::License(license, challenges));

        return licenceFile->addLicense(std::move(lic));
    }

    papupata::licensing::License* getLicence()
    {
        auto&& licenses = licenceFile->getLicenses();
        return licenses.size() > 0 ? licenses[0] : nullptr;
    }

    JUCE_DECLARE_SINGLETON(LicenceTools, false)

private:
    std::unique_ptr<papupata::licensing::LicenseFile> licenceFile;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LicenceTools)
};





