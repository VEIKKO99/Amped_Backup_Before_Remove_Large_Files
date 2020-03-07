

/*
  ==============================================================================

    LicenceTools.cpp
    Created: 19 Jan 2020 4:18:53pm
    Author:  Veikko Tapaninen

  ==============================================================================
*/

#include "LicenceTools.h"

const unsigned char papupata::licensing::License::exponent[3]{
        0x01 ^ 0xca,
        0x00 ^ 0xfe,
        0x01 ^ 0xba
};

const unsigned char papupata::licensing::License::modulus[65]{
        0x00 ^ 0xca,
        0xcc ^ 0xfe,
        0x95 ^ 0xba,
        0x57 ^ 0xbe,
        0x98 ^ 0xca,
        0xbe ^ 0xfe,
        0xf1 ^ 0xba,
        0xa2 ^ 0xbe,
        0x5d ^ 0xca,
        0x0d ^ 0xfe,
        0x14 ^ 0xba,
        0x7f ^ 0xbe,
        0x8b ^ 0xca,
        0xd2 ^ 0xfe,
        0x48 ^ 0xba,
        0x8b ^ 0xbe,
        0xe6 ^ 0xca,
        0x0d ^ 0xfe,
        0xe8 ^ 0xba,
        0x98 ^ 0xbe,
        0x4f ^ 0xca,
        0xfe ^ 0xfe,
        0x32 ^ 0xba,
        0xde ^ 0xbe,
        0x86 ^ 0xca,
        0xff ^ 0xfe,
        0x5d ^ 0xba,
        0x3e ^ 0xbe,
        0x15 ^ 0xca,
        0xda ^ 0xfe,
        0x55 ^ 0xba,
        0x94 ^ 0xbe,
        0x39 ^ 0xca,
        0x71 ^ 0xfe,
        0xbb ^ 0xba,
        0x77 ^ 0xbe,
        0xca ^ 0xca,
        0x23 ^ 0xfe,
        0x5d ^ 0xba,
        0xc8 ^ 0xbe,
        0xa4 ^ 0xca,
        0x82 ^ 0xfe,
        0xee ^ 0xba,
        0x8c ^ 0xbe,
        0xdd ^ 0xca,
        0xc7 ^ 0xfe,
        0xa3 ^ 0xba,
        0x51 ^ 0xbe,
        0x3f ^ 0xca,
        0x0a ^ 0xfe,
        0x2b ^ 0xba,
        0xe3 ^ 0xbe,
        0x21 ^ 0xca,
        0x12 ^ 0xfe,
        0x2f ^ 0xba,
        0xfc ^ 0xbe,
        0x6a ^ 0xca,
        0x3e ^ 0xfe,
        0x50 ^ 0xba,
        0x07 ^ 0xbe,
        0xda ^ 0xca,
        0x59 ^ 0xfe,
        0x10 ^ 0xba,
        0xbb ^ 0xbe,
        0x73 ^ 0xca,
};


juce::OwnedArray<papupata::licensing::Challenge> papupata::licensing::Challenge::generateChallenges()
{
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
    return challenges;
}

JUCE_IMPLEMENT_SINGLETON(LicenceTools)

LicenceTools::LicenceTools()
{
    licenceFile.reset(papupata::licensing::LicenseFile::getInstance());
}

LicenceTools::~LicenceTools()
{
    clearSingletonInstance();
}

bool LicenceTools::isValidLicence() {
    return licenceFile->hasValidLicense();
   //return true;
}
