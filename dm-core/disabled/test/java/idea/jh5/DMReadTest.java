package idea.jh5;

import java.io.File;
import java.io.IOException;

import org.apache.log4j.BasicConfigurator;
import org.apache.log4j.Level;
import org.apache.log4j.LogManager;

import hdf.hdf5lib.exceptions.HDF5Exception;
import icuInterface.PlatformUtil;
import idea.persistence.PiDatastreamImporter;
import idea.persistence.PiSubjectImporter;
import idea.persistmanager.PiImporterUtil;

public class DMReadTest {
	private static void getHeaderAndNotes(File f, String string) throws IOException {
		PiSubjectImporter importer = PiImporterUtil.getImporterFromFile( f );
		importer.connect();
		PiDatastreamImporter[] devs = importer.getDevices();
		for( PiDatastreamImporter dev : devs ) {
			String name = dev.getName();
			System.out.println("found group: " + name );
		}
		importer.disconnect();
	}
	
	public static void main( String [] args ) throws NullPointerException, IOException, HDF5Exception {
		BasicConfigurator.configure();
		// LogManager.getRootLogger().setLevel((Level) Level.WARN);

		PlatformUtil.init();
		PlatformUtil.loadLibrary("hdf5");
		PlatformUtil.loadLibrary("hdf5_java");
		
		// File f = new File("Z:/00-PROTOCOLS/A-16-004 RECAP/RECAP idea/Jun062017_9683/9683/2017_06_06_08.49.11/0000.h5");
		File f = new File("c:/tmp/0000.h5");
				
		if( !f.exists() ) {
			System.err.println("Cannot find file to test: " + f );
			return;
		}
		getHeaderAndNotes( f, "/Drager_1/numerics");
	}


}
