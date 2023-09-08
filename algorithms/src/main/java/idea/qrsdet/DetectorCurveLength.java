package idea.qrsdet;

import java.util.LinkedList;
import java.util.List;


public class DetectorCurveLength extends AbstractDetector {

	/**
	 * The major differences between this algorithm and the algorithm
	 * implemented in DetectorPanTompkinsModified.java include the following:
	 * 
	 * 1. Only a low-pass filter applied to the data 2. Buffers of
	 * past eight frequency samples used to compute curve length transform
	 * 
	 * This algorithm employs the strengths of the Modified Pan-Tompkins
	 * algorithm, including filters and the search-back technique for
	 * peaks/thresholds.
	 */


	private int MS130;
	private int MS250;
	private int MS400;
	private int BUFFER_LGTH;
	private int CLBUFFER_LGTH;

	private boolean timeStampNotInitialized;
	private long currTimeStamp;


	/* Variables unique to DetectorCurveLength.java */

	private long abspos;
	private long lastrwave;
	private int []rri;

	// private static final int BUFLN  = 16384;    /* must be a power of 2, see ltsamp() */
	private static final double EYE_CLS = 250;    /* eye-closing period is set to 0.25 sec (250 ms) */ 
	private static final double MaxQRSw = 130;    /* maximum QRS width (130ms) */                        
	private static final double NDP = 2500;        /* adjust threshold if no QRS found in 2.5 seconds */
	private static final int PWFreqDEF = 60;      /* power line (mains) frequency, in Hz (default) */
	private static final int TmDEF = 100;         /* minimum threshold value (default) */

	private static final int gain = 200;          /* minimum threshold value (default) */

	private int from = 0;

	private double lfsc;            /* length function scale constant */
	private int nsig;               /* number of input signals */
	private int LPn, LP2n;          /* filter parameters (dependent on sampling rate) */
	private int LTwindow;           /* LT window size */
	private int PWFreq = PWFreqDEF;	/* power line (mains) frequency, in Hz */
	private int sig = -1;	        /* signal number of signal to be analyzed */
	private int Tm = TmDEF;         /* minimum threshold value */

	private int sps;
	private int samplingInterval;
	private int spm;
	private int next_minute;
	private int EyeClosing; /* set eye-closing period */
	private int ExpectPeriod;	/* maximum expected RR interval */

	private int eyeClosingCount;
	private int timer = 0;

	private double Ta, T0, T1;		     /* high and low detection thresholds */
	private boolean learning;

	private long[] buffer;
	private double[] clbuffer;

	private static double MIN_MSNUM;

	private int sampleRate;	/* Sample rate in Hz. */
	private double MS_PER_SAMPLE;
	private int MS10;
	private int MS25;
	private int MS80;
	private int MS95;
	private int MS100;
	private int MS125;
	private int MS150;
	private int MS195;
	private int MS220;
	private int MS360;
	private int MS1000;
	private int MS1500;
	private int DERIV_LENGTH;
	private int LPBUFFER_LGTH;
	private int HPBUFFER_LGTH;
	private int PRE_BLANK;
	private int MIN_PEAK_AMP;// Prevents detections of peaks smaller than 150 uV.		
	private int WINDOW_WIDTH;	// Moving window integration width.
	// filter delays plus 200 ms blanking delay
	private int FILTER_DELAY;
	private int DER_DELAY;

	private int det_thresh, qpkcnt;
	private int[] qrsbuf;
	private int[] noise;
	private int[] rrbuf;
	private int[] rsetBuff;
	private int rsetCount = 0;
	private int nmean, qmean, rrmean;
	private int count, sbpeak, sbloc, sbcount;
	int maxder, lastmax;
	private int initBlank, initMax;
	private int preBlankCnt, tempPeak;
	private FilterMark filter;
	int fdatum, QrsDelay;
	int i, newPeak;
	private int peakmax, peaktimeSinceMax, peaklastDatum;

	// final static double TH = 0.3125;
	final static double TH = 0.05;//0.3125;

	private int[] DDBuffer;
	private int DDPtr;	/* Buffer holding derivative data. */

	// final static int MEMMOVELEN = 7 * sizeof(int);
	final static int MEMMOVECT = 7;

	/* Variables duplicated from DetectorPanTompkinsModified.java */

	// private double CHECK_AMP_THRESHOLD = 0.50;
	private double CHECK_AMP_THRESHOLD = 0.50;

	private int polarity;
	double[] lastThreeAmplitutes = new double[3];
	int[] lastThreeIntervals = new int[3]; // the last three intervals	 fourth is temp holder
	int[] last10Pts = new int[10];
	int last10Index = 0;

	int lastThreeIndex = 0;

	int currentMaxR;
	int rrInt;
	int abs_pos;
	int relative_rpos;
	int prev_r = Integer.MIN_VALUE;

	boolean gv_firstBeat;
	private int last_r_pos = 0;
	// private int recentAvg = 0;


	public DetectorCurveLength(int sr) {
		timeStampNotInitialized = true;
		setSampleRate(sr);
		MIN_MSNUM = MS220;
		getConfiguration().setName("DetectorCurveLength");
	}

	public DetectorCurveLength(int sr, int minRRI) {
		timeStampNotInitialized = true;
		setSampleRate(sr);
		MIN_MSNUM = ((int) (minRRI / MS_PER_SAMPLE + 0.5));
		getConfiguration().setName("DetectorCurveLength");
	}

	@Override
	public void setSampleRate(int sr) {
		sampleRate = sr; /* Sample rate in Hz. */
		MS_PER_SAMPLE = ((double) 1000 / (double) sampleRate);
		MS10 = ((int) (10 / MS_PER_SAMPLE + 0.5));
		MS25 = ((int) (25 / MS_PER_SAMPLE + 0.5));
		MS80 = ((int) (80 / MS_PER_SAMPLE + 0.5));
		// MS95 = ((int)(95 / MS_PER_SAMPLE + 0.5));
		MS100 = ((int) (100 / MS_PER_SAMPLE + 0.5));
		MS125 = ((int) (125 / MS_PER_SAMPLE + 0.5));
		MS150 = ((int) (150 / MS_PER_SAMPLE + 0.5));
		MS195 = ((int) (195 / MS_PER_SAMPLE + 0.5));
		MS220 = ((int) (220 / MS_PER_SAMPLE + 0.5));
		// MS360 = ((int)(360 / MS_PER_SAMPLE + 0.5));
		MS1000 = sampleRate;
		MS1500 = ((int) (1500 / MS_PER_SAMPLE));
		DERIV_LENGTH = MS10;
		LPBUFFER_LGTH = (2 * MS25);
		HPBUFFER_LGTH = MS125;
		PRE_BLANK = MS195;

		WINDOW_WIDTH = MS80; // Moving window integration width.
		// filter delays plus 200 ms blanking delay
		FILTER_DELAY = (int) (((double) DERIV_LENGTH / 2) + ((double) LPBUFFER_LGTH / 2 - 1)
				+ (((double) HPBUFFER_LGTH - 1) / 2) + PRE_BLANK);
		DER_DELAY = WINDOW_WIDTH + FILTER_DELAY + MS100;
		noise = new int[8];
		rrbuf = new int[8];
		QrsDelay = 0;

		DDBuffer = new int[DER_DELAY]; /* Buffer holding derivative data. */

		MS130 = ((int) (130 / MS_PER_SAMPLE + 0.5));
		MS250 = ((int) (250 / MS_PER_SAMPLE + 0.5));
		MS400 = ((int) (400 / MS_PER_SAMPLE + 0.5));

		LTwindow = MS130;                                     // length transform window size
		LPBUFFER_LGTH = (2 * MS25);
		HPBUFFER_LGTH = MS125;
		WINDOW_WIDTH = MS80;
		BUFFER_LGTH = LTwindow + MS250;
		CLBUFFER_LGTH = LTwindow + MS250;

		fdatum = 0;
		count = 0;
		timer = 0;

		/* Initialize variables unique to DetectorCurveLength.java */

		abspos = lastrwave = 0;
		rri = new int[]{0, 0, 0, 0, 0};

		sps = sr;                              // Sample rate in Hz
		samplingInterval = (int) 1000.0/sps;   // MS_PER_SAMPLE

		lfsc = 1.25*gain*gain/sps;	// length function scale constant
		spm = 60 * sps;             // MINUTES_PER_SAMPLE

		next_minute = from + spm;
		LPn = sps/PWFreq; 		        // The LP filter will have a notch at the power line freq

		if (LPn > 8)  LPn = 8;	                               // avoid filtering too aggressively
		LP2n = 2 * LPn;
		EyeClosing = MS250;                                   // set eye-closing period
		ExpectPeriod = ((int) (2500 / MS_PER_SAMPLE + 0.5));  // maximum expected RR interval

		eyeClosingCount = 0;

		Ta = T0 = 0;
		learning = true;

		// Initialize data buffer
		buffer = new long[BUFFER_LGTH];
		for (int i = 0; i < BUFFER_LGTH; i++) buffer[i] = 0; 

		// Initialize  curve length history buffer
		clbuffer = new double[CLBUFFER_LGTH];
		for (int i = 0; i < CLBUFFER_LGTH; i++) clbuffer[i] = 0;

		/* Initialize filters */

		filter = new FilterMark(sampleRate);
		filter.initFilter();
		initQrsDetector();

	}

	/********************************************************************
	 * mean returns the mean of an array of integers. It uses a slow sort
	 * algorithm, but these arrays are small, so it hardly matters.
	 ********************************************************************/

	public double mean(double[] array, int datnum) {
		double sum;
		int i;

		for (i = 0, sum = 0; i < datnum; ++i)
			sum += array[i];
		sum /= 1.0 * datnum;
		return sum;
	}


	/**************************************************************
	 * peak() takes a datum as input and returns a peak height
	 * when the signal returns to half its peak height, or 
	 **************************************************************/

	public int Peak(int datum, int init) {

		int pk = 0;

		if (init != 0)
			peakmax = peaktimeSinceMax = 0;

		if (peaktimeSinceMax > 0)
			++peaktimeSinceMax;

		if ((datum > peaklastDatum) && (datum > peakmax)) {
			peakmax = datum;
			if (peakmax > 2)
				peaktimeSinceMax = 1;
		} else if (datum < (peakmax >> 1)) {
			pk = peakmax;
			peakmax = 0;
			peaktimeSinceMax = 0;
		} else if (peaktimeSinceMax > MS95) {
			pk = peakmax;
			peakmax = 0;
			peaktimeSinceMax = 0;
		}
		peaklastDatum = datum;
		return (pk);
	}

	/********************************************************************
    mean returns the mean of an array of integers.  It uses a slow
    sort algorithm, but these arrays are small, so it hardly matters.
	 ********************************************************************/

	public int mean(int[] array, int datnum) {
		long sum;
		int i;

		for (i = 0, sum = 0; i < datnum; ++i)
			sum += array[i];
		sum /= datnum;
		return ((int)sum);
	}

	/****************************************************************************
     thresh() calculates the detection threshold from the qrs mean and noise
     mean estimates.
	 ****************************************************************************/

	public static int thresh(int qmean, int nmean) {
		int thrsh, dmed;
		double temp;

		dmed = qmean - nmean;
		temp = dmed;
		temp *= TH;
		dmed = (int)temp;
		thrsh = nmean + dmed;

		/*
        temp = .15 * (qmean);

        final double MIN_THRESHOLD = 0;
        if (temp < MIN_THRESHOLD) { 
        	temp = MIN_THRESHOLD;
        }
		 */

		thrsh = (int) temp;

		return (thrsh);
	}

	/***********************************************************************
    BLSCheck() reviews data to see if a baseline shift has occurred.
    This is done by looking for both positive and negative slopes of
    roughly the same magnitude in a 220 ms window.
	 ***********************************************************************/


	public int BLSCheck(int[] dBuf, int dbPtr ) {
		// int maxder;

		int max, min, maxt, mint, t, x;
		max = min = maxt = mint = t = x = 0;

		for (t = 0; t < MS220; ++t) {
			x = dBuf[dbPtr];
			if (x > max) {
				maxt = t;
				max = x;
			} else if (x < min) {
				mint = t;
				min = x;
			}
			if (++dbPtr == DER_DELAY)
				dbPtr = 0;
		}

		maxder = max;
		min = -min;

		/* Possible beat if a maximum and minimum pair are found
        where the interval between them is less than 150 ms. */

		if ((max > (min >> 3)) && (min > (max >> 3)) &&
				(Math.abs(maxt - mint) < MS150))
			return (0);

		else
			return (1);
	}


	public void initQrsDetector() {

		/* Copy from initQrsDetector() of DetectorPanTompkins.java */

		for (i = 0; i < 8; ++i) {
			noise[i] = 0;	/* Initialize noise buffer */
			rrbuf[i] = MS1000;/* and R-to-R interval buffer. */
		}

		qpkcnt = maxder = lastmax = count = sbpeak = 0;
		initBlank = initMax = preBlankCnt;
		sbcount = MS1500;

		filter.initFilter(); //QRSFilter(0,1) ;	/* initialize filters. */
		Peak(0, 1);


		/* Copy from initQrsDetector() of DetectorPanTompkinsModified.java */

		currentMaxR = Integer.MIN_VALUE;

		gv_firstBeat = true;
		rrInt = 0;
		abs_pos = 0;
		relative_rpos = 0;

		lastThreeIndex = 0;
		polarity = 0;
	}

	public int _getValue(int datum) {

		int fdatum = 0;
		int QrsDelay = 0;

		fdatum = filter.lpfilt(datum, 0);
		fdatum = filter.hpfilt(fdatum, 0);

		// fdatum = filter.deriv2(fdatum, 0);
		// fdatum = Math.abs(fdatum);
		fdatum = filter.mvwint(fdatum, 0);

		DDBuffer[DDPtr] = filter.deriv1(datum, 0);
		if (++DDPtr == DER_DELAY)
			DDPtr = 0;

		++count;
		eyeClosingCount++;

		// Update cicular data buffer
		for (int i = 0; i < BUFFER_LGTH-1; i++) buffer[i] = buffer[i+1];
		buffer[BUFFER_LGTH-1] = fdatum;

		// Compute length transform
		double curveLength = 0;
		for (int i = BUFFER_LGTH - 1 - EyeClosing/2; i >= BUFFER_LGTH - LTwindow; i--) {
			curveLength += Math.sqrt(lfsc + (buffer[i] - buffer[i-1]) * (buffer[i] - buffer[i-1]));
			// curveLength += Math.sqrt(lfsc + fdatum*fdatum);
		}

		// Update cicular data buffer
		for (int i = 0; i < CLBUFFER_LGTH-1; i++) clbuffer[i] = clbuffer[i+1];
		clbuffer[CLBUFFER_LGTH-1] = curveLength;

		/* Average the first 8 seconds of the length-transformed samples
			to determine the initial thresholds Ta and T0. The number of samples
			in the average is limited to half of the ltsamp buffer if the sampling
			frequency exceeds about 2 KHz. */

		if (count >= CLBUFFER_LGTH) {
			T0 = mean(clbuffer, CLBUFFER_LGTH);
			Ta = 3 * T0;
		}
		else {
			return 0;
		}

		if (eyeClosingCount < EyeClosing) {
			return 0;
		}

		if (learning) {
			if (count < EyeClosing) { 
				learning = false;
				T1 = T0;
			}
		}
		else {
			T1 = 2*T0;
		}

		/* Compare a length-transformed sample against T1 */
		int max_pos = CLBUFFER_LGTH - 1 - EyeClosing/2 + 1;
		int min_pos = CLBUFFER_LGTH - 1 - EyeClosing/2 - 1;
		double onset = 0;
		int tpq = 0;

		if (curveLength > T1) {	/* found a possible QRS near t */

			timer = 0; /* used for counting the time after previous QRS */

			for (int pos = max_pos; pos < CLBUFFER_LGTH; pos++)
				if (clbuffer[pos] > clbuffer[max_pos]) max_pos = pos;
			for (int pos = min_pos; pos > CLBUFFER_LGTH - 1 - EyeClosing; pos--)
				if (clbuffer[pos] < clbuffer[min_pos]) min_pos = pos;

			if (clbuffer[max_pos] > clbuffer[min_pos]+10) {
				onset = clbuffer[max_pos]/100 + 2;
				tpq = CLBUFFER_LGTH - 1 - EyeClosing/2 - 5;

				/*
				 * Check for maximum derivative and matching minima and maxima for
				 * T-wave and baseline shift rejection. Only consider this peak if
				 * it doesn't seem to be a base line shift.
				 */

				if (!(BLSCheck(DDBuffer, DDPtr) != 0)) {

					for (int i = MEMMOVECT; i > 0; i--) {
						rrbuf[i] = rrbuf[i - 1];
					}
					rrbuf[0] = count - WINDOW_WIDTH;
					count = WINDOW_WIDTH;

					lastmax = maxder;
					maxder = 0;
					QrsDelay = WINDOW_WIDTH + FILTER_DELAY;
				}
			}

			/* Adjust thresholds */
			Ta += (clbuffer[max_pos] - Ta)/10;
			T1 = Ta / 3;

			/* Lock out further detections during the eye-closing period */
			eyeClosingCount = 0;
		}

		else if (!learning) {
			/* Once past the learning period, decrease threshold if no QRS
			was detected recently. */
			if (++timer > ExpectPeriod && Ta > Tm) {
				Ta--;
				T1 = Ta / 3;
			}      
		}

		return QrsDelay;
	}

	public int getValue(int pending, int datum, long tStamp) {

		if (timeStampNotInitialized) {
			currTimeStamp = tStamp;
			timeStampNotInitialized = false;
		}
		return getValue(pending, datum);

    }

	List<Integer> gv_ii = new LinkedList<Integer>();  // must go in the init block

	@Override
	public int getValue(int pending, int datum) {

		int threshold = 1;
		int delay = _getValue(1000*datum);

		if (delay > threshold) {
			fireBeatDetection(-1, 0, -1, leadId, 3);
		}

		/*
		 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! Save features instead of data
		 * points!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		 */

		// datum = feature2;

		last10Pts[last10Index++] = datum;
		last10Index %= 10;

		if (polarity == 0) {
			// determine polarity
		} else if (polarity < 0) {
			datum = -datum;
		}
		abs_pos++;

		if (prev_r == Integer.MIN_VALUE) {
			prev_r = datum;
			last_r_pos = 0;
		}

		// assume bad amplitude
		if (!gv_firstBeat && (abs_pos - last_r_pos > 3 * MS1500)) {
			gv_firstBeat = true; // reset amplitudes
		}

		if (delay > threshold) { // found a beat
			if (gv_firstBeat) {
				lastThreeAmplitutes[0] = currentMaxR;
				lastThreeAmplitutes[1] = currentMaxR;
				lastThreeAmplitutes[2] = currentMaxR;
				gv_firstBeat = false;
			}

			if (checkAndUpdateAmp(lastThreeAmplitutes, currentMaxR)) {
				// found a reasonable currentMaxR as defined by the past n R's
				int r_pos = abs_pos - relative_rpos;
                if (sampleRate == 360) r_pos -= MS10;
                if (sampleRate == 200) r_pos += MS10/2;

				/*
				 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				 * !!!!!! // Account for additional delay due to detection
				 * strength calculations
				 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				 */
				// r_pos = r_pos - 1;

				int interval = r_pos - last_r_pos;
				
				
				// Changed MS25 to MS220 ( 4/6/2010 ) 
				if (interval > MIN_MSNUM) { //MS25) {

					gv_ii.add(r_pos - last_r_pos);

					long r_timestamp= startTime + (r_pos * 1000L) / sampleRate;
					fireRWaveDetection(-relative_rpos, r_pos - last_r_pos, currentMaxR, leadId, 3, r_timestamp);
					last_r_pos = r_pos;

				}

			}
			rrInt = 0;
			currentMaxR = Integer.MIN_VALUE;
			relative_rpos = 0;

		} else {
			relative_rpos++; // maintains a relative offset to the most probable
								// R
			rrInt++;

			// no beat
			int slope = -(datum - prev_r);
			if (slope > currentMaxR) {
				currentMaxR = slope;
				// relative_rpos = 0;

				// find point at which max amplitude actually occurred
				int amppos = 0;
				int ampmax = last10Pts[0];
				for (int i = 0; i < 10; i++) {
					// select max or min depending if this is a local-max or
					// local-min that we have detected
					boolean comparison = (slope > 0) ? (last10Pts[i] < ampmax) : (last10Pts[i] > ampmax);
					if (comparison) {
						amppos = i;
						ampmax = last10Pts[i];
					}
				}

				relative_rpos = (last10Index - amppos + 10) % 10;
			}
		}

		prev_r = datum;

		return 0;
	}

	public boolean checkAndUpdateAmp(double[] pastAmps, double thisAmp) {
		// test that thisAmp is within some threshold of the past amps
		// if ok add thisAmp and return true
		// if not ok do not add and return false
		double avg = 0.0;
		for (int i = 0; i < pastAmps.length; i++)
			avg += pastAmps[i];
		avg /= pastAmps.length;

		// wlb -- removed high-side check
		if (thisAmp >= (avg - (avg * CHECK_AMP_THRESHOLD))) {
			// if (thisAmp >= (avg - (avg * CHECK_AMP_THRESHOLD)) && thisAmp <=
			// (avg + (2 * avg * CHECK_AMP_THRESHOLD))) {
			pastAmps[0] = pastAmps[1];
			pastAmps[1] = pastAmps[2];
			pastAmps[2] = thisAmp;
			return true;
		}

		return false;
	}

	@Override
	public int getSampleRate() {
		return sampleRate;
	}

	@Override
	public void restartDetector() {
		startTime = 0;
		nextBlockTime = 0;
		startTimeInitialized = false;

		fdatum = 0;
		count = 0;
		timer = 0;

		abspos = lastrwave = 0;
		rri = new int[]{0, 0, 0, 0, 0};

	    eyeClosingCount = 0;
	    Ta = T0 = 0;
	    learning = true;

	    // Initialize data buffer
	    buffer = new long[BUFFER_LGTH];
	    for (int i = 0; i < BUFFER_LGTH; i++) buffer[i] = 0; 

		// Initialize  curve length history buffer
		clbuffer = new double[CLBUFFER_LGTH];
		for (int i = 0; i < CLBUFFER_LGTH; i++) clbuffer[i] = 0;

		polarity = 0;
		lastThreeAmplitutes = new double[3];
		lastThreeIntervals = new int[3]; // the last three intervals	 fourth is temp holder
		last10Pts = new int[10];
		last10Index = 0;

		lastThreeIndex = 0;

		currentMaxR = 0;
		rrInt = 0;
		abs_pos = 0;
		relative_rpos = 0;
		prev_r = Integer.MIN_VALUE;

		gv_firstBeat = false;
		last_r_pos = 0;
	}

}