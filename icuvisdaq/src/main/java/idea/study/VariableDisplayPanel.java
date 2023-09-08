/*
 * Created by JFormDesigner on Fri Dec 21 09:32:21 CST 2012
 */

package idea.study;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumnModel;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

/**
 * @author User #1
 */
public class VariableDisplayPanel extends JPanel {
	public VariableDisplayPanel() {
		initComponents();
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		scrollPane1 = new JScrollPane();
		table1 = new JTable();
		panel1 = new JPanel();
		label1 = new JLabel();
		printerList = new JComboBox();
		print = new JButton();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setLayout(new FormLayout(
			"default:grow",
			"default, $lgap, fill:default:grow, $lgap, default"));

		//======== scrollPane1 ========
		{

			//---- table1 ----
			table1.setModel(new DefaultTableModel(
				new Object[][] {
					{null, null, null, null, null},
					{null, null, null, null, null},
				},
				new String[] {
					"O", "Name", "Description", "Value", "Trend"
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
				TableColumnModel cm = table1.getColumnModel();
				cm.getColumn(0).setMinWidth(1);
				cm.getColumn(0).setMaxWidth(1);
				cm.getColumn(0).setPreferredWidth(1);
			}
			scrollPane1.setViewportView(table1);
		}
		add(scrollPane1, cc.xy(1, 3));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"default, $lcgap, default:grow, 2*($lcgap, default), $lcgap, [50dlu,default]",
				"default"));

			//---- label1 ----
			label1.setText("Printer:");
			panel1.add(label1, cc.xy(1, 1));
			panel1.add(printerList, cc.xy(3, 1));

			//---- print ----
			print.setText("Print");
			panel1.add(print, cc.xy(9, 1));
		}
		add(panel1, cc.xy(1, 5));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JScrollPane scrollPane1;
	private JTable table1;
	private JPanel panel1;
	private JLabel label1;
	private JComboBox printerList;
	private JButton print;
	// JFormDesigner - End of variables declaration  //GEN-END:variables
}
