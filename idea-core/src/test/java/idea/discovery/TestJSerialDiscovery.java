package idea.discovery;

import static org.junit.Assert.*;

import java.io.File;
import java.io.IOException;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import icuInterface.discovery.DeviceRecord;
import icuInterface.discovery.DiscoveryAction;
import icuInterface.discovery.DiscoveryListener;
import icuInterface.discovery.JSerialCommDiscoveryWorker;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpHardware;
import idea.schema.rp.RpStudy;

public class TestJSerialDiscovery implements DiscoveryListener {
	JSerialCommDiscoveryWorker worker;
	
	@Before
	public void setUp() throws Exception {

		// 
		RpStudy study = Util.createStudyFromFile( new File("/opt/bernard/study.xml") );
		if( study == null ) {
			System.err.println("study file not found");
			return;
		}
		RpHardware hw = study.getHardware().get(0);
		
		
		TestProbeData.init(study);
		String [] ports = { "/dev/ttyUSB0", "/dev/ttyUSB1", "/dev/ttyUSB2", "/dev/ttyUSB3" };
		
		worker = new JSerialCommDiscoveryWorker();
		worker.setPorts( ports );
		
		for( RpDevice dev : hw.getDevices() ) {
			worker.addDevice(dev);
		}
	}

	@After
	public void tearDown() throws Exception {
	}

	@Test
	public void test() {
		
		if( worker == null ) {
			return;
		}
		for( int i = 0; i < 10; i++ ) {
//			try {
//				worker.tick_probes();
//			} catch (IOException e1) {
//				e1.printStackTrace();
//				fail( e1.getMessage() );
//			}
			worker.tick();
			try {
				Thread.sleep(1000);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		
		assertTrue( true );
		// fail("Not yet implemented");
	}

	@Override
	public void discover(DiscoveryAction action, DeviceRecord dev) {
		// TODO Auto-generated method stub
		System.out.println("discover: " + dev + "=" + action );
	}

	@Override
	public void error(DeviceRecord dev, String message, Exception x) {
		// TODO Auto-generated method stub
		System.out.println("error: " + dev + "=" + message );
		
	}

}
