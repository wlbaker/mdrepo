/*
 * Created by JFormDesigner on Wed Oct 07 12:27:36 CDT 2009
 */

package idea.devwizard;

import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumnModel;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;
import idea.PrefUtil;
import idea.gui.WizardMasterInterface;
import idea.gui.WizardPanelInterface;

/**
 * @author User #2
 */
@Slf4j
@SuppressWarnings("serial")
public class AnnotationPanel extends JPanel implements WizardPanelInterface {
	private static final int CODE_COL = 0;
	private static final int DESC_COL = 1;
	private WizardMasterInterface wizard;

	public AnnotationPanel(WizardMasterInterface wizard) {
		initComponents();
		this.wizard = wizard;
		setName("Annotations");

		GuiUtil.initTable(codeTable, false);
		refresh();
	}

	private void upActionPerformed(ActionEvent e) {
		int curr = codeTable.getSelectedRow();
		if (curr <= 0) {
			// must have a row selected...and not the first one
			return;
		}
		DefaultTableModel model = (DefaultTableModel) codeTable.getModel();
		int prev = curr - 1;

		for (int col = 0; col < model.getColumnCount(); col++) {
			Object sprev = model.getValueAt(prev, col);
			Object scurr = model.getValueAt(curr, col);
			model.setValueAt(sprev, curr, col);
			model.setValueAt(scurr, prev, col);
		}

	}

	private void deleteActionPerformed(ActionEvent e) {
		DefaultTableModel model = (DefaultTableModel) codeTable.getModel();
		int[] rows = codeTable.getSelectedRows();
		if (rows == null || rows.length == 0) {
			return;
		}

		String suffix = (rows.length == 0) ? "" : "s";
		int ok = GuiUtil.showConfirmDialog( //
				"You are about to remove " + rows.length + " row" + suffix + ".  Confirm?", // 
				"Remove Codes", //
				JOptionPane.OK_CANCEL_OPTION //
				);
		if (ok == JOptionPane.OK_OPTION) {
			for (int idx = rows.length - 1; idx >= 0; idx--) {
				model.removeRow(rows[idx]);
			}
		}

	}

	private void downActionPerformed(ActionEvent e) {
		int curr = codeTable.getSelectedRow();
		int next = curr + 1;
		if (curr < 0 && next < codeTable.getRowCount()) {
			// must have a row selected...and not the last
			return;
		}
		DefaultTableModel model = (DefaultTableModel) codeTable.getModel();

		for (int col = 0; col < model.getColumnCount(); col++) {
			Object snext = model.getValueAt(next, col);
			Object scurr = model.getValueAt(curr, col);
			model.setValueAt(snext, curr, col);
			model.setValueAt(scurr, next, col);
		}
	}

	private void addActionPerformed(ActionEvent e) {
		DefaultTableModel model = (DefaultTableModel) codeTable.getModel();
		for (int row = 0; row < codeTable.getRowCount(); row++) {
			String code = (String) model.getValueAt(row, CODE_COL);
			code = code.trim();
			if (code.length() == 0) {
				log.warn("Cannot add a new row while there is a blank one.");
				return;
			}
		}
		model.addRow(new Object[] { "", "" });
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		scrollPane1 = new JScrollPane();
		codeTable = new JTable();
		panel2 = new JPanel();
		up = new JButton();
		down = new JButton();
		add = new JButton();
		delete = new JButton();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout(
			"[200dlu,default]:grow, $lcgap, [80dlu,default]",
			"fill:default:grow"));

		//======== scrollPane1 ========
		{

			//---- codeTable ----
			codeTable.setPreferredScrollableViewportSize(new Dimension(250, 200));
			codeTable.setModel(new DefaultTableModel(
				new Object[][] {
					{null, null},
					{null, null},
				},
				new String[] {
					"Code", "Description"
				}
			));
			{
				TableColumnModel cm = codeTable.getColumnModel();
				cm.getColumn(0).setResizable(false);
				cm.getColumn(1).setPreferredWidth(200);
			}
			codeTable.setFillsViewportHeight(true);
			scrollPane1.setViewportView(codeTable);
		}
		add(scrollPane1, cc.xy(1, 1));

		//======== panel2 ========
		{
			panel2.setLayout(new FormLayout(
				"default:grow",
				"2*(default, $lgap), default:grow, 2*($lgap, default)"));

			//---- up ----
			up.setText("Up");
			up.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					upActionPerformed(e);
				}
			});
			panel2.add(up, cc.xy(1, 1));

			//---- down ----
			down.setText("Down");
			down.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					downActionPerformed(e);
				}
			});
			panel2.add(down, cc.xy(1, 3));

			//---- add ----
			add.setText("Add");
			add.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					addActionPerformed(e);
				}
			});
			panel2.add(add, cc.xy(1, 7));

			//---- delete ----
			delete.setText("Delete");
			delete.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					deleteActionPerformed(e);
				}
			});
			panel2.add(delete, cc.xy(1, 9));
		}
		add(panel2, cc.xy(3, 1));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JScrollPane scrollPane1;
	private JTable codeTable;
	private JPanel panel2;
	private JButton up;
	private JButton down;
	private JButton add;
	private JButton delete;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	@Override
	public boolean finish() {
		saveCodes();
		return true;
	}

	@Override
	public boolean next() {

		return saveCodes();
	}

	private boolean saveCodes() {
		DefaultTableModel model = (DefaultTableModel) codeTable.getModel();
		PrefUtil.saveUserPref("code_count", "" + model.getRowCount());
		for (int i = 0; i < model.getRowCount(); i++) {
			String code = (String) model.getValueAt(i, CODE_COL);
			String desc = (String) model.getValueAt(i, DESC_COL);
			if (code.length() == 0) {
				code = "[?]";
			}
			PrefUtil.saveUserPref("code_" + i, code);
			PrefUtil.saveUserPref("desc_" + i, desc);
		}
		return true;
	}

	@Override
	public void refresh() {
		DefaultTableModel model = (DefaultTableModel) codeTable.getModel();
		model.setRowCount(0);
		String s_count = PrefUtil.getUserPref("code_count", "0");
		if (s_count == null || s_count.length() == 0 || s_count.equals("0")) {
			return;
		}

		int count = Integer.parseInt(s_count);
		for (int i = 0; i < count; i++) {
			String code = (String) PrefUtil.getUserPref("code_" + i, "");
			String desc = (String) PrefUtil.getUserPref("desc_" + i, "");
			if (code.length() > 0) {
				model.addRow(new Object[] { code, desc });
			}
		}
	}

	@Override
	public void previous() {
		saveCodes();
	}

}
