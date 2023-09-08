/*
 * Created by JFormDesigner on Fri Apr 16 12:30:26 CDT 2010
 */

package idea.simulator;

import icuInterface.PlatformUtil;
import icuInterface.RpUtil;
import idea.driver.LabJackDriver;
import idea.intf.AdapterInterface;
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
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.io.IOException;
import java.util.List;

import javax.swing.DefaultComboBoxModel;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JComboBox;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumnModel;
import javax.swing.table.TableModel;

import lombok.extern.slf4j.Slf4j;

import org.jdesktop.beansbinding.AutoBinding.UpdateStrategy;
import org.jdesktop.beansbinding.BeanProperty;
import org.jdesktop.beansbinding.BindingGroup;
import org.jdesktop.beansbinding.Bindings;
import org.jfree.util.Log;

import idea.GuiUtil;
import idea.analysis.DevWrapper;
import idea.analysis.WfWrapper;
import idea.devwizard.SetupWizardInterface;
import idea.gui.WizardPanelInterface;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.DefaultComponentFactory;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

/**
 * @author User #2
 */
@Slf4j
@SuppressWarnings("serial")
public class SimulatorOutputPanel extends JPanel implements WizardPanelInterface {

	private static final int OBJECT_COL = 0;
	private static final int SIG_NAME_COL = 1; // both tables use this!
	private static final int SIG_BIND_COL = 2;
	private static final Object DAQMX_NAME = "National Insruments DAQmx";
	private static final Object DAQMXBASE_NAME = "National Insruments DAQmxBase";
	private static final Object LABJACK_NAME = "LabJack U3-HV";
	private SetupWizardInterface wizard;
	private RpAnalysis analysis;

	public SimulatorOutputPanel(SetupWizardInterface wizard, RpAnalysis anal) {
		this.wizard = wizard;
		this.analysis = anal;

		initComponents();
		setName("Simulation");

		GuiUtil.initPanel(this);

		wizard.enableNext(true);
		wizard.enableFinish(true);

		refresh();
		// ? GuiUtil.closeDialog(this);

		modelToPanel();
	}

	private void modelToPanel() {
		if (analysis == null) {
			return;
		}
		 StringStringMap params = analysis.getParam();
		if (params == null) {
			return;
		}

		for (String key : params.keySet() ) {
			String val = params.get(key);

			if ("enabled".equals(key)) {
				simulation.setSelected("1".equals(val));
			}
			if ("output".equals(key)) {
				outputDevice.setSelectedItem(val);
			} else if ("input".equals(key)) {
				inputDevice.setSelectedItem(val);
				System.err.println("TODO: make sure this triggers the reload of the binding table");
			} else {
				addBinding(key, val);
			}
		}

	}

	private void addBinding(String key, String val) {
		DefaultTableModel model = (DefaultTableModel) bindTable.getModel();
		for (int row = 0; row < model.getRowCount(); row++) {
			if (key.equals(model.getValueAt(row, SIG_NAME_COL))) {
				model.setValueAt(val, row, SIG_BIND_COL);
				break;
			}
		}
	}

	private void simulationStateChanged(ChangeEvent e) {
		System.out.println("state changed: " + e);
	}

	private void inputDeviceActionPerformed(ActionEvent e) {
		Object item = inputDevice.getSelectedItem();
		DefaultTableModel model = (DefaultTableModel) signalTable.getModel();
		model.setRowCount(0);
		if (item != null) {
			RpHardware hw = null; // wizard.getHardware();

			for (RpDevice dev : hw.getDevices()) {
				// if (item.equals(hw.getName())) {
				List<? extends RpMetric> waves = RpUtil.getMetrics(dev, StreamID.WAVEFORM);
				if (waves != null) {
					for (RpMetric wave : waves) {
						model.addRow(new Object[] { wave, wave.getName() });
					}
				}
				// break;
				// }
			}

		}
	}

	private void assignActionPerformed(ActionEvent e) {
		int bindidx = bindTable.getSelectedRow();
		int sigidx = signalTable.getSelectedRow();

		if (bindidx < 0 || sigidx < 0) {
			return;
		}
		Object sigName = signalTable.getValueAt(sigidx, SIG_NAME_COL);
		bindTable.setValueAt(sigName, bindidx, SIG_BIND_COL);
	}

	private void removeActionPerformed(ActionEvent e) {
		int bindidx = bindTable.getSelectedRow();

		if (bindidx < 0) {
			return;
		}

		bindTable.setValueAt(null, bindidx, SIG_BIND_COL);
	}

	private void outputDeviceActionPerformed(ActionEvent e) {
		System.out.println("outputDevice action performed!");
		DefaultTableModel model = (DefaultTableModel) bindTable.getModel();
		model.setRowCount(0);

		refreshOutput();
	}

	private void outputDeviceItemStateChanged(ItemEvent e) {
		System.out.println("outputDevice item state changed!");
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		separator1 = compFactory.createSeparator("Simulation");
		panel2 = new JPanel();
		label5 = new JLabel();
		simulation = new JCheckBox();
		separator3 = compFactory.createSeparator("Device");
		panel1 = new JPanel();
		label4 = new JLabel();
		outputDevice = new JComboBox();
		label1 = new JLabel();
		inputDevice = new JComboBox();
		separator2 = compFactory.createSeparator("Signals");
		panel3 = new JPanel();
		panel4 = new JPanel();
		assign = new JButton();
		remove = new JButton();
		scrollPane1 = new JScrollPane();
		bindTable = new JTable();
		scrollPane2 = new JScrollPane();
		signalTable = new JTable();
		CellConstraints cc = new CellConstraints();

		// ======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout("default:grow", "6*(default, $lgap), fill:default:grow, $lgap, default"));
		add(separator1, cc.xy(1, 1));

		// ======== panel2 ========
		{
			panel2.setLayout(new FormLayout("right:90dlu, $lcgap, [100dlu,default], $lcgap, default:grow, 2*($lcgap, default)",
					"10dlu, $lgap, default, $lgap, 10dlu"));

			// ---- label5 ----
			label5.setText("Enable Analog Simulation:");
			panel2.add(label5, cc.xy(1, 3));

			// ---- simulation ----
			simulation.setText("Yes");
			simulation.addChangeListener(new ChangeListener() {
				@Override
				public void stateChanged(ChangeEvent e) {
					simulationStateChanged(e);
				}
			});
			panel2.add(simulation, cc.xy(3, 3));
		}
		add(panel2, cc.xy(1, 3));
		add(separator3, cc.xy(1, 5));

		// ======== panel1 ========
		{
			panel1.setLayout(new FormLayout("right:90dlu, $lcgap, [100dlu,default], $lcgap, default:grow, 2*($lcgap, default)", "default, $lgap, default"));

			// ---- label4 ----
			label4.setText("Output Device:");
			panel1.add(label4, cc.xy(1, 1));

			// ---- outputDevice ----
			outputDevice.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					outputDeviceActionPerformed(e);
				}
			});
			outputDevice.addItemListener(new ItemListener() {
				@Override
				public void itemStateChanged(ItemEvent e) {
					outputDeviceItemStateChanged(e);
				}
			});
			panel1.add(outputDevice, cc.xy(3, 1));

			// ---- label1 ----
			label1.setText("Input Device:");
			panel1.add(label1, cc.xy(1, 3));

			// ---- inputDevice ----
			inputDevice.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					inputDeviceActionPerformed(e);
				}
			});
			panel1.add(inputDevice, cc.xy(3, 3));
		}
		add(panel1, cc.xy(1, 7));
		add(separator2, cc.xy(1, 11));

		// ======== panel3 ========
		{
			panel3.setLayout(new FormLayout("[90dlu,default], $lcgap, default:grow, $lcgap, default:grow(0.5)", "fill:default"));

			// ======== panel4 ========
			{
				panel4.setLayout(new FormLayout("default", "3*(default, $lgap), default"));

				// ---- assign ----
				assign.setText("Assign");
				assign.addActionListener(new ActionListener() {
					@Override
					public void actionPerformed(ActionEvent e) {
						assignActionPerformed(e);
					}
				});
				panel4.add(assign, cc.xy(1, 1));

				// ---- remove ----
				remove.setText("Remove");
				remove.addActionListener(new ActionListener() {
					@Override
					public void actionPerformed(ActionEvent e) {
						removeActionPerformed(e);
					}
				});
				panel4.add(remove, cc.xy(1, 3));
			}
			panel3.add(panel4, cc.xy(1, 1));

			// ======== scrollPane1 ========
			{

				// ---- bindTable ----
				bindTable.setModel(new DefaultTableModel(new Object[][] { { null, null, null }, { null, null, null }, }, new String[] { "O", "Output Port",
						"Signal" }) {
					boolean[] columnEditable = new boolean[] { true, false, true };

					@Override
					public boolean isCellEditable(int rowIndex, int columnIndex) {
						return columnEditable[columnIndex];
					}
				});
				{
					TableColumnModel cm = bindTable.getColumnModel();
					cm.getColumn(0).setMinWidth(1);
					cm.getColumn(0).setMaxWidth(1);
					cm.getColumn(0).setPreferredWidth(1);
					cm.getColumn(1).setPreferredWidth(120);
					cm.getColumn(2).setPreferredWidth(300);
				}
				bindTable.setPreferredScrollableViewportSize(new Dimension(150, 100));
				scrollPane1.setViewportView(bindTable);
			}
			panel3.add(scrollPane1, cc.xy(3, 1));

			// ======== scrollPane2 ========
			{

				// ---- signalTable ----
				signalTable.setModel(new DefaultTableModel(new Object[][] { { "", null }, { null, null }, }, new String[] { "O", "Signal" }) {
					boolean[] columnEditable = new boolean[] { false, false };

					@Override
					public boolean isCellEditable(int rowIndex, int columnIndex) {
						return columnEditable[columnIndex];
					}
				});
				{
					TableColumnModel cm = signalTable.getColumnModel();
					cm.getColumn(0).setResizable(false);
					cm.getColumn(0).setMinWidth(1);
					cm.getColumn(0).setMaxWidth(1);
					cm.getColumn(0).setPreferredWidth(1);
					cm.getColumn(1).setPreferredWidth(100);
				}
				signalTable.setPreferredScrollableViewportSize(new Dimension(75, 100));
				scrollPane2.setViewportView(signalTable);
			}
			panel3.add(scrollPane2, cc.xy(5, 1));
		}
		add(panel3, cc.xy(1, 13));

		// ---- bindings ----
		bindingGroup = new BindingGroup();
		bindingGroup.addBinding(Bindings.createAutoBinding(UpdateStrategy.READ, simulation, BeanProperty.create("selected"), outputDevice,
				BeanProperty.create("enabled")));
		bindingGroup.addBinding(Bindings.createAutoBinding(UpdateStrategy.READ, simulation, BeanProperty.create("selected"), inputDevice,
				BeanProperty.create("enabled")));
		bindingGroup.addBinding(Bindings.createAutoBinding(UpdateStrategy.READ, simulation, BeanProperty.create("selected"), assign,
				BeanProperty.create("enabled")));
		bindingGroup.addBinding(Bindings.createAutoBinding(UpdateStrategy.READ_WRITE, simulation, BeanProperty.create("selected"), remove,
				BeanProperty.create("enabled")));
		bindingGroup.addBinding(Bindings.createAutoBinding(UpdateStrategy.READ, simulation, BeanProperty.create("selected"), bindTable,
				BeanProperty.create("enabled")));
		bindingGroup.addBinding(Bindings.createAutoBinding(UpdateStrategy.READ, simulation, BeanProperty.create("selected"), signalTable,
				BeanProperty.create("enabled")));
		bindingGroup.bind();
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JComponent separator1;
	private JPanel panel2;
	private JLabel label5;
	private JCheckBox simulation;
	private JComponent separator3;
	private JPanel panel1;
	private JLabel label4;
	private JComboBox outputDevice;
	private JLabel label1;
	private JComboBox inputDevice;
	private JComponent separator2;
	private JPanel panel3;
	private JPanel panel4;
	private JButton assign;
	private JButton remove;
	private JScrollPane scrollPane1;
	private JTable bindTable;
	private JScrollPane scrollPane2;
	private JTable signalTable;
	private BindingGroup bindingGroup;

	// JFormDesigner - End of variables declaration //GEN-END:variables

	private boolean save() {
		boolean ok = true;

		analysis.setAnalysisClass("idea.process.SimulationProcess");

		StringStringMap params = analysis.getParam();
		if( params == null ) {
			params = new StringStringMap();
			analysis.setParam(params);
		}
		saveParam(params, "enabled", simulation.isSelected() ? "1" : "0");
		saveParam(params, "output", outputDevice.getSelectedItem());
		saveParam(params, "input", inputDevice.getSelectedItem());

		TableModel model = bindTable.getModel();
		for (int row = 0; row < model.getRowCount(); row++) {
			String val = (String) model.getValueAt(row, SIG_BIND_COL);
			if (val == null || val.length() == 0) {
				continue;
			}

			String name = (String) model.getValueAt(row, SIG_NAME_COL);
			if (name == null || name.length() == 0) {
				continue;
			}

			saveParam(params, name, val);
		}

		return ok;

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
			value = (String) wrapper; // not really wrapped
		}

		params.put( key,  value);
	}

	@Override
	public boolean finish() {
		if (!save()) {
			return false;
		}

		return true;
	}

	@Override
	public boolean next() {
		return save();
	}

	@Override
	public void refresh() {
		DefaultComboBoxModel model = new DefaultComboBoxModel(new Object[] { DAQMX_NAME, DAQMXBASE_NAME, LABJACK_NAME });
		outputDevice.setModel(model);
		refreshOutput();

		model = new DefaultComboBoxModel();
		RpStudy study = wizard.getStudy();
		if( study == null ) {
			return;
		}
		List<RpHardware> hws = study.getHardware();
		if( hws == null || hws.size() == 0 ) {
			return;
		}
		
		RpHardware hw = hws.get(0); // wizard.getHardware();
		for (RpDevice dev : hw.getDevices()) {
			model.addElement(dev.getName());
		}

		inputDevice.setModel(model);
		inputDeviceActionPerformed(null);
	}

	public void refreshOutput() {
		try {
			_refreshOutput();
		} catch (UnsatisfiedLinkError e) {
			e.printStackTrace();
			// ignore???
		} catch (Exception e) {
			// ignore???
			e.printStackTrace();
		}
	}

	public void _refreshOutput() {

		AdapterInterface driver = null;

		Object output = outputDevice.getSelectedItem();

		try {
			if (DAQMX_NAME.equals(output)) {

				PlatformUtil.loadLibrary("jDAQmx");
				// driver = new NIDAQmxOutputDriver(null);
				driver = null;
				log.error("Probably need NullDriver()");
			} else if (DAQMXBASE_NAME.equals(output)) {
				PlatformUtil.loadLibrary("jDAQmxBase");
				// driver = new NIDAQmxBaseDriver(null);
				driver = null;
				log.error("Probably need NullDriver()");
			} else if (LABJACK_NAME.equals(output)) {
				driver = new LabJackDriver(null);
			} else {
				GuiUtil.showMessage("Could not identify output driver: " + output );
			}
		} catch (Error err) {
			// probably didn't find dll or error initializing
			err.printStackTrace();
		} catch (Exception ex) {
			// probably didn't find dll or error initializing
			ex.printStackTrace();
		}
		
		if( driver == null ) {
			Log.warn( "Could not identify or load output driver." );
			return;
		}

		// TableModelFixer fixer = (TableModelFixer) signalTable.getModel();
		DefaultTableModel model = (DefaultTableModel) bindTable.getModel(); // fixer.getShadowedModel();
		model.setRowCount(0);

		RpDevice cap;

		//		try {
		//			driver.connect();
		//		} catch (IOException e) {
		//			// TODO Auto-generated catch block
		//			e.printStackTrace();
		//		}
		cap = driver.getStaticCapabilities();
		// String[] ports = DaqSystem.getLocal().getPhysicalChannels();
		List<? extends RpMetric> descs = RpUtil.getMetrics(cap, StreamID.WAVEFORM );
		for (RpMetric desc : descs) {
			model.addRow(new Object[] { desc, desc.getName(), null });
		}

		try {
			driver.disconnect();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	@Override
	public void previous() {
		// TODO Auto-generated method stub

	}

}
