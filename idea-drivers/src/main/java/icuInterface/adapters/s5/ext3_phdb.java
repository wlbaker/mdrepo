package icuInterface.adapters.s5;

import jakarta.persistence.Transient;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.CompositeMetric;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;
import lombok.Data;

/* **************************************************************************
* EXT3 fields
*/
@Data
class bal_gas_group {
	@Transient
	private static RpMetric[] metrics= IntfUtil.getMetrics(bal_gas_group.class);;

	int hdr;
	@Metric(loc = "et", code = "et", unit = "mmHg", precision=2)
	Integer et;
	@Metric(loc = "fi", code = "fi", unit = "mmHg", precision=2)
	Integer fi;
}

@Data
class aa2_group {
	@Transient
	private static RpMetric[] metrics= IntfUtil.getMetrics(aa2_group.class);;

	int hdr;
	@Metric(loc = "mac", code = "mac", unit = "mmHg", precision=2)
	Integer mac_age_sum;
	byte[] reserved;
}

@Data
public class ext3_phdb extends PersistentItem {
	@Transient
	private static RpMetric[] metrics = IntfUtil.getMetrics(ext3_phdb.class);

	public ext3_phdb() {
		super( StreamID.MEASUREMENT );
	}

	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}

	@CompositeMetric(loc="gasex")
	gasex_group gasex = new gasex_group();
	
	@CompositeMetric(loc="flow_vol")
	flow_vol_group2 fvol2 = new flow_vol_group2();
	
	@CompositeMetric(loc="bal_gas")
	bal_gas_group bal = new bal_gas_group();
	
	@CompositeMetric(loc="tono")
	tono_group tono = new tono_group();
	
	@CompositeMetric(loc="aa2")
	aa2_group aa2 = new aa2_group();
	
	@Transient
	byte[] reserved = new byte[200];
}
