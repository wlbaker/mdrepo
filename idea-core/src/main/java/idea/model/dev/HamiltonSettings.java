package idea.model.dev;

// Generated May 17, 2007 10:53:35 AM by Hibernate Tools 3.2.0.b9

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;

import javax.persistence.Entity;
import javax.persistence.Table;
import javax.persistence.Transient;

import lombok.Data;
import lombok.EqualsAndHashCode;

@Entity
@Table(name = "HamiltonSettings"
// , uniqueConstraints = { @UniqueConstraint( columnNames = { "ORDER_DATE",
// "TYPE", "RECNUM" } ),
// @UniqueConstraint( columnNames = { "TYPE", "ORDER_DATE", "ORDER_NO", "RECNUM"
// } ),
// @UniqueConstraint( columnNames = { "TYPE", "`DIV`", "ORDER_NO" } ),
// @UniqueConstraint( columnNames = { "`DIV`", "ORDER_NO" } ) }
)
@Data
@EqualsAndHashCode(callSuper=false)
public class HamiltonSettings extends PersistentItem {
	@Transient
	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.buildMetrics( HamiltonSettings.class );
	}
	
	public HamiltonSettings() {
		super(StreamID.MEASUREMENT);
	}

	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}


	@Metric(loc = "0x21", code = "Pmax", unit = "cmH2O")
	private int Ppeak;
	@Metric(loc = "0x22", code = "Pplat", unit = "cmH2O")
	private int Pplat;
	@Metric(loc = "0x23", code = "Pmean", unit = "cmH2O")
	private int Pmean;

	@Metric(loc = "0x2C", code = "VT", desc = "Tidal Volume", unit = "mL")
	private int VT;	
	@Metric(loc = "0x30", code = "f", desc = "f total", unit = "b/min")
	private int f;
	
	@Metric(loc = "0xF0", code = "FiO2", desc = "Insp. O2", unit = "%")
	private int FiO2;



}
