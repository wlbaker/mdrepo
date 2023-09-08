/*
 * Created by JFormDesigner on Fri Jan 15 17:02:06 CST 2010
 */

package idea.repository.gui;

import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.JTree;
import javax.swing.table.DefaultTableModel;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

/**
 * @author User #2
 */
public class RepositoryExploratoryPanel extends JPanel {
	public RepositoryExploratoryPanel() {
		initComponents();
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		panel1 = new JPanel();
		scrollPane2 = new JScrollPane();
		tree1 = new JTree();
		scrollPane1 = new JScrollPane();
		table1 = new JTable();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setLayout(new FormLayout(
			"default:grow",
			"default, 2*($lgap, fill:default:grow)"));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"default, $lcgap, default",
				"fill:default:grow"));

			//======== scrollPane2 ========
			{
				scrollPane2.setViewportView(tree1);
			}
			panel1.add(scrollPane2, cc.xy(1, 1));

			//======== scrollPane1 ========
			{

				//---- table1 ----
				table1.setModel(new DefaultTableModel(
					new Object[][] {
						{null, "", null, null, null},
						{null, null, null, null, null},
					},
					new String[] {
						"Device", "Start Time", "End Time", "??", null
					}
				));
				scrollPane1.setViewportView(table1);
			}
			panel1.add(scrollPane1, cc.xy(3, 1));
		}
		add(panel1, cc.xy(1, 5));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	private JPanel panel1;
	private JScrollPane scrollPane2;
	private JTree tree1;
	private JScrollPane scrollPane1;
	private JTable table1;
	// JFormDesigner - End of variables declaration  //GEN-END:variables
}
