package idea.driver;

import static icuInterface.ConnectionStatus.CONNECTED;
import static icuInterface.ConnectionStatus.NOT_CONNECTED;

import java.io.IOException;
import java.util.List;

import javax.swing.SwingUtilities;

import icuInterface.ConnectionStatus;
import icuInterface.PlatformUtil;
import icuInterface.RpUtil;
import icuInterface.conf.dev.NIDAQConfiguration;
import idea.conf.DeviceCapabilities;
import idea.conf.DeviceConfiguration;
import idea.connections.DAQmxConnection;
import idea.intf.AbstractStreamProducer;
import idea.intf.AdapterInterface;
import idea.intf.AdapterUtil;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.ModelUtil;
import idea.model.PersistentItem;
import ni.DAQcommon.AITerminalConfiguration;
import ni.DAQcommon.AIVoltageUnits;
import ni.DAQcommon.AnalogMultiChannelReader;
import ni.DAQcommon.AnalogWaveform;
import ni.DAQcommon.AsyncCallback;
import ni.DAQcommon.DaqException;
import ni.DAQcommon.DaqSystem;
import ni.DAQcommon.IAsyncResult;
import ni.DAQcommon.SampleClockActiveEdge;
import ni.DAQcommon.SampleQuantityMode;
import ni.DAQcommon.Task;
import ni.DAQcommon.TaskAction;
import ni.DAQmxBase.BaseTask;
import idea.schema.rp.RpMetric;

public class NIDAQmxBaseDriver extends AbstractStreamProducer implements AdapterInterface, AsyncCallback {
	@SuppressWarnings("unused")
private static final String driverName="a2d/NIDAQmxBase A/D";

	Task waveTask;
	Task metricTask;
	NIDAQConfiguration conf; // when you are running...what
	// waveforms do you sample and at
	// what rate
	DeviceCapabilities cap; // what services can this device provide.
	private AnalogMultiChannelReader waveReader;
	private AnalogMultiChannelReader metricReader;

	List<? extends RpMetric> waves;
	List<? extends RpMetric> metrics;
	double rate;
	private int tick;
	private double premultiplier;
	private Class<? extends PersistentItem> metricsClass;
	private Class<? extends PersistentItem> waveClass;

	public static DeviceConfiguration createConfigInstance() {
		return new NIDAQConfiguration(NIDAQmxBaseDriver.class);
	}

	public NIDAQmxBaseDriver(DeviceConfiguration conf) {
		this.conf = (NIDAQConfiguration) conf;

		String s_premult = null;
		if (conf != null) {
			s_premult = conf.getParam("premultiplier");
		}
		if (s_premult != null) {
			s_premult = s_premult.trim();
		}
		if (s_premult == null || s_premult.length() == 0) {
			premultiplier = 1000.0;
		} else {
			premultiplier = Double.parseDouble(s_premult);
		}

	}

	@Override
	public void connect() throws IOException {

		if (waveTask != null) {

			waveTask.stop();
			waveTask.dispose();
		}

		if (metricTask != null) {

			metricTask.stop();
			metricTask.dispose();
		}

		try {

			prepareWaveTask();
			prepareMetricTask();

			setStatus( ConnectionStatus.CONNECTED);
		} catch (DaqException e) {

			throw new IOException(e);
		}
	}

	private void prepareMetricTask() throws DaqException {
		metrics = RpUtil.getMetrics(conf, StreamID.MEASUREMENT);

		metricsClass = AdapterUtil.buildMetricsClass( conf.getName(), metrics );

		if (metricsClass != null) {
			metricTask = new BaseTask("");
			for (RpMetric desc : metrics) {
				metricTask.getAIChannels().createVoltageChannel(desc.getLocation().toString(), "",
						AITerminalConfiguration.DEFAULT, -10.0, 10.0, AIVoltageUnits.Volts);
			}

			// no need to configure the sample clock
			// Verify the task
			metricTask.control(TaskAction.Verify);

			metricReader = metricTask.createAnalogMultiChannelReader();
		}
	}

	private void prepareWaveTask() throws DaqException {
		waves = RpUtil.getMetrics(conf, StreamID.WAVEFORM);
		waveClass = AdapterUtil.buildMetricsClass( conf.getName(), waves );

		if (waves == null || waves.size() == 0) {
			return;
		}

		waveTask = new BaseTask("");
		for (RpMetric desc : waves) {
			waveTask.getAIChannels().createVoltageChannel(desc.getLocation().toString(), "",
					AITerminalConfiguration.DEFAULT, -10.0, 10.0, AIVoltageUnits.Volts);
		}

		rate = conf.getRate();

		String s_rate = conf.getParam("RATE");

		if (s_rate != null) {
			rate = Double.parseDouble(s_rate);
		}

		int samples = (int) (rate / 2);
		// Set up timing
		waveTask.getTiming().configureSampleClock("", rate, SampleClockActiveEdge.Rising,
				SampleQuantityMode.ContinuousSamples, samples);

		// Verify the task
		waveTask.control(TaskAction.Verify);

		waveReader = waveTask.createAnalogMultiChannelReader();

		waveReader.beginReadWaveform(samples, this, waveTask);

	}

	@Override
	public void disconnect() throws IOException {
		if (waveTask != null) {
			waveTask.stop();
			waveTask.dispose();
		}

		if (metricTask != null) {
			metricTask.stop();
			metricTask.dispose();
		}

		setStatus( ConnectionStatus.NOT_CONNECTED);

	}

	@Override
	public void requestCapabilities() throws IOException {

		DeviceCapabilities caps = getStaticCapabilities();
		fireCapabilitiesEvent(this, caps);
	}

	@Override
	public DeviceCapabilities getStaticCapabilities() {

		cap = new DeviceCapabilities( NIDAQmxBaseDriver.class);
		cap.setName("NIDAQmx");
		String[] ports = DaqSystem.getBaseLocal().getPhysicalChannels();
		
		AdapterUtil.getStaticCapabilities( cap, ports, "AI" );
		cap.addConnection(new DAQmxConnection());

		return cap;
	}

	@Override
	public void asyncCallback(IAsyncResult result) {
		try {

			if (waveReader != null) {
				readWaveforms(result);
			}

			if (metricReader != null) {
				readMetrics(result);
			}

		} catch (DaqException exception) {
			// Display Errors
			System.err.println(exception.getMessage());
			// wlb runningTask = null;
			waveTask.dispose();
			metricTask.dispose();

			setStatus( ConnectionStatus.DATA_NOT_AVAIL);
		}
	}

	private void readMetrics(IAsyncResult result) throws DaqException {
		PersistentItem block = ModelUtil.getModelFromDataClass( metricsClass );
		double[] data = metricReader.readSingleSample();

		int idx = 0;
		long time = PlatformUtil.currentTimeMillis();
		block.setTime(time);
		for (RpMetric metric : metrics) {
			IntfUtil.setScaledValue(block, metric.getLocation(), 1000.0 * data[idx]);
			idx++;
		}
		fireStreamEvent(0,this,StreamID.MEASUREMENT, block);
		tick = 0;

	}


	private void readWaveforms(IAsyncResult result) throws DaqException {
		final PersistentItem wfb = ModelUtil.getModelFromDataClass( waveClass );

		AnalogWaveform[] waveforms = waveReader.endReadWaveform(result);

		for (int idx = 0; idx < waves.size(); idx++) {
			RpMetric desc = waves.get(idx);
			AnalogWaveform ni_wf = waveforms[idx];

			IntfUtil.setValue(wfb, desc.getLocation(), ni_wf.getRawData() );

		}
		System.out.println();


		SwingUtilities.invokeLater(new Runnable() {

			@Override
			public void run() {
				fireStreamEvent(0, NIDAQmxBaseDriver.this, StreamID.WAVEFORM, wfb);
				tick = 0;
			}
		});
	}

	@Override
	public DeviceConfiguration getConfiguration() {
		return conf;
	}

	@Override
	public int tick() {
		tick++;
		
		ConnectionStatus deviceState = getStatus();
		if (tick > 4) {
			if (deviceState != NOT_CONNECTED) {
				setStatus( ConnectionStatus.NOT_CONNECTED);
			}
		} else {
			if (deviceState != CONNECTED) {
				setStatus( ConnectionStatus.CONNECTED);
			}
		}
		return 0;
	}

}
