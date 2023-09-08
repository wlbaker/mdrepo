/*
 * Created by JFormDesigner on Tue Jun 27 09:01:30 CDT 2017
 */

package idea.tsoffline.export;

import java.awt.Desktop;
import java.awt.event.ActionEvent;
import java.io.File;
import java.io.IOException;

import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JPanel;

import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.factories.DefaultComponentFactory;
import com.jgoodies.forms.layout.FormLayout;

import idea.message.StreamID;
import idea.GuiUtil;
import idea.gui.WizardPanelInterface;

/**
 * @author User #1
 */
public class ExportComplete extends JPanel implements WizardPanelInterface {
	private ExportWizard wizard;
	File audio_file;
	private String data_spec;

	public ExportComplete(ExportWizard wiz) {
		initComponents();
		setName("Time Range");

		this.wizard = wiz;

		showFiles(false, false);
	}

	@Override
	public void refresh() {
		data_spec = wizard.getExportSpec();
		dataFile.setText("<html>" + data_spec);
		File f = new File(data_spec);
		view.setEnabled(f.exists());

		audio_file = wizard.getAudioFile();
		audioFile.setText((audio_file == null) ? "" : "<html>" + audio_file);
		listen.setEnabled(audio_file != null);
		audioLabel.setEnabled(audio_file != null);

		wizard.enableFinish(true);
	}

	@Override
	public void previous() {
		// ok?

	}

	@Override
	public boolean next() {
		return true;
	}

	@Override
	public boolean finish() {
		return true;
	}

	private void listenActionPerformed(ActionEvent e) {
		try {
			Desktop.getDesktop().open(audio_file);
		} catch (IOException e1) {
			GuiUtil.showError("Could not open audio file.", e1);
		}
	}

	private void exportDATActionPerformed(ActionEvent e) {
		exportDAT.setEnabled(false);
		
		datWFFile.setText("");
		datVitalsFile.setText("");
		datNotesFile.setText("");
		datAudioFile.setText("");
		datZipFile.setText("");
		
		// reset progress indicator
		// start export thread
		try {
			wizard.exportDAT();
			showFiles(true, false);
		} finally {
			exportDAT.setEnabled(true);
		}
	}
	
	private void showFiles( boolean vis, boolean zvis ) {
		labelDatWF.setVisible( vis );
		datWFFile.setVisible(vis);
		viewDatWF.setVisible( vis );
		
		labelDatVitals.setVisible( vis );
		datVitalsFile.setVisible(vis);
		viewDatVitals.setVisible( vis );
		
		labelDatNotes.setVisible( vis );
		datNotesFile.setVisible(vis);
		viewDatNotes.setVisible( vis );
		
		labelDatAudio.setVisible( vis );
		datAudioFile.setVisible(vis);
		// viewDatAudio.setVisible( vis );
		datZipFile.setVisible(zvis);
		labelDatZip.setVisible(zvis);
		
		zipDatFiles.setEnabled(false);
	}

	private void viewActionPerformed(ActionEvent e) {
		try {
			File f = new File(data_spec);
			Desktop.getDesktop().open(f);
		} catch (IOException e1) {
			GuiUtil.showError("Could not open data file.", e1);
		}
	}

	private void viewDatActionPerformed(ActionEvent e) {
		try {
			File f = new File(datWFFile.getText());
			Desktop.getDesktop().open(f);
		} catch (IOException e1) {
			GuiUtil.showError("Could not open DAT file.", e1);
		}
	}

	private void viewVitalsActionPerformed(ActionEvent e) {
		try {
			File f = new File(datVitalsFile.getText());
			Desktop.getDesktop().open(f);
		} catch (IOException e1) {
			GuiUtil.showError("Could not open vitals file.", e1);
		}
	}

	private void viewNotesActionPerformed(ActionEvent e) {
		try {
			File f = new File(datNotesFile.getText());
			Desktop.getDesktop().open(f);
		} catch (IOException e1) {
			GuiUtil.showError("Could not open notes file.", e1);
		}
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		separator1 = compFactory.createSeparator("Output");
		panel1 = new JPanel();
		label1 = new JLabel();
		dataFile = new JLabel();
		view = new JButton();
		audioLabel = new JLabel();
		audioFile = new JLabel();
		listen = new JButton();
		exportDAT = new JButton();
		labelDatWF = new JLabel();
		datWFFile = new JLabel();
		viewDatWF = new JButton();
		labelDatVitals = new JLabel();
		datVitalsFile = new JLabel();
		viewDatVitals = new JButton();
		labelDatNotes = new JLabel();
		datNotesFile = new JLabel();
		viewDatNotes = new JButton();
		labelDatAudio = new JLabel();
		datAudioFile = new JLabel();
		labelDatZip = new JLabel();
		datZipFile = new JLabel();
		zipDatFiles = new JButton();

		//======== this ========
		setLayout(new FormLayout(
			"default:grow",
			"3*(default, $lgap), default:grow"));
		add(separator1, CC.xy(1, 3));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"20dlu, $lcgap, right:default, $lcgap, default:grow, $lcgap, default",
				"3*(default, $lgap), [20dlu,default], 6*($lgap, default)"));

			//---- label1 ----
			label1.setText("Data:");
			panel1.add(label1, CC.xy(3, 3));

			//---- dataFile ----
			dataFile.setText("datafile");
			panel1.add(dataFile, CC.xy(5, 3));

			//---- view ----
			view.setText("View");
			view.addActionListener(e -> viewActionPerformed(e));
			panel1.add(view, CC.xy(7, 3));

			//---- audioLabel ----
			audioLabel.setText("Audio:");
			panel1.add(audioLabel, CC.xy(3, 5));

			//---- audioFile ----
			audioFile.setText("audiofile");
			panel1.add(audioFile, CC.xy(5, 5));

			//---- listen ----
			listen.setText("Listen");
			listen.addActionListener(e -> listenActionPerformed(e));
			panel1.add(listen, CC.xy(7, 5));

			//---- exportDAT ----
			exportDAT.setText("Export DAT");
			exportDAT.addActionListener(e -> exportDATActionPerformed(e));
			panel1.add(exportDAT, CC.xy(7, 7));

			//---- labelDatWF ----
			labelDatWF.setText("Data/waveform:");
			panel1.add(labelDatWF, CC.xy(3, 9));

			//---- datWFFile ----
			datWFFile.setText("datWFFile");
			panel1.add(datWFFile, CC.xy(5, 9));

			//---- viewDatWF ----
			viewDatWF.setText("View");
			viewDatWF.addActionListener(e -> viewDatActionPerformed(e));
			panel1.add(viewDatWF, CC.xy(7, 9));

			//---- labelDatVitals ----
			labelDatVitals.setText("Data/vitals:");
			panel1.add(labelDatVitals, CC.xy(3, 11));

			//---- datVitalsFile ----
			datVitalsFile.setText("datVitalsFile");
			panel1.add(datVitalsFile, CC.xy(5, 11));

			//---- viewDatVitals ----
			viewDatVitals.setText("View");
			viewDatVitals.addActionListener(e -> viewVitalsActionPerformed(e));
			panel1.add(viewDatVitals, CC.xy(7, 11));

			//---- labelDatNotes ----
			labelDatNotes.setText("Data/notes:");
			panel1.add(labelDatNotes, CC.xy(3, 13));

			//---- datNotesFile ----
			datNotesFile.setText("datNotesFile");
			panel1.add(datNotesFile, CC.xy(5, 13));

			//---- viewDatNotes ----
			viewDatNotes.setText("View");
			viewDatNotes.addActionListener(e -> viewNotesActionPerformed(e));
			panel1.add(viewDatNotes, CC.xy(7, 13));

			//---- labelDatAudio ----
			labelDatAudio.setText("Audio:");
			panel1.add(labelDatAudio, CC.xy(3, 15));

			//---- datAudioFile ----
			datAudioFile.setText("datAudioFile");
			panel1.add(datAudioFile, CC.xy(5, 15));

			//---- labelDatZip ----
			labelDatZip.setText("Zip:");
			panel1.add(labelDatZip, CC.xy(3, 17));

			//---- datZipFile ----
			datZipFile.setText("datZipFile");
			panel1.add(datZipFile, CC.xy(5, 17));

			//---- zipDatFiles ----
			zipDatFiles.setText("Zip-DAT");
			zipDatFiles.setEnabled(false);
			panel1.add(zipDatFiles, CC.xy(7, 17));
		}
		add(panel1, CC.xy(1, 5));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JComponent separator1;
	private JPanel panel1;
	private JLabel label1;
	private JLabel dataFile;
	private JButton view;
	private JLabel audioLabel;
	private JLabel audioFile;
	private JButton listen;
	private JButton exportDAT;
	private JLabel labelDatWF;
	private JLabel datWFFile;
	private JButton viewDatWF;
	private JLabel labelDatVitals;
	private JLabel datVitalsFile;
	private JButton viewDatVitals;
	private JLabel labelDatNotes;
	private JLabel datNotesFile;
	private JButton viewDatNotes;
	private JLabel labelDatAudio;
	private JLabel datAudioFile;
	private JLabel labelDatZip;
	private JLabel datZipFile;
	private JButton zipDatFiles;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	public void setDatFile(StreamID sid, File datFile) {
		String s = (datFile == null) ? "" : datFile.getPath();
		if( sid == StreamID.WAVEFORM ) {
			datWFFile.setText( s );
		} else if ( sid == StreamID.MEASUREMENT ) {
			datVitalsFile.setText( s );
		} else if ( sid == StreamID.AUDIO ) {
			datAudioFile.setText( s );
		} else if ( sid == null || sid == StreamID.ANNOTATION ) {
			datNotesFile.setText( s );
		}
		
	}
}
