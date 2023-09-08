/** 
* @file
* @brief A first tutorial for accessing PISTA devices from Java. 
*
* @author William L Baker
*
* @date June, 18th 2016
*
**/ 

/** 
* @class Sample01 
* 
* @brief Tutorial Sample-01 
* 
* A more detailed class description 
* Linux Runtime configuration: add launcher environment variable 
* 		LD_LIBRARY_PATH=/home/bbaker/git/pista/pista-core/.libs
*  
*/

package tutorial;

import java.io.File;

import org.pista.pista_datatyp;
import org.pistax.PistaCl;
import org.pistax.PistaDataPacket;
import org.pistax.PistaDev;
import org.pistax.PistaDriver;
import org.pistax.PistaEventHandler;

/**
* @brief Does class brief goes here?
*/
public class Sample01 {
	public static String DEVICE_ID = "bmp180";  // "simu"

	public static final void main(String[] args) throws InterruptedException {

		String pistaLibName = "lib/lin64/jpistax/libjpistax.so";

		File f = new File(System.getProperty("user.dir"), pistaLibName);

		if (f.exists()) {
			System.load(f.getPath());
		} else {
			System.loadLibrary("jpistax");
		}

		PistaCl pista = PistaCl.getInstance();
		
		
		/**
		 * Get the driver from Pista
		 */
		PistaDriver driver = pista.driver(DEVICE_ID);
		
		/**
		 * Create an instance of the device
		 */
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

		pista.run();

		System.out.println("connecting to: " + DEVICE_ID);
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
			default:
				System.err.println("could not decode unknown subtyp: " + subtyp);
				break;
			}
		}
		
	}
}
