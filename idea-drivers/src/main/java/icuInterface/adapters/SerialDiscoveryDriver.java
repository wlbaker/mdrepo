package icuInterface.adapters;

import java.io.IOException;
import java.util.Enumeration;
import java.util.LinkedList;

import com.fazecast.jSerialComm.SerialPort;

import icuInterface.ConnectionStatus;
import idea.conf.DeviceCapabilities;
import idea.conf.DeviceConfiguration;
import idea.intf.AbstractStreamProducer;
import idea.intf.AdapterInterface;
import idea.intf.AdapterUtil;
import idea.intf.DataTyp;
import idea.message.StreamID;
import idea.model.ModelUtil;
import idea.model.PersistentItem;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpMetric;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class SerialDiscoveryDriver extends AbstractStreamProducer implements AdapterInterface {

	@SuppressWarnings("unused")
	private static final String driverName="misc/Serial Discovery Service";

	private RpDevice conf;

	protected static DeviceCapabilities cap;

	public static DeviceConfiguration createConfigInstance() {
		return new DeviceConfiguration(SerialDiscoveryDriver.class);
	}


	static {

		cap = new DeviceCapabilities(SerialDiscoveryDriver.class);

		// cap.addStream(StreamID.MEASUREMENT, AS50_Measurement.class);
		// cap.addStream(StreamID.SETTINGS, AS50_Settings.class);

		// cap.addConnection(new SerialConnection(9600, 8, 1,0));

		// cap.setModels(new String[] { "AS50" });
		
		//rxtx Enumeration<?> portList = CommPortIdentifier.getPortIdentifiers();
		SerialPort[] ports = SerialPort.getCommPorts();

		LinkedList<RpMetric> availablePorts = new LinkedList<RpMetric>();
		//rxtx while (portList.hasMoreElements()) {
		for(SerialPort port : ports) {
			String portId = port.getSystemPortName();
			String portName = port.getDescriptivePortName();  // long name with spaces
			// String portDesc = port.getPortDescription(); // only has a (unique) value for USB devices

			//rxtx if (portID.getPortType() == CommPortIdentifier.PORT_SERIAL) {
				RpMetric m = new RpMetric();
				m.setLocation( portId );  // rxtx portID.getName() )
				m.setName( portName );
				m.setSubtyp( DataTyp.BOOLEAN_TYP );
				availablePorts.add(m);
			//rxtx }
		}
		
		Class<? extends PersistentItem> model;
		try {
			model = ModelUtil.createDynamicModel("serialDisc", availablePorts);
			cap.addStream(StreamID.SETTINGS, model );
		} catch (Exception e) {
			log.error("INTERNAL ERROR", e);
		}

	}

	public SerialDiscoveryDriver(RpDevice conf) {
		this.conf =  conf;

		AdapterUtil.fix_config(cap, conf);

	}

	@Override
	public void connect() throws IOException {
		try {
			
			// start the discovery worker?  Encapsulate the discovery worker here??
		} catch (Exception e) {
			e.printStackTrace();
			throw new IOException(e);
		}

	}

	@Override
	public void disconnect() throws IOException {
		setStatus(ConnectionStatus.NOT_CONNECTED);
	}

	@Override
	public void requestCapabilities() throws IOException {
		fireCapabilitiesEvent(this, cap);
	}

	@Override
	public DeviceCapabilities getStaticCapabilities() {
		return cap;
	}

	public void configureMetrics(RpMetric[] metrics) throws IOException {
		if (metrics == null) {
			return;
		}

		// sendPacket(ESC, CONFIG_DATA, configReq);
	}

	@Override
	public RpDevice getConfiguration() {
		return conf;
	}

	/* *************************************************************************
	 * Requests
	 * *************************************************************************
	 */

	@Override
	public int tick() {
		return 0;
	}

}
