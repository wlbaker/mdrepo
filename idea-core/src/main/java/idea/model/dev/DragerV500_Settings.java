package idea.model.dev;

// Generated May 17, 2007 10:53:35 AM by Hibernate Tools 3.2.0.b9

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.persistence.Text;
import idea.schema.rp.RpMetric;

import jakarta.persistence.Entity;
import jakarta.persistence.Transient;

import lombok.Data;
import lombok.EqualsAndHashCode;

@SuppressWarnings("serial")
@Entity
@Data
@EqualsAndHashCode(callSuper = false)
public class DragerV500_Settings extends PersistentItem {
	private static final String two_subscript = "2";
	@Transient
	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.buildMetrics(DragerV500_Settings.class);
	}

	public DragerV500_Settings() {
		super(StreamID.MEASUREMENT);
	}

	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}

	// settings: Ti, Slope

	@Metric(loc = "1x01", code = "O2", desc = "Insp. Oxygen", unit = "%")
	int O2;
	@Metric(loc = "1x02", code = "iFlow", desc = "Max ins. Flow", unit = "L/min", precision = 1)
	int iFlow;
	@Metric(loc = "1x04", code = "iTV", desc = "Insp. Tidal Volume", unit = "L", precision = 3)
	int iTV;
	@Metric(loc = "1x05", code = "Ti", desc = "Ti", unit = "s", precision = 2)
	int Ti;
	@Metric(loc = "1x07", code = "I:E_I", desc = "I:E I-Part", precision = 2)
	int I2E;
	@Metric(loc = "1x08", code = "I:E_E", desc = "I:E E-Part", precision = 2)
	int E2E;
	@Metric(loc = "1x09", code = "fIMV", desc = "Frequency IMV (SIMV)", unit = "/min", precision = 1)
	int fIMV;
	@Metric(loc = "1x0B", code = "PEEP", desc = "PEEP (CPAP)", unit = "mbar", precision = 2)
	int PEEP;

	@Metric(loc = "1x11", code = "tAPNEA", desc = "Apnea Time", unit = "s")
	int tAPNEA;
	@Metric(loc = "1x16", code = "fTachAp", desc = "Tachyapnea Frequency", unit = "/min")
	int fTachAp;
	@Metric(loc = "1x46", code = "TC", desc = "Tube-Compenstation", unit = "%")
	int TC;
	@Metric(loc = "1x47", code = "tdia", desc = "Tube-Diameter", unit = "mm", precision = 1)
	int tdia;
	@Metric(loc = "1x63", code = "m0", desc = "Max Insp Time CPAP ASB", unit = "s", precision = 2)
	int m0;
	@Metric(loc = "1x72", code = "m1", desc = "Threshold of end of flow", unit = "%", precision = 2)
	int m1;
	@Text(loc = "TXT0", code = "txt0", desc = "Text Code 0", length = 16)
	String txt0;
	@Text(loc = "TXT1", code = "txt1", desc = "Text Code 1", length = 16)
	String txt1;
	@Text(loc = "TXT2", code = "txt2", desc = "Text Code 2", length = 16)
	String txt2;
	@Text(loc = "TXT3", code = "txt3", desc = "Text Code 3", length = 16)
	String txt3;
	@Text(loc = "TXT4", code = "txt4", desc = "Text Code 4", length = 16)
	String txt4;
	@Text(loc = "TXT5", code = "txt5", desc = "Text Code 5", length = 16)
	String txt5;

}
