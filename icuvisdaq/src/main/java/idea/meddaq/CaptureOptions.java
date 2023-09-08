/*
 * Created by JFormDesigner on Fri Jan 20 15:08:36 CST 2012
 */

package idea.meddaq;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.*;

import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;
import com.jgoodies.forms.factories.*;

import idea.GuiUtil;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.DefaultComponentFactory;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class CaptureOptions extends JPanel {
	public CaptureOptions() {
		initComponents();
	}

	private void okActionPerformed(ActionEvent e) {
		cancelActionPerformed(e);
	}

	private void cancelActionPerformed(ActionEvent e) {
		GuiUtil.closeDialog(this);
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		separator1 = compFactory.createSeparator("Movie Capture Options");
		panel3 = new JPanel();
		label4 = new JLabel();
		checkBox1 = new JCheckBox();
		label1 = new JLabel();
		comboBox1 = new JComboBox();
		separator2 = compFactory.createSeparator("Screen Capture Options");
		panel2 = new JPanel();
		label6 = new JLabel();
		checkBox2 = new JCheckBox();
		label2 = new JLabel();
		comboBox2 = new JComboBox();
		label3 = new JLabel();
		panel1 = new JPanel();
		ok = new JButton();
		cancel = new JButton();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout(
			"default:grow",
			"3*(default, $lgap), fill:default:grow, $lgap, default"));
		add(separator1, CC.xy(1, 1));

		//======== panel3 ========
		{
			panel3.setLayout(new FormLayout(
				"[50dlu,default], $lcgap, right:default, $lcgap, [150dlu,default]",
				"2*(default, $lgap), default"));

			//---- label4 ----
			label4.setText("Prompt:");
			panel3.add(label4, CC.xy(3, 1));

			//---- checkBox1 ----
			checkBox1.setText("Yes");
			panel3.add(checkBox1, CC.xy(5, 1));

			//---- label1 ----
			label1.setText("Device:");
			panel3.add(label1, CC.xy(3, 3));
			panel3.add(comboBox1, CC.xy(5, 3));
		}
		add(panel3, CC.xy(1, 3));
		add(separator2, CC.xy(1, 5));

		//======== panel2 ========
		{
			panel2.setLayout(new FormLayout(
				"right:[50dlu,default], $lcgap, right:default, $lcgap, [150dlu,default]",
				"2*(default, $lgap), default"));

			//---- label6 ----
			label6.setText("Prompt:");
			panel2.add(label6, CC.xy(3, 1));

			//---- checkBox2 ----
			checkBox2.setText("Yes");
			panel2.add(checkBox2, CC.xy(5, 1));

			//---- label2 ----
			label2.setText("Device:");
			panel2.add(label2, CC.xy(3, 3));
			panel2.add(comboBox2, CC.xy(5, 3));

			//---- label3 ----
			label3.setText("Capture Type:  Screen / App / Device / Prompt");
			panel2.add(label3, CC.xy(5, 5));
		}
		add(panel2, CC.xy(1, 7));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"default:grow, 2*($lcgap, [50dlu,default])",
				"default"));

			//---- ok ----
			ok.setText("Ok");
			ok.addActionListener(e -> okActionPerformed(e));
			panel1.add(ok, CC.xy(3, 1));

			//---- cancel ----
			cancel.setText("Cancel");
			cancel.addActionListener(e -> cancelActionPerformed(e));
			panel1.add(cancel, CC.xy(5, 1));
		}
		add(panel1, CC.xy(1, 9));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	private JComponent separator1;
	private JPanel panel3;
	private JLabel label4;
	private JCheckBox checkBox1;
	private JLabel label1;
	private JComboBox comboBox1;
	private JComponent separator2;
	private JPanel panel2;
	private JLabel label6;
	private JCheckBox checkBox2;
	private JLabel label2;
	private JComboBox comboBox2;
	private JLabel label3;
	private JPanel panel1;
	private JButton ok;
	private JButton cancel;
	// JFormDesigner - End of variables declaration  //GEN-END:variables
}
