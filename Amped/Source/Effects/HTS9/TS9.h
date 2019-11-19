/**
 * TS9.h
 * @copyright (C)2017 HoRNet Plugins
 *
 * This class emulates the TS9 Ibanez "Tube Screamer" guitar pedal
 */

#ifndef HTS9_h
#define HTS9_h

#include "AudioProcessor.h"
#include "rcfilter.h"
#include <ctime>
#include <cstdlib>

class ts9 : public AudioProcessor {

public:
	
	ts9() {
		srand (static_cast <unsigned> (time(0)));
		
		mOutScaler = 1.;
		mDistAmp = 0.;
		mToneMix = 0.5;
		mLevel = 1.;
		mCurAmp = 1.;
		mBypass = false;
		mHiss = true;
		mAnalogSat = true;
		mOversample = 1;
		mSampleRate = 44100;
		mDistCutOff = 20000.;
		mOutCompensation = true;
		lp1.init(0, mSampleRate * mOversample, mDistCutOff);
		oversampleSetup();
	}
	
	// amp goes from 0 to 1
	void setDistAmp(double amp) {
    amp = amp * amp * amp * amp;
		mCurAmp = amp;
		// op amp distortion, gain goes from 21dB to 41dB
    mDistAmp = DBToAmp(21) + (amp * DBToAmp(41));
		mDistCutOff = 20000. - (amp * 12000);
		lp1.init(0, mSampleRate * mOversample, mDistCutOff);
	}
	
	// tone mix goes from 0 to 1
	void setTone(double tone) {
		mToneMix = tone;
	}
	
	void setBypass(bool bypass) {
		mBypass = bypass;
	}
	
	// level goes from 0 to 1
	void setLevel(double level) {
		mLevel = level;
	}
	
	void setHiss(bool hiss) {
		mHiss = hiss;
	}
	
	void setAnalogSat(bool sat) {
		mAnalogSat = sat;
	}
	
	void setOutCompensation(bool toggle) {
		mOutCompensation = toggle;
	}
 
protected:
	
	void processDsp(double *samples, int samplesCount) {
		
		while (samplesCount--) {
			
			if (!mBypass) {
				
				// high shelf at 720Hz
				double cleanSample = *samples;
				*samples = *samples * mDistAmp * 0.8;
				hp1.process(samples, 1);
        
        if(mAnalogSat) {
          // diode clipper we approximate the diode wix y = 1-EXP(-x) since is not simmetrical
          // we clip positive and negative parts separately and then assemble everything back together
          if(*samples > 0) {
            *samples = 1 - exp(-1 * *samples);
          } else {
            *samples = fabs(*samples);
            *samples = 1 - exp(-1 * *samples);
            *samples = -1 * *samples;
          }
        } else {
          if (*samples > 0.7) {
            *samples = 0.7;
          } else if (*samples < -0.7) {
            *samples = -0.7;
          }
        }
        
        // process the lp filter after the diode clipper
        lp1.process(samples, 1);
      
				*samples = cleanSample + *samples;
        
        
				
				// op amp distortion, gain is applied to hi shelf filter
				if(mAnalogSat) {
					*samples = fast_tanh(*samples);
				}
				
				// process the low pass before the tone control
				lp2.process(samples, 1);
				
				// tone control mixes the signal between a highpass (3200Hz) and a low shelf filter (720Hz)
				// when mToneMix id 0 we have just lowpass, when 1 just highpass
				double sampleLp = *samples * (1 - 0.177828); // -15dB for the low shelf gain
				double sampleHp = *samples;
				toneLp.process(&sampleLp, 1);
				sampleLp = *samples - sampleLp;
				toneHp.ProcessI(1, &sampleHp);
				*samples = ((1. - mToneMix) * sampleLp) + (mToneMix * sampleHp);
				
				// set dist level
				*samples = *samples * mLevel;
				
				if(mOutCompensation == true) {
					// compensate for gain increase due to dist increase
					*samples = *samples * (1.-(mCurAmp * 0.7 ));
				}
				
			}
			
			// last output transistor
			if (mAnalogSat) {
				*samples = fast_tanh(*samples * DBToAmp(20.9))  ;
			}
			
			if(mHiss) {
				float random = -1. + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(1. - -1.)));
				*samples = *samples + random * 1e-05;
			}
			
			// increase sample pointer
			samples++;
		}
		
	}
	
	void oversampleSetup() {
		hp1.init(1, mSampleRate * mOversample, 720.);
		lp1.init(0, mSampleRate * mOversample, mDistCutOff);
		lp2.init(0, mSampleRate * mOversample, 723.4);
		
		toneHp.Setup(1600./mSampleRate * mOversample, 15., 0.707);
		toneLp.init(1, mSampleRate * mOversample, 3170.);
	}
	
private:
	
	double inline fast_tanh(double sample) {
    sample *= 3;
		sample = sample/(0.11605589854E+01+0.37011709966E+00 * sample * sample)+0.10710006710E+00 * sample;
		if(sample > 1.){
			sample = 1.;
		}else if(sample < -1.){
			sample = -1.;
		}
		return sample * 0.33;
	}
	
	rcFilter hp1;
	rcFilter lp1;
	rcFilter lp2;
	Dsp::BiquadHighShelf<1> toneHp;
	rcFilter toneLp;
	
	double mOutScaler;
	double mDistAmp;
	double mDistCutOff;
	double mToneMix;
	double mLevel;
	double mCurAmp;
	bool mBypass;
	bool mHiss;
	bool mAnalogSat;
	bool mOutCompensation;
};


#endif /* HTS9_h */
