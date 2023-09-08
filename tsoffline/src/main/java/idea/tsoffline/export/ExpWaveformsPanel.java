/*
 * Created by JFormDesigner on Fri Apr 16 12:30:26 CDT 2010
 */

package idea.tsoffline.export;


import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.util.LinkedList;
import java.util.Map;
import java.util.prefs.BackingStoreException;

import javax.swing.DefaultComboBoxModel;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JComboBox;
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
import idea.schema.rp.RpMetric;
import idea.GuiUtil;
import idea.PrefUtil;
import idea.gui.WizardPanelInterface;
import idea.tsoffline.TsOfflineSetup;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class ExpWaveformsPanel extends JPanel implements WizardPanelInterface {

	private ExpSignalSelectionPanel signalPanel;
	private ExportWizard wiz;
	
	public ExpWaveformsPanel(ExportWizard wiz) {
		initComponents();
		setName( "Waveforms" );
		
		this.wiz = wiz;

		GuiUtil.initPanel(this);

		dir.setText(TsOfflineSetup.getWaveExportDir());
		resampleMethod.setSelectedIndex( TsOfflineSetup.getResampleMethod() );
		
		sigSelectionHolder.add( signalPanel = new ExpSignalSelectionPanel(wiz, false, true), BorderLayout.CENTER );

	}

	public void refresh(PiSubjectImporter importer) {
		signalPanel.refresh(importer);
		
		defaultFilenameActionPerformed(null);
		
		wiz.enableNext( true );
	}

	private void browseActionPerformed(ActionEvent e) {
		File parent = null;
		String lastDir = dir.getText();
		if( lastDir.length() == 0 ) {
			lastDir = PrefUtil.getUserPref(TsOfflineSetup.getExportDir(), null);
		}
		if (lastDir != null) {
			parent = new File(lastDir);
		}

		GuiUtil.doOpenFileChooser(JFileChooser.FILES_AND_DIRECTORIES, "Waveform Export Directory", this, parent, new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				File file = (File) e.getSource();
				dir.setText(file.getAbsolutePath());
			}
		});
	}

	private void saveActionPerformed(ActionEvent e) {

		try {
			TsOfflineSetup.setWaveExportDir(dir.getText());

//			TsOfflineSetup.setRemoteRepositoryUser(username.getText());
//
//			String s_password = new String(password.getPassword());
//			TsOfflineSetup.setRemoteRepositoryPwd(s_password);
			
//			TsOfflineSetup.setMerge( merge.isSelected() );
			// TsOfflineSetup.setResampleMethod( resampleMethod.getSelectedIndex() );
			
			// TsOfflineSetup.setMetricInterval( (Integer.parseInt(ar[0])) * 1000 );

		} catch (Exception ee) {
			GuiUtil.showError("Export Data Format: ", ee);
		}
	}

	private void defaultFilenameActionPerformed(ActionEvent e) {
		String s = TsOfflineSetup.getArchiveFile();
		File f = new File(s);
		if (f.isDirectory()) {
			f = new File( f, "waveforms");
			dir.setText( f.getPath() );
		} else {
			File dateDir = f.getParentFile();
			if (dateDir.getParentFile() != null) {
				String subject = dateDir.getParent();
				String xlsname = subject + "-waveforms";
				dir.setText(xlsname);
			} else {
				String xlsname = dateDir.getPath() + "-waveforms";
				dir.setText(xlsname);
			}
		}

		return;
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		separator2 = compFactory.createSeparator("Waveform Export");
		fileInfoPanel = new JPanel();
		label4 = new JLabel();
		dir = new JTextField();
		browse = new JButton();
		defaultFilename = new JButton();
		panel3 = new JPanel();
		panel1 = new JPanel();
		label5 = new JLabel();
		doExportTimestamp = new JCheckBox();
		label6 = new JLabel();
		exportMethod = new JComboBox<>();
		label9 = new JLabel();
		waveformFormat = new JComboBox<>();
		label2 = new JLabel();
		waveformFrequency = new JComboBox<>();
		label3 = new JLabel();
		resampleMethod = new JComboBox<>();
		sigSelectionHolder = new JPanel();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout(
			"default:grow",
			"2*(default, $lgap), fill:default:grow"));
		add(separator2, CC.xy(1, 1));

		//======== fileInfoPanel ========
		{
			fileInfoPanel.setLayout(new FormLayout(
				"right:70dlu, $lcgap, default, $lcgap, default:grow, 2*($lcgap, default)",
				"2*(default, $lgap), default"));

			//---- label4 ----
			label4.setText("Output Directory:");
			fileInfoPanel.add(label4, CC.xy(1, 3));
			fileInfoPanel.add(dir, CC.xywh(3, 3, 3, 1));

			//---- browse ----
			browse.setIcon(new ImageIcon(getClass().getResource("/fonta/resources/search.png")));
			browse.setToolTipText("Browse");
			browse.addActionListener(e -> browseActionPerformed(e));
			fileInfoPanel.add(browse, CC.xy(7, 3));

			//---- defaultFilename ----
			defaultFilename.setIcon(new ImageIcon(getClass().getResource("/fonta/resources/repeat.png")));
			defaultFilename.setToolTipText("Reset file name");
			defaultFilename.setMaximumSize(new Dimension(43, 25));
			defaultFilename.setMinimumSize(new Dimension(22, 22));
			defaultFilename.addActionListener(e -> defaultFilenameActionPerformed(e));
			fileInfoPanel.add(defaultFilename, CC.xy(9, 3));
		}
		add(fileInfoPanel, CC.xy(1, 3));

		//======== panel3 ========
		{
			panel3.setLayout(new FormLayout(
				"default, $lcgap, default:grow",
				"fill:default:grow"));

			//======== panel1 ========
			{
				panel1.setLayout(new FormLayout(
					"right:60dlu, $lcgap, [80dlu,default]",
					"6*(default, $lgap), default"));

				//---- label5 ----
				label5.setText("Timestamp:");
				panel1.add(label5, CC.xy(1, 1));

				//---- doExportTimestamp ----
				doExportTimestamp.setText("Yes");
				panel1.add(doExportTimestamp, CC.xy(3, 1));

				//---- label6 ----
				label6.setText("Merge Method:");
				panel1.add(label6, CC.xy(1, 3));

				//---- exportMethod ----
				exportMethod.setModel(new DefaultComboBoxModel<>(new String[] {
					"File/Channel",
					"Single File"
				}));
				exportMethod.setEditable(true);
				exportMethod.setEnabled(false);
				panel1.add(exportMethod, CC.xy(3, 3));

				//---- label9 ----
				label9.setText("Waveform Format:");
				panel1.add(label9, CC.xy(1, 7));

				//---- waveformFormat ----
				waveformFormat.setModel(new DefaultComboBoxModel<>(new String[] {
					"ASCII",
					"None"
				}));
				waveformFormat.setEditable(true);
				waveformFormat.setEnabled(false);
				panel1.add(waveformFormat, CC.xy(3, 7));

				//---- label2 ----
				label2.setText("Frequency:");
				panel1.add(label2, CC.xy(1, 9));

				//---- waveformFrequency ----
				waveformFrequency.setModel(new DefaultComboBoxModel<>(new String[] {
					"Device Speed",
					"1 Hz",
					"20 Hz",
					"50 Hz",
					"100 Hz",
					"200 Hz",
					"500 Hz"
				}));
				waveformFrequency.setEditable(true);
				waveformFrequency.setEnabled(false);
				panel1.add(waveformFrequency, CC.xy(3, 9));

				//---- label3 ----
				label3.setText("Resample Method:");
				panel1.add(label3, CC.xy(1, 11));

				//---- resampleMethod ----
				resampleMethod.setModel(new DefaultComboBoxModel<>(new String[] {
					"None",
					"Sample and Hold",
					"Interpolate"
				}));
				resampleMethod.setEditable(true);
				resampleMethod.setEnabled(false);
				panel1.add(resampleMethod, CC.xy(3, 11));
			}
			panel3.add(panel1, CC.xy(1, 1));

			//======== sigSelectionHolder ========
			{
				sigSelectionHolder.setLayout(new BorderLayout());
			}
			panel3.add(sigSelectionHolder, CC.xy(3, 1));
		}
		add(panel3, CC.xy(1, 5));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JComponent separator2;
	private JPanel fileInfoPanel;
	private JLabel label4;
	private JTextField dir;
	private JButton browse;
	private JButton defaultFilename;
	private JPanel panel3;
	private JPanel panel1;
	private JLabel label5;
	private JCheckBox doExportTimestamp;
	private JLabel label6;
	private JComboBox<String> exportMethod;
	private JLabel label9;
	private JComboBox<String> waveformFormat;
	private JLabel label2;
	private JComboBox<String> waveformFrequency;
	private JLabel label3;
	private JComboBox<String> resampleMethod;
	private JPanel sigSelectionHolder;
	// JFormDesigner - End of variables declaration //GEN-END:variables
	@Override
	public boolean finish() {
		return false;
	}

	@Override
	public boolean next() {
		saveActionPerformed( null );
		
		try {
			TsOfflineSetup.setWaveExportDir( dir.getText() );
		} catch (BackingStoreException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return true;
	}

	@Override
	public void refresh() {
		ExportWizard wizard = ExportWizard.getInstance();
		wizard.enableNext( true );
	}

	@Override
	public void previous() {
		// TODO Auto-generated method stub
		
	}

	public String getExportDir() {
		return dir.getText();
	}

	public void setFileOutput(boolean vis) {
		fileInfoPanel.setVisible( vis );
	}

	public String getOutputFile() {
		return dir.getText();
	}

	public Map<String, LinkedList<? extends RpMetric>> getSignals() {
		return signalPanel.getSignals();
	}


}
