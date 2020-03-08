namespace papupata {
namespace licensing {
class LicenseGenerator {
public:
    /**
     Generate a license string
     @param authPrivateKey RSA private key to use for encrypting.
     @param challenge Challenge to create license for
     @param orderNumber first string for license, typically order number. May not contain \n
     @param orderEmail second string for license, typically email in order. May not contain \n
     @param validDays how many days the license should be valid. 0 for permanent license
     @param licenseData Application-specific extra data to be protected by the license.
     */
    static juce::String createLicense(const juce::RSAKey &authPrivateKey,
                                      const juce::String &challenge,
                                      const juce::String &orderNumber,
                                      const juce::String &orderEmail,
                                      int validDays,
                                      const juce::String &licenseData);
};
}
}
