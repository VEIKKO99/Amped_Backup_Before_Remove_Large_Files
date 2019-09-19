/**
 * InputFilterFender.h
 * @copyright (C)2015 HoRNet Plugins
 *
 * This class implements the gain knob of Fender amps, there is no frequecy
 * filtering in Fender amps so this is just a gain knob.
 */

#ifndef InputFilterFender_h
#define InputFilterFender_h

#include "InputFilter.h"
#include "rcFilter.h"

class InputFilterFender : public InputFilter {

public:
	
	InputFilterFender() {
		mFreq = 8.;
		mGain = 1.;
	}
	
	/* gain goes from 0 to 10 */
	void setGain(double gain) {
		mGain = FromNormalizedParam(gain, 0., 1., 2.);
	}
	
	void process(double *sample) {
		*sample = *sample * mGain;
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
