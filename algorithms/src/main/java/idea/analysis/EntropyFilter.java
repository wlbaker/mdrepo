package idea.analysis;

import icuInterface.events.NumericsEvent;
import idea.conf.DeviceCapabilities;
import idea.conf.DeviceConfiguration;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.Alarm;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.schema.rp.RpAnalysis;

import java.io.PrintStream;
import java.util.Date;

import idea.Stats;
import idea.analysis.event.BeatBlock;
import idea.analysis.event.BeatEvent;
import idea.analysis.event.EntropyBlock;
import idea.analysis.event.RWaveEvent;
import idea.analysis.event.SBCO2Block;
import idea.buffer.SignalBuffer;

class EntPoint {
	protected double entropy;
	protected int[] A;
	protected int[] B;
}

public class EntropyFilter extends AbstractAnalysisProcessor {


	private static final RpAnalysis analysisInfo;
	private static DeviceCapabilities caps;
	
	static { 
		analysisInfo = new RpAnalysis();
		analysisInfo.setName("Sample Entropy");
		analysisInfo.setAnalysisClass( EntropyFilter.class.getCanonicalName() );
		
		caps = new DeviceCapabilities(EntropyFilter.class);
		caps.addStream( StreamID.MEASUREMENT, EntropyBlock.class);
		caps.setName("SAMPEN");
	}

	public static int verbose = 0;
	private SignalBuffer<Integer> rri;

	double r;
	int maxEpoch;

	private int recalc_period;
	private long recalc_last;
	private boolean did_alarm;

	public static double SaEn(double[] signal, double r, int m) {

		Double[] d = new Double[signal.length];
		if (verbose > 0) {
			System.err.println("NEED TO FIX: conversion from double[] to Double[] not necessary");
		}
		for (int i = 0; i < signal.length; i++) {
			d[i] = signal[i]; // autobox
		}

		SignalBuffer<Double> sig = new SignalBuffer<Double>(d, true);

		return SaEn(sig, r, m);
	}

	public static double SaEn(SignalBuffer<? extends Number> signal, double r, int m) {
		return SaEn(signal, r, m, signal.getSampleCount());
	}

	public static double SaEn(SignalBuffer<? extends Number> signal, double r, int m, int sampleCount) {
		return sampen(signal, r, m, sampleCount).entropy;
	}

	public static EntPoint SaEnX(SignalBuffer<? extends Number> signal, double r, int m, int sampleCount) {
		return sampen(signal, r, m, sampleCount);
	}

	// public static double ApEn(double[] signal, double r, int m) {
	//
	// double prob;
	// StatPoint pt = new StatPoint();
	//
	// pt = EntropyProcessor.pMatch(signal, r, m, signal.length);
	// pt.a = 2 * pt.a + (signal.length - m + 1);
	// pt.b = 2 * pt.b + (signal.length - m + 1);
	// prob = pt.b / pt.a;
	//
	// pt = EntropyProcessor.pMatch(signal, r, m + 1, signal.length);
	// pt.a = 2 * pt.a + (signal.length - m);
	// pt.b = 2 * pt.b + (signal.length - m);
	// prob = prob / (pt.b / pt.a);
	//
	// return Math.log(prob);
	// }

	private static EntPoint sampen(SignalBuffer<? extends Number> y, double r, int M, int n) {
		double entropy = Double.MIN_VALUE;

		long N;
		int M1, j, nj, jj, m;
		// int i;
		double y1;

		M++;
		int[] run = new int[n];
		int[] lastrun = new int[n];
		int[] A = new int[M];
		int[] B = new int[M];
		double[] p = new double[M];

		if (r < 0) {
			double sd = Stats.getStandardDeviation(y);
			r = -sd * r;
		}

		PrintStream out = System.out;
		/* start running */
		for (int i = 0; i < n - 1; i++) {
			nj = n - i - 1;
			y1 = y.get(i).doubleValue();

			// out.format("outer loop: i=%d, nj=%d, y1=%f\n", i, nj, y1);

			for (jj = 0; jj < nj; jj++) {
				j = jj + i + 1;
				double y_j = y.get(j).doubleValue();

				if (((y_j - y1) < r) && ((y1 - y_j) < r)) {
					run[jj] = lastrun[jj] + 1;
					M1 = M < run[jj] ? M : run[jj];

					// out.format(" match at (%d,%d)  M1=%d\n", i, jj, M1);
					for (m = 0; m < M1; m++) {
						A[m]++;
						if (j < n - 1)
							B[m]++;
					}
				} else
					run[jj] = 0;
			} /* for jj */
			for (j = 0; j < nj; j++)
				lastrun[j] = run[j];
		} /* for i */

		N = n * (n - 1) / 2;
		p[0] = ((double) A[0]) / N;

		entropy = -Math.log(p[0]);
		// out.format("SampEn(0,%g,%d) = %f\n", r, n, entropy);

		for (m = 1; m < M; m++) {
			p[m] = A[m] / (double) B[m - 1];
			if (p[m] == 0) {
				entropy = -1;
				if (verbose > 0) {
					out.format("No matches! SampEn((%d,%g,%d) = Inf!\n", m, r, n);
				}
			} else {
				entropy = -Math.log(p[m]);
				if (verbose > 0) {
					out.format("SampEn(%d,%g,%d) = %f\n", m, r, n, entropy);
				}
			}
		}

		EntPoint ep = new EntPoint();
		ep.A = A;
		ep.B = B;
		ep.entropy = entropy;

		return ep;
	}

	public EntropyFilter(int count) {
		this(count, -0.2, 2);
	}

	public EntropyFilter(int count, double r, int maxEpoch) {
		rri = new SignalBuffer<Integer>(count, true);
		this.r = r;
		this.maxEpoch = maxEpoch;

	}



	public void addOneRWave(long tm, int val) {

		//		{
		//			System.out.print("ent* ");
		//			Date dt = new Date(tm);
		//			SimpleDateFormat fmt = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		//			System.out.println(fmt.format(dt));
		//		}
		rri.addData(val);

		if (rri.getSampleCount() < rri.getBufferSize()) {
			did_alarm = true;
			Alarm ai = new Alarm("sampen", Alarm.INFO, 0, "Waiting: " + rri.getSampleCount() + " / "
					+ rri.getBufferSize(), true);
			ai.setTm( new Date(tm) );
			fireAlarmEvent(this, ai);
			return;
		}

		boolean process_flag;
		if (recalc_period <= 0 || recalc_last == 0) {
			process_flag = true;
		} else {
			process_flag = (tm - recalc_last > recalc_period);
		}

		if (process_flag) {
			if (did_alarm) {
				Alarm ai = new Alarm("sampen", Alarm.CLEAR, 0, "", true);
				ai.setTm( new Date(tm) );
				fireAlarmEvent(this, ai);
				did_alarm = false; // clear the alarm
			}
			recalc_last = tm;
			EntropyBlock entBlock = process(rri, r, maxEpoch);
			entBlock.setDriver(this);
			entBlock.setTm(new Date(tm));

			fireStreamEvent(0, this, StreamID.MEASUREMENT, entBlock);
		}
	}

	public static EntropyBlock process(SignalBuffer<? extends Number> rri, double r, int epoch) {

		double mean = 0.0;
		double variance = 0.0;

		int length = rri.getSampleCount();

		for (int i = 0; i < length; ++i) {
			mean += rri.get(i).doubleValue();
		}
		mean /= length;

		for (int i = 0; i < length; ++i) {
			double d = rri.get(i).doubleValue() - mean;
			variance += (int) (d * d);
		}
		variance /= (length - 1);

		double sd = Math.sqrt(variance);

		EntropyBlock entBlock = new EntropyBlock();

		double rr = r;
		if (r < 0) {
			rr = -sd * r;
		}

		EntPoint ep = EntropyFilter.SaEnX(rri, rr, epoch, rri.getSampleCount());

		entBlock.setA(ep.A);
		entBlock.setB(ep.B);

		entBlock.setSampEnt((int) (100 * ep.entropy));
		entBlock.setStddev((int) (100 * sd));
		entBlock.setAppxent( -1 );
		entBlock.setMean((int) (100 * mean));
		entBlock.setTolerance((int) (100 * rr));

		double q;
		if (ep.entropy < 0) {
			q = -1; // if no entropy value recorded, don't record a Q either
		} else if (r > 0) {
			q = ep.entropy + Math.log(r);
		} else {
			q = ep.entropy + Math.log(-2 * r) + Math.log(sd);
		}
		entBlock.setQse((int) (100 * q));

		return entBlock;
	}

	@Override
	public DeviceConfiguration getConfiguration() {
		return caps;
	}
	

	@Override
	public DeviceCapabilities getStaticCapabilities() {
		return caps;
	}

	@Override
	void reset() {
		if (rri != null) {
			rri.clear();
		}
	}

	public void setRecalcPeriod(int msec) {
		recalc_period = msec;
	}

	public SignalBuffer<Integer> getRRIs() {
		return rri;
	}

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {
		
		if (sid == StreamID.MEASUREMENT) {

			if (item instanceof SBCO2Block) {
				SBCO2Block sb = (SBCO2Block) item;
				int val = -1; // sb.whatever
				addOneRWave(IntfUtil.getTime(item), val);
			} else {
				BeatBlock block = (BeatBlock)item;
				// since r in ms, use rri in ms!
				int val = block.getMs_interval();

				addOneRWave(IntfUtil.getTime(block), val);
			}

		} else if (sid == StreamID.WAVEFORM) {
			
			// ignore
		}

	}
}
