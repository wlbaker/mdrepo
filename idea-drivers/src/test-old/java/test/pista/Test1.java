/*
 * Linux Runtime configuration: add launcher environment variable 
 * 		LD_LIBRARY_PATH=/home/bbaker/git/pista/pista-core/.libs 
 */
package test.pista;

import java.io.File;

import org.pistax.PistaCl;
import org.pistax.PistaDataPacket;
import org.pistax.PistaDev;
import org.pistax.PistaDriver;
import org.pistax.PistaEventHandler;
import org.pistax.PistaUtil;
import org.pistax.pista_datatyp;

import icuInterface.PlatformUtil;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.model.dev.SimuSine_Measurement;
import idea.model.dev.SimuSine_Waveform;
import idea.schema.rp.RpMetric;

public class Test1 {

	// static SimuSine_Waveform w = new SimuSine_Waveform();
	// static SimuSine_Measurement m = new SimuSine_Measurement();
	static SimuSine_Measurement m = new SimuSine_Measurement();

	public static final void main(String[] args) throws InterruptedException {
		String devname = "simu";
		devname = "bmp180";

		String osID = PlatformUtil.getOSID();

		String pistaLibName = "jpistax";
		if (osID.startsWith("win")) {
			pistaLibName = "lib/" + osID + "jpistax.dll";
		} else {
			pistaLibName = "lib/" + osID + "/libjpistax.so";
		}

		File f = new File(System.getProperty("user.dir"), pistaLibName);
		System.out.println("Pista Library: " + f);

		if (f.exists()) {
			System.load(f.getPath());
		} else {
			System.loadLibrary("jpistax");
		}

		PistaCl pista = PistaCl.getInstance();
		PistaDriver driver = pista.driver(devname);
		PistaDev dev_inst = driver.allocate();

		PistaEventHandler h = new PistaEventHandler() {
			public int event(PistaDataPacket pkt) {
				if (pkt.getStreamID() == 'M') {
					System.out.println("got measurement");
				} else if (pkt.getStreamID() == 'W') {
					System.out.println("got sensor");
				}
				decode(pkt);
				return 0;
			}
		};

		dev_inst.attach(h);
		
		dev_inst.setOption("bus", "2");

		// System.out.println("starting background thread");
		pista.run();

		System.out.println("connecting to: " + devname);
		int rc = dev_inst.connect();
		System.out.println("code=" + rc );

		for (int loop = 1; loop <= 10; loop++) {
			System.out.println("tick..." + loop);
			Thread.sleep(1000);
			// pista.tick();
		}

		System.out.println("disconnecting");
		dev_inst.disconnect();

		System.out.println("JPistaX Test1...successful");
	}

	protected static void decode(PistaDataPacket pkt) {
		int count = pkt.getDescriptorCount();
		System.out.print("[" + count + "]");
		for (int i = 0; i < count; i++) {
			int subtyp = pkt.getDescriptorSubtyp(i);
			String loc = pkt.getDescriptorLoc(i);

			switch (subtyp) {
			case pista_datatyp.INT_TYP:
				System.out.println( loc + "=" + pkt.getInt(i));
				break;
			case pista_datatyp.INT_ARR_TYP:
				System.out.println( loc + "=" +  pkt.getIntArray(i));
				break;
			case pista_datatyp.FLOAT_TYP:
				System.out.println( loc + "=" +  pkt.getFloat(i));
				break;
			case pista_datatyp.FLOAT_ARR_TYP:
				System.out.println( loc + "=" + pkt.getFloatArray(i));
				break;
			case pista_datatyp.DOUBLE_ARR_TYP:
				System.out.println( loc + "=" + pkt.getDoubleArray(i));
				break;
			default:
				System.err.println("could not decode unknown subtyp: " + subtyp);
				break;
			}
		}
		
	}
}
