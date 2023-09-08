/*
 * Created by JFormDesigner on Tue Mar 02 11:32:48 CST 2010
 */

package idea.meddaq;

import idea.intf.AdapterInterface;
import idea.model.Alarm;

import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.FocusAdapter;
import java.awt.event.FocusEvent;
import java.text.SimpleDateFormat;
import java.util.Date;

import javax.swing.DefaultComboBoxModel;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumnModel;

import idea.gui.ExcelAdapter;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;
import com.toedter.calendar.JDateChooser;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class MessagesPanel extends JPanel {

	private final static int COL_OBJ = 0;
	private final static int COL_TIME = 1;
	private final static int COL_STATUS = 2;
	private final static int COL_DEVICE = 3;
	private final static int COL_MESSAGE = 4;

	public MessagesPanel() {
		initComponents();

		clearActionPerformed(null);
		setSimulate( false );
		
		new ExcelAdapter(alarmTable);
		eventTimeChooser.setDateFormatString("MM/dd/yyyy HH:mm:ss");

		alarmTable.getSelectionModel().addListSelectionListener( new ListSelectionListener() {

			@Override
			public void valueChanged(ListSelectionEvent e) {
				if( e.getValueIsAdjusting() ) {
					return;
				}
				
				int idx = e.getFirstIndex();
				Date dt = (Date) alarmTable.getValueAt( idx, COL_OBJ);
				
				eventTimeChooser.setDate( dt );
			} } );
	}
	
	public void setSimulate( boolean simulate ) {
		if( simulate ) {
			clear.setVisible( false );
			go_to.setVisible( true );
		}  else {
			clear.setVisible( true );
			go_to.setVisible( false );
		}
	}

	private void clearActionPerformed(ActionEvent e) {
		clear();
	}
	
	public void clear() {
		DefaultTableModel model = (DefaultTableModel) alarmTable.getModel();
		model.setRowCount(0);
	}

	public void addMessage(Date now, Object source, int info, String msg) {
		DefaultTableModel model = (DefaultTableModel) alarmTable.getModel();

		SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		String s_info;

		switch (info) {
		case Alarm.INFO:
			s_info = "Info";
			break;
		case Alarm.FATAL:
			s_info = "FATAL";
			break;
		case Alarm.WARNING:
			s_info = "Warning";
			break;
		default:
			s_info = "???";
		}
		
		String s_source = "<>";
		if( source != null ) {
			source.toString();
			if( source instanceof AdapterInterface ) {
				AdapterInterface driver = (AdapterInterface)source;
				s_source = driver.getConfiguration().getName();
			}
		}
		model.insertRow(0, new Object[] { now, df.format(now), s_info, s_source, msg });

		while (model.getRowCount() > 100) {
			model.removeRow(model.getRowCount() - 1);
		}
	}

	private void go_toActionPerformed(ActionEvent e) {
		int row = alarmTable.getSelectedRow();
		if( row >= 0 ) {
			Date dt = eventTimeChooser.getDate( );
			putClientProperty("go_to", dt);
		}
	}

	private void startTimeChooserFocusLost(FocusEvent e) {
		// TODO add your code here
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		scrollPane1 = new JScrollPane();
		alarmTable = new JTable();
		panel1 = new JPanel();
		checkBox1 = new JCheckBox();
		checkBox2 = new JCheckBox();
		label1 = new JLabel();
		alarmLevelSelector = new JComboBox();
		eventTimeChooser = new JDateChooser();
		go_to = new JButton();
		clear = new JButton();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setLayout(new FormLayout(
			"default:grow",
			"default, $lgap, fill:default:grow, $lgap, fill:default, 2*($lgap, default)"));

		//======== scrollPane1 ========
		{
			scrollPane1.setPreferredSize(new Dimension(454, 200));

			//---- alarmTable ----
			alarmTable.setModel(new DefaultTableModel(
				new Object[][] {
					{null, null, null, null, null},
					{null, null, null, null, null},
				},
				new String[] {
					"O", "Time", "Severity", "Device", "Message"
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
				TableColumnModel cm = alarmTable.getColumnModel();
				cm.getColumn(0).setResizable(false);
				cm.getColumn(0).setMinWidth(1);
				cm.getColumn(0).setMaxWidth(1);
				cm.getColumn(0).setPreferredWidth(1);
				cm.getColumn(1).setPreferredWidth(60);
				cm.getColumn(2).setPreferredWidth(60);
				cm.getColumn(3).setPreferredWidth(60);
				cm.getColumn(4).setPreferredWidth(280);
			}
			scrollPane1.setViewportView(alarmTable);
		}
		add(scrollPane1, cc.xy(1, 3));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"4*(default, $lcgap), [50dlu,default], $lcgap, default:grow, $lcgap, [130dlu,default], 2*($lcgap, default)",
				"default"));

			//---- checkBox1 ----
			checkBox1.setText("Annotations");
			panel1.add(checkBox1, cc.xy(1, 1));

			//---- checkBox2 ----
			checkBox2.setText("Alarms");
			panel1.add(checkBox2, cc.xy(3, 1));

			//---- label1 ----
			label1.setText("Alarm Level:");
			panel1.add(label1, cc.xy(7, 1));

			//---- alarmLevelSelector ----
			alarmLevelSelector.setModel(new DefaultComboBoxModel(new String[] {
				"Info",
				"Warning",
				"Error"
			}));
			panel1.add(alarmLevelSelector, cc.xy(9, 1));

			//---- eventTimeChooser ----
			eventTimeChooser.setDateFormatString("MM/dd/yyyy HH:mm:ss");
			eventTimeChooser.addFocusListener(new FocusAdapter() {
				@Override
				public void focusLost(FocusEvent e) {
					startTimeChooserFocusLost(e);
				}
			});
			panel1.add(eventTimeChooser, cc.xy(13, 1));

			//---- go_to ----
			go_to.setText("Goto Event");
			go_to.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					go_toActionPerformed(e);
				}
			});
			panel1.add(go_to, cc.xy(15, 1));

			//---- clear ----
			clear.setText("Clear");
			clear.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					clearActionPerformed(e);
				}
			});
			panel1.add(clear, cc.xy(17, 1));
		}
		add(panel1, cc.xy(1, 7));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JScrollPane scrollPane1;
	private JTable alarmTable;
	private JPanel panel1;
	private JCheckBox checkBox1;
	private JCheckBox checkBox2;
	private JLabel label1;
	private JComboBox alarmLevelSelector;
	private JDateChooser eventTimeChooser;
	private JButton go_to;
	private JButton clear;
	// JFormDesigner - End of variables declaration //GEN-END:variables

}
