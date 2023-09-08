package idea.gui;

import javax.swing.JPanel;

public interface WizardMasterInterface {

	void setFinished(boolean b);

	void pushPage(JPanel panel);
	void popPageUntil(String string);


	void enableNext(boolean b);
	void enablePrevious(boolean b);
	void enableFinish(boolean b);

	// void setCurrentPanel(String name);
	Object getClientProperty(Object key);

	default void requestPage( String name ) {
		// ignore
	}
}
