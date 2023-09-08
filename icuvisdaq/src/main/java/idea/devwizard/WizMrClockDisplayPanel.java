/*
 * Created by JFormDesigner on Mon Oct 05 13:52:41 CDT 2009
 */

package idea.devwizard;


import icuInterface.adapters.MrClockDriver;
import idea.schema.rp.RpDevice;
import idea.gui.WizardMasterInterface;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class WizMrClockDisplayPanel extends WizAbstractDisplayPanel {
	public WizMrClockDisplayPanel( WizardMasterInterface wizard, RpDevice conf ) {
		super(wizard, conf, MrClockDriver.class, new String[] { "2-line" } );

	}
}
