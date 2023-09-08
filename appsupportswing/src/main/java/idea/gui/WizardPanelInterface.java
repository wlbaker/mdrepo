package idea.gui;

public interface WizardPanelInterface {

	public void refresh();

	public void previous();
	public boolean next();
	public boolean finish();
	
	default public void dump () { };
	
	// for javaFX
	default public void setWizard(WizardMasterInterface wizard) { };
}
