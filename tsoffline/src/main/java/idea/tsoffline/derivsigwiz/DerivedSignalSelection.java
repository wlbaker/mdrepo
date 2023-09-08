/*
 * Created by JFormDesigner on Tue Jan 11 14:36:21 CST 2011
 */

package idea.tsoffline.derivsigwiz;


import javax.swing.JComponent;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumnModel;

import com.jgoodies.forms.factories.DefaultComponentFactory;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import idea.GuiUtil;
import idea.gui.WizardPanelInterface;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class DerivedSignalSelection extends JPanel implements WizardPanelInterface, ListSelectionListener {

	private static final int OBJECT_COL = 0;
	public DerivedSignalSelection() {
		initComponents();

		DerivedSigWizard wiz = DerivedSigWizard.getInstance();
		wiz.enableNext(true);
		wiz.enableFinish(false);

		initTable();
	}

	private void initTable() {

		table.getSelectionModel().addListSelectionListener(this);
		refresh();

	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		separator1 = compFactory.createSeparator("Derived Signal");
		scrollPane1 = new JScrollPane();
		table = new JTable();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setLayout(new FormLayout(
			"[350dlu,default]:grow",
			"default, $lgap, fill:default:grow"));
		add(separator1, cc.xy(1, 1));

		//======== scrollPane1 ========
		{

			//---- table ----
			table.setModel(new DefaultTableModel(
				new Object[][] {
					{null, null},
					{null, null},
				},
				new String[] {
					"O", "Derived"
				}
			) {
				boolean[] columnEditable = new boolean[] {
					false, false
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
				cm.getColumn(1).setPreferredWidth(400);
			}
			scrollPane1.setViewportView(table);
		}
		add(scrollPane1, cc.xy(1, 3));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JComponent separator1;
	private JScrollPane scrollPane1;
	private JTable table;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	@Override
	public boolean finish() {
		GuiUtil.showMessage("FIXME: ...under construction...try next");
		return true;
	}

	@Override
	public boolean next() {
		DerivedSigWizard wiz = DerivedSigWizard.getInstance();
		
		int row = table.getSelectedRow();
		String derivedSigName = (String) table.getValueAt( row, OBJECT_COL );
		
		wiz.pushPage(derivedSigName);
		return true;

	}

	@Override
	public void refresh() {
		
		DefaultTableModel model = (DefaultTableModel) table.getModel();

		model.setRowCount( 0 );
		model.addRow( new Object[] { "RECUR", "Recursion Plot" } );
		model.addRow( new Object[] { "RRI", "RRI Segmentation" } );
		model.addRow( new Object[] { "IBI", "Breath Interval Segmentation" } );
		
		model.addRow( new Object[] { "HIST", "<Histogram>" } );
		model.addRow( new Object[] { "SEC", "Sample Entropy -- Continuous" } );
		model.addRow( new Object[] { "SEI", "Sample Entropy -- Interval" } );
		model.addRow( new Object[] { "MSE", "Multiscale Entropy" } );
		model.addRow( new Object[] { "QSE", "Quadratic Sample Entropy" } );
		model.addRow( new Object[] { "LYA", "Lyapunov" } );
		model.addRow( new Object[] { "STD", "Standard Set -- Interval" } );

	}

	@Override
	public void valueChanged(ListSelectionEvent e) {
		if( e.getValueIsAdjusting() ) {
			return;
		}
		
		DerivedSigWizard wiz = DerivedSigWizard.getInstance();
		wiz.enableFinish( e.getFirstIndex() >= 0 );
		
	}

	@Override
	public void previous() {
		// TODO Auto-generated method stub
		
	}
}
