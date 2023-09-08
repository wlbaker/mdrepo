/*
 * Created by JFormDesigner on Fri Jan 14 08:22:52 CST 2011
 */

package idea.tsoffline.wiz;

import java.awt.Font;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;

import javax.swing.ButtonGroup;
import javax.swing.ButtonModel;
import javax.swing.JComponent;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.factories.DefaultComponentFactory;
import com.jgoodies.forms.layout.FormLayout;

import idea.gui.WizardMasterInterface;
import idea.gui.WizardPanelInterface;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class MethodSelectionPanel extends JPanel implements WizardPanelInterface, ChangeListener, ItemListener {
	private ButtonGroup buttonGroup;
	private WizardMasterInterface wiz;

	private Font normal;
	private Font bold;

	public MethodSelectionPanel(WizardMasterInterface wiz) {
		initComponents();
		this.wiz = wiz;
		setName("Source Selection");

		wiz.enableFinish(false);

		signalFromFile.setSelected(true);
		normal = signalFromFile.getFont();
		if (normal == null) {
			normal = new Font("Courier", Font.BOLD, 12);
		}
		bold = normal.deriveFont(normal.getStyle() | Font.BOLD);

		wiz.enableNext(true);

		ButtonModel selection = buttonGroup.getSelection();
		if (selection != null) {

			// this is my expectation
			selection.addChangeListener(this);
		} else {
			// this is the reality....dunno!
			signalFromFile.addChangeListener(this);
			signalFromRemote.addChangeListener(this);
			signalFromDevice.addChangeListener(this);
		}

		signalFromFile.addItemListener(this);
		signalFromRemote.addItemListener(this);
		signalFromDevice.addItemListener(this);

		wiz.enableNext(false);
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		separator1 = compFactory.createSeparator("Select the Data Source");
		panel1 = new JPanel();
		signalFromFile = new JRadioButton();
		signalFromRemote = new JRadioButton();
		signalFromDevice = new JRadioButton();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout(
			"default:grow",
			"2*(default, $lgap), [20dlu,default], $lgap, default"));
		add(separator1, CC.xy(1, 3));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"[50dlu,default], $lcgap, [300dlu,default]",
				"4*(default, $lgap), default"));

			//---- signalFromFile ----
			signalFromFile.setText("Local file");
			panel1.add(signalFromFile, CC.xy(3, 1));

			//---- signalFromRemote ----
			signalFromRemote.setText("Remote file");
			panel1.add(signalFromRemote, CC.xy(3, 5));

			//---- signalFromDevice ----
			signalFromDevice.setText("Study");
			panel1.add(signalFromDevice, CC.xy(3, 9));
		}
		add(panel1, CC.xy(1, 7));

		//---- buttonGroup1 ----
		ButtonGroup buttonGroup1 = new ButtonGroup();
		buttonGroup1.add(signalFromFile);
		buttonGroup1.add(signalFromRemote);
		buttonGroup1.add(signalFromDevice);
		// //GEN-END:initComponents

		// added because JFormDesigner doesn't (currently)
		// create the button group as a field variable
		buttonGroup = buttonGroup1;
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JComponent separator1;
	private JPanel panel1;
	private JRadioButton signalFromFile;
	private JRadioButton signalFromRemote;
	private JRadioButton signalFromDevice;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	@Override
	public boolean finish() {
		return true;
	}

	@Override
	public boolean next() {
		return true;
	}

	@Override
	public void previous() {
		// TODO Auto-generated method stub

	}

	@Override
	public void refresh() {

		stateChanged(null);
		wiz.enableFinish(false);

	}

	@Override
	public void itemStateChanged(ItemEvent e) {
		System.out.println("isc: " + e);
		stateChanged(null);
	}

	@Override
	public void stateChanged(ChangeEvent e) {
		System.out.println("--sc" + e);
		ButtonModel s = buttonGroup.getSelection();
		if (s != null) {
			wiz.enableNext(true);
		} else {
			wiz.enableNext(false);
		}

		hilight(signalFromFile);
		hilight(signalFromRemote);
		hilight(signalFromDevice);
	}

	private void hilight(JRadioButton r) {
		// bold
		if (r.isSelected()) {
			r.setFont(bold);
		} else {
			r.setFont(normal);
		}
		// r.setForeground( r.isSelected() ? hilight_color : normal_color );
		r.repaint();
	}

	public boolean isSignalFromFile() {
		return signalFromFile.isSelected();
	}

	public boolean isSignalFromDevice() {
		return signalFromDevice.isSelected();
	}

	public boolean isSignalFromRemote() {
		return signalFromRemote.isSelected();
	}

}
