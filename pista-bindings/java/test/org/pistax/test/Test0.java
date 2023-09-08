package org.pistax.test;

import org.pistax.PistaCl;
import org.pistax.PistaDev;
import org.pistax.PistaDriver;

public class Test0 {

	public static void main(String[] args) {
		
		/*
		 * Specify the bindings file explicitly if it has not been installed
		 * into a OS-findable path.
		 */
		System.load("/home/bbaker/git/pista/pista-bindings/libpista-java.so");
		
		PistaCl pista = PistaCl.getInstance();
		pista.unbufferStdio();
		
		pista.loadPlugin("propaqm", "/home/bbaker/git/pista/libpista-propaqm.so");
		
		PistaDriver driver = pista.driver("propaqm");
		PistaDev propaq = driver.allocate();
		
		// propaq.attach( new JsonEventHandler() );
		propaq.attach( new PropaqEventHandler() );
		//propaq.setOption("host", "192.168.50.55");
		
		propaq.setOption("user", "zolldata:MDARK2018");
		propaq.setOption("host", "AI17A005890.X-Series.device.ZOLL.local");
		
		propaq.dump(7);
		
		propaq.connect();
	
		for( int i = 1; i <= 30; i++ ) {
			pista.tick();
			System.out.println("tick " + i);
			try {
				Thread.sleep(1000);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		propaq.disconnect();
		
		System.out.println("complete");

	}

}
