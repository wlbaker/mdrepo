package idea.analysis;

import idea.conf.DeviceCapabilities;
import idea.conf.DeviceConfiguration;
import idea.display.BandLayout;
import idea.display.CardioStrip;
import idea.display.FieldData;
import idea.display.ParameterLayout;
import idea.display.StripSetup;
import idea.display.WaveformData;
import idea.display.elegant.ElegantDisplayForm;
import idea.display.elegant.ValuePanel;
import idea.intf.AbstractStreamProducer;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.DisplayConfig;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.model.dev.VITMeasurement;
import idea.schema.rp.RpAnalysis;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpMetric;

import java.io.IOException;
import java.util.List;

import javax.swing.JPanel;

import icuInterface.ConnectionStatus;
import lombok.extern.slf4j.Slf4j;

@Slf4j
@SuppressWarnings("serial")
public class VITPressureSummaryPanel extends ElegantDisplayForm implements
		StreamProducer, AnalysisPanelInterface {
	private static final long MIN_DATA_REFRESH_MS = 2000;
	private long last_tm;
	private List<BandLayout> bands;
	private static RpMetric[] metricss;

	private RpMetric[] items;

	private static DeviceCapabilities caps;
	private AbstractStreamProducer sig_pro;

	static {
		caps = new DeviceCapabilities(VITPressureSummaryPanel.class);

				
		caps.addStream( StreamID.MEASUREMENT, VITMeasurement.class );
		caps.setName("VITPressureSummaryPanel");

	}

	public VITPressureSummaryPanel(StreamProducer[] producers,
			RpAnalysis analConfs) {
		super(null, null);

		sig_pro = new AbstractStreamProducer() {

			@Override
			public DeviceCapabilities getStaticCapabilities() {

				return caps;
			}
		};

		// don't add listeners until after we have our producer ready
		for (StreamProducer producer : producers) {
			if (producer.getConfiguration().getName().startsWith("Drager")) {
				reset(producer);
				break;
			}
		}
	}

	@Override
	public void setDisplay(DisplayConfig ddisplay) {
		bands = ddisplay.getBands();
		// metrics = new MetricDescription[bands.length];
		items = new RpMetric[bands.size()];

		super.setDisplay(ddisplay);
	}

	@Override
	protected ValuePanel[] buildDisplayPBoxes(RpDevice conf,
			DisplayConfig disp ) {

		int band_count = disp.getNumBands();
		
		ValuePanel[] valuePanels = (band_count == 0) ? null
				: new ValuePanel[bands.size()];

		int tot = Math.min(bands.size(), metricss.length);

		for (int idx = 0; idx < tot; idx++) {
			BandLayout band = bands.get(idx);
			ParameterLayout box = disp.getPBox(idx); // i get some info the pbox...like
												// color
			// but it should come from the band

			if (box == null || box.fields == null
					|| box.fields.length == 0) {
				log.warn("Param box is empty?  param=" + idx);
				continue;
			}
			FieldData[] params = box.fields;

			ValuePanel vp = new ValuePanel(ValuePanel.CUSTOM_BOX_111,
					box.getForeground());
			WaveformData wave = band.getWave(0);

			// String loc = wave.getLoc() + "val";

			RpMetric md = metricss[idx]; // new MetricDescription(loc,
													// loc, unit="mmHg");
			vp.addParameter(md);
			items[idx] = md;

			// System.out.println(idx + " creating panel: " + vp );
			valuePanels[idx] = vp;
			vp.clear();
		}

		return valuePanels;
	}

	@Override
	synchronized protected void waveformEvent(Object source, PersistentItem item) {
		RpMetric[] waveforms = IntfUtil.getMetrics(item);
		if (waveforms == null) {
			return;
		}

		long tm = item.getTime();

		boolean send_data = (tm - last_tm > MIN_DATA_REFRESH_MS);
		VITMeasurement block = null;
		if (send_data) {
			block = new VITMeasurement();
		}

		JPanel[] vps = getValuePanels();

		for (int idx = 0; idx < waveforms.length; idx++) {

			RpMetric wf = waveforms[idx];

			CardioStrip chart = findChart(wf);
			if (chart != null) {
				int [] vals = (int[])IntfUtil.getRawValue(item, wf);
				chart.addWaveformItem(tm, wf, vals);
				if (send_data) {
					StripSetup[] setups = chart.getSetups();
					StripSetup setup = setups[0];
					int idx_of = idxOf(wf);
					if (idx_of >= 0) {
						ValuePanel vp = (ValuePanel)vps[idx_of];
						RpMetric metric = items[idx_of];

						double val = setup.getCurrentValue();
						IntfUtil.setValue(item, metric, val);
						
						vp.setValue(metric, item);
					}
				}
			}
		}

		if (send_data) {
			last_tm = tm;
			sig_pro.fireStreamEvent(0,this,StreamID.MEASUREMENT, block);
		}
	}

	private int idxOf(RpMetric wf) {
		String loc = (String) wf.getLocation();
		if( items == null ) {
			return -1;
		}
		for( int i = 0; i < items.length; i++ ) {
			RpMetric item = items[i];
			if( item == null ) {
				continue;
			}
			String loc2 = item.getLocation();
			if( loc2.startsWith(loc) ) {
				return i;
			}
		}
		return -1;
	}


	@Override
	public void requestCapabilities() throws IOException {
		sig_pro.fireCapabilitiesEvent(this, caps);
	}

	@Override
	public DeviceCapabilities getStaticCapabilities() {
		return caps;
	}

	@Override
	public DeviceConfiguration getConfiguration() {
		return caps;
	}

	@Override
	public void autoscale() {
		// ignore

	}

	@Override
	public void tick() {
		// ignore

	}

	@Override
	public StreamProducer[] getSignalProducers() {
		return new StreamProducer[] { this };
	}

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {
		// TODO Auto-generated method stub
		
	}



	@Override
	public void addStreamListener(StreamID sid, StreamConsumer l) {
		sig_pro.addStreamListener(sid, l);
	}

	@Override
	public void removeStreamListener(StreamConsumer l) {
		sig_pro.removeStreamListener(l);
	}

	@Override
	public PersistentItem getEvent(StreamID sid) {
		return sig_pro.getEvent(sid);
	}

	@Override
	public void removeAllStreamListeners() {
		sig_pro.removeAllStreamListeners();
	}

	@Override
	public ConnectionStatus getStatus() {
		// TODO Auto-generated method stub
		return null;
	}
}
