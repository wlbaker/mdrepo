package idea.driver.jljack;

import static idea.jljack.ExoDriver.*;

import java.io.IOException;
import java.util.Collection;
import java.util.LinkedList;
import java.util.List;

import javassist.CannotCompileException;
import javassist.NotFoundException;
import lombok.extern.slf4j.Slf4j;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpMetric;
import idea.conf.DeviceCapabilities;
import idea.conf.DeviceConfiguration;
import idea.intf.AbstractStreamProducer;
import idea.intf.AdapterInterface;
import idea.intf.DataTyp;
import idea.jljack.U3Driver;
import idea.jljack.U3;
import idea.jljack.U3_C_DATA_MODEL;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.ModelUtil;
import idea.model.PersistentItem;

enum ALLOCMETHOD {
	FIXEDBUF, // same buf is used over-and-over 
	SINGLEUSE, // buf is used once, then reallocated for next data block
	POOL //
}

@Slf4j
public class ProtoDriver extends AbstractStreamProducer implements AdapterInterface {

	private static DeviceCapabilities caps;
	private static Class<? extends PersistentItem> cl_cap;
	private DeviceConfiguration conf;
	private static int model_seq_no = 10;
	
	static {
		caps = new DeviceCapabilities(ProtoDriver.class);
		caps.setName("U3");
		try {
			cl_cap = createModel(500, 255, 255);
			caps.addStream(StreamID.WAVEFORM, cl_cap);
		} catch (Exception e) {
			log.error("INIT SETUP ERROR", e);
		}
		// caps.addConnection( RpConnection.);
	}
	U3Driver d;
	U3_C_DATA_MODEL cdm;

	Thread th;
	Class<? extends PersistentItem> cl_conf = null;

	boolean running = true;
	Runnable r = new Runnable() {

		@Override
		public void run() {

			float[] dblsAI0 = new float[cdm.getBufsz()];
			float[] dblsAI1 = new float[cdm.getBufsz()];
			float[] dblsAI2 = new float[cdm.getBufsz()];
			// int[] ints = new int[cdm.getBufsz()];

			PersistentItem block = null;
			try {
				block = ModelUtil.getModelFromDataClass(cl_conf);
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			if (block != null) {
				RpMetric[] metrics = IntfUtil.getMetrics(cl_conf);
				IntfUtil.setValue(block, metrics[0], dblsAI0);
				IntfUtil.setValue(block, metrics[1], dblsAI1);
				IntfUtil.setValue(block, metrics[2], dblsAI2);
				running = true;
				while (running) {
					// System.out.println("*************zzread: ");
					d.read();

					block.setTime(System.currentTimeMillis());
					U3.overwrite(cdm, 0, dblsAI0, dblsAI0.length);
					U3.overwrite(cdm, 1, dblsAI1, dblsAI1.length);
					U3.overwrite(cdm, 2, dblsAI2, dblsAI2.length);

					fireStreamEvent(0, ProtoDriver.this, StreamID.WAVEFORM, block);
					//for (int i = 0; i < 3; i++) {
					//	System.out.println("[" +i + "] AI0: " + dblsAI0[i] + " AI1:" + dblsAI1[i]);
					//}
				}
			}
			// d.dump();
			System.out.println("done");
		}

	};

	public ProtoDriver() {
		d = new U3Driver();
	}

	protected static Class<? extends PersistentItem> createModel(int hz, int fio, int eio) throws Exception {
		List<RpMetric> properties = new LinkedList<RpMetric>();

		int mask = fio;
		for (int i = 0; i < 16; i++) {
			boolean f = (mask % 2) == 1;
			if (f) {
				RpMetric m = new RpMetric();
				m.setLocation("ai" + i);
				m.setCode("ai" + i);
				m.setSampleRate(hz);
				m.setSamplesPerPacket(hz / 2);
				m.setSubtyp(DataTyp.FLOAT_ARR_TYP);
				properties.add(m);
			}

			mask >>= 1;
			if (i == 7)
				mask = eio;
		}

		model_seq_no++;
		String modelName = "U3DriverModel" + model_seq_no;
		System.out.println("cr3eating model: " + modelName );
		Class<? extends PersistentItem> cl = ModelUtil.createDynamicModel( modelName, properties);
		return cl;
	}

	private void discover() {
		System.out.println("device count: " + LJUSB_GetDevCount(idea.jljack.ExoDriverConstants.U3_PRODUCT_ID));

	}

	@Override
	public void connect() throws IOException {
		cdm = d.getCDataModel();

		int rc = d.connect();

		if (rc == 0) {
			th = new Thread(r, "U3Streamer");
			th.start();
		} else {
			throw new IOException("U3 connection error: " + rc);
		}

		return;
	}

	@Override
	public void disconnect() throws IOException {
		running = false;
		if (th != null) {
			synchronized (th) {
				th.interrupt();
			}
			try {
				th.join();
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}

		int rc = d.disconnect();
		if (rc != 0) {
			throw new IOException("U3 disconnect error: " + rc);
		}

		return;
	}

	public void tick() {
		d.tick();
	}

	public void setConfig(RpDevice dev) throws IOException {
		// FIXME: ignoring dev configuration
		log.error("FIXME: ignoring dev configuration for C++ driver");
		d.setConfig();
		
		conf = new DeviceConfiguration(dev);
		if( conf.getName() == null ) {
			conf.setName( caps.getName() );
		}
		try {
			cdm = d.getCDataModel();
//			cdm.setHz(100);
//			cdm.setFio(7);
//			cdm.setEio(0);
			cl_conf = createModel(cdm.getHz(), cdm.getFio(), cdm.getEio());
			log.warn("CONF might not have changed....cached config?");
		} catch (Exception e) {
			throw new IOException(e);
		}
		conf.addStream(StreamID.WAVEFORM, cl_conf );
		
	}

	@Override
	public RpDevice getConfiguration() {
		if( conf == null ) {
			return super.getConfiguration();
		}
		return conf;
	}

	@Override
	public DeviceConfiguration getStaticCapabilities() {
		return caps;
	}

	public static void main(String[] args) throws IOException {

		// System.loadLibrary("labjackusb");
		System.loadLibrary("ideaLJack");

		U3.c_unbuf();
		System.out.println("hello from labjack version: " + LJUSB_GetLibraryVersion());

		ProtoDriver f = new ProtoDriver();

		f.discover();
		f.setConfig(null);

		//f.configure(ALLOCMETHOD.FIXEDBUF); // really only viable for a single thread
		f.connect();

		f.tick();
		try {
			Thread.sleep(5000);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		f.disconnect();
	}
}
