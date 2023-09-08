/*
 * Created by JFormDesigner on Tue Mar 05 11:37:13 CST 2013
 */

package idea.adapters.gui;

import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.SwingConstants;

import com.jgoodies.forms.factories.DefaultComponentFactory;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

/**
 * @author User #1
 */
public class BisPanel extends JPanel {
	public BisPanel() {
		initComponents();
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		headerPanel = new JPanel();
		sqiPanel = new JPanel();
		label1 = new JLabel();
		label6 = new JLabel();
		label2 = new JLabel();
		label7 = new JLabel();
		eeg1Panel = new JPanel();
		label4 = new JLabel();
		eeg2Panel = new JPanel();
		label3 = new JLabel();
		separator1 = compFactory.createSeparator("Artifacts");
		panel4 = new JPanel();
		label5 = new JLabel();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setLayout(new FormLayout(
			"default:grow",
			"fill:default, 2*($lgap, default), $rgap, default, $lgap, fill:default:grow, $lgap, default"));

		//======== headerPanel ========
		{
			headerPanel.setLayout(new FormLayout(
				"[80dlu,default], $lcgap, default, $lcgap, default:grow",
				"fill:[80dlu,default]"));

			//======== sqiPanel ========
			{
				sqiPanel.setLayout(new FormLayout(
					"[20dlu,default], $lcgap, default:grow, $lcgap, [20dlu,default], $lcgap, default:grow",
					"fill:default:grow, $lgap, fill:default:grow"));

				//---- label1 ----
				label1.setText("SQI");
				sqiPanel.add(label1, cc.xy(1, 1, CellConstraints.DEFAULT, CellConstraints.TOP));

				//---- label6 ----
				label6.setText("SR");
				sqiPanel.add(label6, cc.xy(5, 1, CellConstraints.DEFAULT, CellConstraints.TOP));

				//---- label2 ----
				label2.setText("EMG");
				sqiPanel.add(label2, cc.xy(1, 3, CellConstraints.DEFAULT, CellConstraints.TOP));

				//---- label7 ----
				label7.setText("BISALT");
				sqiPanel.add(label7, cc.xy(5, 3));
			}
			headerPanel.add(sqiPanel, cc.xy(5, 1));
		}
		add(headerPanel, cc.xy(1, 1));

		//======== eeg1Panel ========
		{
			eeg1Panel.setLayout(new FormLayout(
				"[50dlu,default], $lcgap, default:grow",
				"fill:[50dlu,default]"));

			//---- label4 ----
			label4.setText("EEG1:");
			eeg1Panel.add(label4, cc.xy(1, 1, CellConstraints.DEFAULT, CellConstraints.TOP));
		}
		add(eeg1Panel, cc.xy(1, 3));

		//======== eeg2Panel ========
		{
			eeg2Panel.setLayout(new FormLayout(
				"[50dlu,default], $lcgap, default:grow",
				"fill:[50dlu,default]"));

			//---- label3 ----
			label3.setText("EEG2:");
			eeg2Panel.add(label3, cc.xy(1, 1, CellConstraints.DEFAULT, CellConstraints.TOP));
		}
		add(eeg2Panel, cc.xy(1, 5));
		add(separator1, cc.xy(1, 7));

		//======== panel4 ========
		{
			panel4.setLayout(new FormLayout(
				"[50dlu,default], $lcgap, default:grow",
				"fill:default:grow"));

			//---- label5 ----
			label5.setText("Artifacts...");
			label5.setVerticalAlignment(SwingConstants.TOP);
			panel4.add(label5, cc.xy(3, 1));
		}
		add(panel4, cc.xy(1, 9));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JPanel headerPanel;
	private JPanel sqiPanel;
	private JLabel label1;
	private JLabel label6;
	private JLabel label2;
	private JLabel label7;
	private JPanel eeg1Panel;
	private JLabel label4;
	private JPanel eeg2Panel;
	private JLabel label3;
	private JComponent separator1;
	private JPanel panel4;
	private JLabel label5;
	// JFormDesigner - End of variables declaration  //GEN-END:variables
}
