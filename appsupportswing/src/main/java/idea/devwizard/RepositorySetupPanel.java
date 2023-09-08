/*
 * Created by JFormDesigner on Fri Apr 16 12:30:26 CDT 2010
 */

package idea.devwizard;

import java.awt.Dimension;
import java.awt.event.ActionEvent;

import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumnModel;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.factories.DefaultComponentFactory;
import com.jgoodies.forms.layout.FormLayout;

import idea.GuiUtil;
import idea.gui.WizardMasterInterface;
import idea.gui.WizardPanelInterface;
import idea.repository.RepositoryFactory;
import idea.repository.RepositoryInterface;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class RepositorySetupPanel extends JPanel implements WizardPanelInterface {

	private WizardMasterInterface wizard;

	public RepositorySetupPanel(WizardMasterInterface wizard) {
		initComponents();
		setName("Repository");

		this.wizard = wizard;

		GuiUtil.initPanel(this);

		refresh();
	}

	private void addRemoteActionPerformed(ActionEvent e) {
		RepositoryAddEditPanel panel = new RepositoryAddEditPanel(wizard);
		wizard.pushPage(panel);
	}

	private void removeRemoteActionPerformed(ActionEvent e) {
		int row = repo_table.getSelectedRow();
		if (row >= 0) {

			RepositoryInterface repo = (RepositoryInterface) repo_table.getValueAt(row, 0);

			int ok = GuiUtil.showConfirmDialog("You are about to delete " + repo.getName() +".  Are you sure?",
					"Delete Repository", JOptionPane.YES_NO_CANCEL_OPTION);
			if (ok == JOptionPane.YES_OPTION) {
				RepositoryFactory.unregister(repo.getName());
			}
		}

		refresh();
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		separator3 = compFactory.createSeparator("Remote Repositories");
		panel2 = new JPanel();
		scrollPane1 = new JScrollPane();
		repo_table = new JTable();
		panel4 = new JPanel();
		addRemote = new JButton();
		removeRemote = new JButton();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout(
			"default:grow",
			"default, $lgap, fill:[20dlu,default]:grow"));
		add(separator3, CC.xy(1, 1));

		//======== panel2 ========
		{
			panel2.setLayout(new FormLayout(
				"[40dlu,default], $lcgap, default:grow, $lcgap, [50dlu,default]",
				"fill:default:grow"));

			//======== scrollPane1 ========
			{
				scrollPane1.setPreferredSize(new Dimension(100, 50));

				//---- repo_table ----
				repo_table.setModel(new DefaultTableModel(
					new Object[][] {
						{null, null, null},
						{null, null, null},
					},
					new String[] {
						"O", "Type", "Connection"
					}
				) {
					boolean[] columnEditable = new boolean[] {
						false, false, false
					};
					@Override
					public boolean isCellEditable(int rowIndex, int columnIndex) {
						return columnEditable[columnIndex];
					}
				});
				{
					TableColumnModel cm = repo_table.getColumnModel();
					cm.getColumn(0).setResizable(false);
					cm.getColumn(0).setMinWidth(1);
					cm.getColumn(0).setMaxWidth(1);
					cm.getColumn(0).setPreferredWidth(1);
					cm.getColumn(1).setResizable(false);
					cm.getColumn(1).setMinWidth(90);
					cm.getColumn(1).setMaxWidth(90);
					cm.getColumn(1).setPreferredWidth(90);
					cm.getColumn(2).setPreferredWidth(300);
				}
				scrollPane1.setViewportView(repo_table);
			}
			panel2.add(scrollPane1, CC.xy(3, 1));

			//======== panel4 ========
			{
				panel4.setLayout(new FormLayout(
					"80dlu",
					"default:grow, 2*($lgap, default)"));

				//---- addRemote ----
				addRemote.setText("Add");
				addRemote.addActionListener(e -> addRemoteActionPerformed(e));
				panel4.add(addRemote, CC.xy(1, 3));

				//---- removeRemote ----
				removeRemote.setText("Remove");
				removeRemote.addActionListener(e -> removeRemoteActionPerformed(e));
				panel4.add(removeRemote, CC.xy(1, 5));
			}
			panel2.add(panel4, CC.xy(5, 1));
		}
		add(panel2, CC.xy(1, 3));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JComponent separator3;
	private JPanel panel2;
	private JScrollPane scrollPane1;
	private JTable repo_table;
	private JPanel panel4;
	private JButton addRemote;
	private JButton removeRemote;
	// JFormDesigner - End of variables declaration //GEN-END:variables
	@Override
	public boolean finish() {
		return true;
	}

	@Override
	public boolean next() {
		// saveActionPerformed(null);

		return true;
	}

	@Override
	public void refresh() {
		RepositoryInterface[] repos = RepositoryFactory.getRegisteredRepositories();
		DefaultTableModel model = (DefaultTableModel) repo_table.getModel();
		model.setRowCount( 0 );
		if( repos != null ) {
			for( RepositoryInterface r : repos ) {
				if( "LOCAL".equals(r.getName()) ) {
					// skip local, this is a remote list only
				} else {
					model.addRow( new Object[] { r, r.getName(), r.toString() } );
				}
			}
		}
	}

	@Override
	public void previous() {
		// TODO Auto-generated method stub

	}
}
