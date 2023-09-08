package idea.driver;

import java.io.IOException;

import icuInterface.conf.dev.SocketDeviceConfiguration;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.schema.rp.RpMetric;

public class TestInfinity implements StreamConsumer {

	public static void main(String[] args) throws IOException, InterruptedException {
		System.setProperty("devicelog_dir", "/tmp");
		// System.setProperty("devicelog_file", "infinity.dump");


		TestInfinity inst = new TestInfinity();
		SocketDeviceConfiguration conf = InfinityDriver.createConfigInstance();
		conf.setHost("191.1.1.3");
		conf.setConnectionValue("infinity://224.0.1.3/191.1.1.3");

		InfinityDriver driver = new InfinityDriver(conf);
		
		// I'm only interested in the VITALS type measurements
		driver.addStreamListener(StreamID.MEASUREMENT, inst );
		driver.connect();
		
		Thread.sleep(60* 1000 * 5);
		
		driver.disconnect();
	}

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {
		System.out.println("message: " + item);
		
		Double hr = null;
		String loc = "ecg.hr";
		// method #1 to get value
		RpMetric hr_metric = IntfUtil.getMetricByLoc(item, loc );
		if( hr_metric == null ) {
			// if the ECG heart rate was not found, try the SPO2 pulse rate
			loc = "spo2.pls";
			hr_metric = IntfUtil.getMetricByLoc(item, loc );
		}
		if( hr_metric == null ) {
			// one can also query the HR from the arterial line
			loc = "art.hr";
			hr_metric = IntfUtil.getMetricByLoc(item, loc );
		}
		
		if( hr_metric != null ) {
			hr = (Double)IntfUtil.getScaledValue(item, hr_metric);
		}
		
		System.out.println("hr=" + hr);
		
	}

}
