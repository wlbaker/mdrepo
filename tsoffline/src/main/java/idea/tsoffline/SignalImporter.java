package idea.tsoffline;

import java.awt.Color;
import java.awt.Component;
import java.io.IOException;
import java.util.LinkedList;
import java.util.List;

import org.piccolo2d.PLayer;
import org.piccolo2d.PNode;
import org.piccolo2d.extras.nodes.PLine;

import com.softhorizons.filterdesigner.GuiUtil;

import icuInterface.DriftRectifier;
import icuInterface.events.ManagementEvent;
import idea.intf.DataTyp;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.PiDatastreamImporter;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpMetric;
import lombok.extern.slf4j.Slf4j;
import idea.tsoffline.canvas.PiccoUtil;

// deriving from component gets addpropertychange and firepropertychange
class SegmentBuffer {
	PLayer data_layer;
	double[] xph = new double[101];
	double[] yph = new double[101];
	int i_high;
	public RpMetric metric;
	public double sample_width;
	public int subtyp;
}

@Slf4j
@SuppressWarnings("serial")
public class SignalImporter extends Component implements StreamConsumer {

	public static final String IMPORTER_POS_PROPERTY = "importerPosition";
	public static final String IMPORTER_FILE_PROPERTY = "importerFile";
	private long startTime = 0;
	// private long endTime = 0;
	private long endTime = 0;
	public static boolean stop = false;

	/*
	 * **********************************************************************
	 * add timeseries data
	 * *********************************************************************
	 */

	public long getStartTime() {
		return startTime;
	}

	public long getEndTime() {
		return endTime;
	}

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {
		// we only consume management events.

		if (sid == StreamID.MANAGEMENT) {
			ManagementEvent block = (ManagementEvent) item;
			RpDevice dev = block.getDevice();
			if (dev == null) {
				log.error("UNEXPECTED NULL DEVICE");
			} else {
				firePropertyChange(IMPORTER_FILE_PROPERTY, null, dev.getDriverName());
			}
		} else {
			log.error("unexpected stream event");
		}

	}

	/**
	 * FIXME: maybe sigs should be Ts type...then I could associate the calibration data with
	 * the PLayer structure.
	 * 
	 * @param dev
	 * @param devName
	 * @param sid
	 * @param sigs
	 * @param loadStartTime
	 * @param loadStopTime
	 * @return
	 * @throws NullPointerException
	 * @throws IOException
	 */
	public HPSplitableLayer[] loadSignal(PiDatastreamImporter dev, String devName, StreamID sid, List<RpMetric> sigs,
			long loadStartTime, long loadStopTime) throws NullPointerException, IOException {

		List<PLayer> layerss = new LinkedList<PLayer>();

		PersistentItem block;

		SegmentBuffer[] segInfo = new SegmentBuffer[sigs.size()];

		int sig_idx = 0;
		int color_idx = 0;
		
		Color colors[] = ColorManager.getColors();
		for (RpMetric sig : sigs) {
			
			segInfo[sig_idx] = new SegmentBuffer();

			PLayer layer = null;  // should check to see if canvas already has the layer
			if (layer == null) {
				// ZERO ZERO CYAN HERE IS WHERE THE IMPORT LAYER IS CREATED
				if (sid == StreamID.ANNOTATION) {
					// annotation layers cannot currently exist in the data importer, they only
					// exist in the session
					GuiUtil.showMessage("FIXME: cannot create anno layer here: layer = canvas.getAnnotationLayer( devName );");
				} else {
					
					HPPathLayer hpp = new HPPathLayer(sig, sid, devName);
					hpp.setVisible(true);
					hpp.setPaint( colors[color_idx] );  // 
					// 071217 ... this looks bad?  hpp.add(layer);
					log.error("FIXME??: should the HPPPathLayer always be a child of a PLayer?");
					layer = hpp;
				}
			}
			layerss.add(layer);
			segInfo[sig_idx].data_layer = layer;
			segInfo[sig_idx].metric = sig;
			sig_idx++;
			color_idx++;
			if( color_idx >= colors.length ) {
				color_idx = 0;
			}
		}

		if (loadStartTime != 0) {
			startTime = loadStartTime;
			dev.seek(loadStartTime);
		} else {
			dev.rewind();
		}

		DriftRectifier wf_drifter = new DriftRectifier(1000, 1000, 100);
		DriftRectifier num_drifter = new DriftRectifier(3000, 1500, 100);

		PNode prev = null;

		long sig_startTime = loadStartTime;

		double[][] num_tmss;
		double[][] num_vals;
		int[] num_idxs;
		if (true) { // really only true for non-fiducial metrics
			num_tmss = new double[sigs.size()][10];
			num_vals = new double[sigs.size()][10];
			num_idxs = new int[sigs.size()];
		}

		boolean first = true;
		while ((block = dev.next()) != null && !stop) {

			if (block.getStreamID() != sid.getCode()) {
				// with a little more work, this wont happen!
				log.error("FIXME: unexpected stream {} != {}", block.getStreamID(), sid.getCode());
				continue;
			}

			long tm = block.getTime();

			if (startTime == 0 && first) {
				startTime = tm;
				sig_startTime = tm;
				wf_drifter.setNextExpectedTime(startTime);
				num_drifter.setNextExpectedTime(startTime);
				first = false;
			}
			// FIXME: Error here?  Changed between versions?  FUBAR?  So I commented it out.
			//if (endTime > tm) {
			//	log.error("TIME OUT OF SEQUENCE BLOCK: {} end ({}) > tm({} ", block, endTime, tm);
			//	continue;
			//}
			if( tm > endTime ) {
				endTime = tm;
			}

			if (loadStopTime != 0 && tm >= loadStopTime) {
				// we have reached the stop time...break out of loop
				break;
			}

			long rectified_tm = tm - sig_startTime; // starts at 0...drifter
													// uses relative time
			rectified_tm = wf_drifter.getRectifiedTime(rectified_tm);
			long rel_num_tm = num_drifter.getRectifiedTime(rectified_tm);

			sig_idx = -1;
			for (RpMetric sig : sigs) {
				sig_idx++;
				
				PLayer layer = segInfo[sig_idx].data_layer;
				double sample_width = segInfo[sig_idx].sample_width;
				int typ = segInfo[sig_idx].subtyp;
				if( sample_width <= 0 || typ == 0 ) {
					RpMetric bm = block.getMetric(sig.getLocation());
					segInfo[sig_idx].sample_width = 1000.0 / bm.getSampleRate();
					segInfo[sig_idx].subtyp = bm.getSubtyp();
					
					sample_width = segInfo[sig_idx].sample_width;
					typ = segInfo[sig_idx].subtyp;
					
					/*
					 * this sig is saved with the layer, be sure it
					 * has all the needed fields
					 */
					sig.setCode( bm.getCode() );
					sig.setName( bm.getName() );
					sig.setUnit( bm.getUnit() );
					sig.setSubtyp( typ );
					sig.setSampleRate( bm.getSampleRate() );
					sig.setSamplesPerPacket( bm.getSampleRate() );
				}
				
				boolean do_waves = false;
				boolean do_metrics = false;
				boolean do_anno = false;
				
				if(typ == DataTyp.INT_TYP) do_metrics = true; // = 1;
				if(typ == DataTyp.LONG_TYP) do_metrics = true; // = 2;
				if(typ == DataTyp.DOUBLE_TYP) do_metrics = true;//  = 3;
				if(typ == DataTyp.BYTE_TYP) do_metrics = true; // = 4;
				if(typ == DataTyp.STRING_TYP) do_anno = true; //  = 5;
				//if(typ == DataTyp.OBJ_TYP) do_anno = true; // = 6;
				if(typ == DataTyp.FLOAT_TYP ) do_metrics = true; //= 7;
				if(typ == DataTyp.INT_ARR_TYP) do_waves = true; // = 14;
				if(typ == DataTyp.OBJ_ARR_TYP) do_waves = true; //= 16;
				if(typ == DataTyp.DOUBLE_ARR_TYP) do_waves = true;// = 19;
				if(typ == DataTyp.FLOAT_ARR_TYP) do_waves = true; //= 23;
				//? if(typ == DataTyp.INVALID_ARR_TYP) do_waves = true; = 0xff;
				//? if(typ == DataTyp.INVALID_TYP ) do_metrics = true; //= 0xfe;
				//? if(typ == DataTyp.BOOLEAN_TYP ) do_metrics = true; //= 0x20;				// // uhhm...maybe
				
				// boolean do_metrics = !do_waves;
				
				if ( do_waves ) { //  sid == StreamID.WAVEFORM) {

					// WARNING: this might be slow...it is quicker to get raw
					// value by MD,
					// but as files change, the data type may change as well,
					// though the LOC is still relevant
					// HAPPENS with composite importers.
					Object vals = IntfUtil.getRawValueByLoc(block, sig.getLocation());

					long drifted_tm = addWaveformSegment( rectified_tm, vals, sample_width, segInfo[sig_idx]);
					if (sig_idx == 0) {
						wf_drifter.setNextExpectedTime(drifted_tm);
					}
				} else if (do_anno) { // sid == StreamID.ANNOTATION) {

					double ts = (tm - sig_startTime);

					// import RRI intervals as fudicial points
					Object item = IntfUtil.getRawValueByLoc(block, sig.getLocation());

					PNode node = LayerUtil.addFiducialPoint(layer, ts / 1000, 0, null);
					node.addAttribute("item", block);
					node.addAttribute("txt", item.toString());
				} else if ( do_metrics ) { // 

					double ts = (tm - sig_startTime);
					// Number item = (Number) IntfUtil.getRawValueByLoc(block,
					// );
					RpMetric m = IntfUtil.getMetricByLoc(block, sig.getLocation());
					Number item = (Number) IntfUtil.getScaledValue(block, m);

					int num_idx = num_idxs[sig_idx];
					// if( num_drifter.isBroken() ) {
					// log.warn("FIXME: Post partial for break signal at: {}",
					// block.getTm() );
					// num_idx = 0;
					// }
					// num_drifter.setNextExpectedTime(tm - sig_startTime +
					// 1000);

					if (item != null) {
						double[] num_tm = num_tmss[sig_idx];
						double[] num_val = num_vals[sig_idx];

						num_tm[num_idx] = ts / 1000;
						num_val[num_idx] = item.doubleValue();
						num_idx++;
						if (num_idx == num_tm.length) {
							// LayerUtil.addSignalPoints(layer, num_tm,
							// num_val);
							PLine path_hi = PiccoUtil.createVariableResolutionLine(sig, num_tm, num_val);
							path_hi.setStrokePaint(Color.WHITE);
							layer.addChild(path_hi);

							/*
							 * copy the last point of the current block to the
							 * first point of the next block...creates
							 * overlapping line segments
							 */
							num_tm[0] = num_tm[num_idx - 1];
							num_val[0] = num_val[num_idx - 1];
							num_idx = 1;
						}
						num_idxs[sig_idx] = num_idx;
					}
				}
			}

			firePropertyChange(IMPORTER_POS_PROPERTY, 0, block.getTime());

		}

		HPSplitableLayer[] arr = new HPSplitableLayer[layerss.size()];
		for( int idx = 0; idx < layerss.size(); idx++ ) {
			PLayer data_layer = layerss.get(idx);
			RpMetric m = sigs.get(idx); // this one is just handy to have!
			
			HPSplitableLayer splitable = new HPSplitableLayer(m );
			splitable.addChild( data_layer );
			splitable.setName( data_layer.getName() );
			splitable.setVisible(true);
			splitable.setLayerSeq( idx );
			splitable.setPaint( data_layer.getPaint() ); 
			splitable.setDefaultColor( (Color) data_layer.getPaint() ); 
			
			splitable.addAttribute("dev_name", data_layer.getAttribute("dev_name") );
			splitable.addAttribute("sig_name", data_layer.getAttribute("sig_name") );
			splitable.addAttribute("sig_loc", data_layer.getAttribute("sig_loc") );			

			char code = 'W';
			if (sid != null) {
				code = (char) sid.getCode();
			}
			splitable.addAttribute("sid", "" + code); // this one is just handy to have!

			arr[idx] = splitable;
		}
		return arr;
	}

	/**
	 * addWaveformBlock()
	 * 
	 * return: end time for this block/start time expected for next block
	 */

	/*
	 * segInfo is used to buffer data which is to be stitched together into
	 * larger data nodes.
	 */

	static public long addWaveformSegment( long reltime_ms, Object vals, double sampleWidth,
			SegmentBuffer segInfo) {

		int typ = 0;
		int len;
		int[] idata = null;
		float[] fdata = null;
		double[] ddata = null;

		if (vals == null) {
			log.error("EMPTY VALS -- MIGHT CAUSE TIME SHIFT");
			return reltime_ms;
		} else {
			if (vals instanceof int[]) {
				idata = (int[]) vals;
				len = idata.length;
				typ = 1;
			} else if (vals instanceof float[]) {
				fdata = (float[]) vals;
				len = fdata.length;
				typ = 2;
			} else if (vals instanceof double[]) {
				ddata = (double[]) vals;
				len = ddata.length;
				typ = 3;
			} else {
				log.error("DONT KNOW HOW TO HAND DATA TYP: {}", vals.getClass());
				return reltime_ms;
			}
		}

		double[] xsegbuf = segInfo.xph;
		double[] ysegbuf = segInfo.yph;

		int i_high = segInfo.i_high;

		// this.data = data;
		// this.stats = new SampleStats(data);

		int idx = 0;

		double msPos = reltime_ms;
		// boolean debug = false;
		//

		PLayer layer = segInfo.data_layer;
		RpMetric sig = segInfo.metric;
		for (int i = 0; i < len; i++) {

			xsegbuf[i_high] = (msPos / 1000.0);
			if (typ == 1) {
				ysegbuf[i_high] = idata[idx++];
			} else if (typ == 2) {
				ysegbuf[i_high] = fdata[idx++];
			} else if (typ == 3) {
				ysegbuf[i_high] = ddata[idx++];
			}

			i_high++; // don't increment i_high until low-values are
			// extracted

			if (i_high == xsegbuf.length) {

				PLine path_hi = PiccoUtil.createVariableResolutionLine(sig, xsegbuf, ysegbuf);
				layer.addChild(path_hi);

				xsegbuf[0] = xsegbuf[xsegbuf.length - 1];
				ysegbuf[0] = ysegbuf[ysegbuf.length - 1];
				i_high = 1;
			}

			msPos += sampleWidth;
		}

		segInfo.i_high = i_high;

		return (long) msPos;
	}

}
