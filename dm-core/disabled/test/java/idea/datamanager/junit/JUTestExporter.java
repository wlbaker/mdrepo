package idea.datamanager.junit;

import icuInterface.PlatformUtil;
import idea.conf.DeviceFactory;
import idea.intf.StreamProducer;
import idea.persistence.PiSubjectExporter;
import idea.persistmanager.PiHdf5Exporter;
import hdf.hdf5lib.exceptions.HDF5LibraryException;

import java.io.File;
import java.io.IOException;

import idea.schema.rp.RpDevice;
import idea.schema.rp.RpSubject;

public class JUTestExporter {

	public static void main(String[] args) throws IOException, HDF5LibraryException {
		
		PlatformUtil.init();
		System.loadLibrary("hdf5");
		System.loadLibrary("hdf5_java");

		File f = new File(TestCommon.TEST_DIR, "testfile1.h5");
		
		if( f.exists() ) {
			f.delete();
		}
		
		RpSubject subject = new RpSubject();
		subject.setIdentifier("JOHNDOE");
		subject.setSubject("SUBJECT0");

		StreamProducer producer = TestCommon.createPartialDragerDeltaDevice("partialDrager");
		
		// JpaUtil.initHibernateLogging();
		// PiSubjectExporter exporter = new SQLExporter( subject, null );
		PiSubjectExporter exporter = new PiHdf5Exporter( subject, f.getPath(), true );
		
		exporter.connect();
		exporter.addDevice( producer.getConfiguration() );

		TestUtil.generateDragerData( producer, exporter );
		
		exporter.disconnect();
	}

}
