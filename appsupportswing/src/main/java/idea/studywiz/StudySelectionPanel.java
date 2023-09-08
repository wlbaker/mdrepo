/*
 * Created by JFormDesigner on Mon Oct 05 16:17:27 CDT 2009
 */

package idea.studywiz;

import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.util.List;

import javax.swing.JButton;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumnModel;
import javax.swing.table.TableModel;

import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.layout.FormLayout;

import idea.schema.rp.RpStudy;
import idea.GuiUtil;
import idea.devwizard.LinkStudyPanel;
import idea.devwizard.RetrievalStudyPanel;
import idea.devwizard.StudyDetailPanel;
import idea.gui.TableSorter;
import idea.gui.WizardMasterInterface;
import idea.gui.WizardPanelInterface;
import idea.meddaq.AppSetup;
import idea.repository.RepositoryFactory;
import idea.repository.RepositoryInterface;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class StudySelectionPanel extends JPanel implements WizardPanelInterface, ListSelectionListener {

	private static final int OBJECT_COL = 0;
	private static final int NAME_COL = 1;
	private WizardMasterInterface wizard;

	public StudySelectionPanel(WizardMasterInterface wizard, boolean brief_style, boolean enable_creation,
			boolean enable_finish) {
		this.wizard = wizard;

		initComponents();
		initTable();

		setName("Study Selection");
		refresh();

		if (enable_creation) {
			newStudy.setEnabled(enable_creation);
		}
		// wizard.enableNext( !enable_finish );
		wizard.enableFinish(enable_finish);

		if (brief_style) {
			optionPanel.setVisible(false);
		}

		GuiUtil.initPanel(this);

	}

	private void initTable() {
		TableSorter sorter = new TableSorter(table.getModel());

		table.setAutoCreateColumnsFromModel(false);
		table.setModel(sorter);
		sorter.setTableHeader(table.getTableHeader());
		sorter.setSortingStatus(NAME_COL, TableSorter.ASCENDING);

		table.getSelectionModel().addListSelectionListener(this);

	}

	@Override
	public void refresh() {
		try {
			_refresh();

			valueChanged(null);
		} catch (Exception e) {
			GuiUtil.showError("Loading Studies:", e);
		}
	}

	public void _refresh() throws Exception {
		TableModel m = table.getModel();
		TableSorter sorter = (TableSorter) table.getModel();

		DefaultTableModel model = (DefaultTableModel) sorter.getTableModel();
		model.setRowCount(0);

		RepositoryInterface local = RepositoryFactory.getLocalRepository();

		List<RpStudy> defs = local.getStudyList(null);
		if (defs == null) {
			return;
		}

		for (RpStudy def : defs) {
			model.addRow(new Object[] { def, def.getTitle(), def.getPi(), def.getRepositoryLink(), def.getStatus() });
		}

		// re-apply the sort
		sorter.refresh();

	}

	private void newStudyActionPerformed(ActionEvent e) {

		wizard.pushPage(new StudyDetailPanel(wizard, AppSetup.getLocalRepositoryDir(), true));
	}

	private void deleteStudyActionPerformed(ActionEvent e) {
		int row = table.getSelectedRow();
		if (row >= 0) {
			RpStudy study = (RpStudy) table.getValueAt(row, OBJECT_COL);

			String message;
			if (study.getRepositoryId().endsWith("lnk")) {
				message = "<html>You are about to remove the link: " + study.getRepositoryId();
			} else {
				message = "<html>You are about to delete the selected study AND ASSOCIATED DATA for: "
						+ study.getRepositoryId();
			}
			
			int yes = GuiUtil.showConfirmDialog(message + ".<br><br>Are you sure?</html>", "Confirm Delete",
					JOptionPane.YES_NO_OPTION);
			if (yes == JOptionPane.YES_OPTION) {
				RepositoryInterface local = RepositoryFactory.getLocalRepository();
				try {
					local.removeStudy(study);
					refresh();
				} catch (Exception e1) {
					GuiUtil.showError("Cannot remove study: ", e1);
				}
			}
		}
	}

	private void retrieveStudyActionPerformed(ActionEvent e) {
		wizard.pushPage(new RetrievalStudyPanel(wizard, RetrievalStudyPanel.IMPORT));
	}

	private void importStudyActionPerformed(ActionEvent e) {
		wizard.pushPage(new LinkStudyPanel(wizard));
	}

	private void editStudyActionPerformed(ActionEvent e) {
		int row = table.getSelectedRow();
		if (row < 0) {
			return;
		}
		RpStudy study = (RpStudy) table.getValueAt(row, OBJECT_COL);
		StudyDetailPanel panel = new StudyDetailPanel(wizard, AppSetup.getLocalRepositoryDir(), false);
		panel.setStudy(study);
		wizard.pushPage(panel);
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		scrollPane1 = new JScrollPane();
		table = new JTable();
		optionPanel = new JPanel();
		newStudy = new JButton();
		linkStudy = new JButton();
		deleteStudy = new JButton();
		editStudy = new JButton();

		//======== this ========
		setBorder(null);
		setLayout(new FormLayout(
			"[150dlu,default]:grow, $rgap, default",
			"fill:default:grow"));

		//======== scrollPane1 ========
		{
			scrollPane1.setPreferredSize(new Dimension(200, 100));

			//---- table ----
			table.setModel(new DefaultTableModel(
				new Object[][] {
					{null, null, null, null},
					{null, null, null, null},
				},
				new String[] {
					"A", "Study", "PI", "Location"
				}
			) {
				boolean[] columnEditable = new boolean[] {
					true, false, false, false
				};
				@Override
				public boolean isCellEditable(int rowIndex, int columnIndex) {
					return columnEditable[columnIndex];
				}
			});
			{
				TableColumnModel cm = table.getColumnModel();
				cm.getColumn(0).setMinWidth(1);
				cm.getColumn(0).setMaxWidth(1);
				cm.getColumn(0).setPreferredWidth(1);
				cm.getColumn(1).setPreferredWidth(80);
				cm.getColumn(2).setPreferredWidth(60);
				cm.getColumn(3).setPreferredWidth(200);
			}
			table.setPreferredSize(new Dimension(141, 62));
			table.setFillsViewportHeight(true);
			scrollPane1.setViewportView(table);
		}
		add(scrollPane1, CC.xy(1, 1));

		//======== optionPanel ========
		{
			optionPanel.setLayout(new FormLayout(
				"default",
				"default:grow, 3*($lgap, default), $lgap, 15dlu, $lgap, default"));

			//---- newStudy ----
			newStudy.setText("New Local Study");
			newStudy.addActionListener(e -> newStudyActionPerformed(e));
			optionPanel.add(newStudy, CC.xy(1, 3));

			//---- linkStudy ----
			linkStudy.setText("Link Existing Study");
			linkStudy.addActionListener(e -> importStudyActionPerformed(e));
			optionPanel.add(linkStudy, CC.xy(1, 5));

			//---- deleteStudy ----
			deleteStudy.setText("Delete Local Study");
			deleteStudy.addActionListener(e -> deleteStudyActionPerformed(e));
			optionPanel.add(deleteStudy, CC.xy(1, 7));

			//---- editStudy ----
			editStudy.setText("Edit Study Info");
			editStudy.addActionListener(e -> editStudyActionPerformed(e));
			optionPanel.add(editStudy, CC.xy(1, 11));
		}
		add(optionPanel, CC.xy(3, 1));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JScrollPane scrollPane1;
	private JTable table;
	private JPanel optionPanel;
	private JButton newStudy;
	private JButton linkStudy;
	private JButton deleteStudy;
	private JButton editStudy;
	// JFormDesigner - End of variables declaration //GEN-END:variables
	private RpStudy selected_study;

	@Override
	public boolean next() {

		// make sure the current study is selected...takes care of refresh's 
		valueChanged(null);
		return true;
	}

	@Override
	public void valueChanged(ListSelectionEvent e) {
		int row = table.getSelectedRow();

		wizard.enableNext(row >= 0);
		deleteStudy.setEnabled(row >= 0);

		RpStudy study = (RpStudy) ((row >= 0) ? table.getValueAt(row, OBJECT_COL) : null);
		selected_study = study;
	}

	public RpStudy getSelectedStudy() {
		return selected_study;
	}

	@Override
	public boolean finish() {
		return true;
	}

	@Override
	public void previous() {
		// TODO Auto-generated method stub

	}
}
