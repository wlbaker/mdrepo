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
@Table(name = "BIS_Measurement")
@Data
@EqualsAndHashCode(callSuper = false)
public class BISMeasurement extends PersistentItem {

	@Transient
	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.buildMetrics(BISMeasurement.class);
	}

	public BISMeasurement() {
		super(StreamID.MEASUREMENT);
	}

	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}

	// @Column(name = "spo2.hr", nullable = true)
	@Metric(loc = "CH12.SR", code = "SR", desc = "Suppression Ratio", precision = 1, unit = "%")
	private int SR;
	@Metric(loc = "CH12.BURST", code = "BURST", desc = "Burst Count", unit = "bursts/min")
	private int burstRate;
	@Metric(loc = "CH12.SEF", code = "SEF", desc = "Spectral Edge Frequency", unit = "Hz", precision = 2)
	private int SEF;
	@Metric(loc = "CH12.BISBIT", code = "BISBIT", desc = "BIS bits")
	private int BISBIT;
	@Metric(loc = "CH12.BIS", code = "BIS", desc = "Bispectral Index", precision = 1)
	private int BIS;
	@Metric(loc = "CH12.BISALT", code = "BISALT", desc = "Bispectral Alternative Index", precision = 1)
	private int BISALT;
	@Metric(loc = "CH12.BISAL2", code = "BISAL2", desc = "Bispectral Alternative Index 2", precision = 1)
	private int BISAL2;
	@Metric(loc = "CH12.TOTPOW", code = "POW", desc = "Total Power", unit = "dB", precision = 2)
	private int TOTPOW;
	@Metric(loc = "CH12.EMGLOW", code = "EMG", desc = "EMG Low", unit = "dB", precision = 2)
	private int EMG;
	@Metric(loc = "CH12.SQI", code = "SQI", desc = "Signal Quality Index", precision = 1, unit = "%")
	private int SQI;
	@Metric(loc = "CH12.IMP", code = "IMP", desc = "Impedance", unit = "kOhm")
	private int IMP;
	@Metric(loc = "CH12.ARTF2", code = "ARTF2", desc = "Artifact Flags")
	private int ARTF2;
	// sBIS
	// sEMG
	// RESVAR0
	// ASYM
	// BILBITS

}
