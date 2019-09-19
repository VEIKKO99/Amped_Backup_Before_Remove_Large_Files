/**
 *
 * ToneStack.h
 * @copyright (C)2015 HoRNet Plugins
 *
 * This class implements the "ToneStack" modelling, tone stack is the bass, mid
 * and high, tone control you have on guitar amplifiers.
 * Right now three different types are modelled:
 * - Fender Bassman 5F6-A (the base for all Fender amps)
 * - Marshall JCM-800 Lead 100 (the base tone for all the Marshal amps)
 * - Vox AC-30 (this one has no "mid" control)
 *
 * See example in TubeAmp.h for usage
 */

#ifndef DSP_TONESTACK_H
#define DSP_TONESTACK_H


#include "TDFII.h"

namespace DSP {

typedef struct {
	double R1, R2, R3, R4;
	double C1, C2, C3;
} TSParameters;
	
	
enum eToneStackTypes {
	kToneStackFender = 0,
	kToneStackMarshall,
	kToneStackMesa,
	kToneStackVox,
	kToneStackCount
};
	
	
class ToneStack 
{
  private:
		enum { Order = 3 };

		double c;   // BT coef

		double b1t, b1m, b1l, b1d,
				b2t, b2m2, b2m, b2l, b2lm, b2d,
				b3lm, b3m2, b3m, b3t, b3tm, b3tl,
				a0, a1d, a1m, a1l, a2m, a2lm, a2m2, a2l, a2d,
				a3lm, a3m2, a3m, a3l, a3d;      // intermediate calculations

		double fs;
		TDFII<Order> filter;
	
		TSParameters presets[4];
	
		int mToneStackModel;
	
	public:

		ToneStack() {
#define k *1e3
#define M *1e6
#define nF *1e-9
#define pF *1e-12
			/* parameter order is R1 - R4, C1 - C3 */
			/* R1=treble R2=Bass R3=Mid, C1-3 related caps, R4 = parallel resistor */
			presets[0].R1 = 250 k; presets[0].R2 = 1 M; presets[0].R3 = 25 k; presets[0].R4 = 56 k;
			presets[0].C1 = 250 pF; presets[0].C2 = 20 nF; presets[0].C3 = 20 nF;  /* 59 Bassman 5F6-A */
			
			presets[1].R1 = 220 k; presets[1].R2 = 1 M; presets[1].R3 = 22 k; presets[1].R4 = 33 k;
			presets[1].C1 = 470 pF; presets[1].C2 = 22 nF; presets[1].C3 = 22 nF; /* 59/81 JCM-800 Lead 100 2203 */
			
			presets[2].R1 = 250 k; presets[2].R2 = 1 M; presets[2].R3 = 25 k; presets[2].R4 = 47 k;
			presets[2].C1 = 600 pF; presets[2].C2 = 20 nF; presets[2].C3 = 20 nF; /* Mesa Dual Rect. 'Orange' */
			
			presets[3].R1 =1 M; presets[3].R2 = 1 M; presets[3].R3 = 20 k, presets[3].R4 = 100 k;
			presets[3].C1 = 50 pF; presets[3].C2 = 22 nF; presets[3].C3 = 22 nF; /* 59/86 Vox AC-30 , it has no mid control */
#undef k
#undef M
#undef nF
#undef pF
			setModel(0);
		}
		
		void setSampleRate (double sampleRate) {
			c = 2 * sampleRate;
			filter.init(sampleRate);
		}

		void reset() { filter.reset(); }
	
		void setModel (int model) {
			mToneStackModel = model;
			setParams (presets[model]);
			filter.reset();
		}

		void setParams (const TSParameters &p) {
			double R1 = p.R1, R2 = p.R2, R3 = p.R3, R4 = p.R4;
			double C1 = p.C1, C2 = p.C2, C3 = p.C3;

			b1t  = C1*R1;
			b1m  = C3*R3;
			b1l  = C1*R2 + C2*R2;
			b1d  = C1*R3 + C2*R3;
			b2t  = C1*C2*R1*R4 + C1*C3*R1*R4;
			b2m2 = -(C1*C3*R3*R3 + C2*C3*R3*R3);
			b2m  = C1*C3*R1*R3 + C1*C3*R3*R3 + C2*C3*R3*R3;
			b2l  = C1*C2*R1*R2 + C1*C2*R2*R4 + C1*C3*R2*R4;
			b2lm = C1*C3*R2*R3 + C2*C3*R2*R3;
			b2d  = C1*C2*R1*R3 + C1*C2*R3*R4 + C1*C3*R3*R4;
			b3lm = C1*C2*C3*R1*R2*R3 + C1*C2*C3*R2*R3*R4;
			b3m2 = -(C1*C2*C3*R1*R3*R3 + C1*C2*C3*R3*R3*R4);
			b3m  = C1*C2*C3*R1*R3*R3 + C1*C2*C3*R3*R3*R4;
			b3t  = C1*C2*C3*R1*R3*R4;
			b3tm = -b3t;
			b3tl = C1*C2*C3*R1*R2*R4;
			a0   = 1;
			a1d  = C1*R1 + C1*R3 + C2*R3 + C2*R4 + C3*R4;
			a1m  = C3*R3;
			a1l  = C1*R2 + C2*R2;
			a2m  = C1*C3*R1*R3 - C2*C3*R3*R4 + C1*C3*R3*R3 + C2*C3*R3*R3;
			a2lm = C1*C3*R2*R3 + C2*C3*R2*R3;
			a2m2 = -(C1*C3*R3*R3 + C2*C3*R3*R3);
			a2l  = C1*C2*R2*R4 + C1*C2*R1*R2 + C1*C3*R2*R4 + C2*C3*R2*R4;
			a2d  = C1*C2*R1*R4 + C1*C3*R1*R4 + C1*C2*R3*R4
						 + C1*C2*R1*R3 + C1*C3*R3*R4 + C2*C3*R3*R4;
			a3lm = C1*C2*C3*R1*R2*R3 + C1*C2*C3*R2*R3*R4;
			a3m2 = -(C1*C2*C3*R1*R3*R3 + C1*C2*C3*R3*R3*R4);
			a3m  = C1*C2*C3*R3*R3*R4 + C1*C2*C3*R1*R3*R3 - C1*C2*C3*R1*R3*R4;
			a3l  = C1*C2*C3*R1*R2*R4;
			a3d  = C1*C2*C3*R1*R3*R4;

			filter.reset();
		}

		inline void updateCoefs (double b, double m, double t) {
			
			if(mToneStackModel == kToneStackVox) {
				m = 1.;
			}
			
			struct {
				double a1, a2, a3;
				double b1, b2, b3;
			} acoef; // analog coefficients

			// digital coefficients
			double dcoef_a[Order + 1];
			double dcoef_b[Order + 1];

			m = (m - 1) * 3.5;
			m = pow (10, m);
		
			acoef.a1 = a1d + m*a1m + b*a1l;
			acoef.a2 = m*a2m + b*m*a2lm + m*m*a2m2 + b*a2l + a2d;
			acoef.a3 = b*m*a3lm + m*m*a3m2 + m*a3m + b*a3l + a3d;

			double c2 = c*c, c3 = c2*c;
				
			acoef.a1 *= c, acoef.a2 *= c2, acoef.a3 *= c3;

			dcoef_a[0] = -1 - acoef.a1 - acoef.a2 - acoef.a3; // sets scale
			dcoef_a[1] = -3 - acoef.a1 + acoef.a2 + 3*acoef.a3;
			dcoef_a[2] = -3 + acoef.a1 + acoef.a2 - 3*acoef.a3;
			dcoef_a[3] = -1 + acoef.a1 - acoef.a2 + acoef.a3;

			acoef.b1 = t*b1t + m*b1m + b*b1l + b1d;
			acoef.b2 = t*b2t + m*m*b2m2 + m*b2m + b*b2l + b*m*b2lm + b2d;
			acoef.b3 = b*m*b3lm + m*m*b3m2 + m*b3m + t*b3t + t*m*b3tm + t*b*b3tl;
				
			acoef.b1 *= c, acoef.b2 *= c2, acoef.b3 *= c3;

			dcoef_b[0] = - acoef.b1 - acoef.b2 - acoef.b3;
			dcoef_b[1] = - acoef.b1 + acoef.b2 + 3*acoef.b3;
			dcoef_b[2] = acoef.b1 + acoef.b2 - 3*acoef.b3;
			dcoef_b[3] = acoef.b1 - acoef.b2 + acoef.b3;

			double a0i = 1. / dcoef_a[0];
			
			for (int i=1; i<=3; ++i)
				filter.a[i] = dcoef_a[i] * a0i;
				
			for (int i=0; i<=3; ++i)
				filter.b[i] = dcoef_b[i] * a0i;
		}

		/* actually do the DFII filtering, one sample at a time */
		inline double process (double x) {
			return filter.process (x);
		}
};

} /* namespace DSP */

#endif /* DSP_TONESTACK_H */
