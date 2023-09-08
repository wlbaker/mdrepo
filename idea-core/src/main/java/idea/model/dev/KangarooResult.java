package idea.model.dev;

import idea.intf.AdapterInterface;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.persistence.Text;
import idea.schema.rp.RpMetric;

import javax.persistence.Entity;
import javax.persistence.Table;

import lombok.Data;
import lombok.EqualsAndHashCode;

// status flags
//0, 0x0001, Running, Pump is in Running Mode (Running Screen is displayed), Pump is NOT in Runni
//*1, 0x0002, Bolus Mode, Bolus Mode selected, Continuous Mode selected
//2, 0x0004, Bolus Break Time, Waiting for Next Bolus to start, NOT Waiting for Next Bolus to start
//3, 0x0008, Super Bolus, Super Bolus selected, Super Bolus NOT selected
//4, 0x0010, Feeding Complete, VTBD is nonzero AND required VTBD has been reached, VTBD is 0 OR required VTBD has NOT been reached.
//5, 0x0020, Auto Resume or KTO, Auto Resume or KTO is set, Both Auto Resume and KTO are not set
//6, 0x0040, Feed Set loaded, Feed Only set loaded, Other or No Set loaded
//7, 0x0080, Flush Set loaded, Feed/Flush set loaded, Other or No Set loaded
//**8, 0x0100, Totalizers Cleared, User pressed *Clear Volume* button since last message sent by KANGAROO ePump.
//User powered up or message was sent by KANGAROO ePump more recently than *Clear Volume* pressed.
//9, 0x0200, Power Source, AC Power available, Battery Power only
//10, 0x0400, Battery Charging, Battery is currently charging, Battery is NOT being charged
//11, 0x0800, EZ Mode, EZ-ePump mode is set, Normal Mode
//12, 0x1000, Settings Locked, Settings are Locked, Settings are NOT Locked
//13, 0x2000, Screen Locked, Run Mode Screen Lock function Enabled, Run Mode Screen Lock function Disabled
//14, 0x4000, Controlled Report Mode, Controlled Reporting Mode, Default Reporting Mode
//15, 0x8000, Power Down, Unit is Powering Down, Unit is not in a Powering Down State

@Entity
@Table(name = "Kangaroo")

@Data
@EqualsAndHashCode(callSuper=false)
public class KangarooResult extends PersistentItem {

	public final static String SER_NO = "01";
	public final static String PUMP_FW = "02";
	public final static String PUMP_STATUS = "03";
	public final static String FLUSH_TOTAL = "04";
	public final static String FLUSH_VTBD = "05";
	public final static String FLUSH_IVL = "06";
	public final static String FEED_TOTAL = "07";
	public final static String FEED_RATE = "08";
	public final static String FEED_VTBD = "09";
	public final static String FEED_REMAIN = "10";
	public final static String BOLUS_IVL = "10a";
	public final static String NUM_BOLUS = "11";

	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.getMetrics(KangarooResult.class);
	}

	public KangarooResult(AdapterInterface driver) {
		super(StreamID.MEASUREMENT);
	}

	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}

	@Text(loc = SER_NO, code = "nnnnnnnn", desc = "Serial Number", length = 8)
	private  String serNo;

	@Metric(loc = PUMP_STATUS, code = "ssss", desc = "Status Field", unit = "ml")
	private Integer pumpStatus;

	@Metric(loc = PUMP_FW, code = "????????", desc = "Firmware Version")
	private  Integer fwVer;

	@Metric(loc = FLUSH_TOTAL, code = "aaaaaaaa", desc = "Flush Totalizer", unit = "ml")
	private  Integer flushTotal;
	@Metric(loc = FLUSH_VTBD, code = "bbbb", desc = "Flush VTBD", unit = "ml")
	private  Integer flushVTBD;
	@Metric(loc = FLUSH_IVL, code = "cccc", desc = "Flush Interval", unit = "hr")
	private  Integer flushIVL;
	@Metric(loc = FEED_TOTAL, code = "dddddddd", desc = "Feed/Bolus Totalizer", unit = "ml")
	private  Integer feedTotal;
	@Metric(loc = FEED_RATE, code = "eeee", desc = "Feed/Bolus Rate", unit = "ml/hr")
	private  Integer feedRate;
	@Metric(loc = FEED_VTBD, code = "ffff", desc = "Feed/Bolus VTBD", unit = "ml")
	private  Integer feedVTBD;
	@Metric(loc = FEED_REMAIN, code = "gggg", desc = "Feed VTBD remaining", unit = "ml")
	private  Integer feedRemaining;
	@Metric(loc = BOLUS_IVL, code = "bIvl", desc = "Bolus Interval", unit = "hr")
	private  Integer bolusIVL;
	@Metric(loc = NUM_BOLUS, code = "hhhh", desc = "Number of Boluses")
	private  Integer numBolus;
	

}
