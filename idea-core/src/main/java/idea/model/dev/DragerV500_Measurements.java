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

@SuppressWarnings("serial")
@Entity
@Table(name = "DragerV500"
)
@Data
@EqualsAndHashCode(callSuper=false)
public class DragerV500_Measurements extends PersistentItem {
	private static final String two_subscript = "2";
	@Transient
	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.buildMetrics( DragerV500_Measurements.class );
	}
	
	public DragerV500_Measurements() {
		super(StreamID.MEASUREMENT);
	}

	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}


	@Metric(loc = "0x06", code = "C", desc = "Compliance", unit = "L/bar")
	private int C;
	@Metric(loc = "0x07", code = "Cdyn", desc = "Compliance (Dynamic)", unit = "L/bar")
	private int Cdyn;
	@Metric(loc = "0x0B", code = "R", desc = "Resistance", unit = "mbar/L/s")
	private int R;
	@Metric(loc = "0x08", code = "Ralt", desc = "Resistance (Alt)", unit = "mbar/L/s")
	private int Ralt;
	@Metric(loc = "0x71", code = "Pmin", desc = "Minimum Airway Pressure", unit = "mbar")
	private int Pmin;

	@Metric(loc = "0x72", code = "Pocc", desc = "Occlusion Pressure", unit = "mbar")
	private int Pocc;

	@Metric(loc = "0x73", code = "Pmean", desc = "Mean Airway Pressure", unit = "mbar")
	private int Pmean;

	@Metric(loc = "0x74", code = "Pplat", desc = "Plateau Airway Pressure", unit = "mbar")
	private int Pplat;
	@Metric(loc = "0x78", code = "PEEP", desc = "PEEP Airway Pressure", unit = "cmH2O")
	private int PEEP;
	@Metric(loc = "0x79", code = "iPEEP", desc = "Intrinsic PEEP", unit = "cmH2O")
	private int iPEEP;
	@Metric(loc = "0x7D", code = "Ppeak", desc = "Peak Airway Pressure", unit = "cmH2O")
	private int Ppeak;
	@Metric(loc = "0x81", code = "TrVol", desc = "Trapped Volume", unit = "mL")
	private int TrVol;
	// @Metric( loc = "0x82", code = "TVexp", desc = "Expiratory Tidal Volume",
	// "L") private int TVexp;
	@Metric(loc = "0x88", code = "TVexp", desc = "Expiratory Tidal Volume", unit = "mL")
	private int TVexp;
	@Metric(loc = "0xB5", code = "fspn", desc = "Spont Breathing Frequency", unit = "1/min")
	private int fspn;
	// @Metric( loc = "0xB7", code = "MVspn", desc = "Spont Minute Volume", unit
	// = "L/min") private int MVspn;
	@Metric(loc = "0x7A", code = "MVspn", desc = "Spont Minute Volume", unit = "L/min")
	private int MVspn;
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
	@Metric(loc = "0xD6", code = "ftotal", desc = "Breathing Frequency", unit = "1/min")
	private int ftotal;
	@Metric(loc = "0x8B", code = "VTasb", desc = "Inspiratory spont, Support Volume (VTasb)", unit = "mL")
	private int VTasb;
	@Metric(loc = "0x8D", code = "NIF", desc = "Negative Inspiratory Force", unit = "mbar")
	private int NIF;
	@Metric(loc = "0xC9", code = "RSBI", desc = "Rapid Shallow Breathing Index", unit = "1/L x min")
	private int RSBI;

	@Metric(loc = "0x09", code = "CO2", desc = "CO" + two_subscript + " Production", unit = "mL/min")
	private int CO2;
	@Metric(loc = "0x89", code = "DS", desc = "Dead Space", unit = "mL")
	private int DS;
	@Metric(loc = "0x8A", code = "rDS", desc = "Relative Dead Space", unit = "%")
	private int rDS;
	@Metric(loc = "0xDB", code = "etCO2", desc = "End tidal CO" + two_subscript, unit = "%")
	private int etCO2pct;
	@Metric(loc = "0xE3", code = "etCO2", desc = "End tidal CO" + two_subscript, unit = "kPa")
	private int etCO2kPa;
	@Metric(loc = "0xE6", code = "etCO2", desc = "End tidal CO" + two_subscript, unit = "mmHg")
	private int etCO2mmHg;

	@Metric(loc = "0xF0", code = "FiO2", desc = "Insp. O" + two_subscript, unit = "%")
	private int FiO2;

	@Metric(loc = "0xE1", code = "HRspO2", desc = "Pulserate", unit = "1/min")
	private int HRspO2;
	@Metric(loc = "0xEB", code = "SPO2", desc = "Saturation", unit = "%")
	private int SPO2;


}
