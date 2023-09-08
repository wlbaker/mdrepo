/*
 * Created by JFormDesigner on Mon Apr 02 09:07:57 CDT 2012
 */

package idea.tsoffline.codes_editor;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.FocusAdapter;
import java.awt.event.FocusEvent;

import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;
import com.toedter.calendar.JDateChooser;

import idea.GuiUtil;
import idea.tsoffline.persist.EventItem;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class SingleEventPanel extends JPanel {
	private EventItem event;
	private boolean ok_selected;
	public SingleEventPanel( EventItem event ) {
		initComponents();
		
		this.event = event;
		
		code.setText( event.getCode() );
		description.setText( event.getDesc() );
		dateChooser.setDate( event.getTm() );
	}

	private void okActionPerformed(ActionEvent e) {
		ok_selected = true;
		event.setCode( code.getText( ) );
		event.setDesc( description.getText( ) );
		event.setTm( dateChooser.getDate( ) );
		cancelActionPerformed( null );
	}

	private void cancelActionPerformed(ActionEvent e) {
		GuiUtil.closeDialog(this);
	}

	private void startTimeChooserFocusLost(FocusEvent e) {
		// TODO add your code here
	}

	public boolean isOk() {
		return ok_selected;
	}
	
	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		panel1 = new JPanel();
		label1 = new JLabel();
		code = new JTextField();
		label3 = new JLabel();
		description = new JTextField();
		label2 = new JLabel();
		dateChooser = new JDateChooser();
		panel2 = new JPanel();
		ok = new JButton();
		cancel = new JButton();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout(
			"default:grow",
			"default, $lgap, top:default:grow, $lgap, default"));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"right:default, 2*($lcgap, [50dlu,default])",
				"3*(default, $lgap), default"));

			//---- label1 ----
			label1.setText("Code:");
			panel1.add(label1, cc.xy(1, 1));
			panel1.add(code, cc.xy(3, 1));

			//---- label3 ----
			label3.setText("Description:");
			panel1.add(label3, cc.xy(1, 3));
			panel1.add(description, cc.xywh(3, 3, 3, 1));

			//---- label2 ----
			label2.setText("Date/Time:");
			panel1.add(label2, cc.xy(1, 5));

			//---- dateChooser ----
			dateChooser.setDateFormatString("MM/dd/yyyy HH:mm:ss");
			dateChooser.addFocusListener(new FocusAdapter() {
				@Override
				public void focusLost(FocusEvent e) {
					startTimeChooserFocusLost(e);
				}
			});
			panel1.add(dateChooser, cc.xywh(3, 5, 3, 1));
		}
		add(panel1, cc.xy(1, 3));

		//======== panel2 ========
		{
			panel2.setLayout(new FormLayout(
				"default:grow, 2*($lcgap, [50dlu,default])",
				"default"));

			//---- ok ----
			ok.setText("OK");
			ok.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					okActionPerformed(e);
				}
			});
			panel2.add(ok, cc.xy(3, 1));

			//---- cancel ----
			cancel.setText("Cancel");
			cancel.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					cancelActionPerformed(e);
				}
			});
			panel2.add(cancel, cc.xy(5, 1));
		}
		add(panel2, cc.xy(1, 5));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JPanel panel1;
	private JLabel label1;
	private JTextField code;
	private JLabel label3;
	private JTextField description;
	private JLabel label2;
	private JDateChooser dateChooser;
	private JPanel panel2;
	private JButton ok;
	private JButton cancel;
	// JFormDesigner - End of variables declaration  //GEN-END:variables
}
