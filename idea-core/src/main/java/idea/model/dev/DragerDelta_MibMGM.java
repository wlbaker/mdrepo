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

@Entity
@Table(name = "DragerDelta_MibMGM")
@Data
public class DragerDelta_MibMGM extends PersistentItem {
	@Transient
	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.buildMetrics( DragerDelta_MibMGM.class );
	}
	
	public DragerDelta_MibMGM() {
		super(StreamID.MEASUREMENT);
	}

	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}

	@Column(name = "ethal", nullable = true)
	@Metric(loc ="mgm_agent.ethal", code="etHAL", unit = "%", precision=1)
	private Integer ethal;
	
	@Column(name = "ihal", nullable = true)
	@Metric(loc ="mgm_agent.ihal", code="iHAL", unit = "%", precision=1)
	private Integer ihal;
	
	@Column(name = "eto2", nullable = true)
	@Metric(loc ="mgm_o2.eto2", code="etO2", unit = "%")
	private Integer eto2;
	
	@Column(name = "io2", nullable = true)
	@Metric(loc ="mgm_o2.io2", code="iO2", unit = "%")
	private Integer io2;
	
	@Column(name = "etn2o", nullable = true)
	@Metric(loc ="mgm_n2o.etn2o", code="etN2O", unit = "%")
	private Integer etn2o;
	
	@Column(name = "in2o", nullable = true)
	@Metric(loc ="mgm_n2o.in2o", code="iN2O", unit = "%")
	private Integer in2o;
	
	@Column(name = "etco2", nullable = true)
	@Metric(loc ="mgm_co2.etco2", code="etCO2", unit = "mmHg")
	private Integer etco2;
	
	@Column(name = "ides", nullable = true)
	@Metric(loc ="mgm_agent.ides", code="mgmIDES", unit = "%", precision=1)
	private Integer ides;
	
	@Column(name = "mac", nullable = true)
	@Metric(loc ="mgm_agent.mac", code="mgmMAC", unit = "", precision=1)
	private Integer mac;
	
	@Column(name = "ico2", nullable = true)
	@Metric(loc ="mgm_agent.ico2", code="mgmICO2", unit="mmHg", precision=1)
	private Integer ico2;

	@Column(name = "rr", nullable = true)
	@Metric(loc ="mgm_agent.rr", code="mgmRR", unit="bpm")
	private Integer rr;

	@Column(name = "etiso", nullable = true)
	@Metric(loc ="mgm_agent.etiso", code="mgmEtISO", desc="End tidal Isoflurane", unit="%", precision=1)
	private Integer etiso;

	@Column(name = "iiso", nullable = true)
	@Metric(loc ="mgm_agent.iiso", code="mgmISO", desc="Isoflurane", unit="%", precision=1)
	private Integer iiso;


	@Column(name = "etenf", nullable = true)
	@Metric(loc ="mgm_agent.etenf", code="mgmEtEnf", unit = "%", precision=1)
	private Integer etenf;

	@Column(name = "iinf", nullable = true)
	@Metric(loc ="mgm_agent.iinf", code="mgmIInf", unit = "mmHg")
	private Integer iinf;

	@Column(name = "etsev", nullable = true)
	@Metric(loc ="mgm_agent.etsev", code="mgmEtSEV", unit = "%", precision=1)
	private Integer etsev;

	@Column(name = "isev", nullable = true)
	@Metric(loc ="mgm_agent.isev", code="mgmiSEV", unit = "%", precision=1)
	private Integer isev;

	@Column(name = "etdes", nullable = true)
	@Metric(loc ="mgm_agent.etdes", code="mgmEtDES", unit = "%", precision=1)
	private Integer etdes;


	/*
	 * THIS COULD BE WRONG!!!!...another ico2 entry above
	 * ...MAYBE iso2???
	 */
	@Column(name = "co2_ico2", nullable = true)
		@Metric(loc ="mgm_co2.ico2", code="mgmco2ICO2", unit = "mmHg")
	private Integer co2_ico2;

	@Column(name = "co2_rr", nullable = true)
	@Metric(loc ="mgm_co2.rr", code="mgmco2RR", desc="Respiratory Rate (CO2)", unit = "bpm")
	private Integer co2_rr;

	@Column(name = "ienf", nullable = true)
		@Metric(loc ="mgm_agent.ienf", code="mgmIEnf", unit = "%", precision=1)
	private Integer ienf;

}
