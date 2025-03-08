package idea.model.dev;

// Generated May 17, 2007 10:53:35 AM by Hibernate Tools 3.2.0.b9

import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.persistence.Text;
import idea.schema.rp.RpMetric;

import jakarta.persistence.Column;
import jakarta.persistence.Entity;
import jakarta.persistence.Table;
import jakarta.persistence.Transient;

import lombok.Data;

@Entity

@Table(name = "ISTAT"
// , uniqueConstraints = { @UniqueConstraint( columnNames = { "ORDER_DATE",
// "TYPE", "RECNUM" } ),
// @UniqueConstraint( columnNames = { "TYPE", "ORDER_DATE", "ORDER_NO", "RECNUM"
// } ),
// @UniqueConstraint( columnNames = { "TYPE", "`DIV`", "ORDER_NO" } ),
// @UniqueConstraint( columnNames = { "`DIV`", "ORDER_NO" } ) }
)
@Data
public class IstatMeasurement extends PersistentItem {

	@Transient
	protected static RpMetric[] metrics;

	static {
		metrics = IntfUtil.getMetrics(IstatMeasurement.class);
	}

	public IstatMeasurement() {
		super((StreamProducer)null, StreamID.MEASUREMENT.getCode());
	}
	
	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}

	@Column(name = "Panel")
	@Text(loc = "Panel", code="Panel")
	private String panel;
	
	@Column(name = "Field1", nullable = true)
	@Text(loc = "Field1", code="Field1")
	private String field1;
	@Column(name = "Field2", nullable = true)
	@Text(loc = "Field2", code="Field2")
	private String field2;
	@Column(name = "Field3", nullable = true)
	@Text(loc = "Field3", code="Field3")
	private String field3;
	
	// FIXME: next three fields are not verified!
	@Column(name = "Tpt", nullable = true)
	@Text(loc = "TPT", code="T", desc="Patient Temp" )
	private String tpt;
	@Column(name = "Sample", nullable = true)
	@Text(loc = "SAMPLE", code="Sample")
	private String sample;      // FIXME: ART/VEN/MXVEN...is this really a note?
	@Column(name = "CPB", nullable = true)
	@Text(loc = "CPB", code="CPB", desc="CPB Applied")
	private String CPB;  // FIXME: YES,NO,blank, other???
	
	@Column(name = "pH", nullable = true)
	@Metric(loc = "5", code = "pH", precision=3)
	private Integer pH;	
	@Column(name = "pCO2", nullable = true)
	@Metric(loc = "6", code = "pCO2", unit = "?", precision=1)
	private Integer pCO2;
	@Column(name = "pO2", nullable = true)
	@Metric(loc = "15", code = "pO2")
	private Integer pO2;
	@Column(name = "BE", nullable = true)
	@Metric(loc = "11", code = "BE")
	private Integer BE;
	@Column(name = "HCO3", nullable = true)
	@Metric(loc = "9", code = "HCO3")
	private Integer HCO3;

	@Column(name = "SO2", nullable = true)
	@Metric(loc = "19", code = "SO2", unit = "%")
	private Integer SO2;
	
	@Column(name = "Lac", nullable = true, precision=2)
	@Metric(loc = "24", code = "Lac")
	private Integer lactate;
	
	@Column(name = "Na", nullable = true)
	@Metric(loc = "0", code = "Na")
	private Integer Na;	
	@Column(name = "K", nullable = true)
	@Metric(loc = "1", code = "K")
	private Integer K;
	
	@Column(name = "Cl", nullable = true)
	@Metric(loc = "2", code = "Cl")
	private Integer Cl;
	
	@Column(name = "iCa", nullable = true)
	@Metric(loc = "4", code = "iCa")
	private Integer iCa;
	@Column(name = "TCO2", nullable = true)
	@Metric(loc = "8", code = "TCO2")
	private Integer TCO2;
	@Column(name = "Glu", nullable = true)
	@Metric(loc = "7", code = "Glu")
	private Integer Glu;
	@Column(name = "BUN", nullable = true)
	@Metric(loc = "3", code = "BUN")
	private Integer BUN;
	@Column(name = "Crea", nullable = true)
	@Metric(loc = "25", code = "Crea")
	private Integer Crea;
	@Column(name = "Hct", nullable = true)
	@Metric(loc = "13", code = "Hct")
	private Integer Hct;
	@Column(name = "Hb", nullable = true)
	@Metric(loc = "14", code = "Hb")
	private Integer Hb;
	@Column(name = "AnGap", nullable = true)
	@Metric(loc = "10", code = "AnGap")
	private Integer AnGap;
}
