/** BEGIN_JUCE_MODULE_DECLARATION

    ID:             papupata_licensing
    vendor:         papupata
    version:        0.0.1
    name:           Papupata licensing libraries
    description:    Licensing framework
    website:        
    license:        Proprietary

    dependencies:   juce_core, juce_cryptography, juce_data_structures

    END_JUCE_MODULE_DECLARATION
*/

#pragma once
#define PAPUPATA_LICENSING_H_INCLUDED

#include <juce_core/juce_core.h>
#include <juce_cryptography/juce_cryptography.h>
#include <juce_data_structures/juce_data_structures.h>

//==============================================================================
/** Config: PAPUPATA_ENABLE_GENERATOR
 If this option is turned on, the generator framework is included in the build.
 Typically this should not be included on client implementations
 */
#ifndef PAPUPATA_ENABLE_GENERATOR
#define PAPUPATA_ENABLE_GENERATOR 0
#endif

#ifndef JucePlugin_Name
// If compiling command-line application / non-plugin, these need to be provided by host app
extern juce::String JucePlugin_Name;
extern juce::String JucePlugin_Manufacturer;
#endif

#include "utils/papupata_BaseTools.h"
#include "utils/papupata_HWIDTools.h"
#include "utils/papupata_Challenge.h"
#include "license/papupata_License.h"
#include "license/papupata_LicenseFile.h"

#if PAPUPATA_ENABLE_GENERATOR
#include "generator/papupata_LicenseGenerator.h"
#endif
