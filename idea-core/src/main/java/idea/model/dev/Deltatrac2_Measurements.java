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
@Table(name = "Deltatrac2_Measurements"
// , uniqueConstraints = { @UniqueConstraint( columnNames = { "ORDER_DATE",
// "TYPE", "RECNUM" } ),
// @UniqueConstraint( columnNames = { "TYPE", "ORDER_DATE", "ORDER_NO", "RECNUM"
// } ),
// @UniqueConstraint( columnNames = { "TYPE", "`DIV`", "ORDER_NO" } ),
// @UniqueConstraint( columnNames = { "`DIV`", "ORDER_NO" } ) }
)
@Data
@EqualsAndHashCode(callSuper=false)
public class Deltatrac2_Measurements extends PersistentItem {
	private static final String two_subscript = "2";
	@Transient
	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.buildMetrics( Deltatrac2_Measurements.class );
	}
	
	public Deltatrac2_Measurements() {
		super(StreamID.MEASUREMENT);
	}

	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}


	@Metric(loc="" +4, code="VCO2", unit="ml/min")
	int VCO2;
	@Metric(loc="" +5, code="VO2", unit="ml/min")
	int VO2;
	@Metric(loc="" +6, code="RQ", unit="s", precision=2)
	int RQ;
	@Metric(loc="" +7, code="EE",  unit="kcal/24h", precision=1)
	int EE;
	@Metric(loc="" +8, code="FiO2", unit="%", precision=1 )
	int FiO2;
	@Metric(loc="" +9, code="unk1"  )
	int UNK1;
	@Metric(loc="" +10, code="unk2"  )
	int UNK2;
	@Metric(loc="" +11, code="BRTH", unit="br/min")
	int F;
	@Metric(loc="" +12, code="VE", unit="L/min")
	int VE;
	@Metric(loc="" +13, code="unk3"  )
	int UNK3;
	@Metric(loc="" +14, code="temp", unit="F", precision=1 )
	int T;
	@Metric(loc="" +15, code="unk4"  )
	int UNK4;

}
