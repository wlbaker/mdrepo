/**
 * TODO: NJC: Header Documentation
 * 
 * 
 * 
 * $Date: 2010-08-24 08:05:30 -0500 (Tue, 24 Aug 2010) $
 * $Revision: 10 $
 * $Author: ntl $
 */

package icuInterface.message;

import java.util.Date;

import idea.schema.rp.RpMetric;

public class DateItem extends AbstractItem {

	private Date value;

	public DateItem(RpMetric md) {
		super( md );
	}

	public void setValue(Date value) {
		this.value = value;
	}

	@Override
	public Date getValue() {
		return value;
	}

	@Override
	public void clear() {
		value = null;
	}


}
