package idea.display.elegant;

import java.text.DecimalFormat;
import java.text.NumberFormat;

import icuInterface.message.CompositeItem;
import icuInterface.message.NumericItem;
import idea.schema.rp.RpLinearUnit;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpPrecisionUnit;
import idea.schema.rp.RpUnit;

public class ValueHelper {
	private static NumberFormat df0 = new DecimalFormat("0");
	private static NumberFormat df1 = new DecimalFormat("0.0");
	private static NumberFormat df2 = new DecimalFormat("0.00");
	private static NumberFormat df3 = new DecimalFormat("0.000");

	private static NumberFormat fmt = NumberFormat.getNumberInstance();

	// FIXME: most of this routine is for handling data types that dont exist
	// any more...!!
	@Deprecated
	public static String format(int format, RpMetric desc, Object item) {
		String val = null;

		RpUnit unit = desc.getUnit();

		if (item instanceof NumericItem) {

			NumericItem ni = (NumericItem) item;
			Number niv = ni.getScaledValue();
			if (niv == null || ni.getValue() == null) {
				val = "***";
			} else {
				int int_val = ni.getValue().intValue();
				if ((format == 1) && (int_val <= 4)) {
					val = "***";
				} else if ((format == 4) && (int_val == 1)) {
					val = "";
				} else if ((int_val >= 0x7fffff)) { // magic value for Philips
					val = "-?-";
				} else {
					RpLinearUnit linu = (RpLinearUnit) unit;
					double m = linu.getM();
					if (m < 0.02) {
						val = df2.format(niv.doubleValue());
					} else if (m < .2) {
						val = df1.format(niv.doubleValue());
					} else {
						val = fmt.format(niv.doubleValue());
					}
				}
			}

		} else if (item instanceof CompositeItem) {
			CompositeItem ci = (CompositeItem) item;
			val = "" + ci.getValue(0) + "/" + ci.getValue(1) + "/" + ci.getValue(2);
		} else if (item == null) {
			val = "---";
		} else if (unit instanceof RpPrecisionUnit) {
			RpPrecisionUnit pu = (RpPrecisionUnit) unit;
			int precision = pu.getPrecision();
			NumberFormat f = df0;
			if (precision == 1) {
				f = df1;
			}
			if (precision == 2) {
				f = df2;
			}
			if (precision == 3) {
				f = df3;
			}
			val = f.format(((Number) item).doubleValue());
		} else {
			val = "" + item;
		}

		return val;
	}

}
