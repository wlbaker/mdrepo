package idea.conf;

import icuInterface.PlatformUtil;
import idea.driver.NullDevice;
import idea.intf.AdapterInterface;
import idea.intf.StreamProducer;
import idea.schema.rp.RpDevice;

import java.io.IOException;
import java.lang.reflect.Constructor;
import java.lang.reflect.Method;
import java.util.ArrayList;

import lombok.extern.slf4j.Slf4j;

@Slf4j
public class DeviceFactory {

	private static ArrayList<Class<? extends StreamProducer>> drivers = new ArrayList<Class<? extends StreamProducer>>();

	public static void scanPkg(String pkgName) {
		ArrayList<Class<?>> clzzs;
		try {
			clzzs = PlatformUtil.getClassesForPackage(pkgName);
			for( Class<?> cl : clzzs ) {
				if( StreamProducer.class.isAssignableFrom(cl)) {
					drivers.add((Class<? extends StreamProducer>) cl);
				} else {
					log.warn("Skipping class: {}", cl);
				}
			}
		} catch (IOException e) {
			log.error("could not load package resources");
		}
	}

	public static Class<?> getDriverClass(String name) {
		for (Class<?> clzz : drivers) {
			if (clzz.getName().equals(name)) {
				return clzz;
			}
		}

		return null;
	}

	public static AdapterInterface createDriver(RpDevice conf) {
		String className = conf.getDeviceClass();
		return createDriver(className, conf);
	}

	public static AdapterInterface createDriver(String className, RpDevice conf) {
		AdapterInterface driver = null;

		if (className == null) {
			className = NullDevice.class.getCanonicalName();
		}
		
		/*
		 * compatibility for relocated drivers
		 */
		if( "icuInterface.adapters.IFMoutDriver".equals(className)) {
			className = "idea.driver.IFMoutDriver";
		}
		if( "icuInterface.adapters.InfinityDriver".equals(className)) {
			className = "idea.driver.InfinityDriver";
		}

		try {
			Class<?> clazz = Class.forName(className);
			Constructor<?> mid = clazz.getConstructor(RpDevice.class);
			driver = (AdapterInterface) mid.newInstance(conf);
		} catch (Exception e) {
			log.error("could not build driver for class: {}", className, e);
		}

		return driver;
	}

	public static DeviceConfiguration createConfig(Class<?> cl) {

		DeviceConfiguration conf = null;
		try {
			Method m = cl.getMethod("createConfigInstance", null);
			conf = (DeviceConfiguration) m.invoke(null, null);
		} catch (Exception ex) {
			// TODO Auto-generated catch block
			ex.printStackTrace();
		}
		return conf;
	}

	public static DeviceConfiguration createConfig(String devClassName) {
		Class<?> cl = getDriverClass(devClassName);
		if (cl == null) {
			try {
				cl = Class.forName(devClassName);
			} catch (ClassNotFoundException e) {
				e.printStackTrace();
				return null;
			}
		}
		return createConfig(cl);
	}
	
	public static ArrayList<Class<? extends StreamProducer>> getDrivers() {
		return drivers;
	}

	public static StreamProducer createProducer(String className ) {
		StreamProducer driver = null;

		try {
			Class<?> clazz = Class.forName(className);
			Constructor<?> mid = clazz.getConstructor();
			driver = (StreamProducer) mid.newInstance();
		} catch (Exception e) {
			log.error("could not build stream producer", e);
		}

		return driver;
	}

}
