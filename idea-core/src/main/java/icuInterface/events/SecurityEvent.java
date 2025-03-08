package icuInterface.events;

import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.schema.rp.RpMetric;

import jakarta.persistence.Transient;

import lombok.Data;

@Data
public class SecurityEvent extends PersistentItem {

	@Transient
	private static RpMetric[] metrics = null;

	static {
		metrics = IntfUtil.getMetrics(SecurityEvent.class);
	}

	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}

	private boolean accept;
	
	public SecurityEvent(StreamProducer source, boolean accept ) {
		super(source, StreamID.SECURITY.getCode() );
		this.setLogin( accept );
	}

	public void setLogin(boolean accept) {
		this.accept = accept;
	}

	@Override
	public String toString() {
		return "[Security: " + accept + "]";
	}
	

}
