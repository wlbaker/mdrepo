package idea.model.dev;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Table;

import lombok.Data;
import lombok.EqualsAndHashCode;

@Entity
@Table(name = "PoleStar")

@Data
@EqualsAndHashCode(callSuper=false)
public class PolestarMeasurement extends PersistentItem {

	public final static String RED = "01";
	public final static String GREEN = "02";
	public final static String BLUE = "03";
	public final static String INFR = "04";
	public final static String TEMP = "05";
	public final static String CO2 = "06";

	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.getMetrics(PolestarMeasurement.class);
	}

	public PolestarMeasurement() {
		super( StreamID.MEASUREMENT);
	}

	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}

	@Column(name = "RED", nullable = true)
	@Metric(loc = RED, code = RED, desc = "Red Spectrum")
	private  Integer red;

	@Column(name = "BLUE", nullable = true)
	@Metric(loc = GREEN, code = GREEN, desc = "Green Spectrum")
	private  Integer blue;

	@Column(name = "GREEN" + BLUE, nullable = true)
	@Metric(loc = BLUE, code = BLUE, desc = "Blue Spectrum")
	private Integer green;

	@Column(name = "INFR", nullable = true)
	@Metric(loc = INFR, code = INFR, desc = "Infr Spectrum")
	private  Integer infr;
	
	@Column(name = "TEMP", nullable = true)
	@Metric(loc = TEMP, code = TEMP, desc = "Temp", unit="C")
	private  Integer temp;
	
	@Column(name = "CO2", nullable = true)
	@Metric(loc = CO2, code = CO2, desc = "CO2", unit = "mmHg")
	private  Integer co2;
	

}
