package icuInterface.adapters.s5;

import idea.schema.rp.RpLinearUnit;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class S5Unit extends RpLinearUnit {

	public S5Unit(double m, double b, String name) {
		super(m, b, name);
	}

	public double getValue(Number value) {

		if (value instanceof Short) {
			int s = value.intValue();
			if (s <= -32767) {
				return Double.NaN;
			}
		}

		log.error("FIXME: S5Unit {}", this);
		// v = super.getValue(value);
		return Double.NaN;
	}

}
