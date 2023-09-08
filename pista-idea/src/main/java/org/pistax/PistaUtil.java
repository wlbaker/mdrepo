package org.pistax;

import idea.model.IntfUtil;
import idea.model.PersistentItem;
import lombok.extern.slf4j.Slf4j;
import idea.schema.rp.RpMetric;

@Slf4j
public class PistaUtil {

	public static int decodePistaPacket(PersistentItem dest, PistaDataPacket pkt) {
		dest.setTime(System.currentTimeMillis());

		int count = pkt.getDescriptorCount();
		for (int field_idx = 0; field_idx < count; field_idx++) {
			int subtyp = pkt.getFieldSubtyp(field_idx);
			String loc = pkt.getDescriptorLoc(field_idx);
			if("tm".equals(loc)) {
				long millis;
				if( subtyp ==  pista_datatyp.LONG_TYP ) {
					 millis = pkt.getLong(field_idx);
				} else {
					millis = -1;
					log.error("do not know how to read tm field: " + subtyp);
				}
				dest.setTime(millis);
				continue;
			}
			if("sid".equals(loc)) {
				int sid;
				if( subtyp ==  pista_datatyp.INT_TYP ) {
					 sid = pkt.getInt(field_idx);
				} else {
					sid = -1;
					log.error("do not know how to read sid field: " + subtyp);
				}
				dest.setStreamID( sid );
				continue;
			}

			RpMetric metric = null;
			if (dest != null) {
				metric = dest.getMetric(loc);
			}
			if (metric == null) {
				log.debug("No such metric in item: {}", loc);
				continue;
			}

			switch (subtyp) {
			case pista_datatyp.LONG_TYP:
				IntfUtil.setValue(dest, metric, pkt.getLong(field_idx));
				break;
			case pista_datatyp.INT_TYP:
				IntfUtil.setValue(dest, metric, pkt.getInt(field_idx));
				break;
			case pista_datatyp.INT_ARR_TYP:
				IntfUtil.setValue(dest, metric, pkt.getIntArray(field_idx));
				break;
			case pista_datatyp.FLOAT_TYP:
				IntfUtil.setValue(dest, metric, pkt.getFloat(field_idx));
				break;
			case pista_datatyp.FLOAT_ARR_TYP:
				IntfUtil.setValue(dest, metric, pkt.getFloatArray(field_idx));
				break;
			case pista_datatyp.STRING_TYP:
				IntfUtil.setValue(dest, metric, pkt.getString(field_idx));
				break;
			case pista_datatyp.BYTE_ARR_TYP:
				// int sz = pkt.getDescriptorSize(i)
				// byte [] v = new byte[sz];
				
				// FIXME: prefered method would be pkt.getByteArray(i, v, sz ), 
				// but that method is currently broken in SWIG translation
				
				String v = pkt.getString(field_idx);
				IntfUtil.setValue(dest, metric, v);
				break;
			default:
				System.err.println("could not decode unknown subtyp: " + subtyp);
				break;
			}
		}
		return 0;
	}

	public static String getDriverName(PistaDriver d) {
		return "PISTA: " + d.longname();
	}

	public static void run() {
		try {
			PistaCl pista = PistaCl.getInstance();
			pista.run();
		} catch (Throwable t) {
			log.error("could not start pista", t);
		}

	}

	public static void stop() {
		try {
			PistaCl pista = PistaCl.getInstance();
			pista.stop();
		} catch (Throwable t) {
			log.error("could not stop pista", t);
		}

	}

	public static String getJARVersion() {
		String jarVersion = "N/A";
		//.jarVersion = PISTAConstants.VERSION;
		return jarVersion;
	}

	public static String getNativeVersion() {
		String ver = PISTAXJNI.getPistaVersion();
		ver += " [";
		try {
			PistaCl pista = PistaCl.getInstance();
			int n = pista.driver_count();
			for (int i = 0; i < n; i++) {
				PistaDriver drv = pista.driver(i);
				if (i > 0)
					ver += ",";
				ver += drv.name();
			}
		} catch (Throwable t) {
			ver += " " + t.getMessage();
		}
		ver += "]";
		return ver;
	}
}