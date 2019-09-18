/**
 * TDFII.h
 * @copyright (C)2015 HoRNet Plugins
 *
 * Implements the direct form II transform for the tone stac filters
 */


#ifndef DSP_TDFII_H
#define DSP_TDFII_H

namespace DSP {

/* N is the highest power of s in the transfer function */
template <int N>
class TDFII
{
	public:
		double a[N+1];
		double b[N+1];
		double h[N+1];
	
		void reset() 
			{
				for (int i = 0; i <= N; ++i)
					h[i] = 0;   // zero state
			}

		void init (double fs)
			{
				reset();
				clear();
			}

		void clear() 
			{
				for (int i=0; i<= N; i++) 
					a[i] = b[i] = 0;
				b[0] = 1;
			}

		/* per-band recursion:
		 * 	y = 2 * (a * (x - x[-2]) + c * y[-1] - b * y[-2]) 
		 */
		inline double process (double s)
			{
				double y = h[0] + b[0]*s;

				for (int i=1; i<N; ++i) 
						h[i-1] = h[i] + b[i]*s - a[i]*y;

				h[N-1] = b[N]*s - a[N]*y;

				return (double) y;
			}
};

} /* namespace DSP */

#endif /* DSP_TDFII_H */
