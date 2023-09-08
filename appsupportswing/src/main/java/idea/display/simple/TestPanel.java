/*
 * Created by JFormDesigner on Sun Jun 10 15:53:28 CDT 2012
 */

package idea.display.simple;

import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.SwingConstants;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

/**
 * @author User #2
 */
public class TestPanel extends JPanel {
	public TestPanel() {
		initComponents();
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		label1 = new JLabel();
		label3 = new JLabel();
		label2 = new JLabel();
		paramCode1 = new JLabel();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setLayout(new FormLayout(
			"right:[15dlu,default]:grow, $lcgap, default, $lcgap, [15dlu,default]:grow",
			"default:grow, $lgap, default, $nlgap, default"));

		//---- label1 ----
		label1.setText("text");
		add(label1, cc.xy(1, 1));

		//---- label3 ----
		label3.setText(":");
		add(label3, cc.xy(3, 1));

		//---- label2 ----
		label2.setText("text");
		add(label2, cc.xy(5, 1));

		//---- paramCode1 ----
		paramCode1.setText("text");
		paramCode1.setHorizontalAlignment(SwingConstants.CENTER);
		add(paramCode1, cc.xywh(1, 3, 5, 1));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JLabel label1;
	private JLabel label3;
	private JLabel label2;
	private JLabel paramCode1;
	// JFormDesigner - End of variables declaration  //GEN-END:variables
}
