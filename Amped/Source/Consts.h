/*
  ==============================================================================

    Consts.h
    Created: 8 Nov 2019 9:06:50pm
    Author:  Veikko Tapaninen

  ==============================================================================
*/

#pragma once

enum GainProcessorId { InputGain = 0, OutputGain, DriveGain, SIZE};

const std::string AMPED_STORE_FULL_LICENCE_LINK = "https://ml-sound-lab.com/amped-roots";
const int AMPED_MONO_CHANNEL = 1;

const std::string VTS_INPUT = "input";
const std::string VTS_FX = "fx";
const std::string VTS_DRIVE = "drive";
const std::string VTS_BASS = "bass";
const std::string VTS_MIDDLE = "middle";
const std::string VTS_TREBBLE = "trebble";
const std::string VTS_PRESENCE = "presence";
const std::string VTS_MASTER = "master";
const std::string VTS_CAB_SIM_TYPE = "cabSim_type";
const std::string VTS_OUTPUT = "output";
const std::string VTS_LEFT_RIGHT_INPUT_SWITCH = "leftRightInputSwitch";


// Effects:
const std::string VTS_EF_OD_DRIVE = "effects_od_drive";
const std::string VTS_EF_OD_TONE = "effects_od_tone";
const std::string VTS_EF_OD_LEVEL = "effects_od_level";
const std::string VTS_EF_OD_ON = "effects_od_on";
const std::string VTS_EF_NG_ON = "effects_ng_on";
const std::string VTS_EF_NG_THRESHOLD = "effects_ng_threshold";

// Reverb:
const std::string VTS_EF_REVB_ON = "effects_reverb_on";
const std::string VTS_EF_REVB_SIZE = "effects_reverb_time";
const std::string VTS_EF_REVB_TONE = "effects_reverb_tone";
const std::string VTS_EF_REVB_MIX = "effects_reverb_mix";


inline const char* getBinaryDataWithOriginalFileName(String originalFileName, int& dataSizeInBytes) {
    // THis doesn't work with names starting with number
    //    String replaced = originalFileName.replaceCharacter('.', '_');
    //  return BinaryData::getNamedResource(replaced.toRawUTF8(), dataSizeInBytes);
    originalFileName = originalFileName.replaceFirstOccurrenceOf("memory:", "");
    const char* resourceNameUTF8 = originalFileName.toRawUTF8();
    for (unsigned int i = 0; i < BinaryData::namedResourceListSize; ++i)
    {
        if (strcmp(BinaryData::originalFilenames[i], resourceNameUTF8) == 0) {
            //return BinaryData::namedResourceList[i];
            Logger::getCurrentLogger()->writeToLog(resourceNameUTF8);
            return BinaryData::getNamedResource(BinaryData::namedResourceList[i], dataSizeInBytes);
        }
    }
    return nullptr;
};

/*
inline const char* getBinaryDataWithOriginalFileName(String originalFileName, int& dataSizeInBytes, double sampleR) {
    int sampleRate = (int)(sampleR + 0.5);
    
    String prefix = "192_"; // <== Default
    if (sampleRate < 48000) prefix = "44_";
    else if (sampleRate >= 48000 && sampleRate < 88200) prefix = "48_";
    else if (sampleRate >= 88200 && sampleRate < 96000) prefix = "88_";
    else if (sampleRate >= 96000 && sampleRate < 192000) prefix = "96_";
    else if (sampleRate > 96000) prefix = "192_";
    
    return getBinaryDataWithOriginalFileName(prefix + originalFileName, dataSizeInBytes);
};
*/
