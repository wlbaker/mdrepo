package idea.datamanager.junit;

import static org.junit.Assert.assertTrue;
import icuInterface.conf.dev.SerialDeviceConfiguration;
import idea.driver.NullDevice;
import idea.persistmanager.PiHdf5Exporter;

import java.io.File;
import java.io.IOException;

import hdf.hdf5lib.exceptions.HDF5LibraryException;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import idea.schema.rp.RpDevice;
import idea.schema.rp.RpSubject;

public class RemoveDataset {

	PiHdf5Exporter exporter;
	
	@Before
	public void setUp() throws Exception {
		File f = new File(TestCommon.TEST_DIR, "test_remove.h5");
		if (f.exists()) {
			boolean ok = f.delete();
			assertTrue("COULD NOT DELETE FILE!", ok);
		}
		RpSubject session = TestCommon.getDefaultSession();
		exporter = new PiHdf5Exporter(session, f.getPath(), true);
		exporter.connect();
	}

	@After
	public void tearDown() throws Exception {
		exporter.disconnect();
	}

	@Test
	public void create_file_delete() throws IOException, HDF5LibraryException {
		RpDevice conf = new RpDevice();
		conf.setName("bard");
		NullDevice urimeter = new NullDevice(conf);
		exporter.addDevice( conf );
		
		TestUtil.generateBISData(urimeter, exporter);

		((PiHdf5Exporter)exporter).remove("bard");
		
	}
}
