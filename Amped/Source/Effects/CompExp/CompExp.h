/**
 * CompExp.h
 * @copyright (C)2017 HoRNet Plugins
 *
 * This class implements a simple Compressor/Expander module
 */

#ifndef CompExp_h
#define CompExp_h

#include "envelopeFollower.h"
//#include "autogain.h"

class CompExp
{
public:
  
  enum ECompMode
  {
    kComp = 0,
    kExp
  };
  
//  CompExp();
//  ~CompExp();
  
  void init(int sampleRate);
  
  void Process(double* samples, int nFrames);
  
  // in the original CompExp implmentation, this number goes from 1 to 10
  // where 1 is no compression / expansion appening there is no upper limit
  // to ratio value but above 10 is rellay a limiter
  void SetRatio(double ratio);
  
  // attack in milliseconds for the CompExp algorithm, the original CompExp
  // defaults to 10ms and has a minimum of 1ms with a maximum of 300ms
  void SetAttack(double attack);
  
  // the release time in milliseconds, the original CompExp defaults to 100ms
  // and has a minimum of 50ms and a max of 500ms
  void SetRelease(double release);
  
  // sets the processor mode, 0 is compressor while 1 is expander
  void SetMode(int mode);
  
  // if set to true the processing is bypassed
  void SetBypass(bool toggle);
  
private:

#define AMP_DB 8.685889638065036553
#define IAMP_DB 0.11512925464970
  
  inline double DBToAmp(double dB)
  {
    return exp(IAMP_DB * dB);
  }
  
  inline double AmpToDB(double amp)
  {
    return AMP_DB * log(fabs(amp));
  }
  
  double mRatio = 1.;
  bool mBypass = false;
  int mMode = kComp;
  envelopeFollower mCompEnv;
  
};

#endif /* CompExp_h */
