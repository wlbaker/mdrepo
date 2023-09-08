package idea.tsoffline.persist;

import java.awt.Color;
import java.util.Date;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Table;
import javax.persistence.Transient;

// Generated May 17, 2007 10:53:35 AM by Hibernate Tools 3.2.0.b9

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.persistence.Text;
import idea.schema.rp.RpMetric;
import lombok.Data;

@Entity

@Table(name = "TSO_EVENT")
@Data
public class EventItem extends PersistentItem {

	@Transient
	protected static RpMetric[] metrics;

	static {
		metrics = IntfUtil.getMetrics(EventItem.class);
	}

	public EventItem() {
		super( StreamID.ANNOTATION );
	}
	
	public EventItem(String code, String description, Date dt) {
		this.code = code;
		this.desc = description;
		this.setTm(dt);
	}

	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}
	@Column(name = "desc")
	@Text(loc = "desc", code="", length=128)
	private String desc;
	
	@Column(name = "code")
	@Text(loc = "code", code = "", length=16)
	private String code;
	
	@Column(name = "color")
	@Metric(loc = "color", code = "")
	private Color color;

}
