package idea.tsoffline;

import java.awt.Dimension;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import javax.swing.JFrame;
import javax.swing.JTextField;

public class T implements KeyListener, MouseListener {


	// Uncomment this if you wish to turn off focus
	// traversal. The focus subsystem consumes
	// focus traversal keys, such as Tab and Shift Tab.
	// If you uncomment the following line of code, this
	// disables focus traversal and the Tab events
	// become available to the key event listener.
	// typingArea.setFocusTraversalKeysEnabled(false);

	/** Handle the key typed event from the text field. */
	public void keyTyped(KeyEvent e) {
		displayInfo(e, "KEY TYPED: ");
	}

	/** Handle the key-pressed event from the text field. */
	public void keyPressed(KeyEvent e) {
		displayInfo(e, "KEY PRESSED: ");
	}

	/** Handle the key-released event from the text field. */
	public void keyReleased(KeyEvent e) {
		displayInfo(e, "KEY RELEASED: ");
	}

	private void displayInfo(KeyEvent e, String keyStatus) {

		// You should only rely on the key char if the event
		// is a key typed event.
		int id = e.getID();
		String keyString;
		if (id == KeyEvent.KEY_TYPED) {
			char c = e.getKeyChar();
			keyString = "key character = '" + c + "'";
		} else {
			int keyCode = e.getKeyCode();
			keyString = "key code = " + keyCode + " (" + KeyEvent.getKeyText(keyCode) + ")";
		}
		
		int modifiersEx = e.getModifiersEx();
		String modString = "extended modifiers = " + modifiersEx;
		String tmpString = KeyEvent.getModifiersExText(modifiersEx);
		if (tmpString.length() > 0) {
			modString += " (" + tmpString + ")";
		} else {
			modString += " (no extended modifiers)";
		}

		String actionString = "action key? ";
		if (e.isActionKey()) {
			actionString += "YES";
		} else {
			actionString += "NO";
		}

		String locationString = "key location: ";
		int location = e.getKeyLocation();
		if (location == KeyEvent.KEY_LOCATION_STANDARD) {
			locationString += "standard";
		} else if (location == KeyEvent.KEY_LOCATION_LEFT) {
			locationString += "left";
		} else if (location == KeyEvent.KEY_LOCATION_RIGHT) {
			locationString += "right";
		} else if (location == KeyEvent.KEY_LOCATION_NUMPAD) {
			locationString += "numpad";
		} else { // (location == KeyEvent.KEY_LOCATION_UNKNOWN)
			locationString += "unknown";
		}

		System.out.println( keyString + ", " + modString + ", " + actionString + "," + locationString);

		// Display information about the KeyEvent...
	}
	
	@Override
	public void mouseClicked(MouseEvent arg0) {
		System.out.println("mouseClicked: " + arg0 );
	}

	@Override
	public void mouseEntered(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseExited(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mousePressed(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseReleased(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}
	static public void main( String [] args ) throws Exception {

		TsPluginAPI plugin = new idea.tsoffline.jog.PluginController();
		plugin.initPlugin( null );
		
		T t = new T();
		JFrame f = new JFrame();
		f.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );
		// where initialization occurs:
		JTextField typingArea = new JTextField(20);
		typingArea.addKeyListener( t );
		f.add( typingArea );
		typingArea.setMinimumSize( new Dimension( 300, 20));
		f.pack();
		
		
		f.setVisible(true);
	}

}
