package idea.model.dev;

// Generated May 17, 2007 10:53:35 AM by Hibernate Tools 3.2.0.b9

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;

import jakarta.persistence.Entity;
import jakarta.persistence.Table;
import jakarta.persistence.Transient;

import lombok.Data;
import lombok.EqualsAndHashCode;

@Entity
@Table(name = "ASTM_Measurement")
@Data
@EqualsAndHashCode(callSuper = false)
public class ASTMMeasurement extends PersistentItem {

	@Transient
	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.buildMetrics(ASTMMeasurement.class);
	}

	public ASTMMeasurement() {
		super(StreamID.MEASUREMENT);
	}

	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}

	// @Column(name = "spo2.hr", nullable = true)
	@Metric(loc = "CH12.SR", code = "SR", desc = "Suppression Ratio", precision = 1, unit = "%")
	private int SR;

}
