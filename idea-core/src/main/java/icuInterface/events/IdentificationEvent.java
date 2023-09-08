package icuInterface.events;

import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;

import javax.persistence.Transient;

import lombok.Data;

@SuppressWarnings("serial")
@Data
public class IdentificationEvent extends PersistentItem {
	/**
	 * 
	 */
	@Transient
	private static RpMetric[] metrics;
	
	static {
		metrics = IntfUtil.getMetrics(IdentificationEvent.class);
	}

	@Metric(loc="id", code="id")
	private String id;

	public IdentificationEvent(StreamProducer source, String id) {
		super(source, StreamID.IDENTIFICATION.getCode() );
		this.id = id;

	}

	@Override
	public RpMetric[] getMetrics()  {
		// TODO Auto-generated method stub
		return null;
	}
	

}
