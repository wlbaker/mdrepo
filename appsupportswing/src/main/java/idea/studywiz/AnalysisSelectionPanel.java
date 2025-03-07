/*
 * Created by JFormDesigner on Fri Apr 16 12:30:26 CDT 2010
 */

package idea.studywiz;

import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;
import java.util.List;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JDialog;
import javax.swing.JFileChooser;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.JTextField;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumnModel;
import jakarta.xml.bind.JAXBException;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.factories.DefaultComponentFactory;
import com.jgoodies.forms.layout.FormLayout;

import icuInterface.RpUtil;
import idea.schema.rp.RpAnalysis;
import idea.schema.rp.RpStudy;
import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;
import idea.PrefUtil;
import idea.analysis.AnalysisFactory;
import idea.gui.WizardMasterInterface;
import idea.gui.WizardPanelInterface;
import idea.meddaq.AppSetup;
import idea.repository.io.LocalJAXBRepository;

/**
 * @author User #2
 */
@Slf4j
@SuppressWarnings("serial")
public class AnalysisSelectionPanel extends JPanel implements WizardPanelInterface {

	private static final int OBJECT_COL = 0;
	private static final int COL_ANALYSIS_NAME = 1;
	private WizardMasterInterface wizard;
	RpStudy study;
	String studyRoot = null;

	public AnalysisSelectionPanel(WizardMasterInterface wizard, RpStudy study) {
		this.wizard = wizard;
		this.study = study;

		initComponents();
		setName("Analysis");

		setFileOutput(false); // default for existing code
		GuiUtil.initPanel(this);

		refresh();
	}

	private void browseActionPerformed(ActionEvent e) {
		File parent = null;
		String lastDir = outputFileName.getText();
		if (lastDir == null || lastDir.length() == 0) {
			parent = new File(studyRoot);
		}

		GuiUtil.doOpenFileChooser(JFileChooser.FILES_AND_DIRECTORIES, "Analysis Output File", this, parent,
				new ActionListener() {

					@Override
					public void actionPerformed(ActionEvent e) {
						File file = (File) e.getSource();
						outputFileName.setText(file.getAbsolutePath());
					}
				});
	}

	private void browseStudyActionPerformed(ActionEvent e) {
		File parent = null;
		String lastDir = studyFileName.getText();
		if (lastDir.length() == 0) {
			lastDir = PrefUtil.getUserPref(AppSetup.getAnalysisFile(), null);
		}
		if (lastDir != null) {
			parent = new File(lastDir);
		}

		GuiUtil.doOpenFileChooser(JFileChooser.FILES_AND_DIRECTORIES, "Analysis File", this, parent,
				new ActionListener() {

					@Override
					public void actionPerformed(ActionEvent e) {
						File file = (File) e.getSource();
						studyFileName.setText(file.getAbsolutePath());
					}
				});
	}

	private boolean save() {
		boolean ok = false;

		if (study != null) {

			DefaultTableModel model = (DefaultTableModel) selected.getModel();
			for (int row = 0; row < model.getRowCount(); row++) {
				RpAnalysis analysis = (RpAnalysis) model.getValueAt(row, OBJECT_COL);
				study.getAnalysis().add(analysis);
			}
		}
		ok = true;

		return ok;
	}

	private void resetOutputActionPerformed(ActionEvent e) {
		String s = studyRoot;
		if (s == null) {
			s = AppSetup.getAnalysisFile();
		}
		File f = new File(s);
		if (s == null || s.length() == 0) {
			f = new File(f, "analysis.xml");
			studyFileName.setText(f.getPath());
		} else if (f.isDirectory()) {
			f = new File(f, "analysis.xml");
			studyFileName.setText(f.getPath());
		} else {
			File dateDir = f.getParentFile();
			if (dateDir.getParentFile() != null) {
				String subject = dateDir.getParent();
				String xlsname = subject + "-analysis.xml";
				studyFileName.setText(xlsname);
			} else {
				String xlsname = dateDir.getPath() + "-analysis.xml";
				studyFileName.setText(xlsname);
			}
		}

		return;
	}

	private void addActionPerformed(ActionEvent e) {

		try {
			String t = studyFileName.getText();
			File f = new File(t.trim());
			if (!f.canRead()) {
				GuiUtil.showMessage("Cannot read file: " + f.getAbsolutePath());
				return;
			}

			RpStudy study = LocalJAXBRepository.createStudyFromFile(f);
			_addActionPerformed(selected, study.getAnalysis());
		} catch (JAXBException e1) {
			GuiUtil.showError("Could not add analysis", e1);
		}
	}

	private void _addActionPerformed(JTable dest, List<RpAnalysis> subanalysis) throws JAXBException {

		DefaultTableModel model = (DefaultTableModel) dest.getModel();

		for (RpAnalysis one : subanalysis) {
			model.addRow(new Object[] { one, one.getName() });
		}

	}

	private void addSelectedActionPerformed(ActionEvent e) {
		int row = candidate.getSelectedRow();
		if (row >= 0) {
			RpAnalysis anal = (RpAnalysis) candidate.getValueAt(row, OBJECT_COL);
			anal = RpUtil.clone(anal); // only save a copy...don't alter the original
			_editActionPerformed(anal);

			int idx = 0;
			do {
				String analName = anal.getName();
				if (idx > 0) {
					analName = analName + "[" + idx + "]";
				}
				if (findAnalysis(analName) < 0) {
					anal.setName(analName);
					break;
				}
				idx++;
			} while (true);

			DefaultTableModel model = (DefaultTableModel) selected.getModel();
			model.addRow(new Object[] { anal, anal.getName() });

			row = model.getRowCount() - 1;
			selected.getSelectionModel().setSelectionInterval(row, row);

			boolean exportable = (model.getRowCount() > 0);
			this.putClientProperty("EXPORTABLE", exportable);
		}
	}

	private int findAnalysis(String analName) {
		DefaultTableModel model = (DefaultTableModel) selected.getModel();
		for (int row = 0; row < model.getRowCount(); row++) {
			Object existingName = model.getValueAt(row, COL_ANALYSIS_NAME);
			if (analName.equals(existingName)) {
				return row;
			}
		}
		return -1;
	}

	private void _editActionPerformed(RpAnalysis anal) {
		String cl = anal.getAnalysisClass();
		String title = anal.getName();

		JPanel setup = null;
		if (anal.getName().startsWith("Function.Print")) {
			// setup = new PrintProcessSetupForm(study, null, anal);
			// title = "Print Setup";
			System.err.println("ERROR: Function.Print needs rethought.");
		} else if (anal.getName().startsWith("JavaScript") || anal.getName().startsWith("VB Script")
				|| anal.getName().startsWith("Script")) {
			cl = "idea.process.BannerProcessSetupForm";
			title = "Script Setup";
		} else if (anal.getName().startsWith("Function.Banner")) {
			cl = "idea.process.BannerProcessSetupForm";
			title = "Banner Setup";
		} else {
			cl += "SetupPanel";
			cl = cl.replace("PanelSetup", "Setup"); // drops the end Panel if present
		}

		try {
			setup = AnalysisFactory.buildSetupPanel(cl, study, anal);
		} catch (Exception e1) {
			GuiUtil.showError("Analysis Setup Error", e1);
		}

		if (setup == null) {
			GuiUtil.showMessage("NO SETUP OPTIONS FOR ANALYSIS: " + cl);
		}
		if (setup != null) {
			Object[] options = new Object[0];
			JOptionPane p = new JOptionPane(setup, JOptionPane.PLAIN_MESSAGE, JOptionPane.NO_OPTION, null, options,
					null);
			JDialog d = p.createDialog(this, title);
			GuiUtil.initModalDialog(d, p); // makes the escape key work
			d.setName("$Rev$");
			d.setResizable(true);
			d.pack();
			d.setVisible(true);
		}
	}

	private void removeSelectedActionPerformed(ActionEvent e) {
		DefaultTableModel model = (DefaultTableModel) selected.getModel();

		int row = selected.getSelectedRow();
		if (row >= 0) {
			model.removeRow(row);
		}
		boolean exportable = (model.getRowCount() > 0);
		this.putClientProperty("EXPORTABLE", exportable);
	}

	private void editSelectedActionPerformed(ActionEvent e) {
		int row = selected.getSelectedRow();
		if (row >= 0) {

			RpAnalysis anal = (RpAnalysis) selected.getValueAt(row, OBJECT_COL);
			_editActionPerformed(anal);

		}
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		separator3 = compFactory.createSeparator("Analysis Source File");
		fileInfoPanel = new JPanel();
		label5 = new JLabel();
		outputFileName = new JTextField();
		browseOutput = new JButton();
		resetOutputFile = new JButton();
		panel1 = new JPanel();
		label4 = new JLabel();
		studyFileName = new JTextField();
		browseStudy = new JButton();
		add = new JButton();
		button1 = new JButton();
		panel3 = new JPanel();
		panel4 = new JPanel();
		addSelected = new JButton();
		removeSelected = new JButton();
		editSelected = new JButton();
		scrollPane1 = new JScrollPane();
		candidate = new JTable();
		scrollPane2 = new JScrollPane();
		selected = new JTable();

		// ======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout("default:grow", "3*(default, $lgap), fill:default:grow"));
		add(separator3, CC.xy(1, 1));

		// ======== fileInfoPanel ========
		{
			fileInfoPanel.setLayout(new FormLayout(
					"right:50dlu, $lcgap, [100dlu,default], $lcgap, default:grow, 3*($lcgap, 24dlu)", "default"));

			// ---- label5 ----
			label5.setText("Output File:");
			fileInfoPanel.add(label5, CC.xy(1, 1));
			fileInfoPanel.add(outputFileName, CC.xywh(3, 1, 3, 1));

			// ---- browseOutput ----
			browseOutput.setIcon(new ImageIcon(getClass().getResource("/fonta/resources/search.png")));
			browseOutput.setToolTipText("Browse");
			browseOutput.addActionListener(e -> browseActionPerformed(e));
			fileInfoPanel.add(browseOutput, CC.xy(7, 1));

			// ---- resetOutputFile ----
			resetOutputFile.setIcon(new ImageIcon(getClass().getResource("/fonta/resources/repeat.png")));
			resetOutputFile.setToolTipText("Add analysis from selected file");
			resetOutputFile.addActionListener(e -> resetOutputActionPerformed(e));
			fileInfoPanel.add(resetOutputFile, CC.xy(9, 1));
		}
		add(fileInfoPanel, CC.xy(1, 3));

		// ======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
					"right:50dlu, $lcgap, [100dlu,default], $lcgap, default:grow, 3*($lcgap, 24dlu)", "default"));

			// ---- label4 ----
			label4.setText("Study File:");
			panel1.add(label4, CC.xy(1, 1));
			panel1.add(studyFileName, CC.xywh(3, 1, 3, 1));

			// ---- browseStudy ----
			browseStudy.setIcon(new ImageIcon(getClass().getResource("/fonta/resources/search.png")));
			browseStudy.setToolTipText("Browse");
			browseStudy.addActionListener(e -> browseStudyActionPerformed(e));
			panel1.add(browseStudy, CC.xy(7, 1));

			// ---- add ----
			add.setIcon(new ImageIcon(getClass().getResource("/fonta/resources/repeat.png")));
			add.setToolTipText("Add analysis from selected file");
			add.addActionListener(e -> addActionPerformed(e));
			panel1.add(add, CC.xy(9, 1));

			// ---- button1 ----
			button1.setIcon(new ImageIcon(getClass().getResource("/fonta/resources/save.png")));
			button1.setEnabled(false);
			panel1.add(button1, CC.xy(11, 1));
		}
		add(panel1, CC.xy(1, 5));

		// ======== panel3 ========
		{
			panel3.setLayout(new FormLayout("default, 2*($lcgap, default:grow)", "fill:default:grow"));

			// ======== panel4 ========
			{
				panel4.setLayout(new FormLayout("[50dlu,default]", "3*(default, $lgap), default:grow"));

				// ---- addSelected ----
				addSelected.setText("Add");
				addSelected.addActionListener(e -> addSelectedActionPerformed(e));
				panel4.add(addSelected, CC.xy(1, 1));

				// ---- removeSelected ----
				removeSelected.setText("Remove");
				removeSelected.addActionListener(e -> removeSelectedActionPerformed(e));
				panel4.add(removeSelected, CC.xy(1, 3));

				// ---- editSelected ----
				editSelected.setText("Edit");
				editSelected.addActionListener(e -> editSelectedActionPerformed(e));
				panel4.add(editSelected, CC.xy(1, 5));
			}
			panel3.add(panel4, CC.xy(1, 1));

			// ======== scrollPane1 ========
			{
				scrollPane1.setRequestFocusEnabled(false);
				scrollPane1.setPreferredSize(new Dimension(60, 32));

				// ---- candidate ----
				candidate.setModel(new DefaultTableModel(new Object[][] { { null, null }, { null, null }, },
						new String[] { "O", "Available Analysis" }) {
					boolean[] columnEditable = new boolean[] { true, false };

					@Override
					public boolean isCellEditable(int rowIndex, int columnIndex) {
						return columnEditable[columnIndex];
					}
				});
				{
					TableColumnModel cm = candidate.getColumnModel();
					cm.getColumn(0).setMinWidth(1);
					cm.getColumn(0).setMaxWidth(1);
					cm.getColumn(0).setPreferredWidth(1);
					cm.getColumn(1).setPreferredWidth(120);
				}
				candidate.setPreferredSize(new Dimension(61, 32));
				candidate.setFillsViewportHeight(true);
				scrollPane1.setViewportView(candidate);
			}
			panel3.add(scrollPane1, CC.xy(3, 1));

			// ======== scrollPane2 ========
			{
				scrollPane2.setPreferredSize(new Dimension(60, 32));

				// ---- selected ----
				selected.setModel(new DefaultTableModel(new Object[][] { { null, null }, { null, null }, },
						new String[] { "O", "Selected Analysis" }) {
					boolean[] columnEditable = new boolean[] { false, false };

					@Override
					public boolean isCellEditable(int rowIndex, int columnIndex) {
						return columnEditable[columnIndex];
					}
				});
				{
					TableColumnModel cm = selected.getColumnModel();
					cm.getColumn(0).setMinWidth(1);
					cm.getColumn(0).setMaxWidth(1);
					cm.getColumn(0).setPreferredWidth(1);
				}
				selected.setPreferredSize(new Dimension(60, 32));
				selected.setFillsViewportHeight(true);
				scrollPane2.setViewportView(selected);
			}
			panel3.add(scrollPane2, CC.xy(5, 1));
		}
		add(panel3, CC.xy(1, 7));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JComponent separator3;
	private JPanel fileInfoPanel;
	private JLabel label5;
	private JTextField outputFileName;
	private JButton browseOutput;
	private JButton resetOutputFile;
	private JPanel panel1;
	private JLabel label4;
	private JTextField studyFileName;
	private JButton browseStudy;
	private JButton add;
	private JButton button1;
	private JPanel panel3;
	private JPanel panel4;
	private JButton addSelected;
	private JButton removeSelected;
	private JButton editSelected;
	private JScrollPane scrollPane1;
	private JTable candidate;
	private JScrollPane scrollPane2;
	private JTable selected;

	// JFormDesigner - End of variables declaration //GEN-END:variables
	@Override
	public boolean finish() {
		if (!save()) {
			return false;
		}

		return true;
	}

	@Override
	public boolean next() {
		return save();
	}

	@Override
	public void refresh() {
		try {
			resetOutputActionPerformed(null);
			refreshCandidates();

			DefaultTableModel model = (DefaultTableModel) selected.getModel();

			model.setRowCount(0);

			int count = 0;
			if (study == null) {
				log.error("Analysis Selection Panel: no study to refresh!!");
			} else {
				List<RpAnalysis> subanals = study.getAnalysis();
				if (subanals != null) {
					for (RpAnalysis anal : subanals) {
						model.addRow(new Object[] { anal, anal.getName() });
						count++;
					}
				}
			}

			boolean exportable = (count > 0);
			this.putClientProperty("EXPORTABLE", exportable);
		} catch (Exception e) {
			GuiUtil.showError("Analysis Panel Error", e);
		}
	}

	private void refreshCandidates() throws IOException, JAXBException {

		DefaultTableModel model = (DefaultTableModel) candidate.getModel();

		model.setRowCount(0);

		List<RpAnalysis> anals = AnalysisFactory.getAnalyses();
		_addActionPerformed(candidate, anals);
	}

	@Override
	public void previous() {
		// TODO Auto-generated method stub

	}

	public void setStudyRoot(String root) {
		this.studyRoot = root;
	}

	public void setFileOutput(boolean vis) {
		fileInfoPanel.setVisible(vis);
	}

	public String getOutputFile() {
		return outputFileName.getText();
	}
}
