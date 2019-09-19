/**
 * InputFilterMesa.h
 * @copyright (C)2015 HoRNet Plugins
 *
 * This class implements the behavior of the filter linked to the gain knob in
 * Mesa Boogie style amplifier
 */

#ifndef InputFilterMesa_h
#define InputFilterMesa_h

#include "InputFilter.h"
#include "DspFilter.h"

class InputFilterMesa : public InputFilter {

public:
	
	InputFilterMesa() {
		mFreq = 8.;
		mGain = 1.;
	}
	
	/* gain goes from 0 to 1 */
	void setGain(double gain) {
		gain = FromNormalizedParam(gain, 0., 10., 2.);
		// empirically found using eurequa
		mFreq = 393.178403183687 + 0.00214917755903875*pow(gain,6) + 166.996875220576/(0.0362499002619686 + gain) + 1.09965224877834e-21*pow(209.054691904321,gain)*pow(gain,2) - 9.19313961905175*gain;
		mGain = (3.67302525738676*gain - 36.7316847846717)/(0.612194197731186 + pow((1.08197967906607*gain),0.530518300496681));
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
