/**
 * TODO: NJC: Header Documentation
 * 
 * 
 * 
 * $Date: 2009-11-30 08:19:40 -0600 (Mon, 30 Nov 2009) $
 * $Revision: 640 $
 * $Author: bbaker $
 * $HeadURL: svn://143.83.220.223/DSS/trunk/ICUInterface/src/icuInterface/serverMessages/JobRequest.java $
 * $Id: JobRequest.java 640 2009-11-30 14:19:40Z bbaker $
 */

package icuInterface.message;

@Deprecated
public class DeviceReply {

	DeviceInfo [] devices;
	
	public DeviceReply(DeviceInfo[] devices) {
		this.devices = devices;
	}

}
