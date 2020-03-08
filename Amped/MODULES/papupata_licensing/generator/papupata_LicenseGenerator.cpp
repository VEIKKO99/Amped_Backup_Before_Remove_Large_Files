constexpr double licenseExpirationTime = 60. * 60. * 24.;

juce::String papupata::licensing::LicenseGenerator::createLicense(const juce::RSAKey& authPrivateKey,
                                                const juce::String &challenge,
                                                const juce::String &orderNumber,
                                                const juce::String &orderEmail,
                                                int validDays,
                                                const juce::String &licenseData)
{
    // @TODO pull-out the consts to common header for generator/parser
    juce::String nc =
        orderNumber + "\n" +
        orderEmail + "\n" +
        (validDays > 0 ?
         (juce::String((juce::Time::getCurrentTime() + juce::RelativeTime(licenseExpirationTime * validDays)).toMilliseconds() / 1000ULL - 0x5B000000ULL)) :
         "0") + "\n" + licenseData;

    const char *chstr = nc.toRawUTF8();
    juce::MemoryBlock b(chstr, strlen(chstr) + 1);

    juce::MD5 chmd5(challenge.toUTF8());
    juce::BlowFish bf(chmd5.getChecksumDataArray(), 16);
        bf.encrypt(b);

    juce::BigInteger i;
    i.loadFromMemoryBlock(b);

    authPrivateKey.applyToValue(i);

    return BaseTools::toBase36(i);
}
