package idea.qrsdet;

import java.util.LinkedList;
import java.util.List;

public class DetectorFixedWidth extends AbstractDetector {

	/**
	 * The major differences between this algorithm and the algorithm implemented in
	 * DetectorPanTompkinsModified.java include the following:
	 * 
	 * 1. Only low-pass and high-pass filters applied to the data 2. Buffers of past
	 * eight frequency samples used to compute decimated sub-band feature signals 3.
	 * Detection strengths used to threshold feature signal samples 4. Octave signal
	 * processing employed, if necessary
	 * 
	 * This algorithm employs the strengths of the Modified Pan-Tompkins algorithm,
	 * including filters and the search-back technique for peaks/thresholds.
	 */

	/* Variables duplicated from DetectorPanTompkins.java */

	private int sampleRate; /* Sample rate in Hz. */
	private double MS_PER_SAMPLE;
	private int MS1000;

	// final static double TH = 0.3125;
	final static double TH = 0.3125;

	int abs_pos;
	int relative_rpos;

	public DetectorFixedWidth(int sr) {
		setSampleRate(sr);
	}

	@Override
	public void setSampleRate(int sr) {
		sampleRate = sr; /* Sample rate in Hz. */
		MS_PER_SAMPLE = ((double) 1000 / (double) sampleRate);
		MS1000 = sampleRate;

		restartDetector();
	}

	// / <summary>
	// main find value
	// / </returns>

	List<Integer> gv_ii = new LinkedList<Integer>(); // must go in the init
														// block

	public int getValue(int pending, int datum, long tStamp) {

		return datum;

	}

	@Override
	public int getValue(int pending, int datum) {

		abs_pos++;
		relative_rpos++;
		
		if (relative_rpos > MS1000) {
			long r_timestamp = startTime + (abs_pos * 1000L) / sampleRate;
			fireRWaveDetection(-relative_rpos, MS1000, 1, 1, 1, r_timestamp);
			relative_rpos = 0;
		}

		return 0;
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

		abs_pos = 0;
		relative_rpos = 0;
	}

}