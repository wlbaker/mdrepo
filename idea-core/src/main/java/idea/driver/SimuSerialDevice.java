package idea.driver;

import idea.conf.DeviceCapabilities;
import idea.conf.DeviceConfiguration;
import idea.connections.NoConnection;
import idea.intf.AdapterInterface;
import idea.intf.AdapterUtil;
import idea.intf.DataTyp;
import idea.intf.SerialAdapter;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.ModelUtil;
import idea.model.PersistentItem;
import idea.model.dev.SimuSine_Measurement;
import idea.model.dev.SimuSine_Waveform;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpMetric;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;

import com.fazecast.jSerialComm.SerialPort;

import lombok.extern.slf4j.Slf4j;

@Slf4j
public class SimuSerialDevice extends SerialAdapter implements AdapterInterface {

	private static final String driverName = "z/Serial Device Simulator";
	
	private static final Map<StreamID, Class<? extends PersistentItem>> models = new HashMap<StreamID, Class<? extends PersistentItem>>();
	Map<Integer, Integer> pos_s = new HashMap<Integer,Integer>();
	
	private static DeviceCapabilities default_caps;
	final double BASE_PERIOD = Math.PI / 100;
	final double SCALE = 10;
	final double OFFSET = 10;

	private double dtick;

	
	static {
		default_caps = new DeviceCapabilities(SimuSerialDevice.class);
		default_caps.setName( driverName );
		default_caps.addStream(StreamID.MEASUREMENT, SimuSine_Measurement.class);
		
		default_caps.addConnection( new NoConnection() );
		models.put(StreamID.MEASUREMENT,SimuSine_Measurement.class );
		
		default_caps.setModels( new String [] {"Vitals Monitor"} );
	}
	public static DeviceConfiguration createConfigInstance() {
		DeviceConfiguration conf = new DeviceConfiguration(SimuSineStreamProducer.class );
		conf.setName("SINE00");
		conf.setModelName("sine");
		conf.addStream(StreamID.MEASUREMENT, SimuSine_Measurement.class);
		
		return conf;
	}

	public SimuSerialDevice( RpDevice conf) {
		this( null, conf);
	}
	
	public SimuSerialDevice(DeviceCapabilities caps, RpDevice conf) {
		super( conf);

		if( caps == null ) {
			caps = default_caps;
		}
		
		AdapterUtil.fix_config(caps, conf);
		
	}

	@Override
	public DeviceCapabilities getStaticCapabilities() {
		return default_caps;
	}


	@Override
	public int tick() {

		StreamID[] sids = new StreamID[] { StreamID.MEASUREMENT, StreamID.WAVEFORM };
		// StreamID[] sids = new StreamID[] { StreamID.WAVEFORM };
		
		dtick += 0.1;
		
		for (StreamID sid : sids) {
			int freq = 1;
			PersistentItem block = ModelUtil.getModelFromDataClass(models.get(sid));
			block.setTm( new Date() );  // current time

			RpMetric[] metrics = IntfUtil.getMetrics(block);
			int idx = 0;
			for( RpMetric md : metrics ) {
				Integer spp = md.getSamplesPerPacket();
				Object val;
				freq *= 2;
				if( spp == null || spp == 0 || spp == 1 ) {
					double d = (SCALE * Math.sin(BASE_PERIOD*freq + dtick) + OFFSET );
					if( md.getSubtyp() == DataTyp.INT_TYP ) {
						val = (int)d;
					} else {
						val = d;
					}
				} else {
					int subt = md.getSubtyp();
					if( subt == DataTyp.INT_ARR_TYP) {
						val = buildIntArray(freq, idx, spp );
					} else if (subt == DataTyp.FLOAT_ARR_TYP) {
						val = buildFloatArray(freq, idx, spp );
					} else {
						val = null;
						log.error("UNKNOWN DATATYP: {}", subt );
					}
				}
				IntfUtil.setValue(block, md, val );
				idx++;
			}
			this.fireStreamEvent(0, this, sid, block);
		}
		return 0;
	}

	private int[] buildIntArray(double freq, int idx, int spp) {
		int pos = 0;
		Integer o_pos = pos_s.get(idx);
		if( o_pos != null) {
			pos = o_pos;
		}
		int [] seg = new int[spp];
		for( int i = 0; i < spp; i++ ) {
			seg[i] = (int) (SCALE * Math.sin(BASE_PERIOD*freq*pos) + OFFSET);
			pos++;
		}
		pos_s.put( idx, pos );
		idx++;
		
		return seg;
	}

	private float[] buildFloatArray(double freq, int idx, int spp) {
		int pos = 0;
		Integer o_pos = pos_s.get(idx);
		if( o_pos != null) {
			pos = o_pos;
		}
		float [] seg = new float[spp];
		for( int i = 0; i < spp; i++ ) {
			seg[i] = (float) (SCALE * Math.sin(BASE_PERIOD*freq*pos) + OFFSET);
			pos++;
			// System.out.println(idx + ",SIN," + seg[i] + "," + pos );
		}
		pos_s.put( idx, pos );
		
		return seg;
	}

	@Override
	public void connect() throws IOException {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void process(InputStream is, OutputStream os) throws IOException {
		// TODO Auto-generated method stub
		
	}
	
	// test the byte array to see if the data is recognized
	public void probe(OutputStream out) throws IOException {
		out.write("Hello Simulator!!".getBytes());
		return;
	}
	
	public boolean test(byte[] arr) {
		System.err.println("simuserial: " + new String(arr) ); 
		return false;
	}

	@Override
	public int getListeningEvents() {
		return SerialPort.LISTENING_EVENT_DATA_RECEIVED;
	}

}
