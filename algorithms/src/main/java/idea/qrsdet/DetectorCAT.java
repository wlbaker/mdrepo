package idea.qrsdet;

public class DetectorCAT extends AbstractDetector {

	private FilterCAT filter;

	private double m_avg;
	private double r;

	private double[] m = new double[5];
	private int[] rri = new int[5];

	int MS50;
	int MS200;
	int MS350;
	int MS1000;
	int MS1200;
	int MS5000;

	int rslope_start; // 2/3 Rm
	int rslope_width; // from rslope_start to QRS+Rm

	int training;
	int retrigger;
	int mslope_interval;

	double max;
	double mslope_delta;
	double rslope_delta;
	int[][] x = null; // three point history for each lead
	double[] y;
	int y_idx;

	double f;

	long abspos = 0;
	long lastrwave = 0;

	double fdeltaO;
	double fdeltaN;

	private int filter_shift;

	// Date currTimeStamp;

	public DetectorCAT() {
		getConfiguration().setName("DetectorCAT");
	}

	public DetectorCAT(int sampleRate) {
		setSampleRate(sampleRate);
		getConfiguration().setName("DetectorCAT");

	}

	@Override
	public void setSampleRate(int sampleRate) {

		initQrsDetector(sampleRate);

	}

	@Override
	public int getSampleRate() {
		return MS1000;
	}

	public int getValue(int pending, int datum, long tStamp) {

		// currTimeStamp = new Date(tStamp.getTime());
		return getValue(pending, datum);

	}

	@Override
	public int getValue(int pending, int datumm) {

		// currTimeStamp = new Date(timeStamp.getTime());

		int nleads = 1;

		if (x == null) {
			x = new int[1][3];
		}

		abspos++;

		x[0][0] = x[0][1];
		x[0][1] = x[0][2];
		x[0][2] = filter.getValue(datumm);

		double y_curr = 0;
		for (int lead = 0; lead < nleads; lead++) {
			y_curr += Math.abs(x[lead][2] - x[lead][0]);
		}

		// NOTE: see notes in getSignalShift of FilterCAT
		y_curr = filter.lp25filt((int) y_curr);

		y[y_idx++] = y_curr;
		y_idx %= MS350;

		if (y_curr > max) {
			max = y_curr;
		}

		if (training > 0) {
			training--;

			if (training == 0) {

				m[0] = m[1] = m[2] = m[3] = m[4] = (0.6 * max);

				f = 0; // initial F is the average of the Y's over a 350ms
						// interval
				for (int i = 0; i < MS350; i++) {
					f += y[i];
				}
				f /= MS350;
			}

		} else if (retrigger > 0) {
			retrigger--;

			if (retrigger == 0) {
				m[0] = m[1];
				m[1] = m[2];
				m[2] = m[3];
				m[3] = m[4];
				m[4] = (0.6 * max);

				if (m[4] > 1.5 * m[3]) {
					m[4] = 1.1 * m[3];
				}

				// WLB: 03JUN16 if m3 is ever 0, then the m array will
				// reach a permanent state of "0", so just retrain
				if( max == 0 ) {
					// if m3 is ever 0, then 
					training = MS5000;
				}

				max = 0;
				r = 0;

				for (int i = 0; i < 5; i++) {
					m_avg += m[i];
				}
				m_avg /= 5;

				mslope_delta = 0.6 * m_avg / MS1000;
				rslope_delta = mslope_delta / 1.4;

				mslope_interval = MS1000;
			}
		} else {

			f = 0.0;

			double mfr = m_avg + f + r;
			if (y_curr >= mfr) {
				// WE GOT A BEAT
				retrigger = MS200;

				int r_pos = (int) abspos - filter_shift;
				int rr_interval = (int) (abspos - lastrwave);

				if (rr_interval > 4000) {
					// 03JUN16 WLB: although this might be a good idea, it causes
					// the RRI's to not add up to the total length of data.  Hmm.
					System.out.println("[CAT] break/retrain");
				} else {

					rri[0] = rri[1];
					rri[1] = rri[2];
					rri[2] = rri[3];
					rri[3] = rri[4];
					rri[4] = rr_interval;

					{
						long r_timestamp = startTime + (r_pos * 1000L) / MS1000;
						fireRWaveDetection(r_pos, rr_interval, (int) y_curr, leadId, 1, r_timestamp);
					}
				}

				lastrwave = abspos;

				int Rm = 0;
				for (int i = 0; i < 5; i++) {
					Rm += rri[i];
				}
				Rm /= 5;

				rslope_start = 2 * Rm / 3;
				rslope_width = Rm - rslope_start;
			} else if (mslope_interval > 0) {
				m_avg -= mslope_delta;
				mslope_interval--;

				if (rslope_start > 0) {
					rslope_start--;
				} else if (rslope_width > 0) {
					r -= rslope_delta;
					rslope_width--;
				}

			}
		}

		return 0;
	}

	public void initQrsDetector(int sampleRate) {

		filter = new FilterCAT(sampleRate);
		filter_shift = filter.getSignalShift();
		filter.initFilter();

		MS50 = sampleRate / 20;
		MS200 = sampleRate / 5;
		MS350 = MS200 + 3 * MS200 / 4;
		MS1000 = sampleRate;
		MS1200 = sampleRate + MS200;
		MS5000 = sampleRate * 5;

		retrigger = 0;
		training = MS5000;

		abspos = 0;
		lastrwave = 0;

		y = new double[MS350];
	}

	@Override
	public void restartDetector() {
		startTime = 0;
		nextBlockTime = 0;
		startTimeInitialized = false;

		m_avg = 0;
		r = 0;

		m = new double[5];
		rri = new int[5];
		
		training = MS5000;

		retrigger = 0;
		y_idx = 0;

		abspos = 0;
		lastrwave = 0;

		y = new double[MS350];
	}

}