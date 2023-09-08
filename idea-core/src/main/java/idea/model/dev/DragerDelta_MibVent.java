package idea.model.dev;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Table;
import javax.persistence.Transient;

import lombok.Data;
import lombok.EqualsAndHashCode;

@Entity
@Table(name = "DragerDelta_MibVent")
@Data
@EqualsAndHashCode(callSuper=false)
public class DragerDelta_MibVent extends PersistentItem {
	@Transient
	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.buildMetrics( DragerDelta_MibVent.class );
	}
	
	public DragerDelta_MibVent() {
		super(StreamID.MEASUREMENT);
	}

	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}

	@Metric(loc = "mib_vent.tva_spon", code = "TVA_SPON", unit = "ml")
	private int tva_spon;

	@Metric(loc = "mib_vent.tva_mech", code = "TVA_MECH", unit = "ml")
	private int tva_mech;

	@Metric(loc = "mib_vent.mva_spon", code = "MVA_SPON", unit = "L", precision=1)
	private int mva_spon;

	@Metric(loc = "mib_vent.mva_mech", code = "MVA_MECH", unit = "L", precision=1)
	private int mva_mech;

	@Metric(loc = "mib_vent.peco2", code = "PECO2", unit = "mmHg")
	private int peco2;

	@Metric(loc = "mib_vent.dilut_ratio_aw", code = "dilut_ratio_aw", unit = "", precision=2)
	private int dilut_ratio_aw;

	@Metric(loc = "mib_vent.insp_time", code = "insp_time", unit = "s")
	private int insp_time;

	@Metric(loc = "mib_vent.exp_time", code = "exp_time", unit = "s")
	private int exp_time;

	@Metric(loc = "mib_vent.insp_time_pct", code = "insp_time_pct", unit = "%")
	private int insp_time_pct;

	@Metric(loc = "mib_vent.tv_leak", code = "tv_leak", unit = "%")
	private int tv_leak;

	@Metric(loc = "mib_vent.mv_pct", code = "mv_pct", unit = "%")
	private int mv_pct;

	@Metric(loc = "mib_vent.raw", code = "raw", unit = "cmH2O/L/s")
	private int raw;

	@Metric(loc = "mib_vent.pap", code = "pap", unit = "cmH2O")
	private int pap;

	@Metric(loc = "mib_vent.peep", code = "peep", unit = "cmH2O")
	private int peep;

	@Metric(loc = "mib_vent.pmap", code = "pmap", unit = "cmH2O")
	private int pmap;

	@Metric(loc = "mib_vent.mv", code = "mv", unit = "L/min", precision=1)
	private int mv;

	@Metric(loc = "mib_vent.tv", code = "tv", unit = "ml")
	private int tv;

	@Metric(loc = "mib_vent.rr", code = "rr", unit = "bpm")
	private int rr;

	@Metric(loc = "mib_vent.pause", code = "pause", unit = "cmH2O")
	private int pause;

	@Metric(loc = "mib_vent.io2", code = "io2", unit = "%")
	private int io2;

	@Metric(loc = "mib_vent.mvi", code = "mvi", unit = "L/min", precision=1)
	private int mvi;

	@Metric(loc = "mib_vent.tvi", code = "tvi", unit = "ml")
	private int tvi;

	@Metric(loc = "mib_vent.tvi_mech", code = "tvi_mech", unit = "ml")
	private int tvi_mech;

	@Metric(loc = "mib_vent.tvi_spon", code = "tvi_spon", unit = "ml")
	private int tvi_spon;

	@Metric(loc = "mib_vent.tva", code = "tva", unit = "ml")
	private int tva;

	@Metric(loc = "mib_vent.mva", code = "mva", unit = "L", precision=1)
	private int mva;

	@Metric(loc = "mib_vent.vd_aw", code = "vd_aw", unit = "ml")
	private int vd_aw;

	@Metric(loc = "mib_vent.c_dyn", code = "c_dyn", unit = "ml/cmH2O")
	private int c_dyn;

	@Metric(loc = "mib_vent.c2o_dyn", code = "c2o_dyn", unit = "", precision=2)
	private int c2o_dyn;

	@Metric(loc = "mib_vent.eraw", code = "eraw", unit = "cmH2O/L/s")
	private int eraw;

	@Metric(loc = "mib_vent.iraw", code = "iraw", unit = "cmH2O/L/s")
	private int iraw;

	@Metric(loc = "mib_vent.wo_bimp", code = "wo_bimp", unit = "J/L/s", precision=2)
	private int wo_bimp;

	@Metric(loc = "mib_vent.pif", code = "pif", unit = "L/min")
	private int pif;

	@Metric(loc = "mib_vent.pef", code = "pef", unit = "L/min")
	private int pef;

	@Metric(loc = "mib_vent.tve_mech", code = "tve_mech", unit = "ml")
	private int tve_mech;

	@Metric(loc = "mib_vent.tve_spon", code = "tve_spon", unit = "ml")
	private int tve_spon;

	@Metric(loc = "mib_vent.mve_mech", code = "mve_mech", unit = "L", precision=1)
	private int mve_mech;

	@Metric(loc = "mib_vent.mve_spon", code = "mve_spon", unit = "L", precision=1)
	private int mve_spon;

	@Metric(loc = "mib_vent.rr_mech", code = "rr_mech", unit = "bpm")
	private int rr_mech;

	@Metric(loc = "mib_vent.rr_spon", code = "rr_spon", unit = "bpm")
	private int rr_spon;
	@Column(name = "rsbi", nullable = true)
	@Metric(loc = "mib_vent.rsbi", code = "rsbi", unit = "bpm/L")
	private int rsbi;

	@Metric(loc = "mib_vent.mvco2", code = "mvco2", unit = "ml/min")
	private int mvco2;

	@Metric(loc = "mib_vent.tvco2", code = "tvco2", unit = "ml")
	private int tvco2;

	//@Column(name = "mib_vent.tva_spon", nullable = true)
	//	@Metric(loc ="mib_vent.tva_spon", code="tva_spon", unit = "??")
	//private int tva_spon;

	@Metric(loc = "mib_vent.map", code = "mib_vent.map", unit = "??")
	private int map;

	@Metric(loc = "mib_vent.ieratio", code = "mib_vent.ieratio", unit = "", precision=1)
	private int ieratio;

}
