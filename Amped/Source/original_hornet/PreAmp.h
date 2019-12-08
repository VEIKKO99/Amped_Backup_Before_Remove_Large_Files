/**
 * PreAmp.h
 * @copyright (C)2015 HoRNet Plugins
 *
 * This class implements a preamplifier made by three tubes in cascade.
 * A high gain option is available using a preamp tube *before* the input
 * filter like implemented in the "high" input of the JCM800
 */

#ifndef PreAmp_h
#define PreAmp_h

#include "TubeStage.h"
#include "rcFilter.h"
#include "DspFilter.h"
#include "InputFilterGuitarKit.h"
#include "InputFilterFender.h"
#include "InputFilterMarshall.h"
#include "InputFilterMesa.h"

#define NUMBER_OF_STAGES 4

class PreAmp {

public:
	
	enum EInputType
	{
		kGuitarKit = 0,
		kFender,
		kMarshall,
		kMesa
	};
	
	TubeStage tubeStage[NUMBER_OF_STAGES];

	int amountOfPreampTubesInUse = 3;
	
	PreAmp() {
		mGain = 1.;
		mLsFreq = 20000;
		mLsGain = -100.;
		mHighGainStage = true;
		mSampleRate = 44100;
		tubeStage[0].setRK(2700);
		tubeStage[0].setRP(100000);
		tubeStage[0].setVk0(2.2);
		tubeStage[0].setLowPassFbk(86.);
		tubeStage[0].setOutHpFreq(30.);
		tubeStage[0].setVPlus(334);
		tubeStage[1].setRK(820);
		tubeStage[1].setRP(100000);
		tubeStage[1].setVk0(3.3);
		tubeStage[1].setLowPassFbk(86.);
		tubeStage[1].setOutHpFreq(30.);
		tubeStage[1].setVPlus(334);
		tubeStage[2].setRK(820);
		tubeStage[2].setRP(100000);
		tubeStage[2].setVk0(1.2);
		tubeStage[2].setLowPassFbk(86.);
		tubeStage[2].setOutHpFreq(30.);
		tubeStage[2].setVPlus(348);
		tubeStage[3].setRK(100000);
		tubeStage[3].setRP(0);
		tubeStage[3].setVk0(3.82);
		tubeStage[3].setLowPassFbk(0);
		tubeStage[3].setOutHpFreq(30.);
		tubeStage[3].setVPlus(348);
		mBrigthHp.init(1, mSampleRate, 20000);
		mInputFilter = new InputFilterGuitarKit();
	}
	
	void setSampleRate(int sampleRate) {
		mSampleRate = sampleRate;
		for (int i = 0; i < NUMBER_OF_STAGES; i++) {
			tubeStage[i].setSampleRate(sampleRate);
		}
		mBrigthHp.init(1, mSampleRate, mLsFreq);
		mInputFilter->setSampleRate(mSampleRate);
	}
	
  /**
   * Sets the gain of the input filter, the range is from 0 to 1
   */
	void setGain( double gain) {
		mGain = gain;
		mInputFilter->setGain(gain);
	}
	
  /**
   * Sets the input filter type using one of the values in
   * EInputType enum
   */
	void setInputType(int inputType) {
		
		switch (inputType) {
			case EInputType::kGuitarKit:
				mInputFilter = new InputFilterGuitarKit();
				break;
				
			case EInputType::kFender:
				mInputFilter = new InputFilterFender();
				break;
				
			case EInputType::kMarshall:
				mInputFilter = new InputFilterMarshall();
				break;
				
			case EInputType::kMesa:
				mInputFilter = new InputFilterMesa();
				break;
				
			default:
				mInputFilter = new InputFilterGuitarKit();
				break;
		}
		mInputFilter->setSampleRate(mSampleRate);
		mInputFilter->setGain(mGain);
	}
	
	double inline process(double sample) {
		if (mHighGainStage) {
			sample = tubeStage[0].process(sample);
		}
		
		mInputFilter->process(&sample);
		
		for (int i = 1; i < amountOfPreampTubesInUse; i++) {
			sample = tubeStage[i].process(sample);
		}
		// lower 6db to recover high gain stage
		if (mHighGainStage) {
			sample = sample * 0.5;
		}
		return sample;
	}
	
	void setHighGainStageActive(bool toggle) {
		mHighGainStage = toggle;
	}

    void setAmountOfPreampTubesInUse(int amountOfTubes) {
		this->amountOfPreampTubesInUse = amountOfTubes;
    }

private:
	
	int mSampleRate;
	int mInputType;
	bool mHighGainStage;
	double mGain;
	double mLsFreq;
	double mLsGain;
	
	rcFilter mBrigthHp;
	Dsp::ButterLowShelf<1,1> mBrightLs;
	
	InputFilter* mInputFilter;

};

#endif 
