package icuInterface.events;

import jakarta.persistence.Transient;

import idea.conf.DeviceConfiguration;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.PersistentItem;
import idea.schema.rp.RpMetric;

@SuppressWarnings("serial")
public class CapabilitiesEvent extends PersistentItem {

	@Transient
	private static RpMetric[] metrics = null;
	private DeviceConfiguration cap;

	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}

	public CapabilitiesEvent(StreamProducer source, DeviceConfiguration cap) {
		super(source, StreamID.CAPABILITIES.getCode() );
		this.setCapabilities(cap);

	}

	public void setCapabilities(DeviceConfiguration cap) {
		this.cap = cap;
	}

	public DeviceConfiguration getCapabilities() {
		return cap;
	}

	@Override
	public String toString() {
		String val = "???";
		
		if( cap != null ) {
			val = cap.toString();
		}
		
		return val;
	}

	

}
