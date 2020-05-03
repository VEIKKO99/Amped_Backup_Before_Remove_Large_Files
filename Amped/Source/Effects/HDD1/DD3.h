/**
 * DD3.h
 * @copyright (C)2015 HoRNet Plugins
 *
 * This class implements the processing for the BOSS DD3 delay emulation
 */

#ifndef Dly_DD3_h
#define Dly_DD3_h

#include "AudioProcessor.h"
#include "DspFilter.h"
#include "CheapDelay.h"
#include <ctime>
#include <cstdlib>

enum eDD3DelayMode {
	kDD3Dly50 = 0,
	kDD3Dly200,
	kDD3Dly800,
	kDD3DlyHold,
	kNumDD3DlyModes
};

inline double FromNormalizedParam(double normalizedValue, double min, double max, double shape)
{
  return min + pow((double) normalizedValue, shape) * (max - min);
}
  
class DD3 : public Effects_DD::AudioProcessor {

public:
	
	DD3() {
		srand (static_cast <unsigned> (time(0)));
		mDrySample = 0.;
		mPrevDlySample = 0.;
		mSampleRate = 44100;
		mActive = false;
		mStereoMode = false;
		mHoldMode = false;
		mMakeHiss = true;
		mAnalogSat = true;
		mMinDlyTime = 12.5;
		mMaxDlyTime = 50.;
		mDelayTime = 0.;
		mFeedback = 0.;
		mPrevDlySample = 0.;
		mEffectLevel = 1.;
	}
	
	void setDelayMode(int delayMode) {
		mHoldMode = false;
		switch (delayMode) {
			case kDD3Dly50:
			default:
				mDelay.setMaxDelayTime(50);
				mMinDlyTime = 12.5;
				mMaxDlyTime = 50.;
				break;
			case kDD3Dly200:
				mDelay.setMaxDelayTime(200);
				mMinDlyTime = 50.;
				mMaxDlyTime = 200.;
				break;
			case kDD3Dly800:
				mDelay.setMaxDelayTime(800);
				mMinDlyTime = 200.;
				mMaxDlyTime = 800.;
				break;
			case kDD3DlyHold:
				mHoldMode = true;
				mDelay.setMaxDelayTime(800);
				mMinDlyTime = 200.;
				mMaxDlyTime = 800.;
				mDelay.zeroBuffer();
		}
		mDelay.setDlyTime( FromNormalizedParam(mDelayTime, mMinDlyTime, mMaxDlyTime, 1) );
	}
	
	void setDelayTime(double delayTime) {
		mDelayTime = delayTime;
		mDelay.setDlyTime( FromNormalizedParam(delayTime, mMinDlyTime, mMaxDlyTime, 1) );
	}
	
	void setFeedback(double fdbkAmount) {
		mFeedback = fdbkAmount;
	}
	
	void setEffectLevel(double effectAmount) {
		mEffectLevel = effectAmount;
	}
	
	void setActive(bool toggle) {
		mActive = toggle;
	}
	
	void setStereoMode(bool toggle) {
		mStereoMode = toggle;
	}
	
	void setAnalogHiss(bool toggle) {
		mMakeHiss = toggle;
	}
	
	void setAnalogSat(bool toggle) {
		mAnalogSat = toggle;
	}
	
	double mDrySample;
	
    inline double AmpToDB(double amp)
    {
      return AMP_DB * log(fabs(amp));
    }
    
    inline double DBToAmp(double dB)
    {
      return exp(IAMP_DB * dB);
    }
    
	void processDsp(double* samples, int samplesCount) {
		
		long int m = 1 << (12-1);
		
		while (samplesCount--) {
			
			if(mAnalogSat) {
				*samples = tanh(*samples);
			}
			
			mPreEmph.ProcessII(1, samples);
			double drySample = *samples;
			
			mAntiAlias.ProcessII(1, samples);

			*samples = *samples + (mPrevDlySample * mFeedback);
			
			//compressor
			mCompEnv.Process(1, samples);
			double env = mCompEnv.Envelope(1);
			double envdB = AmpToDB(env) / 2.;
			double gainReduction = env / DBToAmp(envdB);
			*samples = *samples * gainReduction;
			
			// simulate 12bit ADC
			*samples = (long int)(*samples * m)/(double)m;
			
			//if (mActive || mHoldMode) {
				*samples = mDelay.processDelay(*samples);
			//}
			
			// expander
			mExpEnv.Process(1, samples);
			env = mExpEnv.Envelope(1);
			envdB = AmpToDB(env) * 2.;
			gainReduction = env / DBToAmp(envdB);
			*samples = *samples * gainReduction;
			
			// save for feedback and compensate gain
			mPrevDlySample = *samples;
			
			mReconstruction.ProcessII(1, samples);
			
			*samples = *samples * 1.58489; // recover 4dB lost somewhere
			
			if(mActive) {
				mDelay.setHoldMode(mHoldMode);
				if(mStereoMode) {
					mDrySample = drySample;
					drySample = 0.;
				}
				*samples = drySample + (*samples * mEffectLevel);
			} else {
				if(mStereoMode) {
					mDrySample = drySample;
					drySample = 0.;
				}
				mDelay.setHoldMode(false);
				*samples = drySample;
			}
			
			mDeEmph.ProcessII(1, samples);
			
			if(mMakeHiss) {
				float random = -1. + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(1. - -1.)));
				*samples = *samples + random * 1.77828e-05; // -95dB SNR;
			}
			
			samples++;
		}
	}
	
	void oversampleSetup() {
		mDelay.setSampleRate(mSampleRate * mOversample);
		mPreEmph.Setup(3386./(mSampleRate * mOversample), 6., 0.707);
		mDeEmph.Setup(3386./(mSampleRate * mOversample), -6., 0.707);
		mAntiAlias.SetupAs(7000./(mSampleRate * mOversample));
		mReconstruction.SetupAs(7000./(mSampleRate * mOversample));
		mCompEnv.Setup(42., 42., mSampleRate * mOversample);
		mExpEnv.Setup(42., 42., mSampleRate * mOversample);
		int size = floor(mSampleRate * 0.8);
		mDelay.setMemoryBankSize(size);
	}
	
	bool mActive;
	bool mStereoMode;
	bool mHoldMode;
	bool mMakeHiss;
	bool mAnalogSat;
	CheapDelay mDelay;
	double mMinDlyTime;
	double mMaxDlyTime;
	double mDelayTime;
	double mFeedback;
	double mPrevDlySample;
	double mEffectLevel;
	Dsp::BiquadHighShelf<1> mPreEmph;
	Dsp::BiquadLowShelf<1> mDeEmph;
	Dsp::ButterLowPass<3, 1> mAntiAlias;
	Dsp::ButterLowPass<2, 1> mReconstruction;
	Dsp::EnvelopeFollower<1> mCompEnv;
	Dsp::EnvelopeFollower<1> mExpEnv;
	
};

#endif
