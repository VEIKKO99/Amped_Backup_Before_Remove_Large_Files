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

// Reverb Demo:
const std::string VTS_EF_REVB_ON = "VTS_EF_REVB_ON";
const std::string VTS_EF_REVB_ROOM = "VTS_EF_REVB_ROOM";
const std::string VTS_EF_REVB_DAMPING = "VTS_EF_REVB_DAMPING";
const std::string VTS_EF_REVB_WLEV = "VTS_EF_REVB_WLEV";
const std::string VTS_EF_REVB_DLEV = "VTS_EF_REVB_DLEV";
const std::string VTS_EF_REVB_WIDTH = "VTS_EF_REVB_WIDTH";
const std::string VTS_EF_REVB_FREEZE = "VTS_EF_REVB_FREEZE";

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
            return BinaryData::getNamedResource(BinaryData::namedResourceList[i], dataSizeInBytes);
        }
    }
    return nullptr;
};