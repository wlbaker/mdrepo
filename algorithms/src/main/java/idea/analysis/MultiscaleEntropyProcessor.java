package idea.analysis;

import idea.conf.DeviceCapabilities;
import idea.conf.DeviceConfiguration;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.Alarm;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.schema.rp.RpAnalysis;

import java.util.Date;

import idea.Stats;
import idea.analysis.event.BeatBlock;
import idea.analysis.event.MSEBlock;
import idea.buffer.SignalBuffer;

public class MultiscaleEntropyProcessor extends AbstractAnalysisProcessor implements StreamConsumer {

	private static final RpAnalysis analysisInfo;
	static { 
		analysisInfo = new RpAnalysis();
		analysisInfo.setName("Multiscale Entropy");
		analysisInfo.setAnalysisClass( MultiscaleEntropyProcessor.class.getCanonicalName() );
		// analysisInfo.
	}

	private static double DEFAULT_TOLERANCE = 6;

	/* Global variables */

	private SignalBuffer<Number> rri;

	private double tolerance;

	private DeviceCapabilities caps;

	private int recalc_period;

	private long recalc_last;

	private boolean did_alarm;

	public static double process(double[] rri, int scale, double r, int m) {

		/* Memory allocation. */
		double[] y = new double[rri.length / scale]; // NOT RIGHT

		return process(rri, scale, r, m, y);
	}

	public static double process(int[] rri, int scale, double r, int m) {

		/* Memory allocation. */
		double[] y = new double[rri.length / scale]; // NOT RIGHT

		return process(rri, scale, r, m, y);
	}

	public static double process(int[] rri, int scale, double r, int m, double[] coarse_buf) {


		/* Process a single data file. */


		/* Perform the coarse-graining procedure. */
		int y_tot = CoarseGraining(rri, scale, coarse_buf);

		if (r < 0) {
			double sd;
			/* Calculate standard deviation. */
			sd = Stats.sd(rri);
			r = -sd * r;
		}
		/* Calculate SampEn for each scale and each r value. */
		double se = SampleEntropy(r, scale, m, coarse_buf, y_tot);

		/* Print results. */
		// PrintResults(scale);
		// System.out.println( "MSE scale=" + scale + " processing w r=" + r + " se=" + se );

		return se;
	}

	public static double process(double[] rri, int scale, double r, int m, double[] coarse_buf) {

		double sd;

		/* Process a single data file. */

		/* Calculate standard deviation. */
		sd = Stats.sd(rri);

		/* Perform the coarse-graining procedure. */
		int y_tot = CoarseGraining(rri, scale, coarse_buf);

		if (r < 0) {
			r = -sd * r;
		}
		/* Calculate SampEn for each scale and each r value. */
		double se = SampleEntropy(r, scale, m, coarse_buf, y_tot);

		/* Print results. */
		// PrintResults(scale);

		return se;
	}

	private static int CoarseGraining(int[] rri, int scale, double[] y) {
		int i, k;

		int tot = rri.length / scale;
		for (i = 0; i < tot; i++) {
			y[i] = 0;
			for (k = 0; k < scale; k++)
				y[i] += rri[i * scale + k];
			y[i] /= scale;
		}

		return tot;
	}

	private static int CoarseGraining(double[] rri, int scale, double[] y) {
		int i, k;

		int tot = rri.length / scale;
		for (i = 0; i < tot; i++) {
			y[i] = 0;
			for (k = 0; k < scale; k++)
				y[i] += rri[i * scale + k];
			y[i] /= scale;
		}

		return tot;
	}

	private static double SampleEntropy(double r, int scale, int m_max, double[] y, int y_tot) {
		int i, k, l, nlin_j;
		int[] cont = new int[m_max + 2];

		nlin_j = y_tot - m_max;

		for (i = 0; i < m_max; i++)
			cont[i] = 0;

		for (i = 0; i < nlin_j; ++i) {
			for (l = i + 1; l < nlin_j; ++l) { /* self-matches are not counted */
				k = 0;
				while (k < m_max && Math.abs(y[i + k] - y[l + k]) <= r)
					cont[++k]++;
				if (k == m_max && Math.abs(y[i + m_max] - y[l + m_max]) <= r)
					cont[m_max + 1]++;
			}
		}

		double se;

		// for (i = 1; i <= m_max; i++) {
		i = m_max;
		if (cont[i + 1] == 0 || cont[i] == 0)
			se = -Math.log((double) 1 / ((nlin_j) * (nlin_j - 1)));
		else
			se = -Math.log((double) cont[i + 1] / cont[i]);
		// }
		return se;
	}

	void PrintResults(double[][] SE, int scale, int c, int m_min, int m_max, int m_step, double r_min, double r_step) {
		int m, k;

		System.out.print("\n");
		for (m = m_min; m <= m_max; m += m_step)
			for (k = 0; k < c; k++) {
				System.out.format("\nm = %d,  r = %.3f\n\n", m, r_min + k * r_step);

				System.out.format("scale %d\t", scale);
				System.out.format("%.3f\t", SE[k][m]);
				System.out.print("\n");

			}
	}

	/* ********************************************************************************
	 * 
	 * BAD PRACTICE...this is really two classes in one
	 * 
	 * 
	 * **************************************************************************
	 * *****
	 */

	public MultiscaleEntropyProcessor() {
		this(800, DEFAULT_TOLERANCE, 2);
	}

	public MultiscaleEntropyProcessor(int count, double rfactor, int maxEpoch) {
		rri = new SignalBuffer<Number>(count, true);
		this.tolerance = rfactor;

		caps = new DeviceCapabilities(this.getClass() );
		caps.setName("MSE");
		caps.addStream(StreamID.MEASUREMENT, MSEBlock.class );
	}

	public void setRRI(SignalBuffer<Number> rri) {
		this.rri = rri;
	}

	public void addData(int[] vals) {
		System.err.println("FIXME: THIS IS A BAD SOLUTION FOR A LIMITATION OF GENERICS!");

		Integer[] i_vals = new Integer[vals.length];
		for (int i = 0; i < vals.length; i++) {
			i_vals[i] = vals[i];
		}
		rri.addData(i_vals);
	}

	public void addData(double[] vals) {
		System.err.println("FIXME: THIS IS A BAD SOLUTION FOR A LIMITATION OF GENERICS!");

		Integer[] i_vals = new Integer[vals.length];
		for (int i = 0; i < vals.length; i++) {
			i_vals[i] = (int) vals[i];
		}
		rri.addData(i_vals);
	}

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {

		if (item instanceof BeatBlock) {

			BeatBlock inblock = (BeatBlock) item;
			long tm = IntfUtil.getTime(inblock);

			int val = inblock.getMs_interval();
			rri.addData(val);

			if (rri.getSampleCount() < rri.getBufferSize()) {
				did_alarm = true;
				Alarm ai = new Alarm("mse", Alarm.INFO, 0, "Waiting: " + rri.getSampleCount() + " / " + rri.getBufferSize(), true);
				ai.setTm( item.getTm() );
				fireAlarmEvent(this, ai);
				return;
			}

			// WARNING: using 11ms to compenstate for 200Hz signal
			boolean process_flag;
			if (recalc_period <= 0 || recalc_last == 0) {
				process_flag = true;
			} else {
				process_flag = (tm - recalc_last > recalc_period);
			}

			if (process_flag) {
				if (did_alarm) {
					Alarm ai = new Alarm("mse", Alarm.CLEAR, 0, "", true);
					ai.setTm(item.getTm());
					fireAlarmEvent(this, ai);
				}

				recalc_last = tm;
				int[] iar = rri.asInts();
				double mse1 = process(iar, 1, tolerance, 2);
				double mse2 = process(iar, 2, tolerance, 2);
				double mse3 = process(iar, 3, tolerance, 2);
				double mse4 = process(iar, 4, tolerance, 2);
				double mse5 = process(iar, 5, tolerance, 2);

				MSEBlock block = new MSEBlock( );
				block.setTm( new Date(tm) );

				block.setMSE1((int) (mse1 * 100));
				block.setMSE2((int) (mse2 * 100));
				block.setMSE3((int) (mse3 * 100));
				block.setMSE4((int) (mse4 * 100));
				block.setMSE5((int) (mse5 * 100));
				block.setMSE((int) ((mse1 + mse2 + mse3 + mse4 + mse5) * 100));

				fireStreamEvent(0,this,StreamID.MEASUREMENT, block);
			}

		} else if (sid == StreamID.MEASUREMENT) {
		} else if (sid == StreamID.WAVEFORM) {
			// ignore
		}
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

	public SignalBuffer<Number> getRRIs() {
		return rri;
	}

}
