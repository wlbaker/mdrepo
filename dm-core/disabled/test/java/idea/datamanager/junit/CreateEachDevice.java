package idea.datamanager.junit;

import static org.junit.Assert.assertTrue;

import idea.conf.DeviceCapabilities;
import idea.driver.NullDevice;
import idea.intf.StreamProducer;
import idea.persistmanager.PiHdf5Exporter;

import java.io.File;
import java.io.IOException;
import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.ArrayList;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import idea.schema.rp.RpDevice;
import idea.schema.rp.RpSubject;

public class CreateEachDevice {

	private PiHdf5Exporter exporter;

	@Before
	public void setUp() throws Exception {
		File f = new File(TestCommon.TEST_DIR, "test_create_each.h5");
		if (f.exists()) {
			boolean ok = f.delete();
			assertTrue("COULD NOT DELETE FILE!", ok);
		}
		RpSubject session = TestCommon.getDefaultSession();
		exporter = new PiHdf5Exporter(session, f.getPath(), true);
		exporter.connect();

	}

	@Test
	public void test() throws  IOException {
		NullDevice d = new NullDevice(null);
		// Class<?> cl0 = Class.forName("icuInterface.EvitaDriver");
		Package pkg = d.getClass().getPackage();
		ArrayList<Class<?>> clss = TestCommon.getClassesForPackage(pkg);

		for (Class<?> cls : clss) {
			if (cls.isInterface()) {
				System.err.println("INTERFACE=" + cls);
			} else if (StreamProducer.class.isAssignableFrom(cls)) {

				Object conf = null;
				try {
					Method m = cls.getMethod("createConfigInstance", null);
					conf = (RpDevice) m.invoke(null, null);
				} catch (NoSuchMethodException ex) {
					System.err.println("ABSTRACT??? " + cls);
					continue;
				} catch (Exception ex) {
					// TODO Auto-generated catch block
					ex.printStackTrace();
					continue;
				}

				StreamProducer p = null;

				try {
					Constructor<?> mid = cls.getConstructor(RpDevice.class); // conf.getClass());
					p = (StreamProducer) mid.newInstance(new Object[] { null });
				} catch (InvocationTargetException ex) {
					System.err.println("NEED DLL??? " + cls);
					continue;
				} catch (Exception e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}

				try {
					RpDevice caps = p.getStaticCapabilities();
				} catch (UnsatisfiedLinkError ex) {
					System.err.println("NEED DLL??? " + cls);
					continue;
				}

				System.out.println("CLZZ=" + cls);
				
				exporter.addDevice( p.getConfiguration() );
			}
		}
	}
	
	@After
	public void tearDown() throws Exception {
		exporter.disconnect();
	}



}
