/*
 * Created by JFormDesigner on Tue May 15 08:01:23 CDT 2012
 */

package idea.resources_obs;

import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.SwingConstants;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

/**
 * @author User #2
 */
public class Ftmp extends JPanel {
	public Ftmp(JPanel left, JPanel right) {
		initComponents();
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		panel1 = new JPanel();
		label1 = new JLabel();
		panel2 = new JPanel();
		uomLabel = new JLabel();
		label2 = new JLabel();
		scaled0 = new JLabel();
		panel_92 = new JPanel();
		labelCode92a = new JLabel();
		labelCode92b = new JLabel();
		scaled92a = new JLabel();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setLayout(new FormLayout(
			"100dlu, $lcgap, 160dlu",
			"2*(fill:100dlu, $lgap), default"));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"right:default:grow",
				"default:grow"));

			//---- label1 ----
			label1.setText("text");
			panel1.add(label1, cc.xy(1, 1));
		}
		add(panel1, cc.xy(1, 1));

		//======== panel2 ========
		{
			panel2.setLayout(new FormLayout(
				"[80dlu,default]:grow, $lcgap, 50dlu",
				"default, $lgap, fill:default:grow"));

			//---- uomLabel ----
			uomLabel.setText("text");
			panel2.add(uomLabel, cc.xy(1, 1));

			//---- label2 ----
			label2.setText("text");
			panel2.add(label2, cc.xy(3, 1));

			//---- scaled0 ----
			scaled0.setText("text");
			scaled0.setHorizontalAlignment(SwingConstants.TRAILING);
			panel2.add(scaled0, cc.xy(1, 3));
		}
		add(panel2, cc.xy(3, 1));

		//======== panel_92 ========
		{
			panel_92.setLayout(new FormLayout(
				"default:grow, $lcgap, default:grow",
				"default, $lgap, fill:default:grow, $lgap, 15dlu"));

			//---- labelCode92a ----
			labelCode92a.setText("text");
			panel_92.add(labelCode92a, cc.xy(1, 1));

			//---- labelCode92b ----
			labelCode92b.setText("text");
			panel_92.add(labelCode92b, cc.xy(3, 1));

			//---- scaled92a ----
			scaled92a.setText("text");
			scaled92a.setHorizontalAlignment(SwingConstants.TRAILING);
			panel_92.add(scaled92a, cc.xy(1, 3));
		}
		add(panel_92, cc.xy(3, 3));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JPanel panel1;
	private JLabel label1;
	private JPanel panel2;
	private JLabel uomLabel;
	private JLabel label2;
	private JLabel scaled0;
	private JPanel panel_92;
	private JLabel labelCode92a;
	private JLabel labelCode92b;
	private JLabel scaled92a;
	// JFormDesigner - End of variables declaration  //GEN-END:variables
}
