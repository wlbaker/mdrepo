/*
 * Created by JFormDesigner on Fri Dec 21 09:28:22 CST 2012
 */

package idea.study;

import icuInterface.RpUtil;
import idea.message.StreamID;
import idea.schema.rp.RpAnalysis;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpHardware;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpStudy;
import idea.schema.rp.StringStringMap;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.util.Arrays;
import java.util.HashSet;
import java.util.List;

import javax.swing.DefaultComboBoxModel;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumnModel;
import javax.swing.table.TableModel;

import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;
import idea.analysis.DevWrapper;
import idea.analysis.WfWrapper;

import com.jgoodies.forms.factories.DefaultComponentFactory;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

/**
 * @author User #1
 */
@SuppressWarnings("serial")
@Slf4j
public class VariableCollectionSetupPanel extends JPanel {

	private final static int COL_OBJ = 0;
	private final static int COL_DEVNAME = 1;
	private final static int COL_LOC = 2;
	private final static int COL_DESC = 3;

	private RpStudy study;
	private RpAnalysis analysis;

	public VariableCollectionSetupPanel(RpStudy study, RpAnalysis anal) {
		initComponents();

		this.study = study;
		this.analysis = anal;

		modelToPanel();

		//String defaultFileName = PrefUtil.getUserPref(TASK, "");
		//destFile.setText(defaultFileName);
	}

	private void modelToPanel() {
		if (analysis == null) {
			return;
		}
		StringStringMap params = analysis.getParam();
		if (params == null || params.size() == 0) {
			return;
		}

		for (String key : params.keySet()) {
			String val = params.get(key);

			addDeviceMetrics(key, val);
		}

	}

	private void addDeviceMetrics(String key, String val) {
		DefaultTableModel model = (DefaultTableModel) table1.getModel();

		RpDevice dev = null;
		HashSet<String> set = null;
		for (int idx = 0; idx < device.getItemCount(); idx++) {
			DevWrapper wrapper = (DevWrapper) device.getItemAt(idx);
			dev = wrapper.getDevice();
			if (key.equals(dev.getName())) {
				String[] arr = val.split(",");
				set = new HashSet<String>(Arrays.asList(arr));
				break;
			}
		}

		if (set == null) {
			// NOT EXPECTED
			log.error("NO DEVICES: " + key);
			return;
		}

		List<? extends RpMetric> metrics = RpUtil.getMetrics(dev, StreamID.MEASUREMENT);
		for (RpMetric metric : metrics) {
			boolean checked = set.contains(metric.getLocation().toString());
			if (existsInTable(model, metric)) {
				// ignore
			} else {
				model.addRow(new Object[] { metric, checked, dev.getName(), metric.getLocation(), metric.getName() });
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

		//	List<RpKVPair> params = analysis.getParam();
		//	setSelector(params, "signal", signal);
		//	setSelector(params, "detector", algorithm);
	}

	private void addVariableActionPerformed(ActionEvent e) {
		DefaultTableModel model = (DefaultTableModel) table1.getModel();

		DevWrapper wrapper = (DevWrapper) device.getSelectedItem();
		RpDevice dev = wrapper.getDevice();
		List<? extends RpMetric> metrics = RpUtil.getMetrics(dev, StreamID.MEASUREMENT);
		for (RpMetric metric : metrics) {
			if (existsInTable(model, metric)) {
				// ignore
			} else {
				model.addRow(new Object[] { metric, Boolean.TRUE, dev.getName(), metric.getLocation(), metric.getName() });
			}
		}
	}

	private boolean existsInTable(DefaultTableModel model, RpMetric ref) {
		for (int row = 0; row < model.getRowCount(); row++) {
			RpMetric metric = (RpMetric) model.getValueAt(row, COL_OBJ);
			if (ref == metric) {
				return true;
			}
		}
		return false;
	}

	private void okActionPerformed(ActionEvent e) {
		
		panelToModel();
		// PrefUtil.saveUserPref(TASK, destFile.getText());

		GuiUtil.closeDialog( this );
	}

	private void panelToModel() {
		
		StringStringMap params = analysis.getParam();
//		saveParam(params, "dest", destFile.getText());
//		saveParam(params, "secs", secs.getSelectedItem());
//		saveParam(params, "window", windowPoints.getText() );

		String lastDev = null;
		StringBuffer pts = new StringBuffer();
		TableModel model = table1.getModel();
		for( int row = 0; row < model.getRowCount(); row++ ) {
			
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

	private void saveParam(StringStringMap params, String key, Object wrapper) {
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
			value = (String) wrapper;  // not really wrapped
		}

		params.put( key, value );
	}

	private void cancelActionPerformed(ActionEvent e) {
		GuiUtil.closeDialog( this );
	}

	private void removeVariableActionPerformed(ActionEvent e) {
		// TODO add your code here
	}

	private void deviceActionPerformed(ActionEvent e) {
		// TODO add your code here
		log.error("tbd: action performed");
	}

	private void deviceItemStateChanged(ItemEvent e) {
		// TODO add your code here
		log.error("tbd: state changed");
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		separator2 = compFactory.createSeparator("Variable");
		panel1 = new JPanel();
		label1 = new JLabel();
		device = new JComboBox();
		label2 = new JLabel();
		variable = new JComboBox();
		panel2 = new JPanel();
		addVariable = new JButton();
		separator1 = compFactory.createSeparator("Selection");
		scrollPane1 = new JScrollPane();
		table1 = new JTable();
		panel3 = new JPanel();
		removeVariable = new JButton();
		ok = new JButton();
		cancel = new JButton();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setLayout(new FormLayout(
			"default:grow",
			"4*(default, $lgap), fill:default:grow, $lgap, default"));
		add(separator2, cc.xy(1, 1));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"2*(default, $lcgap), [120dlu,default], 2*($lcgap, default), $lcgap, [80dlu,default]",
				"2*(default, $lgap), default"));

			//---- label1 ----
			label1.setText("Device:");
			panel1.add(label1, cc.xy(3, 3));

			//---- device ----
			device.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					deviceActionPerformed(e);
				}
			});
			device.addItemListener(new ItemListener() {
				@Override
				public void itemStateChanged(ItemEvent e) {
					deviceItemStateChanged(e);
				}
			});
			panel1.add(device, cc.xy(5, 3));

			//---- label2 ----
			label2.setText("Variable:");
			panel1.add(label2, cc.xy(9, 3));
			panel1.add(variable, cc.xy(11, 3));
		}
		add(panel1, cc.xy(1, 3));

		//======== panel2 ========
		{
			panel2.setLayout(new FormLayout(
				"default:grow, $lcgap, [50dlu,default]",
				"default"));

			//---- addVariable ----
			addVariable.setText("Add");
			addVariable.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					addVariableActionPerformed(e);
				}
			});
			panel2.add(addVariable, cc.xy(3, 1));
		}
		add(panel2, cc.xy(1, 5));
		add(separator1, cc.xy(1, 7));

		//======== scrollPane1 ========
		{

			//---- table1 ----
			table1.setModel(new DefaultTableModel(
				new Object[][] {
					{null, null, null, null},
					{null, null, null, null},
				},
				new String[] {
					"O", "Device", "Variable", "Description"
				}
			) {
				boolean[] columnEditable = new boolean[] {
					false, false, false, false
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
				cm.getColumn(2).setPreferredWidth(100);
				cm.getColumn(3).setPreferredWidth(200);
			}
			scrollPane1.setViewportView(table1);
		}
		add(scrollPane1, cc.xy(1, 9));

		//======== panel3 ========
		{
			panel3.setLayout(new FormLayout(
				"[50dlu,default], $lcgap, default:grow, 2*($lcgap, [50dlu,default])",
				"default"));

			//---- removeVariable ----
			removeVariable.setText("Remove");
			removeVariable.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					removeVariableActionPerformed(e);
				}
			});
			panel3.add(removeVariable, cc.xy(1, 1));

			//---- ok ----
			ok.setText("OK");
			ok.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					okActionPerformed(e);
				}
			});
			panel3.add(ok, cc.xy(5, 1));

			//---- cancel ----
			cancel.setText("Cancel");
			cancel.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					cancelActionPerformed(e);
				}
			});
			panel3.add(cancel, cc.xy(7, 1));
		}
		add(panel3, cc.xy(1, 11));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JComponent separator2;
	private JPanel panel1;
	private JLabel label1;
	private JComboBox device;
	private JLabel label2;
	private JComboBox variable;
	private JPanel panel2;
	private JButton addVariable;
	private JComponent separator1;
	private JScrollPane scrollPane1;
	private JTable table1;
	private JPanel panel3;
	private JButton removeVariable;
	private JButton ok;
	private JButton cancel;
	// JFormDesigner - End of variables declaration  //GEN-END:variables
}
