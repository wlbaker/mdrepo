package idea.analysis;

import idea.conf.DeviceCapabilities;
import idea.intf.AbstractStreamProducer;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.Alarm;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.analysis.event.BeatBlock;
import idea.analysis.event.PulseTransitTimeBlock;

public class PulseTransitTimeProcessor extends AbstractStreamProducer implements
		StreamConsumer {

	/************************************************************************
	 * This class provides the methods needed to calculate the ECG-ABP pulse
	 * transit time (PTT) using the onset time detected by an ABP onset
	 * detection algorithm and the R wave times detected by the Automated
	 * Electrocardiogram Selection of Peaks algorithm
	 * 
	 * @param PTT
	 *            pulse transit time
	 * 
	 *************************************************************************/

	private static final int PTT_THTRESHOLD = 300;

	private static int verbose = 0;

	private long detOnsetTime = 0;
	private long detPeakTime = 0;
	private long prevPTT = 0;
	private boolean detectedFromECG = false;
	private boolean detectedFromABP = false;
	
	private static DeviceCapabilities caps;
	static {
		caps = new DeviceCapabilities( PulseTransitTimeProcessor.class);
		caps.addStream(StreamID.MEASUREMENT, PulseTransitTimeBlock.class );
		//caps.addConnection(None);
	}

	public PulseTransitTimeProcessor() {
		detOnsetTime = 0;
		detPeakTime = 0;
		detectedFromECG = false;
		detectedFromABP = false;
	}

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {

		if (item instanceof BeatBlock) {

			BeatBlock block = (BeatBlock) item;

			int leadId = block.getLead_id();
			long rTimeStamp = IntfUtil.getTime(block);

			// System.out.println("Detector" + leadId + " with SQI: " + sqi);
			if (leadId == 0 && !detectedFromECG) {
				detPeakTime = rTimeStamp;
				detectedFromECG = true;
			}
			if (leadId == 1 && !detectedFromABP) {
				detOnsetTime = rTimeStamp;
				detectedFromABP = true;
			}

			if (detectedFromECG && detectedFromABP) {

				if ((detOnsetTime - detPeakTime) < PTT_THTRESHOLD
						&& (detOnsetTime - detPeakTime) > 0) {
					PulseTransitTimeBlock pttBlock = new PulseTransitTimeBlock();
					pttBlock.setPTT((detOnsetTime - detPeakTime));
					prevPTT = (detOnsetTime - detPeakTime);
					pttBlock.setTime(Math.max(detPeakTime, detOnsetTime));
					fireStreamEvent(0,this,StreamID.MEASUREMENT, pttBlock);
					fireAlarmEvent(this, new Alarm(null, 50, 11, " ",
							Boolean.TRUE));
					detPeakTime = 0;
					detOnsetTime = 0;
					detectedFromECG = false;
					detectedFromABP = false;
				} else if ((detOnsetTime - detPeakTime) < 0) {
					PulseTransitTimeBlock pttBlock = new PulseTransitTimeBlock();
					// pttBlock.getPTTItem().setValue((detOnsetTime -
					// detPeakTime));
					pttBlock.setPTT(prevPTT);
					pttBlock.setTime(Math.max(detPeakTime, detOnsetTime));
					fireStreamEvent(0,this,StreamID.MEASUREMENT, pttBlock);
					fireAlarmEvent(this, new Alarm(null, 50, 11, "ABP FN",
							Boolean.TRUE));
					fireAlarmEvent(this, new Alarm(null, 50, 11, "PTT = "
							+ (detOnsetTime - detPeakTime), Boolean.TRUE));
					detOnsetTime = 0;
					detectedFromABP = false;
				} else if ((detOnsetTime - detPeakTime) >= PTT_THTRESHOLD
						&& (detOnsetTime - detPeakTime) < 2.5 * PTT_THTRESHOLD) {
					PulseTransitTimeBlock pttBlock = new PulseTransitTimeBlock();
					// pttBlock.getPTTItem().setValue((detOnsetTime -
					// detPeakTime));
					pttBlock.setPTT(prevPTT);
					pttBlock.setTime(Math.max(detPeakTime, detOnsetTime));
					fireStreamEvent(0,this,StreamID.MEASUREMENT, pttBlock);
					fireAlarmEvent(this, new Alarm(null, 50, 11,
							"Sync issue!", Boolean.TRUE));
					fireAlarmEvent(this, new Alarm(null, 50, 11, "PTT = "
							+ (detOnsetTime - detPeakTime), Boolean.TRUE));
					detPeakTime = 0;
					detectedFromECG = false;
				} else {
					PulseTransitTimeBlock pttBlock = new PulseTransitTimeBlock();
					// pttBlock.getPTTItem().setValue((detOnsetTime -
					// detPeakTime));
					pttBlock.setPTT(prevPTT);
					pttBlock.setTime(Math.max(detPeakTime, detOnsetTime));
					fireStreamEvent(0,this,StreamID.MEASUREMENT, pttBlock);
					fireAlarmEvent(this, new Alarm(null, 50, 11,
							"ECG-ABP error!", Boolean.TRUE));
					fireAlarmEvent(this, new Alarm(null, 50, 11, "PTT = "
							+ (detOnsetTime - detPeakTime), Boolean.TRUE));
					detPeakTime = 0;
					detOnsetTime = 0;
					detectedFromECG = false;
					detectedFromABP = false;
				}

			}
		}

	}

	@Override
	public DeviceCapabilities getStaticCapabilities() {
		return caps;
	}
}
