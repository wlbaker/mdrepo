package idea.analysis;

import idea.conf.DeviceCapabilities;
import idea.intf.AbstractStreamProducer;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.Alarm;
import idea.model.PersistentItem;
import idea.analysis.event.BeatBlock;
import idea.analysis.event.DetrendedFluctuationBlock;
import idea.analysis.event.RWaveEvent;
import idea.buffer.SignalBuffer;

public class DetrendedFluctuationProcessor extends AbstractStreamProducer implements
		StreamConsumer {

	/************************************************************************
	 * This class provides the methods needed to perform detrended 
	 * fluctuation analysis (DFA) on the R-R intervals (RRIs) detected by 
	 * a QRS detection algorithm, such as the Automated Electrocardiogram 
	 * Selection of Peaks (AESOP) algorithm. Specifically, the DFA calculates 
	 * the average fluctuation F(n) for box size n. Furthermore, it involves 
	 * the estimation of a short-term fractal scaling exponent alpha1 and a 
	 * long-term fractal scaling exponent alpha2 by making a least squares fit 
	 * of log F(n) versus log n for 4 <= n <= 16 and for 16 <= n <= 64, 
	 * respectively.
	 * 
	 * @param 
	 * 
	 *************************************************************************/

	private final static int NUM_SAMPLES_FOR_ANALYSIS = 800;
	// private final static int NUM_SAMPLES_FOR_ANALYSIS = 106083;

	private static int verbose = 0;

	// Variables for calculations
	private int sampleRate;
	private int totSamples;
	private SignalBuffer<Integer> rris;
	private int mstime;

	/* Global variables. */
	private String pname;			/* this program's name (for use in error messages) */
	private static double[] seq;	/* input data buffer; allocated and filled by input() */
	private static long[] rs;		/* box size array; allocated and filled by rscale() */
	private static double[] mse;	/* fluctuation array; allocated by setup(), filled by dfa() */
	private static int nfit = 2;	/* order of the regression fit, plus 1 */
	private static int nr;			/* number of box sizes */

	public DetrendedFluctuationProcessor(int count) {
		totSamples = 0;
		rris = new SignalBuffer<Integer>(count, true);
		mstime = 0;
	}

	private double getSampleMeanVariance(SignalBuffer<? extends Number> signal) {

		double mean = 0.0;
		Number standardDev = null;
		double variance = 0;

		int tot = signal.getSampleCount();
		for (int i = 0; i < tot; ++i) {
			mean += signal.get(i).doubleValue(); // rwaves[i];
		}
		mean /= tot;

		for (int i = 0; i < tot; ++i) {
			variance += Math.pow(signal.get(i).doubleValue() - mean, 2.0);
		}
		variance /= (tot - 1);

		standardDev = Math.sqrt(variance);

		return standardDev.doubleValue(); 

	}

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {

		if (item instanceof RWaveEvent) {

			BeatBlock block = (BeatBlock)item;
			int interval = block.getMs_interval();
			mstime += interval;

			rris.addData(interval);

			totSamples++;

			if (totSamples < NUM_SAMPLES_FOR_ANALYSIS) {
				if (verbose > 0) {
					System.out.println("   entropy progress: "
							+ rris.getSampleCount() + " out of "
							+ rris.getBufferSize());
				}
				Alarm ai = new Alarm("sample",Alarm.INFO, 0, "Waiting: "
						+ rris.getSampleCount() + " out of "
						+ rris.getBufferSize(), true);
				fireAlarmEvent(this, ai);
				return;
			}


			/********************
			 * Calculate alpha
			 ********************/


			DetrendedFluctuationBlock dfaBlock = calculateAlpha( rris );

			fireStreamEvent(0,this,StreamID.MEASUREMENT, dfaBlock);

			// System.out.println("alpha=" + alpha + " alpha1=" + alpha1 + " alpha2=" + alpha2);
		}

	}


	/* Read input data, allocating and filling seq[], integrating if iflag != 0.
	   Following the convention used for other arrays in this program, seq[0] is
	   unused, and the first point is stored in seq[1].  The return value is the
	   number of points read.

	   This function allows the input buffer to grow as large as necessary, up to
	   the available memory (assuming that a long int is large enough to address
	   any memory location).  Note that the integration is done using double
	   precision arithmetic to avoid complete loss of precision when the integrated
	   data reach large amplitudes.  */
	static double[] integrate(SignalBuffer<Integer> intervals)
	{
		double y = 0;
		int length = intervals.getSampleCount();
		double[] seq = new double[length]; 
		
		for (int i = 0; i < length; i++) {
			y += intervals.get(i).doubleValue();
			seq[i] = y;
		}

		return (seq);
	}

	private static int rslen;	/* length of rs[] */

	/* rscale() allocates and fills rs[], the array of box sizes used by dfa()
	   below.  The box sizes range from (exactly) minbox to (approximately) maxbox,
	   and are arranged in a geometric series such that the ratio between
	   consecutive box sizes is (approximately) boxratio.  The return value is
	   the number of box sizes in rs[].
	 */
	static int rscale(long minbox, long maxbox, double boxratio)
	{
		int ir, n;
		long rw;

		/* Determine how many scales are needed. */
		rslen = (int) ( (Math.log10(maxbox /(double)minbox)) / (Math.log10(boxratio)) + 1.5 );
		/* Thanks to Peter Domitrovich for pointing out that a previous version
	       of the above calculation undercounted the number of scales in some
	       situations. */
		rs = new long[rslen];
		for (ir = 1, n = 1, rs[0] = minbox; n < rslen && rs[n-1] < maxbox; ir++)
			if ((rw = (long) (minbox * Math.pow(boxratio, ir) + 0.5)) > rs[n-1])
				rs[n++] = rw;
		// if (rs[--n] > maxbox) --n;
		if (rs[--n] >= maxbox) --n;
		return (n+1);
	}

	private static double[][] x;	/* matrix of abscissas and their powers, for polyfit(). */

	/* Detrended fluctuation analysis
	    seq:	input data array
	    npts:	number of input points
	    nfit:	order of detrending (2: linear, 3: quadratic, etc.)
	    rs:		array of box sizes (uniformly distributed on log scale)
	    nr:		number of entries in rs[] and mse[]
	    sw:		mode (0: non-overlapping windows, 1: sliding window)
	   This function returns the mean squared fluctuations in mse[].
	 */
	static void dfa(double[] seq, long npts, int nfit, long[] rs, int nr, int sw)
	{
		long i, boxsize, inc, j;
		double stat;

		for (i = 0; i < nr; i++) {
			boxsize = rs[(int)i];
			if (sw != 0) { inc = 1; stat = (int)(npts - boxsize + 1) * boxsize; }
			else { inc = boxsize; stat = (int)(npts / boxsize) * boxsize; }
			for (mse[(int)i] = 0.0, j = 0; j <= npts - boxsize; j += inc) {
				double[] y = new double[(int)boxsize];
				for (int k = 0; k < boxsize; k++) y[k] = seq[(int)j + k];
				mse[(int)i] += polyfit(x, y, boxsize, nfit);
			}
			mse[(int)i] /= stat;
		}
	}

	/* workspace for polyfit() */
	private static double[] beta;
	private static double[][] covar, covar0;
	private static int[] indxc, indxr, ipiv;

	/* This function allocates workspace for dfa() and polyfit(), and sets
	   x[i][j] = i**(j-1), in preparation for polyfit(). */
	static void setup()
	{
		long i;
		int j, k;

		pboxsize = 0L;

		beta = new double[nfit];
		covar = new double[nfit][nfit];
		covar0 = new double[nfit][nfit];
		indxc = new int[nfit];
		indxr = new int[nfit];
		ipiv = new int[nfit];
		mse = new double[nr];
		x = new double[(int) rs[nr]][nfit];
		for (i = 0; i < rs[nr]; i++) {
			x[(int)i][0] = 1.0;
			x[(int)i][1] = i;
			for (j = 2; j < nfit; j++)
				x[(int)i][j] = x[(int)i][j-1] * i;
		}
	}

	private static long pboxsize;

	/* polyfit() is based on lfit() and gaussj() from Numerical Recipes in C
	   (Press, Teukolsky, Vetterling, and Flannery; Cambridge U. Press, 1992).  It
	   fits a polynomial of degree (nfit-1) to a set of boxsize points given by
	   x[1...boxsize][2] and y[1...boxsize].  The return value is the sum of the
	   squared errors (chisq) between the (x,y) pairs and the fitted polynomial.
	 */
	static double polyfit( double[][] x, double[] y, long boxsize, int nfit )
	{
		int icol = 0, irow = 0, j, k;
		double big, chisq, pivinv, temp;
		long i;

		/* This block sets up the covariance matrix.  Provided that boxsize
	       never decreases (which is true in this case), covar0 can be calculated
	       incrementally from the previous value. */
		if (pboxsize != boxsize) {	/* this will be false most of the time */
			if (pboxsize > boxsize)	/* this should never happen */
				pboxsize = 0L;
			if (pboxsize == 0L)	/* this should be true the first time only */
				for (j = 0; j < nfit; j++)
					for (k = 0; k < nfit; k++)
						covar0[j][k] = 0.0;
			for (i = pboxsize+1-1; i < boxsize; i++)
				for (j = 0; j < nfit; j++)
					for (k = 0, temp = x[(int)i][j]; k <= j; k++)
						covar0[j][k] += temp * x[(int)i][k];
			for (j = 1; j < nfit; j++)
				for (k = 0; k < j; k++)
					covar0[k][j] = covar0[j][k];
			pboxsize = boxsize;
		}
		for (j = 0; j < nfit; j++) {
			beta[j] = ipiv[j] = 0;
			for (k = 0; k < nfit; k++)
				covar[j][k] = covar0[j][k];
		}
		for (i = 0; i < boxsize; i++) {
			beta[0] += (temp = y[(int)i]);
			beta[1] += temp * i;
		}
		if (nfit > 2)
			for (i = 0; i < boxsize; i++)
				for (j = 2, temp = y[(int)i]; j < nfit; j++)
					beta[j] += temp * x[(int)i][j];
		for (i = 0; i < nfit; i++) {
			big = 0.0;
			for (j = 0; j < nfit; j++)
				if (ipiv[j] != 1)
					for (k = 0; k < nfit; k++) {
						if (ipiv[k] == 0) {
							if ((temp = covar[j][k]) >= big ||
									(temp = -temp) >= big) {
								big = temp;
								irow = j;
								icol = k;
							}
						}
						else if (ipiv[k] > 1)
							System.err.println("singular matrix");
					}
			++(ipiv[icol]);
			if (irow != icol) {
				for (j = 0; j < nfit; j++) {
					temp = covar[irow][j]; covar[irow][j] = covar[icol][j]; covar[icol][j] = temp;
				}
				temp = beta[irow]; beta[irow] = beta[icol]; beta[icol] = temp;
			}
			indxr[(int)i] = irow;
			indxc[(int)i] = icol;
			if (covar[icol][icol] == 0.0) System.err.println("singular matrix");
			pivinv = 1.0 / covar[icol][icol];
			covar[icol][icol] = 1.0;
			for (j = 0; j < nfit; j++) covar[icol][j] *= pivinv;
			beta[icol] *= pivinv;
			for (j = 0; j < nfit; j++)
				if (j != icol) {
					temp = covar[j][icol];
					covar[j][icol] = 0.0;
					for (k = 0; k < nfit; k++) covar[j][k] -= covar[icol][k]*temp;
					beta[j] -= beta[icol] * temp;
				}
		}
		chisq = 0.0;
		if (nfit <= 2)
			for (i = 0; i < boxsize; i++) {
				temp = beta[0] + beta[1] * i - y[(int)i];
				chisq += temp * temp;
			}
		else
			for (i = 0; i < boxsize; i++) {
				temp = beta[0] + beta[1] * i - y[(int)i];
				for (j = 2; j < nfit; j++) temp += beta[j] * x[(int)i][j];
				chisq += temp * temp;
			}
		return (chisq);
	}


	private static double getSampleSlopeAlpha(double[] y, long[] x) {

		double sumX = 0.0;
		double sumY = 0.0;
		double sumXY = 0.0;
		double sumXX = 0.0;
		double slope = -999;

		double mean = 0.0;
		Number standardDev = null;
		double variance = 0;

		double numValid = 0;

		for (int i = 0; i < y.length; ++i) {

			if (y[i] == -999) continue;
			if (y[i] > Double.MAX_VALUE) continue;
			numValid++;
			sumX += Math.log10(x[i]); 
			sumY += Math.log10(y[i])/2.0;
			sumXY += Math.log10(x[i]) * Math.log10(y[i])/2.0; 
			sumXX += Math.log10(x[i]) * Math.log10(x[i]);

		}

		if (numValid == 0) return slope;
		else slope = (numValid * sumXY - sumX * sumY)/(numValid * sumXX - sumX * sumX);
		

		if (numValid == 0) mean = -999;
		else mean = sumY / numValid;

		numValid = 0;

		for (int i = 0; i < y.length; ++i) {

			if (y[i] == -999) continue;
			if (y[i] > Double.MAX_VALUE) continue;
			numValid++;
			variance += Math.pow(y[i] - mean, 2.0);

		}

		if (numValid == 0) variance = -999;
		else variance /= (numValid - 1);

		if (numValid == 0) standardDev = -999;
		else standardDev = Math.sqrt(variance);

		// return standardDev.doubleValue();

		// Adjust so that rate involves 3-minute factor
		return slope;

	}


	public static DetrendedFluctuationBlock calculateAlpha( SignalBuffer<Integer> rris ) {

		/********************
		 * Calculate alpha
		 ********************/

		int i, sw = 0;
		long minbox = 0L, maxbox = 0L, npts, temp;

		/* Allocate and fill the input data array seq[]. */
		seq = integrate(rris);
		npts = seq.length;

		/* Set minimum and maximum box sizes. */
		if (minbox < 2*nfit) minbox = 2*nfit;
		if (maxbox == 0 || maxbox > npts/4) maxbox = npts/4;
		if (minbox > maxbox) {
			temp = minbox; minbox = maxbox; maxbox = temp;
			if (minbox < 2*nfit) minbox = 2*nfit;
		}

		/* Allocate and fill the box size array rs[].  rscale's third argument
		       specifies that the ratio between successive box sizes is 2^(1/8). */
		nr = rscale(minbox, maxbox, Math.pow(2.0, 1.0/8.0));

		/* Allocate memory for dfa() and the functions it calls. */
		setup();

		/* Measure the fluctuations of the detrended input data at each box size
		       using the DFA algorithm; fill mse[] with these results. */
		dfa(seq, npts, nfit, rs, nr, sw);

		double alpha = getSampleSlopeAlpha(mse, rs);


		/********************
		 * Calculate alpha1
		 ********************/

		i = 0; sw = 0;
		minbox = 0L; maxbox = 0L;

		/* Allocate and fill the input data array seq[]. */
		seq = integrate(rris);
		npts = seq.length;

		/* Set minimum and maximum box sizes. */
		if (minbox < 2*nfit) minbox = 2*nfit;
		if (maxbox == 0 || maxbox > npts/4) maxbox = npts/4;
		if (minbox > maxbox) {
			temp = minbox; minbox = maxbox; maxbox = temp;
			if (minbox < 2*nfit) minbox = 2*nfit;
		}

		/* Allocate and fill the box size array rs[].  rscale's third argument
			       specifies that the ratio between successive box sizes is 2^(1/8). */
		// nr = rscale(minbox, maxbox, Math.pow(2.0, 1.0/8.0));
		// System.out.println("Number of box sizes:" + nr);
		rs = new long[]{4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
		nr = rs.length-1;

		/* Allocate memory for dfa() and the functions it calls. */
		setup();

		/* Measure the fluctuations of the detrended input data at each box size
			       using the DFA algorithm; fill mse[] with these results. */
		dfa(seq, npts, nfit, rs, nr, sw);

		double alpha1 = getSampleSlopeAlpha(mse, rs);


		/********************
		 * Calculate alpha2
		 ********************/

		i = 0; sw = 0;
		minbox = 0L; maxbox = 0L;

		/* Allocate and fill the input data array seq[]. */
		seq = integrate(rris);
		npts = seq.length;

		/* Set minimum and maximum box sizes. */
		if (minbox < 2*nfit) minbox = 2*nfit;
		if (maxbox == 0 || maxbox > npts/4) maxbox = npts/4;
		if (minbox > maxbox) {
			temp = minbox; minbox = maxbox; maxbox = temp;
			if (minbox < 2*nfit) minbox = 2*nfit;
		}

		/* Allocate and fill the box size array rs[].  rscale's third argument
			       specifies that the ratio between successive box sizes is 2^(1/8). */
		// nr = rscale(minbox, maxbox, Math.pow(2.0, 1.0/8.0));
		// System.out.println("Number of box sizes:" + nr);
		rs = new long[]{16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 
				32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 
				50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64};
		nr = rs.length-1;

		/* Allocate memory for dfa() and the functions it calls. */
		setup();

		/* Measure the fluctuations of the detrended input data at each box size
			       using the DFA algorithm; fill mse[] with these results. */
		dfa(seq, npts, nfit, rs, nr, sw);

		double alpha2 = getSampleSlopeAlpha(mse, rs);


		DetrendedFluctuationBlock dfaBlock = new DetrendedFluctuationBlock();

		dfaBlock.setAlpha(alpha);
		dfaBlock.setAlpha1(alpha1);
		dfaBlock.setAlpha2(alpha2);


		return dfaBlock;
	}


	@Override
	public DeviceCapabilities getStaticCapabilities() {
		DeviceCapabilities caps = new DeviceCapabilities(this.getClass());
		caps.addStream(StreamID.MEASUREMENT, DetrendedFluctuationBlock.class);
		return caps;

	}

}
