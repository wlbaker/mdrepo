package idea.datamanager.junit;

import idea.driver.NullDevice;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.dev.BISMeasurement;
import idea.model.dev.DragerDelta_Measurements;
import idea.model.dev.DragerDelta_MibBIS;
import idea.model.dev.DragerDelta_Sensors;
import idea.persistmanager.PiHdf5Exporter;

public class TestUtil {

	public static void generateDragerData(StreamProducer producer, StreamConsumer exporter) {
		DragerDelta_Measurements m = new DragerDelta_Measurements();
		
		m.setArt$sys(100);
		m.setArt$dia(40);
		m.setArt$mean(70);
		
		//exporter.streamEvent( 0, producer, StreamID.MEASUREMENT, m);
		
		DragerDelta_MibBIS bis = new DragerDelta_MibBIS();
		bis.setBis(99);
		bis.setPower(1);
		bis.setDeviceLoc("L86-14");
		
		m.setOid(0);
		m.setArt$sys(110);
		m.setArt$dia(45);
		m.setArt$mean(75);
		m.setBis(bis);
		
		//exporter.streamEvent( 0, producer, StreamID.MEASUREMENT, m);
		
		DragerDelta_Sensors sens = new DragerDelta_Sensors();
		int[] art = sens.getArt();
		if( art == null ) {
			art = new int[20];
			sens.setArt(art);
		}
		for( int i = 0; i < art.length; i++) {
			art[i] = i;
		}
		
		exporter.streamEvent( 0, producer, StreamID.WAVEFORM, sens);
	}

	public static void generateBISData(NullDevice d, PiHdf5Exporter exporter) {
		BISMeasurement bis = new BISMeasurement();
		bis.setOid(0);
		bis.setBIS(110);
		bis.setBurstRate(45);
		bis.setSQI(123);
		
		exporter.streamEvent( 0, d, StreamID.MEASUREMENT, bis);
	}

}
