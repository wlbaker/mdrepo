/*
 * Created by JFormDesigner on Tue Oct 18 15:36:00 CDT 2011
 */

package idea.analysis;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JPanel;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.DefaultComponentFactory;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import idea.schema.rp.RpAnalysis;
import idea.schema.rp.RpStudy;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class PulmonaryAnalysisSetupPanel extends JPanel {
	public PulmonaryAnalysisSetupPanel(RpStudy study, RpAnalysis anal) {
		initComponents();
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		separator1 = compFactory.createSeparator("Blood Gas");
		panel3 = new JPanel();
		label6 = new JLabel();
		comboBox3 = new JComboBox();
		label3 = new JLabel();
		comboBox2 = new JComboBox();
		separator2 = compFactory.createSeparator("Ventilator");
		panel2 = new JPanel();
		label1 = new JLabel();
		comboBox1 = new JComboBox();
		label2 = new JLabel();
		label4 = new JLabel();
		label5 = new JLabel();
		panel1 = new JPanel();
		ok = new JButton();
		cancel = new JButton();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout(
			"default:grow",
			"3*(default, $lgap), default:grow, $lgap, default"));
		add(separator1, cc.xy(1, 1));

		//======== panel3 ========
		{
			panel3.setLayout(new FormLayout(
				"right:[50dlu,default], $lcgap, [50dlu,default], $lcgap, default, $lcgap, right:[50dlu,default], $lcgap, left:[50dlu,default]",
				"2*(default, $lgap), default"));

			//---- label6 ----
			label6.setText("Device:");
			panel3.add(label6, cc.xy(1, 3));
			panel3.add(comboBox3, cc.xy(3, 3));

			//---- label3 ----
			label3.setText("PaCO2:");
			panel3.add(label3, cc.xy(7, 3));
			panel3.add(comboBox2, cc.xy(9, 3));
		}
		add(panel3, cc.xy(1, 3));
		add(separator2, cc.xy(1, 5));

		//======== panel2 ========
		{
			panel2.setLayout(new FormLayout(
				"right:[50dlu,default], $lcgap, [50dlu,default], $lcgap, default, $lcgap, right:[50dlu,default], $lcgap, [50dlu,default]",
				"3*(default, $lgap), default"));

			//---- label1 ----
			label1.setText("Device:");
			panel2.add(label1, cc.xy(1, 1));
			panel2.add(comboBox1, cc.xy(3, 1));

			//---- label2 ----
			label2.setText("text");
			panel2.add(label2, cc.xy(1, 3));

			//---- label4 ----
			label4.setText("vCO2/min:");
			panel2.add(label4, cc.xy(7, 3));

			//---- label5 ----
			label5.setText("text");
			panel2.add(label5, cc.xy(7, 5));
		}
		add(panel2, cc.xy(1, 7));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"default:grow, 2*($lcgap, [50dlu,default])",
				"default"));

			//---- ok ----
			ok.setText("Ok");
			panel1.add(ok, cc.xy(3, 1));

			//---- cancel ----
			cancel.setText("Cancel");
			panel1.add(cancel, cc.xy(5, 1));
		}
		add(panel1, cc.xy(1, 9));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JComponent separator1;
	private JPanel panel3;
	private JLabel label6;
	private JComboBox comboBox3;
	private JLabel label3;
	private JComboBox comboBox2;
	private JComponent separator2;
	private JPanel panel2;
	private JLabel label1;
	private JComboBox comboBox1;
	private JLabel label2;
	private JLabel label4;
	private JLabel label5;
	private JPanel panel1;
	private JButton ok;
	private JButton cancel;
	// JFormDesigner - End of variables declaration  //GEN-END:variables
}
