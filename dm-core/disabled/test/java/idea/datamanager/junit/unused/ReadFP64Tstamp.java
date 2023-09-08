package idea.datamanager.junit.unused;

import static org.junit.Assert.assertTrue;
import idea.datamanager.junit.TestCommon;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.ModelUtil;
import idea.model.PersistentItem;
import idea.persistmanager.PiHdf5Exporter;
import idea.persistmanager.PiHdf5Importer;

import java.io.File;
import java.util.Date;
import java.util.List;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import idea.schema.rp.RpDevice;
import idea.schema.rp.RpStream;
import idea.schema.rp.RpSubject;

public class ReadFP64Tstamp {

	PiHdf5Importer importer;

	StreamProducer src;

	@Before
	public void setUp() throws Exception {
		File f = new File(TestCommon.TEST_DIR, "cf_9718d.h5");
//		if (f.exists()) {
//			boolean ok = f.delete();
//			assertTrue("COULD NOT DELETE FILE!", ok);
//		}
		importer = new PiHdf5Importer( f, true);
		importer.connect();
	}

	@Test
	public void testReadFP64ts() {
		try {
			_testReadOneRecord();
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public void _testReadOneRecord() throws Exception {
		PersistentItem item = importer.next();

		Date tm = item.getTm();
		// dump item???

		long reqTime = item.getTime();
		assertTrue( reqTime == tm.getTime() );

	}


	@After
	public void tearDown() throws Exception {
		importer.disconnect();
	}

}
