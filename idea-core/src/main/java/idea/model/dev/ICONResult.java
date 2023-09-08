package idea.model.dev;

import idea.intf.AdapterInterface;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.persistence.Text;
import idea.schema.rp.RpMetric;

import javax.persistence.Entity;
import javax.persistence.Table;

import lombok.Data;
import lombok.EqualsAndHashCode;

@Entity
@Table(name = "ICON")

@Data
@EqualsAndHashCode(callSuper=false)
public class ICONResult extends PersistentItem {

	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.getMetrics(ICONResult.class);
	}

	public ICONResult(AdapterInterface driver) {
		super(StreamID.MEASUREMENT);

	}

	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}

	@Text(loc = "GENDER", code = "GENDER", desc = "Gender", length = 6)
	private  String gender;

	@Metric(loc = "age", code = "age", desc = "Age", unit = "yr")
	private  Integer AGE;
	@Metric(loc = "P4", code = "p4", desc = "P4", unit = "")
	private  Integer p4;
	@Metric(loc = "CO", code = "CO", desc = "Cardiac Output", unit = "l/min")
	private  Integer CO;
	@Metric(loc = "HR", code = "HR", desc = "Heart Rate", unit = "bpm")
	private  Integer HR;
	@Metric(loc = "SV", code = "SV", desc = "SV", unit = "ml")
	private  Integer SV;
	@Metric(loc = "TFC", code = "TFC", desc = "TFC", unit = "")
	private  Integer TFC;
	@Metric(loc = "ICON", code = "ICON", desc = "ICON", unit = "")
	private  Integer ICON;
	@Metric(loc = "P14", code = "P14", desc = "P14", unit = "")
	private  Integer P14;
	@Metric(loc = "STR", code = "STR", desc = "STR", unit = "")
	private  Integer STR;
	

}
