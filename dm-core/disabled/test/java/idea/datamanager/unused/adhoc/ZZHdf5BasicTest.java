package idea.datamanager.unused.adhoc;

import java.io.IOException;
import java.util.Date;

import idea.persistmanager.PiHdf5Exporter;
import idea.schema.rp.RpSubject;

public class ZZHdf5BasicTest {

	public static void main(String[] args) throws IOException {
		if (args.length < 1) {
			System.out.println("usage: <prog> <file>");
			System.exit(0);
		}

		System.loadLibrary("hdf5");
		System.loadLibrary("hdf5_java");

		String fileName = args[0];

		RpSubject session = null; // buildSessionHeader();
		PiHdf5Exporter exporter = new PiHdf5Exporter(session, fileName, true);
		exporter.connect();

		exporter.disconnect();
	}


}
