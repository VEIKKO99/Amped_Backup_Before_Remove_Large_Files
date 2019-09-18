/**
 * TubeStage.h
 * @copyright (C)2015 HoRNet Plugins
 *
 * This class implements a tube amplification stage it uses valve.h as base to
 * get the output level of a tube from it's table and also models the action of
 * the circuit around the tube itslef (like negative feedback for tube stability
 *
 * For usage example see PreAmp.h and TubeAmp.h
 */

#ifndef TubeStage_h
#define TubeStage_h

#include "rcFilter.h"
#include "valve.h"

class TubeStage {
	
public:
	
	TubeStage() {
		mTubeType = 0;
		mSampleRate = 44100;
		mFbkBypass = false;
		mVPlus = 250;
		mRk = 2700.;
		mVk0 = 2.5;
		mRp = 100000.;
		mPrevSample = 0.;
		mHpOutBypass = false;
		mTubeLpf = 1000.;
		mHighPassFreq = 5.;
	}

	void setTubeType(int tubeType) {
		mTubeType = tubeType;
		// comes from valve.h
		const table1d& tab = *tubetab[tubeType];
		mTubeLpf = tab.fLp;
		mInputLowPass.init(0, mSampleRate, tab.fLp);
	}
	
  /**
   * this sets the voltage of the tube, refer to the schematic of the amp you
   * are modelling for exact value
   */
	void setVPlus(double vplus) {
		mVPlus = vplus;
	}
	
  /**
   * this sets the value of the Cathode resistor for the tube,
   * refer to the schematic of the amp you are modelling for exact value
   */
	void setRK( double rk) {
		if(rk <= 0.) {
			rk = 1.;
		}
		mRk = rk;
	}
	
  /**
   * this sets the value of the polarization resistor (the one on the Anode of
   * the tube) refer to the schematic of the amp you are modelling for
   * exact value
   */
	void setRP(double rp) {
		if(rp <= 0.) {
			rp = 1.;
		}
		mRp = rp;
	}
	
  /**
   * this sets the level of the Cathode voltage, compute using the tool
   * "tube_transfer.py vk0 <tube name> [triode|pentode|pentode2]
   */
	void setVk0(double vk0) {
		mVk0 = vk0;
	}
	
	void setSampleRate(int sampleRate) {
		mSampleRate = sampleRate;
		mInputLowPass.init(0, mSampleRate, mTubeLpf);
		mHighPass.init(1, mSampleRate, mHighPassFreq);
	}
	
  /**
   * Sets the freqeuncy of the lowpass filter made by used for feddback in some
   * tube circuit, refer to the schematic of the amp you are modelling for
   * exact value
   */
	void setLowPassFbk(double lowPassFreq) {
		if(lowPassFreq <= 0) {
			mFbkBypass = true;
		} else {
			mFbkBypass = false;
			mLowPass.init(0, mSampleRate, lowPassFreq);
		}
	}
	
  /**
   * Allows you to model the dc blocking output capacitor of the tube stage
   * that implements an high pass filter. Sometimes they are quite high in
   * frequency so they may have an effect on what's audible
   */
	void setOutHpFreq(double highPassFreq) {
		mHighPassFreq = highPassFreq;
		mHighPass.init(1, mSampleRate, highPassFreq);
		if (highPassFreq <= 0.) {
			mHpOutBypass = true;
		}
	}
	
	double inline process(double register sample) {
		
		// input low pass
		mInputLowPass.process(&sample, 1);
		
		mPrevSample = mPrevSample * (mRk/mRp);
		mLowPass.process(&mPrevSample, 1);
		if(mFbkBypass == true) {
			mPrevSample = 0.;
		}
		sample += mPrevSample;
		sample += -1. * mVk0;
		sample = Ftube(mTubeType, sample);
		double vkc = mVk0 * (mRp/mRk);
		sample += (vkc - mVPlus);
		mPrevSample = sample;
		if (mHpOutBypass == false) {
			mHighPass.process(&sample, 1);
		}
		return sample;
	}
	
private:
	
	int mTubeType;
	int mSampleRate;
	int mHighPassFreq;
	bool mFbkBypass;
	bool mHpOutBypass;
	double mVPlus;
	double mRk;
	double mVk0;
	double mRp;
	double mPrevSample;
	double mTubeLpf;
	rcFilter mLowPass;
	rcFilter mHighPass;
	rcFilter mInputLowPass;
	
};

#endif /* TubeStage_h */
