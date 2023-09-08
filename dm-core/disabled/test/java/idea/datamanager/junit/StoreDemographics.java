package idea.datamanager.junit;

import static org.junit.Assert.*;
import idea.conf.DeviceConfiguration;
import idea.driver.NullDevice;
import idea.message.StreamID;
import idea.persistmanager.PiHdf5Exporter;
import junit.framework.AssertionFailedError;

import java.io.File;
import java.io.IOException;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import idea.schema.rp.RpDevice;
import idea.schema.rp.RpSubject;

public class StoreDemographics {

	private PiHdf5Exporter exporter;
	private static int idx = 0;

	@Before
	public void setUp() throws Exception {
		File f = new File(TestCommon.TEST_DIR, "test_demographics_" + (++idx) + ".h5");
		if (f.exists()) {
			boolean ok = f.delete();
			assertTrue("COULD NOT DELETE FILE!", ok);
		}
		RpSubject session = TestCommon.getDefaultSession();
		exporter = new PiHdf5Exporter(session, f.getPath(), true);
		exporter.connect();

	}

	@Test
	public void testAddDemographics() throws IOException {

		RpDevice conf = NullDevice.createConfigInstance();
		conf.setName("demographic_producer");
		
		NullDevice driver = new NullDevice(conf);
		
		exporter.addDevice(driver.getConfiguration());
		
		fail("UPGRADE FROM NUMERIC BLOCK");
//		for( int i=0; i < 3; i++ ) {
//			block.setTime( System.currentTimeMillis() + i * 1000 );
//			item1.setValue( i );
//			item2.setValue( "bonnie" );
//			exporter.signalEvent( 0, driver, StreamID.DDDEMOGRAPHICS, block);
//		}
	}

	@After
	public void tearDown() throws Exception {
		exporter.disconnect();
	}

}
