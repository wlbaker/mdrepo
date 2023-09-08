package idea.datamanager.junit;

import icuInterface.RpUtil;
import icuInterface.conf.dev.SocketDeviceConfiguration;

import java.io.File;
import java.io.IOException;
import java.net.URISyntaxException;
import java.net.URL;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.jar.JarEntry;
import java.util.jar.JarFile;

import idea.conf.DeviceCapabilities;
import idea.conf.DeviceConfiguration;
import idea.driver.NullDevice;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.dev.DragerDelta_Demographics;
import idea.model.dev.DragerDelta_Measurements;
import idea.model.dev.DragerDelta_Sensors;
import idea.persistence.StudyDefinition;
import hdf.hdf5lib.exceptions.HDF5LibraryException;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpStream;
import idea.schema.rp.RpSubject;

public class TestCommon {

	public static File TEST_DIR;

	static {
		String os = System.getProperty("os.name");

		if ("linux".equals(os.toLowerCase())) {
			TEST_DIR = new File("/tmp");
		} else {
			TEST_DIR = new File("c:/tmp");
		}

	}

	public static StreamProducer createPartialDragerDeltaDevice(String devName)
			throws IOException, HDF5LibraryException {

		DeviceConfiguration conf = NullDevice.createConfigInstance();
		conf.setName(devName);

		NullDevice d = new NullDevice(conf);
		DeviceCapabilities caps = d.getStaticCapabilities();

		{
			DragerDelta_Sensors sens = new DragerDelta_Sensors();

			RpMetric m1 = IntfUtil.getMetricByLoc(sens, "ecg lead_I");
			RpMetric m2 = IntfUtil.getMetricByLoc(sens, "art");
			// conf.addStream( caps.getStream(StreamID.MEASUREMENT));
			// conf.addStream( caps.getStream(StreamID.WAVEFORM));
			RpStream s = new RpStream();
			s.setName(StreamID.WAVEFORM.getName());
			s.getMetric().add(m1);
			s.getMetric().add(m2);

			// conf.addStream(s);
		}
		{
			DragerDelta_Measurements mm = new DragerDelta_Measurements();

			RpMetric m1 = IntfUtil.getMetricByLoc(mm, "art.sys");
			RpMetric m2 = IntfUtil.getMetricByLoc(mm, "art.dia");

			RpStream s = new RpStream();
			s.setName(StreamID.MEASUREMENT_2.getName());
			s.getMetric().add(m1);
			s.getMetric().add(m2);

			conf.addStream(s);
		}
		// conf.addStream(StreamID.MEASUREMENT, DragerDelta_Measurements.class);
		// conf.addStream(StreamID.DDDEMOGRAPHICS, DragerDelta_Demographics.class);

		return d;
	}

	public static ArrayList<Class<?>> getClassesForPackage(Package pkg) {
		String pkgname = pkg.getName();
		ArrayList<Class<?>> classes = new ArrayList<Class<?>>();
		// Get a File object for the package
		File directory = null;
		String fullPath;
		String relPath = pkgname.replace('.', '/');
		System.out.println("ClassDiscovery: Package: " + pkgname + " becomes Path:" + relPath);
		URL resource = ClassLoader.getSystemClassLoader().getResource(relPath);
		System.out.println("ClassDiscovery: Resource = " + resource);
		if (resource == null) {
			throw new RuntimeException("No resource for " + relPath);
		}
		fullPath = resource.getFile();
		// System.out.println("ClassDiscovery: FullPath = " + resource);

		try {
			directory = new File(resource.toURI());
		} catch (URISyntaxException e) {
			throw new RuntimeException(
					pkgname + " (" + resource
							+ ") does not appear to be a valid URL / URI.  Strange, since we got it from the system...",
					e);
		} catch (IllegalArgumentException e) {
			directory = null;
		}
		// System.out.println("ClassDiscovery: Directory = " + directory);

		if (directory != null && directory.exists()) {
			// Get the list of the files contained in the package
			String[] files = directory.list();
			for (int i = 0; i < files.length; i++) {
				// we are only interested in .class files
				if (files[i].endsWith(".class")) {
					// removes the .class extension
					String className = pkgname + '.' + files[i].substring(0, files[i].length() - 6);
					// System.out.println("ClassDiscovery: className = " + className);
					try {
						classes.add(Class.forName(className));
					} catch (ClassNotFoundException e) {
						throw new RuntimeException("ClassNotFoundException loading " + className);
					}
				}
			}
		} else {
			try {
				String jarPath = fullPath.replaceFirst("[.]jar[!].*", ".jar").replaceFirst("file:", "");
				JarFile jarFile = new JarFile(jarPath);
				Enumeration<JarEntry> entries = jarFile.entries();
				while (entries.hasMoreElements()) {
					JarEntry entry = entries.nextElement();
					String entryName = entry.getName();
					if (entryName.startsWith(relPath) && entryName.length() > (relPath.length() + "/".length())) {
						// System.out.println("ClassDiscovery: JarEntry: " + entryName);
						String className = entryName.replace('/', '.').replace('\\', '.').replace(".class", "");
						// System.out.println("ClassDiscovery: className = " + className);
						try {
							classes.add(Class.forName(className));
						} catch (ClassNotFoundException e) {
							throw new RuntimeException("ClassNotFoundException loading " + className);
						}
					}
				}
			} catch (IOException e) {
				throw new RuntimeException(pkgname + " (" + directory + ") does not appear to be a valid package", e);
			}
		}
		return classes;
	}

	public static RpSubject getDefaultSession() {
		// TODO Auto-generated method stub
		return null;
	}

}
