/*
  ==============================================================================

    Consts.h
    Created: 8 Nov 2019 9:06:50pm
    Author:  Veikko Tapaninen

  ==============================================================================
*/

#pragma once

enum GainProcessorId { InputGain = 0, OutputGain, DriveGain, SIZE};

const int AMPED_MONO_CHANNEL = 1;

inline const char* getBinaryDataWithOriginalFileName(String originalFileName, int& dataSizeInBytes) {
    // THis doesn't work with names starting with number
    //    String replaced = originalFileName.replaceCharacter('.', '_');
    //  return BinaryData::getNamedResource(replaced.toRawUTF8(), dataSizeInBytes);
    originalFileName = originalFileName.trimCharactersAtStart("memory:");
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