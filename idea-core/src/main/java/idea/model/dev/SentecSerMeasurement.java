package idea.model.dev;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Table;
import javax.persistence.Transient;

import lombok.Data;

@Entity
@Table(name = "SentecSer")
@Data
public class SentecSerMeasurement extends PersistentItem {
	@Transient
	private static RpMetric[] metrics;
	
	public static final String PACO2_LOC = "PACO2";
	public static final String SPO2_LOC = "SPO2";
	public static final String HR_LOC = "HR";
	public static final String PI_LOC = "PI"; // wrong!
	public static final String RHP_LOC = "RHP"; // wrong!

	static {
		metrics = IntfUtil.getMetrics(SentecSerMeasurement.class);
	}

	public SentecSerMeasurement() {
		super( StreamID.MEASUREMENT );
	}

	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}
	
	@Column(name = PACO2_LOC, nullable = true)
	@Metric(loc = PACO2_LOC, code = PACO2_LOC, unit = "mmHg", precision=1)
	private Integer paCO2Item;
	
	@Column(name = SPO2_LOC, nullable = true)
	@Metric(loc = SPO2_LOC, code = SPO2_LOC, unit = "%")
	private Integer spO2Item;

	@Column(name = HR_LOC, nullable = true)
	@Metric(loc = HR_LOC, code = HR_LOC, unit = "bpm")
	private Integer hrItem;

	@Column(name = PI_LOC, nullable = true)
	@Metric(loc = PI_LOC, code = PI_LOC, unit = "unk")
	private Integer piItem;

	@Column(name = RHP_LOC, nullable = true)
	@Metric(loc = RHP_LOC, code = RHP_LOC, unit = "")
	private Integer rhpItem;


}
