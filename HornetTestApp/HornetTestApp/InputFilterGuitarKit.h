/**
 * InputFilterGuitarKit.h
 * @copyright (C)2015 HoRNet Plugins
 *
 * This class implements ta custom designed input filter for the gain knob,
 * it's an high pass filter with linear behaviour from 600 to 4000 hertz
 */

#ifndef InputFilterGuitarKit_h
#define InputFilterGuitarKit_h

#include "InputFilter.h"
#include "rcFilter.h"

class InputFilterGuitarKit : public InputFilter {

public:
	
	InputFilterGuitarKit() {
		mFreq = 10.;
		mGain = 1.;
	}
	
	/* gain goes from 0 to 1 */
	void setGain(double gain) {
		mGain = gain;
		mFreq = FromNormalizedParam(1. - mGain, 600., 4000., 2.);
		mBrigthHp.init(1, mSampleRate, mFreq);
	}
	
	void process(double *sample) {
		mBrigthHp.process(sample, 1);
	}
	
	void setSampleRate(int sampleRate) {
		InputFilter::setSampleRate(sampleRate);
		mBrigthHp.init(1, mSampleRate, mFreq);
		mBrigthHp.reset();
	}
	
private:
	
	rcFilter mBrigthHp;

};

#endif /* InputFilterGuitarKit_h */
