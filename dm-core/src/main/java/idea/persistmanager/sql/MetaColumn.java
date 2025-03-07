package idea.persistmanager.sql;

import jakarta.persistence.Column;
import jakarta.persistence.Entity;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;
import jakarta.persistence.NamedQueries;
import jakarta.persistence.NamedQuery;
import jakarta.persistence.Table;

import idea.schema.rp.RpLinearUnit;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpPrecisionUnit;
import idea.schema.rp.RpUnit;
import lombok.Data;

/**
 * Database metadata reflective of the RpMetric
 */
@SuppressWarnings("serial")
@Entity
@NamedQueries({
//@NamedQuery(name = "metaByDevice", query = "from MetaLog t where t.device=:device order by t.seq"),
@NamedQuery(name = "metaByTable", query = "from MetaColumn t where t.table=:table order by t.seq") // 
})
@Table(name = "AA_METACOL")
@Data
public class MetaColumn implements java.io.Serializable {

	@Id
	@GeneratedValue(strategy = GenerationType.IDENTITY)
	private long oid;
	
	@Column
	private long tallyOID;

	@Column(name = "TABL", length = 16, nullable = false)
	private String table;
	@Column
	private int streamID;

	//@Column(name = "DEV_OID", nullable = false)
	@Column(name = "SEQ")
	private int seq;

	@Column(length = 16, nullable = false)
	private String loc;
	@Column(length = 16)
	private String code;
	@Column(length = 16)
	private String name;
	@Column(length = 16)
	private String unit;

	@Column
	private double m;

	@Column
	private double b;

	public MetaColumn() {
	}

	public MetaColumn(long tallyOID, String table, int streamID, int seq, RpMetric md) {
		this.tallyOID = tallyOID;
		this.table = table;
		this.streamID = streamID;
		this.seq = seq;
		this.loc = md.getLocation();
		this.code = md.getCode();
		this.name = md.getName();
		this.unit = md.getUnitName();
		RpUnit unit = md.getUnit();
		if (unit == null) {
			// ignore
		} else if (unit instanceof RpLinearUnit) {
			RpLinearUnit linear = (RpLinearUnit) unit;
			this.m = linear.getM();
			this.b = linear.getB();
		} else if (unit instanceof RpPrecisionUnit) {
			RpPrecisionUnit prec = (RpPrecisionUnit) unit;
			this.m = prec.getPrecision();
		}
	}

}
