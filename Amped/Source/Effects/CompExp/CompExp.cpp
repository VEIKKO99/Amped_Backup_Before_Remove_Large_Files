/**
 * CompExp.cpp
 * @copyright (C)2017 HoRNet Plugins
 *
 * This class implements a simple Compressor/Expander module
 */

#include "CompExp.h"
#include <math.h>

void CompExp::SetAttack(double attack)
{
  mCompEnv.setAttack(attack);
}

void CompExp::SetRelease(double release)
{
  mCompEnv.setRelease(release);
}

void CompExp::SetRatio(double ratio)
{
  mRatio = ratio;
}

void CompExp::SetMode(int mode)
{
  mMode = mode;
}

void CompExp::init(int sampleRate)
{
  mCompEnv.init(sampleRate);
}

void CompExp::SetBypass(bool toggle)
{
  mBypass = toggle;
}

void CompExp::Process(double *samples, int nFrames)
{
  for (int s = 0; s < nFrames; ++s)
  {
    double env = mCompEnv.process(*samples * 7.94328); // add 18dB gain to move threshod,to -18
    
    double inDB = AmpToDB(env);
    double outDB;
    if (inDB > -110.) {
      outDB = inDB / mRatio;
    } else {
      outDB = inDB;
    }
    
    double gainReduction = 1.;
    
    if(mMode == ECompMode::kComp) {
      gainReduction = DBToAmp(outDB) / DBToAmp(inDB);
    } else {
      gainReduction = DBToAmp(inDB) / DBToAmp(outDB);
    }
    
    if(mBypass || isinf(inDB)) {
      gainReduction = 1.;
    }
    
    *samples *= gainReduction;
    
    samples++;
  }
}
