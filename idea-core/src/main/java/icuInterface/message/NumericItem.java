/**
 * TODO: NJC: Header Documentation
 * 
 * 
 * 
 * $Date: 2012-01-31 14:30:35 -0600 (Tue, 31 Jan 2012) $
 * $Revision: 4023 $
 * $Author: bbaker $
 * $HeadURL: svn://143.83.220.223/DSS/trunk/ICUInterface/src/icuInterface/serverMessages/NumericsItem.java $
 * $Id: NumericsItem.java 4023 2012-01-31 20:30:35Z bbaker $
 */

package icuInterface.message;

import static idea.intf.DataTyp.DOUBLE_TYP;
import static idea.intf.DataTyp.INT_TYP;
import static idea.intf.DataTyp.LONG_TYP;

import idea.schema.rp.RpMetric;

public class NumericItem extends AbstractItem {

	private Number value;

	public NumericItem(RpMetric md) {
		super( md );
	}

	public void setValue(Number value) {
		if( value instanceof Long ) {
			assert( md.getSubtyp() == LONG_TYP ) : "[NumericsItem] INVALID LONG ASSIGNMENT to typ: " + md.getSubtyp();
		}
		if( value instanceof Integer ) {
			assert( md.getSubtyp() == INT_TYP ) : "[NumericsItem] INVALID INT ASSIGNMENT to typ: " + md.getSubtyp();
		}
		if( value instanceof Double ) {
			if( md.getSubtyp() == DOUBLE_TYP ) {
				// good!
			} else if( md.getSubtyp() == INT_TYP ) {
				// value = value.intValue();
			} else {
				assert( md.getSubtyp() == DOUBLE_TYP ) : "[NumericsItem] INVALID DOUBLE ASSIGNMENT to type: " + md.getSubtyp() + " md=" + md;				
			}
		}
		
		this.value = value;
	}

	@Override
	public Number getValue() {
		return value;
	}

	@Override
	public Number getScaledValue() {
		return (Number)super.getScaledValue();
	}
	
	@Override
	public void clear() {
		value = null;
	}

	public int getSubtyp() {
		return md.getSubtyp();
	}
	
	@Override
	public String toString() {
		return super.toString() + " value=" + value;
	}


}
