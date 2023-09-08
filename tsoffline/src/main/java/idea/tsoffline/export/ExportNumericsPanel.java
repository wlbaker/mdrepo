/*
 * Created by JFormDesigner on Fri Apr 16 12:30:26 CDT 2010
 */

package idea.tsoffline.export;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;
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
public class ExportNumericsPanel extends JPanel implements WizardPanelInterface {

	private static final int DEVICE_SPEED = 0;
	private static final int ANNOTATION_SPEED = -1;

	private ExportWizard wizard;
	private int interval;
	private ExpSignalSelectionPanel signalPanel;

	public ExportNumericsPanel(ExportWizard wiz) {
		initComponents();
		setName("Numerics");

		this.wizard = wiz;
		// GuiUtil.initPanel(this);

		dir.setText(TsOfflineSetup.getExportDir());
		merge.setSelected(TsOfflineSetup.getMerge());
		resampleMethod.setSelectedIndex(TsOfflineSetup.getResampleMethod());
		int secs = TsOfflineSetup.getMetricInterval();
		if (secs > 0) {
			// value is recorded in MS, escept for the special values of DEVICE_SPEED and ANNOTATION_SPEED
			secs = secs / 1000;
		}
		int pos = 2;
		if (secs == 1) {
			pos = 0;
		}
		if (secs == 3) {
			pos = 1;
		}
		if (secs == 5) {
			pos = 2;
		}
		if (secs == 10) {
			pos = 3;
		}
		if (secs == 60) {
			pos = 4;
		}
		if (secs == 300) {
			pos = 5;
		}
		if (secs == 3600) {
			pos = 6;
		}
		if (secs == DEVICE_SPEED) {
			pos = 7;
		}
		if (secs == ANNOTATION_SPEED) {
			pos = 8;
		}
		metricInterval.setSelectedIndex(pos);

		sigSelectionHolder.add(signalPanel = new ExpSignalSelectionPanel(wiz, true, false), BorderLayout.CENTER);
	}

	public void refresh(PiSubjectImporter importer) throws IOException {

		defaultFilenameActionPerformed(null);

		signalPanel.refresh(importer);
		wizard.enableNext(true);
	}

	private void browseActionPerformed(ActionEvent e) {
		File parent = null;
		String lastDir = dir.getText();
		if (lastDir.length() == 0) {
			lastDir = PrefUtil.getUserPref(TsOfflineSetup.getExportDir(), null);
		}
		if (lastDir != null) {
			parent = new File(lastDir);
		}

		GuiUtil.doOpenFileChooser(JFileChooser.FILES_AND_DIRECTORIES, "Local Repository", this, parent,
				new ActionListener() {

					@Override
					public void actionPerformed(ActionEvent e) {
						File file = (File) e.getSource();
						dir.setText(file.getAbsolutePath());
					}
				});
	}

	private void saveActionPerformed(ActionEvent e) {

		try {
			TsOfflineSetup.setExportDir(dir.getText());

			TsOfflineSetup.setMetricInterval(getExportInterval());
			TsOfflineSetup.setMerge(merge.isSelected());
			TsOfflineSetup.setResampleMethod(resampleMethod.getSelectedIndex());

		} catch (Exception ee) {
			GuiUtil.showError("Export Data Format: ", ee);
		}
	}

	public int getExportInterval() {
		String item = (String) metricInterval.getSelectedItem();
		interval = parseMetricInterval(item);

		return interval;
	}

	public int getExportResampleMethod() {
		return resampleMethod.getSelectedIndex();
	}

	public boolean getExportMergeIndicator() {
		return merge.isSelected();
	}

	private int parseMetricInterval(String item) {
		int ivl = 0;
		String[] ar = item.split(" ");
		if ("Device".equals(ar[0])) {
			// ivl is 0
		} else if ("Annotation".equals(ar[0])) {
			// ivl is 0
			ivl = -1;
		} else {
			ivl = (Integer.parseInt(ar[0])) * 1000;
			String unit = ar[1];
			if (unit.startsWith("sec")) {
				// ivl ok
			} else if (unit.startsWith("min")) {
				ivl *= 60;
			} else if (unit.startsWith("h")) {
				ivl *= 3600;
			}
			try {
				TsOfflineSetup.setMetricInterval(ivl);
			} catch (BackingStoreException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		return ivl;
	}

	private void defaultFilenameActionPerformed(ActionEvent e) {
		String s = TsOfflineSetup.getArchiveFile();
		File f = new File(s);
		if (f.isDirectory()) {
			File parent = f.getParentFile();
			File ff = new File(parent.getPath(), "${SUBJECT}.xls");
			String xlsname = ff.getPath();
			dir.setText(xlsname);
		} else {
			File dateDir = f.getParentFile();
			if (dateDir.getParentFile() != null) {
				String subject = dateDir.getParent();
				String xlsname = subject + ".xls";
				dir.setText(xlsname);
			} else {
				String xlsname = dateDir.getPath() + ".xls";
				dir.setText(xlsname);
			}
		}

		return;
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		separator2 = compFactory.createSeparator("Numeric Export");
		fileInfoPanel = new JPanel();
		label5 = new JLabel();
		dir = new JTextField();
		browse = new JButton();
		defaultFilename = new JButton();
		panel2 = new JPanel();
		panel1 = new JPanel();
		label3 = new JLabel();
		resampleMethod = new JComboBox<>();
		label1 = new JLabel();
		metricInterval = new JComboBox<>();
		label6 = new JLabel();
		merge = new JCheckBox();
		sigSelectionHolder = new JPanel();

		// ======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout("default:grow", "default, $lgap, default, $ugap, fill:default:grow"));
		add(separator2, CC.xy(1, 1));

		// ======== fileInfoPanel ========
		{
			fileInfoPanel.setLayout(new FormLayout("right:60dlu, $lcgap, default:grow, 3*($lcgap, default)",
					"default, $lgap, default"));

			// ---- label5 ----
			label5.setText("Output File:");
			fileInfoPanel.add(label5, CC.xy(1, 3));
			fileInfoPanel.add(dir, CC.xywh(3, 3, 3, 1));

			// ---- browse ----
			browse.setIcon(new ImageIcon(getClass().getResource("/fonta/resources/search.png")));
			browse.setToolTipText("Browse");
			browse.setMinimumSize(new Dimension(22, 22));
			browse.setMaximumSize(new Dimension(43, 25));
			browse.addActionListener(e -> browseActionPerformed(e));
			fileInfoPanel.add(browse, CC.xy(7, 3));

			// ---- defaultFilename ----
			defaultFilename.setIcon(new ImageIcon(getClass().getResource("/fonta/resources/repeat.png")));
			defaultFilename.setToolTipText("Reset file name");
			defaultFilename.setMaximumSize(new Dimension(43, 25));
			defaultFilename.setMinimumSize(new Dimension(22, 22));
			defaultFilename.addActionListener(e -> defaultFilenameActionPerformed(e));
			fileInfoPanel.add(defaultFilename, CC.xy(9, 3));
		}
		add(fileInfoPanel, CC.xy(1, 3));

		// ======== panel2 ========
		{
			panel2.setLayout(new BorderLayout());

			// ======== panel1 ========
			{
				panel1.setLayout(
						new FormLayout("right:60dlu, $lcgap, 70dlu, $lcgap, 2*(min)", "4*(default, $lgap), default"));

				// ---- label3 ----
				label3.setText("Resample:");
				panel1.add(label3, CC.xy(1, 5));

				// ---- resampleMethod ----
				resampleMethod.setModel(
						new DefaultComboBoxModel<>(new String[] { "None", "Sample and Hold", "Interpolate" }));
				resampleMethod.setEditable(true);
				resampleMethod.setEnabled(false);
				panel1.add(resampleMethod, CC.xy(3, 5));

				// ---- label1 ----
				label1.setText("Interval:");
				panel1.add(label1, CC.xy(1, 7));

				// ---- metricInterval ----
				metricInterval.setModel(new DefaultComboBoxModel<>(
						new String[] { "1 sec/record", "3 sec/record", "5 sec/record", "10 sec/record", "60 sec/record",
								"5 min/record", "1 hr/record", "Device Speed", "Annotation Speed" }));
				metricInterval.setEditable(true);
				panel1.add(metricInterval, CC.xy(3, 7));

				// ---- label6 ----
				label6.setText("Merge:");
				panel1.add(label6, CC.xy(1, 9));

				// ---- merge ----
				merge.setText("Yes");
				panel1.add(merge, CC.xy(3, 9));
			}
			panel2.add(panel1, BorderLayout.WEST);

			// ======== sigSelectionHolder ========
			{
				sigSelectionHolder.setLayout(new BorderLayout());
			}
			panel2.add(sigSelectionHolder, BorderLayout.CENTER);
		}
		add(panel2, CC.xy(1, 5));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JComponent separator2;
	private JPanel fileInfoPanel;
	private JLabel label5;
	private JTextField dir;
	private JButton browse;
	private JButton defaultFilename;
	private JPanel panel2;
	private JPanel panel1;
	private JLabel label3;
	private JComboBox<String> resampleMethod;
	private JLabel label1;
	private JComboBox<String> metricInterval;
	private JLabel label6;
	private JCheckBox merge;
	private JPanel sigSelectionHolder;

	// JFormDesigner - End of variables declaration //GEN-END:variables
	@Override
	public boolean finish() {
		return false;
	}

	@Override
	public boolean next() {

		saveActionPerformed(null);

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

	public void setFileOutput(boolean vis) {
		fileInfoPanel.setVisible(vis);
	}

	public String getOutputFile() {
		return dir.getText();
	}

	public Map<String, LinkedList<? extends RpMetric>> getSignals() {
		return signalPanel.getSignals();
	}
}
