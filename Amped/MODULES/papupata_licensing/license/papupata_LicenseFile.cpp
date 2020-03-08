namespace papupata {
    namespace licensing {
        JUCE_IMPLEMENT_SINGLETON(LicenseFile)

        static juce::File getPropertiesFilePath(const juce::PropertiesFile::Options &opt)
        {
#ifndef JUCE_MAC
            auto dir = juce::File::getSpecialLocation (juce::File::userApplicationDataDirectory);
#else
#if JUCE_STANDALONE_APPLICATION
            auto dir = juce::File::getSpecialLocation (juce::File::userApplicationDataDirectory);
#else
            char buffer[8192];
            struct passwd pwd, *result = NULL;
            getpwuid_r(geteuid(), &pwd, buffer, 8192, &result);

            auto dir = juce::File(juce::String(pwd.pw_dir));
            dir = dir.getChildFile("Library");
            dir = dir.getChildFile(opt.osxLibrarySubFolder);
#endif
#endif

            dir = dir.getChildFile (opt.folderName.isNotEmpty() ? opt.folderName
                                    : opt.applicationName);

            dir = (opt.filenameSuffix.startsWithChar (L'.')
                   ? dir.getChildFile (opt.applicationName).withFileExtension (opt.filenameSuffix)
                   : dir.getChildFile (opt.applicationName + "." + opt.filenameSuffix));

            DBG(juce::String("LicenseTools user settings file at ") + dir.getFullPathName());

            return dir;
        }

        LicenseFile::LicenseFile(void)
        {
            juce::PropertiesFile::Options opt;

            opt.applicationName = JucePlugin_Name;
            opt.commonToAllUsers = false;
            opt.doNotSave = false;
            opt.filenameSuffix = ".settings";
            opt.folderName = JucePlugin_Manufacturer;
            opt.ignoreCaseOfKeyNames = true;
            opt.millisecondsBeforeSaving = 500;
            opt.osxLibrarySubFolder = "Application Support";
            opt.storageFormat = juce::PropertiesFile::StorageFormat::storeAsCompressedBinary;

            propertiesFile.reset(new juce::PropertiesFile(getPropertiesFilePath(opt), opt));

            readLicenses();
        }

        int LicenseFile::readLicenses(void)
        {
            int read = 0;
            propertiesFile->reload();
            auto&& props = propertiesFile->getAllProperties();
            auto&& keys = props.getAllKeys();

            licenses.clear();

            for (auto&& s : keys)
            {
                if (s.indexOf("license") == 0)
                {
                    auto&& trimmedl = props[s].trim();
                    DBG("License read from slot " + s + ": " + trimmedl);
                    juce::OwnedArray<Challenge> challenges(Challenge::generateChallenges());
                    std::unique_ptr<License> l(new License(trimmedl, challenges));
                    if (l->isValid())
                    {
                        DBG("\tLicense validation OK");
                        licenses.add(std::move(l));
                        read++;
                    }
                }
            }

            return read;
        }

        bool LicenseFile::storeLicenses()
        {
            int written = 0;
            propertiesFile->reload();
            propertiesFile->clear();

            for (auto&& l : licenses)
            {
                if (l->isValid())
                {
                    propertiesFile->setValue(juce::String::formatted("license%d", written), l->toString());
                    written++;
                }
            }

            return propertiesFile->save();
        }
    }
}
