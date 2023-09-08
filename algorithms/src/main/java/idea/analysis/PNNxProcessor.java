package idea.analysis;

import idea.conf.DeviceCapabilities;
import idea.intf.AbstractStreamProducer;
import idea.intf.AdapterUtil;
import idea.intf.DataTyp;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.ModelUtil;
import idea.model.PersistentItem;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpPrecisionUnit;

import java.util.Arrays;

import idea.buffer.SignalBuffer;

public class PNNxProcessor extends AbstractStreamProducer implements
		StreamConsumer {

	public static double[] PNNx(double[] buckets, int[] signal) {

		if (signal == null || signal.length == 0) {
			return null;
		}

		double[] pnnx = new double[buckets.length];

		int lastrri = signal[0];
		int tot = signal.length;
		for (int i = 1; i < tot; i++) {
			int rri = signal[i];
			int dt = Math.abs(lastrri - rri);
			// System.out.println( "DT=" + dt );
			for (int pos = 0; pos < buckets.length; pos++) {
				if (buckets[pos] <= dt) {
					pnnx[pos]++;
					// System.out.println( "  [" + pos + "] " + dt + " > " +
					// buckets[pos] );
				}
			}
			lastrri = rri;
		}

		for (int pos = 0; pos < buckets.length; pos++) {
			pnnx[pos] /= tot;
		}

		return pnnx;
	}

	public static double[] PNNx(double[] buckets, SignalBuffer<Double> signal) {

		if (signal == null || signal.getSampleCount() == 0) {
			return null;
		}

		double[] pnnx = new double[buckets.length];

		double lastrri = signal.get(0);
		int tot = signal.getSampleCount();
		for (int i = 1; i < tot; i++) {
			double rri = signal.get(i);
			double dt = Math.abs(lastrri - rri);

			for (int pos = 0; pos < buckets.length; pos++) {
				if (buckets[pos] <= dt) {
					pnnx[pos]++;
				}
			}
			lastrri = rri;
		}

		for (int pos = 0; pos < buckets.length; pos++) {
			pnnx[pos] /= tot;
		}

		return pnnx;
	}

	private int recalc_period;
	private long recalc_last;

	private double[] buckets;
	private String loc;
	RpMetric[] metrics;
	private SignalBuffer<Double> buffer; // an implementation of a circular
											// buffer
	private Class<? extends PersistentItem> metricsClass;

	public PNNxProcessor(double[] buckets, String loc, int buflen) {
		this.buckets = Arrays.copyOf(buckets, buckets.length);
		this.loc = loc;
		metrics = new RpMetric[buckets.length];

		RpPrecisionUnit thousandths = new RpPrecisionUnit(3, "");
		RpMetric [] metrics = new RpMetric[buckets.length]; 
		for (int i = 0; i < buckets.length; i++) {
			int x = (int) buckets[i];
			metrics[i] = new RpMetric("pNN" + x, null, null, thousandths, DataTyp.INT_TYP);
		}

		metricsClass = AdapterUtil.buildMetricsClass("PNN", Arrays.asList(metrics) );
		buffer = new SignalBuffer<Double>(buflen, true);
	}

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {

		if (sid == StreamID.MEASUREMENT) {
			Number rri = IntfUtil.getScaledValueByLoc(item, loc);

			long tm = item.getTime();

			buffer.addData(rri.doubleValue()); // add event to sliding
												// window...called
												// "signal"...see other
			boolean process_flag;
			if (recalc_period <= 0 || recalc_last == 0) {
				process_flag = true;
			} else {
				process_flag = (tm - recalc_last > recalc_period);
			}

			if (process_flag) {
			if (buffer.getBufferSize() == buffer.getSampleCount()) {
				double[] out = PNNx(buckets, buffer);
				PersistentItem block = ModelUtil.getModelFromDataClass(metricsClass);
				block.setTime(tm);
				for (int i = 0; i < buckets.length; i++) {
					int x = (int) buckets[i];
					String loc = "pNN" + x;
					int val = (int) (1000 * out[i]);
					IntfUtil.setScaledValue(block, loc, val);
				}
				recalc_last = tm;
				fireStreamEvent(0,this,StreamID.MEASUREMENT, block);
			}
			}
		} else if (sid == StreamID.WAVEFORM) {
			// ignore
		}

	}

	@Override
	public DeviceCapabilities getStaticCapabilities() {
		return null; // capabilities depend on how this class was constructed
	}
	
	
	//?!!! @Override
	void reset() {
		if (buffer != null) {
			buffer.clear();
		}
	}


	public void setRecalcPeriod(int msec) {
		recalc_period = msec;
	}

}
