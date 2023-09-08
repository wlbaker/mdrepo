/*
 * Created by JFormDesigner on Thu May 09 14:14:45 CDT 2019
 */

package idea.tsoffline.event_editor;

import java.awt.Color;
import java.awt.event.ActionEvent;
import java.util.Date;
import java.util.LinkedList;
import java.util.List;
import java.util.ListIterator;

import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumn;
import javax.swing.table.TableColumnModel;

import org.piccolo2d.PLayer;
import org.piccolo2d.PNode;

import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.layout.FormLayout;

import net.miginfocom.swing.MigLayout;
import idea.GuiUtil;
import idea.tsoffline.ColorManager;
import idea.tsoffline.canvas.TsPSwingCanvas;

/**
 * @author WILLIAM BAKER
 */
public class PhaseExplorer extends JPanel {
	private static final int OBJECT_COL = 0;
	private final static int NAME_COL = 1;
	private final static int COLOR_COL = 2;
	private final static int START_COL = 3;
	private final static int STOP_COL = 4;
	private TsPSwingCanvas canvas;
	
	boolean ok = false;
	List<PNode> deletedList = new LinkedList<PNode>();
	
	public PhaseExplorer(TsPSwingCanvas canvas) {
		this.canvas = canvas;

		initComponents();
		GuiUtil.initTable( table1 , true );
	
		refresh();
		
		initTable( table1 );
	}

	private void initTable(JTable table12) {
		TableColumn col = table1.getColumnModel().getColumn(COLOR_COL);
		GuiUtil.initColorColumn(col, ColorManager.getColors());
		
	}

	private void refresh() {
		DefaultTableModel model = (DefaultTableModel)table1.getModel();
		model.setRowCount(0);
		
		PLayer phaseLayer = canvas.getPhaseLayer();
		if (phaseLayer != null) {
			ListIterator<PNode> it = phaseLayer.getChildrenIterator();
			while (it != null && it.hasNext()) {
				PNode node = it.next();
				long tm0 = canvas.getStartTime();
				long start_tm = tm0 + (long) (1000 * node.getX() );
				long end_tm = start_tm + (long) (1000 * node.getWidth() );
				
				model.addRow( new Object[] { node, node.getName(), node.getPaint(), new Date(start_tm), new Date(end_tm) } );
			}
		}

	}

	private void applyActionPerformed(ActionEvent e) {
		this.ok = true;
		long tm0 = canvas.getStartTime();
		DefaultTableModel model = (DefaultTableModel)table1.getModel();
		for( int row = 0; row < model.getRowCount(); row++  ) {
			PNode node = (PNode) model.getValueAt( row, OBJECT_COL );
			String name = (String) model.getValueAt( row, NAME_COL);
			Color color = (Color) model.getValueAt( row, COLOR_COL);
			Date start = (Date)model.getValueAt( row, START_COL );
			Date stop = (Date)model.getValueAt( row, STOP_COL );
			
			node.setPaint( color );
			node.setName( name );
			node.setX( (start.getTime() - tm0) / 1000.0 );
			node.setWidth( (stop.getTime() - start.getTime())  / 1000.0 );
		}
		PLayer phaseLayer = canvas.getPhaseLayer();
		for( PNode node : deletedList ) {
			phaseLayer.removeChild( node );
		}
		cancelActionPerformed(e);
	}

	private void cancelActionPerformed(ActionEvent e) {
		GuiUtil.closeDialog(this);
	}

	private void deleteRowActionPerformed(ActionEvent e) {
		DefaultTableModel model = (DefaultTableModel)table1.getModel();
		int [] selectedRows = table1.getSelectedRows();
		for( int idx = selectedRows.length - 1; idx >= 0 ; idx-- ) {
			int row = selectedRows[idx];
			PNode node = (PNode) model.getValueAt(row, OBJECT_COL);
			deletedList.add(node);
			model.removeRow(row);
		}
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		scrollPane1 = new JScrollPane();
		table1 = new JTable();
		panel2 = new JPanel();
		apply = new JButton();
		deleteRow = new JButton();
		cancel = new JButton();

		//======== this ========
		setLayout(new MigLayout(
			"hidemode 3",
			// columns
			"[grow,fill]" +
			"[fill]",
			// rows
			"[]" +
			"[grow,fill]0" +
			"[]0" +
			"[]0" +
			"[]0" +
			"[]" +
			"[]"));

		//======== scrollPane1 ========
		{

			//---- table1 ----
			table1.setModel(new DefaultTableModel(
				new Object[][] {
					{null, null, null, null, null},
					{null, null, null, null, null},
				},
				new String[] {
					"O", "Name", "Color", "Start", "Stop"
				}
			) {
				Class<?>[] columnTypes = new Class<?>[] {
					Object.class, String.class, Object.class, Date.class, Date.class
				};
				boolean[] columnEditable = new boolean[] {
					false, true, true, true, true
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
				TableColumnModel cm = table1.getColumnModel();
				cm.getColumn(0).setResizable(false);
				cm.getColumn(0).setMinWidth(1);
				cm.getColumn(0).setMaxWidth(1);
				cm.getColumn(0).setPreferredWidth(1);
				cm.getColumn(1).setPreferredWidth(160);
				cm.getColumn(2).setPreferredWidth(60);
				cm.getColumn(3).setPreferredWidth(100);
				cm.getColumn(4).setPreferredWidth(100);
			}
			scrollPane1.setViewportView(table1);
		}
		add(scrollPane1, "cell 0 1");

		//======== panel2 ========
		{
			panel2.setLayout(new FormLayout(
				"default:grow, $lcgap, [50dlu,default], $lcgap, default, $lcgap, [50dlu,default]",
				"default"));

			//---- apply ----
			apply.setText("Apply");
			apply.addActionListener(e -> applyActionPerformed(e));
			panel2.add(apply, CC.xy(3, 1));

			//---- deleteRow ----
			deleteRow.setText("Delete");
			deleteRow.addActionListener(e -> deleteRowActionPerformed(e));
			panel2.add(deleteRow, CC.xy(5, 1));

			//---- cancel ----
			cancel.setText("Cancel");
			cancel.addActionListener(e -> cancelActionPerformed(e));
			panel2.add(cancel, CC.xy(7, 1));
		}
		add(panel2, "cell 0 6");
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	private JScrollPane scrollPane1;
	private JTable table1;
	private JPanel panel2;
	private JButton apply;
	private JButton deleteRow;
	private JButton cancel;
	// JFormDesigner - End of variables declaration  //GEN-END:variables
	public boolean isOk() {
		return ok;
	}
}
