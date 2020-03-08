#ifdef PAPUPATA_LICENSING_H_INCLUDED
/* When you add this cpp file to your project, you mustn't include it in a file where you've
   already included any other headers - just put it inside a file on its own, possibly with your config
   flags preceding it, but don't include anything else. That also includes avoiding any automatic prefix
   header files that the compiler may be using.
*/
#error "Incorrect use of PAPUPATA cpp file"
#endif

#include "papupata_licensing.h"

#include "utils/papupata_BaseTools.cpp"
#include "utils/papupata_HWIDTools.cpp"
#include "utils/papupata_Challenge.cpp"
#include "license/papupata_License.cpp"
#include "license/papupata_LicenseFile.cpp"

#if PAPUPATA_ENABLE_GENERATOR
#include "generator/papupata_LicenseGenerator.cpp"
#endif
