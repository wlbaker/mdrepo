package idea.analysis;

import idea.conf.DeviceCapabilities;
import idea.intf.AbstractStreamProducer;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.Alarm;
import idea.model.PersistentItem;
import idea.analysis.event.BeatBlock;
import idea.analysis.event.PoincareBlock;
import idea.buffer.SignalBuffer;

public class PoincareProcessor extends AbstractStreamProducer implements
		StreamConsumer {

	/************************************************************************
	 * This class provides the methods needed to perform a Poincare plot 
	 * analysis on the R-R intervals (RRIs) detected by a QRS detection 
	 * algorithm, such as the Automated Electrocardiogram Selection of Peaks 
	 * (AESOP) algorithm.
	 * 
	 * @param SDRR		Standard deviation of RRIs  
	 * @param SDSD		Standard deviation of successive RRI differences
	 * @param SD1		Short-term variability of RRIs
	 * @param SD2		Long-term variability of RRIs
	 * @param SDRatio	Ratio of short-term to long-term RRI variability
	 * 
	 *************************************************************************/

	private static int verbose = 0;

	private int sampleRate;
	private int totSamples;

	private SignalBuffer<Integer> rris;
	private SignalBuffer<Integer> rriDiffs;

	private int mstime;

	private int prevMSInterval;

	private double SDRR;
	private double SDSD;

	private double SD1;
	private double SD2;
	private double SDRatio;

	public PoincareProcessor(int count) {
		totSamples = 0;
		rris = new SignalBuffer<Integer>(count, true);
		rriDiffs = new SignalBuffer<Integer>(count-1, true);
		prevMSInterval = 0;
		mstime = 0;
	}

	private double getSampleMeanVariance(SignalBuffer<? extends Number> signal) {

		double mean = 0.0;
		Number standardDev = null;
		double variance = 0;

		int tot = signal.getSampleCount();
		for (int i = 0; i < tot; ++i) {
			mean += signal.get(i).doubleValue(); // rwaves[i];
		}
		mean /= tot;

		for (int i = 0; i < tot; ++i) {
			variance += Math.pow(signal.get(i).doubleValue() - mean, 2.0);
		}
		variance /= (tot - 1);

		standardDev = Math.sqrt(variance);

		return standardDev.doubleValue(); 

	}

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {

		if (item instanceof BeatBlock) {

			BeatBlock block = (BeatBlock)item;

			int interval = block.getMs_interval();
			mstime += interval;

			// Add successive RRI difference
			if (totSamples > 0) {
				rriDiffs.addData(interval - prevMSInterval);
			}

			prevMSInterval = interval;

			rris.addData(interval);
			
			totSamples++;

			if (rris.getSampleCount() < rris.getBufferSize()) {
				if (verbose > 0) {
					System.out.println("   Poincare progress: "
							+ rris.getSampleCount() + " out of "
							+ rris.getBufferSize());
				}
				Alarm ai = new Alarm("poincare", Alarm.INFO, 0, "Waiting: "
						+ rris.getSampleCount() + " out of "
						+ rris.getBufferSize(), true);
				fireAlarmEvent(this, ai);
				return;
			}

			SDRR = getSampleMeanVariance(rris);
			SDSD = getSampleMeanVariance(rriDiffs);

			SD1 = Math.sqrt( 0.5 * SDSD*SDSD );
			SD2 = Math.sqrt( 2 * SDRR*SDRR - 0.5 * SDSD*SDSD );
			SDRatio = SD1 / SD2;


			PoincareBlock poincareBlock = new PoincareBlock();

			poincareBlock.setSDRR(SDRR);
			poincareBlock.setSDSD(SDSD);
			poincareBlock.setSD1(SD1);
			poincareBlock.setSD2(SD2);
			poincareBlock.setSDRatio(SDRatio);

			fireStreamEvent(0,this,StreamID.MEASUREMENT, poincareBlock);

		}

	}

	@Override
	public DeviceCapabilities getStaticCapabilities() {
		DeviceCapabilities caps = new DeviceCapabilities(this.getClass());
		caps.addStream(StreamID.MEASUREMENT, PoincareBlock.class);
		return caps;
	}
}
