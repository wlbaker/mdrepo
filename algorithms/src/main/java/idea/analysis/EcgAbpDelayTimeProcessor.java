package idea.analysis;

import idea.conf.DeviceCapabilities;
import idea.intf.AbstractStreamProducer;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.Alarm;
import idea.model.IntfUtil;
import idea.model.PersistentItem;

import java.util.Date;

import idea.analysis.event.BeatBlock;
import idea.analysis.event.EcgAbpDelayTimeBlock;

public class EcgAbpDelayTimeProcessor extends AbstractStreamProducer implements
		StreamConsumer {

	/************************************************************************
	 * This class provides the methods needed to calculate the ECG-ABP delay
	 * time (DT) using the peak times detected by a peak detection algorithm,
	 * such as the Automated Electrocardiogram Selection of Peaks (AESOP)
	 * algorithm or BEBOP algorithm.
	 * 
	 * @param DT
	 *            delay time
	 * 
	 *************************************************************************/

	private static final int DT_THTRESHOLD = 300;

	private static int verbose = 0;

	private long[] detPeakTime = { 0, 0 };
	private int prevDT = 0;
	private boolean detectedFromECG = false;
	private boolean detectedFromABP = false;

	public EcgAbpDelayTimeProcessor() {
		detPeakTime[0] = 0;
		detPeakTime[1] = 0;
		prevDT = 0;
		detectedFromECG = false;
		detectedFromABP = false;
	}

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {

		if (item instanceof BeatBlock) {

			BeatBlock block = (BeatBlock) item;

			int rPos = block.getPos();
			int rrInterval = block.getSamp_interval();
			int rAmplitude = block.getAmplitude();
			int leadId = block.getLead_id();
			int detId = block.getDetector_id();
			long rTimeStamp = IntfUtil.getTime(block);

			// System.out.println("Detector" + leadId + " with SQI: " + sqi);
			if (leadId == 0 && !detectedFromECG) {
				detPeakTime[0] = rTimeStamp;
				detectedFromECG = true;
			}
			if (leadId == 1 && !detectedFromABP) {
				detPeakTime[1] = rTimeStamp;
				detectedFromABP = true;
			}

			if (detectedFromECG && detectedFromABP) {

				if ((detPeakTime[1] - detPeakTime[0]) < DT_THTRESHOLD
						&& (detPeakTime[1] - detPeakTime[0]) > 0) {
					EcgAbpDelayTimeBlock dtBlock = new EcgAbpDelayTimeBlock();
					dtBlock.setDt(
							(int) (detPeakTime[1] - detPeakTime[0]));
					prevDT = (int) (detPeakTime[1] - detPeakTime[0]);
					dtBlock.setTm(new Date(Math.max(detPeakTime[0], detPeakTime[1])));
					fireStreamEvent(0,this,StreamID.MEASUREMENT, dtBlock);
					fireAlarmEvent(this, new Alarm(null, 50, 11, " ",
							Boolean.TRUE));
					detPeakTime[0] = 0;
					detPeakTime[1] = 0;
					detectedFromECG = false;
					detectedFromABP = false;
				} else if ((detPeakTime[1] - detPeakTime[0]) < 0) {
					EcgAbpDelayTimeBlock dtBlock = new EcgAbpDelayTimeBlock();
					// dtBlock.getDTItem().setValue((detPeakTime[1] -
					// detPeakTime[0]));
					dtBlock.setDt(prevDT);
					dtBlock.setTm(new Date(Math.max(detPeakTime[0], detPeakTime[1])));
					fireStreamEvent(0,this,StreamID.MEASUREMENT, dtBlock);
					fireAlarmEvent(this, new Alarm(null, 50, 11, "ABP FN",
							Boolean.TRUE));
					fireAlarmEvent(this, new Alarm(null, 50, 11, "DT = "
							+ (detPeakTime[1] - detPeakTime[0]), Boolean.TRUE));
					detPeakTime[1] = 0;
					detectedFromABP = false;
				} else if ((detPeakTime[1] - detPeakTime[0]) >= DT_THTRESHOLD
						&& (detPeakTime[1] - detPeakTime[0]) < 2.5 * DT_THTRESHOLD) {
					EcgAbpDelayTimeBlock dtBlock = new EcgAbpDelayTimeBlock();
					// dtBlock.getDTItem().setValue((detPeakTime[1] -
					// detPeakTime[0]));
					dtBlock.setDt(prevDT);
					dtBlock.setTm(new Date(Math.max(detPeakTime[0], detPeakTime[1])));
					fireStreamEvent(0,this,StreamID.MEASUREMENT, dtBlock);
					fireAlarmEvent(this, new Alarm(null, 50, 11,
							"Sync issue!", Boolean.TRUE));
					fireAlarmEvent(this, new Alarm(null, 50, 11, "DT = "
							+ (detPeakTime[1] - detPeakTime[0]), Boolean.TRUE));
					detPeakTime[0] = 0;
					detectedFromECG = false;
				} else {
					EcgAbpDelayTimeBlock dtBlock = new EcgAbpDelayTimeBlock();
					// dtBlock.getDTItem().setValue((detPeakTime[1] -
					// detPeakTime[0]));
					dtBlock.setDt(prevDT);
					dtBlock.setTm(new Date(Math.max(detPeakTime[0], detPeakTime[1])));
					fireStreamEvent(0,this,StreamID.MEASUREMENT, dtBlock);
					fireAlarmEvent(this, new Alarm(null, 50, 11,
							"ECG-ABP error!", Boolean.TRUE));
					fireAlarmEvent(this, new Alarm(null, 50, 11, "DT = "
							+ (detPeakTime[1] - detPeakTime[0]), Boolean.TRUE));
					detPeakTime[0] = 0;
					detPeakTime[1] = 0;
					detectedFromECG = false;
					detectedFromABP = false;
				}

			}
		} else if (sid == StreamID.MEASUREMENT) {
		} else if (sid == StreamID.WAVEFORM) {
		}

	}

	@Override
	public DeviceCapabilities getStaticCapabilities() {
		DeviceCapabilities caps = new DeviceCapabilities(this.getClass());
		caps.addStream(StreamID.MEASUREMENT, EcgAbpDelayTimeBlock.class);
		return caps;
	}
}
