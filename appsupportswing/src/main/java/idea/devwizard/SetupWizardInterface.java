package idea.devwizard;

import idea.schema.rp.RpStudy;
import idea.gui.WizardMasterInterface;

/*
 * 
 * NOTICE: This class should go the way of the DODO.  Use the WizardMasterInterface only.  This
 * class exist because data storage (the model) was not handled generically enough in earlier
 * incarnations, and has to be reworked.  This is a temp fix until the rework to generalize.
 * 
 */
public interface SetupWizardInterface extends WizardMasterInterface {


	RpStudy getStudy();

}
