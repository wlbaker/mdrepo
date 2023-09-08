/*
 * Created by JFormDesigner on Tue Mar 02 12:40:02 CST 2010
 */

package idea.meddaq;

import idea.buffer.SignalBuffer;

import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.table.DefaultTableModel;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import idea.buffer.SignalBuffer;

/**
 * @author User #2
 */
public class MedDAQAnalysisPanel extends JPanel {
	public MedDAQAnalysisPanel() {
		initComponents();
	}

	public void init(int sampleRate, int i, int j) {
		// TODO Auto-generated method stub
		
	}
	
	public void rwaveDetect(SignalBuffer<Integer> rri,
			JLabel saEntLabel2, int rPos, int rrInterval, int rAmplitude) {
		// TODO Auto-generated method stub
		
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		scrollPane1 = new JScrollPane();
		table1 = new JTable();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setLayout(new FormLayout(
			"default:grow",
			"default, $lgap, fill:default, $lgap, default"));

		//======== scrollPane1 ========
		{

			//---- table1 ----
			table1.setModel(new DefaultTableModel(
				new Object[][] {
					{null, null, null, null, null},
				},
				new String[] {
					"O", "Source", "Action", null, "Trend"
				}
			) {
				boolean[] columnEditable = new boolean[] {
					false, false, false, false, true
				};
				@Override
				public boolean isCellEditable(int rowIndex, int columnIndex) {
					return columnEditable[columnIndex];
				}
			});
			scrollPane1.setViewportView(table1);
		}
		add(scrollPane1, cc.xy(1, 3));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}



	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	private JScrollPane scrollPane1;
	private JTable table1;
	// JFormDesigner - End of variables declaration  //GEN-END:variables
}
