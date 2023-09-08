/*
 * Created by JFormDesigner on Mon Oct 05 13:52:41 CDT 2009
 */

package idea.devwizard;

import idea.driver.InfinityDriver;
import idea.schema.rp.RpDevice;
import idea.gui.WizardMasterInterface;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class WizInfinityPanel extends WizRefreshablePanel {
	public WizInfinityPanel(WizardMasterInterface wizard, RpDevice conf) {
		super( wizard, conf, InfinityDriver.class.getCanonicalName() );
	}

}
