package idea.model.dev;

// Generated May 17, 2007 10:53:35 AM by Hibernate Tools 3.2.0.b9

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;

import jakarta.persistence.Entity;
import jakarta.persistence.Transient;

import lombok.Data;
import lombok.EqualsAndHashCode;

@SuppressWarnings("serial")
@Entity
@Data
@EqualsAndHashCode(callSuper = false)
public class Fabius_Settings extends PersistentItem {
	@Transient
	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.buildMetrics(Fabius_Settings.class);
	}

	public Fabius_Settings() {
		super(StreamID.MEASUREMENT);
	}

	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}

	// settings: Ti, Slope

	@Metric(loc = "1x04", code = "iTV", desc = "Inspiratory Tidal Volume", unit = "L", precision = 3)
	int iTV;
	@Metric(loc = "1x05", code = "Ti", desc = "Inspiratory Time", unit = "s", precision = 2)
	int Ti;
	@Metric(loc = "1x07", code = "I:E_I", desc = "I:E I-Part", precision = 2)
	int I2E;
	@Metric(loc = "1x08", code = "I:E_E", desc = "I:E E-Part", precision = 2)
	int E2E;
	@Metric(loc = "1x0A", code = "fIPPV", desc = "Frequency IPPV", unit = "/min", precision = 1)
	int fIPV;

	@Metric(loc = "1x0B", code = "PEEP", desc = "PEEP (CPAP)", unit = "mbar", precision = 2)
	int PEEP;

	@Metric(loc = "1x0C", code = "intPEEP", desc = "Intermittend PEEP", unit = "mbar")
	int intPEEP;

	@Metric(loc = "1x13", code = "miap", desc = "Max. insp. Airway Pressure", unit = "mbar", precision = 1)
	int miap;
	@Metric(loc = "1x27", code = "iPiT", desc = "Insp. Pause / Insp Time", unit = "%")
	int iPiT;
	@Metric(loc = "1x29", code = "Flow Trigger", desc = "Flow Trigger", unit = "L/min")
	int FT;
	@Metric(loc = "1x45", code = "iP", desc = "Insp. Pressure", unit = "mbar", precision = 1)
	int iP;
	@Metric(loc = "1x4C", code = "iFlow", desc = "Inspiratory Flow", unit = "L/sec", precision=3)  //???
	int tdia;
	@Metric(loc = "1x54", code = "m0", desc = "Max Insp Time CPAP ASB", unit = "s", precision = 2)
	int m0;
//	@Text(loc = "TXT0", code = "txt0", desc = "Text Code 0", length = 16)
//	String txt0;
//	@Text(loc = "TXT1", code = "txt1", desc = "Text Code 1", length = 16)
//	String txt1;
//	@Text(loc = "TXT2", code = "txt2", desc = "Text Code 2", length = 16)
//	String txt2;
//	@Text(loc = "TXT3", code = "txt3", desc = "Text Code 3", length = 16)
//	String txt3;
//	@Text(loc = "TXT4", code = "txt4", desc = "Text Code 4", length = 16)
//	String txt4;
//	@Text(loc = "TXT5", code = "txt5", desc = "Text Code 5", length = 16)
//	String txt5;

}
