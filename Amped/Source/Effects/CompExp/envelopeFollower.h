/**
 * envelopeFollower.h
 * @copyright (C)2012 HoRNet Plugins
 *
 *  A simple envelope follower implementation
 */

#ifndef envelopeFollower_h
#define envelopeFollower_h

#include <math.h>

class envelopeFollower {
	
private:
	
	double mEnv;
	int mSampleRate;
	double mAttCoef;
	double mRelCoef;
	
public:
	
	void init(int sampleRate) {
		mEnv = 0.;
		mSampleRate = sampleRate;
	}
	
	void setAttack(double attack){
		mAttCoef = exp( (-1.0 / ((attack/1000.) * mSampleRate )) );
	}
	
	void setRelease(double release){
		mRelCoef = exp( (-1.0 / ((release/1000.) * mSampleRate )) );
	}
	
	void setAttack99(double attack){
		mAttCoef = pow( 0.01, 1.0 / ( attack * mSampleRate * 0.001 ) );
	}
	
	void setRelease99(double release){
		mRelCoef = pow( 0.01, 1.0 / ( release * mSampleRate * 0.001 ) );
	}
	
	double process(double sample) {
		sample=fabs(sample);
		double coef;
		if (sample > mEnv) {
			coef = mAttCoef;
		}else{
			coef = mRelCoef;
		}
		mEnv *= coef;
		mEnv += (1-coef)* sample;
		return mEnv;
	}
	
};

#endif

