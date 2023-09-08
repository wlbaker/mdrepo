/**
 * TODO: NJC: Header Documentation
 * 
 * 
 * 
 * $Date: 2010-03-11 16:38:12 -0600 (Thu, 11 Mar 2010) $
 * $Revision: 1022 $
 * $Author: bbaker $
 * $HeadURL: svn://143.83.220.223/DSS/trunk/ICUInterface/src/icuInterface/serverMessages/NumericsItem.java $
 * $Id: NumericsItem.java 1022 2010-03-11 22:38:12Z bbaker $
 */

package icuInterface.message;

import icuInterface.UnitUtil;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpUnit;

public abstract class AbstractItem {

	protected RpMetric md;

	public AbstractItem(RpMetric md) {
		this.md = md;
	}

	public String getName() {
		return md.getName();
	}

	public String getLocation() {
		return md.getLocation();
	}

	public RpMetric getDescription() {
		return md;
	}

	@Override
	public String toString() {
		return md.getLocation() + ":" + getValue();
	}

	// abstract public void setValue(Object value);
	abstract public Object getValue();

	abstract public void clear();

	public Object getScaledValue() {
		Object o = getValue();
		if (o != null && md != null ) {
			RpUnit unit = md.getUnit();
			if (unit != null && o instanceof Number) {
				Object d = UnitUtil.getValue(unit,((Number) o).doubleValue());
				if (d != null) {
					o = d;
				}
			}
		}

		return o;
	}
}