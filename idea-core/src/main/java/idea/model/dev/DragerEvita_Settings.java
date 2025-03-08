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


@Entity
@Data
@EqualsAndHashCode(callSuper = false)
public class DragerEvita_Settings extends PersistentItem {

	@Transient
	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.buildMetrics(DragerEvita_Settings.class);
	}

	public DragerEvita_Settings() {
		super(StreamID.MEASUREMENT);
	}

	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}

	// settings: Ti, Slope

	@Metric(loc = "1x01", code = "O2", desc = "Insp. Oxygen", unit = "%")
	Integer O2;
	@Metric(loc = "1x02", code = "iFlow", desc = "Max ins. Flow", unit = "L/min", precision = 1)
	Integer iFlow;
	@Metric(loc = "1x04", code = "iTV", desc = "Insp. Tidal Volume", unit = "L", precision = 3)
	Integer iTV;
	@Metric(loc = "1x05", code = "Ti", desc = "Ti", unit = "s", precision = 2)
	Integer Ti;
	@Metric(loc = "1x07", code = "I:E_I", desc = "I:E I-Part", precision = 2)
	Integer I2E;
	@Metric(loc = "1x08", code = "I:E_E", desc = "I:E E-Part", precision = 2)
	Integer E2E;
	@Metric(loc = "1x09", code = "fIMV", desc = "Frequency IMV (SIMV)", unit = "/min", precision = 1)
	Integer fIMV;
	@Metric(loc = "1x0A", code = "fIPPV", desc = "Frequency IPPV", unit = "/min", precision = 1)
	Integer fIPV;

	@Metric(loc = "1x0B", code = "PEEP", desc = "PEEP (CPAP)", unit = "mbar", precision = 2)
	Integer PEEP;

	@Metric(loc = "1x0C", code = "intPEEP", desc = "Intermittend PEEP", unit = "mbar")
	Integer intPEEP;
	@Metric(loc = "1x0D", code = "lpBIPAP", desc = "BIPAP low Pressure", unit = "mbar")
	Integer lpBIPAP;
	@Metric(loc = "1x0E", code = "hpBIPAP", desc = "BIPAP high Pressure", unit = "mbar")
	Integer hpBIPAP;
	@Metric(loc = "1x0F", code = "ltBIPAP", desc = "BIPAP low Time", unit = "s", precision = 1)
	Integer ltBIPAP;
	@Metric(loc = "1x10", code = "htBIPAP", desc = "BIPAP high Time", unit = "s", precision = 1)
	Integer htBIPAP;

	@Metric(loc = "1x11", code = "tAPNEA", desc = "Apnea Time", unit = "s")
	Integer tAPNEA;
	@Metric(loc = "1x12", code = "ASB", desc = "Assisted spon Breath", unit = "mbar")
	Integer ASB;
	@Metric(loc = "1x13", code = "miap", desc = "Max. insp. Airway Pressure", unit = "mbar", precision = 1)
	Integer miap;
	@Metric(loc = "1x15", code = "tp", desc = "Trigger Pressure", unit = "mbar", precision = 1)
	Integer tp;

	@Metric(loc = "1x16", code = "fTachAp", desc = "Tachyapnea Frequency", unit = "/min")
	Integer fTachAp;

	@Metric(loc = "1x17", code = "tTachAp", desc = "Tachyapnea Duration", unit = "s")
	Integer tTachAp;
	@Metric(loc = "1x29", code = "Flow Trigger", desc = "Flow Trigger", unit = "L/min")
	Integer FT;
	@Metric(loc = "1x2E", code = "rASB", desc = "ASB Ramp", unit = "s", precision = 2)
	Integer rASB;

	@Metric(loc = "1x3C", code = "fa", desc = "Flow Assist", unit = "mbar*s/L", precision = 1)
	Integer FA;
	@Metric(loc = "1x3D", code = "va", desc = "Volume Assist", unit = "mbar/L", precision = 1)
	Integer VA;
	@Metric(loc = "1x4E", code = "td", desc = "Tdeconnected", unit = "s")
	Integer TD;

	@Metric(loc = "1x42", code = "bF", desc = "Backup Frequency", unit = "/min", precision = 1)
	Integer BF;
	@Metric(loc = "1x43", code = "bInspP", desc = "Backup insp. Pressure", unit = "mbar", precision = 1)
	Integer bInspP;
	@Metric(loc = "1x44", code = "bTV", desc = "Backup Tidal Volume", unit = "L", precision = 3)
	Integer bTV;
	@Metric(loc = "1x45", code = "iP", desc = "Insp. Pressure", unit = "mbar", precision = 1)
	Integer iP;

	@Metric(loc = "1x46", code = "TC", desc = "Tube-Compenstation", unit = "%")
	Integer TC;
	@Metric(loc = "1x47", code = "tdia", desc = "Tube-Diameter", unit = "mm", precision = 1)
	Integer tdia;
	@Metric(loc = "1x63", code = "m0", desc = "Max Insp Time CPAP ASB", unit = "s", precision = 2)
	Integer m0;
	@Metric(loc = "1x72", code = "m1", desc = "Threshold of end of flow", unit = "%", precision = 2)
	Integer m1;
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
