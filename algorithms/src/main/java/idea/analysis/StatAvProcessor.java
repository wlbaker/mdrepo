package idea.analysis;

import idea.conf.DeviceCapabilities;
import idea.intf.AbstractStreamProducer;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.Alarm;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.Stats;
import idea.analysis.event.BeatBlock;
import idea.analysis.event.StatAvBlock;
import idea.buffer.CircularIntBuffer;

public class StatAvProcessor extends AbstractStreamProducer implements
		StreamConsumer {

	/************************************************************************
	 * This class provides the methods needed to calculate the StatAv 
	 * (index of nonstationarity) using the R-R intervals (RRIs) detected by 
	 * a QRS detection algorithm, such as the Automated Electrocardiogram 
	 * Selection of Peaks (AESOP) algorithm.
	 * 
	 * @param SDRR		Standard deviation of RRIs  
	 * @param SDSD		Standard deviation of successive RRI differences
	 * @param SDAV		Standard deviation of RRI epochs
	 * @param StatAv	SDAV / SDRR
	 * 
	 *************************************************************************/

	private final static int NUM_EPOCHS = 40;

	private static int verbose = 0;

	private int totSamples;

	private CircularIntBuffer rris;
	private CircularIntBuffer rriDiffs;

	private int mstime;

	private int prevMSInterval;

	public StatAvProcessor(int count) {
		totSamples = 0;
		rris = new CircularIntBuffer(count, true);
		rriDiffs = new CircularIntBuffer(count-1, true);
		prevMSInterval = 0;
		mstime = 0;
	}

	public static StatAvBlock process( int [] rri ) {
		
		int [] rriDiffs = new int[rri.length - 1];
		
		for( int i = 0; i < rri.length - 1 ; i++ ) {
			rriDiffs[i] = rri[i+1] - rri[i];
		}

		return process( rri, rriDiffs );
	}
	
	public static StatAvBlock process( int [] rri, int [] rriDiffs ) {
		CircularIntBuffer circleRri = new CircularIntBuffer( rri, true );
		CircularIntBuffer circleDiff = new CircularIntBuffer( rriDiffs, true );
		
		return process( null, circleRri, circleDiff );
	}

	public static StatAvBlock process(StatAvBlock statAvBlock, CircularIntBuffer rri, CircularIntBuffer rriDiffs) {
		double mean = 0.0;

		int epochLength = rri.length()/NUM_EPOCHS;

		double SDRR = Stats.getStandardDeviation(rri);
		double SDSD = Stats.getStandardDeviation(rriDiffs);

		double [] rriEpochs = new double[NUM_EPOCHS];
		for (int i = 0; i < NUM_EPOCHS; ++i) {
			mean = 0.0;
			for (int j = epochLength*i; j < epochLength*(i+1); j++) {
				mean += rri.get(j);
			}
			mean /= epochLength;

			rriEpochs[i] = mean;
		}

		double SDAV = Stats.sd(rriEpochs);

		double StatAv = 1.0 * SDAV / SDRR;

		if( statAvBlock == null ) {
			statAvBlock = new StatAvBlock();
		}

		statAvBlock.setSdrr(SDRR);
		statAvBlock.setSdsd(SDSD);
		statAvBlock.setSdav(SDAV);
		statAvBlock.setStatav(StatAv);

		return statAvBlock;
	}

	public static StatAvBlock process( double [] rri ) {
		
		double [] rriDiffs = new double[rri.length - 1];
		
		for( int i = 0; i < rri.length - 1 ; i++ ) {
			rriDiffs[i] = rri[i+1] - rri[i];
		}

		return process( rri, rriDiffs );
	}
	
	public static StatAvBlock process( double [] rri, double [] rriDiffs ) {
		return process( null, rri, rriDiffs );
	}

	public static StatAvBlock process(StatAvBlock statAvBlock,double [] rri, double [] rriDiffs) {
		double mean = 0.0;

		int epochLength = rri.length/NUM_EPOCHS;

		double SDRR = Stats.sd(rri);
		double SDSD = Stats.sd(rriDiffs);

		double [] rriEpochs = new double[NUM_EPOCHS];
		for (int i = 0; i < NUM_EPOCHS; ++i) {
			mean = 0.0;
			for (int j = epochLength*i; j < epochLength*(i+1); j++) {
				mean += rri[j];
			}
			mean /= epochLength;

			rriEpochs[i] = mean;
		}

		double SDAV = Stats.sd(rriEpochs);

		double StatAv = 1.0 * SDAV / SDRR;

		if( statAvBlock == null ) {
			statAvBlock = new StatAvBlock();
		}

		statAvBlock.setSdrr(SDRR);
		statAvBlock.setSdsd(SDSD);
		statAvBlock.setSdav(SDAV);
		statAvBlock.setStatav(StatAv);

		return statAvBlock;
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

			if (rris.getSampleCount() < rris.length()) {
				if (verbose > 0) {
					System.out.println("   StatAv progress: "
							+ rris.getSampleCount() + " out of "
							+ rris.length());
				}
				Alarm ai = new Alarm("statav", Alarm.INFO, 0, "Waiting: "
						+ rris.getSampleCount() + " out of "
						+ rris.length(), true);
				fireAlarmEvent(this, ai);
				return;
			}

			StatAvBlock staBlock = process( null, rris, rriDiffs );
			staBlock.setTime(IntfUtil.getTime(block));

			fireStreamEvent(0,this,StreamID.MEASUREMENT, staBlock);

		}

	}

	@Override
	public DeviceCapabilities getStaticCapabilities() {
		DeviceCapabilities caps = new DeviceCapabilities(this.getClass());
		caps.addStream(StreamID.MEASUREMENT, StatAvBlock.class);
		return caps;
	}
}
