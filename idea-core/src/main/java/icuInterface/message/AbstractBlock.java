/**
 * TODO: NJC: Header Documentation
 * 
 * 
 * 
 * $Date: 2011-01-12 14:16:15 -0600 (Wed, 12 Jan 2011) $
 * $Revision: 2353 $
 * $Author: bbaker $
 * $HeadURL: svn://143.83.220.223/DSS/trunk/ICUInterface/src/icuInterface/serverMessages/AbstractBlock.java $
 * $Id: AbstractBlock.java 2353 2011-01-12 20:16:15Z bbaker $
 */

package icuInterface.message;

import idea.intf.StreamProducer;

import java.util.Date;

public abstract class AbstractBlock  {

	public final static int NUMERIC_STREAM = 0;
	public final static int WAVEFORM_STREAM = 1;
	public final static int SETTINGS_STREAM = 2;
	public final static int ALARM_STREAM = 3;
	
	private StreamProducer driver;
	private long time;
	private int streamID;

	public AbstractBlock( StreamProducer driver ) {
		this.driver = driver;
	}
	
	public AbstractBlock(int streamID) {
		this.streamID = streamID;
	}

	public void setTime(long time) {
		this.time = time;
	}

	public long getTime() {
		return time;
	}

	public void setDriver(StreamProducer driver) {
		this.driver = driver;
	}

	public StreamProducer getDriver() {
		return driver;
	}

	public abstract AbstractItem[] getItems();
	public abstract AbstractItem getItem(String loc);

	@Override
	public String toString() {
		Date dt = new Date(time);
		String txt = "[" + dt + "] " + driver;
		AbstractItem[] items = getItems();
		if( items != null ) {
			for( AbstractItem item : items ) {
				txt += "*" + item.toString();
			}
		}
		return txt;
	}

	public void setStreamID(int id) {
		this.streamID = id;
	}

	public int getStreamID() {
		return streamID;
	}
	
	
}
