package idea.discovery;

import static org.junit.Assert.*;

import java.io.IOException;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.pistax.PistaAdapter;

import icuInterface.discovery.DeviceRecord;
import icuInterface.discovery.DiscoveryAction;
import icuInterface.discovery.DiscoveryListener;
import icuInterface.discovery.JSerialCommDiscoveryWorker;
import idea.driver.NullStreamProducer;
import idea.driver.SimuSineStreamProducer;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpHardware;
import idea.schema.rp.RpStudy;

public class TestPistaDiscovery implements DiscoveryListener {
	JSerialCommDiscoveryWorker worker;
	
	@Before
	public void setUp() throws Exception {

		// LocalJAXBRepository.createStudyFromFile("/opt/bernard/study.xml");
		RpStudy study = new RpStudy();
		RpHardware hw = new RpHardware();
		
		
		
		RpDevice dev = new RpDevice();
		dev.setDeviceClass( SimuSineStreamProducer.class.getCanonicalName() );
		hw.getDevices().add( dev );
		
		dev = new RpDevice();
		dev.setDeviceClass( NullStreamProducer.class.getCanonicalName() );
		hw.getDevices().add( dev );
		
		dev = new RpDevice();
		dev.setDeviceClass( PistaAdapter.class.getCanonicalName() );
		hw.getDevices().add( dev );
		
		study.getHardware().add( hw );
		
		System.err.println("Removed ProbeData.init(study)...so how do I tell PISTA about the drivers?");
		String [] ports = { "/dev/ttyUSB0", "/dev/ttyUSB1", "/dev/ttyUSB2", "/dev/ttyUSB3" };
		
		worker = new JSerialCommDiscoveryWorker();
		worker.setPorts( ports );
	}

	@After
	public void tearDown() throws Exception {
	}

	@Test
	public void test() {
		
		for( int i = 0; i < 10; i++ ) {
			try {
				worker.tick_probes();
			} catch (IOException e1) {
				// TODO Auto-generated catch block
				fail( e1.getMessage() );
			}
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
