package idea.model.dev;

// Generated May 17, 2007 10:53:35 AM by Hibernate Tools 3.2.0.b9

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Text;
import idea.schema.rp.RpMetric;

import jakarta.persistence.Entity;
import jakarta.persistence.Transient;

import lombok.Data;
import lombok.EqualsAndHashCode;

@SuppressWarnings("serial")
@Entity
@Data
@EqualsAndHashCode(callSuper = false)
public class ZTrace extends PersistentItem {
	@Transient
	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.buildMetrics(ZTrace.class);
	}

	public ZTrace() {
		super(StreamID.TRACE);
	}

	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}

	@Text(loc = "TXT0", code = "txt0", desc = "Text Code 0", length = 16)
	String txt0;
	@Text(loc = "TXT1", code = "txt1", desc = "Text Code 1", length = 16)
	String txt1;

}
