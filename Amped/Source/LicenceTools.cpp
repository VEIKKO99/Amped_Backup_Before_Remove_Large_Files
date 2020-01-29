

/*
  ==============================================================================

    LicenceTools.cpp
    Created: 19 Jan 2020 4:18:53pm
    Author:  Veikko Tapaninen

  ==============================================================================
*/

#include "LicenceTools.h"


// Slightly mangled public key exponent and modulus.
// These should not belong to this file but should be in external storage.
const unsigned char papupata::licensing::License::exponent[3]{
        0x01 ^ 0xca,
        0x00 ^ 0xfe,
        0x01 ^ 0xba

};
const unsigned char papupata::licensing::License::modulus[65]{
        0x00 ^ 0xca,
        0xc7 ^ 0xfe,
        0x2a ^ 0xba,
        0xf2 ^ 0xbe,
        0x5a ^ 0xca,
        0x20 ^ 0xfe,
        0xd7 ^ 0xba,
        0xe9 ^ 0xbe,
        0x9b ^ 0xca,
        0x6c ^ 0xfe,
        0x4b ^ 0xba,
        0x73 ^ 0xbe,
        0xf5 ^ 0xca,
        0x74 ^ 0xfe,
        0x2f ^ 0xba,
        0xa7 ^ 0xbe,
        0x86 ^ 0xca,
        0x05 ^ 0xfe,
        0xd7 ^ 0xba,
        0x5f ^ 0xbe,
        0x36 ^ 0xca,
        0xf5 ^ 0xfe,
        0xa2 ^ 0xba,
        0x62 ^ 0xbe,
        0xce ^ 0xca,
        0xe1 ^ 0xfe,
        0xc1 ^ 0xba,
        0x19 ^ 0xbe,
        0xa6 ^ 0xca,
        0x64 ^ 0xfe,
        0xfd ^ 0xba,
        0x52 ^ 0xbe,
        0x7a ^ 0xca,
        0xc6 ^ 0xfe,
        0x86 ^ 0xba,
        0x2a ^ 0xbe,
        0x3e ^ 0xca,
        0xa3 ^ 0xfe,
        0x83 ^ 0xba,
        0xdf ^ 0xbe,
        0xd9 ^ 0xca,
        0x1a ^ 0xfe,
        0x03 ^ 0xba,
        0x57 ^ 0xbe,
        0xc9 ^ 0xca,
        0x6b ^ 0xfe,
        0xb7 ^ 0xba,
        0x4e ^ 0xbe,
        0x95 ^ 0xca,
        0xbe ^ 0xfe,
        0x60 ^ 0xba,
        0xb5 ^ 0xbe,
        0xaa ^ 0xca,
        0x5e ^ 0xfe,
        0x16 ^ 0xba,
        0x20 ^ 0xbe,
        0xae ^ 0xca,
        0xee ^ 0xfe,
        0x36 ^ 0xba,
        0x1d ^ 0xbe,
        0xc2 ^ 0xca,
        0x95 ^ 0xfe,
        0x9c ^ 0xba,
        0x04 ^ 0xbe,
        0x27 ^ 0xca
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
}
