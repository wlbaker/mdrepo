/*
 * Created by JFormDesigner on Wed Nov 15 15:38:03 CST 2017
 */

package idea.studywiz;

import javax.swing.JComboBox;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JPanel;

import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.factories.DefaultComponentFactory;
import com.jgoodies.forms.layout.FormLayout;

import idea.gui.WizardMasterInterface;

/**
 * @author User #1
 */
public class MultimediaPanel extends JPanel {
	private WizardMasterInterface wiz;

	public MultimediaPanel(WizardMasterInterface wiz) {
		this.wiz = wiz;
		initComponents();
		
		populate();
	}

	private void populate() {
		
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		separator1 = compFactory.createSeparator("Multimedia");
		panel1 = new JPanel();
		label1 = new JLabel();
		microphoneCombo = new JComboBox();
		label2 = new JLabel();
		cameraCombo = new JComboBox();

		//======== this ========
		setLayout(new FormLayout(
			"default:grow",
			"2*(default, $lgap), default"));
		add(separator1, CC.xy(1, 1));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"default, $lcgap, right:[50dlu,default], $lcgap, [150dlu,default], $lcgap, default",
				"2*(default, $lgap), default"));

			//---- label1 ----
			label1.setText("Audio:");
			panel1.add(label1, CC.xy(3, 1));
			panel1.add(microphoneCombo, CC.xy(5, 1));

			//---- label2 ----
			label2.setText("Video:");
			panel1.add(label2, CC.xy(3, 3));
			panel1.add(cameraCombo, CC.xy(5, 3));
		}
		add(panel1, CC.xy(1, 3));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	private JComponent separator1;
	private JPanel panel1;
	private JLabel label1;
	private JComboBox microphoneCombo;
	private JLabel label2;
	private JComboBox cameraCombo;
	// JFormDesigner - End of variables declaration  //GEN-END:variables
}
