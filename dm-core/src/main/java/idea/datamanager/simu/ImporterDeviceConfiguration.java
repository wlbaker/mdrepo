package idea.datamanager.simu;

import java.util.LinkedList;

import idea.conf.DeviceConfiguration;

public class ImporterDeviceConfiguration extends DeviceConfiguration {

	private static final long serialVersionUID = 1L;
	// private PiSubjectImporter importer;
	
	private LinkedList<DeviceConfiguration> configs;
	private int speed;
	
	public ImporterDeviceConfiguration(Class<?> cl) {
		super(cl);
		
	}

//	public void setImporter(PiSubjectImporter importer) {
//		this.importer = importer;
//	}
//
//	public PiSubjectImporter getImporter() {
//		return importer;
//	}

	public DeviceConfiguration [] getConfigurations() {
		if( configs.size() == 0 ) {
			return null;
		}
		DeviceConfiguration[] ar = new DeviceConfiguration[configs.size()];
		configs.toArray(ar);
		return ar;
	}

	public void setSpeed(int speed ) {
		this.speed = speed;
	}

}
