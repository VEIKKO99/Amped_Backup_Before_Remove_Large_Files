namespace papupata {
    namespace licensing {
        /** Utilities to convert BigInteger to ASCII-representable Strings and back. */
        class BaseTools
        {
        public:
            static juce::String toBase58(const juce::BigInteger &b);

            /** Convert from proprietary Base36 to BigInteger */
            static juce::BigInteger fromBase36(const juce::String &input);

            /** Convert from BigInteger to proprietary Base36 String. */
            static juce::String toBase36(const juce::BigInteger &b);
            JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BaseTools)
        };
    }
}
