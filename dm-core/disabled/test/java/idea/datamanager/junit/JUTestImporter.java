package idea.datamanager.junit;

import idea.model.PersistentItem;
import idea.persistence.PiSubjectImporter;
import idea.persistence.PiDatastreamImporter;
import idea.persistmanager.PiImporterUtil;
import idea.persistmanager.sql.SQLImporter;

import java.io.File;
import java.io.IOException;

import org.apache.log4j.Level;
import org.apache.log4j.LogManager;

import icuInterface.PlatformUtil;

public class JUTestImporter {

	public static void main(String[] args) throws IOException {

		PlatformUtil.init();
		
		LogManager.getRootLogger().setLevel((Level) Level.WARN);

		// String path = "Y:/A-14-001 MSC/Data/Data and Graphs/3054/data.db";
		// String path = "c:/tmp/data.db";
		// SQLImporter importer = new SQLImporter( "jdbc:sqlite:" + path );
		// new SQLImporter( "jdbc:sqlite:" + path );
		File path = new File("c:/tmp/0000.h5");
		PiSubjectImporter importer = PiImporterUtil.getImporterFromFile( path );
		
		importer.connect();
		
		try {
			PersistentItem n;
			do {
				n = importer.next();
				System.out.println("n=" + n);
			} while( n != null );
			
			testDevs( importer );
		} finally {

			importer.disconnect();
			System.out.println("disconnected");
		}
	}

	public static void testDevs(PiSubjectImporter importer) throws IOException {
		for( PiDatastreamImporter dev : importer.getDevices() ) {
			System.out.println("dev=" + dev);
			PersistentItem n;
			do {
				n = dev.next();
				if( n != null ) {
					System.out.println("n=" + n + " tm=" + n.getTm());
				}
			} while( n != null );

		}
		
		System.out.println("testDevs complete");
	}
}
