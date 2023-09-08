package idea.driver;

import idea.conf.DeviceCapabilities;
import idea.conf.DeviceConfiguration;
import idea.intf.AdapterInterface;
import idea.model.IntfUtil;
import idea.schema.rp.RpMetric;

import java.io.IOException;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

import icuInterface.adapters.EvitaDriver;


public class SQLCheckAnnotatedCapabilities {

	/**
	 * @param args
	 * @throws IOException
	 */
	public static void main(String[] args) throws IOException {

		// run_driver_comparisons(new Cosmo8100Driver(null), Cosmo.class );
		// run_driver_comparisons(new DragerDriver(null), DragerDelta.class );
		run_driver_comparisons(new EvitaDriver(null), null); // FIXME DragerEvita.class );
		
	}

	private static void run_driver_comparisons(AdapterInterface driver, Class<?> db_class ) {
			DeviceConfiguration caps = driver.getStaticCapabilities();
			RpMetric[] dev_metrics = null; // FIXME caps.getMetrics();
			RpMetric[] db_metrics = IntfUtil.getMetrics(db_class);

			compare_metrics(dev_metrics, db_metrics);
	}

	private static void compare_metrics(RpMetric[] dev_metrics, RpMetric[] db_metrics) {
		Map<String, RpMetric> dev_map = new HashMap<String, RpMetric>();
		add_all_metrics(dev_map, dev_metrics);
		Map<String, RpMetric> db_map = new HashMap<String, RpMetric>();
		add_all_metrics(db_map, db_metrics);

		// iterate through the parameters of the dev_set
		Iterator<String> ii = dev_map.keySet().iterator();
		while (ii.hasNext()) {
			String loc = ii.next();
			RpMetric ref = dev_map.get(loc);
			RpMetric comp = db_map.get(loc);
			compareMetrics(ref, comp);
			if (comp != null) {
				db_map.remove(loc);
			}
		}

		// anything left was not found in the reference map
		for (String key : db_map.keySet()) {
			log_not_found(" only in DB map", db_map.get(key));
		}
	}

	private static void add_all_metrics(Map<String, RpMetric> map, RpMetric[] metrics) {
		for (RpMetric metric : metrics) {
			map.put(metric.getLocation().toString(), metric);
		}

	}

	private static int compareMetrics(RpMetric ref, RpMetric comp) {
		int err = 0;
		if (comp == null) {
			err++;
			log_not_found(" only in REF map", ref);
			return err;
		}

		System.out.print(ref.getLocation());
		err += compare_equal("code", ref.getCode(), comp.getCode());
		err += compare_equal("name", ref.getName(), comp.getName());
		err += compare_equal("unit", ref.getUnit(), comp.getUnit());

		if (err == 0) {
			System.out.println("...ok");
		} else {
			System.out.println("...err=" + err);
		}

		return err;
	}

	private static int compare_equal(String key, Object ref, Object comp) {
		int err = 0;
		if( ref == null && comp == null ) {
			return 0;
		}
		
		if( comp instanceof String ) {
			String s = (String)comp;
			if( ref == null && s.length() == 0 ) {
				// let it slide for now
				return 0;
			}
		}
	
		if (ref == null || !ref.equals(comp)) {
			err++;
			System.out.print(" ");
			System.out.print(key);
			System.out.print("(");
			System.out.print(ref);
			System.out.print("!=");
			System.out.print(comp);
			System.out.print(")");
		}
		return err;
	}

	private static void log_not_found(String prefix, RpMetric metric) {
		System.out.print(prefix);
		System.out.print(": ");
		System.out.println(metric.toString());
	}

}
