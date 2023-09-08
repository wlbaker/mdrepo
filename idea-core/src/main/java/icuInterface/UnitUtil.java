package icuInterface;

import idea.schema.rp.RpLinearUnit;
import idea.schema.rp.RpPrecisionUnit;
import idea.schema.rp.RpUnit;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class UnitUtil {
	
	@Deprecated
	public static double getValue(RpUnit unit, double v) {
		double val = unit.transform_d( v );
		
		return val;
	}
	
	


	public static RpLinearUnit parseLinearUnit(String s) {
		RpLinearUnit l = null;
		if (s == null) {
			// ignore
		} else {
			String[] arr = s.split("[\\[,\\]]");

			if (arr.length != 3) {
				log.error("UNIT PARSING failed: {}", s);
			} else {
				double m = Double.parseDouble(arr[1]);
				double b = Double.parseDouble(arr[2]);
				String name = arr[0];
				l = new RpLinearUnit(m, b, name);
			}
		}
		return l;
	}


}
