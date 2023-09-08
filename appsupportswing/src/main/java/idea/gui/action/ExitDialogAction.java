package idea.gui.action;

import java.awt.Container;
import java.awt.event.ActionEvent;

import javax.swing.AbstractAction;
import javax.swing.JDialog;
import javax.swing.JOptionPane;


@SuppressWarnings("serial")
public class ExitDialogAction extends AbstractAction {
	public static void exitDialog( Container c ) {
		JDialog dlg = null;
		JOptionPane op = null;
		do {
			if(c instanceof JDialog) {
				dlg = (JDialog)c;
				break;
			}
			//if(c instanceof JOptionPane) {
			//	op = (JOptionPane)c;
			//	break;
			//}
			c = c.getParent();
		} while( c != null );
		
		if( dlg != null ) {
			dlg.dispose();
		}		
		if( op != null ) {
			op.setVisible( false );
		}		
	}
	
	public void actionPerformed(ActionEvent e) {

        Container c = (Container)e.getSource();
        exitDialog(c);
	}

	public ExitDialogAction(String s) {
		super(s);
	}

}
