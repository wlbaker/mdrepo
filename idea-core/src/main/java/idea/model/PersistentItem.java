package idea.model;

// Generated May 17, 2007 10:53:35 AM by Hibernate Tools 3.2.0.b9

import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.schema.rp.RpMetric;

import java.util.Date;

import jakarta.persistence.Column;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;
import jakarta.persistence.MappedSuperclass;
import jakarta.persistence.Transient;

/**
 * FIXME: This item should not derive from EventObject after integration with crimea complete.
 */
@MappedSuperclass
public abstract class PersistentItem {

	@Id
	@GeneratedValue(strategy = GenerationType.IDENTITY)
	@Column(name = "OID", unique = true, nullable = false)
	private long oid;

	@Column(name = "TM")
	private Date tm;
	
	@Column(name = "DEV_LOC", nullable = true, length = 16)
	private String deviceLoc; // room
	@Column(name = "TALLY_OID", nullable = true)
	private long tallyOID; // patient

	@Transient
	private int streamID;
	@Transient
	private StreamProducer source;

	public PersistentItem( ) {
		this(StreamID.MEASUREMENT);
	}
	
	public PersistentItem( StreamID sid) {
		this.streamID = sid.getCode();
		this.setTm( new Date() );  // default to current date/time
	}
	
	@Deprecated
	public PersistentItem(StreamProducer driver, int streamID) {
		this.streamID = streamID;
		this.setTm( new Date() );  // default to current date/time
	}

	abstract public RpMetric[] getMetrics() ;
	
	public RpMetric getMetricFromCode(String code) {
		RpMetric[] metrics = getMetrics();
		if( metrics == null || metrics.length == 0 ) {
			return null;
		}
		RpMetric m = null;
		for(RpMetric d : metrics ) {
			if( code.equals( d.getCode()) ) {
				m = d;
				break;
			}
		}
		
		return m;
	}

	public RpMetric getMetric(String loc) {
		RpMetric[] metrics = getMetrics();
		if( metrics == null || metrics.length == 0 ) {
			return null;
		}
		RpMetric m = null;
		for(RpMetric d : metrics ) {
			if( loc.equals( d.getLocation())) {
				m = d;
				break;
			}
		}
		
		return m;
	}


	@Deprecated
	public void setDriver( StreamProducer driver ) {
		// this.driver = driver;
	}

	public void setStreamID( int sid ) {
		this.streamID = sid;
	}
	
	public int getStreamID( ) {
		return streamID;
	}


	// public PersistanceItemBase(AdapterInterface driver, MetricDescription[] metrics) {
	// super(driver,metrics);
	// }

	public long getOid() {
		return this.oid;
	}

	public void setOid(long oid) {
		this.oid = oid;
	}

	public Date getTm() {
		return this.tm;
	}

	public void setTm(Date tm) {
		this.tm = tm;
	}

	public long getTallyOID() {
		return this.tallyOID;
	}

	public void setTallyOID(long tallyOID) {
		this.tallyOID = tallyOID;
	}

	public String getDeviceLoc() {
		return this.deviceLoc;
	}

	public void setDeviceLoc(String deviceLoc) {
		this.deviceLoc = deviceLoc;
	}

	public Object getScaledValue(String loc){
	
		RpMetric metric = getMetric(loc);
		return IntfUtil.getScaledValue( this, metric);
	}

	@Deprecated
	public long getTime() {
		return tm.getTime();
	}

	public void setTime(long millis) {
		if( tm == null ) {
			tm = new Date(millis);
		} else {
			tm.setTime(millis);
		}
		
	}

	/*
	 * Get the transient value identifying the data source.  
	 * This value is not persisted and is not guaranteed to be non-null except on data reads from H5 files.  
	 */
	public StreamProducer getSource() {
		return source;
	}
	public void setSource(StreamProducer source) {
		this.source = source;
	}

}
