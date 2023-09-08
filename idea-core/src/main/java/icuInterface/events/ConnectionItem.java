package icuInterface.events;

import icuInterface.ConnectionStatus;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;

import javax.persistence.Transient;

import lombok.Data;

@Data
public class ConnectionItem extends PersistentItem {

	private static final long serialVersionUID = 1519789946653270221L;
	
	@Transient
	private static RpMetric[] metrics;
	
	@Metric(loc="info", code="info")
	private String connectInfo;
	@Metric(loc="stat", code="stat")
	private ConnectionStatus status;

	static {
		metrics = IntfUtil.getMetrics(ConnectionItem.class);
	}
	
	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}

	public ConnectionItem(ConnectionStatus newStatus) {
		this( newStatus, "<????>" ); 
	}

	public ConnectionItem(ConnectionStatus newStatus, String connectInfo) {
		super( StreamID.CONNECTION );
		this.setStatus(newStatus);
		this.connectInfo = connectInfo;
	}

}