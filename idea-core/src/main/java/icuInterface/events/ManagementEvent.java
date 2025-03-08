package icuInterface.events;

import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpMetric;

import jakarta.persistence.Transient;

import lombok.Data;

@Data
@SuppressWarnings("serial")
public class ManagementEvent extends PersistentItem {

	public static final int DEV_CHANGE = 99;

	@Transient
	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.getMetrics(ManagementEvent.class);
	}

	// not sure what to do with this!  Serialize?
	RpDevice conf;

	@Metric(loc = "action", code = "action")
	private int action;
	@Metric(loc = "reqid", code = "reqid")
	private int reqId;

	public ManagementEvent(StreamProducer source, int action, int reqId, RpDevice conf) {
		super(source, StreamID.MANAGEMENT.getCode());
		this.action = action;
		this.reqId = reqId;
		this.conf = conf;
	}

	public RpDevice getDevice() {
		return conf;
	}

	public int getAction() {
		return action;
	}

	public int getReqId() {
		return reqId;
	}

	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}

}
