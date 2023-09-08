package idea.devwizard;

import java.util.ArrayList;
import java.util.TreeSet;

import org.pistax.PistaDriver;

import icuInterface.adapters.MindrayNetworkDriver;
import icuInterface.adapters.MrClockDriver;
import idea.conf.DeviceFactory;
import idea.model.IntfUtil;
import lombok.extern.slf4j.Slf4j;
import idea.pista.wizard.WizNationalInstrumentsPanel;

// devices that might need assistance:
//
// addDevice( MECIFDriver.class, WizMECIFPanel.class, "Philips/HP Agilent Monitor" );
// addDevice( ServoDriver.class, null, "Maquet Servo 300/900*" );
// addDevice( IDEAProxyDevice.class, WizRemoteEntryPanel.class,
// "Generic: Remote Data Entry **";

//
//	addDevice(null, NIDAQmxDriver.class, WizNationalInstrumentsPanel.class, "a2d/National Instruments DAQmx");
//	addDevice(null, NIDAQmxBaseDriver.class, WizNationalInstrumentsPanel.class,	"a2d/National Instruments DAQmxBase");

class WizardPanelDatum implements Comparable<WizardPanelDatum> {
	private Class<?> devCl;
	private Class<?> wizCl;
	private String name;
	private PistaDriver pistaDev;

	WizardPanelDatum(PistaDriver dev, Class<?> devCl, Class<?> wizCl, String name) {
		this.pistaDev = dev;
		this.devCl = devCl;
		this.wizCl = wizCl;
		this.name = name;
	}

	public PistaDriver getPistaDriver() {
		return pistaDev;
	}

	public Class<?> getDevCl() {
		return devCl;
	}

	public Class<?> getWizCl() {
		return wizCl;
	}

	public String getName() {
		return name;
	}

	@Override
	public int compareTo(WizardPanelDatum o) {
		return name.compareTo(o.getName());
	}
}

@Slf4j
public class SetupData {

	private static TreeSet<WizardPanelDatum> ll = new TreeSet<WizardPanelDatum>();

	static {

		String[] builtin = { "idea.driver", "icuInterface.adapters" };
		Package[] pkgs = Package.getPackages();
		for (Package apkg : pkgs) {
			System.out.println(apkg);
		}

		for (String pkgName : builtin) {
			DeviceFactory.scanPkg(pkgName);

		}

		// addDevice( AlphaDisplay.class, WizAlphaDisplayPanel.class, "Alpha
		// Display" );
		addDevice(null, MindrayNetworkDriver.class, WizMindrayEthernetPanel.class, "monitor/Mindray Ethernet*");
		addDevice(null, MrClockDriver.class, WizMrClockDisplayPanel.class, "z/Mr Clock");


		/*
		 * For all devices not otherwise specified, use the default
		 * configuration panel: WizStreamAdapterPanel
		 */
		for (Class<?> deviceCl : DeviceFactory.getDrivers()) {
			addDevice(null, deviceCl, WizStreamAdapterPanel.class, IntfUtil.getDriverName(deviceCl));
		}

		log.error("FIXME: pista disabled.");
//		try {
//			ArrayList<PistaDriver> pista_devs = PistaFactory.getDevices();
//			if (pista_devs != null) {
//				for (PistaDriver d : pista_devs) {
//					// specifically use the pista adapter class
//					addDevice(d, PistaAdapter.class, WizStreamAdapterPanel.class, PistaUtil.getDriverName(d));
//				}
//			}
//		} catch (UnsatisfiedLinkError t) {
//			log.error("Could not load Pista library: {}", t.getMessage() );
//		} catch (Throwable t) {
//			log.error("Could not get Pista devices: {} {}", t.getClass(), t.getMessage() );
//		}

	}

	public static void addDevice(PistaDriver dev, Class<?> devCl, Class<?> wizCl, String name) {
		WizardPanelDatum datum = new WizardPanelDatum(dev, devCl, wizCl, name);
		ll.add(datum);
	}

	public static Class<?> getWizardForDevice(String className) {
		Class<?> clazz = null;

		for (WizardPanelDatum datum : ll) {
			Class<?> datum_cl = datum.getDevCl();
			if (className.equals(datum_cl.getCanonicalName())) {
				clazz = datum.getWizCl();
				break;
			}
			if (className.indexOf("DragerDriver") > 0 && datum_cl.getCanonicalName().indexOf("InfinityDriver") > 0) {
				clazz = datum.getWizCl(); // found a match
				break;
			}
		}

		return clazz;
	}

	public static Class<?> getWizardForDevice(Class<?> devCl) {
		Class<?> clazz = null;

		for (WizardPanelDatum datum : ll) {
			if (datum.getDevCl().equals(devCl)) {
				clazz = datum.getWizCl();
				break;
			}
		}

		return clazz;
	}

	public static WizardPanelDatum[] getDevices() {
		WizardPanelDatum[] ar = new WizardPanelDatum[ll.size()];

		ll.toArray(ar);
		return ar;
	}

}
