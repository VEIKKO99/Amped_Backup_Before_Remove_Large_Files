/**
 * InputFilterMarshall.h
 * @copyright (C)2015 HoRNet Plugins
 *
 * This class implements the behavior of the filtering linked to the gain knob
 * in Marshall amps
 */

#ifndef InputFilterMarshall_h
#define InputFilterMarshall_h

#include "InputFilter.h"
#include "DspFilter.h"

class InputFilterMarshall : public InputFilter {

public:
	
	InputFilterMarshall() {
		mFreq = 8.;
		mGain = 1.;
	}
	
	/* gain goes from 0 to 1 */
	void setGain(double gain) {
		gain = FromNormalizedParam(gain, 0., 10., 2.);
		// empirically found using eurequa
		mFreq = 899.938927087152 + 14100.0610855761*pow(0.0178004541663901,sqrt(gain)) + 1549.7708267355*gain/exp(pow(gain,(1.25096632097358 + 1002.99272966155*pow(0.0183815986072618,gain))));
		mGain = pow(1.10075302780872,gain) + -64.0000102624155/exp(pow((0.936511286733256*gain),0.389489311829953));
		mBrightLs.Setup(mFreq / mSampleRate, mGain, 0.5);
	}
	
	void process(double *sample) {
		mBrightLs.ProcessII(1, sample);
	}
	
	void setSampleRate(int sampleRate) {
		InputFilter::setSampleRate(sampleRate);
		mBrightLs.Setup(mFreq / mSampleRate, mGain);
	}
	
private:
	
	Dsp::BiquadLowShelf<1> mBrightLs;

};

#endif /* InputFilterGuitarKit_h */
