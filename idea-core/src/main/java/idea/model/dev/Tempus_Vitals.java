package idea.model.dev;

// Generated May 17, 2007 10:53:35 AM by Hibernate Tools 3.2.0.b9

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;

import jakarta.persistence.CascadeType;
import jakarta.persistence.Entity;
import jakarta.persistence.JoinColumn;
import jakarta.persistence.OneToOne;
import jakarta.persistence.Table;
import jakarta.persistence.Transient;

import lombok.Data;
import lombok.EqualsAndHashCode;

@Entity
@Table(name = "Tempus$Vitals")
@Data
@EqualsAndHashCode(callSuper=false)
public class Tempus_Vitals extends PersistentItem {

	@Transient
	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.buildMetrics( Tempus_Vitals.class );
	}
	
	public Tempus_Vitals() {
		super(StreamID.MEASUREMENT);
	}

	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}

	 @Metric(loc="SysNIBP", unit="mm[Hg]")
	 Double SysNIBP;
	 @Metric(loc="DiaNIBP", unit="mm[Hg]")
	 Double DiaNIBP;
	 @Metric(loc="MeanNIBP", unit="mm[Hg]")
	 Double MeanNIBP;
	 @Metric(loc="HR", unit="/min")
	 Double HR;
	 @Metric(loc="SPO2", unit="%")
	 Double SPO2;
	 @Metric(loc="RESP", unit="/min")
	 Double RESP;
	 @Metric(loc="ETCO2", unit="mm[Hg]")
	 Double ETCO2;
	 @Metric(loc="Temperature1", unit="C")
	 Double Temperature1;
	 @Metric(loc="Temperature2", unit="C")
	 Double Temperature2;
	 @Metric(loc="P1_Sys", unit="mm[Hg]")
	 Double P1_Sys;
	 @Metric(loc="P1_Dia", unit="mm[Hg]")
	 Double P1_Dia;
	 @Metric(loc="P1_Mean", unit="mm[Hg]")
	 Double P1_Mean;
	 @Metric(loc="P2_Sys", unit="mm[Hg]")
	 Double P2_Sys;
	 @Metric(loc="P2_Dia", unit="mm[Hg]")
	 Double P2_Dia;
	 @Metric(loc="P2_Mean", unit="mm[Hg]")
	 Double P2_Mean;
	 @Metric(loc="P3_Sys", unit="mm[Hg]")
	 Double P3_Sys;
	 @Metric(loc="P3_Dia", unit="mm[Hg]")
	 Double P3_Dia;
	 @Metric(loc="P3_Mean", unit="mm[Hg]")
	 Double P3_Mean;
	 @Metric(loc="P4_Sys", unit="mm[Hg]")
	 Double P4_Sys;
	 @Metric(loc="P4_Dia", unit="mm[Hg]")
	 Double P4_Dia;
	 @Metric(loc="P4_Mean", unit="mm[Hg]")
	 Double P4_Mean;
	 @Metric(loc="PI", unit="%")
	 Double PI;
	 @Metric(loc="PVI", unit="%")
	 Double PVI;
	 @Metric(loc="SPOC", unit="ml/dl")
	 Double SPOC;
	 @Metric(loc="SPHB", unit="g/dl")
	 Double SPHB;
	 @Metric(loc="SPCO", unit="%")
	 Double SPCO;
	 @Metric(loc="SPMET", unit="%")
	 Double SPMET;

}
