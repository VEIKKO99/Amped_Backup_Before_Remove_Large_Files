/**
 * TubeAmp.h
 * @copyright (C)2015 HoRNet Plugins
 *
 * This class implements an ideal tube amplifier that uses the 4 stages preamp
 * found in PreAmp.h and a final pentode stage in push pull configuration
 * It also implements the "presence" control
 * The class inherits from the "AudioProcessor" base class that takes care of
 * oversampling and other duties
 */

#ifndef TubeAmp_h
#define TubeAmp_h

#include "HornetAudioProcessor.h"
#include "PreAmp.h"
#include "ToneStack.h"
#include "TubeStage.h"
#include "rcFilter.h"
#include "DspFilter.h"

class TubeAmp : public HornetAudioProcessor {

public:
	
	TubeAmp() {
		mHighGainActive = true;
		mToneStackActive = true;
		mTreble = 0.5;
		mMid = 0.5;
		mBass = 0.5;
		mToneStack.updateCoefs(mBass, mMid, mTreble);
		mVolume = 0.5;
		mPrevSample = 0.;
		mPresenceFreq = 20000.;
	}
	
	void setHighGainStageActive(bool toggle) {
		mHighGainActive = toggle;
		mPreAmp.setHighGainStageActive(toggle);
	}
	
	void setTubeType(int stage, int tubeType) {
		mPreAmp.tubeStage[stage].setTubeType(tubeType);
	}
	
	void setInputType(int type) {
		mPreAmp.setInputType(type);
	}
	
	void setPreGain( double gain ) {
		mPreGain = gain;
		mPreAmp.setGain(gain);
	}
	
	void setToneStackActive(bool toggle) {
		mToneStackActive = toggle;
	}
	
	void setToneStackHigh(double high) {
		mTreble = high;
		mToneStack.updateCoefs(mBass, mMid, mTreble);
	}
	
	void setToneStackMid(double mid) {
		mMid = mid;
		mToneStack.updateCoefs(mBass, mMid, mTreble);
	}
	
	void setToneStackLow(double low) {
		mBass = low;
		mToneStack.updateCoefs(mBass, mMid, mTreble);
	}
	
	void setToneStackModel(int ToneStackModel) {
		mToneStack.setModel(ToneStackModel);
		mToneStack.updateCoefs(mBass, mMid, mTreble);
	}
	
	void setMasterVolume( double volume ) {
		mVolume = volume;
	}
	
	void setPowerAmpTubeType(int tubeType) {
		mPowerAmp[0].setTubeType(tubeType);
		mPowerAmp[1].setTubeType(tubeType);
	}
	
	void setPresence(double presence) {
		mPresenceFreq = 720. + ((1. - presence) * 20000);
		mPresence.init(1, mSampleRate * mOversample, mPresenceFreq);
	}
	
	PreAmp mPreAmp;
	TubeStage mPowerAmp[2];

    void setAmountOfPreampTubesInUse(int amountOfTubes) {
        mPreAmp.setAmountOfPreampTubesInUse(amountOfTubes);
    }

protected:
	
	void oversampleSetup() {
		mPreAmp.setSampleRate(mSampleRate * mOversample);
		mToneStack.setSampleRate(mSampleRate * mOversample);
		mToneStack.updateCoefs(mBass, mMid, mTreble);
		mPowerAmp[0].setSampleRate(mSampleRate * mOversample);
		mPowerAmp[1].setSampleRate(mSampleRate * mOversample);
		mPowerAmp[0].setVPlus(468);
		mPowerAmp[0].setRK(0.);
		mPowerAmp[0].setRP(3.4e3);
		mPowerAmp[0].setVk0(0);
		mPowerAmp[0].setOutHpFreq(10.);
		mPowerAmp[0].setLowPassFbk(338.);
		mPowerAmp[1].setVPlus(468);
		mPowerAmp[1].setRK(0.);
		mPowerAmp[1].setRP(3.4e3);
		mPowerAmp[1].setVk0(0);
		mPowerAmp[1].setOutHpFreq(10.);
		mPowerAmp[1].setLowPassFbk(338.);
		mPresence.init(1, mSampleRate * mOversample, mPresenceFreq);
		mDCBlock.init(1, mSampleRate * mOversample, 10.);
		
	}
	
	void inline processDsp(double *samples, int samplesCount) {
		double* tmpSamples = samples ;
		int tmpSampleCount = samplesCount;
		
		while (samplesCount--) {
			for (int i = 0; i < mNChans; i++) {
				*samples = mPreAmp.process(*samples);
				if (mToneStackActive == true) {
					*samples = mToneStack.process(*samples);
					//*samples = *samples * 2.;
				}
				//*samples = (*samples / 340.); // * mVolume;
				*samples *= mVolume;
				double tmpSample = *samples;
				mPresence.process(&tmpSample, 1);
				*samples = *samples + (tmpSample * 1.5);
				double samplePush = mPowerAmp[0].process(*samples -27.01); // simulate a little difference between psh and pull tubes
				double samplePull = mPowerAmp[1].process((*samples * -1.) -27.);
				*samples = (samplePush - samplePull);
				*samples = *samples / 468.; // bring back the level to more resonable scale
				//mDCBlock.process(samples, 1);
				//*samples = samplePull;
				samples++;
			}
		}
	}
	
private:
	
	double mPreGain;
	double mBass;
	double mMid;
	double mTreble;
	double mVolume;
	double mPrevSample;
	double mPresenceFreq;
	
	bool mHighGainActive;
	bool mToneStackActive;
	
	DSP::ToneStack mToneStack;
	
	rcFilter mPresence;
	rcFilter mDCBlock;

};

#endif /* TubeAmp_h */
