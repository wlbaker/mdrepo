/*
 * Created by JFormDesigner on Tue Dec 16 09:29:25 CST 2014
 */

package idea.tsoffline.prefs;

import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JRadioButton;

import com.jgoodies.forms.factories.DefaultComponentFactory;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

/**
 * @author User #1
 */
public class EditorPrefsPage extends JPanel {
	public EditorPrefsPage() {
		initComponents();
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		separator1 = compFactory.createSeparator("Grid Lines");
		panel1 = new JPanel();
		label1 = new JLabel();
		radioButton1 = new JRadioButton();
		radioButton2 = new JRadioButton();
		radioButton3 = new JRadioButton();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setLayout(new FormLayout(
			"20dlu, $lcgap, default:grow",
			"5*(default, $lgap), default"));
		add(separator1, cc.xywh(1, 3, 3, 1));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"default, $lcgap, default:grow",
				"3*(default, $lgap), default"));

			//---- label1 ----
			label1.setText("Grid Lines:");
			panel1.add(label1, cc.xy(1, 1));

			//---- radioButton1 ----
			radioButton1.setText("None");
			panel1.add(radioButton1, cc.xy(3, 3));

			//---- radioButton2 ----
			radioButton2.setText("Zero");
			panel1.add(radioButton2, cc.xy(3, 5));
			panel1.add(radioButton3, cc.xy(3, 7));
		}
		add(panel1, cc.xy(3, 5));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JComponent separator1;
	private JPanel panel1;
	private JLabel label1;
	private JRadioButton radioButton1;
	private JRadioButton radioButton2;
	private JRadioButton radioButton3;
	// JFormDesigner - End of variables declaration  //GEN-END:variables
}
