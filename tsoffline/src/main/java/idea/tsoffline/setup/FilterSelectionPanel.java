/*
 * Created by JFormDesigner on Fri Apr 05 15:08:43 CDT 2019
 */

package idea.tsoffline.setup;

import java.awt.event.ActionEvent;
import java.util.List;

import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumnModel;

import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.layout.FormLayout;

import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;
import idea.devwizard.SetupWizardInterface;
import idea.gui.WizardPanelInterface;
import idea.ts.TsFilter;
import idea.ts.TsoPrefs;
import idea.tsoffline.AppFrame;

/**
 * @author WILLIAM BAKER
 */
@Slf4j
public class FilterSelectionPanel extends JPanel implements WizardPanelInterface, ListSelectionListener {
	
	private static final int OBJECT_COL = 0;
	private static final int BIDIR_COL = 3;
	
	private SetupWizardInterface wizard;
	private FilterSetupDesignPanel designer;
	
	private TsoPrefs prefs;
	
	
	public FilterSelectionPanel(SetupWizardInterface wizard) {
		setName("Filter Selection");
		this.wizard = wizard;
		
		initComponents();
		
		GuiUtil.initTable(table, true);

		table.getSelectionModel().addListSelectionListener(this);
		
		refresh();
	}

	private void addButtonActionPerformed(ActionEvent e) {

		if( designer == null ) {
			designer = new FilterSetupDesignPanel( wizard );
			designer.setName("Design");
		}
		wizard.pushPage( designer );
		wizard.enableFinish( false );
	}

	private void deleteButtonActionPerformed(ActionEvent e) {
		int row = table.getSelectedRow();
		
		DefaultTableModel model = (DefaultTableModel) table.getModel();
		model.removeRow(row);

		//table.clearSelection();
		// deleteButton.setEnabled( false );
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		scrollPane1 = new JScrollPane();
		table = new JTable();
		panel1 = new JPanel();
		addButton = new JButton();
		deleteButton = new JButton();

		//======== this ========
		setLayout(new FormLayout(
			"default:grow",
			"default, $lgap, fill:default:grow, $lgap, default"));

		//======== scrollPane1 ========
		{

			//---- table ----
			table.setModel(new DefaultTableModel(
				new Object[][] {
					{null, null, false, false, null},
					{null, null, null, null, null},
				},
				new String[] {
					"O", "Name", "Global", "BiDir", "Description"
				}
			) {
				Class<?>[] columnTypes = new Class<?>[] {
					Object.class, Object.class, Boolean.class, Boolean.class, Object.class
				};
				boolean[] columnEditable = new boolean[] {
					false, true, false, true, false
				};
				@Override
				public Class<?> getColumnClass(int columnIndex) {
					return columnTypes[columnIndex];
				}
				@Override
				public boolean isCellEditable(int rowIndex, int columnIndex) {
					return columnEditable[columnIndex];
				}
			});
			{
				TableColumnModel cm = table.getColumnModel();
				cm.getColumn(0).setResizable(false);
				cm.getColumn(0).setMinWidth(1);
				cm.getColumn(0).setMaxWidth(1);
				cm.getColumn(0).setPreferredWidth(1);
				cm.getColumn(2).setMinWidth(40);
				cm.getColumn(2).setMaxWidth(40);
				cm.getColumn(2).setPreferredWidth(40);
				cm.getColumn(3).setMinWidth(40);
				cm.getColumn(3).setMaxWidth(40);
				cm.getColumn(3).setPreferredWidth(40);
				cm.getColumn(4).setPreferredWidth(200);
			}
			scrollPane1.setViewportView(table);
		}
		add(scrollPane1, CC.xy(1, 3));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"default:grow, 2*($lcgap, default)",
				"default"));

			//---- addButton ----
			addButton.setText("Add");
			addButton.addActionListener(e -> addButtonActionPerformed(e));
			panel1.add(addButton, CC.xy(3, 1));

			//---- deleteButton ----
			deleteButton.setText("Delete");
			deleteButton.setEnabled(false);
			deleteButton.addActionListener(e -> deleteButtonActionPerformed(e));
			panel1.add(deleteButton, CC.xy(5, 1));
		}
		add(panel1, CC.xy(1, 5));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	private JScrollPane scrollPane1;
	private JTable table;
	private JPanel panel1;
	private JButton addButton;
	private JButton deleteButton;
	// JFormDesigner - End of variables declaration  //GEN-END:variables
	@Override
	public void refresh() {
		
		DefaultTableModel model = (DefaultTableModel)table.getModel();
		model.setRowCount(0);
		
		prefs = AppFrame.getInstance().getPrefs();
		List<TsFilter> filters = prefs.getFilters();
		
		for( TsFilter filter : filters ) {
			String name = filter.getName();
			if( name == null ) name = "";
			String desc = filter.getDescription();
			if( desc == null || desc.length() == 0 ) {
				// ignore
			} else {
				model.addRow( new Object[] { filter, filter.getName(), filter.isGlobal(), filter.isBidirectional(), filter.getDescription() } );
			}
		}
	}

	@Override
	public boolean finish() {
		saveFilters();
		return true;
	}

	@Override
	public void valueChanged(ListSelectionEvent e) {
		int row = table.getSelectedRow();

		// wizard.enableNext(row >= 0);
		deleteButton.setEnabled( row >= 0 );
	}

	@Override
	public boolean next() {
		return saveFilters();
	}

	private boolean saveFilters() {
		DefaultTableModel model = (DefaultTableModel)table.getModel();
		
		for( int row = 0; row < model.getRowCount(); row++ ) {
			TsFilter filter = (TsFilter) model.getValueAt( row, OBJECT_COL );
			Boolean bidir = (Boolean) model.getValueAt( row, BIDIR_COL );
			
			filter.setBidirectional( bidir );
		}
		return true;
	}

	@Override
	public void previous() {
		// TODO Auto-generated method stub
		
	}

	public void setPrefs(TsoPrefs prefs) {
		this.prefs = prefs;
		refresh();
	}
}
