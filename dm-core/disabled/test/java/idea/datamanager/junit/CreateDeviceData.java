package idea.datamanager.junit;

import static org.junit.Assert.*;
import idea.conf.DeviceConfiguration;
import idea.driver.NullDevice;
import idea.intf.DataTyp;
import idea.message.StreamID;
import idea.persistence.StudyDefinition;
import idea.persistmanager.PiHdf5Exporter;
import idea.schema.rp.RpLinearUnit;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpSubject;

import java.io.File;
import java.io.IOException;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;


public class CreateDeviceData {

	private PiHdf5Exporter exporter;

	@Before
	public void setUp() throws Exception {
		TestCommon.TEST_DIR.mkdirs();
		
		File f = new File(TestCommon.TEST_DIR, "test_createdev.h5");
		if (f.exists()) {
			boolean ok = f.delete();
			assertTrue("COULD NOT DELETE FILE!", ok);
		}
		RpSubject session = TestCommon.getDefaultSession();
		exporter = new PiHdf5Exporter(session, f.getPath(), true);
		exporter.connect();

	}

	@Test
	public void testCreateDeviceApriori() throws IOException {

		 DeviceConfiguration conf = NullDevice.createConfigInstance();
		conf.setName("apriori");
//		conf.addMetric( new RpMetric("loc1","code1","desc1", RpLinearUnit.unit, DataTyp.INT_TYP));
//		conf.addMetric( new RpMetric("loc2","code2","desc2", RpLinearUnit.unit, DataTyp.INT_TYP));
//		conf.addMetric( new RpMetric("loc3","code3","desc3", RpLinearUnit.unit, DataTyp.INT_TYP));
		
		NullDevice driver = new NullDevice(conf);
		
		exporter.addDevice(driver.getConfiguration());
		
		fail("UPGRADE FROM NUMERIC BLOCK");
//		NumericBlock block = new NumericBlock(driver, conf.getMetrics());
//		NumericItem item1 = (NumericItem) block.getItem("loc1");
//		NumericItem item2 = (NumericItem) block.getItem("loc2");
//		NumericItem item3 = (NumericItem) block.getItem("loc3");
//		for( int i=0; i < 10; i++ ) {
//			block.setTime( System.currentTimeMillis() + i * 1000 );
//			item1.setValue( i );
//			item2.setValue( i*10 );
//			item3.setValue( i*100 );
//			exporter.signalEvent(0, driver, StreamID.MEASUREMENT, block);
//		}
	}

	@Test
	public void testCreateDevicePosthoc() {
		DeviceConfiguration conf = NullDevice.createConfigInstance();
		conf.setName("posthoc");
//		conf.addMetric( new MetricDescription("loc1","code1","desc1", ""));
//		conf.addMetric( new MetricDescription("loc2","code2","desc2", ""));
//		conf.addMetric( new MetricDescription("loc3","code3","desc3", ""));
		
		NullDevice driver = new NullDevice(conf);
		
		fail("UPGRADE FROM NUMERIC BLOCK");
//		NumericBlock block = new NumericBlock(driver, conf.getMetrics());
//		NumericItem item1= (NumericItem) block.add( new MetricDescription("loc1","code1","desc1", "mm"));
//		NumericItem item2= (NumericItem) block.add( new MetricDescription("loc2","code2","desc2", "cm"));
//		NumericItem item3= (NumericItem) block.add( new MetricDescription("loc2","code2","desc2", "dm"));
//		for( int i=0; i < 5; i++ ) {
//			block.setTime( System.currentTimeMillis() + i * 1000 );
//			item1.setValue( i );
//			item2.setValue( i*10 );
//			item3.setValue( i*100 );
//			exporter.streamEvent( 0, driver, StreamID.MEASUREMENT, block);
//		}
	}
	
	@After
	public void tearDown() throws Exception {
		exporter.disconnect();
	}

}
