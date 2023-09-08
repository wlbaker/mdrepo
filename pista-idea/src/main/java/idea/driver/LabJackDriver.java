package idea.driver;

import static icuInterface.ConnectionStatus.CONNECTED;
import static icuInterface.ConnectionStatus.NOT_CONNECTED;

import java.io.IOException;
import java.text.DecimalFormat;
import java.text.NumberFormat;
import java.util.Collection;

import com.labjack.LJUD;
import com.labjack.LJUDException;
import com.sun.jna.Memory;
import com.sun.jna.Pointer;
import com.sun.jna.ptr.DoubleByReference;
import com.sun.jna.ptr.IntByReference;

import icuInterface.ConnectionStatus;
import icuInterface.PlatformUtil;
import icuInterface.RpUtil;
import icuInterface.conf.dev.LabJackConfiguration;
import icuInterface.discovery.DeviceRecord;
import idea.conf.DeviceCapabilities;
import idea.conf.DeviceConfiguration;
import idea.connections.LabJackConnection;
import idea.intf.AbstractStreamProducer;
import idea.intf.AdapterInterface;
import idea.intf.AdapterUtil;
import idea.message.StreamID;
import idea.model.Alarm;
import idea.model.IntfUtil;
import idea.model.ModelUtil;
import idea.model.PersistentItem;
import lombok.extern.slf4j.Slf4j;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpStream;
import idea.schema.rp.StringStringMap;

// TODO: We have no "discovery" features in the drivers
//
// LJUD.ListAll(DeviceType, ConnectionType, pNumFound, pSerialNumbers, pIDs, pAddresses);
//

@Slf4j
public class LabJackDriver extends AbstractStreamProducer implements AdapterInterface {

	@SuppressWarnings("unused")
	private static final String driverName = "a2d/LabJack USB A/D";

	int errCode;
	DoubleByReference refZero = new DoubleByReference(0);

	int intHandle = 0;
	private boolean running = false;
	NumberFormat formatter = new DecimalFormat("0.000"); // used for debug
	// output

	RpDevice conf; // when you are running...what waveforms do you sample and
					// at...what rate
	static DeviceCapabilities cap; // what services can this device provide.

	private static Class<? extends PersistentItem> waveModel;

	private static Class<? extends PersistentItem> metricModel;

	/*
	 * state passed into background thread
	 */
	private static final int SAMPLES_PER_PACKET = 64;
	private int n_channels;
	Collection<? extends RpMetric> waves;
	private int scanRate;

	/*
	 * Initialization
	 */

	static {
		cap = new DeviceCapabilities(LabJackDriver.class);
		cap.setName("LabJack");

		String[] ports = { "AIN-0", "AIN-1", "AIN-2", "AIN-3", "FIO-4", "FIO-5", "FIO-6", "FIO-7", // AIO
				"EIO-0", "EIO-1", "EIO-2", "EIO-3", "EIO-4", "EIO-5", "EIO-6", "EIO-7" // EIO
		};
		AdapterUtil.getStaticCapabilities(cap, ports, "LJ");
		// cap.addConnection(new Lab());

		RpStream s = cap.getStream(StreamID.WAVEFORM);
		waveModel = (Class<? extends PersistentItem>) s.getPIClass();
		s = cap.getStream(StreamID.MEASUREMENT);
		if (s != null) {
			metricModel = (Class<? extends PersistentItem>) s.getPIClass();
		}
		cap.setModels(new String[] { "U3-LV", "U3-HV" });
		cap.addConnection(new LabJackConnection());
	}

	private int tick;

	public static DeviceConfiguration createConfigInstance() {
		LabJackConfiguration local_conf = new LabJackConfiguration(LabJackDriver.class);

		// local_conf.addStream( cap.getStream(StreamID.WAVEFORM) );
		return local_conf;
	}

	public LabJackDriver(RpDevice conf) {
		this.conf = conf;
	}

	public static double version() {
		double version = LJUD.getDriverVersion();
		return version;
	}

	// Java uses signed bytes but the UD driver requires unsigned bytes
	// therefore these two methods
	// are needed to convert back and forth. For more info see
	// http://www.lykkenborg.no/java/2005/03/how-do-i-read-unsigned-byte-in-java.html
	public static byte signed(int i) {
		return (byte) i;
	}

	public static int unsigned(byte b) {
		return b & 0xFF;
	}

	// displayed so that you can find the line of code where the error occurred.
	public static void ErrorHandler(int Errorcode) throws Exception {

		Pointer err = new Memory(256);

		if (Errorcode < 0) {
			LJUD.errorToString(Errorcode, err);
			String message = err.getString(0);
			int pos = message.indexOf(0);
			if (pos > 0) {
				message = message.substring(0, pos);
			}
			log.warn("Error number = {}", Errorcode);
			log.warn("Error string = {}", message);

			Exception excep = new Exception(message);

			throw (excep);
		}
	}

	@Override
	public void connect() throws IOException {

		waves = RpUtil.getMetrics(conf, StreamID.WAVEFORM);
		n_channels = waves.size();

		scanRate = 100;
		if (conf != null && conf.getParam() != null) {
			StringStringMap params = conf.getParam();
			String s_rate = params.get("rate");
			if (s_rate != null) {
				// divide by two to get device clock scan rate
				scanRate = Integer.parseInt(s_rate) / 2;
			}
		}

		try {
			initScanner(waves, scanRate);
		} catch (Exception e) {
			throw new IOException(e);
		}

		Runnable r = new Runnable() {

			@Override
			public void run() {
				try {
					_run();
				} catch (Exception ex) {
					log.error("RUN ERR", ex);
					Alarm item = new Alarm("labj", Alarm.FATAL, 0, "LabJack Error: " + ex.getMessage(), true);
					fireAlarmEvent(LabJackDriver.this, item);
				}

				running = false;
			}

			public void _run() throws Exception {

				running = true;

				PersistentItem block = ModelUtil.getModelFromDataClass(waveModel);
				String s_spp = RpUtil.getParam(conf, "spp");
				int numScans = 0;
				if (s_spp != null) {
					numScans = Integer.parseInt(s_spp);
				}
				if (numScans == 0) {
					for (RpMetric desc : waves) {
						Integer spp = desc.getSamplesPerPacket();
						if (spp != null && spp > numScans) {
							numScans = spp;
						}
					}
				}
				if (numScans == 0) {
					numScans = SAMPLES_PER_PACKET;
				}
				double[] adblData = new double[n_channels * numScans]; // Max
																		// buffer
																		// size

				int z = 0;
				float[][] values = new float[n_channels][];
				for (RpMetric desc : waves) {
					values[z] = new float[numScans];
					RpMetric desc0 = desc;
					desc0.setSampleRate(scanRate);
					desc0.setSamplesPerPacket(numScans);
					IntfUtil.setValue(block, desc.getLocation(), values[z]);
					z++;
				}

				setStatus(CONNECTED);

				DoubleByReference numScansRequested = new DoubleByReference(0);
				numScansRequested.setValue(0);

				while (running && errCode == 0) {

					// Note that the array we pass must be sized to hold enough
					// SAMPLES,
					// and the Value we pass specifies the number of SCANS to
					// read.
					numScansRequested.setValue(numScans);
					try {
						errCode = LJUD.eGet(intHandle, LJUD.Constants.ioGET_STREAM_DATA, LJUD.Constants.chALL_CHANNELS,
								numScansRequested, adblData);
					} catch (LJUDException le) {
						System.err.println(le);
						if (le.getError() == LJUD.Errors.NO_DATA_AVAILABLE.getValue()) {
							Thread.sleep(100);
						} else if (le.getError() == LJUD.Errors.NO_MORE_DATA_AVAILABLE.getValue()) {
							Thread.sleep(100);
						} else if (le.getError() == LJUD.Errors.BUFFER_OVERRUN.getValue()) {
							throw new IOException("buffer overrun", le);
						} else {
							throw new IOException("misc error", le);

						}
					}
					if (errCode != 0) {
						break;
					}

					int idx = 0;
					for (int i = 0; i < numScans; i++) {
						for (int j = 0; j < n_channels; j++) {
							values[j][i] = (float) (1000 * adblData[idx++]);
						}
					}

					// we kinda don't care about the backlog

					long time = PlatformUtil.currentTimeMillis();
					block.setTime(time);

					fireStreamEvent(0, LabJackDriver.this, StreamID.WAVEFORM, block);

					tick = 0;
				}

				ErrorHandler(errCode);

				// Stop the stream
				errCode = LJUD.eGet(intHandle, LJUD.Constants.ioSTOP_STREAM, 0, refZero, 0);
				ErrorHandler(errCode);

				setStatus(ConnectionStatus.NOT_CONNECTED);

			}

		};

		Thread th = new Thread(r);
		th.start();

	}

	protected void initScanner(Collection<? extends RpMetric> waves, double scanRate) throws Exception {

		int n_channels = waves.size();

		IntByReference IOType = new IntByReference(0);
		IntByReference Channel = new IntByReference(0);
		DoubleByReference refValue = new DoubleByReference(0);
		// (#channels*numScansRequested)
		IntByReference iZero = new IntByReference(0);

		// Read and display the UD and LJUDJava versions.
		log.info("UD Driver Version = {}", formatter.format(LJUD.getDriverVersion()));

		IntByReference refHandle = new IntByReference(0);
		// Open the first found LabJack U3.
		errCode = LJUD.openLabJack(LJUD.Constants.dtU3, LJUD.Constants.ctUSB, "1", 1, refHandle);
		ErrorHandler(errCode);
		intHandle = refHandle.getValue();

		// Read and display the hardware version of this U3.
		errCode = LJUD.eGet(intHandle, LJUD.Constants.ioGET_CONFIG, LJUD.Constants.chHARDWARE_VERSION, refValue, 0);
		log.info("U3 Hardware Version = {}", refValue.getValue());
		ErrorHandler(errCode);

		// Read and display the firmware version of this U3.
		errCode = LJUD.eGet(intHandle, LJUD.Constants.ioGET_CONFIG, LJUD.Constants.chFIRMWARE_VERSION, refValue, 0);
		log.info("U3 Firmware Version = {}", refValue.getValue());
		ErrorHandler(errCode);

		// Start by using the pin_configuration_reset IOType so that all
		// pin assignments are in the factory default condition.
		errCode = LJUD.ePut(intHandle, LJUD.Constants.ioPIN_CONFIGURATION_RESET, 0, 0, 0);
		ErrorHandler(errCode);

		int ai_mask = getAIMask(waves);
		// Configure FIO0 and FIO1 as analog, all else as digital. That means we
		// will start from channel 0 and update all 16 flexible bits. We will
		// pass a value of b0000000000000011 or d3.
		errCode = LJUD.ePut(intHandle, LJUD.Constants.ioPUT_ANALOG_ENABLE_PORT, 0, ai_mask, 16);
		ErrorHandler(errCode);

		// Configure the stream:
		// Set the scan rate.
		errCode = LJUD.addRequest(intHandle, LJUD.Constants.ioPUT_CONFIG, LJUD.Constants.chSTREAM_SCAN_FREQUENCY,
				scanRate, 0, 0);
		ErrorHandler(errCode);
		// Give the driver a 5 second buffer (scanRate * 2 channels * 5
		// seconds).
		errCode = LJUD.addRequest(intHandle, LJUD.Constants.ioPUT_CONFIG, LJUD.Constants.chSTREAM_BUFFER_SIZE, scanRate
				* n_channels * 5, 0, 0);
		ErrorHandler(errCode);
		// Configure reads to retrieve whatever data is available without
		// waiting (wait mode swNONE). See comments below to change this
		// program to use swSLEEP mode.
		errCode = LJUD.addRequest(intHandle, LJUD.Constants.ioPUT_CONFIG, LJUD.Constants.chSTREAM_WAIT_MODE,
				LJUD.Constants.swSLEEP, 0, 0);
		ErrorHandler(errCode);
		// Define the scan list as AIN0 then FIOEIO.
		errCode = LJUD.addRequest(intHandle, LJUD.Constants.ioCLEAR_STREAM_CHANNELS, 0, 0, 0, 0);
		ErrorHandler(errCode);

		// **********************************
		// request SE streaming on AIN0 and AIN1
		// **********************************
		for (RpMetric desc : waves) {
			String loc = desc.getLocation();

			String s = loc.substring(4);
			int iloc = Integer.parseInt(s);
			if (loc.startsWith("E")) {
				iloc += 8;
			}

			log.info("ADDING LOC: {}", iloc);
			errCode = LJUD.addRequest(intHandle, LJUD.Constants.ioADD_STREAM_CHANNEL, iloc, 0, 0, 0);
			ErrorHandler(errCode);
		}

		// **** THIS IS THE SPECIAL 0-3.2v mode...probably has no effect on HV
		// hardware??
		// Errorcode = LJUD.AddRequest(intHandle,
		// LJUD.ioADD_STREAM_CHANNEL_DIFF, 1, 0, 32, 0);

		// Execute the list of requests.
		errCode = LJUD.goOne(intHandle);
		ErrorHandler(errCode);

		// Get all the results just to check for errors.
		errCode = LJUD.getFirstResult(intHandle, IOType, Channel, refValue, iZero, refZero);
		ErrorHandler(errCode);
		while (true) {
			try {
				errCode = LJUD.getNextResult(intHandle, IOType, Channel, refValue, iZero, refZero);
			} catch (LJUDException le) {
				if (le.getError() == LJUD.Errors.NO_MORE_DATA_AVAILABLE.getValue()) {
					break;
				} else {
					ErrorHandler(errCode);
					throw le;
				}
			}
		}

		// Start the stream.
		try {
			errCode = LJUD.eGet(intHandle, LJUD.Constants.ioSTART_STREAM, 0, refValue, 0);
			log.info("startStream request returned: {}", errCode);
		} catch (LJUDException le) {
			try {
				errCode = LJUD.eGet(intHandle, LJUD.Constants.ioSTOP_STREAM, 0, refZero, 0);
				errCode = LJUD.eGet(intHandle, LJUD.Constants.ioSTART_STREAM, 0, refValue, 0);
			} catch (LJUDException lee) {
				// ok to fail here
				log.info("stopStream request returned: {}", errCode);
				ErrorHandler(errCode);
			}
		}

		// The actual scan rate is dependent on how the desired scan rate
		// divides into the LabJack clock. The actual scan rate is returned
		// in the value parameter from the start stream command.
		log.info("Actual Scan Rate = {}", refValue.getValue());
		log.info("Actual Sample Rate = {}", (2 * refValue.getValue()));

	}

	private int getAIMask(Collection<? extends RpMetric> waves) {
		int mask = 0;
		// **********************************
		// request SE streaming on AIN0 and AIN1
		// **********************************
		for (RpMetric desc : waves) {
			String loc = desc.getLocation();

			String s = loc.substring(4);
			int bit = Integer.parseInt(s);
			if (loc.startsWith("E")) {
				bit += 8;
			}

			mask |= 1 << bit;
		}

		return mask;
	}

	@Override
	public void disconnect() throws IOException {

		running = false;

		setStatus(ConnectionStatus.NOT_CONNECTED);

	}

	@Override
	public DeviceCapabilities getStaticCapabilities() {

		return cap;
	}

	public void asyncCallback() {
		try {

			PersistentItem nmb = ModelUtil.getModelFromDataClass(metricModel);
			// double[] data = metricReader.readSingleSample();

			// int idx = 0;
			long time = PlatformUtil.currentTimeMillis();
			nmb.setTime(time);
			for (RpMetric metric : nmb.getMetrics()) {
				// NumericsItem item = new NumericsItem(metric);
				// item.setValue( (int) (1000.0 * data[idx]) );
				// item.setTime(time);
				// nmb.add(item);
				// idx++;
				log.error("LabJack: Async Reading not ready.");
			}
			fireStreamEvent(0, this, StreamID.MEASUREMENT, nmb);

		} catch (Exception exception) {
			// // Display Errors
			// System.err.println(exception.getMessage());
			// // wlb runningTask = null;
			// waveTask.dispose();
			// metricTask.dispose();
			//
			setStatus(ConnectionStatus.DATA_NOT_AVAIL);
		}
	}

	/*
	 * ListAll(), labjack specific function
	 */
	
	public static DeviceRecord[] getDevices() {
		IntByReference pNumFound = new IntByReference(0);
		
		// as documented, must pass a buffer with at least 128 elements allocated
		int[] serNo = new int[128];
		int[] id = new int[128];
		double[] addr = new double[128];
		LJUD.listAll(LJUD.Constants.dtU3, LJUD.Constants.ctUSB, pNumFound , serNo, id, addr);
		
		int numFound = pNumFound.getValue();
		if( numFound == 0 ) {
			return null;
		}
		
		DeviceRecord [] devs = new DeviceRecord[ numFound ];
		
		for( int i = 0; i < numFound; i++ ) {
			DeviceRecord dev = new DeviceRecord();
			// dev.setSerialNo("" + serNo[i]);
			dev.setUniqueID("" + id[i]);
			dev.setFullName("" + addr[i]);
			
			devs[i] = dev;
		}
		
		return devs;
	}
	/*
	 * (non-Javadoc)
	 * @see idea.intf.AbstractStreamProducer#getConfiguration()
	 */
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
				setStatus(NOT_CONNECTED);
			}
		} else {
			if (deviceState != CONNECTED) {
				setStatus(CONNECTED);
			}
		}
		
		return 0;
	}

}
