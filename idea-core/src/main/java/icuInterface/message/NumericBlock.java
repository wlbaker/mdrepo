/**
 * TODO: NJC: Header Documentation
 * 
 * 
 * 
 * $Date: 2012-03-23 07:24:27 -0500 (Fri, 23 Mar 2012) $
 * $Revision: 4289 $
 * $Author: bbaker $
 * $HeadURL: svn://143.83.220.223/DSS/trunk/ICUInterface/src/icuInterface/serverMessages/NumericsBlock.java $
 * $Id: NumericsBlock.java 4289 2012-03-23 12:24:27Z bbaker $
 */

package icuInterface.message;

import icuInterface.PlatformUtil;
import idea.conf.CompositeDescription;
import idea.intf.StreamProducer;
import idea.model.PersistentItem;
import idea.schema.rp.RpMetric;

import java.util.LinkedList;

import lombok.extern.slf4j.Slf4j;

@Slf4j
public class NumericBlock extends AbstractBlock {

	private boolean settings;
	private LinkedList<AbstractItem> nums;

	/** Default Constructor */
	public NumericBlock() {
		this(null, null);
	}

	public NumericBlock(int streamID) {
		super(streamID);
	}

	public NumericBlock(StreamProducer driver) {
		this(driver, null);
	}

	public NumericBlock(StreamProducer driver, RpMetric[] md) {
		this(AbstractBlock.NUMERIC_STREAM, driver, md, PlatformUtil
				.currentTimeMillis());
	}

	public NumericBlock(StreamProducer driver, RpMetric[] md, long tm) {
		this(AbstractBlock.NUMERIC_STREAM, driver, md, tm);
	}

	public NumericBlock(int id, StreamProducer driver, RpMetric[] md) {
		this(id, driver, md, PlatformUtil.currentTimeMillis());
	}

	public NumericBlock(int id, StreamProducer driver, RpMetric[] md,
			long tm) {
		super(driver);
		setStreamID(id);
		setTime(tm);
		if (md != null) {
			for (RpMetric desc : md) {
				add(desc);
			}
		}
	}

	public NumericBlock(PersistentItem item ) {
		super( item.getStreamID() );
		log.error("FIXME: shim incomplete.");
		this.setTime( item.getTime() );
	}

	public boolean isSettings() {
		return settings;
	}

	public void setSettings(boolean s) {
		settings = s;
	}

	public AbstractItem add(RpMetric desc) {
		AbstractItem item = null;
		if (desc instanceof CompositeDescription) {
			item = new CompositeItem((CompositeDescription) desc);
		} else if (desc instanceof RpMetric) {
			item = new NumericItem(desc);
		} else {
			log.error("UNKNOWN ITEM TYPE in NumericsBlock???");
		}
		add(item);
		return item;
	}

	public void add(AbstractItem vdi) {

		add(-1, vdi);
	}

	public void add(int idx, AbstractItem item) {
		if (nums == null) {
			nums = new LinkedList<AbstractItem>();
		}
		if (idx < 0) {
			idx = nums.size();
		}
		nums.add(idx, item);
	}

	/**
	 * @return the vitalsDataItems
	 */
	@Override
	public AbstractItem[] getItems() {
		AbstractItem[] ar = null;
		if (nums != null) {
			ar = new AbstractItem[nums.size()];
			ar = nums.toArray(ar);
		}
		return ar;
	}

	public int getItemCount() {
		if (nums == null) {
			return 0;
		}
		return nums.size();
	}

	@Override
	public AbstractItem getItem(String loc) {

		if (nums == null || loc == null) {
			return null;

		}
		AbstractItem val = null;
		for (AbstractItem item : nums) {
			RpMetric desc = item.getDescription();
			if (loc.equals(desc.getLocation())) {
				val = item;
				break;
			}

			if (loc.equals(desc.getName())) {
				// System.err.println("  -- FOUND BY NAME/ PLEASE FIX " +
				// " name=" + desc.getName());
				val = item;
				break;
			}

			if (loc.equals(desc.getCode())) {
				// System.err.println("  -- FOUND BY CODE/ PLEASE FIX " +
				// " code=" + desc.getCode());
				val = item;
				break;
			}
		}

		return val;
	}

	public AbstractItem getItemByCode(String code) {

		if (nums == null || code == null) {
			return null;

		}
		AbstractItem val = null;
		for (AbstractItem item : nums) {
			RpMetric desc = item.getDescription();

			if (code.equals(desc.getCode())) {
				val = item;
				break;
			}
		}

		return val;
	}

	public void clear() {
		if (nums != null) {
			for (AbstractItem item : nums) {
				item.clear();
			}
		}
	}

	public int size() {

		return (nums == null) ? 0 : nums.size();
	}

	public void setNumericValue(String loc, int val) {
		AbstractItem item = getItem(loc);
		if (item == null) {
			log.error("NUMERICS ITEM does not exist: {}", loc);
			return;
		}

		if (item instanceof NumericItem) {
			NumericItem ni = (NumericItem) item;
			ni.setValue(val);
		} else {
			log.error("Requested set-value is not a numeric item: {}", loc);
		}
	}

	public AbstractItem getItemByPosition(int i) {
		return nums.get(i);
	}

	@Deprecated
	public AbstractItem getItem(Integer iloc) {
		log.warn("deprecated int loc");
		return getItem("" + iloc);
	}

}
