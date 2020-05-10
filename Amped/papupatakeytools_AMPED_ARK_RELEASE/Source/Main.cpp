/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a JUCE application.

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"

juce::String JucePlugin_Name("Amped - Roots");
juce::String JucePlugin_Manufacturer("ML Sound Lab");

extern juce::RSAKey authPrivateKey;

juce::OwnedArray<papupata::licensing::Challenge> papupata::licensing::Challenge::generateChallenges()
{
    juce::OwnedArray<papupata::licensing::Challenge> challenges;
    challenges.add(new papupata::licensing::Challenge(true));
    return challenges;
}

void usage(const char *prg, int retVal)
{
    std::cerr << "Usage: " << std::endl;
    std::cerr << "\t" << prg << " -c|--generate-challenge" << std::endl;
    std::cerr << "\t" << prg << " -g|--generate <challenge> <orderID> <userEmail> <timeValid> <licenseString>" << std::endl;
    std::cerr << "\t" << prg << " <challenge> <licenseString>" << std::endl;
    std::cerr << std::endl;
    std::cerr << "Where" << std::endl;
    std::cerr << "\t<challenge>\t\tChallenge / request key" << std::endl;
    std::cerr << "\t<orderID>\t\tShopify Order ID" << std::endl;
    std::cerr << "\t<userEmail>\t\tOrder user email address" << std::endl;
    std::cerr << "\t<timeValid>\t\t0 for permanent license or number of days from curren time until expiry" << std::endl;
    std::cerr << "\t<licenseString>\t\tLicense string" << std::endl;
    std::cerr << std::endl;
    std::cerr << "Examples:" << std::endl;
    std::cerr << "\t" << prg << " -c" << std::endl;
    std::cerr << "\t" << prg << " -g 3LYW-QTHI-L93T-YTQX-IW6N-CYQK-GCBA-MR89 \"#2252.1\" foo@bar.baz 0 yahooThisIsMySecretString" << std::endl;
    std::cerr << "\t" << prg << " 3LYW-QTHI-L93T-YTQX-IW6N-CYQK-GCBA-MR89 3EX3281TDQU6FFZ4YT1XVFC6O74Q88LI501G5369QIUSL1JV8B9KPRXXTAR78642MZ5XJJ5JV5VTFSCAPA0BDMH43LKM8473RPX" << std::endl;
    exit(retVal);
}

//==============================================================================
int main (int argc, char* argv[])
{
    bool generate = false;
    juce::ArgumentList my_args(argc, argv);
    
    if (my_args.containsOption("--generate|-g"))
    {
        generate = true;
    }
    
    if (my_args.containsOption("--generate-challenge|-c"))
    {
        std::cout << papupata::licensing::Challenge(true).toString() << std::endl;
    }
    else if (generate) {
        DBG("VALIDATE ARGS");
        if (my_args.size() != 6)
            usage(argv[0], -1);

        DBG("VALIDATE CHALLENGE");
        papupata::licensing::Challenge challenge(my_args[1].text);
        if (!challenge.isValid())
            usage(argv[0], -2);
        
        DBG("INPUT:");
        DBG(my_args[1].text);
        DBG(my_args[2].text);
        DBG(my_args[3].text);
        DBG(my_args[4].text);
        DBG(my_args[5].text);

        juce::String license(papupata::licensing::LicenseGenerator::createLicense(authPrivateKey, my_args[1].text, my_args[2].text, my_args[3].text, my_args[4].text.getIntValue(), my_args[5].text));
        
        DBG("NON-VALIDATED LICENSE:");
        DBG(license);
        if (!papupata::licensing::License(license, my_args[1].text).isValid())
            usage(argv[0], -3);

        DBG("VALIDATED LICENSE:");
        std::cout << license;
    }
    else
    {
        DBG("VALIDATE ARGS");
        if (my_args.size() != 2)
            usage(argv[0], -10);

        papupata::licensing::License license(my_args[1].text, my_args[0].text);
        DBG("CHECK LICENSE");
        if (!license.isValid())
            usage(argv[0], -11);

        DBG("LICENSE DATA:");
        std::cout << license.getUserName() << std::endl;
        std::cout << license.getUserEmail() << std::endl;
        std::cout << license.getValidTS() << std::endl;
        std::cout << license.getProtectionKey(-1) << std::endl;
    }

    return 0;
}
