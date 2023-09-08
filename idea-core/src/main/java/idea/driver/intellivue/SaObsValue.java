package idea.driver.intellivue;

import java.nio.ByteBuffer;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import lombok.extern.slf4j.Slf4j;

@Slf4j
public class SaObsValue implements Reportable {
	private static int prev = 0;
	private static Map<Integer,SaObsValue> cache = new HashMap<Integer,SaObsValue>();
	
	short physio_id;
	short state;
	int[] vals;

	public static SaObsValue parse(ByteBuffer bb) {
		short physio_id = bb.getShort();
		short state = bb.getShort();
		short len = bb.getShort();
		
		int key = (len << 16) + physio_id;
		SaObsValue obs = cache.get(key);
		if (obs == null) {
			obs = new SaObsValue();
			cache.put( key, obs );
			obs.physio_id = physio_id;
			obs.state = state;
			if (obs.vals == null) {
				obs.vals = new int[len / 2];
			}
			log.debug("PUT CACHE physio_id={} len={} key=0x" + Integer.toHexString(key), physio_id, len );
		} else {
			// log.debug("GET CACHE physio_id={} len={} key=0x" + Integer.toHexString(key), physio_id, len );
		}
		
		if( len == 2*obs.vals.length ) {
			parse(obs, 	obs.vals.length, bb);
		} else { 
			log.error("Incorrect length value storage length! physio_id={} len={} alloc=" + obs.vals.length, physio_id, len);
		}
		return obs;
	}


	public static void parse(SaObsValue obs, int count, ByteBuffer bb) {

		for (int i = 0; i < count; i++) {
			int val = bb.getShort();
			if (val < 0)
				val += 65536;

			if (val == 0x7fffff) {
				val = -1;
			}
			obs.vals[i] = val; // top bit...used as beat detect?
			prev = val;
		}

		return;
	}

	public int[] getValues() {
		return vals;
	}

	@Override
	public void dump() {
		System.out.println("SaObsValue");
		System.out.println("    physio_id: " + physio_id);
		System.out.println("        state: 0x" + Integer.toHexString(state));
		System.out.print("        vals: ");
		if (vals == null) {
			System.out.print("NONE");
		} else {
			for (int val : vals) {
				System.out.print(" ");
				System.out.print(val);
			}
		}
		System.out.println();

	}

	public int getPhysioID() {
		int p = physio_id;
		if (p < 0) {
			p += 65536;
		}
		return p;
	}

	public void fixSpecMask(SimpleArraySpecn aspec, SampleArrayFixedValueSpecn fvspecn) {
		if (aspec == null) {
			log.debug("NO ASPEC...no fix");
			return;
		}

		if (fvspecn != null) {
			List<SaFixedValSpec16> specs = fvspecn.getSpecs();
			// System.out.print("\nspecs=" + specs.size());
			for (SaFixedValSpec16 spec : specs) {
				// System.out.println();
				// System.out.print(spec);
				// System.out.print(": ");
				for (int i = 0; i < vals.length; i++) {
					// System.out.print(Integer.toHexString(vals[i]));
					// System.out.print(" ");
					if ((vals[i] & spec.sa_fixed_val) == spec.sa_fixed_val) {
						if (log.isDebugEnabled()) {
							System.out.println("ERASING SPEC MARK: " + spec.sa_fixed_val_id + " oldval: "
									+ Integer.toHexString(vals[i]));
							System.out.println(" mask: " + Integer.toHexString(spec.sa_fixed_val));
							System.out.println(" newval: " + Integer.toHexString(vals[i]));
						}
						vals[i] = vals[i] ^ spec.sa_fixed_val;
					}
				}
			}
		}

		// we must apply the global mask AFTER applying flag filters
		int mask = 0xFFFF >> (16 - aspec.getSignificantBits());
		for (int i = 0; i < vals.length; i++) {
			vals[i] = mask & vals[i];
		}

	}

	@Override
	public String toString() {

		return "[SaObsValue: physio_id=" + physio_id + "]";
	}

}
