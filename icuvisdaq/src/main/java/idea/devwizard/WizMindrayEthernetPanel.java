/*
 * Created by JFormDesigner on Mon Oct 05 13:52:41 CDT 2009
 */

package idea.devwizard;

import icuInterface.adapters.MindrayNetworkDriver;
import idea.schema.rp.RpDevice;
import idea.gui.WizardMasterInterface;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class WizMindrayEthernetPanel extends WizRefreshablePanel {
	public WizMindrayEthernetPanel(WizardMasterInterface wizard, RpDevice conf) {
		super( wizard, conf, MindrayNetworkDriver.class.getCanonicalName() );
	}

}
