/**
 * AudioProcessor.h
 * @copyright (C)2015 HoRNet Plugins
 *
 * This class implements the basic interface with the audio plugin allowing
 * for oversample and block process
 */

#ifndef AudioProcessor_h
#define AudioProcessor_h

// aligned malloc for CLANG and GCC
#ifndef _MSC_VER
#define _aligned_malloc(N, A) malloc(N)
#define _aligned_free(P) free(P)
#endif

#include "DspFilter.h"

class AudioProcessor {
	
public:
	
	AudioProcessor() {
		mSampleRate = 44100;
		mDryWet = 1.;
		mOversample = 1;
	}
	
	virtual void setOversample(int oversampleAmount) {
		if (oversampleAmount < 1) {
			oversampleAmount = 1;
		}
		mOversample = oversampleAmount;
		osFilter.SetupAs((mSampleRate/2.)/(mSampleRate * mOversample),9);
		dwnFilter.SetupAs((mSampleRate/2.)/(mSampleRate * mOversample),9);
		oversampleSetup();
	}
	
	virtual void setDryWet(double drywet) {
		mDryWet = drywet;
	}
	
	virtual void init() {
		osFilter.Reset();
		dwnFilter.Reset();
		osFilter.SetupAs((mSampleRate * 0.5)/(mSampleRate * mOversample),9);
		dwnFilter.SetupAs((mSampleRate * 0.5)/(mSampleRate * mOversample),9);
	}
	
	virtual void setSampleRate(int sampleRate) {
		mSampleRate = sampleRate;
	}
	
	virtual void setNumChans(int chans) {
		mNChans = chans;
	}

	void inline process(double *samples, int samplesCount) {
		
		if(mOversample > 1){
			samplesCount = samplesCount * mOversample;
			double* osSamples = (double*) _aligned_malloc (samplesCount * mNChans * sizeof(double),16);
			double* drySamples = (double*) _aligned_malloc (samplesCount * mNChans * sizeof(double),16);
			oversample(samples, osSamples, samplesCount/mOversample);
			Dsp::copy(mNChans, samplesCount, drySamples, osSamples);
			processDsp(osSamples, samplesCount);
			Dsp::scale(mNChans, samplesCount, osSamples, mDryWet);
			Dsp::scale(mNChans, samplesCount, drySamples, 1. - mDryWet);
			Dsp::mix(mNChans, samplesCount, osSamples, drySamples);
			downsample(osSamples, samples, samplesCount);
			_aligned_free(osSamples);
			_aligned_free(drySamples);
		}else{
			double* drySamples = (double*) _aligned_malloc (samplesCount * mNChans * sizeof(double),16);
			Dsp::copy(mNChans, samplesCount, drySamples, samples);
			processDsp(samples, samplesCount);
			Dsp::scale(mNChans, samplesCount, samples, mDryWet);
			Dsp::scale(mNChans, samplesCount, drySamples, 1. - mDryWet);
			Dsp::mix(mNChans, samplesCount, samples, drySamples);
			_aligned_free(drySamples);
		}
	}
	
protected:
	
	// this is the actual processing of the DSP, must be overridden by concrete class
	virtual void processDsp(double *samples, int samplesCount) = 0;
	
	// this is called after the setting of the oversampling amount to allow for concrete classes
	// to correctly setup their stuff
	virtual void oversampleSetup() = 0;
	
	int mSampleRate;
	int mOversample;
	
	double mNChans;
	
private:
	
	void oversample(double* samplesSrc, double* samplesDest, int numSamples) {
		int tmpSamples = numSamples;
		double* osSamplesPtr = samplesDest;
		while(tmpSamples > 0){
			double sampleL = *samplesSrc;
			double sampleR;
			*samplesDest = sampleL;
			++samplesDest;
			++samplesSrc;
			
			if(mNChans == 2) {
				sampleR = *samplesSrc;
				*samplesDest = sampleR;
				++samplesDest;
				++samplesSrc;
			}
			
			for(int i = 0; i < (mOversample - 1); i++){
				*samplesDest = sampleL;
				++samplesDest;
				if(mNChans == 2) {
					*samplesDest = sampleR;
					++samplesDest;
				}
			}
			--tmpSamples;
		}
		osFilter.ProcessII(numSamples * mOversample, osSamplesPtr);
	}

	void downsample(double* samplesSrc, double* samplesDest, int numSamples) {
		dwnFilter.ProcessII(numSamples, samplesSrc);
		while(numSamples > 0){
			*samplesDest = *samplesSrc;
			++samplesDest;
			++samplesSrc;
			
			if (mNChans == 2) {
				*samplesDest = *samplesSrc;
				++samplesDest;
				++samplesSrc;
			}
			
			--numSamples;
			for(int i = 0; i < (mOversample -1); i++){
				++samplesSrc;
				if (mNChans == 2) {
					++samplesSrc;
				}
				--numSamples;
			}
		}
	}
	
	double mDryWet;
	Dsp::ChebyIILowPass<6,1> osFilter;
	Dsp::ChebyIILowPass<6,1> dwnFilter;

};

#endif
