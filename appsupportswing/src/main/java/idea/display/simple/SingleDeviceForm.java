/*
 * Created by JFormDesigner on Thu Dec 17 14:21:21 CST 2009
 */

package idea.display.simple;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Stroke;
import java.io.IOException;
import java.lang.reflect.Field;
import java.util.Calendar;
import java.util.List;

import javax.swing.JPanel;
import javax.swing.JScrollPane;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;
import com.jgoodies.forms.layout.RowSpec;

import icuInterface.ConnectionStatus;
import icuInterface.RpUtil;
import icuInterface.events.ConnectionItem;
import idea.display.BandLayout;
import idea.display.CardioStrip;
import idea.display.ChartRefresher;
import idea.display.DisplayUtil;
import idea.display.FieldData;
import idea.display.ParameterLayout;
import idea.display.WaveformData;
import idea.intf.DataTyp;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.DisplayConfig;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpStream;
import idea.schema.rp.RpUnit;
import lombok.extern.slf4j.Slf4j;

/**
 * @author User #2
 */
@Slf4j
@SuppressWarnings("serial")
public class SingleDeviceForm extends JPanel implements StreamConsumer {
	private static final int PARAM_COLS = 8;

	private StreamProducer driver;

	private JPanel metricsPanel;

	private SingleValuePanel[] valuePanels;

	private JScrollPane waveformPanel;

	private CardioStrip[] charts;
	private ChartRefresher refresher;

	private int[] sampleRate;

	private int verbose = 0;

	private RpDevice conf;

	public SingleDeviceForm(StreamProducer driver) {
		initComponents();

		this.driver = driver;
		this.conf = driver.getConfiguration();

		refresher = ChartRefresher.getInstance();
		// refresher.addChart(cardioChart);

		if (conf != null) {
			// used for debugging
			setName(conf.getName());
			log.debug("CREATING SINGLEDEVICEPANEL: {}", getName());
		} else {
			log.debug("CREATING UNNAMED DEVICE PANEL");
		}

	}

	public StreamProducer getDriver() {
		return driver;
	}

	private JPanel buildMetricsPanel(List<ParameterLayout> boxes) {
		int count = boxes.size();

		if (count == 0) {
			valuePanels = null;
			return null;
		}

		JPanel p = new JPanel();
		CellConstraints cc = new CellConstraints();

		int col_count = Math.min(PARAM_COLS, count);

		FormLayout fl = new FormLayout(col_count + "*([60dlu,default], $lcgap), default", "$lgap, default");

		p.setLayout(fl);

		valuePanels = new SingleValuePanel[count];
		int col = 0;
		int row = 0;

		RpStream stream = RpUtil.getStream(conf, StreamID.MEASUREMENT);
		for (int idx = 0; idx < count; idx++) {
			ParameterLayout box = boxes.get(idx);
			SingleValuePanel svp = new SingleValuePanel();

			FieldData[] params = box.getFieldData();

			// FIXME: expecting one and only one param for now
			FieldData param = params[0];
			RpMetric md = RpUtil.getMetricFromStream(stream, param.getLoc());
			RpUnit unit = md.getUnit();
			svp.setName(md.getLocation().toString());
			svp.clear();
			if (unit != null) {
				svp.setUnits(unit.getUnitName());
			}

			String code = md.getCode();
			if (code == null) {
				code = md.getLocation().toString();
			}
			svp.setCode(code);

			valuePanels[idx] = svp;

			p.add(valuePanels[idx], cc.xy(2 * col + 1, 2 * row + 2)); // skip related-gap row&col
			col++;
			if (col >= PARAM_COLS) {
				row++;
				col = 0;
				RowSpec[] rs = RowSpec.decodeSpecs("$lgap, default");
				// RowSpec rs = new RowSpec(100);
				fl.appendRow(rs[0]);
				fl.appendRow(rs[1]);
			}
		}

		return p;
	}

	private Color getColorFromName(String colorName) {
		try {
			// Find the field and value of colorName
			Field field = Class.forName("java.awt.Color").getField(colorName);
			return (Color) field.get(null);
		} catch (Exception e) {
			return null;
		}
	}

	public JPanel buildWaveformPanel(List<BandLayout> bands) {
		JPanel p = null;

		if (bands == null || bands.size() == 0) {
			return null;
		}

		CellConstraints cc = new CellConstraints();
		p = new JPanel();

		int band_count = bands.size();
		p.setLayout(new FormLayout("default:grow", band_count + "*(fill:[60dlu,default,60dlu], $lgap), default"));

		RpStream stream = RpUtil.getStream(conf, StreamID.WAVEFORM );

		sampleRate = new int[band_count];
		charts = new CardioStrip[band_count];
		for (int idx = 0; idx < band_count; idx++) {
			CardioStrip chart = new CardioStrip();
			BandLayout band = bands.get(idx);
			
			chart.setTimeScalesInMillis(10000);
			
			List<WaveformData> waves = band.getWaves();
			if( waves != null ) {
			for(  WaveformData wf_setup : waves ) {
				RpMetric wave = RpUtil.getMetricFromStream(stream, wf_setup.getLoc() );
				byte byte_col = wf_setup.getWaveColor();
				Color color = DisplayUtil.getColorFromDrager( byte_col );
				chart.addWaveformDescription(wave, color, 0, 0, true);
				chart.setName( wave.getCode() );  // FIXME...name if more than one wf??
			}

			refresher.addChart(chart);
			}
			
			charts[idx] = chart;
			p.add(chart, cc.xy(1, 2 * idx + 1));
		}

		return p;
	}

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {
		try {
			_eventOccurred(jobID, source, sid, item);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}

	public void _eventOccurred(int jobID, StreamProducer source, StreamID sid, PersistentItem item) throws IOException {
		if (sid == StreamID.WAVEFORM) {
			waveformEvent(source, item);

		} else if (sid == StreamID.MEASUREMENT) {
			persistentItemEvent(source, item);

		} else if (sid == StreamID.CONNECTION) {
			ConnectionItem ce = (ConnectionItem) item;
			if (ce.getStatus() != ConnectionStatus.CONNECTED) {
				clear();
			}
		}
	}

	public void waveformEvent(Object sender, PersistentItem item) {

		if (item == null) {
			log.warn("unexpected null waveform block");
			return;
		}
		RpMetric[] waveforms = IntfUtil.getMetrics(item);
		if (waveforms == null) {
			log.warn("NO WAVEFORMS IN EVENT");
			return;
		}

		for (int idx = 0; idx < waveforms.length; idx++) {

			RpMetric wf = waveforms[idx];

			int chart_idx = findChart(wf);
			if (chart_idx < 0) {

				// ??

			} else {

				if (wf.getSampleRate() != sampleRate[chart_idx]) {

					sampleRate[chart_idx] = wf.getSampleRate();

					Calendar cal = Calendar.getInstance();
					long ms = cal.getTimeInMillis() - item.getTime();

					refresher.setTimeDeltaInMillis_DELETE_ME_OBSOLETE(ms);
				}

				Object v = IntfUtil.getRawValue(item, wf);
				if (v instanceof int[]) {
					charts[chart_idx].addWaveformItem(item.getTime(), wf, (int[]) v);
				} else if (v instanceof float[]) {
					charts[chart_idx].addWaveformItem(item.getTime(), wf, (float[]) v);
				}
			}
		}
	}

	private int findChart(RpMetric wf) {
		int chart_idx = -1;

		if (charts != null) {
			Object loc = wf.getLocation();

			for (int i = 0; i < charts.length; i++) {
				if( charts[i] == null ) {
					continue;  // race condition...receiving data before charts created on event thread
				}
				RpMetric[] waves = charts[i].getWaveforms();
				if( waves == null ) {
					continue;  // reconfigured by user after setup...run time
				}

				for (RpMetric chart_desc : waves) {
					if (chart_desc.getLocation().equals(loc)) {
						chart_idx = i;
						break;
					}
				}
			}
		}
		return chart_idx;
	}

	private void persistentItemEvent(Object source, PersistentItem block) {

		if (valuePanels == null) {
			return; // nothing to display here
		}
		if (block == null) {
			log.error("unexpected message: no data <block> from {}", source);
			return;
		}
		RpMetric[] items = block.getMetrics();

		if (items == null) {
			return; // nothing to process...should probably never be sent
		}

		for (RpMetric desc : items) {
			if( desc == null ) {
				log.error("null description");
				continue;
			}
			String name = desc.getLocation();
			boolean found = false;
			for (SingleValuePanel p : valuePanels) {
				String p_name = p.getName();
				log.debug("panel name: ", p_name);
				if (p == null) {
					// this can happen if you have more parameters selected than
					// can be displayed
				} else if (name.equals(p_name)) {
					RpUnit unit = desc.getUnit();

					if (desc.getSubtyp() == DataTyp.STRING_TYP) {
						Object val = IntfUtil.getRawValue(block, desc);

						if (val == null) {
							p.setValue("");
						} else {
							p.setValue("" + val);
						}
					} else {
						Number val = (Number) IntfUtil.getScaledValue(block, desc);
						if (val == null) {
							p.setValue("");
						} else {
							p.setValue((Number) val);
						}
					}
					found = true;
					break;
				}
			}
			if (!found) {
				log.warn("FIXME: item not found: {}", name);
			}
		}
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		contentPane = new JPanel();
		valuesPanel = new JPanel();
		CellConstraints cc = new CellConstraints();

		// ======== this ========
		setLayout(new FormLayout("default:grow", "fill:default:grow, $lgap, default"));

		// ======== contentPane ========
		{
			contentPane.setLayout(new BorderLayout());

			// ======== valuesPanel ========
			{
				valuesPanel.setLayout(new BorderLayout());
			}
			contentPane.add(valuesPanel, BorderLayout.SOUTH);
		}
		add(contentPane, cc.xy(1, 1));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JPanel contentPane;
	private JPanel valuesPanel;

	// JFormDesigner - End of variables declaration //GEN-END:variables

	public void autoScale(String loc ) {
		if (charts != null) {
			for (CardioStrip chart : charts) {
				chart.autoScale( loc );
			}
		}
	}

	public void clear() {

		// refresher.stop();

		if (charts != null) {
			for (CardioStrip chart : charts) {
				chart.clear();
			}
		}

		if (valuePanels != null) {
			for (SingleValuePanel value : valuePanels) {
				if (value != null) {
					value.clear();
				}
			}
		}

	}



	public void setStroke(Stroke stroke) {
		if (charts != null) {
			for (CardioStrip chart : charts) {
				chart.setPenStroke(stroke);
			}
		}

	}

	public void resetDisplay() {
		DisplayConfig display = new DisplayConfig();
		
		byte band_num = 0;
		for( RpStream s : (List<? extends RpStream>)conf.getStreams() ) {
			System.out.println("rebuild: " + s.getName() );
			List<RpMetric> metrics = s.getMetric();
			if( metrics != null ) {
				for( RpMetric m : metrics ) {
					if( m.getSampleRate() <= 1 ) {
						FieldData field = new FieldData(m.getLocation(), (byte)0);
						FieldData[] fields = new FieldData[] { field };
						ParameterLayout box = new ParameterLayout( (byte)0, fields );
						display.addParamBox(box);
					} else if( m.getSampleRate() > 1 ) {
						BandLayout band = new BandLayout(band_num++, (byte)0 );
						band.addWaveform( m );
						display.addBand( band );
					}
				}
			}
			// display.addBand(band);
			// display.addParamBox(box);
		}
		setDisplay( display );
	}
	
	public void setDisplay(DisplayConfig display) {

		// save wf bands for later
		List<BandLayout> bands = display.getBands();
		if (bands != null) {
			if (waveformPanel != null) {
				contentPane.remove(waveformPanel);
			}

			waveformPanel = new JScrollPane(buildWaveformPanel(bands));
			
			if (waveformPanel != null) {
				contentPane.add(waveformPanel, BorderLayout.CENTER);
			}

		}

		// metrics
		List<ParameterLayout> boxes = display.getParameterBoxs();
		if (boxes != null) {
			metricsPanel = buildMetricsPanel(boxes);

			if (metricsPanel != null) {
				valuesPanel.add(metricsPanel, BorderLayout.CENTER);

				metricsPanel.doLayout();
			}
		}

		doLayout();
	}

	public DisplayConfig getDisplay() {
		// TODO Auto-generated method stub
		return null;
	}

}
