namespace papupata {
    namespace licensing {
        void License::revalidate(const Challenge& challenge)
        {
            if (licenseString.isEmpty())
            {
                DBG("License string is empty");
                valid = false;
            }
            else
            {
                juce::BigInteger l = papupata::licensing::BaseTools::fromBase36(licenseString);
                // Demangle and de-serialize binary public key to String for juce::RSAKey
                juce::String tmp;
                for(unsigned int i = 0; i < sizeof(exponent); i++)
                {
                    unsigned char tmpc = exponent[i];
                    if (i % 4 == 0)
                        tmpc ^= 0xca;
                    else if (i % 4 == 1)
                        tmpc ^= 0xfe;
                    else if (i % 4 == 2)
                        tmpc ^= 0xba;
                    else
                        tmpc ^= 0xbe;
                    tmp.append(juce::String::formatted("%02hhx", tmpc), 2);
                }
                tmp.append(",", 1);
                for(unsigned int i = 0; i < sizeof(modulus); i++)
                {
                    unsigned char tmpc = modulus[i];
                    if (i % 4 == 0)
                        tmpc ^= 0xca;
                    else if (i % 4 == 1)
                        tmpc ^= 0xfe;
                    else if (i % 4 == 2)
                        tmpc ^= 0xba;
                    else
                        tmpc ^= 0xbe;
                    tmp.append(juce::String::formatted("%02hhx", tmpc), 2);
                }

                juce::RSAKey authPublicKey(tmp);
                jassert(authPublicKey.isValid());
                authPublicKey.applyToValue(l);
                authPublicKey = juce::RSAKey("03,07");

                juce::MemoryBlock b = l.toMemoryBlock();

                while (b.getSize() % 8 != 0) {
                    DBG("b.getSize() % 8 != 0: " + juce::String(b.getSize()));
                    b.append("\0", 1);
                }

                l.setRange(0, l.getHighestBit(), false);

                // Get MD5 hash of the challenge and decipher the license key
                juce::MD5 chmd5(challenge.toString().toUTF8());
                juce::BlowFish bf(chmd5.getChecksumDataArray(), 16);
                bf.decrypt(b);

                /* Decrypted block must have length and consist of printable-only, whitespace or NULL.
                   Binary not allowed. */
                if (b.getSize() == 0) {
                    valid = false;
                    DBG("Decrypt failed " + juce::String(b.getSize()));
                    return;
                }
                for (size_t i = 0; i < b.getSize(); i++)
                {
                    if (!juce::CharacterFunctions::isPrintable(b[i]) && !juce::CharacterFunctions::isWhitespace(b[i]) && b[i] != '\0') {
                        valid = false;
                        return;
                    }
                }

                juce::String cleartextLicense = b.toString();
                b.fillWith(0x00);

                // Cleartext license format:
                // Line 1: 'username<\n>' Can be just "\n".
                // Line 2: 'userEmail<\n>' Can be just "\n". Does not have to be email address, any ASCII string is ok.
                // Line 3: license validity, 0 if permanent, otherwise valid until in seconds since epoch - 0x5B000000
                // Line 4-: free-form application-specific ASCII data. May contain NULLs, whitespace or any printable.
                userName = cleartextLicense.upToFirstOccurrenceOf("\n", false, false);
                cleartextLicense = cleartextLicense.substring(userName.length() + 1);
                if (userName.length() == 0) {
                    valid = false;
                    DBG("Username validation failed");
                    return;
                }

                userEmail = cleartextLicense.upToFirstOccurrenceOf("\n", false, false);
                cleartextLicense = cleartextLicense.substring(userEmail.length() + 1);
                if (userEmail.length() == 0) {
                    valid = false;
                    DBG("Useremail validation failed");
                    return;
                }

                juce::String tmpTime = cleartextLicense.upToFirstOccurrenceOf("\n", false, false);
                cleartextLicense = cleartextLicense.substring(tmpTime.length() + 1);
                if (tmpTime.length() < 1) {
                    valid = false;
                    return;
                }
                for (int i = 0; i < tmpTime.length(); i++) {
                    if (!juce::CharacterFunctions::isDigit(tmpTime[i])) {
                        valid = false;
                        return;
                    }
                }
                if (tmpTime.getLargeIntValue() == 0)
                {
                    DBG("Permanent license");
                    validUntil = juce::Time(0ULL);
                } else {
                    validUntil = juce::Time((0x5B000000ULL + tmpTime.getLargeIntValue()) * 1000ULL);
                    DBG("Valid until " + validUntil.toString(true, true));
                }

                valid = validUntil.toMilliseconds() == 0ULL || juce::Time::getCurrentTime() <= validUntil;
                if (valid)
                {
                    while(cleartextLicense.length() > 0)
                    {
                        auto&& token = cleartextLicense.upToFirstOccurrenceOf(",", false, false);
                        cleartextLicense = cleartextLicense.substring(token.length() + 1);

                        int forId = -1;
                        int separatorPos = token.indexOfChar(':');
                        if (separatorPos != -1)
                        {
                            forId = token.getIntValue();
                            DBG("License targeted for: " + juce::String(forId));
                            token = token.substring(separatorPos + 1);
                        }
                        else
                        {
                            DBG("Wildcard license");
                        }
                        forIDs.add(forId);
                        protectionKeys.set(forId, token);
                    }
                }
                else
                {
                    DBG("Time validation failed");
                    protectionKeys.clear();
                    userName.clear();
                    userEmail.clear();
                }
            }
        }
    }
}
