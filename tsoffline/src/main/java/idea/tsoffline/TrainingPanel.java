/*
 * Created by JFormDesigner on Sun Mar 05 13:47:21 CST 2017
 */

package idea.tsoffline;

import java.awt.Desktop;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.io.File;
import java.io.IOException;

import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.ListSelectionModel;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumnModel;

import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.layout.FormLayout;

import idea.GuiUtil;

/**
 * @author User #1
 */
public class TrainingPanel extends JPanel {
	
	private final static int OBJECT_COL = 0;
	private final static int FILENAME_COL = 1;
	
	public TrainingPanel() {
		initComponents();
		
		launch.setEnabled(false);
		ListSelectionModel selmod = table1.getSelectionModel();
		selmod.setSelectionMode( ListSelectionModel.SINGLE_SELECTION );
		selmod.addListSelectionListener( new ListSelectionListener() {

			@Override
			public void valueChanged(ListSelectionEvent e) {
				if( e.getValueIsAdjusting() ) {
					return;
				}
				
				launch.setEnabled( e.getFirstIndex() >= 0 );
				
			} } );
		
		populate();
	}

	private void populate() {
		DefaultTableModel model = (DefaultTableModel)table1.getModel();
		model.setRowCount(0);
		
		String r_home = System.getenv("R_HOME");
		
		File fr_home = new File(r_home);
		File training_home = new File(fr_home,"training");
		File [] files = training_home.listFiles();
		if( files != null ) {
			for( File f : files ) {
				if( f.isDirectory() ) {
					continue;  // ignore
				}
				if( f.isHidden() ) {
					continue;  // ignore Thumbs.db
				}
				model.addRow( new Object[] { f, f.getName(), null} );
			}
		}
	}

	private void launchActionPerformed(ActionEvent e) {
		int row = table1.getSelectedRow();
		if( row >= 0 ) {
			File f = (File) table1.getValueAt( row, OBJECT_COL);
			try {
				Desktop.getDesktop().open(f);
			} catch (IOException e1) {
				GuiUtil.showError( "Could not open file: " + f, e1 );
			}
		}
	}

	private void closeActionPerformed(ActionEvent e) {
		GuiUtil.closeDialog(this);
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		scrollPane1 = new JScrollPane();
		table1 = new JTable();
		panel1 = new JPanel();
		launch = new JButton();
		close = new JButton();

		//======== this ========
		setLayout(new FormLayout(
			"default:grow",
			"default, $lgap, fill:default:grow, $lgap, default"));

		//======== scrollPane1 ========
		{

			//---- table1 ----
			table1.setPreferredScrollableViewportSize(new Dimension(450, 200));
			table1.setModel(new DefaultTableModel(
				new Object[][] {
					{null, null, null},
					{null, null, null},
				},
				new String[] {
					"O", "Module", "Description"
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
				TableColumnModel cm = table1.getColumnModel();
				cm.getColumn(0).setResizable(false);
				cm.getColumn(0).setMinWidth(1);
				cm.getColumn(0).setMaxWidth(1);
				cm.getColumn(0).setPreferredWidth(1);
				cm.getColumn(1).setPreferredWidth(100);
				cm.getColumn(2).setPreferredWidth(200);
			}
			scrollPane1.setViewportView(table1);
		}
		add(scrollPane1, CC.xy(1, 3));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"default:grow, 2*($lcgap, [50dlu,default])",
				"default"));

			//---- launch ----
			launch.setText("Launch");
			launch.addActionListener(e -> {
			launchActionPerformed(e);
			launchActionPerformed(e);
		});
			panel1.add(launch, CC.xy(3, 1));

			//---- close ----
			close.setText("Close");
			close.addActionListener(e -> closeActionPerformed(e));
			panel1.add(close, CC.xy(5, 1));
		}
		add(panel1, CC.xy(1, 5));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	private JScrollPane scrollPane1;
	private JTable table1;
	private JPanel panel1;
	private JButton launch;
	private JButton close;
	// JFormDesigner - End of variables declaration  //GEN-END:variables
}
