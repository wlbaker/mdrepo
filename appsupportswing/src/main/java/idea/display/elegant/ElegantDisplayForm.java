/*
 * 
 *  this form is built from receipt of a DisplayConfig event
 *  --> used currently for Dragers
 *  
 */

package idea.display.elegant;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Stroke;
import java.io.IOException;
import java.util.Calendar;
import java.util.Date;
import java.util.LinkedList;
import java.util.List;

import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;
import javax.swing.border.CompoundBorder;
import javax.swing.border.EmptyBorder;
import javax.swing.border.LineBorder;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;
import com.jgoodies.forms.layout.RowSpec;

import icuInterface.RpUtil;
import icuInterface.message.CompositeItem;
import icuInterface.message.NumericItem;
import idea.display.BandLayout;
import idea.display.CardioStrip;
import idea.display.ChartRefresher;
import idea.display.DisplayUtil;
import idea.display.FieldData;
import idea.display.InstrumentDisplayInterface;
import idea.display.ParameterLayout;
import idea.display.RefreshablePanel;
import idea.display.WaveformData;
import idea.intf.DataTyp;
import idea.intf.IDEAClient;
import idea.intf.IDEATransferInterface;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.DisplayConfig;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpStream;
import lombok.extern.slf4j.Slf4j;
import idea.IdeaTimeManager;

/**
 * @author User #2
 */
@Slf4j
@SuppressWarnings("serial")
public class ElegantDisplayForm extends JPanel implements InstrumentDisplayInterface, StreamConsumer, RefreshablePanel {

	private static int HISTORY_JOB_BASE = 400;
	private int HISTORY_JOB;

	// private DisplayConfig display;
	JPanel[] valuePanels;
	protected List<CardioStrip> charts;
	private JPanel content;

	private ChartRefresher refresher;

	private StreamProducer driver;
	private RpDevice conf = null;
	private Double scale_min_range;
	private JLabel portLabel;
	protected JPanel center;
	private JPanel north;

	public ElegantDisplayForm(StreamProducer driver, DisplayConfig display) {
		initComponents();

		HISTORY_JOB_BASE++;
		HISTORY_JOB = HISTORY_JOB_BASE;

		setBackground(Color.BLACK);
		refresher = ChartRefresher.getInstance();

		if (display != null) {
			setDisplay(display);
		}

		reset(driver);
	}

	@Override
	public void reset(StreamProducer driver) {
		StreamProducer old_driver = this.driver;

		if (old_driver != null) {
			old_driver.removeStreamListener(this);
		}

		this.driver = driver;
		if (driver != null) {
			conf = driver.getConfiguration();
			driver.addStreamListener(StreamID.MEASUREMENT, this);
			driver.addStreamListener(StreamID.SETTINGS, this);
			driver.addStreamListener(StreamID.WAVEFORM, this);
			driver.addStreamListener(StreamID.DISPLAY, this);
		}
	}

	synchronized private JPanel buildDisplay(DisplayConfig display) {

		int param_col_count = 1;
		int param_row_count = 1; // (display.getHorizPboxes() > 0) ? 1 : 0;
		int charts_col;
		int first_param_col;

		System.err.println("FIXME WLB: int param_row_count = 1; // (display.getHorizPboxes() > 0) ? 1 : 0;");

		List<BandLayout> bandss = display.getBands();
		// int row_count = bands.size();
		// int vert_count = display.getVertPboxes();
		// row_count += param_row_count; // wlb june 2012

		JPanel panel_out = new JPanel();
		panel_out.setBackground(Color.BLACK);

		String colLayout = param_col_count + "*($lcgap, [80dlu,default]), $lcgap";
		if (display.isLeftLayout()) {
			colLayout = colLayout + ", fill:default:grow";
			charts_col = 2 * param_col_count + 2;
			first_param_col = 2;
		} else {
			colLayout = "fill:default:grow, " + colLayout;
			charts_col = 1;
			first_param_col = 3;
		}

		FormLayout fl = new FormLayout(colLayout, "$lgap");

		panel_out.setLayout(fl);

		CellConstraints cc = new CellConstraints();

		// bandPanels = (bandss == null || bandss.size() == 0) ? null : new JPanel[bandss.size()];

		valuePanels = buildDisplayPBoxes(conf, display);

		int param_ccol = 0;
		int param_idx = 0;
		int pboxes_length = display.getNumPBoxes();

		charts = new LinkedList<CardioStrip>();

		int band_row = 1;

		for (BandLayout band : bandss) {

			if (band == null) {
				log.error("NULL BAND");
				continue;
			}

			if (band.getWaves() == null) {
				log.warn("NO WAVES FOR BAND");
				continue;
			}

			CardioStrip chart = new CardioStrip();
			chart.setBackground(Color.BLACK);
			chart.enableAutoscale(false);

			for (WaveformData wave : band.getWaves()) {
				String loc = wave.getLoc();
				RpStream stream = IntfUtil.getStream(conf, StreamID.WAVEFORM);
				RpMetric desc = RpUtil.getMetricFromStream(stream, loc);

				if (desc == null) {
					log.warn("SIGNAL NOT FOUND: {}", loc);
				} else {
					Color color = DisplayUtil.getColorFromDrager(wave.getWaveColor());

					chart.addWaveformDescription(desc, color, wave.getRangeMax(), wave.getRangeMin(), false);
				}
			}
			byte attr = band.getBandAttribute();
			if (attr == 2) {
				log.error("FIXME: test against evita...(attr == 2)");
			}

			int band_weight = band.getBandAttribute();
			if (band_weight == 0) {
				band_weight = 1;
			}
			int display_h = 2 * band_weight - 1;

			RowSpec[] rs = RowSpec.decodeSpecs(band_weight + "*(fill:default:grow,$lgap)");
			for (RowSpec r : rs) {
				fl.appendRow(r);
			}

			panel_out.add(chart, cc.xywh(charts_col, 2 * band_row, 1, display_h));
			band_row += band_weight;

			if (scale_min_range != null) {
				chart.setScaleMinimumRange(scale_min_range);
			}

			refresher.addChart(chart);
			charts.add(chart);

		}

		/*
		 * Create vertical parameter panel
		 */

		int n_vert_boxes = display.getVertPboxes(); // FIXME: we could have more vert boxes than this!

		int vp_col = first_param_col;
		for (int idx = 0; idx < n_vert_boxes; idx++) {
			int row = idx % band_row;
			if (idx > 0 && row == 0) {
				vp_col += 2;
			}
			int vp_row = 2 * row + 1 + 1; // row 1 is lgap, row 2 is usable

			JPanel vp = valuePanels[param_idx++];
			vp.setBorder(new CompoundBorder(new LineBorder(Color.DARK_GRAY), new EmptyBorder(4, 4, 4, 4)));
			panel_out.add(vp, cc.xy(vp_col, vp_row));
		}

		/*
		 * Create horizontal parameter panel
		 */
		JPanel horizPanel = null;
		param_ccol = 0;
		int sub_row = 0;

		int n_hz_boxes = pboxes_length - param_idx;
		for (; param_idx < pboxes_length; param_idx++) {
			if (horizPanel == null) {

				// horizontal panel can hold 6 boxes...always
				colLayout = n_hz_boxes + "*([70dlu,default])";
				String rowLayout = "fill:default"; // at least one row
				if (param_row_count > 1) {
					rowLayout = rowLayout + "," + (param_row_count - 1) + "*($lgap, fill:default)";
				}
				horizPanel = new JPanel();
				horizPanel.setLayout(new FormLayout(colLayout, rowLayout));
				horizPanel.setBackground(Color.BLACK);

				RowSpec[] rs = RowSpec.decodeSpecs("[50dlu,default], $lgap");
				for (RowSpec r : rs) {
					fl.appendRow(r);
				}

				panel_out.add(horizPanel, cc.xyw(charts_col, 2 * band_row, 3));
				band_row++;
			}

			if (valuePanels[param_idx] != null) {
				// null can happen when using the default display on a config
				// that is different...or not collecting displayed data
				vp_col = n_hz_boxes - param_ccol;
				int vp_row = 2 * sub_row + 1;
				if (vp_col < 1) {
					log.error("ERROR in column calculations!");
					log.error("    NEED A SECOND ROW!");
				} else {
					// System.out.println(param_ccol + "pbox_idx=" + param_idx +
					// " horiz panel adding: " + valuePanels[param_idx]);
					JPanel vp = valuePanels[param_idx];
					vp.setBorder(new CompoundBorder(new LineBorder(Color.DARK_GRAY), new EmptyBorder(4, 4, 4, 4)));
					horizPanel.add(vp, cc.xy(vp_col, vp_row));
				}
			}
			param_ccol++;
		}

		return panel_out;
	}

	protected JPanel[] buildDisplayPBoxes(RpDevice conf2, DisplayConfig display) {

		int n = display.getNumPBoxes();
		JPanel[] valuePanels = (n == 0) ? null : new JPanel[n];

		int idx = 0;
		for (ParameterLayout box : display.getParameterBoxs()) {

			if (box == null || box.fields == null || box.fields.length == 0) {
				log.warn("Param box is empty?  param={}", box);
				continue;
			}
			FieldData[] params = box.fields;

			/*
			 * FIXME: I should not need to check against these two streams
			 */
			RpStream stream = IntfUtil.getStream(conf2, StreamID.MEASUREMENT);
			RpStream stream2 = IntfUtil.getStream(conf2, StreamID.SETTINGS);
			ValuePanelInterface vp = ValueFactory.createPanel(box.getFormat(), box.getForeground());
			for (FieldData param : params) {
				if (param == null) {
					log.error("param cannot be null for value panel.");
					continue;
				}
				String loc = param.getLoc();
				if (loc == null) {
					log.error("loc cannot be null for value panel.");
					continue;
				}

				RpMetric md = RpUtil.getMetricFromStream(stream, loc);
				if (md == null) {
					md = RpUtil.getMetricFromStream(stream2, loc);
				}
				if (md == null) {
					log.warn("could not find loc: {} dev: {}", param.getLoc(), conf2.getName());
				} else {
					vp.addParameter(md);
				}
			}
			valuePanels[idx++] = (JPanel) vp;
			vp.clear();
		}

		return valuePanels;
	}

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {
		try {
			if (north != null) {
				if (north instanceof StreamConsumer) {
					((StreamConsumer) north).streamEvent(jobID, source, sid, item);
				}
			}
			_eventOccurred(source, sid, item);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}

	public void _eventOccurred(StreamProducer source, StreamID sid, PersistentItem item) throws IOException {
		if (sid == StreamID.WAVEFORM) {
			waveformEvent(source, item);
		} else if (sid == StreamID.MEASUREMENT) {
			numericsEvent(source, item); // find it in the parameter boxes

		} else if (sid == StreamID.SETTINGS) {
			numericsEvent(source, item); // find it in the parameter boxes

		} else if (sid == StreamID.DISPLAY) {
			log.info("display event received");

			setDisplay((DisplayConfig) item);
		}
	}

	private Runnable displayBuilder = new Runnable() {

		@Override
		public void run() {

			if (center != null) {
				content.remove(center);
			}

			center = buildDisplay(display);
			if (center != null) {
				content.add(center, BorderLayout.CENTER);
			}

			String portDesc = RpUtil.getParam(conf, "host");
			if (portDesc == null) {
				portDesc = conf.getParam().get("port");
			} else {
				portDesc = portDesc + "/" + conf.getParam().get("port");
			}
			if (portLabel != null) {
				portLabel.setText("Port: " + portDesc);
			}
		}
	};
	private DisplayConfig display;

	public void setDisplay(final DisplayConfig ddisplay) {

		if (ddisplay == null || ddisplay.getBands() == null) {
			log.error("invalid display: {}", ddisplay);
			return;
		}
		// put this request on the GUI thread

		this.display = ddisplay;
		SwingUtilities.invokeLater(displayBuilder);
	}

	synchronized protected void numericsEvent(Object source, PersistentItem item) {
		if (valuePanels == null) {
			return; // nothing to display here
		}
		if (item == null) {
			log.error("display config: FIXME:  no data --> clear display values");
			this.clear();
			return;
		}
		RpMetric[] items = IntfUtil.getMetrics(item);

		if (items == null) {
			return; // nothing to process...should probably never be sent
		}

		processNumericItems(item, items);
	}

	private void processNumericItems(PersistentItem block, RpMetric[] metrics) {
		for (RpMetric desc : metrics) {
			String loc = desc.getLocation();
			boolean found = false;
			for (JPanel p : valuePanels) {
				ValuePanelInterface vp = (ValuePanelInterface) p;
				// assert (p != null) : "INTERNAL ERROR: null panel!";

				if (p == null) {
					// System.err.println(
					// "[DragerDeviceForm] skipping null name panel." );
					continue;
				}

				if (vp.containsLoc(loc)) {
					Object val = IntfUtil.getScaledValue(block, desc);
					// Number val = IntfUtil.getScaledValueByLoc(block, loc);
					vp.setValue(desc, val);
					found = true;
					break;
				}
			}
			// BETA2 / FIXME: maybe need more attention to items not found?
			if (!found) {
				Object val = IntfUtil.getScaledValueByLoc(block, loc);
				if (val instanceof CompositeItem) {
					log.error("FIXME: stub drilling on composite: {}", loc);
					CompositeItem comp = (CompositeItem) val;
					NumericItem[] sub_items = comp.getValues();
					log.error("FIXME: processNumericItems( sub_items );");
					continue;
				} else {
					log.info("item not found for display: value: {}  loc: {}", val, loc);
				}
			}
		}
	}

	synchronized protected void waveformEvent(Object source, PersistentItem item) {
		if (item == null) {
			log.warn("displayconfig wf: got no-data event -- ignore");
			return;
		}
		RpMetric[] waveforms = IntfUtil.getMetrics(item);

		long tm = item.getTime();
		for (int idx = 0; idx < waveforms.length; idx++) {
			RpMetric wave = waveforms[idx];
			CardioStrip chart = findChart(wave);

			if (chart == null) {
				log.debug("NO CHART: {}", wave);
				continue;
			}

			int subtyp = wave.getSubtyp();
			if (subtyp == DataTyp.INT_ARR_TYP) {
				int[] wf = (int[]) IntfUtil.getRawValue(item, wave);
				chart.addWaveformItem(tm, wave, wf);
			} else if (subtyp == DataTyp.FLOAT_ARR_TYP) {
				float[] wf = (float[]) IntfUtil.getRawValue(item, wave);
				chart.addWaveformItem(tm, wave, wf);
			} else if (subtyp == DataTyp.DOUBLE_ARR_TYP) {
				double[] wf = (double[]) IntfUtil.getRawValue(item, wave);
				chart.addWaveformItem(tm, wave, wf);
			} else {
				log.error("CANNOT HANDLE DATA TYPE FOR DISPLAY: {}", subtyp);
			}
		}
	}

	protected CardioStrip findChart(RpMetric waveform) {
		CardioStrip chart_found = null;

		if (charts != null) {
			Object loc = waveform.getLocation();

			charts_loop: for (CardioStrip chart : charts) {
				if (chart == null) {
					// System.err.println("null chart!");
					continue;
				}
				RpMetric[] waves = chart.getWaveforms();
				if (waves == null) {
					// null entry in the chart
					continue;
				}
				for (RpMetric chart_desc : waves) {

					if (chart_desc != null && chart_desc.getLocation() != null) {
						if (chart_desc.getLocation().equals(loc)) {

							chart_found = chart;
							// System.out.println( "chart=" + idx + " for: " +
							// chart_desc );
							break charts_loop;
						}
					}
				}
			}
		}
		return chart_found;
	}

	private void initComponents() {
		content = new JPanel();
		CellConstraints cc = new CellConstraints();

		// ======== this ========
		setLayout(new FormLayout("default:grow", "fill:default:grow, $lgap")); // 14APR16 , default"));

		// ======== content ========
		{
			content.setLayout(new BorderLayout());

			// 14APR16 content.add(subpanel = new DisplayMetaSubpanel(this), BorderLayout.SOUTH);
		}
		add(content, cc.xy(1, 1));
		// //GEN-END:initComponents
	}

	public StreamProducer getDriver() {
		return driver;
	}

	public void autoScale(String loc) {
		System.err.println("WARNING: only needed in simulation mode");
		if (charts != null) {
			for (CardioStrip strip : charts) {
				strip.autoScale(loc);
			}
		}

	}

	@Override
	public void clear() {
		if (charts != null) {
			for (CardioStrip strip : charts) {
				strip.clear();
			}
		}
	}

	public void setStroke(Stroke stroke) {
		if (charts != null) {
			for (CardioStrip strip : charts) {
				strip.setPenStroke(stroke);
			}
		}
	}

	public void setScaleMinimumRange(Double range) {
		this.scale_min_range = range;
		if (charts != null) {
			for (CardioStrip strip : charts) {
				strip.setScaleMinimumRange(range);
			}
		}
	}

	public void setRealtime(boolean running) {
		if (charts != null) {
			for (CardioStrip strip : charts) {
				strip.setSweepSpeed(0);
			}
		}
	}

	@Override
	public void refresh(IDEAClient idea, Date dt) {

		clear();

		if (dt == null) {
			dt = IdeaTimeManager.getCurrentTime();
		}

		Calendar cal = Calendar.getInstance();
		if (dt != null) {
			cal.setTime(dt);
		}
		cal.add(Calendar.SECOND, -15);
		Date dtStart = cal.getTime();
		Date dtEnd = dt;

		if (dt != null) {
			cal.setTime(dt);
			cal.add(Calendar.SECOND, 5);
			dtEnd = cal.getTime();
		}

		// setRangeEndTime(dtEnd);

		IDEATransferInterface req = idea.createTransferRequest(HISTORY_JOB, dtStart, dtEnd, conf, 0);
		req.addStreamListener(null, this);
		try {
			req.connect();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public void addContentPane(JPanel panel, String constraint) {
		north = panel;
		content.add(panel, constraint);
		content.doLayout();
	}

	@Override
	public void update() {
		// ignore...no scrolling trends to update
	}

	protected JPanel[] getValuePanels() {
		return valuePanels;
	}

// 04APR16	public void addDisplay(String displayName, DisplayConfig display) {
// 04APR16		subpanel.add(displayName, display);
// 04APR16	}

	public DisplayConfig getDisplay() {
		return display;
	}

	@Override
	public void setDisplay(DisplayConfig display, boolean overwrite, boolean ignoreupdates) {

		log.error("fixme: overwrite note implemented");
		log.error("fixme: ignoreupdates note implemented");
		this.setDisplay( display );
	}

	@Override
	public RpDevice getCapabilities() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public float[] getDisplayData(String loc, float[] arr) {
		// TODO Auto-generated method stub
		return null;
	}

}
