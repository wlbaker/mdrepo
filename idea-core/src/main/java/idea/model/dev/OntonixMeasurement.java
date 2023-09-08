package idea.model.dev;

import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;

import javax.persistence.Entity;
import javax.persistence.Transient;

import lombok.Data;

@Entity
@SuppressWarnings("serial")
@Data
public class OntonixMeasurement extends PersistentItem {
	@Transient
	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.getMetrics(OntonixMeasurement.class);
	}

	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}

	@Metric( loc="STS", code="STS", unit="", precision=2)
	private int STS;
	@Metric( loc="MTS", code="MTS", unit="", precision=2)
	private int MTS;
	@Metric( loc="LTS", code="LTS", unit="", precision=2)
	private int LTS;
	@Metric( loc="CPLX", code="CPLX", unit="", precision=2)
	private int CPLX;
	@Metric( loc="LWRCPLX", code="LWRCPLX", unit="", precision=2)
	private int LWRCPLX;
	@Metric( loc="UPRCPLX", code="UPRCPLX", unit="", precision=2)
	private int UPRCPLX;
	@Metric( loc="ENTR", code="ENTR", unit="", precision=2)
	private int ENTR;
	@Metric( loc="ROBUST", code="ROBUST", unit="", precision=2)
	private int ROBUST;
	

}
