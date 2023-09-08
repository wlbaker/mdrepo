package idea.meddaq.entry;

import idea.intf.DataTyp;
import idea.model.ModelUtil;
import idea.model.PersistentItem;

import java.util.Arrays;
import java.util.LinkedList;

import lombok.extern.slf4j.Slf4j;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpLinearUnit;
import idea.schema.rp.RpMetric;

@Slf4j
public class EntrySheet {

	private static int model_idx = 0;
	private LinkedList<String> timepoints;
	private LinkedList<EntryItem> items;
	private String name;

	Class<? extends PersistentItem> model;

	public EntrySheet(String name, LinkedList<EntryItem> items, LinkedList<String> item_timepoints) {
		setItems(items);
		setName(name);
		setTimepoints(item_timepoints);
	}

	private void setTimepoints(LinkedList<String> timepoints) {
		this.timepoints = timepoints;
	}

	public void setItems(LinkedList<EntryItem> items) {
		this.items = items;
	}

	public LinkedList<EntryItem> getItems() {
		return items;
	}

	private void setName(String name) {
		this.name = name;
	}

	public String getName() {
		return name;
	}

	public LinkedList<String> getTimepoints() {
		return timepoints;
	}

	public RpDevice getDevice() {
		// TODO Auto-generated method stub
		return null;
	}

	public Class<? extends PersistentItem> getDataModel() {

		if (model == null) {

			RpMetric[] metrics = new RpMetric[items.size() + 1];
			int idx = 0;
			metrics[idx++] = new RpMetric("TPOINT", null, "Timepoint", null, DataTyp.STRING_TYP);
			for (EntryItem item : items) {
				RpMetric md = new RpMetric(item.getDestLoc(), item.getDevValue(), item.getPrompt(), RpLinearUnit.unit,
						DataTyp.INT_TYP);
				metrics[idx++] = md;
			}
			
			try {
				model_idx++;
				model = ModelUtil.createDynamicModel("ENTRY_" + model_idx, Arrays.asList(metrics) );
			} catch (Exception e) {
				log.error("Could not create model.");
			}
		}

		return model;
	}

}
