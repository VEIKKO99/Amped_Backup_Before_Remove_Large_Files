/**
 *
 * rcFilter.h
 * @copyright (C)2015 HoRNet Plugins
 *
 * This class implements the classic RC anlog filter network
 * It can work as a first order high pass or low pass filter
 */

#ifndef __RCFILTER
#define __RCFILTER

class rcFilter
{
public:
  
	rcFilter()
	{

		//reset coeficents
		a0=a1=b1=0.0;

		// in/out history
		ou1=ou2=in1=in2=0.0;
	}

	void reset()
	{
		// in/out history
		ou1=ou2=in1=in2=0.0;
	}

	void init(int type, float samplerate, float cutoff)
	{
		// temp pi
		double const temp_pi=3.1415926535897932384626433832795;
		double const e=2.71828182845904523536;

		double x;
		x=pow(e,(-2*temp_pi*(cutoff/samplerate)));
		//type 0 lowpass
		if(type==0)
		{
			a0=1-x;
			a1=0;
			b1=x;

		//type 1 highpass
		}else{
			a0=(1+x)/2;
			a1=-(1+x)/2;
			b1=x;
		}

	}

	inline void process(double *in, register int sampleCount)
	{
		//double ou;
		double i1,i2,i3;

		while(sampleCount){
      // prevent denormals
			*in += 0.00000000000000000000001;
			i1 = b1*ou1;
			i2 = a1*in1;
			i3 = a0* *in;
			// push in/out buffers
			in2=in1;
			in1=*in;
			ou2=ou1;
			*in=i3+i2+i1;
			ou1=*in;

			in++;

			--sampleCount;
		}


	}

	private:

	// in/out history
	double ou1,ou2,in1,in2;

	double a0,a1,b1;
};

#endif
