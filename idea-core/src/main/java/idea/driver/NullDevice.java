package idea.driver;

import static icuInterface.ConnectionStatus.CONNECTED;
import static icuInterface.ConnectionStatus.NOT_CONNECTED;
import idea.conf.DeviceCapabilities;
import idea.conf.DeviceConfiguration;
import idea.intf.AbstractStreamProducer;
import idea.intf.AdapterInterface;
import idea.message.StreamID;
import idea.model.ModelUtil;
import idea.model.PersistentItem;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpStream;

import java.io.IOException;
import java.util.List;

import lombok.extern.slf4j.Slf4j;

@Slf4j
public class NullDevice extends AbstractStreamProducer implements
		AdapterInterface {

	private static final String driverName = "misc/Null Driver";

	protected RpDevice conf;
	protected DeviceCapabilities caps;

	public static DeviceConfiguration createConfigInstance() {
		DeviceConfiguration conf = new DeviceConfiguration(NullDevice.class);
		conf.setName(driverName);
		// conf.setModelName("[no_model]");
		return conf;
	}

	public NullDevice(RpDevice conf) { // no capabilities...hmm
		this.conf = conf;
		caps = new DeviceCapabilities(NullDevice.class);
		if (conf == null) {
			log.error("NO CONFIGURATION");
		} else {
			for (RpStream s : (List<? extends RpStream>)conf.getStreams()) {
				caps.addStream(s);
			}
		}
	}

	public NullDevice(DeviceCapabilities caps, DeviceConfiguration conf) {
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
		
		List streams = caps.getStreams();
		if( streams.size() > 0 ) {
			for( Object s : streams ) {
				RpStream rps = (RpStream) s;
				Class cl = rps.getPIClass();
				System.out.println("pi class=" + cl );
				PersistentItem model = ModelUtil.getModelFromDataClass( cl );
				model.setTime( System.currentTimeMillis() );
				this.fireStreamEvent( 0, // unsolicited
						this, // src
						StreamID.MEASUREMENT, // stream id
						model);  // data
			}
		}
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

}
