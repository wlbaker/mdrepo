package idea.model.dev;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.persistence.Text;
import idea.schema.rp.RpMetric;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Table;

import lombok.Data;
import lombok.EqualsAndHashCode;

@Entity
@Table(name = "MASTERFLEX")

@Data
@EqualsAndHashCode(callSuper=false)
public class LinkableInstrumentsMeasurement extends PersistentItem {

	public final static String SER_NO = "01";
	public final static String RPM = "RPM";
	public final static String TO_GO = "TO_GO";

	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.getMetrics(LinkableInstrumentsMeasurement.class);
	}

	public LinkableInstrumentsMeasurement() {
		super(StreamID.MEASUREMENT);

	}

	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}

	@Text(loc = SER_NO, code = "nnnnnnnn", desc = "Serial Number", length = 8)
	private  String serNo;

	@Column(name = RPM, nullable = true)
	@Metric(loc = "S", code = "rpm", desc = "RPM", unit = "rpm")
	private Double rpm;

	@Column(name = TO_GO, nullable = true)
	@Metric(loc = "V", code = "to_go", desc = "Revolutions To Go")
	private  Integer toGo;

}
