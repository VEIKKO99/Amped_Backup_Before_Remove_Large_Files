

/*
  ==============================================================================

    LicenceTools.cpp
    Created: 19 Jan 2020 4:18:53pm
    Author:  Veikko Tapaninen

  ==============================================================================
*/

#include "LicenceTools.h"
#include "UIConsts.h"

juce::OwnedArray<papupata::licensing::Challenge> papupata::licensing::Challenge::generateChallenges()
{
    juce::OwnedArray<papupata::licensing::Challenge> challenges;
    challenges.add(new papupata::licensing::Challenge(true));
    return challenges;
/*
    juce::OwnedArray<papupata::licensing::Challenge> challenges;
    challenges.add(new papupata::licensing::Challenge(true));
#ifdef JUCE_WINDOWS
    challenges.add(new papupata::licensing::Challenge(true, false, false));
	// Windows 1903 blunder check, should be conditional
    challenges.add(new papupata::licensing::Challenge(true, true, false));
    challenges.add(new papupata::licensing::Challenge(false, false, false));
    // Windows 1903 blunder check, should be conditional
    challenges.add(new papupata::licensing::Challenge(false, true, false));
#endif

    return challenges; */
}

LicenceTools::LicenceTools()
{
    licenceFile.reset(papupata::licensing::LicenseFile::getInstance());
}

LicenceTools::~LicenceTools()
{
    clearSingletonInstance();
}

bool LicenceTools::isValidLicence() {
//#ifdef AMPED_DEBUG
//	return true;
//#else
    return licenceFile->hasValidLicense();
//#endif
}

JUCE_IMPLEMENT_SINGLETON(LicenceTools)
