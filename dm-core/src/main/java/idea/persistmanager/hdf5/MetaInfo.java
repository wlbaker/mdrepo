package idea.persistmanager.hdf5;

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
import lombok.EqualsAndHashCode;

@Entity
@Table(name = "META")
@Data
@EqualsAndHashCode(callSuper = false)
public class MetaInfo extends PersistentItem {

	@Transient
	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.buildMetrics(MetaInfo.class);
	}

	public MetaInfo() {
		super(StreamID.MEASUREMENT);
	}

	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}

	// @Column(name = "spo2.hr", nullable = true)
	@Text(loc = "loc", length=16)
	private String loc;
	@Text(loc = "code", length=16)
	private String code;
	@Text(loc = "desc", length=32)
	private String desc;
	@Text(loc = "unit", length=32)
	private String unit;
	@Metric(loc = "sigtyp")
	private int sigtyp;
	@Metric(loc = "rate")
	private int rate;
	@Metric(loc = "spp")
	private int spp;
	@Metric(loc = "lu_m")
	private double lu_m;
	@Metric(loc = "lu_b")
	private double lu_b;
	@Metric(loc = "pu_p")
	private int pu_p;
	//@Metric(loc = "txt_len")
	//private int txt_len;
	@Metric(loc = "subtyp")
	private int subtyp;

}
