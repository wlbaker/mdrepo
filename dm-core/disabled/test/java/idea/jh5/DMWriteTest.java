package idea.jh5;

import java.io.File;
import java.io.IOException;

import org.apache.log4j.BasicConfigurator;
import org.apache.log4j.Level;
import org.apache.log4j.LogManager;

import hdf.hdf5lib.exceptions.HDF5Exception;
import icuInterface.PlatformUtil;
import idea.persistence.PiDatastreamImporter;
import idea.persistence.PiSubjectExporter;
import idea.persistence.PiSubjectImporter;
import idea.persistmanager.PiHdf5Exporter;
import idea.persistmanager.PiImporterUtil;
import idea.schema.rp.RpSubject;

public class DMWriteTest {
	private static void writeHeaderAndNotes(File f ) throws IOException {
		
		RpSubject subject = new RpSubject();
		subject.setCompany("idea");
		subject.setMedicalId("9999");
		subject.setOperator("wlb");
		PiSubjectExporter exporter = new PiHdf5Exporter(subject, f.getPath(), true);
		exporter.connect();
		// exporter.streamEvent(0, source, sid, item);
		exporter.disconnect();
	}
	
	public static void main( String [] args ) throws NullPointerException, IOException, HDF5Exception {
		BasicConfigurator.configure();
		// LogManager.getRootLogger().setLevel((Level) Level.WARN);

		PlatformUtil.init();
		PlatformUtil.loadLibrary("hdf5");
		PlatformUtil.loadLibrary("hdf5_java");
		
		// File f = new File("Z:/00-PROTOCOLS/A-16-004 RECAP/RECAP idea/Jun062017_9683/9683/2017_06_06_08.49.11/0000.h5");
		File f = new File("c:/tmp/9999.h5");
				
		if( !f.exists() ) {
			f.delete();
		}
		writeHeaderAndNotes( f );
	}


}
