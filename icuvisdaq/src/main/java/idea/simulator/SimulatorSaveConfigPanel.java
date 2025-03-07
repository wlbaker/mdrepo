/*
 * Created by JFormDesigner on Thu May 26 13:27:25 CDT 2011
 */

package idea.simulator;


import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;

import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JFileChooser;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;
import jakarta.xml.bind.JAXBContext;
import jakarta.xml.bind.JAXBElement;
import jakarta.xml.bind.JAXBException;
import jakarta.xml.bind.Marshaller;

import idea.GuiUtil;
import idea.PrefUtil;
import idea.gui.WizardPanelInterface;
import idea.meddaq.AppSetup;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.DefaultComponentFactory;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import idea.schema.rp.ObjectFactory;
import idea.schema.rp.RpAnalysis;
import idea.schema.rp.RpStudy;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class SimulatorSaveConfigPanel extends JPanel implements WizardPanelInterface {
	private RpAnalysis analysis;
	private RpStudy study;

	public SimulatorSaveConfigPanel(SimulatorWizard wiz, RpStudy study, RpAnalysis analysis) {
		initComponents();
		setName("Save");

		this.study = study;
		this.analysis = analysis;

		wiz.enableNext(false);
		wiz.enableFinish(true);
	}

	private void saveActionPerformed(ActionEvent e) {
		try {
			_saveActionPerformed(e);
		} catch (Exception exc) {
			GuiUtil.showError("Save Config", exc);
		}
	}

	private void _saveActionPerformed(ActionEvent e) throws InstantiationException, IllegalAccessException,
			JAXBException {
		String fname = fileName.getText();
		File studyf = new File(fname);
		// File studyf = new File(subf, "study.xml");

		ObjectFactory factory = ObjectFactory.class.newInstance();
		JAXBContext jaxbContext = JAXBContext.newInstance("idea.schema.rp");

		Marshaller marshaller = jaxbContext.createMarshaller();
		marshaller.setProperty(Marshaller.JAXB_FORMATTED_OUTPUT, Boolean.TRUE);

		JAXBElement<RpStudy> out = factory.createRpStudyImpl(study);

		marshaller.marshal(out, studyf);
	}

	private void browseActionPerformed(ActionEvent e) {
		File parent = null;
		String lastDir = fileName.getText();
		if (lastDir.length() == 0) {
			lastDir = PrefUtil.getUserPref(AppSetup.getAnalysisFile(), null);
		}
		if (lastDir != null) {
			parent = new File(lastDir);
		}

		GuiUtil.doOpenFileChooser(JFileChooser.FILES_AND_DIRECTORIES, "Save Analysis", this, parent, new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				File file = (File) e.getSource();
				fileName.setText(file.getAbsolutePath());
			}
		});
	}

	@Override
	public boolean finish() {
		return false;
	}

	@Override
	public boolean next() {
		// unused!
		assert( false ) : "cannot go past last item";
		return false;
	}

	@Override
	public void previous() {
		// handled automatically
	}

	@Override
	public void refresh() {
		// TODO Auto-generated method stub

	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		separator1 = compFactory.createSeparator("Save Configuration");
		panel1 = new JPanel();
		label1 = new JLabel();
		fileName = new JTextField();
		browse = new JButton();
		save = new JButton();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout(
			"default:grow",
			"2*(default, $lgap), default"));
		add(separator1, cc.xy(1, 1));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"right:[80dlu,default], $lcgap, [150dlu,default], 2*($lcgap, default)",
				"[12dlu,default], 3*($lgap, default)"));

			//---- label1 ----
			label1.setText("File Name:");
			panel1.add(label1, cc.xy(1, 3));
			panel1.add(fileName, cc.xy(3, 3));

			//---- browse ----
			browse.setText("Browse");
			browse.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					browseActionPerformed(e);
				}
			});
			panel1.add(browse, cc.xy(5, 3));

			//---- save ----
			save.setText("Save");
			save.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					saveActionPerformed(e);
				}
			});
			panel1.add(save, cc.xy(5, 7));
		}
		add(panel1, cc.xy(1, 3));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JComponent separator1;
	private JPanel panel1;
	private JLabel label1;
	private JTextField fileName;
	private JButton browse;
	private JButton save;
	// JFormDesigner - End of variables declaration //GEN-END:variables

}
