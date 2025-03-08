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
@Table(name = "DragerEvita_Measurements"
// , uniqueConstraints = { @UniqueConstraint( columnNames = { "ORDER_DATE",
// "TYPE", "RECNUM" } ),
// @UniqueConstraint( columnNames = { "TYPE", "ORDER_DATE", "ORDER_NO", "RECNUM"
// } ),
// @UniqueConstraint( columnNames = { "TYPE", "`DIV`", "ORDER_NO" } ),
// @UniqueConstraint( columnNames = { "`DIV`", "ORDER_NO" } ) }
)
@Data
@EqualsAndHashCode(callSuper=false)
public class DragerEvita_Measurements extends PersistentItem {
	private static final String two_subscript = "2";
	@Transient
	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.buildMetrics( DragerEvita_Measurements.class );
	}
	
	public DragerEvita_Measurements() {
		super(StreamID.MEASUREMENT);
	}

	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}


	// @Column(name = "HR", nullable = true)
	@Metric(loc = "0x06", code = "C", desc = "Compliance", unit = "L/bar")
	private Integer C;
	@Metric(loc = "0x07", code = "Cdyn", desc = "Compliance (Dynamic)", unit = "L/bar")
	private Integer Cdyn;
	@Metric(loc = "0x0B", code = "R", desc = "Resistance", unit = "mbar/L/s")
	private Integer R;
	@Metric(loc = "0x08", code = "Ralt", desc = "Resistance (Alt)", unit = "mbar/L/s")
	private Integer Ralt;
	@Metric(loc = "0x71", code = "Pmin", desc = "Minimum Airway Pressure", unit = "mbar")
	private Integer Pmin;

	@Metric(loc = "0x72", code = "Pocc", desc = "Occlusion Pressure", unit = "mbar")
	private Integer Pocc;

	@Metric(loc = "0x73", code = "Pmean", desc = "Mean Airway Pressure", unit = "mbar")
	private Integer Pmean;

	@Metric(loc = "0x74", code = "Pplat", desc = "Plateau Airway Pressure", unit = "mbar")
	private Integer Pplat;
	@Metric(loc = "0x78", code = "PEEP", desc = "PEEP Airway Pressure", unit = "cmH2O")
	private Integer PEEP;
	@Metric(loc = "0x79", code = "iPEEP", desc = "Intrinsic PEEP", unit = "cmH2O")
	private Integer iPEEP;
	@Metric(loc = "0x7D", code = "Ppeak", desc = "Peak Airway Pressure", unit = "cmH2O")
	private Integer Ppeak;
	@Metric(loc = "0x81", code = "TrVol", desc = "Trapped Volume", unit = "mL")
	private Integer TrVol;
	// @Metric( loc = "0x82", code = "TVexp", desc = "Expiratory Tidal Volume",
	// "L") private Integer TVexp;
	@Metric(loc = "0x88", code = "TVexp", desc = "Expiratory Tidal Volume", unit = "mL")
	private Integer TVexp;
	@Metric(loc = "0xB5", code = "fspn", desc = "Spont Breathing Frequency", unit = "1/min")
	private Integer fspn;
	@Metric( loc = "0xB7", code = "MVspn", desc = "Spont Minute Volume", unit = "L/min") 
	private Integer MVspn;
	@Metric(loc = "0x7A", code = "MVspn", desc = "(Deprecated) Spont Minute Volume", unit = "L/min")
	private Integer MVspn7A;
	// @Metric( loc = "0xB8", code = "MV", desc = "Minute Volume - ??", unit =
	// "L/min") private Integer MV;
	@Metric(loc = "0xB9", code = "MV", desc = "Minute Volume", unit = "mL/min")
	private Integer MV;
	@Metric(loc = "0x0C", code = "Ltc", desc = "Lung Timeconstant", unit = "ms")
	private Integer Ltc;
	@Metric(loc = "0xD0", code = "MTF", desc = "Mandatory Trigger Frequency", unit = "1/min")
	private Integer MTF;

	@Metric(loc = "0xC1", code = "GTemp", desc = "Gas Temperature", unit = "C")
	private Integer GTemp;
	@Metric(loc = "0xD6", code = "ftotal", desc = "Breathing Frequency", unit = "1/min")
	private Integer ftotal;
	@Metric(loc = "0x8B", code = "VTasb", desc = "Inspiratory spont, Support Volume (VTasb)", unit = "mL")
	private Integer VTasb;
	@Metric(loc = "0x8D", code = "NIF", desc = "Negative Inspiratory Force", unit = "mbar")
	private Integer NIF;
	@Metric(loc = "0xC9", code = "RSBI", desc = "Rapid Shallow Breathing Index", unit = "1/L x min")
	private Integer RSBI;

	@Metric(loc = "0x09", code = "CO2", desc = "CO" + two_subscript + " Production", unit = "mL/min")
	private Integer CO2;
	@Metric(loc = "0x89", code = "DS", desc = "Dead Space", unit = "mL")
	private Integer DS;
	@Metric(loc = "0x8A", code = "rDS", desc = "Relative Dead Space", unit = "%")
	private Integer rDS;
	@Metric(loc = "0xDB", code = "etCO2", desc = "End tidal CO" + two_subscript, unit = "%")
	private Integer etCO2pct;
	@Metric(loc = "0xE3", code = "etCO2", desc = "End tidal CO" + two_subscript, unit = "kPa")
	private Integer etCO2kPa;
	@Metric(loc = "0xE6", code = "etCO2", desc = "End tidal CO" + two_subscript, unit = "mmHg")
	private Integer etCO2mmHg;

	@Metric(loc = "0xF0", code = "FiO2", desc = "Insp. O" + two_subscript, unit = "%")
	private Integer FiO2;

	@Metric(loc = "0xE1", code = "HRspO2", desc = "Pulserate", unit = "1/min")
	private Integer HRspO2;
	@Metric(loc = "0xEB", code = "SPO2", desc = "Saturation", unit = "%")
	private Integer SPO2;

}
