namespace papupata {
    namespace licensing {
        class LicenseFile {
        public:
            virtual ~LicenseFile() {
                clearSingletonInstance();
            }

            /** Any valid licenses available? */
            bool hasValidLicense() {
                return licenses.size() > 0;
            }

            /** Get view to license array. */
            const juce::OwnedArray<License, juce::CriticalSection>& getLicenses() const
            {
                return licenses;
            }

            /** Add license to storage and take ownership.
             * @return true if successfully stored.
             */
            bool addLicense(std::unique_ptr<License> license)
            {
                if (license->isValid())
                {
                    licenses.add(std::move(license));
                    return storeLicenses();
                }

                return false;
            }

            const License* getLicense(int forId = -1)
            {
                for (auto l : licenses)
                {
                    if (l->getForIds().contains(forId) && l->isValid())
                        return l;
                }

                return nullptr;
            }

            /** Find protection key from the license file.
             * @param forId optional target ID to search for.
             * @return protection key or "" if not found.
             */
            juce::String getProtectionKey(int forId = -1)
            {
                for (auto l : licenses)
                {
                    if (l->getForIds().contains(forId) && l->isValid())
                        return l->getProtectionKey(forId);
                }

                return juce::String();
            }

            // LicenseFile is a thread-safe singleton
            JUCE_DECLARE_SINGLETON(LicenseFile, false)

        protected:
            LicenseFile();

            /** Read licenses from persistent storage to memory.
             * @return the number of licenses read.
             */
            int readLicenses();

            /** Store licenses to persistent storage from memory.
             * @return true if successfully saved.
             */
            bool storeLicenses();


        private:
            std::unique_ptr<juce::PropertiesFile> propertiesFile;
            juce::OwnedArray<License, juce::CriticalSection> licenses;

            JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LicenseFile)
        };
    }
}
