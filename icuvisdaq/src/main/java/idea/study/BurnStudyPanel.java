/*
 * Created by JFormDesigner on Wed Apr 20 11:42:05 CDT 2011
 */

package idea.study;

import javax.swing.ButtonGroup;
import javax.swing.JCheckBox;
import javax.swing.JFormattedTextField;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.SwingConstants;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;
import com.toedter.calendar.JDateChooser;

/**
 * @author User #2
 */
public class BurnStudyPanel extends JPanel {
	public BurnStudyPanel() {
		initComponents();
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		label2 = new JLabel();
		scrollPane1 = new JScrollPane();
		textArea1 = new JTextArea();
		label1 = new JLabel();
		panel1 = new JPanel();
		radioButton1 = new JRadioButton();
		radioButton2 = new JRadioButton();
		label3 = new JLabel();
		panel2 = new JPanel();
		formattedTextField1 = new JFormattedTextField();
		label4 = new JLabel();
		panel5 = new JPanel();
		formattedTextField2 = new JFormattedTextField();
		label5 = new JLabel();
		panel6 = new JPanel();
		formattedTextField3 = new JFormattedTextField();
		label6 = new JLabel();
		panel3 = new JPanel();
		textField1 = new JTextField();
		label7 = new JLabel();
		panel4 = new JPanel();
		dateChooser1 = new JDateChooser();
		label8 = new JLabel();
		panel7 = new JPanel();
		dateChooser2 = new JDateChooser();
		label9 = new JLabel();
		panel8 = new JPanel();
		checkBox1 = new JCheckBox();
		label10 = new JLabel();
		panel9 = new JPanel();
		formattedTextField4 = new JFormattedTextField();
		label11 = new JLabel();
		panel10 = new JPanel();
		formattedTextField5 = new JFormattedTextField();
		label12 = new JLabel();
		panel11 = new JPanel();
		formattedTextField6 = new JFormattedTextField();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout(
			"right:[80dlu,default], $rgap, [250dlu,default]:grow",
			"default, $lgap, fill:[30dlu,default]:grow, 2*($lgap, default), $rgap, 9*(default, $lgap), default"));

		//---- label2 ----
		label2.setText("Medical History:");
		label2.setVerticalAlignment(SwingConstants.TOP);
		add(label2, cc.xy(1, 3));

		//======== scrollPane1 ========
		{

			//---- textArea1 ----
			textArea1.setName("hist");
			scrollPane1.setViewportView(textArea1);
		}
		add(scrollPane1, cc.xy(3, 3));

		//---- label1 ----
		label1.setText("Gender:");
		add(label1, cc.xy(1, 5));

		//======== panel1 ========
		{
			panel1.setName("sex");
			panel1.setLayout(new FormLayout(
				"2*(default, $lcgap), default",
				"default"));

			//---- radioButton1 ----
			radioButton1.setText("Male");
			radioButton1.setName("M");
			panel1.add(radioButton1, cc.xy(3, 1));

			//---- radioButton2 ----
			radioButton2.setText("Female");
			radioButton2.setName("F");
			panel1.add(radioButton2, cc.xy(5, 1));
		}
		add(panel1, cc.xy(3, 5));

		//---- label3 ----
		label3.setText("% Burn:");
		add(label3, cc.xy(1, 7));

		//======== panel2 ========
		{
			panel2.setLayout(new FormLayout(
				"[50dlu,default], $lcgap, default",
				"default"));

			//---- formattedTextField1 ----
			formattedTextField1.setName("pct_burn");
			panel2.add(formattedTextField1, cc.xy(1, 1));
		}
		add(panel2, cc.xy(3, 7));

		//---- label4 ----
		label4.setText("% Full Thickness Burn:");
		add(label4, cc.xy(1, 9));

		//======== panel5 ========
		{
			panel5.setLayout(new FormLayout(
				"[50dlu,default], $lcgap, default",
				"default"));

			//---- formattedTextField2 ----
			formattedTextField2.setName("pct_fullthickness");
			panel5.add(formattedTextField2, cc.xy(1, 1));
		}
		add(panel5, cc.xy(3, 9));

		//---- label5 ----
		label5.setText("Pre-admin Fluids(ml):");
		add(label5, cc.xy(1, 11));

		//======== panel6 ========
		{
			panel6.setLayout(new FormLayout(
				"[50dlu,default], $lcgap, default",
				"default"));

			//---- formattedTextField3 ----
			formattedTextField3.setName("fluids");
			panel6.add(formattedTextField3, cc.xy(1, 1));
		}
		add(panel6, cc.xy(3, 11));

		//---- label6 ----
		label6.setText("Cause of Burn:");
		add(label6, cc.xy(1, 13));

		//======== panel3 ========
		{
			panel3.setLayout(new FormLayout(
				"[150dlu,default], $lcgap, default",
				"default"));

			//---- textField1 ----
			textField1.setName("cb");
			panel3.add(textField1, cc.xy(1, 1));
		}
		add(panel3, cc.xy(3, 13));

		//---- label7 ----
		label7.setText("Time of Burn:");
		add(label7, cc.xy(1, 15));

		//======== panel4 ========
		{
			panel4.setLayout(new FormLayout(
				"default, $lcgap, default",
				"default"));

			//---- dateChooser1 ----
			dateChooser1.setName("tofburn");
			dateChooser1.setDateFormatString("MM/dd/yyyy HH:mm:ss");
			panel4.add(dateChooser1, cc.xy(1, 1));
		}
		add(panel4, cc.xy(3, 15));

		//---- label8 ----
		label8.setText("Time of Admission:");
		add(label8, cc.xy(1, 17));

		//======== panel7 ========
		{
			panel7.setLayout(new FormLayout(
				"default, $lcgap, default",
				"default"));

			//---- dateChooser2 ----
			dateChooser2.setName("tofadmin");
			dateChooser2.setDateFormatString("MM/dd/yyyy HH:mm:ss");
			panel7.add(dateChooser2, cc.xy(1, 1));
		}
		add(panel7, cc.xy(3, 17));

		//---- label9 ----
		label9.setText("Inhalation Injury:");
		add(label9, cc.xy(1, 19));

		//======== panel8 ========
		{
			panel8.setLayout(new FormLayout(
				"default, $lcgap, default",
				"default"));

			//---- checkBox1 ----
			checkBox1.setText("Yes");
			checkBox1.setName("inh_injury");
			panel8.add(checkBox1, cc.xy(1, 1));
		}
		add(panel8, cc.xy(3, 19));

		//---- label10 ----
		label10.setText("Age:");
		add(label10, cc.xy(1, 21));

		//======== panel9 ========
		{
			panel9.setLayout(new FormLayout(
				"[50dlu,default], $lcgap, default",
				"default"));

			//---- formattedTextField4 ----
			formattedTextField4.setName("age");
			panel9.add(formattedTextField4, cc.xy(1, 1));
		}
		add(panel9, cc.xy(3, 21));

		//---- label11 ----
		label11.setText("Height:");
		add(label11, cc.xy(1, 23));

		//======== panel10 ========
		{
			panel10.setLayout(new FormLayout(
				"[50dlu,default], $lcgap, default",
				"default"));

			//---- formattedTextField5 ----
			formattedTextField5.setName("height");
			panel10.add(formattedTextField5, cc.xy(1, 1));
		}
		add(panel10, cc.xy(3, 23));

		//---- label12 ----
		label12.setText("Weight:");
		add(label12, cc.xy(1, 25));

		//======== panel11 ========
		{
			panel11.setLayout(new FormLayout(
				"[50dlu,default], $lcgap, default",
				"default"));

			//---- formattedTextField6 ----
			formattedTextField6.setName("weight");
			panel11.add(formattedTextField6, cc.xy(1, 1));
		}
		add(panel11, cc.xy(3, 25));

		//---- buttonGroup1 ----
		ButtonGroup buttonGroup1 = new ButtonGroup();
		buttonGroup1.add(radioButton1);
		buttonGroup1.add(radioButton2);
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	private JLabel label2;
	private JScrollPane scrollPane1;
	private JTextArea textArea1;
	private JLabel label1;
	private JPanel panel1;
	private JRadioButton radioButton1;
	private JRadioButton radioButton2;
	private JLabel label3;
	private JPanel panel2;
	private JFormattedTextField formattedTextField1;
	private JLabel label4;
	private JPanel panel5;
	private JFormattedTextField formattedTextField2;
	private JLabel label5;
	private JPanel panel6;
	private JFormattedTextField formattedTextField3;
	private JLabel label6;
	private JPanel panel3;
	private JTextField textField1;
	private JLabel label7;
	private JPanel panel4;
	private JDateChooser dateChooser1;
	private JLabel label8;
	private JPanel panel7;
	private JDateChooser dateChooser2;
	private JLabel label9;
	private JPanel panel8;
	private JCheckBox checkBox1;
	private JLabel label10;
	private JPanel panel9;
	private JFormattedTextField formattedTextField4;
	private JLabel label11;
	private JPanel panel10;
	private JFormattedTextField formattedTextField5;
	private JLabel label12;
	private JPanel panel11;
	private JFormattedTextField formattedTextField6;
	// JFormDesigner - End of variables declaration  //GEN-END:variables
}
