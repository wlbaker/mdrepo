package idea.model.dev;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.persistence.Text;
import idea.schema.rp.RpMetric;

import jakarta.persistence.Entity;
import jakarta.persistence.Table;

import lombok.Data;
import lombok.EqualsAndHashCode;

/*
 * CYCLE modes:
Number	Mode
0	Power Up
1	Parameter Update
2	Service
3	Calibration
4	Startup
5	Prime
6	Alarm Tests
7	Recirculate
8	Patient Connect
9	Treatment
10	Arterial Disconnect
11	Rinse back
12	DBG Password
13	Post-Rinse back
 */

/*
 * Pureflow SL modes:
 * 
 * Number	Mode
1	(future use)
2	Startup
3	Power Failure Recovery
4	Remote Software Update
5	User Settings
6	User Maintenance
7	NxStage Service
8	Standby
9	Replace/Prime PAK
10	(future use)
11	Make Batch (includes SAK Prime & Alarm Test)
12	Hold Batch
13	Use Batch
14	Drain SAK
15	Unload SAK
16	(future use)
17	Debug Password
18	Load SAK
19	Delayed Start
20	Product Water Test
21	Condo Sensor Preventative Maintenance
22	Activation
23	Condo Check

 */


/*
 * Volume Units
Number	Units
0	Milliliter (ml)
1	Liter (L)
 */

@Entity
@Table(name = "NXSTAGE")
@Data
@EqualsAndHashCode(callSuper = false)
public class NxStageMeasurement extends PersistentItem {

	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.getMetrics(NxStageMeasurement.class);
	}

	public NxStageMeasurement() {
		super(StreamID.MEASUREMENT);

	}

	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}

	// Version	The version of the message.	Integer	1
	// CYC_Serial_Number	The cycler�s serial number.	Integer	0-999,999
	@Metric(loc = "cyc_serNo", code = "CYC_Serial_Number", unit = "")
	private Integer cyc_serNo;
	// Provider	The provider ID. The value of 1 is reserved for a test provider.	Integer	0 = N/A
	@Metric(loc = "provider", code = "Provider", unit = "")
	private Integer provider;
	// Facility	The facility ID. The value of 1 is reserved for a test facility.	Integer	0 = N/A 
	@Metric(loc = "facility", code = "Facility", unit = "")
	private Integer facility;
	// Patient	The patient ID. The ID values from 1-1000 are reserved for test patients.	Integer	0 = N/A
	@Metric(loc = "patientNo", code = "PatientNo", unit = "")
	private Integer patientNo;
	// Patient	The patient ID. Ascii	string	ascii
	@Text(loc = "patientID", code = "PatientID", unit = "")
	private Integer patientID;
	// CYC_TFV	Therapy fluid volume	Integer	
	@Metric(loc = "tfv", code = "CYC_TFV", unit = "ml")
	private Integer tfv;
	// CYC_TFR	Therapy fluid rate	Float	>= 0.0
	@Metric(loc = "tfr", code = "CYC_TFR", unit = "ml/min", precision=2)
	private Integer tfR;
	// CYC_BFR	Blood flow rate	Integer	
	@Metric(loc = "bfr", code = "CYC_BFR", unit = "ml/min")
	private Integer bfr;
	// CYC_UFV	Ultrafiltration volume	Integer	
	@Metric(loc = "tfv", code = "CYC_UFV", unit = "ml")
	private Integer ufv;
	// CYC_UFR	Ultrafiltration rate	Float	>= 0.0
	@Metric(loc = "ufr", code = "CYC_UFR", unit = "ml/min", precision=2)
	private Integer ufr;
	// CYC_AP	Filtered Arterial pressure	Integer	
	@Metric(loc = "ap", code = "CYC_AP", unit = "mmHg")
	private Integer ap;
	// CYC_VP	Filtered Venous Pressure	Integer	
	@Metric(loc = "vp", code = "CYC_VP", unit = "mmHg")
	private Integer vp;
	// CYC_EP	Filtered Effluent Pressure	Integer	
	@Metric(loc = "ep", code = "CYC_EP", unit = "mmHg")
	private Integer ep;
	// CYC_ALARM	The current alarm number. If there is no alarm then this value will be -1.	Integer	0-999
	@Metric(loc = "alarm", code = "CYC_ALARM", unit = "")
	private Integer alarm;
	// CYC_CAUTION	The current caution code. If there is no caution then this value will be -1. This value is valid when the CYC_Alarm value is  1.	Integer	0-999
	@Metric(loc = "caution", code = "CYC_CAUTION", unit = "")
	private Integer caution;
	// CYC_MODE	The current mode of the cycler.	Integer	See Table 2.
	@Metric(loc = "mode", code = "CYC_MODE", unit = "")
	private Integer mode;

	// CYC_ET	The amount of time spent in the current treatment.	Integer	0-32768
	@Metric(loc = "et", code = "CYC_ET", unit = "min")
	private Integer et;
	// CYC_TR	The amount of time remaining in the current treatment.	Integer	0-32768
	@Metric(loc = "tr", code = "CYC_TR", unit = "min")
	private Integer tr;
	// CYC_TIA	The amount of time that the cycler has been displaying the current alarm or caution.	Integer	0-32767
	@Metric(loc = "tia", code = "CYC_TIA", unit = "sec")
	private Integer tia;
	// PFSL_Serial_Number	The PFSL�s serial number. If this field is missing then the PFSL is not in use.	Integer	0-999,999
	@Metric(loc = "pfsl_serNo", code = "PFSL_Serial_Number", unit = "")
	private Integer pfsl_serNo;
	// PFSL_Mode	The current mode of the PureFlow SL.	Integer	See Table 3
	@Metric(loc = "pfsl_mode", code = "PFSL_Mode", unit = "")
	private Integer pfsl_mode;

	// CYC_TFV_SUMMARY	Therapy fluid volume used during the summary period	Float	>= 0.00
	// CYC_TFR_DISPLAY	Current Therapy fluid rate displayed on the Cycler	Float	>= 0.0
	// CYC_UFV_SUMMARY	Ultrafiltration volume used during the summary period	Float	>= 0 or	>= 0.00
	@Metric(loc = "ufv_summary", code = "CYC_UFV_SUMMARY", unit = "ml")
	private Integer ufv_summary;
	// CYC_UFR_DISPLAY	Current Ultrafiltration rate displayed on the Cycler	Float	>= 0 or	>= 0.00
	// CYC_UFR_DISPLAY_UNITS	The units for the CYC_UFV_DISPLAY field	Integer	See Table 4

	// CYC_SUMMARY_START	The seconds since Unix Epoch at the beginning of the summary time period	Integer	0 = N/A 

	// CYC_SUMMARY_END	The seconds since Unix Epoch at the end of the summary time period	Integer	0 = N/A 

	// CYC_TIMESTAMP	The current time in seconds since Unix Epoch	Integer	0 = N/A

}
