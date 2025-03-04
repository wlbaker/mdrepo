package idea.analysis;

import icuInterface.UnitUtil;
import idea.conf.DeviceCapabilities;
import idea.intf.AbstractStreamProducer;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.schema.rp.RpAnalysis;
import idea.schema.rp.RpLinearUnit;
import idea.schema.rp.RpMetric;

import java.io.PrintStream;
import java.util.Date;

import lombok.extern.slf4j.Slf4j;
import idea.analysis.event.SBCO2Block;
import idea.analysis.ventilator.BrState;
import idea.analysis.ventilator.SBCO2;
import idea.buffer.SignalBuffer;

@Slf4j
public class SBSegmentFilter extends AbstractStreamProducer implements StreamConsumer {
	private static final RpAnalysis analysisInfo;
	
	static { 
		analysisInfo = new RpAnalysis();
		analysisInfo.setName("Breath Segmentation");
		analysisInfo.setAnalysisClass( SBSegmentFilter.class.getCanonicalName() );
		// analysisInfo.
	}

	// WARNING: this depends on sample frequency!
	// you want min IBI to be at least at 40 breaths / min
	private int minimumIBI = 60;

	// WARNING: this depends on sample frequency!
	// you want max IBI to be at least at 4 breaths / min
	private static final int MAX_BREATH_IBI = 800;

	private BrState brState = null;

	private double flow_threshold = 500;
	private double exp_vol = 0.0;

	private int pos = 0;

	private int phase_len = 0;
	private int breath_len = 0;

	PrintStream out_raw = null; // System.out;

	Date sampleDate;
	long mstime;

	private String srcawp_loc;
	private String srcflow_loc;
	private RpLinearUnit srcawp_unit;
	private RpLinearUnit srcflow_unit;

	private SignalBuffer<Double> vol_sig_seg = new SignalBuffer<Double>(100, false);

	private SignalBuffer<Double> flow_sig = new SignalBuffer<Double>(1000, true);
	private SignalBuffer<Double> vol_sig = new SignalBuffer<Double>(1000, true);

	SBCO2Block sbco2 = new SBCO2Block();

	private int ibi_pos;
	double sampleRate;
	double sampleTime;

	private Long initial_tm;

	private static DeviceCapabilities caps;
	static {
		caps = new DeviceCapabilities( SBCO2.class);
		caps.addStream(StreamID.MEASUREMENT, SBCO2Block.class );
		//caps.addConnection(None);
	}
	
	public SBSegmentFilter() {
		this((RpAnalysis)null);
	}

	public SBSegmentFilter(RpAnalysis anal) {
		if (anal == null) {
			// ok
		} else {
			srcflow_loc = anal.getParam().get("sig");
			srcflow_unit = new RpLinearUnit(0.1, -180.0, "L/min");
		}
	}

	public SBSegmentFilter(RpMetric flow) {
		if (flow == null) {
			// ok
		} else {
			sampleRate = flow.getSampleRate();
			srcflow_loc = flow.getLocation();
			srcflow_unit = new RpLinearUnit(0.1, -180.0, "L/min");
		}
	}

	public void setSourceAWP(String awpLoc, RpLinearUnit awpUnit) {
		srcawp_loc = awpLoc;
		srcawp_unit = awpUnit;
	}

	public void setSourceFlow(String flowLoc, RpLinearUnit flowUnit) {
		srcflow_loc = flowLoc;
		srcflow_unit = flowUnit;

	}

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {

		if (sid == StreamID.WAVEFORM) {
			addWaveform(item);
		} else if (sid == StreamID.MEASUREMENT) {
			// ignore
			// NumericsEvent ne = (NumericsEvent) event;

		}

	}

	public void addWaveform(PersistentItem item) {

		int[] flowWave = (int[]) IntfUtil.getRawValueByLoc(item, srcflow_loc);
		int[] awpWave = (int[]) IntfUtil.getRawValueByLoc(item, srcawp_loc);
		
		double sampleRate = item.getMetric(srcflow_loc).getSampleRate();
		addWaveform(item.getTime(), sampleRate, flowWave, awpWave);
	}

	private void addWaveform(long blockTime, double sampleRate, int[] flow_ar, int[] awp_ar) {

		if (sampleTime == 0) {
			sampleTime = 1.0 / sampleRate;
		}


		long tm_ms = blockTime;
		for (int i = 0; i < flow_ar.length; i++) {
			double awp = 0;
			// double tm = blockTime + pos / sampleRate;
			double flow = UnitUtil.getValue(srcflow_unit, flow_ar[i]);
			if (awp_ar != null) {
				awp = UnitUtil.getValue(srcawp_unit,awp_ar[i]);
			}

			getDatum(tm_ms, flow, awp);
		}
	}

	double[] queue = new double[8];

	private int count;

	public void getDatum(long tm, double flow_lpm, double awp) {

		if (initial_tm == null) {
			initial_tm = tm;
		}

		/* an elementary block filter */
		double tot = 0;
		for (int i = 1; i < queue.length; i++) {
			tot += queue[i];
			queue[i - 1] = queue[i];
		}

		queue[queue.length - 1] = flow_lpm;
		tot += flow_lpm;
		flow_lpm = tot / queue.length;
		/* end of filter */

		assert (sampleRate != 0) : "SAMPLE RATE NOT INITIALIZED";
		pos++;

		double flow = 1000 * flow_lpm / 60.0; // convert from L/min to mL/sec
		//10-Nov-2014 
		// removed by wlb : flow -= 3000; // EVITA

		// boolean save_raw = (tm > 0 && tm < 3);

		log.debug("{}  {}", flow, brState);
		// System.out.println( flow + "  " + brState );

		if (brState == null) {
			// ignore...add one point...accumulate data...
			// BLIND ERROR: ASSUME PHASE 3!!!!
			brState = BrState.REST;
			// } else if( phase_len < 10 ) {
			// do nothing
		} else if (brState == BrState.REST && flow > flow_threshold) {
			int ibi = pos - ibi_pos;
			brState = BrState.INHALE;

			if (ibi > MAX_BREATH_IBI || ibi < minimumIBI) {
				// breath too long or too short
				log.warn("too short/too long: {}", ibi);
			} else {
				log.debug("fire");
				if (count == 0) {
					log.debug("ignoring first waveform");
				} else {
					fire(tm);
				}
				count++;
			}

			reset_metrics();
		} else if (brState == BrState.INHALE && flow < -flow_threshold) {
			brState = BrState.EXHALE;
			phase_len = 0;
		} else if (brState == BrState.EXHALE && flow > -flow_threshold) {
			brState = BrState.REST;
			phase_len = 0;

			if (out_raw != null) { // gives a break in the
				// vco2/vol/pct_co2 lines
				out_raw.format("%8.7g\t", pos / sampleRate);
				out_raw.format("%3.3g\t%3.3g", flow, awp);
				out_raw.format("\t0\t0\t0"); // vol, vco2, pct_co2);
				out_raw.println();

			}
			vol_sig.addData(exp_vol); // just one fake point
			flow_sig.addData(flow);

		}
		phase_len++;
		breath_len++;

		double delta_vol = -flow * sampleTime;

		// we don't save the "rest" or "insp" data for phase2/phase3 slope
		// determinations
		// -- rest data is very noisy for slope calculations
		// -- insp data is not involved in phase2/phase3
		if (brState == BrState.EXHALE) {
			exp_vol += delta_vol; // only interested in exhaled volume
			vol_sig_seg.addData(exp_vol);
		}

		if (brState == BrState.EXHALE) {
			if (out_raw != null) {
				out_raw.format("%8.7g\t", pos / sampleRate);
				out_raw.format("%3.3g\t%3.3g", flow, awp);
				out_raw.format("\t%3.3g", exp_vol);
				out_raw.println();
			}

			vol_sig.addData(exp_vol);
			flow_sig.addData(flow);
		}

	} // end of fuction

	private void fire(long tm) {

		// check that slopes make sense, reject otherwise!

		sbco2.setTm( new Date(tm) );

		sbco2.setFlowData(flow_sig.asDoubles());
		sbco2.setVolData(vol_sig.asDoubles());

		sbco2.setTV( exp_vol);
		sbco2.setRelativeTime((tm - initial_tm) / 1000.0); // in seconds

		sbco2.setIbi((int) (100 * (pos - ibi_pos) / sampleRate)); // convert pts to ms

		fireStreamEvent(0,this,StreamID.MEASUREMENT, sbco2);

	}

	private void reset_metrics() {
		phase_len = 0;
		breath_len = 0;
		//
		// etco2 should only be cleared if the event is fired...let it keep
		// inching up
		// in the case of flenches and spont breathing
		//
		// etco2 = 0;
		exp_vol = 0.0;

		vol_sig_seg.clear();

		ibi_pos = pos;

		vol_sig.clear();
		flow_sig.clear();

	}

	@Override
	public DeviceCapabilities getStaticCapabilities() {
		return caps;
	}

	public void setMinIBI(int minIBI_ms) {

		// convert ms to samples

		this.minimumIBI = (int) ((sampleRate * minIBI_ms) / 1000);
	}

	public void setFlowThreshold(int flowThreshold) {
		this.flow_threshold = flowThreshold;
	}

}
