/*
 * Created by JFormDesigner on Sun Feb 28 12:37:54 CST 2010
 */

package idea.tsoffline.importwiz;


import javax.swing.JLabel;
import javax.swing.JPanel;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import idea.GuiUtil;
import idea.gui.WizardPanelInterface;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class StudyErrorPanel extends JPanel implements WizardPanelInterface {

	public StudyErrorPanel( String message_text ) {
		initComponents();
		setName( "Error");

		refresh();
		
		message.setText( message_text );
	}
	
	


	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		message = new JLabel();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout(
			"default:grow",
			"default, $lgap, fill:default:grow, $lgap, default"));

		//---- message ----
		message.setText("text");
		add(message, cc.xy(1, 3));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JLabel message;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	@Override
	public boolean finish() {
		return false;
	}

	@Override
	public boolean next() {
		GuiUtil.closeDialog( this );
		return true;
	}

	@Override
	public void refresh() {
	}




	@Override
	public void previous() {
		// TODO Auto-generated method stub
		
	}
}
