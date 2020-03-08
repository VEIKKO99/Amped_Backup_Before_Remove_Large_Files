namespace papupata {
    namespace licensing {
        class Challenge
        {
        public:
            /** Instantiate Challenge from a String. */
            Challenge(const juce::String &c) : challengeString(c)
            {
            }
            /** Instantiate Challenge by generating a new one.
             @param generate64Bit
             */
            Challenge(bool generate64Bit, bool tryPreviousWin = false, bool skipWinSystemDir = true)
            {
                /* Build challenge string. <UUID>,<deviceIDs>,<APPID>,<salt> */
                juce::StringArray challengeData = HWIDTools::getInstance()->getUniqueInstallationID();
#ifndef JUCE_MAC
                challengeData.addArray(HWIDTools::getInstance()->getDeviceIDs(generate64Bit, tryPreviousWin, skipWinSystemDir));
#endif
                challengeData.add(getAppId());

                challengeData.add(challengeSalt);
                juce::String challengeJoined = challengeData.joinIntoString(",");
                buildFromJoinedString(challengeJoined, challengeData.size());
            }

            /** Return true if the challenge is valid. */
            bool isValid() const;

            /** Get the challenge String */
            const juce::String& toString() const { DBG(challengeString); return challengeString; }

            /** Generate challenges. This needs to be implemented in the application. */
            static juce::OwnedArray<papupata::licensing::Challenge> generateChallenges();
        protected:
            /** Build challengeString from joined HW-unique data. */
            void buildFromJoinedString(const juce::String& challengeJoined, int challengeItems);

            static const juce::String challengeSalt;

        private:
            /** Dashify the input String to 4 character blocks. */
            static juce::String dashify(const juce::String &in);

            /** Compress memoryblock to half of the size. XORs first half with second half. */
            static juce::MemoryBlock compressToHalf(const juce::MemoryBlock &in);

            /** Get Application ID. */
            static juce::String getAppId() { return JucePlugin_Name; }

            /** The dashified challenge String. */
            juce::String challengeString;
        };
    }
}
