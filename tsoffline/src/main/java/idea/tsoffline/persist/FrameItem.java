package idea.tsoffline.persist;

import java.util.Date;

import jakarta.persistence.Column;
import jakarta.persistence.Entity;
import jakarta.persistence.Table;
import jakarta.persistence.Transient;

// Generated May 17, 2007 10:53:35 AM by Hibernate Tools 3.2.0.b9

import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.persistence.Text;
import idea.schema.rp.RpMetric;
import lombok.Data;

@Entity

@Table(name = "TSO_FRAME")
@Data
public class FrameItem extends PersistentItem {

	@Transient
	protected static RpMetric[] metrics;

	static {
		metrics = IntfUtil.getMetrics(FrameItem.class);
	}

	public FrameItem() {
		super((StreamProducer)null, StreamID.MEASUREMENT.getCode());
	}
	
	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}


	@Column(name = "Panel")
	@Text(loc = "Panel", code="Panel")
	private String panel;
	
	@Column(name = "sig_dev")
	@Text(loc = "sig_dev", code = "")
	private String sig_dev;
	
	@Column(name = "sig_loc")
	@Text(loc = "sig_loc", code = "")
	private String sig_loc;
	
	@Column(name = "sig_name")
	@Text(loc = "sig_name", code = "")
	private String sig_name;
	
	@Column(name = "ts_start")
	@Metric(loc = "ts_start", code = "")
	private Date ts_start;
	
	@Column(name = "ts_end")
	@Metric(loc = "ts_end", code = "")
	private Date ts_end;
	
	@Column(name = "view_start")
	@Metric(loc = "view_start", code = "")
	private Date view_start;
	
	@Column(name = "view_end")
	@Metric(loc = "view_end", code = "")
	private Date view_end;
	
	@Column(name = "pos")
	@Metric(loc = "pos", code = "")
	private int pos;

}
