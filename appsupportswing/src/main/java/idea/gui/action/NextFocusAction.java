package idea.gui.action;

import java.awt.Component;
import java.awt.DefaultKeyboardFocusManager;
import java.awt.FocusTraversalPolicy;
import java.awt.KeyboardFocusManager;
import java.awt.event.ActionEvent;

import javax.swing.AbstractAction;
import javax.swing.Action;
import javax.swing.JComponent;
import javax.swing.JTextArea;

import idea.GuiUtil;


@SuppressWarnings("serial")
public class NextFocusAction extends AbstractAction {
	public void actionPerformed(ActionEvent e2) {

		// KeyEvent event = (KeyEvent) e2.getSource();
		// KeyStroke ks = KeyStroke.getKeyStrokeForEvent((KeyEvent) event);

		// Object source = e.getSource() ...hm. This is usually the frame.
		DefaultKeyboardFocusManager focusManager = (DefaultKeyboardFocusManager) KeyboardFocusManager
				.getCurrentKeyboardFocusManager();
		Component source = focusManager.getFocusOwner();

		boolean ignoreEvent = false;

		if (source instanceof JComponent) {
			JComponent comp = (JComponent) source;
			if (comp instanceof JTextArea) {
				ignoreEvent = true;
			} else {
				Action enterAction = GuiUtil.getEnterAction(comp);
				if (enterAction != null) {
					enterAction.actionPerformed(e2);
				}
//				FormInterface form = DDD.getAutosaveForm(comp);
//				if (form != null) {
//					if (form instanceof EditableFormInterface) {
//						((EditableFormInterface) form).save();
//						ignoreEvent = true;
//					}
//				}
			}
		}

		if (!ignoreEvent) {
			FocusTraversalPolicy policy = focusManager.getDefaultFocusTraversalPolicy();
			focusManager.focusNextComponent();
		}

		setEnabled(true);
	}

	public NextFocusAction(String s) {
		super(s);
	}
}