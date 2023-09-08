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
import lombok.extern.slf4j.Slf4j;
import ni.DAQcommon.AIChannel;
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
import ni.DAQmx.MxAnalogMultiChannelReader;
import ni.DAQmx.MxTask;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpMetric;

/*
 * ALTERNATE METHOD USING JAW
 * 
 * http://www.aplu.ch/home/apluhomex.jsp?site=5
 * 
 */

@Slf4j
public class NIDAQmxDriver extends AbstractStreamProducer implements AdapterInterface, AsyncCallback {
	@SuppressWarnings("unused")
	private static final String driverName="a2d/NIDAQmx A/D";

	Task waveTask;
	Task metricTask;
	RpDevice conf; // when you are running...what
	// waveforms do you sample and at
	// what rate
	DeviceCapabilities cap; // what services can this device provide.
	private AnalogMultiChannelReader waveReader;
	private AnalogMultiChannelReader metricReader;

	List<? extends RpMetric> waves;
	List<? extends RpMetric> metrics;
	double rate;
	double premultiplier;
	private int tick;
	private Class<? extends PersistentItem> metricsClass;
	private Class<? extends PersistentItem> waveClass;

	public static DeviceConfiguration createConfigInstance() {
		return new NIDAQConfiguration(NIDAQmxDriver.class);
	}

	public NIDAQmxDriver(RpDevice conf) {
		this.conf = conf;

		premultiplier = 1000.0;
		if (conf != null) {
			premultiplier = RpUtil.getDoubleParam(conf, "multiplier");
			if (premultiplier <= 0 || premultiplier == Double.NaN) {
				premultiplier = 1000.0;
			}
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

			setStatus(ConnectionStatus.CONNECTED);
		} catch (DaqException e) {
			setStatus(ConnectionStatus.ERROR);
			throw new IOException(e);
		} catch (Throwable e) {
			// such as unsatisfied link error
			setStatus(ConnectionStatus.ERROR);
			throw new IOException(e);
		}
	}

	private void prepareMetricTask() throws DaqException {
		metrics = RpUtil.getMetrics(conf, StreamID.MEASUREMENT);

		if( metrics == null || metrics.size() == 0 ) {
			return;
		}
		metricsClass = AdapterUtil.buildMetricsClass( conf.getName(), metrics );

		
		if (metrics != null) {
			metricTask = new MxTask("");
			createTaskChannels(metricTask, metrics);

			// no need to configure the sample clock
			// Verify the task
			metricTask.control(TaskAction.Verify);

			metricReader = new MxAnalogMultiChannelReader(metricTask.getStream());
		}
	}

	private void prepareWaveTask() throws DaqException {
		waves = RpUtil.getMetrics(conf, StreamID.WAVEFORM);
		if( waves == null || waves.size() == 0 ) {
			return;
		}
		waveClass = AdapterUtil.buildMetricsClass( conf.getName(), waves );

		if (waves == null || waves.size() == 0) {
			return;
		}

		waveTask = new MxTask("");

		createTaskChannels(waveTask, waves);

		rate = RpUtil.getDoubleParam(conf, "rate");

		if ( rate <= 0 || rate == Double.NaN) {
			RpMetric wfd = waves.get(0);
			if (wfd != null) {
				rate = wfd.getSampleRate();
			}

		}

		int samples = (int) (rate / 2);
		// Set up timing
		waveTask.getTiming().configureSampleClock("", rate, SampleClockActiveEdge.Rising,
				SampleQuantityMode.ContinuousSamples, samples);

		// Verify the task
		waveTask.control(TaskAction.Verify);

		waveReader = new MxAnalogMultiChannelReader(waveTask.getStream());

		IAsyncResult ok = waveReader.beginReadWaveform(samples, this, waveTask);
		System.out.println("nidaq waveReader ok=" + ok );
	}

	private void createTaskChannels(Task niTask, List<? extends RpMetric> metriclist) throws DaqException {
		String s_tc = RpUtil.getParam(conf, "terminalConfig" );
		AITerminalConfiguration default_tc = getTerminalConfiguration(s_tc);
		for (RpMetric desc : metriclist) {
			String loc = desc.getLocation().toString();
			AITerminalConfiguration tc = getTerminalConfiguration(loc);
			String sensorlist = loc;
			double mmin = -10.0;
			double mmax = 10.0;
			if (tc == null) {
				tc = default_tc;
			} else {
				int idx = loc.indexOf(":"); // must be >1, since tc is not
											// default
				sensorlist = loc.substring(idx + 1);
				log.debug("using sensorlist: {}", sensorlist);
			}
			int idx = loc.indexOf("[");
			int idx2 = loc.indexOf("]");
			if (idx >= 0 && idx2 > idx) {
				String minmax = loc.substring(idx + 1, idx2);
				String[] ar = minmax.split(",");
				if (ar.length == 2) {
					mmin = Double.parseDouble(ar[0]);
					mmax = Double.parseDouble(ar[1]);
				}
			}

			AIChannel ch = niTask.getAIChannels().createVoltageChannel(sensorlist, "", tc, mmin, mmax, AIVoltageUnits.Volts);
			if( ch == null ) {
				log.error("could not create AI channel");
			}
		}
	}

	private AITerminalConfiguration getTerminalConfiguration(String loc) {

		AITerminalConfiguration tc = null;
		if (loc != null) {

			loc = loc.toLowerCase(); // create a temporary lower case copy for
										// comparisons

			if (loc.startsWith("diff")) {
				tc = AITerminalConfiguration.Differential;
			} else if (loc.startsWith("nrse")) {
				tc = AITerminalConfiguration.Nrse;
			} else if (loc.startsWith("rse")) {
				tc = AITerminalConfiguration.Rse;
			} else if (loc.startsWith("pseudo")) {
				tc = AITerminalConfiguration.Pseudodifferential;
			} else if (loc.startsWith("default")) {
				tc = AITerminalConfiguration.DEFAULT;
			}
		}

		return tc;
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

		setStatus(ConnectionStatus.NOT_CONNECTED);

	}

	@Override
	public DeviceCapabilities getStaticCapabilities() {

		cap = new DeviceCapabilities(NIDAQmxDriver.class);
		cap.setName("NIDAQmxBase");
		String[] ports = DaqSystem.getMxLocal().getPhysicalChannels();
		
		AdapterUtil.getStaticCapabilities( cap, ports, "AI" );
		cap.addConnection(new DAQmxConnection());

		return cap;
	}

	@Override
	public void asyncCallback(IAsyncResult result) {
		try {

			// wlb if (runningTask == result.AsyncState) {
			// Read the available data from the channels

			if (waveReader != null) {
				readWaveforms(result);
			}

			if (metricReader != null) {
				readMetrics(result);
			}

		} catch (DaqException exception) {
			// Display Errors
			log.error("asyncCallback error", exception );
			// wlb runningTask = null;
			waveTask.dispose();
			metricTask.dispose();

			setStatus(ConnectionStatus.DATA_NOT_AVAIL);
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

		SwingUtilities.invokeLater(new Runnable() {

			@Override
			public void run() {
				fireStreamEvent(0, NIDAQmxDriver.this, StreamID.WAVEFORM, wfb);
				tick = 0;
			}
		});

	}

	@Override
	public RpDevice getConfiguration() {
		return conf;
	}

	@Override
	public int tick() {
		tick++;

		ConnectionStatus deviceState = getStatus();
		if (tick > 4) {
			if (deviceState != NOT_CONNECTED) {
				deviceState = NOT_CONNECTED;
				setStatus(ConnectionStatus.NOT_CONNECTED);
			}
		} else {
			if (deviceState == NOT_CONNECTED) {
				deviceState = CONNECTED;
				setStatus(ConnectionStatus.CONNECTED);
			}
		}
		return 0;
	}

}
