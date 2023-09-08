/*
 * Created by JFormDesigner on Tue Jul 26 14:42:10 CDT 2011
 */

package idea.analysis;


import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumnModel;

import idea.GuiUtil;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class SignalPriorityPanel extends JPanel {
	
	private boolean didOk = false;
	
	public SignalPriorityPanel() {
		initComponents();
	}
	
	public void setSignals() {
		// TODO Auto-generated method stub
		
	}
	
	public boolean isOk() {
		return didOk;
	}

	private void cancelActionPerformed(ActionEvent e) {
		GuiUtil.closeDialog( this );
	}

	private void okActionPerformed(ActionEvent e) {
		didOk  = true;
		GuiUtil.closeDialog(this);
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		panel2 = new JPanel();
		scrollPane1 = new JScrollPane();
		table1 = new JTable();
		panel1 = new JPanel();
		button1 = new JButton();
		button2 = new JButton();
		panel3 = new JPanel();
		ok = new JButton();
		cancel = new JButton();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setLayout(new FormLayout(
			"default",
			"default, $lgap, default"));

		//======== panel2 ========
		{
			panel2.setLayout(new FormLayout(
				"default:grow, $lcgap, default",
				"fill:default:grow"));

			//======== scrollPane1 ========
			{

				//---- table1 ----
				table1.setModel(new DefaultTableModel(
					new Object[][] {
						{null, null, null, null},
						{null, null, null, null},
					},
					new String[] {
						"O", "Enable", "Code", "Description"
					}
				) {
					Class<?>[] columnTypes = new Class<?>[] {
						Object.class, Boolean.class, Object.class, Object.class
					};
					boolean[] columnEditable = new boolean[] {
						false, true, true, true
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
					cm.getColumn(2).setPreferredWidth(60);
					cm.getColumn(3).setPreferredWidth(200);
				}
				scrollPane1.setViewportView(table1);
			}
			panel2.add(scrollPane1, cc.xy(1, 1));

			//======== panel1 ========
			{
				panel1.setLayout(new FormLayout(
					"default",
					"3*(default, $lgap), default"));

				//---- button1 ----
				button1.setText("Up");
				panel1.add(button1, cc.xy(1, 3));

				//---- button2 ----
				button2.setText("Down");
				panel1.add(button2, cc.xy(1, 5));
			}
			panel2.add(panel1, cc.xy(3, 1));
		}
		add(panel2, cc.xy(1, 1));

		//======== panel3 ========
		{
			panel3.setLayout(new FormLayout(
				"default:grow, 2*($lcgap, [50dlu,default])",
				"default"));

			//---- ok ----
			ok.setText("OK");
			ok.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					okActionPerformed(e);
				}
			});
			panel3.add(ok, cc.xy(3, 1));

			//---- cancel ----
			cancel.setText("Cancel");
			cancel.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					cancelActionPerformed(e);
				}
			});
			panel3.add(cancel, cc.xy(5, 1));
		}
		add(panel3, cc.xy(1, 3));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JPanel panel2;
	private JScrollPane scrollPane1;
	private JTable table1;
	private JPanel panel1;
	private JButton button1;
	private JButton button2;
	private JPanel panel3;
	private JButton ok;
	private JButton cancel;
	// JFormDesigner - End of variables declaration  //GEN-END:variables
}
