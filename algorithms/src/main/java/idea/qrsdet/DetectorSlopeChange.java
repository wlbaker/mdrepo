package idea.qrsdet;

import java.util.LinkedList;
import java.util.List;

public class DetectorSlopeChange extends AbstractDetector {

	/**
	 * The major differences between this algorithm and the algorithm
	 * implemented in DetectorPanTompkinsModified.java include the following:
	 * 
	 * 1. Only low-pass and high-pass filters applied to the data 2. Buffers of
	 * past eight frequency samples used to compute decimated sub-band feature
	 * signals 3. Detection strengths used to threshold feature signal samples
	 * 4. Octave signal processing employed, if necessary
	 * 
	 * This algorithm employs the strengths of the Modified Pan-Tompkins
	 * algorithm, including filters and the search-back technique for
	 * peaks/thresholds.
	 */

	/* Variables duplicated from DetectorPanTompkins.java */

	private int sampleRate; /* Sample rate in Hz. */
	private double MS_PER_SAMPLE;
	private int MS10;
	private int MS25;
	private int MS80;
	// private int MS95;
	private int MS100;
	private int MS125;
	private int MS150;
	private int MS195;
	private int MS220;
	// private int MS360;
	private int MS1000;
	private int MS1500;
	private int DERIV_LENGTH;
	private int LPBUFFER_LGTH;
	private int HPBUFFER_LGTH;
	private int PRE_BLANK;
	private int WINDOW_WIDTH; // Moving window integration width.
	// filter delays plus 200 ms blanking delay
	private int FILTER_DELAY;
	private int DER_DELAY;

	private int[] noise;
	private int[] rrbuf;
	private int count;
	int maxder, lastmax;
	private FilterMarkBands filter;
	// private FilterMark filter;
	int fdatum, QrsDelay;
	int i, newPeak;

	// final static double TH = 0.3125;
	final static double TH = 0.3125;

	private int[] DDBuffer;
	private int DDPtr; /* Buffer holding derivative data. */

	// final static int MEMMOVELEN = 7 * sizeof(int);
	final static int MEMMOVECT = 7;

	/* Variables duplicated from DetectorPanTompkinsModified.java */

	// private double CHECK_AMP_THRESHOLD = 0.50;
	private double CHECK_AMP_THRESHOLD = 0.50;

	private int polarity;
	double[] lastThreeAmplitutes = new double[3];
	int[] lastThreeIntervals = new int[3]; // the last three intervals fourth is
											// temp holder
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

	/* Variables unique to DetectorFilterBanksOnly.java */

	int[] last8F1Pts = new int[8];
	int[] last8F2Pts = new int[8];
	int[] last8F3Pts = new int[8];

	static int prevSlope;

	static double THRESH1;
	static double THRESH2;
	static double THRESH4;

	static double SL1; // Channel 1 signal level
	static double NL1; // Channel 1 noise level
	static double SL2; // Channel 2 signal level
	static double NL2; // Channel 2 noise level
	static double SL4; // Channel 4 signal level
	static double NL4; // Channel 4 noise level

	int eventCount;

	int feature1;
	int feature2;
	int feature3;

	boolean isFilled;
	int fillCount, s1idx, n1idx, s2idx, n2idx, s4idx, n4idx;
	double[] s1buffer = new double[8];
	double[] n1buffer = new double[8];
	double[] s2buffer = new double[8];
	double[] n2buffer = new double[8];
	double[] s4buffer = new double[8];
	double[] n4buffer = new double[8];

	double detStrength;

	public DetectorSlopeChange(int sr) {
		setSampleRate(sr);
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

		/* Initialize variables unique to DetectorFilterBanksOnly.java */

		for (int i = 0; i < 8; i++) {
			last8F1Pts[i] = 0;
			last8F2Pts[i] = 0;
			last8F3Pts[i] = 0;
		}

		prevSlope = 0; // default slope = 0

		THRESH1 = 0.08;
		THRESH2 = 0.7;
		THRESH4 = 0.3;

		SL1 = 0;
		NL1 = 0;
		SL2 = 0;
		NL2 = 0;
		SL4 = 0;
		NL4 = 0;

		eventCount = 0;

		feature1 = 0;
		feature2 = 0;
		feature3 = 0;

		isFilled = false;
		fillCount = 0;
		s1idx = 0;
		n1idx = 0;
		s2idx = 0;
		n2idx = 0;
		s4idx = 0;
		n4idx = 0;

		for (int i = 0; i < 8; i++) {
			s1buffer[i] = 0;
			n1buffer[i] = 0;
			s2buffer[i] = 0;
			n2buffer[i] = 0;
			s4buffer[i] = 0;
			n4buffer[i] = 0;
		}

		detStrength = 0;

		/* Initialize filters */

		filter = new FilterMarkBands(sampleRate);
		// filter = new FilterMark(sampleRate);
		filter.initFilter();
		initQrsDetector();

	}

	/********************************************************************
	 * mean returns the mean of an array of integers. It uses a slow sort
	 * algorithm, but these arrays are small, so it hardly matters.
	 ********************************************************************/

	public int mean(int[] array, int datnum) {
		long sum;
		int i;

		for (i = 0, sum = 0; i < datnum; ++i)
			sum += array[i];
		sum /= datnum;
		return ((int) sum);
	}

	/********************************************************************
	 * dmean returns the mean of an array of doubles. It uses a slow sort
	 * algorithm, but these arrays are small, so it hardly matters.
	 ********************************************************************/

	public double dmean(double[] array, int datnum) {
		double sum;
		int i;

		for (i = 0, sum = 0; i < datnum; ++i)
			sum += array[i];
		sum /= datnum;
		return sum;
	}

	/***********************************************************************
	 * BLSCheck() reviews data to see if a baseline shift has occurred. This is
	 * done by looking for both positive and negative slopes of roughly the same
	 * magnitude in a 220 ms window.
	 ***********************************************************************/

	public int BLSCheck(int[] dBuf, int dbPtr) {
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

		/*
		 * Possible beat if a maximum and minimum pair are found where the
		 * interval between them is less than 150 ms.
		 */

		if ((max > (min >> 3)) && (min > (max >> 3)) && (Math.abs(maxt - mint) < MS150))
			return (0);

		else
			return (1);
	}

	public void initQrsDetector() {

		/* Copy from initQrsDetector() of DetectorPanTompkins.java */

		for (i = 0; i < 8; ++i) {
			noise[i] = 0; /* Initialize noise buffer */
			rrbuf[i] = MS1000;/* and R-to-R interval buffer. */
		}

		filter.initFilter(); // QRSFilter(0,1) ; /* initialize filters. */

		/* Copy from initQrsDetector() of DetectorPanTompkinsModified.java */

		currentMaxR = Integer.MIN_VALUE;

		gv_firstBeat = true;
		rrInt = 0;
		abs_pos = 0;
		relative_rpos = 0;

		lastThreeIndex = 0;
		polarity = 0;

	}

	// / <summary>
	// main find value
	// / </returns>

	List<Integer> gv_ii = new LinkedList<Integer>(); // must go in the init
														// block

	public int _getValue(int datum) {

		// int fdatum = 0;
		int QrsDelay = 0;

		// DetectorFilterBank data variables
		int sb1datum = 0;
		int sb2datum = 0;
		int sb3datum = 0;

		// Level 1 variables
		int currSlope = 0;
		int diffSlope = 0;

		// Level 2 variables
		double detStrength1;
		double detStrength2;
		double detStrength4;

		// Classification of feature
		// 0 = none, -1 = noise, 1 = signal
		int classCh1 = 0;
		int classCh2 = 0;
		int classCh4 = 0;

		// Level 3 variables
		double delta1 = 0;
		double delta2 = 0;

		/*
		 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! Only perform sub-band filtering
		 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		 */

		// Extract feature 1 from Sub-band 1

		sb1datum = filter.lpfilt(datum, 0);
		// sb1datum = filter.hpfilt(sb1datum, 0);

		// sb1datum = Math.abs(sb1datum);
		// sb1datum *= sb1datum;

		feature1 = sb1datum;
		// feature1 = filter.mwi1(sb1datum, 0);

		for (int i = 0; i < 8 - 1; i++) {
			last8F1Pts[i] = last8F1Pts[i + 1];
		}
		last8F1Pts[7] = feature1;

		// Extract feature 2 from Sub-band 2

		// sb2datum = filter.hpfiltSb2(datum, 0);
		// sb2datum = Math.abs(sb2datum);
		// sb2datum *= sb2datum;

		sb2datum = Math.abs(datum);
		// sb2datum *= sb2datum;

		feature2 = filter.mwi2(sb2datum, 0);

		for (int i = 0; i < 8 - 1; i++) {
			last8F2Pts[i] = last8F2Pts[i + 1];
		}
		last8F2Pts[7] = feature2;

		// Extract feature 3 from Sub-band 3

		sb3datum = filter.hpfiltSb3(datum, 0);

		sb3datum = Math.abs(sb3datum);
		// sb3datum *= sb3datum;

		feature3 = filter.mwi3(sb3datum, 0);

		for (int i = 0; i < 8 - 1; i++) {
			last8F3Pts[i] = last8F3Pts[i + 1];
		}
		last8F3Pts[7] = feature3;

		// Initialize signal feature and noise feature buffers
		if (isFilled != true) {
			s1buffer[fillCount] = feature2;
			s2buffer[fillCount] = feature2;
			s4buffer[fillCount++] = feature3;

			if (fillCount == 8) {
				isFilled = true;
				SL1 = dmean(s1buffer, 8) + .1 * dmean(s1buffer, 8);
				NL1 = dmean(s1buffer, 8) - .1 * dmean(s1buffer, 8);
				SL2 = dmean(s2buffer, 8) + .1 * dmean(s2buffer, 8);
				NL2 = dmean(s2buffer, 8) - .1 * dmean(s2buffer, 8);
				SL4 = dmean(s4buffer, 8) + .1 * dmean(s4buffer, 8);
				NL4 = dmean(s4buffer, 8) - .1 * dmean(s4buffer, 8);
				for (int i = 0; i < 8; i++) {
					n1buffer[i] = NL1;
					n2buffer[i] = NL2;
					n4buffer[i] = NL4;
				}
			}
		}

		/*
		 * Level 1: The first level (see Figs. 6, 7) determines candidate beats
		 * by detecting peaks in the output of a MWI on feature A peak detection
		 * algorithm detects a peak when there is an inflexion point in the
		 * output of the MWI. The feature value itself is not compared to any
		 * threshold and a peak is the only requirement to trigger an event.
		 * This level, thus, detects most of the true beats (i.e., has a few
		 * FN�s) but also very often incorrectly detects the presence of a beat
		 * (i.e., noise peaks and has many FP�s).
		 * 
		 * This level, thus, serves as an �event detector,� and is used to
		 * trigger further logic to eliminate FP�s introduced here. This level
		 * is designed to have few FN�s but it limits the theoretical best FN
		 * rate possible for the overall beat detection algorithm. Since this
		 * level operates at the downsampled rate of the FB it contributes to
		 * the computational efficiency of the algorithm.
		 */

		// Level 1 (Detrmine if event occurs between features in Sub-band 1)
		if (Math.abs(feature1 - last8F1Pts[6]) < 0.00005) {
			currSlope = 0;
		} else {
			currSlope = (int) Math.signum(feature1 - last8F1Pts[6]);
		}

		diffSlope = (currSlope - prevSlope);
		prevSlope = currSlope;

		/*
		 * Level 2: This level, as shown in Figs. 7 and 9, has 2 one-channel
		 * detection processes (Chan1 and Chan2) operating simultaneously. Both
		 * channels use feature F2 in their respective MWI�s, however the preset
		 * thresholds are different. Chan1 has a low threshold (T1 = 0.08) and
		 * Chan2 has a high threshold (T2 = 0.7). When level 1 triggers an event
		 * the output in the MWI�s of each of and are compared with their
		 * respective signal and noise levels. The signal (and noise) levels in
		 * each channel are computed from the signal (and noise) history of
		 * their respective channels. Each channel computes its own detection
		 * strength and compares with their respective thresholds to result in
		 * two simultaneous (and possibly different) classifications of the
		 * current event as a beat or noise. When a channel detects a beat (or
		 * noise peak) its own signal (or noise) history is updated irrespective
		 * of the detection status from the other channel.
		 * 
		 * In a one-channel beat detection algorithm, the threshold value
		 * determines the classification of an incoming feature as a signal peak
		 * or noise peak. A low threshold will result in noise peaks being
		 * classified as a beat, and the feature value updated in the signal
		 * history. This will result in an inaccurate estimated signal level.
		 * However the noise history is updated accurately since the low
		 * threshold does not allow signal peaks to be incorrectly detected as
		 * noise. Similarly a high threshold will incorrectly result in some
		 * signal peaks being classified as noise and updated in the noise
		 * history. This will incorrectly raise the noise level and affect
		 * future beat detections. However in this scenario the signal history
		 * is updated accurately since beat detections using a high threshold
		 * are most likely correct. This level, thus, operates two one-channel
		 * beat detection blocks which have complementary FN and FP detection
		 * rates. Chan1 generates a few FN�s but many FP�s and Chan2 generates
		 * many FN�s but a few FP�s.
		 * 
		 * Level 2 is operated only when Level 1 detects an event. Computations
		 * of the features, the MWI, and signal and noise levels operate at the
		 * reduced FB rate and this contributes to the overall computational
		 * efficiency of the beat detection algorithm.
		 */

		if ((diffSlope == 2) && ((SL1 != 0) && (NL1 != 0)) && ((SL2 != 0) && (NL2 != 0)) && ((SL4 != 0) && (NL4 != 0))
				&& (isFilled == true)) {

			// ??????? Don't know if below performs better test
			// if ( (diffSlope == 2) && ( (SL != 0) && (NL != 0) ) ) {

			// Level 2 (Event detected, so use features in Sub-band 2 to
			// classify)

			/*
			 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! Use detStrength
			 * variable to store detection strengths
			 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			 */

			detStrength1 = (feature2 - NL1) / (SL1 - NL1);

			if (detStrength1 > THRESH1) {
				classCh1 = 1;

				s1buffer[s1idx++] = feature2;
				s1idx = s1idx % 8;
			} else {
				classCh1 = -1;

				n1buffer[n1idx++] = feature2;
				n1idx = n1idx % 8;
			}

			detStrength2 = (feature2 - NL2) / (SL2 - NL2);

			if (detStrength2 > THRESH2) {
				classCh2 = 1;

				s2buffer[s2idx++] = feature2;
				s2idx = s2idx % 8;

			} else {
				classCh2 = -1;

				n2buffer[n2idx++] = feature2;
				n2idx = n2idx % 8;
			}

			/*
			 * Level 3: This level fuses the beat detection status from each of
			 * the 2 one-channel detection algorithms in level 2 by
			 * incorporating a set of if-then-else rules. The rules incorporate
			 * the fact that the 2 one- channel detection blocks have
			 * complementary detection rates. There are four possible cases to
			 * design rules for. If both channels indicate a beat then the
			 * output of level 3 classifies the current event as a beat. Since
			 * Chan2 uses a high threshold in its detection logic, it generates
			 * few FP�s and, thus, beat detection is very accurate. If both
			 * channels indicate not-a-beat then the output of level 3 is that
			 * the current event is not a beat. Since the threshold used in is
			 * very low, it has very few FN�s, and more than likely a beat did
			 * not occur in reality. If Chan1 indicates not-a-beat and Chan2
			 * indicates a beat, then the output is classified as a beat.
			 * However, this scenario does not occur since, the threshold used
			 * in Chan1 is very low, and the same feature is used in Chan2. A
			 * beat detected by Chan2 more than likely got detected in Chan1. If
			 * Chan1 indicates a beat and Chan2 indicates a not-a-beat, then the
			 * detection strengths from each channel are compared. Chan1
			 * generates many FP�s but Chan2 generates many FN�s. The normalized
			 * detection strength which indicates which decision was �stronger,�
			 * can be compared to favor the channel with the stronger decision.
			 */

			delta1 = (detStrength1 - THRESH1) / (1 - THRESH1);
			delta2 = (THRESH2 - detStrength2) / THRESH2;

			// eventCount++;

			if (((classCh1 == 1) && (classCh2 == 1)) || (classCh2 == 1) || ((classCh1 == 1) && (delta1 > delta2))) {

				detStrength = Math.max(detStrength1, detStrength2);

				/*
				 * System.out.println("Event " + eventCount +
				 * " detected with strength " + detStrength);
				 * 
				 * if (detStrength < THRESH2) { System.out.println("delta1 " +
				 * delta1 + " : delta2 " + delta2); }
				 * 
				 * if (detStrength > Double.MAX_VALUE) {
				 * System.out.println("SL " + SL + " and NL " + NL); }
				 */
			} else {

				/*
				 * Level 4: This level incorporates another one-channel
				 * detection block and uses feature as the input to the MWI. If
				 * a beat is detected in level 3, the signal history is updated
				 * and the detection status from this level is that the current
				 * event is a beat. If level 3 did not classify the current
				 * event as a beat, the detection strength of the one-channel
				 * detection block is computed and compared with the threshold
				 * (T4 = 0.30 for this block). If the detection strength is
				 * greater than the threshold a beat is indicated and the signal
				 * history is updated. If the detection strength is less than
				 * the threshold the noise history is updated and the detection
				 * status from this level is not-a-beat.
				 * 
				 * This level reduces FN�s (events which were inaccurately
				 * missed as beats by level 3). The beat detection rates after
				 * level 3 are higher than those from the detections in level 2.
				 * Since the signal and noise levels in the one-channel
				 * detectionblock of level 4 use detection rates from level 3,
				 * the signal and noise level estimates are more accurate than
				 * the signal and noise levels estimated in the one-channel
				 * detection blocks of level 2. This leads to improved detection
				 * rates.
				 */

				// eventCount++;

				detStrength4 = (feature3 - NL4) / (SL4 - NL4);

				if (detStrength4 > THRESH4) {
					classCh4 = 1;

					s4buffer[s4idx++] = feature3;
					s4idx = s4idx % 8;

					detStrength = Math.max(detStrength, detStrength4);
				} else {
					classCh4 = -1;

					n4buffer[n4idx++] = feature3;
					n4idx = n4idx % 8;

					detStrength = 0;
				}

				/*
				 * Level 5: The previous levels do not incorporate any timing
				 * information in the decision logic. Level 5, thus, includes
				 * decision logic to eliminate possible false detection during
				 * the refractory period. However this is not a complete
				 * blanking of a beat during the refractory period, but rather a
				 * partial blanking. If a beat was detected during the
				 * refractory period (with reference to the previous beat
				 * detection) and also had a minimal detection strength in level
				 * 4 then the status of the event is changed from a-beat to
				 * not-a-beat. Note that since level 4 only checks for FN�s, it
				 * is possible for an event to be classified as a beat in level
				 * 3 and not get checked with the threshold in level 4.
				 */

				int r_pos = abs_pos - relative_rpos;
				int interval = r_pos - last_r_pos;

				if (interval < MS220) {

					int min = Integer.MAX_VALUE;
					for (int i = 0; i < last8F3Pts.length; i++)
						min = Math.min(last8F3Pts[i], min);

					if (((min - NL4) / (SL4 - NL4)) < 0.05) {
						// if ( ( (last8F3Pts[6] - NL4) / (SL4 - NL4)) < 0.1 ) {

						classCh4 = -1;
						// System.out.println("Level 5 detected strength " +
						// detStrength4);

						detStrength = 0;

					}

				}

				// System.out.println("Event " + eventCount +
				// " detected with strength " + detStrength4);

			}

		} else {

			// No event detected, revert to DetectorPanTompkinsModified

			classCh1 = 0;
			classCh2 = 0;
			classCh4 = 0;
			delta1 = 0;
			delta2 = 0;
			detStrength = 0;

		}

		/*
		 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! // If had
		 * gotten filtered value, no need to repeat below
		 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		 */

		/*
		 * fdatum = filter.lpfilt(datum, 0); fdatum = filter.hpfilt(fdatum, 0);
		 * 
		 * fdatum = filter.deriv2(fdatum, 0); // Take the derivative. fdatum =
		 * Math.abs(fdatum); // Take the absolute value. fdatum =
		 * filter.mvwint(fdatum, 0); // Average over an 80 ms window .
		 */

		fdatum = filter.getValue(datum);
		// Console.WriteLine(fdatum);

		/*
		 * Save derivative of raw signal for T-wave and baseline shift
		 * discrimination.
		 */

		DDBuffer[DDPtr] = filter.deriv1(datum, 0);
		if (++DDPtr == DER_DELAY)
			DDPtr = 0;

		++count;

		/*
		 * (Repeated from above) Level 3: This level fuses the beat detection
		 * status from each of the 2 one-channel detection algorithms in level 2
		 * by incorporating a set of if-then-else rules. The rules incorporate
		 * the fact that the 2 one- channel detection blocks have complementary
		 * detection rates. There are four possible cases to design rules for.
		 * If both channels indicate a beat then the output of level 3
		 * classifies the current event as a beat. Since Chan2 uses a high
		 * threshold in its detection logic, it generates few FP�s and, thus,
		 * beat detection is very accurate. If both channels indicate not-a-beat
		 * then the output of level 3 is that the current event is not a beat.
		 * Since the threshold used in is very low, it has very few FN�s, and
		 * more than likely a beat did not occur in reality. If Chan1 indicates
		 * not-a-beat and Chan2 indicates a beat, then the output is classified
		 * as a beat. However, this scenario does not occur since, the threshold
		 * used in Chan1 is very low, and the same feature is used in Chan2. A
		 * beat detected by Chan2 more than likely got detected in Chan1. If
		 * Chan1 indicates a beat and Chan2 indicates a not-a-beat, then the
		 * detection strengths from each channel are compared. Chan1 generates
		 * many FP�s but Chan2 generates many FN�s. The normalized detection
		 * strength which indicates which decision was �stronger,� can be
		 * compared to favor the channel with the stronger decision.
		 */

		/*
		 * Test the beat as a QRS complex if Level 3 or Level 4 processing
		 * successful or if the peak is larger than 0
		 */

		if (((classCh1 == 1) && (classCh2 == 1)) || (classCh2 == 1) || ((classCh1 == 1) && (delta1 > delta2))
				|| (classCh4 == 1)) {

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

		/*
		 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! Update
		 * Level 2 variables SL and NL whenever qmean and nmean updated.
		 * Alternatively, if SL = NL, let NL = det_thresh
		 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		 */

		// SL = qmean;
		// NL = nmean;

		if (isFilled == true) {
			SL1 = dmean(s1buffer, 8);
			NL1 = dmean(n1buffer, 8);
			SL2 = dmean(s2buffer, 8);
			NL2 = dmean(n2buffer, 8);
			SL4 = dmean(s4buffer, 8);
			NL4 = dmean(n4buffer, 8);
		}

		// if (SL == NL) NL = det_thresh;
		// if (SL == NL) NL = .5*SL;;
		// if (SL == NL) {SL = 0; NL = 0;}

		return QrsDelay;
	}

	public int getValue(int pending, int datum, long tStamp) {

		return getValue(pending, datum);

    }

	@Override
	public int getValue(int pending, int datum) {

		int threshold = 1;
		int delay = _getValue(datum);

		if (delay > threshold) {
			fireBeatDetection(-1, 0, -1, leadId, 1);
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
				if (interval > MS220) { //MS25) {

					gv_ii.add(r_pos - last_r_pos);

					long r_timestamp= startTime + (r_pos * 1000L) / sampleRate;
					fireRWaveDetection(-relative_rpos, r_pos - last_r_pos, currentMaxR, leadId, 1, r_timestamp);
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

		detStrength = 0;

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

		currentMaxR = 0;
		rrInt = 0;
		abs_pos = 0;
		relative_rpos = 0;
		prev_r = Integer.MIN_VALUE;

		last_r_pos = 0;

		prevSlope = 0; // default slope = 0

		THRESH1 = 0.08;
		THRESH2 = 0.7;
		THRESH4 = 0.3;

		SL1 = 0;
		NL1 = 0;
		SL2 = 0;
		NL2 = 0;
		SL4 = 0;
		NL4 = 0;

		eventCount = 0;

		feature1 = 0;
		feature2 = 0;
		feature3 = 0;

		isFilled = false;
		fillCount = 0;
		s1idx = 0;
		n1idx = 0;
		s2idx = 0;
		n2idx = 0;
		s4idx = 0;
		n4idx = 0;

		for (int i = 0; i < 8; i++) {
			s1buffer[i] = 0;
			n1buffer[i] = 0;
			s2buffer[i] = 0;
			n2buffer[i] = 0;
			s4buffer[i] = 0;
			n4buffer[i] = 0;
		}

		detStrength = 0;
	}

}