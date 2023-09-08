package idea.analysis;

/*
 * Notes and considerations:
 * 
 *  Ward uses embedding dimension of 2 always, and usually phase shift of 4.
 *  
 *  IOTA should always be at least as large as the measurement error.  500Hz is 2ms.  The algorithm 
 *  currently uses Ward's approach and assumes log(distance) for a perfect match is 0.
 *  
 *  Rosenstein marks nearest neighbors and tries to avoid duplication calculations using the isNeighbor array,
 *  while Ward doesn't avoid reuse of orbits.  Rosenstein's method is not 100% effective.  But it does cut 
 *  computation substantially.
 *  
 *  Ward's phase shift of 4 is Rosenstein's lag (J) of 3.  Ward's phase shift of 10 is Rosenstein's lag of 9.
 *  
 *  Backwards for the exclusion window.  Ward's window of 25 is my windows of 26.
 *  
 */

import idea.conf.DeviceCapabilities;
import idea.intf.AbstractStreamProducer;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.Alarm;
import idea.model.IntfUtil;
import idea.model.PersistentItem;

import java.io.FileNotFoundException;
import java.io.PrintStream;

import lombok.extern.slf4j.Slf4j;
import idea.analysis.event.LyaBlock;
import idea.buffer.SignalBuffer;

@Slf4j
public class LyaProcessor extends AbstractStreamProducer implements StreamConsumer {

	public static final double IIOTA = 10e-15;
	// public static final double IIOTA = 10e-3;
	// public static final double IOTA = 10e-15;
	public static final int MAX_LN_R = 12;
	public static final int MIN_LN_R = -12;
	public static final int N_LN_R = 600;

	public int verbose = 0;

	int divergeT;
	double[] gDivergence;
	public double[] gCSum;
	int[] gNDivergence; // count of matches? mostly linearly decreasing...hmmm
	// LyaParams parms;

	// double lineSlope;
	double b, rr;
	int last = 100; // used to measure pct done
	private int m;
	private int window;
	private String loc;
	private int lastCalcIdx = 0;
	private int currIdx = 0;

	SignalBuffer<Number> signal;
	double[] gData;

	private int nPts;
	private int W;
	private int J;
	private double dt;

	/**
	 * 
	 * Constructor for the Lyapunov processor.
	 * 
	 * @param nPts
	 *            The number of points to consider in our dataset.
	 * @param slidingWindowIncrement
	 *            The Lyapunov is recomputed after this many new signal points
	 *            have been added.
	 * @param divergeT
	 *            Maximum distance to follow the divergence.
	 * @param embedding
	 *            Number of embedding dimensions. Vector length.
	 * @param exclusionWindow
	 *            Number of points to ignore around the initial point before
	 *            finding the nearest neighbor. In the literature, this should
	 *            be greater than the mean period.
	 * @param lag
	 *            Number of points to skip between samples to construct the
	 *            phase vector. Denoted as J in the literature. Usually 1.
	 * @param loc
	 *            The signal analyze from the multiple signals provided in the
	 *            signal source. Corresponds to "series#" in the Rossler
	 *            article.
	 */

	LyaBlock block;

	double lineErr = 0.0;

	public LyaProcessor() {
		this( 500, 1, 50, 100, 2, 10, 1, null );
		log.warn("default lya initialization");
	}
	
	public LyaProcessor(int nPts) {
		this( nPts, 1, 50, 100, 2, 10, 1, null );
		log.warn("default lya initialization w pts");
	}
	
	public LyaProcessor(int nPts, double dt) {
		this( nPts, dt, 50, 100, 2, 10, 1, null );
		log.warn("default lya initialization w pts and dt");
	}
	
	public LyaProcessor(int nPts, double dt, int slidingWindowIncrement, int divergeT, int embedding,
			int exclusionWindow, int lag) {
		this( nPts, dt, slidingWindowIncrement, divergeT, embedding, exclusionWindow, lag, null);
	}
	
	public LyaProcessor(int nPts, double dt, int slidingWindowIncrement, int divergeT, int embedding,
			int exclusionWindow, int lag, String loc) {
		this.m = embedding;
		this.window = slidingWindowIncrement;
		this.loc = loc;
		this.nPts = nPts;
		this.dt = dt;
		this.W = exclusionWindow;
		this.J = lag;
		this.divergeT = divergeT;

		reset();


		block = new LyaBlock();

	}

	public void reset() {
		gData = new double[nPts];
		signal = new SignalBuffer<Number>(nPts, true);
		gNDivergence = new int[divergeT];
		gDivergence = new double[divergeT]; // save lyapunov and
		gCSum = new double[N_LN_R];

		last = 100; // used to measure pct done
		lastCalcIdx = 0;
		currIdx = 0;
	}

	private void computeCorrelationDimSlopes_unchecked() {
		int i, j;
		double k;
		double[] data;

		data = new double[N_LN_R > divergeT ? N_LN_R : divergeT];

		i = 0;

		/*** work on correlation dimension first ***/

		k = (double) N_LN_R / (MAX_LN_R - MIN_LN_R);

		/* pack the array column into the local data array */
		for (j = 0; j < N_LN_R; j++)
			data[j] = gCSum[j];
		/* compute the 7-point slopes */
		for (j = 3; j < N_LN_R - 3; j++) {
			double slope = LineFit(data, j - 3, 7);
			gCSum[j] = k * slope;
		}

		/* handle the edges */
		gCSum[2] = k * LineFit(data, 0, 5);
		gCSum[N_LN_R - 3] = k * LineFit(data, N_LN_R - 5, 5);
		gCSum[1] = k * LineFit(data, 0, 3);
		gCSum[N_LN_R - 2] = k * LineFit(data, N_LN_R - 3, 3);
		gCSum[0] = k * (data[1] - data[0]);
		gCSum[N_LN_R - 1] = k * (data[N_LN_R - 1] - data[N_LN_R - 2]);

		/*** now work on divergence data ***/

		/* pack the array column into the local data array */
		for (j = 0; j < divergeT; j++)
			data[j] = gDivergence[j];
		/* compute the 7-point slopes */
		for (j = 3; j < divergeT - 3; j++) {
			gDivergence[j] = LineFit(data, j - 3, 7);
		}
		/* handle the edges */

		gDivergence[2] = LineFit(data, 0, 5);
		gDivergence[divergeT - 3] = LineFit(data, divergeT - 5, 5);
		gDivergence[1] = LineFit(data, 0, 3);
		gDivergence[divergeT - 2] = LineFit(data, divergeT - 3, 3);
		gDivergence[0] = data[1] - data[0];
		gDivergence[divergeT - 1] = data[divergeT - 1] - data[divergeT - 2];

	}

	private double LineFit(double[] ddata, int offset, double n) {
		double sx, sy, sxy, sx2, sy2;
		double x, y, k, slope, bTemp, rrTemp;

		sx = sy = sxy = sx2 = sy2 = 0;
		for (int i = 0; i < n; i++) {
			x = i;
			y = ddata[i + offset];
			sx += x;
			sy += y;
			sx2 += x * x;
			sy2 += y * y;
			sxy += x * y;
		}
		;
		k = n * sx2 - sx * sx;
		slope = (n * sxy - sx * sy) / k;
		bTemp = (sx2 * sy - sx * sxy) / k;
		k = sy * sy / n;
		if (k == sy2)
			rrTemp = 1.0;
		else {
			rrTemp = (bTemp * sy + slope * sxy - k) / (sy2 - k);
			rrTemp = 1.0 - (1.0 - rrTemp) * (n - 1.0) / (n - 2.0);
		}
		;
		b = bTemp;
		rr = rrTemp;

		lineErr = 0.0;
		for (int i = 0; i < n; i++) {
			double y0 = ddata[i];
			double y1 = m * i + b;

			double delta = (y0 - y1);
			lineErr += delta * delta;
		}
		lineErr = Math.sqrt(lineErr) / n;

		return slope;
	}

	void lyaPercentDone(int percentDone) {

		if (percentDone < last) {
			last = 0;
			System.out.print("0");
			System.out.flush();
		} else if (percentDone > last && percentDone % 2 == 0) {
			last = percentDone;
			if (percentDone % 10 == 0)
				System.out.format("%d", percentDone / 10);
			else
				System.out.print(".");

			if (percentDone == 100) {
				System.out.println();
			}

			System.out.flush();
		}
	}

	public double lyaProcessTest() {
		return lyaProcessTest(gData);
	}

	public double lyaProcessTest(double[] gData) {
		int neighborIndex, maxIndex;
		int i, j, k, T, CSumIndex, percentDone;
		int nCompletedPairs = 0, nVectors;
		byte[] isNeighbor;
		double distance, d;
		double k1, k2, temp, kNorm;

		k1 = (double) N_LN_R / (MAX_LN_R - MIN_LN_R);
		k1 *= 0.5; /* accounts for the SQUARED distances later on */
		k2 = N_LN_R / 2;

		nVectors = nPts - J * (m - 1);

		isNeighbor = new byte[nVectors];
		neighborIndex = 0; // uninitialized in original algorithm?

		/* clear the divergence arrays */
		for (i = 0; i < divergeT; i++) {
			gNDivergence[i] = 0;
			gDivergence[i] = 0;
		}

		/* loop through vectors */
		i = 0;
		last = 0;
		while (i < nVectors) {

			percentDone = (int) (100.0 * nCompletedPairs / nVectors * 2 + 0.5);
			percentDone = (int) (100.0 * i / nVectors + 0.5);
			if (verbose > 0) {
				lyaPercentDone(percentDone);
			}

			if (verbose > 8) {
				System.out.print("\nfinding neighbor for " + i + " vector[ ");
				for (k = 0; k < m; k++) {
					T = k * J;
					System.out.print(gData[i + T] + ",");
				}
				System.out.println("]");
			}

			if (isNeighbor[i] == 0) {
				distance = 10e10;

				/* find the nearest neighbor for the vector at i */
				/* ignore temporally close neighbors using W */
				if (i > W)
					for (j = 0; j < i - W; j++) {
						/* calculate distance squared */
						d = 0;
						for (k = 0; k < m; k++) {
							T = k * J;
							temp = gData[i + T] - gData[j + T];
							temp *= temp;
							d += temp;
						}

						/* map the squared distance to array position */
						if (d > IIOTA) {
							CSumIndex = (int) (k1 * Math.log(d) + k2);
							if (CSumIndex < 0)
								CSumIndex = 0;
							if (CSumIndex >= N_LN_R) {
								CSumIndex = N_LN_R - 1;
							}
							/* increment the correlation sum array */
							gCSum[CSumIndex]++;
						}

						/* now compare to current nearest neighbor */
						/* use IOTA above to ignore nbrs that are too close */
						if (d < distance) {
							if (verbose > 1) {
								System.out.format("   Candidate nearest neighbor of %d: %d dist=%6f\n", i, j, Math.pow(
										d, 0.5));
							}
							distance = d;
							neighborIndex = j;
						}
					}

				if (i < nVectors - W) {
					for (j = i + W; j < nVectors; j++) {
						d = 0;
						for (k = 0; k < m; k++) {
							T = k * J;
							temp = gData[i + T] - gData[j + T];
							temp *= temp;
							d += temp;
						}

						if (d > IIOTA) {
							CSumIndex = (int) (k1 * Math.log(d) + k2);
							if (CSumIndex < 0)
								CSumIndex = 0;
							if (CSumIndex >= N_LN_R)
								CSumIndex = N_LN_R - 1;
							gCSum[CSumIndex]++;
						}

						if (d < distance) {
							if (verbose > 1) {
								System.out.format("   xcl-neighbor: %d  distance=%6f", j, d);
								System.out.println();
							}
							distance = d;
							neighborIndex = j;

						}
					}
				}

				isNeighbor[neighborIndex] = 1;

				if (verbose > 1) {
					System.out.format("   Nearest Neighbor %d: %d dist=%6f\n", i, neighborIndex, distance);
				}

				for (j = 0; j < divergeT; j++) {
					maxIndex = nPts - m * J - j - 1;

					if (i < maxIndex && neighborIndex < maxIndex) {
						d = 0;
						for (k = 0; k < m; k++) {
							T = k * J + j;
							temp = gData[i + T] - gData[neighborIndex + T];
							temp *= temp;

							d += temp;
						}

						gNDivergence[j]++;
						if (d > IIOTA) {
							temp = 0.5 * Math.log(d);
							gDivergence[j] += temp;
						} else {
							temp = 0;
						}

						if (verbose > 1) {
							System.out.format("    div += %6f", temp);
							System.out.format("  gNDiverge[%d]=%d", j, gNDivergence[j]);
							System.out.format(" gDivergence[%d]=%6f", j, gDivergence[j]);
							System.out.println();
						}

					}

					if (verbose > 3) {
						System.out.println();
					}

				}

				nCompletedPairs++;
			}

			i++;
		}

		/* integrate the correlation sum array to get the correlation sum curve */
		for (i = 1; i < N_LN_R; i++)
			gCSum[i] += gCSum[i - 1];

		/* next normalize values */
		kNorm = 1.0 / gCSum[N_LN_R - 1];
		for (i = 0; i < N_LN_R; i++)
			gCSum[i] *= kNorm;

		/* now take natural log of the values */
		for (i = 0; i < N_LN_R; i++) {
			temp = gCSum[i];
			if ((temp < 0.000045) || (temp > 0.990050))
				gCSum[i] = 0;
			else
				gCSum[i] = Math.log(temp);
		}

		/* now take care of Lyapunovv average */
		// BLIND: again why <= and not strictly <??? for (i = 0; i <= divergeT;
		// i++)
		for (i = 0; i < divergeT; i++)
			if (gNDivergence[i] > 0)
				gDivergence[i] /= gNDivergence[i];

		if (verbose > 1) {
			System.out.println("first 50 divergence");
			for (i = 0; i < 50; i++) {
				System.out.format("  %d: %f", i, gDivergence[i]);
			}
			System.out.println();
		}

		double l0Slope = calculateSlope(0);

		block.setLya(l0Slope / dt);
		block.setDivlen(divCount);
		block.setDivergence(divValue);
		block.setErr(lineErr);

		double l2Slope = calculateSlope(2);
		block.setLya2(l2Slope / dt);

		return l0Slope / dt;
	}

	Double divValue;
	int divCount;

	private double calculateSlope(int offset) {
		divCount = 0;
		divValue = null;

		Double mavgFirst = null;
		double mavgCurr = 0;
		double mavgPrev;

		int FILTER_SIZE = 20; // 3; // 20;
		int MIN_PTS = 12; // 2; // 12;

		// I need three moving average points: the first one, the current one,
		// and the prev one
		for (divCount = 0; divCount < gDivergence.length - FILTER_SIZE; divCount++) {
			mavgPrev = mavgCurr;
			mavgCurr = 0;
			for (int j = 0; j < FILTER_SIZE; j++) {
				mavgCurr += gDivergence[j + divCount];
			}
			mavgCurr /= FILTER_SIZE;

			if (mavgFirst == null) {
				mavgFirst = mavgCurr;
			} else if (divCount > MIN_PTS) {
				if (Math.abs(mavgCurr - mavgPrev) < 0.0005) {
					divValue = mavgCurr;
					break;
				}
			}
		}
		
		// divCount = offset + 4;

		// System.out.println( "DIVCOUNT=" + divCount + " ASYMPTOTE=" + mavgCurr
		// + " POINT=" + THISPOINT );

		// Find the slope.
		double SumX = 0;
		double SumY = 0;
		double SumX2 = 0;
		double SumXY = 0;
		for (int Counter = 0; Counter < divCount; Counter++) {
			double X = Counter;
			double Y = gDivergence[Counter];
			SumX += X;
			SumY += Y;
			SumX2 += (X * X);
			SumXY += (X * Y);
		}
		double X = SumX / divCount;
		double Y = SumY / divCount;
		double Sxx = SumX2 - (SumX * SumX) / divCount;
		double Sxy = SumXY - (SumX * SumY) / divCount;

		double Slope = 0;
		if (Sxx != 0)
			Slope = Sxy / Sxx;
		// unused double Intercept = Y - Slope * X;

		/*
		 * find the error
		 */
		double[] ddata = new double[divCount];
		for (int i = 0; i < divCount; i++) {
			ddata[i] = gDivergence[i + offset];
		}
		double lineSlope = LineFit(ddata, 0, divCount);

		// System.out.println( "WARD: " + Intercept + " slope=" + Slope );
		// System.out.println( "Rossler: " + b + " slope=" + lineSlope + " RR="
		// + rr + " err=" + lineErr );
		//	     
		// THISPOINT++;
		//	     
		// if( THISPOINT == 770 || THISPOINT == 500 ) {
		// System.out.println( "STOPPED HERE");
		// }
		
		return lineSlope;
	}

	public void saveL1Results(String fileRoot) throws FileNotFoundException {

		System.out.format("\nSaving data for largest Lyapunov exponent...\n");

		String fileName = fileRoot + ".l1";

		PrintStream out = new PrintStream(fileName);

		int idx = 0;

		for (int i = 0; i < divergeT; i++) {
			int testN = 0;
			out.format("%d\t", gNDivergence[i]);
			out.format("%6.3f\t", gDivergence[i]);
			// out.print( "\t" );
			out.println();
		}

		out.close();

	}

	public Double add(long tm, Number rPos) {
		Double val = null;
		synchronized (signal) {
			signal.addData(rPos);
			currIdx++;
		}
		if (signal.getSampleCount() >= nPts && currIdx - lastCalcIdx >= window) {

			for (int i = 0; i < nPts; i++) {
				gData[i] = signal.get(i).doubleValue();
			}
			val = lyaProcessTest();

			if (val != null) {
				block.setTime(tm);
				if (val != null) {
					fireStreamEvent(0,this,StreamID.MEASUREMENT, block);

				} else {
					if (verbose > 0) {
						System.out.println("   lyapunov progress: " + signal.getSampleCount() + " out of " + nPts);
					}

					if (signal.getSampleCount() < nPts) {
						Alarm ai = new Alarm("sample", Alarm.INFO, 0, "Waiting: " + signal.getSampleCount() + " out of " + nPts, true);
						fireAlarmEvent(this, ai);
					}

				}

			}
			lastCalcIdx = currIdx;
		}
		return val;
	}

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {
		if (sid == StreamID.MEASUREMENT) {
			Number value = IntfUtil.getScaledValueByLoc(item,loc);

			Double val = add(item.getTime(), value );

		}

	}

	@Override
	public DeviceCapabilities getStaticCapabilities() {
		// TODO Auto-generated method stub
		return null;
	}

	public double getDivergenceAsymptote() {
		return block.getDivergence();
	}

	public double[] getDivergenceCurve() {
		return gDivergence;
	}

	public int getN() {
		return nPts;
	}

	public int getW() {
		return W;
	}
	public int getJ() {
		return J;
	}
	
	public int getM() {
		return m;
	}
	
	public int getDivergeT() {
		return divergeT;
	}
	
	public void setN( int nPts ) {
		this.nPts = nPts;
	}

	public void setW(int W) {
		this.W = W;
	}
	public void setJ(int J) {
		this.J = J;
	}
	
	public void setM(int m) {
		this.m = m;
	}
	
	public void setDivergeT(int T) {
		this.divergeT = T;
	}

}
