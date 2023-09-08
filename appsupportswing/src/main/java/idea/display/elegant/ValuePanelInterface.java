package idea.display.elegant;

import java.awt.Color;

import idea.schema.rp.RpMetric;

public interface ValuePanelInterface {
	public void addParameter(RpMetric desc);
	public void clear();
	public boolean containsLoc(String loc);
	public void setColor( Color color );
	public void setValue(RpMetric desc, Object item);
}
