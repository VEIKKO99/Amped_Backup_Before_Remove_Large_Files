namespace papupata {
    namespace licensing {
        class HWIDTools
        {
        public:
            virtual ~HWIDTools() {}
            static HWIDTools *getInstance();
            static void destroy() { const juce::ScopedLock myLock(validateLock); pImpl.reset(); }

            /** Get array of unique device IDs to identify the HW. */
            virtual juce::StringArray getDeviceIDs(bool generate64Bit, bool tryPreviousWin, bool skipWinSystemDir) const = 0;

            /** Get device unique installation ID. */
            virtual juce::String getUniqueInstallationID(void) const = 0;

        protected:
            HWIDTools() {}

        private:
            //! Lock for create/get/destroy of pImpl
            static juce::CriticalSection validateLock;
            static std::unique_ptr<HWIDTools> pImpl;

            JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(HWIDTools)
        };
    }
}
