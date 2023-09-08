package unused;

import idea.message.StreamID;
import idea.schema.rp.RpLinearUnit;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpUnit;

@Slf4j
public class BuildVolume {
	protected void buildVolumeSignal() {
		OfflineSignal flowSig = null;
		OfflineSignal volSig = null;
		for (OfflineDevice dev0 : AppModel.getDevices()) {
			OfflineStream stream = dev0.getStream(StreamID.WAVEFORM);
			if (stream == null) {
				continue;
			}

			List<OfflineSignal> sigs = stream.getCachedSignals();
			if (sigs == null) {
				continue;
			}

			/*
			 * HARD CODED VALUE USED FOR INSPIROGRAPH / HSE
			 */
			for (OfflineSignal sig : sigs) {
				String sigName = sig.getCode();
				if ("PulmFl1".equals(sigName)) {
					flowSig = sig;
					break;
				}
			}
		}

		if (flowSig == null) {
			log.error("Could not find flow signal.");
		}

		double[][] dat = flowSig.getDataInRange(0, -1);
		RpMetric flowDesc = flowSig;
		RpUnit flowUnit = flowDesc.getUnit();
		double[] flow = dat[1];
		double[] vol = new double[flow.length];

		/*
		 * algorithm to compute flow derived volume
		 */

		/*
		 * FIRST: find first breath: start_pos and an end position...gives a set of
		 * breaths to recalc the flow zero Consider the range of zero'ing the flow over
		 * a 20 sec interval at 500 hz.
		 */
		double avg = 0.0;
		int start_pos = findBreathStart(0, flow, flowUnit);
		int end_pos = -1;

		if (start_pos > 0) {
			// find end position
			end_pos = findBreathStart(start_pos + 500 * 10, flow, flowUnit);

			for (int i = start_pos; i < end_pos; i++) {
				avg += flowUnit.transform_d(flow[i]);

			}
			if (end_pos > start_pos) {
				avg = avg / (end_pos - start_pos);
			}
		}

		// Hard code the flow unit!
		RpLinearUnit lu = (RpLinearUnit) flowUnit;
		// lu.setM(1);
		// lu.setB(-2006 );

		/*
		 * SECOND: compute derived breath
		 */
		double cumsum = 0.0;
		for (int i = start_pos; i < flow.length; i++) {
			cumsum += (flowUnit.transform_d(flow[i]) - avg);
			if (cumsum < 25000) { // simulate a slight leak to get VOL to 0
									// between breaths
				cumsum -= 0.01;
			}
			if (cumsum < 0) // volume can never go below zero
				cumsum = 0;

			vol[i] = cumsum / 500.0; // emperically derived...Hz?
		}

		/*
		 * Add new signal to layer
		 */
		OfflineStream derivedStream = new OfflineStream(StreamID.WAVEFORM);
		OfflineDevice derivedDev = AppModel.getDevice("DERIVED");
		if (volSig == null) {
			RpUnit u = new RpLinearUnit(1, 0, "mL");
			RpMetric volDesc = new RpMetric("DERIVEDVOL", "Vol", "Flow Derived Volume", u, DataTyp.DOUBLE_ARR_TYP);
			volDesc.setSampleRate(flowDesc.getSampleRate());
			volSig = new OfflineSignal(volDesc, TimeseriesType.TT_DATA);
			volSig.setDefaultColor(Color.BLACK);
			volSig.setColor(Color.BLACK);
		}
		vol_layer = new HPPathLayer(volSig, StreamID.WAVEFORM, "DERIVED");
		SignalImporter.addWaveformData(volSig, 0, vol); // layer must be
														// attached before you
														// can add data

		derivedStream.addSignal(volSig);
		derivedDev.addStream(derivedStream);

		TsPSwingCanvas canv = tpanel.getCanvas1();
		canv.addSignalLayer(vol_layer);

		manager.refresh(); // refresh the dpanel after creating a derived signal
	}

	private int findBreathStart(int offset, double[] flow, RpUnit flowUnit) {

		NumberFormat nf = new DecimalFormat("000.00");

		int consec_positive = 0;
		int start_pos = -1;
		// double max = 0;
		for (int i = offset; i < flow.length; i++) {
			double dvol = flowUnit.transform_d(flow[i]);
			// if( i % 50 == 0 ) {
			// System.out.print(" " + nf.format(dvol) );
			// }
			// if( i % 500 == 0 ) {
			// System.out.print("\n");
			// }
			// if( dvol > max ) {
			// max = dvol;
			// System.out.println("\n" + i + " MAX**" + max);
			// }
			if (dvol > 200.0) {
				if (consec_positive == 0) {
					start_pos = i - 1;
					// System.out.println("\nSTART CONSEC: " + i + " DVOL=" +
					// dvol);
				}
				consec_positive++;

				if (consec_positive > 100) { // flow must be for at least a
												// second
					break;
				}
			} else {
				// if( consec_positive > 0 ) {
				// System.out.println("\nBREAK CONSEC: " + i + " DVOL=" + dvol +
				// " DELTA=" + consec_positive);
				// }
				consec_positive = 0;
				start_pos = -1;
			}
		}

		return start_pos;
	}


}
