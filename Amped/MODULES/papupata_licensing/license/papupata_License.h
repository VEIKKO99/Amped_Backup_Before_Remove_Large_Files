namespace papupata {
    namespace licensing {
        /** A License.
         * Serializable to a Base36 dashified String.
         * Has storage for 2 mandatory free-form fields (userName, email), valid until timestamp and one
         * String for application-specific data (protectionKey).
         */
        class License {
        public:
            License(const juce::String &license, const juce::OwnedArray<Challenge>& challenges)
            : licenseString(license)
            {
                for (auto&& ch : challenges)
                {
                    revalidate(*ch);
                    if (valid)
                        break;
                }
            }

            /** Is the license valid?
             * If not, the license field getters may return random data.
             */
            bool isValid(void) const
            {
                return valid;
            }

            /** Get userName, first String field in license. */
            const juce::String& getUserName() const
            {
                return userName;
            }

            /** Get userEmail, second String field in license. */
            const juce::String& getUserEmail() const
            {
                return userEmail;
            }

            /** Get ISO8601 formatted valid Until date. */
            juce::String getValidUntil() const
            {
                return validUntil.toISO8601(true);
            }

            /** Get license valid until date in milliseconds since epoch. */
            juce::int64 getValidTS() const
            {
                return validUntil.toMilliseconds();
            }

            /**
             Get protection key.

             @return Protection key from license to be used for deciphering stuff.
             */
            const juce::String getProtectionKey(int targetId) const {
                jassert(protectionKeys.contains(targetId));
                return protectionKeys[targetId];
            }

            /**
             Get the target content IDs which this key protects.
             */
            const juce::Array<int>& getForIds() const {
                return forIDs;
            }

            const juce::String& toString() const {
                return licenseString;
            }

        protected:
            License() {}

            /** Revalidate licenseString and parse it to subfields.
             * @param challenge Challenge to validate against.
             */
            void revalidate(const Challenge& challenge);

        private:
            /** Place holder for 512-bit RSA public key. It is very weak (factorization is rather easy).
             * However, increasing the key size will increase the length of the license string.
             * This needs to be instantiated in appication code with the application-specific
             * public key. */
            static const unsigned char exponent[3];
            static const unsigned char modulus[65];

            juce::String licenseString{""};
            bool valid{false};
            juce::String userName;
            juce::String userEmail;
            juce::Time validUntil;
            juce::Array<int> forIDs;
            juce::HashMap<int, juce::String> protectionKeys;

            JUCE_LEAK_DETECTOR(License)
        };
    }
}
