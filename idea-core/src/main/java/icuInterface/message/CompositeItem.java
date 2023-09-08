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

import idea.conf.CompositeDescription;
import idea.schema.rp.RpMetric;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class CompositeItem extends AbstractItem {

	private NumericItem [] values;

	public CompositeItem(CompositeDescription md) {
		super( md );
		RpMetric[] descs = md.getMetrics();
		int count = descs.length;
		values = new NumericItem[count];
		for( int i = 0; i < count ; i++ ) {
			values[i] = new NumericItem(descs[i]);
		}
	}
	
	public int getCount() {
		return values.length;
	}

	public NumericItem[] getValues() {
		return values;
	}
	
	public void setValue(int[] value) {
		log.error("CompositeItem...not expect setValue");
		// this.value = value;
	}

	@Override
	public Number getValue() {
		return null;
	}

	@Override
	public Number getScaledValue() {
		return null;
	}
	
	@Override
	public void clear() {
		for( NumericItem value : values ) {
			value.clear();
		}
	}

	public int getSubtyp() {
		return md.getSubtyp();
	}
	
	@Override
	public String toString() {
		return super.toString() + " value=" + values;
	}

	public void setValue(int i, int val) {
		values[i].setValue(val);
	}

	public Number getValue(int i) {
		return values[i].getValue();
	}

}
