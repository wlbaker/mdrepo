package idea.driver;

import static icuInterface.ConnectionStatus.CONNECTED;
import static icuInterface.ConnectionStatus.NOT_CONNECTED;
import idea.conf.DeviceCapabilities;
import idea.conf.DeviceConfiguration;
import idea.intf.AbstractStreamProducer;
import idea.intf.AdapterInterface;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpStream;

import java.io.IOException;
import java.util.List;

public class NullStreamProducer extends AbstractStreamProducer implements AdapterInterface {

	private static final String driverName="z/Null Stream Producer";
	protected RpDevice conf;
	protected DeviceCapabilities caps;

	public static DeviceConfiguration createConfigInstance() {
		DeviceConfiguration conf = new DeviceConfiguration(NullStreamProducer.class);
		conf.setName("Null00");
		conf.setModelName("[no_model]");
		return conf;
	}

	public NullStreamProducer(RpDevice conf) { // no capabilities...hmm
		this.conf = conf;
		List<RpStream> streams = null;

		caps = getStaticCapabilities();  // superclass can override--hint
		if (conf != null) {
			streams = conf.getStreams();
		} else if (caps != null ) {
			streams = caps.getStreams();
		}

//		if (streams != null) {
//			for (RpStream s : streams) {
//				conf.addStream(s);
//			}
//		}
	}

	public NullStreamProducer(DeviceCapabilities caps, DeviceConfiguration conf) {
		this.conf = conf;
		this.caps = caps;
	}

	@Override
	public void connect() throws IOException {
		setStatus(CONNECTED);
	}

	@Override
	public void disconnect() {
		setStatus(NOT_CONNECTED);
	}

	@Override
	public RpDevice getConfiguration() {
		return conf;
	}

	@Override
	public void requestCapabilities() throws IOException {
		fireCapabilitiesEvent(this, caps);
	}

	@Override
	public DeviceCapabilities getStaticCapabilities() {
		return caps;
	}

	@Override
	public int tick() {
		return 0;
	}

	@Override
	public String toString() {
		String str;
		if (conf != null) {
			str = "[nulldevice " + conf.toString() + "]";
		} else {
			str = super.toString();
		}
		return str;
	}

	protected void setCapabilities(DeviceCapabilities caps) {
		this.caps = caps;

	}

}
