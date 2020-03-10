#ifdef JUCE_MAC
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pwd.h>
#endif

namespace papupata {
    namespace licensing {
        juce::CriticalSection HWIDTools::validateLock;
        std::unique_ptr<HWIDTools> HWIDTools::pImpl;

#ifdef JUCE_WINDOWS
        class HWIDToolsWindows : public HWIDTools
        {
        public:
            HWIDToolsWindows() {}
            virtual ~HWIDToolsWindows() {}

            virtual juce::StringArray getDeviceIDs(bool generate64Bit, bool tryPreviousWin, bool skipWinSystemDir) const
            {
				DBG("getDeviceIDs " + juce::String((int)generate64Bit) + " " + juce::String((int)tryPreviousWin) + " " + juce::String((int)skipWinSystemDir));
                juce::StringArray ids;

				juce::String machineGuid64 = juce::WindowsRegistry::getValue("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Cryptography\\MachineGuid",
					"", juce::WindowsRegistry::WoW64Mode::WoW64_64bit);
				juce::String machineGuid = generate64Bit ? machineGuid64 :
					juce::WindowsRegistry::getValue("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Cryptography\\MachineGuid", machineGuid64,
						juce::WindowsRegistry::WoW64Mode::WoW64_32bit);
				jassert(machineGuid.length() > 0);
				ids.add(machineGuid);

				if (!(skipWinSystemDir && machineGuid.length() > 0))
				{
#ifdef JUCE_32BIT
					juce::File f(generate64Bit ? juce::File::getSpecialLocation(juce::File::windowsSystemDirectory).getParentDirectory().getChildFile("sysnative") : juce::File::getSpecialLocation(juce::File::windowsSystemDirectory));
#else
					juce::File f(generate64Bit ? juce::File::getSpecialLocation(juce::File::windowsSystemDirectory) : juce::File::getSpecialLocation(juce::File::windowsSystemDirectory).getParentDirectory().getChildFile("SysWoW64"));
#endif

					if (tryPreviousWin)
					{
						// Ugly hack for WIN 1903 shit. windows\system32 and other related changed file ids.
						// Old dirs were moved to \windows.old\windows\system32 and new ones created with new IDs..
						juce::String regPath(juce::String("HKEY_CURRENT_USER\\Software\\") + juce::String(JucePlugin_Manufacturer) + juce::String("\\") + juce::String(JucePlugin_Name) + juce::String("\\ID"));
						regPath.append(generate64Bit ? "1" : "0", 1);
#ifdef JUCE_32BIT
						regPath.append("0", 1);
#else
						regPath.append("1", 1);
#endif
						if (juce::WindowsRegistry::getValue(regPath).length() <= 0)
						{
							juce::File f2 = juce::File(f.getFullPathName().replaceFirstOccurrenceOf("Windows", "windows.old\\Windows", true));
							if (f2.exists())
							{
								juce::String id = juce::String::toHexString((juce::int64)f2.getFileIdentifier());
								DBG("Storing old id of " + f2.getFullPathName() + "(" + id + ") to " + regPath + ": " + regPath);
								juce::WindowsRegistry::setValue(regPath, id);
							}
						}
						if (juce::WindowsRegistry::getValue(regPath).length() > 0)
						{
							ids.add(juce::WindowsRegistry::getValue(regPath));
						}
						else
						{
							if (auto num = f.getFileIdentifier())
							{
								ids.add(juce::String::toHexString((juce::int64)num));
							}
						}
					}
					else {
						if (auto num = f.getFileIdentifier())
						{
							ids.add(juce::String::toHexString((juce::int64)num));
						}
					}
				}

                jassert(ids.size() > 0); // Failed to create any IDs!

                return ids;
            }

            virtual juce::String getUniqueInstallationID(void) const
            {
                if (!juce::WindowsRegistry::valueExists(getUUIDPath()))
                {
                    juce::WindowsRegistry::setValue(getUUIDPath(), juce::Uuid().toDashedString());
                }
				DBG(getUUIDPath());
                juce::String val = juce::WindowsRegistry::getValue(getUUIDPath());
                juce::Logger::outputDebugString(val);

                return val;
            }

            static juce::String getRegistryPath() { return juce::String("HKEY_CURRENT_USER\\SOFTWARE\\") + juce::String(JucePlugin_Manufacturer) + juce::String("\\") + juce::String(JucePlugin_Name); }
            static juce::String getUUIDPath() { return getRegistryPath() + "\\UUID"; }
        };

        HWIDTools *HWIDTools::getInstance() {
            const juce::ScopedLock myLock(validateLock);
            if (nullptr == pImpl) {
                pImpl.reset(new HWIDToolsWindows());
            }
            return pImpl.get();
        }
#elif defined JUCE_MAC
        class HWIDToolsMac : public HWIDTools
        {
        public:
            HWIDToolsMac() {}
            virtual ~HWIDToolsMac() {}

            virtual juce::StringArray getDeviceIDs(bool /*generate64Bit*/, bool /*tryPreviousWin*/, bool /*skipWinSystemDir*/) const
            {
                juce::StringArray ids;
                juce::File f("~");

                if (auto num = f.getFileIdentifier())
                {
                    juce::String id = juce::String::toHexString((juce::int64)num);
                    ids.add(id);
                }

                jassert(ids.size() > 0); // Failed to create any IDs!

                return ids;
            }

            virtual juce::String getUniqueInstallationID(void) const
            {
                uuid_t uuid;
                struct timespec waitTime;
                waitTime.tv_sec = waitTime.tv_nsec = 0;
                int loopFor = 10;

                while(loopFor-- > 0 && gethostuuid(uuid, &waitTime) != 0);

                juce::String val;
                for(int i = 0; i < 16; i++)
                {
                    val.append(juce::String::formatted("%02hhX", ((const unsigned char *)uuid)[i]), 2);
                }

                return val;
            }
        };

        HWIDTools *HWIDTools::getInstance() {
            const juce::ScopedLock myLock(validateLock);
            if (nullptr == pImpl) {
                pImpl.reset(new HWIDToolsMac());
            }
            return pImpl.get();
        }
#elif defined JUCE_LINUX
        class HWIDToolsLinux : public HWIDTools
        {
        public:
            HWIDToolsLinux() {}
            virtual ~HWIDToolsLinux() {}

            virtual juce::StringArray getDeviceIDs(bool /*generate64Bit*/, bool /*tryPreviousWin*/, bool /*skipWinSystemDir*/) const
            {
                juce::StringArray ids;
		jassert(false);

                return ids;
            }

            virtual juce::String getUniqueInstallationID(void) const
            {
                juce::String val;

		jassert(false);

                return val;
            }
        };

        HWIDTools *HWIDTools::getInstance() {
            const juce::ScopedLock myLock(validateLock);
            if (nullptr == pImpl) {
                pImpl.reset(new HWIDToolsLinux());
            }
            return pImpl.get();
        }
#endif
    }
}
