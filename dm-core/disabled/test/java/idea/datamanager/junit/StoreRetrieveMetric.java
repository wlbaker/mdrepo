package idea.datamanager.junit;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

import idea.DataGenerator;
import idea.intf.AbstractStreamProducer;
import idea.intf.StreamProducer;
import idea.model.PersistentItem;
import idea.persistmanager.PiHdf5Exporter;
import idea.persistmanager.PiHdf5Importer;

import java.io.File;
import java.io.IOException;

import hdf.hdf5lib.exceptions.HDF5LibraryException;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import idea.schema.rp.RpSubject;

public class StoreRetrieveMetric {

	private File f;
	private static int idx = 0;

	PiHdf5Exporter exporter;
	PiHdf5Importer importer;

	StreamProducer src;

	@Before
	public void setUp() throws Exception {
		f = new File(TestCommon.TEST_DIR, "test_rtrv_metric" + (++idx) + ".h5");
		if (f.exists()) {
			boolean ok = f.delete();
			assertTrue("could not delete file...not properly closed!", ok);
		}
	}

	private void createImportExportData() throws IOException, HDF5LibraryException {
		RpSubject session = TestCommon.getDefaultSession();
		exporter = new PiHdf5Exporter(session, f.getPath(), true);
		exporter.connect();

		src = TestCommon.createPartialDragerDeltaDevice("name0");
		DataGenerator.loadDefaultDataRange(exporter, src, 1000, 1, 500 );

		importer = new PiHdf5Importer(exporter.getHdf5FileId());
		importer.connect();
	}

	@Test
	public void testExporterOpenClose() throws Exception {
		RpSubject session = TestCommon.getDefaultSession();
		exporter = new PiHdf5Exporter(session, f.getPath(), true);
		exporter.connect();

		exporter.disconnect();

		importer = new PiHdf5Importer(f);
		importer.connect();

		importer.disconnect();

		boolean ok = f.delete();
		assertTrue("could not delete file...not properly closed!", ok);
	}

	@Test
	public void testImporterOpenClose() throws Exception {
		RpSubject session = TestCommon.getDefaultSession();
		exporter = new PiHdf5Exporter(session, f.getPath(), true);
		exporter.connect();

		exporter.disconnect();

		boolean ok = f.delete();

		assertTrue("Resources not closed...cannot delete!", ok);
	}

	@Test
	public void testStoreAndRetrieveOneMetric() throws Exception {
		createImportExportData();

		PersistentItem retrieved;

		// test seek first record
		importer.seek(1000);
		retrieved = importer.next();
		assertEquals("retrieving first record", 1000, retrieved.getTime());

		// test seek middle record
		importer.seek(1010);
		retrieved = importer.next();
		assertEquals("retrieving first record", 1010, retrieved.getTime());

		// test seek middle record
		importer.seek(10);
		retrieved = importer.next();
		assertEquals("before-first record", 1000, retrieved.getTime());

		// test seek after-last record
//		importer.seek(99999 + 1);
//		retrieved = importer.next();
//		assertNull("after last record", retrieved);

	}

	@After
	public void tearDown() throws Exception {
		if (importer != null) {
			importer.disconnect();
		}
		exporter.disconnect();
//		if (f.exists()) {
//			boolean ok = f.delete();
//			assertTrue("could not delete file...not properly closed!", ok);
//		}
	}

}
