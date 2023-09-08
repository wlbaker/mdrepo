package idea.datamanager.junit;

import static org.junit.Assert.assertTrue;
import icuInterface.conf.dev.SerialDeviceConfiguration;
import idea.DataGenerator;
import idea.driver.NullDevice;
import idea.model.PersistentItem;
import idea.persistmanager.PiHdf5Exporter;
import idea.persistmanager.PiHdf5Importer;

import java.io.File;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;

import hdf.hdf5lib.exceptions.HDF5LibraryException;

import org.junit.Before;
import org.junit.Test;

import idea.schema.rp.RpDevice;
import idea.schema.rp.RpSubject;

public class SeekTest {

	public String dest_name = "bard";
	private PiHdf5Exporter exporter;
	private RpDevice bard_conf;

	@Before
	public void setUp() throws Exception {
		File f = new File(TestCommon.TEST_DIR, "test_seektest.h5");
		if (f.exists()) {
			boolean ok = f.delete();
			assertTrue("COULD NOT DELETE FILE!", ok);
		}
		RpSubject session = TestCommon.getDefaultSession();
		exporter = new PiHdf5Exporter(session, f.getPath(), true);
		exporter.connect();

		bard_conf = new RpDevice();
		bard_conf.setName(dest_name);
		NullDevice urimeter = new NullDevice(bard_conf);

		try {
			DataGenerator.loadDefaultData(exporter, urimeter);  // need more than 1hr of data
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		try {
			exporter.flush();
		} catch (HDF5LibraryException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	@Test
	public void test30MinRangeByMinute() throws IOException {

		SimpleDateFormat df = new SimpleDateFormat("yyyyMMDD HH:mm:ss");
		long now = System.currentTimeMillis();

		PiHdf5Importer index = new PiHdf5Importer( //
				exporter.getHdf5FileId() );
		
		//?		now - 60 * 60 * 1000, // msStart
		//?		now - 30 * 60 * 1000, // msEnd 
		//?		60 * 1000, bard_conf);

		index.connect();
		
		int count = 0;
		for (;;) {
			PersistentItem block = index.next();
			if (block == null)
				break;

			Date dt = block.getTm();
			
			count++;
			System.out.println("[" + count + "] date= " + df.format(dt));
		}
	
		assertTrue( "Expecting 30 mins of data a 1-min intervals", count == 30 );
	}

}
