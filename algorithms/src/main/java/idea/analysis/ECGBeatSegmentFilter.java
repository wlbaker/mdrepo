package idea.analysis;

import idea.conf.DeviceCapabilities;
import idea.intf.AbstractStreamProducer;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.PersistentItem;
import idea.schema.rp.RpAnalysis;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpStudy;
import idea.schema.rp.StringStringMap;
import lombok.extern.slf4j.Slf4j;
import idea.analysis.event.BeatBlock;
import idea.qrsdet.AbstractDetector;
import idea.qrsdet.DetectorFactory;

@Slf4j
public class ECGBeatSegmentFilter extends AbstractStreamProducer implements StreamConsumer {
	private static final RpAnalysis analysisInfo;
	private static final String DETECTOR_PARAM = "detector";
	
	public static final String DEVICE_PARAM = "dev";
	public static final String STREAM_PARAM = "stream";
	public static final String SIGNAL_LOC = "loc";
	public static final String SIGNAL_CODE = "code";

	static {
		analysisInfo = new RpAnalysis();
		analysisInfo.setName("ECG Segmentation");
		analysisInfo.setAnalysisClass(ECGBeatSegmentFilter.class.getCanonicalName());
		
		StringStringMap params = new StringStringMap();
		params.put(DETECTOR_PARAM, "PT1");
		params.put(DEVICE_PARAM, "dev0" );
		params.put(STREAM_PARAM, StreamID.WAVEFORM.getName() );
		params.put(SIGNAL_CODE, "<SELECTION>");
		params.put(SIGNAL_LOC, "<LOC>");
		
		analysisInfo.setParam( params );
	}

	AbstractDetector detector;
	private String detectorName;
	private String loc;
	private String code;

	private static DeviceCapabilities caps;
	static {
		caps = new DeviceCapabilities(BeatBlock.class);
		caps.addStream(StreamID.MEASUREMENT, BeatBlock.class);
		//caps.addConnection(None);
	}

	public ECGBeatSegmentFilter() {
		this((RpStudy)null, (RpAnalysis) null);
	}

	public ECGBeatSegmentFilter(RpAnalysis anal) {
		this((RpStudy)null, anal);
	}

	public ECGBeatSegmentFilter(RpStudy study, RpAnalysis anal) {
		StringStringMap params = null;

		if (anal != null) {
			params = anal.getParam();
		}

		if (params != null) {
			detectorName = params.get(DETECTOR_PARAM);
			code = params.get(SIGNAL_CODE);
			loc = params.get(SIGNAL_LOC);
		}
	}

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {

		if (sid == StreamID.WAVEFORM) {
			if (detector == null) {
				RpMetric desc = item.getMetric(loc);
				detector = DetectorFactory.createDetector(detectorName, desc);
				
				// listeners have attached to us, to proxy the messages from detector
				// through to the actual listeners
				detector.addStreamListener(null, new StreamConsumer() {

					@Override
					public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {
						ECGBeatSegmentFilter.this.fireStreamEvent(jobID, ECGBeatSegmentFilter.this, sid, item);
					} } );
			}

			detector.streamEvent(jobID, source, sid, item);
		}
	}

	@Override
	public DeviceCapabilities getStaticCapabilities() {
		return caps;
	}

}
