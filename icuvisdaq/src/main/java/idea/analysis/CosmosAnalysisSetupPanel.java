/*
 * Created by JFormDesigner on Fri Jul 22 16:39:25 CDT 2011
 */

package idea.analysis;


import icuInterface.RpUtil;
import idea.message.StreamID;
import idea.schema.rp.RpAnalysis;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpHardware;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpStudy;
import idea.schema.rp.StringStringMap;

import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.Map;

import javax.swing.DefaultComboBoxModel;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JComponent;
import javax.swing.JFormattedTextField;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.JTextField;
import javax.swing.SwingConstants;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumnModel;
import javax.swing.table.TableModel;

import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;
import idea.PrefUtil;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.DefaultComponentFactory;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

/**
 * @author User #2
 */
@Slf4j
@SuppressWarnings("serial")
public class CosmosAnalysisSetupPanel extends JPanel {

	private static final String TASK = "CosmosAnalysis";
	private static final int COL_OBJ = 0;
	private static final int COL_SELECTION = 1;
	private static final int COL_DEVNAME = 2;
	
	private RpStudy study;
	private RpAnalysis analysis;
	
	public CosmosAnalysisSetupPanel(RpStudy study, RpAnalysis anal) {
		initComponents();
		
		this.study = study;
		this.analysis = anal;
		
		windowPoints.setFormatterFactory( GuiUtil.getIntegerFormatterFactory() );
		windowPoints.setValue(100);  // a default value
		
		DefaultTableModel model = (DefaultTableModel) table1.getModel();
		model.setRowCount( 0 );  // clear out design data

		refresh();
		modelToPanel();
		
		String defaultFileName = PrefUtil.getUserPref(TASK, "");
		destFile.setText( defaultFileName );
	}

	private void modelToPanel() {
		if( analysis == null ) {
			return;
		}
		StringStringMap params = analysis.getParam();
		if( params == null || params.size() == 0 ) {
			return;
		}
		
		for( String key : params.keySet() ) {
			String val = params.get(key);
			
			if( "dest".equals(key)) {
				destFile.setText( val );
			} else if ( "secs".equals(key)) {
				secs.setSelectedItem(val );
			} else if ("window".equals(key)) {
				try {
					windowPoints.setValue( Integer.getInteger(val));
				} catch (Exception ee ) {
					// parsing exception
					log.error("could not parse value as int: {}", val);
				}
			} else {
				addDeviceMetrics( key, val );
			}
		}
		
	}

	private void addDeviceMetrics(String key, String val) {
		DefaultTableModel model = (DefaultTableModel) table1.getModel();

		RpDevice dev = null;
		HashSet<String> set = null ;
		for( int idx = 0; idx < device.getItemCount() ; idx++ ) {
			DevWrapper wrapper = (DevWrapper) device.getItemAt(idx);
			dev = wrapper.getDevice();
			if( key.equals(dev.getName()) ) {
				String [] arr = val.split(",");
				set = new HashSet<String>( Arrays.asList( arr ) );
				break;
			}
		}
		
		if( set == null ) {
			// NOT EXPECTED
			log.error( "DID NOT FIND DEVICE! {}", key );
			return;
		}
		
		List<? extends RpMetric> metrics = RpUtil.getMetrics(dev, StreamID.MEASUREMENT);
		for( RpMetric metric : metrics ) {
			boolean checked = set.contains( metric.getLocation() );
			if( existsInTable( model, metric )) {
				// ignore
			} else {
				model.addRow( new Object[] { metric, checked, dev.getName(), metric.getLocation(), metric.getName() } );
			}
		}
	}

	private void refresh() {
		RpHardware hw = study.getHardware().get(0);
		List<RpDevice> devs = hw.getDevices();
		
		DefaultComboBoxModel model = new DefaultComboBoxModel();
		for (RpDevice dev : devs) {
			model.addElement(new DevWrapper(dev));
		}

		device.setModel(model);

	}

	private void addDeviceActionPerformed(ActionEvent e) {
		DefaultTableModel model = (DefaultTableModel) table1.getModel();
		
		DevWrapper wrapper = (DevWrapper) device.getSelectedItem();
		RpDevice dev = wrapper.getDevice();
		List<? extends RpMetric> metrics = RpUtil.getMetrics(dev, StreamID.MEASUREMENT);
		for( RpMetric metric : metrics ) {
			if( existsInTable( model, metric )) {
				// ignore
			} else {
				model.addRow( new Object[] { metric, Boolean.TRUE, dev.getName(), metric.getLocation(), metric.getName() } );
			}
		}
	}

	private boolean existsInTable(DefaultTableModel model, RpMetric ref) {
		for( int row = 0; row < model.getRowCount() ; row++ ) {
			RpMetric metric = (RpMetric) model.getValueAt( row, COL_OBJ );
			if( ref == metric ) {
				return true;
			}
		}
		return false;
	}

	private void removeDeviceActionPerformed(ActionEvent e) {
		// TODO add your code here
	}

	private void selectAllActionPerformed(ActionEvent e) {
		DefaultTableModel model = (DefaultTableModel) table1.getModel();
		
		for( int row = 0; row < model.getRowCount() ; row++ ) {
			model.setValueAt(Boolean.TRUE, row, COL_SELECTION );
		}
	}

	private void okActionPerformed(ActionEvent e) {
		
		panelToModel();
		PrefUtil.saveUserPref(TASK, destFile.getText());

		GuiUtil.closeDialog( this );
	}

	private void panelToModel() {
		
		Map<String,String> params = analysis.getParam();
		saveParam(params, "dest", destFile.getText());
		saveParam(params, "secs", secs.getSelectedItem());
		saveParam(params, "window", windowPoints.getText() );

		String lastDev = null;
		StringBuffer pts = new StringBuffer();
		TableModel model = table1.getModel();
		for( int row = 0; row < model.getRowCount(); row++ ) {
			Boolean selected = (Boolean) model.getValueAt( row, COL_SELECTION );
			if( !selected ) {
				continue;
			}
			
			RpMetric metric = (RpMetric) model.getValueAt(row, COL_OBJ );
			String devName = (String) model.getValueAt( row, COL_DEVNAME );
			if( lastDev != null && !lastDev.equals(devName)) {
				saveParam(params, lastDev, pts.toString() );
				pts.setLength( 0 );
			}
			lastDev = devName;
			
			if(pts.length() > 0 ) {
				pts.append(",");
			}
			pts.append(metric.getLocation().toString());
		}
		
		if( pts.length() > 0 ) {
			saveParam(params, lastDev, pts.toString() );
		}
		
	}

	private void saveParam(Map<String,String> params, String key, Object wrapper) {
		String value = null;
		if (wrapper instanceof WfWrapper) {
			WfWrapper w = (WfWrapper) wrapper;
			RpMetric wave = w.getWave();
			value = wave.getLocation();
		} else if (wrapper instanceof DevWrapper) {
			DevWrapper w = (DevWrapper) wrapper;
			RpDevice dev = w.getDevice();
			value = dev.getName();
		} else {
			value = (String)wrapper;  // not really wrapped
		}

		params.put( key,  value );
	}

	private void cancelActionPerformed(ActionEvent e) {
		GuiUtil.closeDialog( this );
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		separator1 = compFactory.createSeparator("Destination");
		panel1 = new JPanel();
		label5 = new JLabel();
		destFile = new JTextField();
		browse = new JButton();
		label2 = new JLabel();
		secs = new JComboBox();
		label3 = new JLabel();
		windowPoints = new JFormattedTextField();
		label4 = new JLabel();
		separator3 = compFactory.createSeparator("Source");
		panel3 = new JPanel();
		label1 = new JLabel();
		device = new JComboBox();
		addDevice = new JButton();
		removeDevice = new JButton();
		separator2 = compFactory.createSeparator("Signals");
		scrollPane1 = new JScrollPane();
		table1 = new JTable();
		panel2 = new JPanel();
		selectAll = new JButton();
		ok = new JButton();
		cancel = new JButton();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout(
			"default:grow",
			"5*(default, $lgap), default:grow, $lgap, default"));
		add(separator1, cc.xy(1, 1));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"30dlu, $lcgap, right:[50dlu,default], $lcgap, [50dlu,default], $lcgap, [50dlu,default]:grow, $lcgap, default",
				"2*(default, $lgap), default"));

			//---- label5 ----
			label5.setText("File:");
			panel1.add(label5, cc.xy(3, 1));
			panel1.add(destFile, cc.xywh(5, 1, 3, 1));

			//---- browse ----
			browse.setText("Browse");
			browse.setEnabled(false);
			panel1.add(browse, cc.xy(9, 1));

			//---- label2 ----
			label2.setText("Frequency:");
			panel1.add(label2, cc.xy(3, 3));

			//---- secs ----
			secs.setModel(new DefaultComboBoxModel(new String[] {
				"1 sec",
				"5 sec",
				"10 sec"
			}));
			secs.setSelectedIndex(1);
			panel1.add(secs, cc.xy(5, 3));

			//---- label3 ----
			label3.setText("Window:");
			panel1.add(label3, cc.xy(3, 5));

			//---- windowPoints ----
			windowPoints.setText("100");
			windowPoints.setHorizontalAlignment(SwingConstants.TRAILING);
			panel1.add(windowPoints, cc.xy(5, 5));

			//---- label4 ----
			label4.setText("Number of points needed for computation.");
			panel1.add(label4, cc.xywh(7, 5, 3, 1));
		}
		add(panel1, cc.xy(1, 3));
		add(separator3, cc.xy(1, 5));

		//======== panel3 ========
		{
			panel3.setLayout(new FormLayout(
				"30dlu, $lcgap, right:[50dlu,default], $lcgap, [80dlu,default], $lcgap, [50dlu,default], $lcgap, default",
				"2*(default, $lgap), default"));

			//---- label1 ----
			label1.setText("Device:");
			panel3.add(label1, cc.xy(3, 3));
			panel3.add(device, cc.xy(5, 3));

			//---- addDevice ----
			addDevice.setText("Add");
			addDevice.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					addDeviceActionPerformed(e);
				}
			});
			panel3.add(addDevice, cc.xy(7, 3));

			//---- removeDevice ----
			removeDevice.setText("Remove");
			removeDevice.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					removeDeviceActionPerformed(e);
				}
			});
			panel3.add(removeDevice, cc.xy(9, 3));
		}
		add(panel3, cc.xy(1, 7));
		add(separator2, cc.xy(1, 9));

		//======== scrollPane1 ========
		{

			//---- table1 ----
			table1.setModel(new DefaultTableModel(
				new Object[][] {
					{null, null, null, null, null},
					{null, null, null, null, null},
				},
				new String[] {
					"O", "Select", "Device", "Loc", "Description"
				}
			) {
				Class<?>[] columnTypes = new Class<?>[] {
					Object.class, Boolean.class, Object.class, Object.class, Object.class
				};
				boolean[] columnEditable = new boolean[] {
					false, true, false, false, false
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
				cm.getColumn(0).setMinWidth(1);
				cm.getColumn(0).setMaxWidth(1);
				cm.getColumn(0).setPreferredWidth(1);
				cm.getColumn(1).setPreferredWidth(40);
				cm.getColumn(2).setPreferredWidth(80);
				cm.getColumn(3).setPreferredWidth(80);
				cm.getColumn(4).setPreferredWidth(200);
			}
			table1.setPreferredScrollableViewportSize(new Dimension(450, 200));
			scrollPane1.setViewportView(table1);
		}
		add(scrollPane1, cc.xy(1, 11));

		//======== panel2 ========
		{
			panel2.setLayout(new FormLayout(
				"default, $lcgap, default:grow, 2*($lcgap, [50dlu,default])",
				"default"));

			//---- selectAll ----
			selectAll.setText("Select All");
			selectAll.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					selectAllActionPerformed(e);
				}
			});
			panel2.add(selectAll, cc.xy(1, 1));

			//---- ok ----
			ok.setText("OK");
			ok.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					okActionPerformed(e);
				}
			});
			panel2.add(ok, cc.xy(5, 1));

			//---- cancel ----
			cancel.setText("Cancel");
			cancel.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					cancelActionPerformed(e);
				}
			});
			panel2.add(cancel, cc.xy(7, 1));
		}
		add(panel2, cc.xy(1, 13));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JComponent separator1;
	private JPanel panel1;
	private JLabel label5;
	private JTextField destFile;
	private JButton browse;
	private JLabel label2;
	private JComboBox secs;
	private JLabel label3;
	private JFormattedTextField windowPoints;
	private JLabel label4;
	private JComponent separator3;
	private JPanel panel3;
	private JLabel label1;
	private JComboBox device;
	private JButton addDevice;
	private JButton removeDevice;
	private JComponent separator2;
	private JScrollPane scrollPane1;
	private JTable table1;
	private JPanel panel2;
	private JButton selectAll;
	private JButton ok;
	private JButton cancel;
	// JFormDesigner - End of variables declaration  //GEN-END:variables
}
