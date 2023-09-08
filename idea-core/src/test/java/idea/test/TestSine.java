package idea.test;

import java.util.List;

import idea.conf.DeviceConfiguration;
import idea.driver.SimuSineStreamProducer;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.PersistentItem;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpStream;

public class TestSine implements StreamConsumer {

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {
		System.out.println( sid + ": " + item );
		
	}

	public static void main(String[] args) {
		TestSine t = new TestSine();

		DeviceConfiguration conf = SimuSineStreamProducer.createConfigInstance();
		
		for( RpStream stream : (List<? extends RpStream>)conf.getStreams() ) {
			System.out.println("stream: " + stream );
		}

		SimuSineStreamProducer producer = new SimuSineStreamProducer(conf);
		producer.addStreamListener(StreamID.WAVEFORM, t);
		producer.addStreamListener(StreamID.MEASUREMENT, t );
		for( int i = 0; i < 10; i++) {
			producer.tick();
		}
		System.out.println("done!");
	}

}
