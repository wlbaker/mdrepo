/*
 * Created by JFormDesigner on Fri Apr 16 12:30:26 CDT 2010
 */

package idea.tsoffline.export;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;

import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JComponent;
import javax.swing.JFileChooser;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.factories.DefaultComponentFactory;
import com.jgoodies.forms.layout.FormLayout;

import idea.persistence.PiSubjectImporter;
import idea.GuiUtil;
import idea.PrefUtil;
import idea.gui.WizardPanelInterface;
import idea.meddaq.AppSetup;
import idea.tsoffline.TsOfflineSetup;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class ExportDestinationPanel extends JPanel implements WizardPanelInterface {

	private ExportWizard wizard;

	public ExportDestinationPanel(ExportWizard wiz) {
		initComponents();
		setName("Time Range");

		this.wizard = wiz;

		String uri = TsOfflineSetup.getConnectionURI(); // PrefUtil.getUserPref(pref_key,
														// null);
		if (uri != null) {
			connectionURI.setText(uri);
		}

		mergeOption.setSelected(PrefUtil.getUserPref("merge_option", "true").equals("true"));
		audioOption.setSelected(PrefUtil.getUserPref("audio_option", "true").equals("true"));
		annotationOption.setSelected(PrefUtil.getUserPref("anno_option", "true").equals("true"));
		
		String dirName = PrefUtil.getUserPref("export_dir", System.getProperty("user.dir"));
		
		File dir = new File(dirName);
		while( dir.isDirectory() == false  ) {
			File p = dir.getParentFile();
			if( p == null ) {
				break;
			}
			dir = p;
		}
		
		File dest = new File(dir, "${SUBJECT}_${START_TIME}.xlsx");
		filePath.setText( dest.getAbsolutePath() );
	}

	public void refresh(PiSubjectImporter importer) throws IOException {

	}

	private void browseActionPerformed(ActionEvent e) {
		File parent = null;
		String lastDir = PrefUtil.getUserPref(AppSetup.getLocalRepositoryDir(), null);
		if (lastDir != null) {
			parent = new File(lastDir);
		}

		GuiUtil.doOpenFileChooser(JFileChooser.DIRECTORIES_ONLY, "Export Directory", this, parent,
				new ActionListener() {

					@Override
					public void actionPerformed(ActionEvent e) {
						File dir = (File) e.getSource();
						File pre = new File(filePath.getText());
						File post = new File( dir, pre.getName() );
						filePath.setText(post.getAbsolutePath());
					}
				});
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		separator2 = compFactory.createSeparator("Destination");
		panel3 = new JPanel();
		fileCheckbox = new JCheckBox();
		filePath = new JTextField();
		browse = new JButton();
		dreOutput = new JCheckBox();
		dreFilePath = new JTextField();
		label10 = new JLabel();
		panel1 = new JPanel();
		hdf5Checkbox = new JCheckBox();
		jdbcCheckbox = new JCheckBox();
		label1 = new JLabel();
		connectionURI = new JTextField();
		label9 = new JLabel();
		separator1 = compFactory.createSeparator("Options");
		panel2 = new JPanel();
		mergeOption = new JCheckBox();
		audioOption = new JCheckBox();
		annotationOption = new JCheckBox();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout(
			"default:grow",
			"6*(default, $lgap), default"));
		add(separator2, CC.xy(1, 1));

		//======== panel3 ========
		{
			panel3.setLayout(new FormLayout(
				"20dlu, $lcgap, 50dlu, $lcgap, [30dlu,default], $lcgap, default:grow, $lcgap, default",
				"default, $rgap, 2*(default, $lgap), default"));

			//---- fileCheckbox ----
			fileCheckbox.setText("XLSX Files");
			panel3.add(fileCheckbox, CC.xywh(3, 1, 3, 1));

			//---- filePath ----
			filePath.setText("${SUBJECT}_${START_TIME}.xlsx");
			panel3.add(filePath, CC.xy(7, 1));

			//---- browse ----
			browse.setText("Browse");
			browse.addActionListener(e -> browseActionPerformed(e));
			panel3.add(browse, CC.xy(9, 1));

			//---- dreOutput ----
			dreOutput.setText("DRE Files");
			dreOutput.setSelected(true);
			panel3.add(dreOutput, CC.xywh(3, 3, 3, 1));

			//---- dreFilePath ----
			dreFilePath.setText("c:\\tmp\\${SUBJECT}_${START_TIME}.dat");
			panel3.add(dreFilePath, CC.xy(7, 3));

			//---- label10 ----
			label10.setText("Hint:  c:\\tmp\\${SUBJECT}_${START_TIME}_Modified_${USER}${TODAY}.xlsx");
			panel3.add(label10, CC.xywh(5, 5, 3, 1));
		}
		add(panel3, CC.xy(1, 3));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"20dlu, $lcgap, [50dlu,default], $lcgap, right:[30dlu,default], $lcgap, [150dlu,default], $lcgap, default, $lcgap, default:grow",
				"3*(default, $lgap), default"));

			//---- hdf5Checkbox ----
			hdf5Checkbox.setText("HDF5 File");
			panel1.add(hdf5Checkbox, CC.xy(3, 1));

			//---- jdbcCheckbox ----
			jdbcCheckbox.setText("Database");
			panel1.add(jdbcCheckbox, CC.xy(3, 3));

			//---- label1 ----
			label1.setText("JDBC:");
			panel1.add(label1, CC.xy(5, 3));
			panel1.add(connectionURI, CC.xy(7, 3));

			//---- label9 ----
			label9.setText("Hint:  jdbc:sqlite:/c:/tmp/file${SUBJECT}_${START_TIME}.db");
			panel1.add(label9, CC.xywh(5, 5, 7, 1));
		}
		add(panel1, CC.xy(1, 5));
		add(separator1, CC.xy(1, 9));

		//======== panel2 ========
		{
			panel2.setLayout(new FormLayout(
				"20dlu, $lcgap, default, $lcgap, right:[30dlu,default], $lcgap, [150dlu,default], $lcgap, default:grow",
				"3*(default, $lgap), default"));

			//---- mergeOption ----
			mergeOption.setText("Merge");
			panel2.add(mergeOption, CC.xy(3, 1));

			//---- audioOption ----
			audioOption.setText("Audio");
			audioOption.setSelected(true);
			panel2.add(audioOption, CC.xy(3, 3));

			//---- annotationOption ----
			annotationOption.setText("Annotations");
			annotationOption.setSelected(true);
			annotationOption.setEnabled(false);
			panel2.add(annotationOption, CC.xy(3, 5));
		}
		add(panel2, CC.xy(1, 11));

		//---- buttonGroup1 ----
		ButtonGroup buttonGroup1 = new ButtonGroup();
		buttonGroup1.add(fileCheckbox);
		buttonGroup1.add(dreOutput);
		buttonGroup1.add(hdf5Checkbox);
		buttonGroup1.add(jdbcCheckbox);
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JComponent separator2;
	private JPanel panel3;
	private JCheckBox fileCheckbox;
	private JTextField filePath;
	private JButton browse;
	private JCheckBox dreOutput;
	private JTextField dreFilePath;
	private JLabel label10;
	private JPanel panel1;
	private JCheckBox hdf5Checkbox;
	private JCheckBox jdbcCheckbox;
	private JLabel label1;
	private JTextField connectionURI;
	private JLabel label9;
	private JComponent separator1;
	private JPanel panel2;
	private JCheckBox mergeOption;
	private JCheckBox audioOption;
	private JCheckBox annotationOption;
	// JFormDesigner - End of variables declaration //GEN-END:variables
	@Override
	public boolean finish() {
		return false;
	}

	@Override
	public boolean next() {

		PrefUtil.saveUserPref("merge_option", "" + mergeOption.isSelected());
		PrefUtil.saveUserPref("audio_option", "" + audioOption.isSelected());
		PrefUtil.saveUserPref("anno_option", "" + audioOption.isSelected());
		PrefUtil.saveUserPref("export_dir", filePath.getText() );
		return true;
	}

	@Override
	public void refresh() {
		wizard.enableNext(true);
	}

	@Override
	public void previous() {
		// TODO Auto-generated method stub
	}

	public boolean isFileOutput() {
		return fileCheckbox.isSelected();
	}

	public boolean isDreOutput() {
		return dreOutput.isSelected();
	}

	public boolean isJDBCOutput() {
		return jdbcCheckbox.isSelected();
	}

	public String getJDBCConnectionURI() {
		return connectionURI.getText();
	}

	public String getFilePath() {
		return filePath.getText();
	}

	public boolean getMergeOption() {
		return mergeOption.isSelected();
	}

	public void hasAudio(boolean b) {
		audioOption.setEnabled( b );
		audioOption.setSelected( b );
	}
	
	public boolean hasAudio() {
		return audioOption.isSelected( );
	}

	public String getDreOutputFile() {
		return dreFilePath.getText();
	}

	public boolean isHdf5Output() {
		return hdf5Checkbox.isSelected();
	}
	
	public String getHdf5OutputFile() {
		return "c:\\tmp\\zero.h5";
	}

}
