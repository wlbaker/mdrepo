package idea.qrsdet;



public class DetectorABPOnset extends AbstractDetector {

	/**
	 * The major differences between this algorithm and the algorithm
	 * implemented in DetectorPanTompkinsModified.java include the following:
	 * 
	 * 1. Only a low-pass filter applied to the data 2. Buffers of
	 * past eight frequency samples used to compute slope sum function transform
	 * 
	 * This algorithm employs the strengths of the Modified Pan-Tompkins
	 * algorithm, including filters and the search-back technique for
	 * peaks/thresholds.
	 */


	private int sampleRate; /* Sample rate in Hz. */
	private double MS_PER_SAMPLE;
	private int MS25;
	private int MS80;
	private int MS125;
	private int MS130;
	private int MS220;
	private int MS250;
	private int MS400;
	private int MS1000;

	private int LPBUFFER_LGTH;
	private int HPBUFFER_LGTH;	
	private int WINDOW_WIDTH;	// Moving window integration width.
	private int BUFFER_LGTH;
	private int SSFBUFFER_LGTH;

	private boolean timeStampNotInitialized;
	private long currTimeStamp;

	private long count;

	private FilterMark filter;

	private int fdatum;

	/* Variables unique to DetectorCurveLength.java */

    private long abspos;
    private long lastrwave;
    private int []rri;

	// private static final int BUFLN  = 16384;    /* must be a power of 2, see ltsamp() */
	private static final double EYE_CLS = 250;    /* eye-closing period is set to 0.25 sec (250 ms) */ 
	private static final double NDP = 2500;        /* adjust threshold if no QRS found in 2.5 seconds */
	private static final int PWFreqDEF = 60;      /* power line (mains) frequency, in Hz (default) */
	private static final int TmDEF = 5;         /* minimum threshold value (default) */

	private int from = 0;

	private double lfsc;            /* length function scale constant */
	private int nsig;               /* number of input signals */
	private int LPn, LP2n;          /* filter parameters (dependent on sampling rate) */
	private int SlopeWindow;           /* slope window size */
	private int PWFreq = PWFreqDEF;	/* power line (mains) frequency, in Hz */
	private int sig = -1;	        /* signal number of signal to be analyzed */
	private int Tm = TmDEF;         /* minimum threshold value */


	private int sps;
	private int samplingInterval;
	private int spm;
	private int next_minute;
	private int EyeClosing; /* set eye-closing period */
	private int LPeriod;	      /* learning period is the first LPeriod samples  */

	private int eyeClosingCount;
	private int timer = 0;

	private double Ta, T0, T1;		     /* high and low detection thresholds */
	private boolean learning;

	private long[] buffer;
	private double[] ssfbuffer;

	private static double MIN_MSNUM;


	public DetectorABPOnset(int sr) {
		timeStampNotInitialized = true;
		setSampleRate(sr);
		MIN_MSNUM = MS220;
	}

	public DetectorABPOnset(int sr, int minRRI) {
		timeStampNotInitialized = true;
		setSampleRate(sr);
		MIN_MSNUM = ((int) (minRRI / MS_PER_SAMPLE + 0.5));;
	}

	@Override
	public void setSampleRate(int sr) {
		sampleRate = sr; /* Sample rate in Hz. */

		if (sr == 200) {
			System.err.println("Error: Changing sample rate from 200 Hz to 100 Hz ...");
			sampleRate = 100;
		}

		MS_PER_SAMPLE = ((double) 1000 / (double) sampleRate);

		MS25 = ((int) (25 / MS_PER_SAMPLE + 0.5));
        MS80 = ((int)(80 / MS_PER_SAMPLE + 0.5));
        MS125 = ((int)(125 / MS_PER_SAMPLE + 0.5));
		MS130 = ((int) (130 / MS_PER_SAMPLE + 0.5));
		MS220 = ((int) (220 / MS_PER_SAMPLE + 0.5));
		MS250 = ((int) (250 / MS_PER_SAMPLE + 0.5));
		MS400 = ((int) (400 / MS_PER_SAMPLE + 0.5));
		MS1000 = sampleRate;

	    SlopeWindow = MS130;                                     // length transform window size
        LPBUFFER_LGTH = (2 * MS25);
        HPBUFFER_LGTH = MS125;
        WINDOW_WIDTH = MS80;
		BUFFER_LGTH = SlopeWindow + MS250;
		SSFBUFFER_LGTH = SlopeWindow + MS250;

		fdatum = 0;
		count = 0;
		timer = 0;

		/* Initialize variables unique to DetectorCurveLength.java */

		abspos = lastrwave = 0;
		rri = new int[]{0, 0, 0, 0, 0};

		sps = sr;                              // Sample rate in Hz
	    samplingInterval = (int) 1000.0/sps;   // MS_PER_SAMPLE

	    spm = 60 * sps;             // MINUTES_PER_SAMPLE

	    next_minute = from + spm;
	    LPn = sps/PWFreq; 		        // The LP filter will have a notch at the power line freq

	    if (LPn > 8)  LPn = 8;	                               // avoid filtering too aggressively
	    LP2n = 2 * LPn;
	    EyeClosing = MS250;                                   // set eye-closing period
	    LPeriod = 1000;

	    eyeClosingCount = 0;

	    Ta = T0 = 0;
	    learning = true;

	    // Initialize data buffer
	    buffer = new long[BUFFER_LGTH];
	    for (int i = 0; i < BUFFER_LGTH; i++) buffer[i] = 0; 

	    // Initialize  slope sum function history buffer
	    ssfbuffer = new double[SSFBUFFER_LGTH];
	    for (int i = 0; i < SSFBUFFER_LGTH; i++) ssfbuffer[i] = 0;

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

	public void initQrsDetector() {


		filter.initFilter(); // QRSFilter(0,1) ; /* initialize filters. */

	}

	public int getValue(int pending, int datum, long tStamp) {

		if (timeStampNotInitialized) {
			currTimeStamp = tStamp;
			timeStampNotInitialized = false;
		}
		return getValue(pending, datum);

    }

	@Override
	public int getValue(int pending, int datum) {

		abspos++;

		if (timeStampNotInitialized) {
			//??? currTimeStamp = tStamp;
			timeStampNotInitialized = false;
		}

		fdatum = filter.lpfilt(datum, 0);
		if (sampleRate == 500) fdatum = filter.hpfilt(fdatum, 0);
		if (sampleRate == 500) fdatum = filter.deriv1(fdatum, 0);
		if (sampleRate == 500) fdatum = filter.mvwint(fdatum, 0);

		count++;
		eyeClosingCount++;

		// Update cicular data buffer
		for (int i = 0; i < BUFFER_LGTH-1; i++) buffer[i] = buffer[i+1];
		buffer[BUFFER_LGTH-1] = fdatum;

		// Compute slope sum function transform
		double slopeSum = 0;
		double dy = 0;
		for (int i = BUFFER_LGTH - 1 - EyeClosing/2; i >= BUFFER_LGTH - SlopeWindow; i--) {
			dy = (buffer[i] - buffer[i-1]);
			if (dy < 0) dy = 0;
			if (sampleRate == 500) slopeSum += dy;
			else slopeSum += dy;
		}

		// Update cicular data buffer
		for (int i = 0; i < SSFBUFFER_LGTH-1; i++) ssfbuffer[i] = ssfbuffer[i+1];
		ssfbuffer[SSFBUFFER_LGTH-1] = slopeSum;

	    /* Average the first 8 seconds of the length-transformed samples
	       to determine the initial thresholds Ta and T0. The number of samples
	       in the average is limited to half of the ltsamp buffer if the sampling
	       frequency exceeds about 2 KHz. */

		if (count >= SSFBUFFER_LGTH) {
			T0 = mean(ssfbuffer, SSFBUFFER_LGTH);
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
		int max_pos = SSFBUFFER_LGTH - 1 - EyeClosing/2 + 1;
		int min_pos = SSFBUFFER_LGTH - 1 - EyeClosing/2 - 1;
		double onset = 0;
		int tpq = 0;

		if (slopeSum > T1) {	/* found a possible QRS near t */

			timer = 0; /* used for counting the time after previous QRS */

			for (int pos = max_pos; pos < SSFBUFFER_LGTH; pos++)
				if (ssfbuffer[pos] > ssfbuffer[max_pos]) max_pos = pos;
			for (int pos = min_pos; pos > SSFBUFFER_LGTH - 1 - EyeClosing; pos--)
				if (ssfbuffer[pos] < ssfbuffer[min_pos]) min_pos = pos;

			if (ssfbuffer[max_pos] > ssfbuffer[min_pos]+10) {
				onset = ssfbuffer[max_pos]/100 + 2;
				tpq = SSFBUFFER_LGTH - 1 - EyeClosing/2 - 5;

				int onset_pos = (int) abspos - EyeClosing/2 - 5;

				int r_pos = (int) abspos;
				int rr_interval = (int)( abspos - lastrwave );

				rri[0] = rri[1];
				rri[1] = rri[2];
				rri[2] = rri[3];
				rri[3] = rri[4];
				rri[4] = rr_interval;

				// if (rr_interval > getSampleRate()/4) {
				if (rr_interval > MIN_MSNUM) {

					long r_timestamp= startTime - 2*MS25 + (onset_pos * 1000L) / MS1000;
					// if (sampleRate == 500) r_timestamp= startTime - 2*MS25 - MS125 + (r_pos * 1000L) / MS1000;
					fireRWaveDetection(r_pos, rr_interval, fdatum, leadId, 3, r_timestamp);

					lastrwave = abspos;
				}

				/* Adjust thresholds */
				Ta += (ssfbuffer[max_pos] - Ta)/10;
				T1 = Ta / 3;

				/* Lock out further detections during the eye-closing period */
				eyeClosingCount = 0;
			}

		}
		else if (!learning) {
			/* Once past the learning period, decrease threshold if no QRS
		       was detected recently. */
			if (++timer > LPeriod && Ta > Tm) {
				Ta--;
				T1 = Ta / 3;
			}      
		}


		return 0;

	}

	@Override
	public int getSampleRate() {
		return sampleRate;
	}


	@Override
	public void setLeadId(int id) {
		this.leadId = id;
	}

	@Override
	public void setSignalLoc(String parameter) {
		this.loc = parameter;
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

	    // Initialize  slope sum function history buffer
	    ssfbuffer = new double[SSFBUFFER_LGTH];
	    for (int i = 0; i < SSFBUFFER_LGTH; i++) ssfbuffer[i] = 0;
	}

}