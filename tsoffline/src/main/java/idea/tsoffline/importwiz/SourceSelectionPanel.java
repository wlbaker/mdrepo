/*
 * Created by JFormDesigner on Fri Jan 14 08:22:52 CST 2011
 */

package idea.tsoffline.importwiz;

import javax.swing.ButtonGroup;
import javax.swing.ButtonModel;
import javax.swing.JComponent;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

import com.jgoodies.forms.factories.DefaultComponentFactory;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import lombok.extern.slf4j.Slf4j;
import idea.gui.WizardPanelInterface;

/**
 * @author User #2
 */
@Slf4j
@SuppressWarnings("serial")
public class SourceSelectionPanel extends JPanel implements WizardPanelInterface, ChangeListener {
	public static final String FILE_SELECTION = "File Selection";
	public static final String EVENTS_SELECTION = "Events File";
	public static final String DEVICE_SELECTION = "Device Selection";
	private ButtonGroup buttonGroup;
	private ImportWizard wiz;

	public SourceSelectionPanel( ImportWizard wiz) {
		initComponents();

		this.wiz = wiz;
		
		wiz.enableFinish(false);
		wiz.enableNext(true);

		ButtonModel selection = buttonGroup.getSelection();
		if (selection != null) {
			
			// this is my expectation
			selection.addChangeListener(this);
		} else {
			// this is the reality....dunno!
			signalFromFile.addChangeListener(this);
			signalFromDevice.addChangeListener(this);
			signalFromRepository.addChangeListener(this);
			studyEvents.addChangeListener(this);
		}
		
		wiz.enableNext( false );
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		separator1 = compFactory.createSeparator("Import Source");
		panel1 = new JPanel();
		signalFromFile = new JRadioButton();
		signalFromDevice = new JRadioButton();
		signalFromRepository = new JRadioButton();
		studyEvents = new JRadioButton();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setLayout(new FormLayout(
			"default:grow",
			"3*(default, $lgap), default"));
		add(separator1, cc.xy(1, 3));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"[50dlu,default], $lcgap, [200dlu,default]:grow",
				"6*(default, $lgap), default"));

			//---- signalFromFile ----
			signalFromFile.setText("Signal from a file");
			panel1.add(signalFromFile, cc.xy(3, 1));

			//---- signalFromDevice ----
			signalFromDevice.setText("Signal from a device");
			panel1.add(signalFromDevice, cc.xy(3, 5));

			//---- signalFromRepository ----
			signalFromRepository.setText("Signal from repository");
			panel1.add(signalFromRepository, cc.xy(3, 9));

			//---- studyEvents ----
			studyEvents.setText("Study events");
			studyEvents.setEnabled(false);
			panel1.add(studyEvents, cc.xy(3, 13));
		}
		add(panel1, cc.xy(1, 7));

		//---- buttonGroup1 ----
		ButtonGroup buttonGroup1 = new ButtonGroup();
		buttonGroup1.add(signalFromFile);
		buttonGroup1.add(signalFromDevice);
		buttonGroup1.add(signalFromRepository);
		buttonGroup1.add(studyEvents);
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
	private JRadioButton signalFromDevice;
	private JRadioButton signalFromRepository;
	private JRadioButton studyEvents;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	@Override
	public boolean finish() {
		return false;
	}

	@Override
	public boolean next() {
		boolean ok = true;
		return ok;
	}

	@Override
	public void previous() {
		// TODO Auto-generated method stub

	}

	@Override
	public void refresh() {
		ImportWizard wiz = ImportWizard.getInstance();

		wiz.enableNext(false);
		wiz.enableFinish(false);

	}

	@Override
	public void stateChanged(ChangeEvent e) {
		ImportWizard wiz = ImportWizard.getInstance();
		log.info("BUTTON CHANGE!");
		ButtonModel s = buttonGroup.getSelection();
		if( s != null ) {
			Object[] objs = s.getSelectedObjects();
			log.info("objs={}", objs);
			wiz.enableNext( true );
		} else {
			wiz.enableNext( false );
		}
	}

	public String getNextPage() {
		String selection = "";
		if (signalFromFile.isSelected()) {
			selection = FILE_SELECTION;
		} else if (signalFromDevice.isSelected()) {
			selection = DEVICE_SELECTION;
		} else if (studyEvents.isSelected()) {
			selection = EVENTS_SELECTION;
		} else {
			assert (false) : "unexpected inport source";
		}

		return selection;
	}
}
