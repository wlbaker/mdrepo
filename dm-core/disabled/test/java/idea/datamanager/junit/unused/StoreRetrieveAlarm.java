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
import java.util.List;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import idea.schema.rp.RpDevice;
import idea.schema.rp.RpStream;
import idea.schema.rp.RpSubject;

public class StoreRetrieveAlarm {

	PiHdf5Exporter exporter;
	PiHdf5Importer importer;

	StreamProducer src;

	@Before
	public void setUp() throws Exception {
		File f = new File(TestCommon.TEST_DIR, "test_storeretrieve.h5");
		if (f.exists()) {
			boolean ok = f.delete();
			assertTrue("COULD NOT DELETE FILE!", ok);
		}
		RpSubject session = TestCommon.getDefaultSession();
		exporter = new PiHdf5Exporter(session, f.getPath(), true);
		exporter.connect();

		src = TestCommon.createPartialDragerDeltaDevice("name0");
		// DataGenerator.loadDefaultData(exporter, src);

		importer = new PiHdf5Importer(exporter.getHdf5FileId());
		importer.connect();
	}

	@Test
	public void testStoreAndRetrieveOneAlarm() {
		try {
			_testStoreAndRetrieveOneAlarm();
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public void _testStoreAndRetrieveOneAlarm() throws Exception {
		RpDevice conf = src.getConfiguration();
		List<RpStream> streams = conf.getStreams();
		Class dataclaz = ModelUtil.createDynamicModel("vodoo", streams.get(0).getMetric() ); 
		PersistentItem item = ModelUtil.getModelFromDataClass( dataclaz );

		// ni.setValue(5551212);

		item.setTime(99999);
		exporter.put(src, StreamID.MEASUREMENT, item);
		exporter.flush();

		int reqTime = 1017;
		importer.seek( reqTime );
		PersistentItem retrieved = importer.next();

		System.out.println("expected: " + reqTime );
		System.out.println("got: " + retrieved.getTime());


		// dump item???

		assertTrue( reqTime == retrieved.getTime() );

	}


	@After
	public void tearDown() throws Exception {
		exporter.disconnect();
		importer.disconnect();
	}

}
