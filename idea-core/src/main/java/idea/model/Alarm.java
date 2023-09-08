/**
 * TODO: NJC: Header Documentation
 * 
 * 
 * 
 * $Date: 2009-12-03 16:04:31 -0600 (Thu, 03 Dec 2009) $
 * $Revision: 679 $
 * $Author: bbaker $
 * $HeadURL: svn://143.83.220.223/DSS/trunk/ICUInterface/src/icuInterface/serverMessages/NumericsItem.java $
 * $Id: NumericsItem.java 679 2009-12-03 22:04:31Z bbaker $
 */

package idea.model;

import idea.message.StreamID;
import idea.persistence.Metric;
import idea.persistence.Text;
import idea.schema.rp.RpMetric;
import lombok.Data;

@Data
public class Alarm extends PersistentItem {

	public static final int FATAL = 100;
	public static final int CLEAR = 0;
	public static final int INFO = 1;
	public static final int DEV_GENERIC = 20;
	public static final int WARNING = 10;

	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.getMetrics( Alarm.class );
	}
	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}

	/** Default Constructor 
	 * @param active */
	public Alarm() {
		super(StreamID.ALARM);
	}
	
	public Alarm(String devParam, int severity, int devCode, String message, boolean active) {
		super(StreamID.ALARM);
		this.setSeverity( (byte)severity);
		this.setCode( devCode );
		this.setMessage( message );
		this.setActive(active);
		this.setDevParam( devParam );
	}



	@Metric(loc = "code", code = "code", desc = "Device Code")  // DataTyp.BYTE_TYP
	private int code;

	@Metric(loc = "active", code = "active", desc = "Active")  // DataTyp.BYTE_TYP 
	private boolean active;
	
	@Metric(loc = "severity", code = "severity", desc = "Severity")
	private int severity;

	@Text(loc = "message", code = "message", length=128)
	private String message;
	@Text(loc = "param", code = "param", length=16)
	private String devParam;


}
