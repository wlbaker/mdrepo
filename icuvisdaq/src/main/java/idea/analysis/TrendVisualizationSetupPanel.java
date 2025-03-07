/*
 * Created by JFormDesigner on Fri Apr 16 12:30:26 CDT 2010
 */

package idea.analysis;

import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.io.IOException;
import java.util.List;

import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JSpinner;
import javax.swing.JTable;
import javax.swing.SpinnerNumberModel;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumnModel;
import jakarta.xml.bind.JAXBException;

import idea.GuiUtil;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.factories.DefaultComponentFactory;
import com.jgoodies.forms.layout.FormLayout;

import idea.schema.rp.RpAnalysis;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpStudy;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class TrendVisualizationSetupPanel extends JPanel {

	private static final int OBJECT_COL = 0;
	private static final int COL_ANALYSIS_NAME = 1;
	private RpStudy study;
	private RpAnalysis anal;

	public TrendVisualizationSetupPanel(RpStudy study, RpAnalysis anal ) {

		initComponents();
		setName("Analysis");

		this.study = study;
		this.anal = anal;

		refresh();
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
			RpMetric metric = (RpMetric)candidate.getValueAt(row, OBJECT_COL);

			int idx = 0;
			do {
				String analName = metric.getName();
				if (idx > 0) {
					analName = analName + "[" + idx + "]";
				}
				if (findAnalysis(analName) < 0) {
					anal.setName(analName);
					break;
				}
				idx++;
			} while (true);

			DefaultTableModel model = (DefaultTableModel) elected.getModel();
			model.addRow(new Object[] { metric, metric.getName() });

			row = model.getRowCount() - 1;
			elected.getSelectionModel().setSelectionInterval(row, row);

		}
	}

	private int findAnalysis(String analName) {
		DefaultTableModel model = (DefaultTableModel) elected.getModel();
		for (int row = 0; row < model.getRowCount(); row++) {
			Object existingName = model.getValueAt(row, COL_ANALYSIS_NAME);
			if (analName.equals(existingName)) {
				return row;
			}
		}
		return -1;
	}

	private void removeSelectedActionPerformed(ActionEvent e) {
		int row = elected.getSelectedRow();
		if (row >= 0) {
			DefaultTableModel model = (DefaultTableModel) elected.getModel();
			model.removeRow(row);
		}
	}

	private void editSelectedActionPerformed(ActionEvent e) {
		// TODO add your code here
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		separator3 = compFactory.createSeparator("Trend Visualization Setup");
		panel1 = new JPanel();
		label1 = new JLabel();
		spinner1 = new JSpinner();
		separator2 = compFactory.createSeparator("Signal Selection");
		panel3 = new JPanel();
		panel4 = new JPanel();
		addSelected = new JButton();
		removeSelected = new JButton();
		scrollPane1 = new JScrollPane();
		candidate = new JTable();
		scrollPane2 = new JScrollPane();
		elected = new JTable();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout(
			"default:grow",
			"3*(default, $lgap), fill:default:grow"));
		add(separator3, CC.xy(1, 1));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"[50dlu,default], $lcgap, default, $lcgap, [30dlu,default]",
				"10dlu, $lgap, default, $lgap, 10dlu"));

			//---- label1 ----
			label1.setText("Number of Bands:");
			panel1.add(label1, CC.xy(3, 3));

			//---- spinner1 ----
			spinner1.setModel(new SpinnerNumberModel(1, 1, 5, 1));
			panel1.add(spinner1, CC.xy(5, 3));
		}
		add(panel1, CC.xy(1, 3));
		add(separator2, CC.xy(1, 5));

		//======== panel3 ========
		{
			panel3.setLayout(new FormLayout(
				"default, $lcgap, default:grow(0.19999999999999998), $lcgap, default:grow(0.6)",
				"fill:default:grow"));

			//======== panel4 ========
			{
				panel4.setLayout(new FormLayout(
					"[50dlu,default]",
					"3*(default, $lgap), default:grow"));

				//---- addSelected ----
				addSelected.setText("Add");
				addSelected.addActionListener(e -> addSelectedActionPerformed(e));
				panel4.add(addSelected, CC.xy(1, 1));

				//---- removeSelected ----
				removeSelected.setText("Remove");
				removeSelected.addActionListener(e -> removeSelectedActionPerformed(e));
				panel4.add(removeSelected, CC.xy(1, 3));
			}
			panel3.add(panel4, CC.xy(1, 1));

			//======== scrollPane1 ========
			{
				scrollPane1.setRequestFocusEnabled(false);
				scrollPane1.setPreferredSize(new Dimension(60, 32));

				//---- candidate ----
				candidate.setModel(new DefaultTableModel(
					new Object[][] {
						{null, null},
						{null, null},
					},
					new String[] {
						"O", "Available Signals"
					}
				) {
					boolean[] columnEditable = new boolean[] {
						true, false
					};
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

			//======== scrollPane2 ========
			{
				scrollPane2.setPreferredSize(new Dimension(60, 32));

				//---- elected ----
				elected.setModel(new DefaultTableModel(
					new Object[][] {
						{null, null, null, null},
						{null, null, null, null},
					},
					new String[] {
						"O", "Selected Signals", "Band", "Color"
					}
				) {
					boolean[] columnEditable = new boolean[] {
						false, false, true, true
					};
					@Override
					public boolean isCellEditable(int rowIndex, int columnIndex) {
						return columnEditable[columnIndex];
					}
				});
				{
					TableColumnModel cm = elected.getColumnModel();
					cm.getColumn(0).setMinWidth(1);
					cm.getColumn(0).setMaxWidth(1);
					cm.getColumn(0).setPreferredWidth(1);
					cm.getColumn(1).setPreferredWidth(100);
					cm.getColumn(2).setPreferredWidth(40);
					cm.getColumn(3).setPreferredWidth(40);
				}
				elected.setPreferredSize(new Dimension(60, 32));
				elected.setFillsViewportHeight(true);
				scrollPane2.setViewportView(elected);
			}
			panel3.add(scrollPane2, CC.xy(5, 1));
		}
		add(panel3, CC.xy(1, 7));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JComponent separator3;
	private JPanel panel1;
	private JLabel label1;
	private JSpinner spinner1;
	private JComponent separator2;
	private JPanel panel3;
	private JPanel panel4;
	private JButton addSelected;
	private JButton removeSelected;
	private JScrollPane scrollPane1;
	private JTable candidate;
	private JScrollPane scrollPane2;
	private JTable elected;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	public void refresh() {
		try {
			refreshCandidates();

			DefaultTableModel model = (DefaultTableModel) elected.getModel();

			model.setRowCount(0);

			List<RpAnalysis> subanals = study.getAnalysis();
			if (subanals != null) {
				for (RpAnalysis anal : subanals) {
					model.addRow(new Object[] { anal, anal.getName() });
				}
			}
		} catch (Exception e) {
			GuiUtil.showError("Analysis Panel Error", e);
		}
	}

	private void refreshCandidates() throws IOException, JAXBException {

		DefaultTableModel model = (DefaultTableModel) candidate.getModel();

		model.setRowCount(0);

		List<RpAnalysis> anals = AnalysisFactory.getAnalyses();
		_addActionPerformed(candidate, anals );
	}


}
