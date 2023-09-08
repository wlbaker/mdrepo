package idea.driver;

import static icuInterface.ConnectionStatus.CONNECTED;
import static icuInterface.ConnectionStatus.NOT_CONNECTED;

import java.io.IOException;
import java.util.List;

import icuInterface.ConnectionStatus;
import icuInterface.RpUtil;
import icuInterface.conf.dev.NIDAQConfiguration;
import idea.conf.DeviceCapabilities;
import idea.conf.DeviceConfiguration;
import idea.connections.DAQmxConnection;
import idea.intf.AbstractStreamProducer;
import idea.intf.AdapterInterface;
import idea.intf.AdapterUtil;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import ni.DAQcommon.AOTerminalConfiguration;
import ni.DAQcommon.AOVoltageUnits;
import ni.DAQcommon.AnalogMultiChannelReader;
import ni.DAQcommon.AnalogMultiChannelWriter;
import ni.DAQcommon.AsyncCallback;
import ni.DAQcommon.DaqException;
import ni.DAQcommon.DaqSystem;
import ni.DAQcommon.IAsyncResult;
import ni.DAQcommon.SampleClockActiveEdge;
import ni.DAQcommon.SampleQuantityMode;
import ni.DAQcommon.Task;
import ni.DAQcommon.TaskAction;
import ni.DAQmx.MxAnalogMultiChannelWriter;
import ni.DAQmx.MxTask;
import ni.DAQmx.NI;
import idea.schema.rp.RpMetric;

public class NIDAQmxOutputDriver extends AbstractStreamProducer implements AdapterInterface, AsyncCallback,
		StreamConsumer {
	@SuppressWarnings("unused")
	private static final String driverName="a2d/NIDAQmx Output Driver";

	Task waveTask;
	Task metricTask;
	NIDAQConfiguration conf; // when you are running...what
	// waveforms do you sample and at
	// what rate
	DeviceCapabilities cap; // what services can this device provide.
	private AnalogMultiChannelWriter waveWriter;
	private AnalogMultiChannelReader metricReader;

	List<? extends RpMetric> waves;
	RpMetric[] metrics;
	double rate;
	double premultiplier;
	private int tick;
	private int n_blocks;

	public static DeviceConfiguration createConfigInstance() {
		return new NIDAQConfiguration(NIDAQmxOutputDriver.class);
	}

	public NIDAQmxOutputDriver(DeviceConfiguration conf) {
		this.conf = (NIDAQConfiguration) conf;

		premultiplier = 1000.0;
		if (conf != null) {
			premultiplier = this.conf.getPremultiplier();
			if (premultiplier <= 0) {
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

			n_blocks = 0;  // used for determining when the buffer is full enough to call task.start()
			prepareWaveTask();
			// prepareMetricTask();

			setStatus( ConnectionStatus.CONNECTED);
		} catch (DaqException e) {

			throw new IOException(e);
		}
	}

	private void prepareWaveTask() throws DaqException {
		if( conf == null ) {
			return;
		}
		waves = RpUtil.getMetrics(conf, StreamID.WAVEFORM);

		if (waves == null || waves.size() == 0) {
			return;
		}

		waveTask = new MxTask("");

		createTaskChannels(waveTask, waves);

		rate = conf.getRate();

		String s_rate = conf.getParam("RATE");

		if (s_rate != null) {
			rate = Double.parseDouble(s_rate);
		} else if (waves != null && waves.size() > 0) {
			RpMetric wfd = waves.get(0);
			if (wfd != null) {
				rate = wfd.getSampleRate();
			}

		}

		int samples = (int) (rate / 2);
		// Set up timing
		waveTask.getTiming().configureSampleClock("", rate, SampleClockActiveEdge.Rising,
				SampleQuantityMode.ContinuousSamples, samples);

		waveTask.getStream().setWriteAttribute( NI.Write_RegenMode, NI.Val_DoNotAllowRegen);
		waveTask.getStream().configureOutputBuffer( samples * 2);
		
		// Verify the task
		waveTask.control(TaskAction.Verify);

		waveWriter = new MxAnalogMultiChannelWriter(waveTask.getStream());

	}

	private void createTaskChannels(Task niTask, List<? extends RpMetric> descs) throws DaqException {
		for (RpMetric desc : descs) {
			String loc = desc.getLocation().toString();
			AOTerminalConfiguration tc = getTerminalConfiguration(loc);
			String sensorlist = loc;
			double mmin = -10.0;
			double mmax = 10.0;
			if (tc == null) {
				tc = AOTerminalConfiguration.DEFAULT;
			} else {
				int idx = loc.indexOf(":"); // must be >1, since tc is not
											// default
				sensorlist = loc.substring(idx + 1);
				System.out.println("using sensorlist: " + sensorlist);
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

			// niTask.getAOChannels().createVoltageChannel(sensorlist, "", tc,
			// mmin, mmax, AOVoltageUnits.Volts);
			niTask.getAOChannels().createVoltageChannel(sensorlist, "", mmin, mmax, AOVoltageUnits.Volts);
		}
	}

	private AOTerminalConfiguration getTerminalConfiguration(String loc) {

		AOTerminalConfiguration tc = null;

		loc = loc.toLowerCase(); // create a temporary lower case copy for
									// comparisons

		if (loc.startsWith("diff")) {
			tc = AOTerminalConfiguration.Differential;
		} else if (loc.startsWith("nrse")) {
			tc = AOTerminalConfiguration.Nrse;
		} else if (loc.startsWith("rse")) {
			tc = AOTerminalConfiguration.Rse;
		} else if (loc.startsWith("pseudo")) {
			tc = AOTerminalConfiguration.Pseudodifferential;
		} else if (loc.startsWith("default")) {
			tc = AOTerminalConfiguration.DEFAULT;
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

		cap = new DeviceCapabilities( NIDAQmxOutputDriver.class);
		cap.setName("NIDAQmxOut");
		String[] ports = DaqSystem.getMxLocal().getPhysicalAOChannels();

		AdapterUtil.getStaticCapabilities( cap, ports, "AO" );
		cap.addConnection(new DAQmxConnection());
		
		return cap;
	}

	@Override
	public void asyncCallback(IAsyncResult result) {
		System.out.println("NIDAQmxOutputDriver: unexpected async callback");
		// try {
		//
		// // wlb if (runningTask == result.AsyncState) {
		// // Read the available data from the channels
		//
		// if (waveWriter != null) {
		// writeWaveforms(result);
		// }
		//
		//
		// } catch (DaqException exception) {
		// // Display Errors
		// System.err.println(exception.getMessage());
		// // wlb runningTask = null;
		// waveTask.dispose();
		// metricTask.dispose();
		//
		// deviceState = DeviceState.OFFLINE;
		// ConnectionEvent event = new ConnectionEvent(this,
		// ConnectionStatus.DATA_NO_LONGER_AVAIL);
		// fireEvent(StreamID.CONNECTION, event);
		// }
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
				setStatus( NOT_CONNECTED );
			}
		} else {
			if (deviceState != CONNECTED) {
				setStatus( CONNECTED );
			}
		}
		return 0;
	}

	// This device has analog out capabilities

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {
		try {
			_signalEvent(jobID,  source,  sid,  item);
		} catch (DaqException e) {
			// dont know what to do here....just spit out the exception info
			e.printStackTrace();
		}
	}

	private void _signalEvent(Object event, StreamProducer source, StreamID sid, PersistentItem item) throws DaqException {
		if (sid == StreamID.WAVEFORM) {

			RpMetric[] waves = item.getMetrics();
			if (waves.length > 0) {
				RpMetric wave = waves[0];  // ERROR: assuming wf[0]
				int[] ivals = (int[]) IntfUtil.getRawValue(item, wave);
				double[] dvals = new double[(ivals.length > 250) ? ivals.length : 250];  // ERROR: assuming data block to transmit is 250 samples (min)
				for (int i = 0; i < ivals.length; i++) {
					dvals[i] = ivals[i] / 4000.0f;

				}
				waveWriter.writeSingleSample(true, dvals);
				
				n_blocks++;
				if( n_blocks == 2 ) {
					waveTask.start();
				}
			}

		} else if (sid == StreamID.MEASUREMENT) {
		} else if (sid == StreamID.CONNECTION) {
		}
	}

}
