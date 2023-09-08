package idea.display;

import idea.model.DisplayConfig;
import idea.schema.rp.RpDevice;

public interface InstrumentDisplayInterface {

	void setDisplay(DisplayConfig display, boolean overwrite, boolean ignoreupdates );

	RpDevice getCapabilities();

	DisplayConfig getDisplay();

	float[] getDisplayData(String loc, float [] arr);

}
