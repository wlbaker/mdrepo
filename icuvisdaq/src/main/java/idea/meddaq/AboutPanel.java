/*
 * Created by JFormDesigner on Wed Nov 18 06:41:47 CST 2009
 */

package idea.meddaq;


import com.jgoodies.forms.factories.*;
import idea.persistmanager.hdf5.H5Util;

import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Enumeration;
import java.util.LinkedList;
import java.util.Map;
import java.util.Properties;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;
import javax.swing.JTable;
import javax.swing.JTextArea;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumnModel;

import org.pistax.PistaUtil;

import idea.GuiUtil;
import idea.r.RUtil;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class AboutPanel extends JPanel {
	public AboutPanel() {
		initComponents();
		fillMessage();
		fillEnviron();
		fillModules();
		
		versionLabel.setText( MedDAQFrame.APP_NAME + " " + MedDAQFrame.APP_VERSION + " " + MedDAQFrame.APP_RELEASE);
	}
	
	private void fillModules() {
		DefaultTableModel model = (DefaultTableModel) modulesTable.getModel();
		model.setRowCount( 0 );
		
		String name = RUtil.getName();
		String status = RUtil.getStatus();
		model.addRow( new String [] { name, status } );
		
//		name = JDAQmxUtil.getName();
//		status = JDAQmxUtil.getStatus();
//		model.addRow( new String [] { name, status } );
		

		int [] ver = null;
		String msg = "??";
		try {
			ver = H5Util.getJNIVersion();
			msg = arrayToString( ver );
		} catch( Throwable e ) {
			msg = e.getMessage();
		}
		model.addRow( new String [] { "HDF5 JNI", msg } );
		
		msg = "??";
		try {
			int [] v2 = new int[3];
			H5Util.getLoadedVersion( v2 );
			msg = arrayToString( v2 );
		} catch (Throwable e) {
			msg = "[ERROR: " + e.getMessage() + "]";
		}
		model.addRow( new String [] { "HDF5 SO", msg } );

		try {
			String jarVer = PistaUtil.getJARVersion();
			model.addRow( new String [] { "JPista JAR", jarVer } );
			String soVer = PistaUtil.getNativeVersion();
			model.addRow( new String [] { "JPista JNI", soVer } );
		} catch (Throwable e) {
			// e.printStackTrace();
			model.addRow( new String [] { "JPista JNI", e.getMessage() } );
		}
		
		msg = "??";
		model.addRow( new String [] { "JDAQmx", msg } );
		
		msg = "??";
		try {
			String jarVer = "[not installed]"; // RXTXVersion.getVersion();
			model.addRow( new String [] { "RXTX Serial JAR", jarVer } );
			
			String soVer = "[not installed]"; // RXTXVersion.nativeGetVersion();
			model.addRow( new String [] { "RXTX Serial JNI", soVer } );
		} catch (Throwable e) {
			// e.printStackTrace();
			msg = e.getMessage();
			model.addRow( new String [] { "RXTX Serial JNI", msg } );
		}
		try {
			String jarVer = "[unknown]";
			model.addRow( new String [] { "JSerialComm JAR", jarVer } );
			String soVer = "[unknown]";
			model.addRow( new String [] { "JSerialComm JNI", soVer } );
		} catch (Throwable e) {
			// e.printStackTrace();
			model.addRow( new String [] { "JSerialComm JNI", e.getMessage() } );
		}
		
	}

	private String arrayToString(int[] ver) {
		String s = "";

		
		for( int v : ver  ) {
			s += "" + v;
			s += ".";
		}
		return s;
	}

	private void fillMessage() {
		Properties props = System.getProperties();

		String txt = "";
		Enumeration<Object> keys = props.keys();
		ArrayList<Object> list = Collections.list(keys);
		Collections.sort( list, new Comparator<Object>() {

			@Override
			public int compare(Object arg0, Object arg1) {
				String s1 = (String)arg0;
				String s2 = (String)arg1;
				return s1.compareTo( s2 );
			}} );

		for ( Object key : list ) {
			txt = txt + key + "=" + props.getProperty((String) key) + "\n";
		}
		message.setText(txt);
	}

	private void fillEnviron() {
		Map<String, String> env_map = System.getenv();

		LinkedList<String> keys = new LinkedList<String>( env_map.keySet() );
		Collections.sort( keys ) ;
		String txt = "";
		for ( String key : keys) {
			txt = txt + key + "=" + env_map.get(key) + "\n";
		}
		env.setText(txt);
	}


	private void okButtonActionPerformed(ActionEvent e) {
		GuiUtil.closeDialog( this );
	}

//	private void easterActionPerformed(ActionEvent e) {
//		MgDAQPanel.easterEgg += 100;
//	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		tabbedPane1 = new JTabbedPane();
		panel2 = new JPanel();
		button2 = new JButton();
		panel3 = new JPanel();
		versionLabel = new JLabel();
		label2 = new JLabel();
		label3 = new JLabel();
		label4 = new JLabel();
		label5 = new JLabel();
		button1 = new JButton();
		panel4 = new JPanel();
		scrollPane1 = new JScrollPane();
		message = new JTextArea();
		panel6 = new JPanel();
		scrollPane3 = new JScrollPane();
		env = new JTextArea();
		panel5 = new JPanel();
		scrollPane2 = new JScrollPane();
		modulesTable = new JTable();
		panel1 = new JPanel();
		okButton = new JButton();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout(
			"default:grow",
			"fill:default:grow, $lgap, default"));

		//======== tabbedPane1 ========
		{

			//======== panel2 ========
			{
				panel2.setBorder(Borders.DLU4);
				panel2.setLayout(new FormLayout(
					"default, $lcgap, [12dlu,default], $lcgap, default:grow",
					"default, $lgap, top:[60dlu,default]:grow, $lgap, default"));

				//---- button2 ----
				button2.setIcon(new ImageIcon(getClass().getResource("/idea/meddaq/idea.png")));
				button2.setBorder(null);
				panel2.add(button2, CC.xy(1, 1));

				//======== panel3 ========
				{
					panel3.setLayout(new FormLayout(
						"[150dlu,default]:grow",
						"default, $lgap, [12dlu,default], 3*($lgap, default), $lgap, default:grow, $lgap, default"));

					//---- versionLabel ----
					versionLabel.setText("MedDAQ 0.9.2");
					panel3.add(versionLabel, CC.xy(1, 1));

					//---- label2 ----
					label2.setText("US Army Institute of Surgical Research");
					panel3.add(label2, CC.xy(1, 5));

					//---- label3 ----
					label3.setText("3400 Rawley E Chambers, Bldg 3611");
					panel3.add(label3, CC.xy(1, 7));

					//---- label4 ----
					label4.setText("Ft. Sam Houston, TX  78234");
					panel3.add(label4, CC.xy(1, 9));

					//---- label5 ----
					label5.setText("POC: Dr. Jose Salinas  210-539-0806");
					panel3.add(label5, CC.xy(1, 13));
				}
				panel2.add(panel3, CC.xywh(5, 1, 1, 3));

				//---- button1 ----
				button1.setIcon(new ImageIcon(getClass().getResource("/idea/meddaq/meddaq.png")));
				button1.setBorder(null);
				panel2.add(button1, CC.xy(1, 3));
			}
			tabbedPane1.addTab("About", panel2);

			//======== panel4 ========
			{
				panel4.setBorder(Borders.DLU4);
				panel4.setLayout(new FormLayout(
					"[default,500dlu]:grow",
					"fill:[default,300dlu]:grow"));

				//======== scrollPane1 ========
				{
					scrollPane1.setMaximumSize(new Dimension(600, 400));
					scrollPane1.setViewportView(message);
				}
				panel4.add(scrollPane1, CC.xy(1, 1));
			}
			tabbedPane1.addTab("System", panel4);

			//======== panel6 ========
			{
				panel6.setBorder(Borders.DLU4);
				panel6.setLayout(new FormLayout(
					"[default,500dlu]:grow",
					"fill:[default,300dlu]:grow"));

				//======== scrollPane3 ========
				{
					scrollPane3.setViewportView(env);
				}
				panel6.add(scrollPane3, CC.xy(1, 1));
			}
			tabbedPane1.addTab("Environment", panel6);

			//======== panel5 ========
			{
				panel5.setBorder(Borders.DLU4);
				panel5.setLayout(new FormLayout(
					"default:grow",
					"fill:default:grow"));

				//======== scrollPane2 ========
				{
					scrollPane2.setPreferredSize(new Dimension(454, 223));

					//---- modulesTable ----
					modulesTable.setModel(new DefaultTableModel(
						new Object[][] {
							{null, null},
							{null, null},
						},
						new String[] {
							"Module", "Status"
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
						TableColumnModel cm = modulesTable.getColumnModel();
						cm.getColumn(0).setPreferredWidth(300);
						cm.getColumn(1).setPreferredWidth(100);
					}
					scrollPane2.setViewportView(modulesTable);
				}
				panel5.add(scrollPane2, CC.xy(1, 1));
			}
			tabbedPane1.addTab("JNI Modules", panel5);
		}
		add(tabbedPane1, CC.xy(1, 1));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"default, $lcgap, default:grow, $lcgap, default, $lcgap, [50dlu,default]",
				"default"));

			//---- okButton ----
			okButton.setText("Ok");
			okButton.addActionListener(e -> okButtonActionPerformed(e));
			panel1.add(okButton, CC.xy(7, 1));
		}
		add(panel1, CC.xy(1, 3));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	private JTabbedPane tabbedPane1;
	private JPanel panel2;
	private JButton button2;
	private JPanel panel3;
	private JLabel versionLabel;
	private JLabel label2;
	private JLabel label3;
	private JLabel label4;
	private JLabel label5;
	private JButton button1;
	private JPanel panel4;
	private JScrollPane scrollPane1;
	private JTextArea message;
	private JPanel panel6;
	private JScrollPane scrollPane3;
	private JTextArea env;
	private JPanel panel5;
	private JScrollPane scrollPane2;
	private JTable modulesTable;
	private JPanel panel1;
	private JButton okButton;
	// JFormDesigner - End of variables declaration  //GEN-END:variables
}
