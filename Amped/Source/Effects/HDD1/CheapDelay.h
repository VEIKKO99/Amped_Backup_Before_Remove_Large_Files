/**
 * CheapDelay.h
 * @copyright (C)2015 HoRNet Plugins
 *
 * This class implements a cheap digital delay simulating a fixed memory chip
 * being accessed at different speed to change delay times
 */

#ifndef CheapDelay_h
#define CheapDelay_h

#ifndef _MSC_VER
#define _aligned_malloc(N, A) malloc(N)
#define _aligned_free(P) free(P)
#endif

class CheapDelay {

public:
	
	CheapDelay() {
		mSampleRate = 44100;
		mBufferPointer = 0;
		mOsAmount = 20;
		mHoldMode = false;
		mBankCreated = false;
	}
	
	~CheapDelay() {
        if (mBankCreated)
            _aligned_free(mMemoryBank);
	}
	
	double processDelay(double inSample) {
		double outSample = 0.;
		for (int i = 0; i < round(mOsAmount * mClockMultiplier); i++) {
				outSample = advanceBuffer(inSample);
		}
		return outSample;
	}
	
	void setMaxDelayTime(int milliseconds) {
		mMaxDlyTime = milliseconds;
		double seconds = milliseconds / 1000.;
		int size = round(mSampleRate * seconds);
		mMaxReadPointer = floor(mOsAmount * size);
		if (mMaxReadPointer >= mSize) {
			mMaxReadPointer = mSize;
		}
		if(mBufferPointer >= mMaxReadPointer) {
			mBufferPointer = mMaxReadPointer;
		}
	}
	
	void setHoldMode(bool toggle) {
		mHoldMode = toggle;
	}
	
	void setDlyTime(int milliseconds) {
		mDlyTime = milliseconds;
		if (mDlyTime > mMaxDlyTime) {
			mDlyTime = mMaxDlyTime;
		}
		mClockMultiplier =  (double)mMaxDlyTime / (double)mDlyTime;
	}
	
	void setSampleRate(int sampleRate) {
		mSampleRate = sampleRate;
	}
	
	void setMemoryBankSize(int size) {
		mSize = size * mOsAmount;
		if(mBankCreated) {
			_aligned_free(mMemoryBank);
		}
		mMemoryBank = (double*) _aligned_malloc(mSize * sizeof(double),16);
		mBankCreated = true;
		// zero buffer
		zeroBuffer();
	}
	
	void zeroBuffer() {
		for (int i = 0; i < mSize; i++) {
			mMemoryBank[i] = 0.;
		}
		mBufferPointer = 0;
	}

private:
	
	inline double advanceBuffer(double sample) {
		if(mHoldMode == false) {
			mMemoryBank[mBufferPointer] = sample;
		}
		mBufferPointer++;
		if(mBufferPointer >= mMaxReadPointer) {
			mBufferPointer = 0;
		}
		return mMemoryBank[mBufferPointer];
	}
	
	double* mMemoryBank;
	int mOsAmount;
	int mSize;
	double mClockMultiplier;
	int mSampleRate;
	int mMaxDlyTime;
	int mDlyTime;
	int mBufferPointer;
	int mMaxReadPointer;
	bool mHoldMode;
	bool mBankCreated;
	
	
};


#endif
