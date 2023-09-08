package idea;

import java.awt.AWTEvent;
import java.awt.Component;
import java.awt.EventQueue;
import java.awt.Toolkit;
import java.awt.Window;
import java.awt.event.ActionEvent;
import java.awt.event.KeyEvent;

import javax.swing.Action;
import javax.swing.ActionMap;
import javax.swing.InputMap;
import javax.swing.JTextField;
import javax.swing.KeyStroke;

public class GlobalHotkeyManager extends EventQueue {
	private static final GlobalHotkeyManager instance = new GlobalHotkeyManager();
	public static final Object IGNORE_HOTKEY = "IGNORE_HOTKEY";
	
	private final InputMap keyStrokes = new InputMap();
	private final ActionMap actions = new ActionMap();
	static {
		// here we register ourselves as a new link in the chain of
		// responsibility
		Toolkit.getDefaultToolkit().getSystemEventQueue().push(instance);
	}

	private GlobalHotkeyManager() {
	} // One is enough - singleton

	public static GlobalHotkeyManager getInstance() {
		return instance;
	}

	public InputMap getInputMap() {
		return keyStrokes;
	}

	public ActionMap getActionMap() {
		return actions;
	}

	protected void dispatchEvent(AWTEvent event) {
		if (event instanceof KeyEvent) {
			// KeyStroke.getKeyStrokeForEvent converts an ordinary KeyEvent
			// to a keystroke, as stored in the InputMap. Keep in mind that
			// Numpad keystrokes are different to ordinary keys, i.e. if you
			// are listening to
			KeyStroke ks = KeyStroke.getKeyStrokeForEvent((KeyEvent) event);
			String actionKey = (String) keyStrokes.get(ks);

			if( actionKey != null ) {
				if (ks.getKeyEventType() == KeyEvent.KEY_TYPED) {

						Action action = actions.get(actionKey);

						Window src = (Window) event.getSource();
						Component dest = src.getFocusOwner();
						if( dest instanceof JTextField ) {
							JTextField tf = (JTextField)dest;
							Object ignoreHotkey = tf.getClientProperty( IGNORE_HOTKEY );
							if( ignoreHotkey != null ) {
								action = null;
							}
						}
						
						if (action != null && action.isEnabled()) {
							// I'm not sure about the parameters
							action.actionPerformed(new ActionEvent( event, event.getID(), actionKey,
									((KeyEvent) event).getModifiers()));

							if( action.isEnabled() ) {
								KeyEvent ke = (KeyEvent)event;
								ke.consume();
							}
						}
				} else if ( ks.getKeyChar() != '\n' ){
					// first, check to see if the dest component implements a key action
					
					// if not, then we might provide one.
					Action action = actions.get(actionKey);
					if (action != null && action.isEnabled()) {
						// I'm not sure about the parameters
						action.actionPerformed(new ActionEvent( event, event.getID(), actionKey,
								((KeyEvent) event).getModifiers()));
					}
				}
			}
		}
		super.dispatchEvent(event); // let the next in chain handle event
	}
}