/*
 * Created by JFormDesigner on Mon Feb 06 13:07:49 CST 2017
 */

package idea.tsoffline.wiz;

import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.factories.DefaultComponentFactory;
import com.jgoodies.forms.layout.FormLayout;

/**
 * @author User #1
 */
public class BeatStatsDetailPanel extends JPanel {
	public BeatStatsDetailPanel() {
		initComponents();
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		separator1 = compFactory.createSeparator("Beat Detail");
		panel1 = new JPanel();
		label1 = new JLabel();
		layerName = new JTextField();

		//======== this ========
		setLayout(new FormLayout(
			"default:grow",
			"4*(default, $lgap), default"));
		add(separator1, CC.xy(1, 1));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"2*(default, $lcgap), [80dlu,default]",
				"2*(default, $lgap), default"));

			//---- label1 ----
			label1.setText("Layer Name:");
			panel1.add(label1, CC.xy(3, 1));
			panel1.add(layerName, CC.xy(5, 1));
		}
		add(panel1, CC.xy(1, 3));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	private JComponent separator1;
	private JPanel panel1;
	private JLabel label1;
	private JTextField layerName;
	// JFormDesigner - End of variables declaration  //GEN-END:variables
}
