package idea.model.dev;

import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;

import jakarta.persistence.Column;
import jakarta.persistence.Transient;

import lombok.Data;

@SuppressWarnings("serial")
@Data
public class AestivaMeasurement extends PersistentItem {
	@Transient
	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.getMetrics(AestivaMeasurement.class);
	}
	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}
	
	@Column(name="TV", nullable=false)
	@Metric(loc="aaaa", code="mtv", desc="Measured tidal volume", unit="ml") private int mtv;
	@Metric(loc="bbbb", code="mmv", desc="Measured Minute Volume", unit="L") private int mmv;
	@Metric(loc="ddd", code="mrr", desc="Measured Respiratory Rate", unit="/min") private int mrr;
	@Metric(loc="eee", code="mol", desc="Measured Oxygen Level", unit="%") private int mol;
	@Metric(loc="fff", code="mmpp", desc="Measured Max Positive Pressure", unit="cmH2O") private int mmpp;
	@Metric(loc="ggg", code="mipp", desc="Measured Inspiratory Plateau Press", unit="cmH2O") private int mipp;
	@Metric(loc="hhh", code="mmeanp", desc="Measured Mean Pressure", unit="cmH2O") private int mmeanp;
	@Metric(loc="iii", code="mminp", desc="Measured Minimum Pressure", unit="cmH2O") private int mminp;
	@Metric(loc="j", code="mJ", desc="Measured Data Status") private int mJ;

	@Metric(loc="stv_a", code="stv", desc="Set Tidal Volume", unit="ml") private int stv;
	@Metric(loc="stv_b", code="stv", desc="Set Tidal Volume", unit="/min") private int stv$b;
	@Metric(loc="dddd", code="i:e", desc="Set I:E ratio") private int i2e;
	@Metric(loc="ee", code="ipaus", desc="Inspiratory Pause") private int ipaus;
	@Metric(loc="ff", code="sPEEP", desc="Set PEEP", unit="cmH2O") private int sPEEP;
	@Metric(loc="sPP", code="sPP", desc="Set Peak Pressure", unit="cmH2O") private int sPP;
	@Metric(loc="hh", code="sIP", desc="Set Inspired Pressure", unit="cmH2O") private int sIP;
	@Metric(loc="ii", code="sSPal", desc="Set Sustained Pressure Alarm Limit", unit="cmH2O") private int sSPal;
	@Metric(loc="jjj", code="HVal", desc="High Minute Volume Alarm Limit", unit="L", precision=1) private int HVal;
	@Metric(loc="kkk", code="LVal", desc="Low Minute Volume Alarm Limit", unit="L", precision=1) private int LVal;
	@Metric(loc="lll", code="HVL", desc="High Vte Limit", unit="ml", precision=1) private int HVL;
	@Metric(loc="mmm", code="LVL", desc="Low Vte Limit", unit="ml",precision=1) private int LVL;
	@Metric(loc="nnn", code="HOal", desc="High Oxygen Alarm Limit", unit="%O2") private int HOal;
	@Metric(loc="ooo", code="LOal", desc="Low Oxygen Alarm Limit", unit="%O2") private int LOal;
	@Metric(loc="q", code="qv", desc="Ventilation Mode") private int qv;
	@Metric(loc="rrrrrrrrrrrr", code="stv", desc="Set ") private int sunk;


}
