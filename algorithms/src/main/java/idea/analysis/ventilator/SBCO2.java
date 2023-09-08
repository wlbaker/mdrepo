package idea.analysis.ventilator;

import icuInterface.UnitUtil;
import idea.conf.DeviceCapabilities;
import idea.intf.AbstractStreamProducer;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.schema.rp.RpLinearUnit;
import idea.schema.rp.RpMetric;

import java.io.PrintStream;
import java.text.DecimalFormat;
import java.text.SimpleDateFormat;
import java.util.Date;

import lombok.extern.slf4j.Slf4j;
import no.uib.cipr.matrix.DenseMatrix;
import no.uib.cipr.matrix.DenseVector;
import idea.Stats;
import idea.analysis.event.SBCO2Block;
import idea.buffer.SignalBuffer;

@Slf4j
public class SBCO2 extends AbstractStreamProducer implements StreamConsumer {

	private static final double MIN_BREATH_ETCO2 = 16;
	private static final double MIN_PHASE3_ETCO2 = 20;

	// WARNING: this depends on sample frequency!
	// you want min IBI to be at least at 40 breaths / min
	private static final int MIN_BREATH_IBI = 60;

	// WARNING: this depends on sample frequency!
	// you want max IBI to be at least at 4 breaths / min
	private static final int MAX_BREATH_IBI = 1200; // 12 seconds for 100hz data
	private static final int HIST_SIZE = 1200; // 12 seconds for 100hz data

	private BrState brState = null;

	public static double FLOW_THRESHHOLD = 500;
	private double exp_vol = 0.0;
	private double vco2 = 0.0;
	private double etco2 = 0.0;

	private double phase2_slope = 0.0;
	private double phase2_pos = 0;
	private double phase2_intercept = 0;
	private double phase2_y = 0;

	private double phase3_slope = 0.0;
	// private double phase3_pos = 0;
	private double phase3_intercept = 0;
	private double compliance;
	private double resistance;
	private double phyDeadSpace;
	// private double phase3_y = 0;

	private int pos = 0;

	private int phase_len = 0;
	private int breath_len = 0;

	private int verbose = 0;

	PrintStream out_raw = null; // System.out;

	// Date sampleDate;
	long mstime;

	private String srcco2_loc;
	private String srcawp_loc;
	private String srcflow_loc;
	private String srccompliance_loc;
	private String srcresistance_loc;

	private RpLinearUnit srcco2_unit;
	private RpLinearUnit srcawp_unit;
	private RpLinearUnit srcflow_unit;

	private RpLinearUnit srccompliance_unit;
	private RpLinearUnit srcresistance_unit;

	private SignalBuffer<Double> vol_sig_seg = new SignalBuffer<Double>(100, false);
	private SignalBuffer<Double> vco2_sig_seg = new SignalBuffer<Double>(100, false);
	private SignalBuffer<Double> fco2_sig_seg = new SignalBuffer<Double>(100, false);

	private SignalBuffer<Double> flow_sig = new SignalBuffer<Double>(1000, true);
	private SignalBuffer<Double> vco2_sig = new SignalBuffer<Double>(1000, true);
	private SignalBuffer<Double> vol_sig = new SignalBuffer<Double>(1000, true);

	private SignalBuffer<Double> hist_sig = new SignalBuffer<Double>(1200, true);

	private int ibi_pos;
	private PrintStream out;
	private long tm;

	private static DeviceCapabilities caps;
	static {
		caps = new DeviceCapabilities( SBCO2.class);
		caps.addStream(StreamID.MEASUREMENT, SBCO2Block.class );
		//caps.addConnection(None);
	}

	public SBCO2() {
	}

	public void setSourceCO2(String co2Loc, RpLinearUnit co2Unit) {
		srcco2_loc = co2Loc;
		srcco2_unit = co2Unit;
	}

	public void setSourceAWP(String awpLoc, RpLinearUnit awpUnit) {
		srcawp_loc = awpLoc;
		srcawp_unit = awpUnit;
	}

	public void setSourceFlow(String flowLoc, RpLinearUnit flowUnit) {
		srcflow_loc = flowLoc;
		srcflow_unit = flowUnit;
	}

	public void setSourceCompliance(String loc, RpLinearUnit unit) {
		srccompliance_loc = loc;
		srccompliance_unit = unit;
	}

	public void setSourceResistance(String loc, RpLinearUnit unit) {
		srcresistance_loc = loc;
		srcresistance_unit = unit;
	}

	public void addWaveform(PersistentItem item) {
		int[] co2Wave = (int[]) IntfUtil.getRawValueByLoc(item, srcco2_loc);
		int[] flowWave = (int[]) IntfUtil.getRawValueByLoc(item, srcflow_loc);
		int[] awpWave = (int[]) IntfUtil.getRawValueByLoc(item, srcawp_loc);

		RpMetric co2Desc = item.getMetric(srcco2_loc);
		double sampleRate = co2Desc.getSampleRate();
		addWaveform(sampleRate, co2Wave, flowWave, awpWave);
	}

	private void addWaveform(double sampleRate, int[] co2_ar, int[] flow_ar, int[] awp_ar) {


		double sampleTime = 1.0 / sampleRate;

		log.debug("state={}", brState);

		int len = co2_ar.length;
		for (int i = 0; i < len; i++) {
			// out.format( "%d\t%d\t%d\n", co2_ar[i], flow_ar[i], awp_ar[i] );
			double co2 = UnitUtil.getValue(srcco2_unit, co2_ar[i]);
			double flow = UnitUtil.getValue(srcflow_unit, flow_ar[i]);
			double awp = UnitUtil.getValue(srcawp_unit, awp_ar[i]);
			double pct_co2 = 0;

			flow = 1000 * flow / 60.0; // convert from L/min to mL/sec

			hist_sig.addData(flow);
			pos++;

			verbose = 0;
			double tm = pos / sampleRate;
			boolean save_raw = (tm > 0 && tm < 3);

			if (brState == null) {
				// ignore...add one point...accumulate data...
				// BLIND ERROR: ASSUME PHASE 3!!!!
				brState = BrState.REST;
				// } else if( phase_len < 10 ) {
				// do nothing
			} else if (brState == BrState.REST && flow > FLOW_THRESHHOLD) {
				int ibi = pos - ibi_pos;
				if (etco2 < MIN_BREATH_ETCO2) {
					// skip the breath...patient not connected
					if (verbose > 2) {
						System.out.print("*");
					}
					//?? } else if (srccompliance_loc != null && compliance <= 0 || resistance <= 0) {
					//?? 	System.out.print("c");
				} else if (ibi > MAX_BREATH_IBI || ibi < MIN_BREATH_IBI) {
					// breath too long or too short
					if (verbose > 2) {
						System.out.print("i");
					}
				} else {

					// this is not the way you really want to do this....
					if (vco2_sig.getSampleCount() > MIN_PHASE3_ETCO2) {
						findPhase3Slope();
					} else {
						// look in the code for the other line that sets this value
						phase3_slope = -1;
					}

					// phase3_intercept = getYIntercept(phase3_pos, phase3_y,
					// phase3_slope);

					findPhase2Values();
					findDeadspace();

					double x_intercept = 0;
					if (phase2_slope > 0.0) {
						x_intercept = -phase2_intercept / phase2_slope;
					}

					// phase3 slope can be less than 0 where calc was not possible
					if (phase3_slope >= phase2_slope) {

						if (verbose > 0) {
							System.out.print("m");
						}
					} else if (x_intercept < 10.0) {
						// phase3 slope can be less than 0 where calc was not possible
						log.debug("d {}", x_intercept);
					} else {
						fire();
						// only clear etco2 if event fired...avoids some
						// spontaineous breathing creating false low values of
						// etco2
						etco2 = 0;
					}
				}
				brState = BrState.INHALE;

				reset_metrics();
			} else if (brState == BrState.INHALE && flow < -FLOW_THRESHHOLD) {
				brState = BrState.EXHALE;
				phase_len = 0;
			} else if (brState == BrState.EXHALE && flow > -FLOW_THRESHHOLD) {
				brState = BrState.REST;
				phase_len = 0;

				if (out_raw != null) { // gives a break in the
					// vco2/vol/pct_co2 lines
					out_raw.format("%8.7g\t", pos / sampleRate);
					out_raw.format("%3.3g\t%3.3g\t%3.3g", co2, flow, awp);
					out_raw.format("\t0\t0\t0"); // vol, vco2, pct_co2);
					out_raw.println();

				}
				vol_sig.addData(exp_vol); // just one fake point
				vco2_sig.addData(co2);
				flow_sig.addData(flow);

			}
			phase_len++;
			breath_len++;

			if (brState != BrState.INHALE) { // etco2 can come from exhale or
				// rest..but not inhale/rebreath
				if (co2 > etco2) {
					etco2 = co2;
				}
			}

			double delta_vol = -flow * sampleTime;

			// co2 rebreathe happens in INSP
			if (Math.abs(awp) > 0.01) {
				pct_co2 = co2 / awp;
				double delta_co2 = pct_co2 * delta_vol;
				vco2 += delta_co2;
			}

			// we don't save the "rest" or "insp" data for phase2/phase3 slope
			// determinations
			// -- rest data is very noisy for slope calculations
			// -- insp data is not involved in phase2/phase3
			if (brState == BrState.EXHALE) {
				exp_vol += delta_vol; // only interested in exhaled volume
				vco2_sig_seg.addData(co2); // ERROR: really need something more
				// like vco2??
				vol_sig_seg.addData(exp_vol);
				fco2_sig_seg.addData(pct_co2);

			}

			if (brState == BrState.EXHALE) {
				if (out_raw != null) {
					out_raw.format("%8.7g\t", pos / sampleRate);
					out_raw.format("%3.3g\t%3.3g\t%3.3g", co2, flow, awp);
					out_raw.format("\t%3.3g\t%3.3g\t%3.3g", exp_vol, vco2, pct_co2);
					out_raw.println();
				}

				vol_sig.addData(exp_vol);
				vco2_sig.addData(co2);
				flow_sig.addData(flow);
			}

		} // end of loop
	} // end of fuction

	private void findDeadspace() {

		double max = 0;
		double vtot = 0;
		phyDeadSpace = 0;

		if (vco2_sig == null || vco2_sig.getSampleCount() < 10) {
			if (verbose > 0) {
				log.warn("vco2_sig is empty");
			}
			return;
		}

		double y0 = vco2_sig.get(6);
		for (int i = 6; i < vco2_sig.getSampleCount(); i++) {

			double y1 = vco2_sig.get(i);
			double delta = y1 - y0;

			if (delta > max) {
				max = delta;
				phyDeadSpace = vol_sig.get(i);
			}

			y0 = y1;
		}
	}

	private void fire() {

		// check that slopes make sense, reject otherwise!
		SBCO2Block sbco2 = new SBCO2Block();

		sbco2.setTm( new Date(tm));

		sbco2.setVco2Data(vco2_sig.asDoubles());
		sbco2.setFlowData(flow_sig.asDoubles());
		sbco2.setVolData(vol_sig.asDoubles());
		sbco2.setMph2(phase2_slope);
		sbco2.setPh2int(phase2_intercept);
		sbco2.setMph3(phase3_slope);
		sbco2.setPh3int(phase3_intercept);
		sbco2.setETCO2(etco2);
		sbco2.setHistData(hist_sig.asDoubles());

		sbco2.setCompliance(compliance);
		sbco2.setResistance(resistance);
		// System.out.println("exp_vol...should be in ml!  deadspace in ml?");
		sbco2.setDs( (int) phyDeadSpace);
		sbco2.setTV( exp_vol);
		sbco2.setVco2((int) vco2);

		int ibi;
		sbco2.setIbi(ibi = pos - ibi_pos);
		sbco2.setExh(vco2_sig.getSampleCount());

		SimpleDateFormat fmt = new SimpleDateFormat("MM/dd/yyyy HH:mm:ss");
		DecimalFormat df4 = new DecimalFormat("0.0000");
		DecimalFormat df1 = new DecimalFormat("0.0");

		if (out != null) {
			out.print(fmt.format(sbco2.getTm()));
			out.print("\t");
			out.print(ibi);
			out.print("\t");
			out.print(df4.format(phase2_slope));
			out.print("\t");
			out.print(df1.format(phase2_intercept));
			out.print("\t");
			out.print(df4.format(phase3_slope));
			out.print("\t");
			out.print(df1.format(phase3_intercept));
			out.print("\t");
			out.print(df1.format(phyDeadSpace));
			out.print("\t");
			out.print(etco2);
			out.println();
		}
		fireStreamEvent(0, this, StreamID.MEASUREMENT, sbco2);

		hist_sig.clear(); // this one is not reset in the resetMetrics() call like the others

	}

	private void findPhase2Values() {

		double slope = 0;
		phase2_slope = 0;
		phase2_pos = 0;
		phase2_y = 0;

		for (int i = 6; i < vco2_sig.getSampleCount(); i++) {

			double dco2 = vco2_sig.get(i) - vco2_sig.get(i - 6);
			double dvol = vol_sig.get(i) - vol_sig.get(i - 6);
			if (dvol > 10) {
				slope = dco2 / dvol;
				if (phase2_slope < slope) {
					phase2_slope = slope;
					phase2_pos = vol_sig.get(i);
					phase2_y = vco2_sig.get(i);

					if (verbose > 2) {
						DecimalFormat df3 = new DecimalFormat("0.000");
						System.out.print(" idx=" + i);
						System.out.print(" x_vol=" + df3.format(exp_vol));
						System.out.print(" y_vco2=" + df3.format(vco2_sig.get(i)));
						System.out.print(" -" + df3.format(vco2_sig.get(i - 6)));
						System.out.print("     dco2=" + df3.format(dco2));
						System.out.print(" dvol=" + df3.format(dvol));
						System.out.print(" ph2 slope=" + df3.format(slope));
						System.out.print("      xpos=" + df3.format(phase2_pos));
						System.out.println();
					}

				}
			}
		}

		phase2_intercept = getYIntercept(phase2_pos, phase2_y, phase2_slope);

	}

	// m = (y-y1)/(x-x1)
	//
	// ...y-intercept at point where x==0
	//
	private double getYIntercept(double x, double y, double m) {
		return y - m * x;
	}

	private void findPhase3Slope() {
		// take last third of the volume, and do a least-squares fit

		double max = (Double) Stats.max(vco2_sig);

		double limit = max * 0.8;

		int max_idx = vco2_sig.getSampleCount() - 1;
		int start_idx = 0;

		for (start_idx = 0; start_idx < max_idx; start_idx++) {
			if (vco2_sig.get(start_idx) > limit) {

				break;
			}
		}

		int len = max_idx - start_idx;
		if (len < 2) {
			phase3_slope = -1;
			phase3_intercept = 0;
			return;
		}
		double[] x = new double[len];
		double[] y = new double[len];
		for (int i = 0; i < len; i++) {
			x[i] = vol_sig.get(i + start_idx);
			y[i] = vco2_sig.get(i + start_idx);
		}

		least_squares(x, y);
		// least_squares_mtj( x, y);

		return;
	}

	private void least_squares(double[] x, double[] y) {
		double x_bar = Stats.mean(x);
		double y_bar = Stats.mean(y);

		double num = 0.0;
		double denom = 0.0;

		for (int i = 0; i < x.length; i++) {
			num += (x[i] - x_bar) * (y[i] - y_bar);
			denom += (x[i] - x_bar) * (x[i] - x_bar);
		}

		phase3_slope = num / denom;
		phase3_intercept = y_bar - phase3_slope * x_bar;
	}

	private void least_squares_mtj(double[] x, double[] y) {

		// hmmm....you only need t and the dimension to calculate the matrix
		// coefficients
		double[][] coeff = { { 0.0, 0.0 }, { 0.0, 0.0 } };
		double[] rhs = new double[2];

		coeff[0][0] = x.length;
		coeff[0][1] = Stats.sum(x); // sum(t(1:n));
		coeff[1][1] = dot_product(x, x); // dot_product(t(1:n),t(1:n));

		coeff[1][0] = coeff[0][1];

		DenseMatrix m = new DenseMatrix(coeff);

		rhs[0] = Stats.sum(y); // sum(d(1:n));
		rhs[1] = dot_product(y, x); // d(1:n)*t(1:n));

		DenseVector rhsv = new DenseVector(rhs);
		DenseVector solution = new DenseVector(2);
		m.solve(rhsv, solution);

		double slope = solution.get(0);
		double b = solution.get(1);

		double errsq = 0;
		for (int i = 0; i < x.length; i++) {
			double err = slope * x[i] + b - y[i];
			errsq += err * err;
		}

		phase3_intercept = b;
		phase3_slope = slope;
	}

	private double dot_product(double[] a, double[] b) {
		double s = 0.0;
		for (int i = 0; i < a.length; i++) {
			s += a[i] * b[i];
		}

		return s;
	}

	private void reset_metrics() {
		vco2 = 0.0;
		phase_len = 0;
		breath_len = 0;
		//
		// etco2 should only be cleared if the event is fired...let it keep
		// inching up
		// in the case of flenches and spont breathing
		//
		// etco2 = 0;
		exp_vol = 0.0;

		vco2_sig_seg.clear();
		vol_sig_seg.clear();
		fco2_sig_seg.clear();

		phase2_intercept = 0.0;
		phase2_slope = 0.0;
		phase2_pos = 0.0;
		phase2_y = 0.0;

		phase3_intercept = 0.0;
		phase3_slope = 0.0;

		ibi_pos = pos;
		compliance = 0;
		resistance = 0;

		vol_sig.clear();
		flow_sig.clear();
		vco2_sig.clear();

		hist_sig.clear();

	}

	@Override
	public DeviceCapabilities getStaticCapabilities() {
		return caps;
	}

	public void setOutputFile(PrintStream out) {
		this.out = out;
		out.print("TMSTAMP\t");
		out.print("IBI\t");
		out.print("mPH2\t");
		out.print("intPH2\t");
		out.print("mPH3\t");
		out.print("intPH3\t");
		out.print("DS\t");
		out.print("EtCO2");
		out.println();
	}

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {

		if (sid == StreamID.WAVEFORM) {
			addWaveform(item);
		} else if (sid == StreamID.MEASUREMENT) {
			compliance = (double) IntfUtil.getScaledValueByLoc(item, srccompliance_loc);
			resistance = (double) IntfUtil.getScaledValueByLoc(item, srcresistance_loc);
		}

	}

}
