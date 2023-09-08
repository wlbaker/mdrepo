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
@Table(name = "HamiltonMeas"
// , uniqueConstraints = { @UniqueConstraint( columnNames = { "ORDER_DATE",
// "TYPE", "RECNUM" } ),
// @UniqueConstraint( columnNames = { "TYPE", "ORDER_DATE", "ORDER_NO", "RECNUM"
// } ),
// @UniqueConstraint( columnNames = { "TYPE", "`DIV`", "ORDER_NO" } ),
// @UniqueConstraint( columnNames = { "`DIV`", "ORDER_NO" } ) }
)
@Data
@EqualsAndHashCode(callSuper=false)
public class HamiltonMeasurement extends PersistentItem {
	@Transient
	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.buildMetrics( HamiltonMeasurement.class );
	}
	
	public HamiltonMeasurement() {
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

	@Metric(loc = "0x24", code = "PEEP", desc = "PEEP/CPAP", unit = "cmH2O")
	private int PEEP;
	@Metric(loc = "0x25", code = "Pmin", unit = "cmH2O")
	private int Pmin;

	@Metric(loc = "0x2C", code = "VTE", desc = "Exp. Volume", unit = "mL")
	private int VTE;
	@Metric(loc = "0x2D", code = "VTEspn", desc = "VT Exp spont", unit = "mL")
	private int VTEspont;
	
	@Metric(loc = "0x30", code = "f", desc = "f total", unit = "b/min")
	private int f;
	@Metric(loc = "0x31", code = "fSpont", desc = "f spont", unit = "b/min")
	private int fSpont;
	
	@Metric(loc = "0x35", code = "R insp", desc = "Resistance (Inspiratory)", unit = "mbar/L/s")
	private int R;
	@Metric(loc = "0x36", code = "R exp", desc = "Resistance (Expiratory)", unit = "mbar/L/s")
	private int Ralt;
	@Metric(loc = "0x37", code = "C", desc = "Compliance", unit = "L/bar")
	private int C;
	@Metric(loc = "0x37", code = "RCinsp", unit = "L/bar")
	private int RCinsp;
	
	
	// RESUME HERE
	
	@Metric(loc = "0x72", code = "Pocc", desc = "Occlusion Pressure", unit = "mbar")
	private int Pocc;

	@Metric(loc = "0x81", code = "TrVol", desc = "Trapped Volume", unit = "mL")
	private int TrVol;
	// @Metric( loc = "0x82", code = "TVexp", desc = "Expiratory Tidal Volume",
	// "L") private int TVexp;

	
	// @Metric( loc = "0xB7", code = "MVspn", desc = "Spont Minute Volume", unit
	// = "L/min") private int MVspn;
	// @Metric( loc = "0xB8", code = "MV", desc = "Minute Volume - ??", unit =
	// "L/min") private int MV;
	@Metric(loc = "0xB9", code = "MV", desc = "Minute Volume", unit = "mL/min")
	private int MV;
	@Metric(loc = "0x0C", code = "Ltc", desc = "Lung Timeconstant", unit = "ms")
	private int Ltc;
	@Metric(loc = "0xD0", code = "MTF", desc = "Mandatory Trigger Frequency", unit = "1/min")
	private int MTF;

	@Metric(loc = "0xC1", code = "GTemp", desc = "Gas Temperature", unit = "C")
	private int GTemp;
	@Metric(loc = "0x8B", code = "VTasb", desc = "Inspiratory spont, Support Volume (VTasb)", unit = "mL")
	private int VTasb;
	@Metric(loc = "0x8D", code = "NIF", desc = "Negative Inspiratory Force", unit = "mbar")
	private int NIF;
	@Metric(loc = "0xC9", code = "RSBI", desc = "Rapid Shallow Breathing Index", unit = "1/L x min")
	private int RSBI;

	@Metric(loc = "0x09", code = "CO2", desc = "CO2 Production", unit = "mL/min")
	private int CO2;
	@Metric(loc = "0x89", code = "DS", desc = "Dead Space", unit = "mL")
	private int DS;
	@Metric(loc = "0x8A", code = "rDS", desc = "Relative Dead Space", unit = "%")
	private int rDS;
	@Metric(loc = "0xDB", code = "etCO2", desc = "End tidal CO2", unit = "%")
	private int etCO2pct;
	@Metric(loc = "0xE3", code = "etCO2", desc = "End tidal CO2", unit = "kPa")
	private int etCO2kPa;
	@Metric(loc = "0xE6", code = "etCO2", desc = "End tidal CO2", unit = "mmHg")
	private int etCO2mmHg;

	@Metric(loc = "0xF0", code = "FiO2", desc = "Insp. O2", unit = "%")
	private int FiO2;

	@Metric(loc = "0xE1", code = "HRspO2", desc = "Pulserate", unit = "1/min")
	private int HRspO2;
	@Metric(loc = "0xEB", code = "SPO2", desc = "Saturation", unit = "%")
	private int SPO2;


}
