/**
 * InputFilter.h
 * @copyright (C)2015 HoRNet Plugins
 *
 * This class implements the base interface from which all the input filters
 * are derived.
 */

#ifndef InputFilter_h
#define InputFilter_h

class InputFilter {

	
public:
	
	/* gain goes from 1 to 10 */
	virtual void setGain(double gain) = 0;
	
	virtual void process(double* sample) = 0;
	
	void setSampleRate(int sampleRate) {
		mSampleRate = sampleRate;
	}
	
protected:
  
  inline double FromNormalizedParam(double normalizedValue, double min, double max, double shape)
  {
    return min + pow((double) normalizedValue, shape) * (max - min);
  }
	
	double mFreq;
	double mGain;
	int mSampleRate;
};

#endif /* InputFilter_h */
