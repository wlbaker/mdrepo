/*
 * Created by JFormDesigner on Mon Oct 05 13:52:41 CDT 2009
 */

package idea.devwizard;

import idea.driver.AlphaDisplay;
import idea.schema.rp.RpDevice;
import idea.gui.WizardMasterInterface;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class WizAlphaDisplayPanel extends WizAbstractDisplayPanel {
	public WizAlphaDisplayPanel( WizardMasterInterface wizard, RpDevice conf ) {
		super(wizard, conf, AlphaDisplay.class, new String[] { "2-line" } );

	}
}
