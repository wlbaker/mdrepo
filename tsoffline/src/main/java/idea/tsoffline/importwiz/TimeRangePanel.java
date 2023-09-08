/*
 * Created by JFormDesigner on Mon Jan 31 10:23:42 CST 2011
 */

package idea.tsoffline.importwiz;

import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JPanel;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.DefaultComponentFactory;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import idea.gui.WizardPanelInterface;

/**
 * @author User #2
 */
public class TimeRangePanel extends JPanel implements WizardPanelInterface {
	private Object wiz;
	public TimeRangePanel(ImportWizard importWizard) {
		initComponents();

		this.wiz = wiz;
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		separator1 = compFactory.createSeparator("Time Selection");
		panel1 = new JPanel();
		label1 = new JLabel();
		label2 = new JLabel();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout(
			"default:grow",
			"default, $rgap, fill:default:grow"));
		add(separator1, cc.xy(1, 1));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"right:default, $lcgap, default",
				"4*(default, $lgap), default"));

			//---- label1 ----
			label1.setText("Start Time:");
			panel1.add(label1, cc.xy(1, 3));

			//---- label2 ----
			label2.setText("End Time:");
			panel1.add(label2, cc.xy(1, 7));
		}
		add(panel1, cc.xy(1, 3));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	private JComponent separator1;
	private JPanel panel1;
	private JLabel label1;
	private JLabel label2;
	// JFormDesigner - End of variables declaration  //GEN-END:variables
	@Override
	public void refresh() {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void previous() {
		// TODO Auto-generated method stub
		
	}

	@Override
	public boolean next() {
		// TODO Auto-generated method stub
		return true;
	}

	@Override
	public boolean finish() {
		// TODO Auto-generated method stub
		return false;
	}
}
