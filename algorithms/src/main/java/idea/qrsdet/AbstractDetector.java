package idea.qrsdet;

import idea.conf.DeviceCapabilities;
import idea.intf.AbstractStreamProducer;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.schema.rp.RpMetric;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.OutputStream;
import java.io.PrintStream;
import java.util.Date;

import lombok.extern.slf4j.Slf4j;
import idea.analysis.event.BeatBlock;

@Slf4j
public abstract class AbstractDetector extends AbstractStreamProducer implements StreamConsumer {

	int verbose = 0;
	protected String loc = null;
	protected Object source = "Drager"; // Default

	int cached_datatyp = 0;

	public long startTime = 0;
	public long nextBlockTime = 0;
	public boolean startTimeInitialized = false;

	protected int detId = 0;
	protected int leadId = 0;
	protected String logDir = null; // "c:/opt/study/aesop-verification/2011-09-22";

	public abstract void restartDetector();

	public void setDetId(int id) {
		this.detId = id;
	}

	public Object getDetId() {
		return detId;
	}

	public void setLeadId(int id) {
		this.leadId = id;
	}

	public Object getLeadId() {
		return leadId;
	}

	public void setSignalLoc(String loc) {
		this.loc = loc;
	}

	public String getSignalLoc() {
		return loc;
	}

	public void setSignalSource(Object source) {
		this.source = source;
	}

	public Object getSignalSource() {
		return source;
	}

	public void setInitialTime(long startTime) {
		this.startTime = startTime;
	}

	public abstract int getValue(int pending, int datum);

	public abstract void setSampleRate(int rate);

	public abstract int getSampleRate();

	@Override
	public DeviceCapabilities getStaticCapabilities() {
		DeviceCapabilities caps = new DeviceCapabilities(this.getClass());
		caps.addStream(StreamID.MEASUREMENT, BeatBlock.class);
		caps.setName("ABSTRACT_DETECTOR");
		return caps;
	}

	@Override
	public void requestCapabilities() {
		fireCapabilitiesEvent(this, getStaticCapabilities());
	}

	protected void fireBeatDetection(int r_pos, int rr_interval, int r_amplitude, int lead_id, int det_id) {

		BeatBlock block = new BeatBlock(this);

		block.setPos(r_pos);
		block.setSamp_interval(rr_interval);
		block.setAmplitude(r_amplitude);
		block.setDetector_id(det_id);
		block.setLead_id(lead_id);

		int sampleRate = getSampleRate();
		block.setMs_interval(rr_interval * 1000 / sampleRate); // WARNING:
																// integer
		// division

		// fireEvent(BeatEvent.class, new BeatEvent(this, block));
	}

	protected void fireRWaveDetection(int rPos, int rr_interval, int r_amplitude, int lead_id, int det_id,
			long r_timestamp) {

		BeatBlock block = new BeatBlock(this);

		block.setPos(rPos);
		block.setSamp_interval(rr_interval);

		int sampleRate = getSampleRate();
		block.setMs_interval((rr_interval * 1000) / sampleRate); // WARNING:
																	// integer
		// division

		block.setAmplitude(r_amplitude);
		block.setLead_id(lead_id);
		block.setDetector_id(det_id);

		block.setTm(new Date(r_timestamp));
		// log.error("FIXME: r_timestamp date={}", new Date(r_timestamp));

		fireStreamEvent(0, this, StreamID.MEASUREMENT, block);
	}

	protected void fireRWaveDetection(int rPos, int rr_interval, int r_amplitude, int lead_id, int det_id,
			int quality_idx, long r_timestamp) {

		BeatBlock block = new BeatBlock(this);

		block.setPos(rPos);
		block.setSamp_interval(rr_interval);

		int sampleRate = getSampleRate();
		block.setMs_interval((rr_interval * 1000) / sampleRate); // WARNING:
																	// integer
		// division

		block.setAmplitude(r_amplitude);
		block.setLead_id(lead_id);
		block.setDetector_id(det_id);

		block.setQuality_idx(quality_idx);

		block.setTm(new Date(r_timestamp));

		fireStreamEvent(0, this, StreamID.MEASUREMENT_2, block);
	}

	public void setLogDir(String logDir) {
		this.logDir = logDir;
	}

	protected void log_rwave(String src, long rTimeStamp, int rPos, int rrInterval, int leadId, int qidx)
			throws FileNotFoundException {
		if (logDir == null) {
			return; // no logging
		}

		synchronized (logDir) {
			File fout = new File(logDir);
			if (!fout.exists()) {
				fout.mkdirs();
			}
			fout = new File(fout, src);
			OutputStream out = new FileOutputStream(fout, true);

			PrintStream s = new PrintStream(out);
			s.println("" + rTimeStamp + ", " + rPos + ", " + rrInterval + ", " + leadId);
			s.close();
		}
	}

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem block) {

		if (block == null) {
			// no data indicator...ignore
			return;
		}

		if (sid == StreamID.WAVEFORM) {

			long tm = block.getTime();
			if (loc == null) {
				return;
			}

			if (!startTimeInitialized) {
				setInitialTime(tm);
				nextBlockTime = startTime;
				startTimeInitialized = true;
			}

			if (startTimeInitialized && nextBlockTime > 0) {
				if (tm - nextBlockTime > 1000) { // 1 second
					restartDetector();

					// For convention
					setInitialTime(tm);
					nextBlockTime = startTime;
					startTimeInitialized = true;
				} else {
					// Must compensate for jitter
					if ((tm - nextBlockTime > 0) && (tm - nextBlockTime < 4))
						nextBlockTime = tm;
				}
			}

			RpMetric wf = IntfUtil.getMetricByLoc(block, loc);

			// check to see that the requested wf was found in this block
			if (wf != null) {
				if (wf.getSampleRate() != getSampleRate()) {
					setSampleRate(wf.getSampleRate());
				}
				Object oDatums = IntfUtil.getRawValue(block, wf);
				if (oDatums == null) {
					// ignore
				} else {

					if (cached_datatyp == 0) {
						if (oDatums instanceof int[]) {
							cached_datatyp = 1;
						} else if (oDatums instanceof float[]) {
							cached_datatyp = 2;
						} else if (oDatums instanceof double[]) {
							cached_datatyp = 3;
						} else {
							log.error("UNHANDLED DATA TYPE: {}", oDatums.getClass());
						}
					}

					int datum_length = 0;
					if (cached_datatyp == 1) {
						int[] datums = (int[]) oDatums;
						int detectorPending = datum_length = datums.length;
						for (int datum : datums) {
							detectorPending--;
							getValue(detectorPending, datum);
						}
					} else if (cached_datatyp == 2) {
						float[] datums = (float[]) oDatums;
						int detectorPending = datum_length = datums.length;
						for (float datum : datums) {
							detectorPending--;
							getValue(detectorPending, (int) (1000 * datum));
						}
					} else if (cached_datatyp == 3) {
						double[] datums = (double[]) oDatums;
						int detectorPending = datum_length = datums.length;
						for (double datum : datums) {
							detectorPending--;
							getValue(detectorPending, (int) (1000 * datum));
						}
					}
					nextBlockTime = nextBlockTime + (long) (datum_length * 1000.0 / getSampleRate());
				}

			}

		}

		return;
	}

}
