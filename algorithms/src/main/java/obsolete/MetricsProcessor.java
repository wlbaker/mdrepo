package obsolete;

import idea.conf.DeviceCapabilities;
import idea.intf.AbstractStreamProducer;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.PersistentItem;
import idea.schema.rp.RpDevice;

import java.io.FileWriter;
import java.io.IOException;
import java.text.DecimalFormat;
import java.util.Date;
import java.util.Vector;

import lombok.extern.slf4j.Slf4j;
import idea.analysis.EntropyFilter;
import idea.analysis.MultiscaleEntropyProcessor;
import idea.analysis.event.BeatBlock;
import idea.analysis.event.MetricsBlock;
import idea.buffer.SignalBuffer;

@Slf4j
public class MetricsProcessor extends AbstractStreamProducer implements
		StreamConsumer {

	/************************************************************************
	 * This class provides the methods needed to perform all heart rate 
	 * variability and complexity (HRV/HRC) metric calculations and  
	 * analysis on the R-R intervals (RRIs) detected by a QRS detection 
	 * algorithm, such as the Automated Electrocardiogram Selection of Peaks 
	 * (AESOP) algorithm.
	 * 
	 * @param sampEn	Sample Entropy  
	 * @param qse		Quadratic Sample Entropy
	 * @param mse		Multi-Scale Entropy  
	 * 
	 * @param sd1		Short-term variability of RRIs
	 * @param sd2		Long-term variability of RRIs
	 * @param sdRatio	Ratio of short-term to long-term RRI variability
	 * 
	 * @param statAv	Degree of Nonstationarity
	 * 
	 * @param alpha		Fractal Exponent for Uniformly Distributed N
	 * @param alpha1	Fractal Exponent for 4 <= N <= 16
	 * @param alpha1	Fractal Exponent for 16 <= N <= 64
	 * 
	 * @param sod		Similarity of Distributions
	 * 
	 * @param sdrr		Standard deviation of RRIs  
	 * @param sdsd		Standard deviation of successive RRI differences
	 * 
	 * @param hr		Estimated heart rate
	 * 
	 *************************************************************************/

	// Variables for calculating entropies
	private int sampleRate;
	private int totSamples;
	private SignalBuffer<Integer> rris;
	private int mstime;
	private double tolerance = 0.2;
	private int templateLength = 2;
	private DecimalFormat df3 = new DecimalFormat("0.000");
	private MultiscaleEntropyProcessor msEntropy;
	private Number std = 0;
	private Number sampEn = 0;
	private Number quadEn = 0;

	// Variables for entropy calculations
	private Integer step = new Integer(4);
	private double mseSingleton;


	// Variables for Poincare plot geometry calculations
	private SignalBuffer<Integer> rriDiffs;
	private int prevMSInterval = 0;

	private double SDRR;
	private double SDSD;

	private double SD1;
	private double SD2;
	private double SDRatio;


	// Variables for StatAv calculations
	private SignalBuffer<Integer> rris2;
	private SignalBuffer<Double> rriEpochs;
	private double SDAV;
	private double StatAv;

	// Variables for Detrended Fluctuation calculations	
	private double alpha;
	private double alpha1, alpha2;

	// Variables for Autocorrelation calculations
	private final static int TAU = 4; // window shift or time delay
	private SignalBuffer<Integer> rris3;
	private RRIHistogram prevRRIHistogram, histogram;
	private int minRRInterval;
	private int maxRRInterval;
	private double SOD;

	// Variables for Estimated Heart Rate calculations
	private static double estimatedHR;


	public MetricsProcessor() {

		// Initialize initial time in seconds and milliseconds
		mstime = 0;

		// Initialize metric values
		sampEn = 0;
		quadEn = 0;
		mseSingleton = 0;
		SD1 = 0;
		SD2 = 0;
		SDRatio = 0;
		StatAv = 0;
		alpha = 0;
		alpha1 = 0;
		alpha2 = 0;
		SOD = 0;
		SDRR = 0;
		SDSD = 0;
		estimatedHR = 0;

		// Initialize variables for HRV/HRC analysis calculations
		totSamples = 0;
		rris = new SignalBuffer<Integer>(200, true);
		rriDiffs = new SignalBuffer<Integer>(199, true);
		rris2 = new SignalBuffer<Integer>(800, true);
		rriEpochs = new SignalBuffer<Double>(40, true);
		msEntropy = new MultiscaleEntropyProcessor();
		rris3 = new SignalBuffer<Integer>(800 + TAU, true);

	}


	private static double getSampleStandardDeviation(SignalBuffer<? extends Number> signal) {

		double mean = 0.0;
		Number standardDev = null;
		double variance = 0;

		int tot = signal.getSampleCount();
		for (int i = 0; i < tot; ++i) {
			mean += signal.get(i).doubleValue();
		}
		mean /= tot;

		for (int i = 0; i < tot; ++i) {
			variance += Math.pow(signal.get(i).doubleValue() - mean, 2.0);
		}
		variance /= (tot - 1);

		standardDev = Math.sqrt(variance);

		return standardDev.doubleValue(); 

	}


	/* Global variables. */
	private String pname;			/* this program's name (for use in error messages) */
	private static double[] seq;	/* input data buffer; allocated and filled by input() */
	private static long[] rs;		/* box size array; allocated and filled by rscale() */
	private static double[] mse;	/* fluctuation array; allocated by setup(), filled by dfa() */
	private static int nfit = 2;	/* order of the regression fit, plus 1 */
	private static int nr;			/* number of box sizes */


	/* Read input data, allocating and filling seq[], integrating if iflag != 0.
	   Following the convention used for other arrays in this program, seq[0] is
	   unused, and the first point is stored in seq[1].  The return value is the
	   number of points read.

	   This function allows the input buffer to grow as large as necessary, up to
	   the available memory (assuming that a long int is large enough to address
	   any memory location).  Note that the integration is done using double
	   precision arithmetic to avoid complete loss of precision when the integrated
	   data reach large amplitudes.  */
	static double[] integrate(SignalBuffer<Integer> rris)
	{
		double y = 0;
		int length = rris.getBufferSize();
		double[] seq = new double[length]; 

		for (int i = 0; i < length; i++) {
			y += rris.get(i).doubleValue();
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

		// Made the changes below for this file only
		// x = new double[(int) rs[nr]][nfit];
		x = new double[(int) rs[nr - 1]][nfit];
		// for (i = 0; i < rs[nr]; i++) {
		for (i = 0; i < rs[nr - 1]; i++) {
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


	public static void calculateAlpha1(int record, SignalBuffer<Integer> intervals, FileWriter analysisOutStream) {

		try {

			int i, sw = 0;
			long minbox = 0L, maxbox = 0L, npts, temp;

			/* Allocate and fill the input data array seq[]. */
			seq = integrate(intervals);
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
			nr = rs.length;

			/* Allocate memory for dfa() and the functions it calls. */
			setup();

			/* Measure the fluctuations of the detrended input data at each box size
			       using the DFA algorithm; fill mse[] with these results. */
			dfa(seq, npts, nfit, rs, nr, sw);

			/* Output the results. */
			// analysisOutStream.write("Record" + "\t" + record + "\n");
			// analysisOutStream.write("\n");

			/*
			for (i = 0; i < nr; i++)
				analysisOutStream.write(Math.log10((double)rs[i]) + "\t" + 
						Math.log10(mse[i])/2.0 + "\n");
			 */


			double alpha = getSampleSlopeAlpha(mse, rs);
			// analysisOutStream.write("\n");
			analysisOutStream.write(alpha + "\n");
			// analysisOutStream.write("\n");
			System.out.println("alpha:" + alpha);

		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}


	public static void calculateAlpha2(int record, SignalBuffer<Integer> intervals, FileWriter analysisOutStream) {

		try {

			int i, sw = 0;
			long minbox = 0L, maxbox = 0L, npts, temp;

			/* Allocate and fill the input data array seq[]. */
			seq = integrate(intervals);
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
			nr = rs.length;

			/* Allocate memory for dfa() and the functions it calls. */
			setup();

			/* Measure the fluctuations of the detrended input data at each box size
			       using the DFA algorithm; fill mse[] with these results. */
			dfa(seq, npts, nfit, rs, nr, sw);

			/* Output the results. */
			// analysisOutStream.write("Record" + "\t" + record + "\n");
			// analysisOutStream.write("\n");

			/*
			for (i = 0; i < nr; i++)
				analysisOutStream.write(Math.log10((double)rs[i]) + "\t" + 
						Math.log10(mse[i])/2.0 + "\n");
			 */


			double alpha = getSampleSlopeAlpha(mse, rs);
			// analysisOutStream.write("\n");
			analysisOutStream.write(alpha + "\n");
			// analysisOutStream.write("\n");
			System.out.println("alpha:" + alpha);

		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}


	private double getSampleMean(SignalBuffer<Integer> buffer, double maxValue) {

		double mean = 0.0;
		Number standardDev = null;
		double variance = 0;

		double numValid = 0;

		for (int i = 0; i < buffer.getSampleCount(); ++i) {

			if (buffer.get(i).doubleValue() == -999) continue;
			if (buffer.get(i).doubleValue() > maxValue) continue;
			numValid++;
			mean += buffer.get(i).doubleValue();

		}

		if (numValid == 0) mean = -999;
		else mean /= numValid;

		numValid = 0;

		for (int i = 0; i < buffer.getSampleCount(); ++i) {

			if (buffer.get(i).doubleValue() == -999) continue;
			if (buffer.get(i).doubleValue() > maxValue) continue;
			numValid++;
			variance += Math.pow(buffer.get(i).doubleValue() - mean, 2.0);

		}

		if (numValid == 0) variance = -999;
		else variance /= (numValid - 1);

		if (numValid == 0) standardDev = -999;
		else standardDev = Math.sqrt(variance);

		// return standardDev.doubleValue(); 
		return mean;

	}


	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {

		if (item instanceof BeatBlock) {

			// Initialize metric values
			sampEn = 0;
			quadEn = 0;
			mseSingleton = 0;
			SD1 = 0;
			SD2 = 0;
			SDRatio = 0;
			StatAv = 0;
			alpha = 0;
			alpha1 = 0;
			alpha2 = 0;
			SOD = 0;
			SDRR = 0;
			SDSD = 0;
			estimatedHR = 0;

			BeatBlock block = (BeatBlock)item;
			int msInterval = block.getMs_interval();
			mstime += msInterval;

			// Add successive RRI difference
			if (totSamples > 0) {
				rriDiffs.addData(msInterval - prevMSInterval);
			}

			prevMSInterval = msInterval;

			rris.addData(msInterval);
			rris2.addData(msInterval);

			totSamples++;

			log.error("FIXME: this use of msEntropy.process() was replaced by mse processor");
			// msEntropy.setRRI(rris);

			// Calculate estimated heart rate
			estimatedHR = 60.0/getSampleMean(rris, Double.MAX_VALUE)*1000;


			// Calculate entropies
			if (totSamples > 200) {

				std = getSampleStandardDeviation(rris);

				// Calculate SampEn
				if (tolerance < 0) {
					sampEn = EntropyFilter.SaEn(rris, -tolerance, templateLength);

				} else {
					sampEn = EntropyFilter.SaEn(rris, 
							std.doubleValue() * tolerance, templateLength);

					if (sampEn.doubleValue() > 10.0) {
						sampEn = 10.0; // caused when tolerance too small
					}
				}

				// 	Calculate QSE
				if (std != null && std.doubleValue() > 0) {
					quadEn = sampEn.doubleValue() + Math.log(0.4) + Math.log(std.doubleValue());
				}

				// Calculate MSE
				log.error("FIXME: msEntropy.process() was replaced by mse processor");
//				if (totSamples >= 200 && (totSamples % step) == 0) {
//					mseSingleton = msEntropy.process(step);
//				}

				// Calculate SDRR
				SDRR = getSampleStandardDeviation(rris);

				// Calculate SDSD
				SDSD = getSampleStandardDeviation(rriDiffs);

				// Calculate Poincare variability ratio
				SD1 = Math.sqrt( 0.5 * SDSD*SDSD );
				SD2 = Math.sqrt( 2 * SDRR*SDRR - 0.5 * SDSD*SDSD );
				SDRatio = SD1 / SD2;

			}

			// Calculate StatAv
			if (totSamples > 800) {

				double mean = 0.0;

				int numEpochs = rriEpochs.getBufferSize();
				int epochLength = rris2.getSampleCount()/numEpochs;


				SDRR = getSampleStandardDeviation(rris2);

				for (int i = 0; i < numEpochs; ++i) {
					mean = 0.0;
					for (int j = epochLength*i; j < epochLength*(i+1); ++j) {
						mean += rris2.get(j).doubleValue(); // rwaves[i];
					}
					mean /= epochLength;

					rriEpochs.addData(mean);
				}

				SDAV = getSampleStandardDeviation(rriEpochs);

				StatAv = 1.0 * SDAV / SDRR;

			}

			// Calculate detrended fluctuation scaling exponent
			if (totSamples > 800) {

				int i, sw = 0;
				long minbox = 0L, maxbox = 0L, npts, temp;

				/* Allocate and fill the input data array seq[]. */
				seq = integrate(rris2);
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

				/* Output the results. */
				/*
					for (i = 0; i < nr; i++)
						analysisOutStream.write(Math.log10((double)rs[i]) + "\t" + 
								Math.log10(mse[i])/2.0 + "\n");
				 */

				alpha = getSampleSlopeAlpha(mse, rs);
				// analysisOutStream.write("\n");
				System.out.println("alpha:" + alpha);

				// Do not calculate alpha1 and alpha2 for the time being
				alpha1 = alpha2 = alpha;

			}

			// Calculate autocorrelation coefficient
			if (totSamples >= 800 + TAU) {

				// Form histogram of previous window
				minRRInterval = rris.get(0);
				maxRRInterval = rris.get(0);

				for (int i = 0; i < rris.getSampleCount() - TAU; i++) {
					minRRInterval = Math.min(minRRInterval, rris.get(i).intValue());
					maxRRInterval = Math.max(maxRRInterval, rris.get(i).intValue());
				}

				// System.out.println("Min R-R: " + minRRInterval);
				// System.out.println("Max R-R: " + maxRRInterval);

				prevRRIHistogram = new RRIHistogram(maxRRInterval, 0, maxRRInterval + 1);
				// RRIHistogram(maxRRInterval, minRRInterval, maxRRInterval);

				for (int i = 0; i < rris.getSampleCount() - TAU; i++) {
					prevRRIHistogram.add(rris.get(i).doubleValue());
				}

				// Form histogram of next window
				minRRInterval = rris.get(TAU);
				maxRRInterval = rris.get(TAU);

				for (int i = TAU; i < rris.getSampleCount(); i++) {
					minRRInterval = Math.min(minRRInterval, rris.get(i).intValue());
					maxRRInterval = Math.max(maxRRInterval, rris.get(i).intValue());
				}

				// System.out.println("Min R-R: " + minRRInterval);
				// System.out.println("Max R-R: " + maxRRInterval);

				histogram = new RRIHistogram(maxRRInterval, 0, maxRRInterval + 1);
				// RRIHistogram(maxRRInterval, minRRInterval, maxRRInterval);

				for (int i = TAU; i < rris.getSampleCount(); i++) {
					histogram.add(rris.get(i).doubleValue());
				}

				// System.out.println("Sample Count: " + rris.getSampleCount());
				// System.out.println("NumBins: " + fNumBins);
				// System.out.println("Total: " + getTotal());

				// Calculate autocorrelation of R-R distributions
				SOD = 0;
				for (int i = 0; i < Math.min(prevRRIHistogram.getFNumBins(), histogram.getFNumBins()); i++) {
					SOD += 1.0 * 
					prevRRIHistogram.getBinValue(i)/prevRRIHistogram.getTotal() * 
					histogram.getBinValue(i)/histogram.getTotal();
				}

			}


			MetricsBlock metricsBlock = new MetricsBlock( );

			metricsBlock.setTm(new Date(mstime));

			if (sampEn.doubleValue() == 0) { metricsBlock.setSampEn(0); } 
			else { metricsBlock.setSampEn(sampEn.doubleValue()); }
			if (quadEn.doubleValue() == 0) { metricsBlock.setQse(0); } 
			else { metricsBlock.setQse(quadEn.doubleValue()); }
			if (mseSingleton == 0) { metricsBlock.setMse(0); } 
			else { metricsBlock.setMse(mseSingleton); }

			if (SD1 == 0) { metricsBlock.setSd1(0); } 
			else { metricsBlock.setSd1(SD1); }
			if (SD2 == 0) { metricsBlock.setSd2(0); } 
			else { metricsBlock.setSd2(SD2); }
			if (SDRatio == 0) { metricsBlock.setSdRatio(0); } 
			else { metricsBlock.setSdRatio(SDRatio); }

			if (StatAv == 0) { metricsBlock.setStatAv(0); } 
			else { metricsBlock.setStatAv(StatAv); }

			if (alpha == 0) { metricsBlock.setAlpha(0); } 
			else { metricsBlock.setAlpha(alpha); }
			if (alpha1 == 0) { metricsBlock.setAlpha1(0); } 
			else { metricsBlock.setAlpha1(alpha1); }
			if (alpha2 == 0) { metricsBlock.setAlpha2(0); } 
			else { metricsBlock.setAlpha2(alpha2); }

			if (SOD == 0) { metricsBlock.setSod(0); } 
			else { metricsBlock.setSod(SOD); }

			if (SDRR == 0) { metricsBlock.setSdrr(0); } 
			else { metricsBlock.setSdrr(SDRR); }
			if (SDSD == 0) { metricsBlock.setSdsd(0); } 
			else { metricsBlock.setSdsd(SDSD); }

			if (estimatedHR == 0) { metricsBlock.setHr(0); } 
			else { metricsBlock.setHr(estimatedHR); }

			// Fire all calculated HRV/HRC metric calculations
			fireStreamEvent(0,this,StreamID.MEASUREMENT, metricsBlock);

		}

	}


	@Override
	public RpDevice getStaticCapabilities() {
		DeviceCapabilities caps = new DeviceCapabilities( this.getClass() );
		caps.addStream(StreamID.MEASUREMENT, MetricsBlock.class);
		return caps;
	}

}



class RRIHistogram {

	private Vector<Integer> binIndices;
	private Vector<Integer> fBins;

	private int fNumBins;
	private int fUnderflows;
	private int fOverflows;

	private double fLo;
	private double fHi;
	private double fRange;

	/** The constructor will create an array of a given
	 * number of bins. The range of the histogram given
	 * by the upper and lower limit values.
	 **/
	public RRIHistogram (int numBins, double lo, double hi) {
		// Check for bad range values.
		// Could throw an exception but will just
		// use default values;
		if (hi < lo) {
			lo = 0.0;
			hi = 1.0;
		}
		if (numBins <= 0) numBins = 1;
		fNumBins = numBins;
		binIndices = new Vector<Integer>(fNumBins);
		fBins = new Vector<Integer>(fNumBins);

		for (int i = 0; i < fNumBins; i++) {
			binIndices.add(Integer.valueOf(i));
			fBins.add(Integer.valueOf(0)); 
		}

		fLo = lo;
		fHi = hi;
		fRange = fHi - fLo;
	}


	/** Get the low end of the range. **/
	public double getLo ()
	{ return fLo; }


	/** Get the high end of the range.**/
	public double getHi ()
	{ return fHi; }


	/** Get the number of entries in the largest bin. **/
	public int getMax () {
		int max = 0;
		for (int i=0; i < fNumBins;i++)
			if (max < fBins.get(i).intValue()) max = fBins.get(i).intValue();
		return max;
	}


	/**
	 * This method returns a reference to the binIndices.
	 * Note that this means the values of the histogram
	 * could be altered by the caller object.
	 **/
	public Vector<Integer> getBinIndices() {
		return binIndices;
	}


	/**
	 * This method returns a reference to the fBins.
	 * Note that this means the values of the histogram
	 * could be altered by the caller object.
	 **/
	public Vector<Integer> getBins() {
		return fBins;
	}

	/** Get the number of entries in the smallest bin.**/
	public int getMin () {
		int min = getMax ();
		for (int i=0; i < fNumBins; i++)
			if (min > fBins.get(i).intValue()) min = fBins.get(i).intValue();
		return min;
	}


	/** Get the total number of entries not counting
	 * overflows and underflows.
	 **/
	public int getTotal () {
		int total = 0;
		for (int i=0; i < fNumBins; i++)
			total += fBins.get(i).intValue();
		return total;
	}

	/** Get the total number of bins
	 **/
	public int getFNumBins () {
		return fNumBins;
	}

	/**
	 * Add an entry to a bin.
	 * @param x double value added if it is in the range:
	 *   lo <= x < hi
	 **/
	public void add (double x) {
		if (x >= fHi) {
			for (int i = fNumBins; i <= x; i++) {
				binIndices.add(Integer.valueOf(i));
				fBins.add(Integer.valueOf(0)); 
			}
			fHi = x + 1;
			fRange = fHi - fLo;
			fNumBins = (int) x;
		}

		if (x >= fHi) fOverflows++;
		else if (x < fLo) fUnderflows++;
		else {
			double val = x - fLo;

			// Casting to int will round off to lower
			// integer value.
			int bin =  (int) (fNumBins *  (val/fRange) );

			// Increment the corresponding bin.
			fBins.set(bin, fBins.get(bin).intValue() + 1);
		}
	}


	/** Clear the histogram bins and the over and under flows.**/
	public void clear () {
		fBins = new Vector<Integer>(3);
		fOverflows = 0;
		fUnderflows= 0;
	}


	/**
	 * Provide access to the value in the bin element
	 * specified by bin.
	 * Return the underflows if bin value negative,
	 * Return the overflows if bin value more than
	 * the number of bins.
	 **/
	public int getBinIndex (int bin) {
		if (bin < 0)
			return 0;
		else if (bin >= fNumBins)
			return fNumBins;
		else
			return binIndices.get(bin).intValue();
	}


	/**
	 * Provide access to the value in the bin element
	 * specified by bin.
	 * Return the underflows if bin value negative,
	 * Return the overflows if bin value more than
	 * the number of bins.
	 **/
	public int getBinValue (int bin) {
		if (bin < 0)
			return fUnderflows;
		else if (bin >= fNumBins)
			return fOverflows;
		else
			return fBins.get(bin).intValue();
	}


	/**
	 * Get the average and standard deviation of the
	 * distribution of entries.
	 * @return double array
	 **/
	public double [] getStats () {
		int total = 0;

		double wt_total = 0;
		double wt_total2 = 0;
		double [] stat = new double[2];
		double bin_width = fRange/fNumBins;

		for (int i=0; i < fNumBins; i++) {
			total += fBins.get(i).intValue();

			double bin_mid =  (i - 0.5) * bin_width + fLo;
			wt_total  += fBins.get(i).intValue() * bin_mid;
			wt_total2 += fBins.get(i).intValue() * bin_mid * bin_mid;
		}

		if (total > 0) {
			stat[0] = wt_total / total;
			double av2 = wt_total2 / total;
			stat[1] = Math.sqrt (av2 - stat[0] * stat[0]);
		} else {
			stat[0] = 0.0;
			stat[1] = -1.0;
		}

		return stat;
	}// getStats()


	/**
	 * Create the histogram from a user derived array along with the
	 * under and overflow values.
	 * The low and high range values that the histogram
	 * corresponds to must be in passed as well.
	 *
	 * @param userBins array of int values.
	 * @param under number of underflows.
	 * @param over number of overflows.
	 * @param lo value of the lower range limit.
	 * @param hi value of the upper range limit.
	 **/
	public void pack (int [] user_bins,
			int under, int over,
			double lo, double hi) {
		fNumBins = user_bins.length;
		fBins = new Vector<Integer>(fNumBins);
		for (int i = 0; i < fNumBins; i++) {
			fBins.add(user_bins[i]);
		}

		fLo = lo;
		fHi = hi;
		fRange = fHi-fLo;
		fUnderflows = under;
		fOverflows = over;
	}// pack()

}
