/*
 * Created by JFormDesigner on Thu Jul 31 15:10:16 CDT 2014
 */

package idea.tsoffline.wiz;

import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;

import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableCellEditor;
import javax.swing.table.TableCellRenderer;
import javax.swing.table.TableColumnModel;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.DefaultComponentFactory;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import idea.schema.rp.RpStudy;
import idea.schema.rp.RpSubject;
import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;
import idea.gui.TableSorter;
import idea.gui.WizardMasterInterface;
import idea.gui.WizardPanelInterface;
import idea.repository.RepositoryFactory;
import idea.repository.RepositoryInterface;

/**
 * @author User #1
 */
@Slf4j
public class SubjectSelectionPanel extends JPanel implements WizardPanelInterface, ListSelectionListener {
	private static final int OBJ_COL = 0;
	private static final int SUBJECT_COL = 1;
	private static final int BRANCH_COL = 2;
	private static final int DATE_COL = 3;
	
	private WizardMasterInterface wizard;
	private RpStudy study;
	public SubjectSelectionPanel( WizardMasterInterface wizard ) {
		initComponents();
		this.wizard = wizard;
		
		initTable();
		
		refresh.setEnabled( true );
	}

	private void initTable() {
		TableSorter sorter = new TableSorter(table.getModel());

		table.setAutoCreateColumnsFromModel(false);
		table.setModel(sorter);
		sorter.setTableHeader(table.getTableHeader());
		sorter.setSortingStatus(SUBJECT_COL, TableSorter.ASCENDING);

		table.getSelectionModel().addListSelectionListener(this);
		
	}

	public void setStudy(RpStudy study) throws Exception {
		this.study = study;
		refreshActionPerformed(null);
	}
	
	private void refreshActionPerformed(ActionEvent e) {
		refresh();
	}

	private void _refresh() throws Exception {
		TableSorter sorter = (TableSorter) table.getModel();
		
		DefaultTableModel model = (DefaultTableModel)sorter.getTableModel();
		model.setRowCount(0);
		
		assert( study != null ): "Study cannot be null";
		
		RepositoryInterface local = RepositoryFactory.getLocalRepository();

		List<RpSubject> subjects = local.getSubjectList( study );
		for( RpSubject subject : subjects ) {
			model.addRow( new Object[] { subject, subject.getBaseFileName(), subject.getIdentifier(), subject.getBranch(),  subject.getSurgeryDate() } );
		}
		
		
		sorter.refresh();
	}

	protected TableCellEditor tableGetCellEditor(TableCellEditor defaultEditor,
			int row, int column) {
//		if (column == COL_PORT) {
//			TableCellEditor editor = editors.get(row);
//			if (editor != null) {
//				// editor.
//				return editor;
//			}
//		}
		return defaultEditor;
	}

	private TableCellRenderer tableGetCellRenderer(
			TableCellRenderer defaultRenderer, int row, int column) {

//		if (renderers != null && column == COL_PORT) {
//			Object pp = table.getValueAt(row, COL_PORT);
//			if (pp instanceof JComboBox) {
//				JComboBox combo = (JComboBox) pp;
//				pp = combo.getSelectedItem();
//			}
//
//			TableCellRenderer renderer = renderers.get(row);
//			if (renderer != null) {
//				if (renderer instanceof ComboCellRenderer) {
//					ComboCellRenderer ccr = (ComboCellRenderer) renderer;
//
//					ccr.setSelectedItem(pp);
//				}
//				return renderer;
//			}
//
//		}
		return defaultRenderer;
	}
	
	public RpSubject getSelectedSubject() {
		return selected_subject;
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		separator1 = compFactory.createSeparator("Subjects");
		panel2 = new JPanel();
		scrollPane1 = new JScrollPane();
		table = new JTable() {
			@Override
		    public TableCellEditor getCellEditor(int row, int column) {
				return tableGetCellEditor(super.getCellEditor(row, column), row, column );
		    }
			@Override
		    public TableCellRenderer getCellRenderer(int row, int column) {
				return tableGetCellRenderer(super.getCellRenderer(row, column), row, column );
		    }
		};
		panel3 = new JPanel();
		statusMessage = new JLabel();
		refresh = new JButton();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout(
			"default:grow",
			"default, $ugap, fill:default:grow, $lgap, default"));
		add(separator1, cc.xy(1, 1));

		//======== panel2 ========
		{
			panel2.setLayout(new FormLayout(
				"default:grow",
				"fill:default:grow"));

			//======== scrollPane1 ========
			{
				scrollPane1.setPreferredSize(new Dimension(154, 223));

				//---- table ----
				table.setModel(new DefaultTableModel(
					new Object[][] {
						{null, null, null, null, null},
					},
					new String[] {
						"O", "File", "Subject", "Arm", "Date"
					}
				) {
					boolean[] columnEditable = new boolean[] {
						false, false, false, false, false
					};
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
					cm.getColumn(1).setPreferredWidth(200);
					cm.getColumn(2).setPreferredWidth(60);
					cm.getColumn(3).setPreferredWidth(60);
					cm.getColumn(4).setPreferredWidth(100);
				}
				scrollPane1.setViewportView(table);
			}
			panel2.add(scrollPane1, cc.xy(1, 1));
		}
		add(panel2, cc.xy(1, 3));

		//======== panel3 ========
		{
			panel3.setLayout(new FormLayout(
				"default:grow, $lcgap, default, $lcgap, [50dlu,default]",
				"default"));

			//---- statusMessage ----
			statusMessage.setText(" ");
			panel3.add(statusMessage, cc.xy(1, 1));

			//---- refresh ----
			refresh.setText("Refresh");
			refresh.setEnabled(false);
			refresh.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					refreshActionPerformed(e);
				}
			});
			panel3.add(refresh, cc.xy(5, 1));
		}
		add(panel3, cc.xy(1, 5));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JComponent separator1;
	private JPanel panel2;
	private JScrollPane scrollPane1;
	private JTable table;
	private JPanel panel3;
	private JLabel statusMessage;
	private JButton refresh;
	private RpSubject selected_subject;
	// JFormDesigner - End of variables declaration  //GEN-END:variables
	@Override
	public void valueChanged(ListSelectionEvent e) {
		int row = table.getSelectedRow();

		wizard.enableNext(row >= 0);
		wizard.enableFinish(row >= 0);

		RpSubject subject = (RpSubject) ((row >= 0) ? table.getValueAt(row, OBJ_COL) : null);
		selected_subject = subject;
	}

	@Override
	public void refresh() {
		try {
			_refresh();
		} catch (Exception e1) {
			GuiUtil.showError("Error in subject selection", e1);
		}
	}

	@Override
	public void previous() {
		// ok
	}

	@Override
	public boolean next() {
		int row = table.getSelectedRow();
		return (row >= 0);
	}

	@Override
	public boolean finish() {
		return true;
	}
	
}
