package org.pistax;

import java.util.ArrayList;

import lombok.extern.slf4j.Slf4j;

@Slf4j
public class PistaFactory {

	public static ArrayList<PistaDriver> getDevices() {
		ArrayList<PistaDriver> drivers = new ArrayList<PistaDriver>();

		// now try to load the Pista drivers
		PistaCl pista = null;
		try {
			pista = PistaCl.getInstance();
		} catch (UnsatisfiedLinkError e ) {
			log.error("Could not load pista [DLL/SO Error]", e );
		} catch (NoSuchMethodError e ) {
			log.error("Could not load pista [Version Error]", e );
		} catch (Exception e ) {
			log.error("Could not load pista [General Error]", e );
		}
		if (pista != null) {
			int n = pista.driver_count();

			for (int i = 0; i < n; i++) {
				PistaDriver d = pista.driver(i);
				drivers.add(d);
			}
		}

		return drivers;
	}

}
