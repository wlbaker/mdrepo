package org.pistax;


import java.io.IOException;
import gnu.io.PortInUseException;
import gnu.io.UnsupportedCommOperationException;

import org.pista.PISTAConstants;
import org.pistax.*;

public class TestLJ {
	static void loadNatives() {
		try {
			System.out.println("LD_LIBRARY_PATH=" + System.getenv("LD_LIBRARY_PATH"));
			// System.out.println("loading libpista.so");
			// System.loadLibrary("pista");
			// System.out.println("loading libpista-cl.so");
			// System.loadLibrary("pista-cl");
			System.out.println("loading libjpista.so");
			System.loadLibrary("jpista");
			System.out.println("loading librxtxSerial.so");
			System.loadLibrary("rxtxSerial");

			System.out.println("LOADED!!!");
		} catch (UnsatisfiedLinkError e) {
			System.err
					.println("Native code library failed to load. See the chapter on Dynamic Linking Problems in the SWIG Java documentation for help.\n"
							+ e);
			System.exit(1);
		}
	}

	public static void main(String[] args) throws PortInUseException, IOException, UnsupportedCommOperationException {
		boolean is_serial = false;

		System.out.println("# ----------------------------------------");
		System.out.println("#");
		System.out.println("# java.library.path: " + System.getProperty("java.library.path"));
		System.out.println("#");
		System.out.println("#");
		System.out.println("# Adding and calling a normal C++ callback");
		System.out.println("# ----------------------------------------");
		System.out.println("#");
		System.out.println("# PISTA version: " + PISTAConstants.VERSION );
		System.out.println("#");

		loadNatives();
		
		PistaCl pista = PistaCl.getInstance();
		PistaDriver driver = pista.driver("Labjack U3");
		PistaDev dev_inst = driver.allocate();

		PistaEventHandler h = new PistaEventHandler() {


		};

		System.out.println("ATTACHING");
		dev_inst.attach(h );

		if( is_serial ) {
			PistaCommHandler ioport; 

			System.out.println();
			System.out.println("Adding and calling a Java callback");
			System.out.println("------------------------------------");
	
			ioport = new RxtxCBAdapter("/dev/ttyUSB0");
			dev_inst.attach(ioport);
			ioport.open();
			ioport.config(115200, 8, 1, 'N');
			ioport.write("hello\n".getBytes());
			ioport.close();
			// dev_inst.detach();

			// Test that a double delete does not occur as the object has already
			// been deleted from the C++ layer.
			// Note that the garbage collector can also call the delete() method via
			// the finalizer (callback.finalize())
			// at any point after here.
			ioport.delete();
		} else {
			// labjack
			System.out.println();
			System.out.println("Running LABJACK");
			System.out.println("------------------------------------");
			System.out.println("start dev...");
			dev_inst.connect();
			System.out.println("loop and tick...");
			for( int i = 0; i < 5; i++) {
				try {
					Thread.sleep(1);
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				System.out.println("tick0...");
				pista.tick();
				System.out.println("tick...");
				pista.tick();
				System.out.println("tick...");
				pista.tick();
			}
			System.out.println("stopping dev...");

			dev_inst.disconnect();
		}

		System.out.println("releasing");
		driver.release(dev_inst);

		System.out.println("java exit");
	}
}

