/*
 * Created by JFormDesigner on Wed Nov 30 16:43:06 CST 2011
 */

package idea.gui;

import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JPanel;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import idea.GuiUtil;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class DefaultOkCancelPanel extends JPanel {
	boolean did_ok = false;
	
	public DefaultOkCancelPanel( Component subpanel ) {
		initComponents();
		
		add( subpanel, BorderLayout.CENTER );
	}

	private void okActionPerformed(ActionEvent e) {
		did_ok = true;
		cancelActionPerformed( null );
	}
	
	public boolean isOk() {
		return did_ok;
	}

	private void cancelActionPerformed(ActionEvent e) {
		GuiUtil.closeDialog( this );
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		panel1 = new JPanel();
		ok = new JButton();
		cancel = new JButton();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new BorderLayout());

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"default:grow, $lcgap, default, 2*($lcgap, [50dlu,default])",
				"default"));

			//---- ok ----
			ok.setText("Ok");
			ok.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					okActionPerformed(e);
				}
			});
			panel1.add(ok, cc.xy(5, 1));

			//---- cancel ----
			cancel.setText("Cancel");
			cancel.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					cancelActionPerformed(e);
				}
			});
			panel1.add(cancel, cc.xy(7, 1));
		}
		add(panel1, BorderLayout.SOUTH);
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JPanel panel1;
	private JButton ok;
	private JButton cancel;
	// JFormDesigner - End of variables declaration  //GEN-END:variables
}
