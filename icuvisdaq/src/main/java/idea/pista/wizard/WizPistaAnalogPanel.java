/*
 * Created by JFormDesigner on Mon Oct 05 13:52:41 CDT 2009
 */

package idea.pista.wizard;


import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.io.IOException;
import java.util.List;

import javax.swing.DefaultComboBoxModel;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumnModel;
import javax.swing.table.TableModel;

import org.pistax.PistaAdapter;

import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.layout.FormLayout;

import icuInterface.PlatformUtil;
import icuInterface.RpUtil;
import idea.conf.DeviceConfiguration;
import idea.intf.AdapterInterface;
import idea.message.StreamID;
import idea.schema.rp.RpConnType;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpLinearUnit;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpStream;
import idea.schema.rp.StringStringMap;
import idea.GuiUtil;
import idea.gui.ComboCellEditor;
import idea.gui.TableModelColumnRenamer;
import idea.gui.WizardMasterInterface;
import idea.gui.WizardPanelInterface;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class WizPistaAnalogPanel extends JPanel implements WizardPanelInterface {

	private static final int COL_OBJECT = 0;
	private static final int COL_ENABLED = 1;
	private static final int COL_PORT = 2;
	private static final int COL_SIGNAME = 3;
	private static final int COL_SIGTYPE = 4;

	String[] types = { "Waveform", "Numeric" };

	// NIDAQConfiguration dc;
	private RpDevice dc;
	private WizardMasterInterface wizard;

	public WizPistaAnalogPanel(WizardMasterInterface wizard, RpDevice conf) {
		initComponents();
		this.dc = conf;
		this.wizard = wizard;

		GuiUtil.initTable(signalTable, true);

		DefaultTableModel ori_model = (DefaultTableModel) signalTable.getModel();
		TableModel new_model = new TableModelColumnRenamer(ori_model, null) {

			// @Override
			// public Class<?> getColumnClass(int columnIndex) {
			// return columnTypes[columnIndex];
			// }

		};
		signalTable.setAutoCreateColumnsFromModel(false);
		// signalTable.setModel( new_model );

		// signalTable.setC

		initTable(signalTable);

	}

	private void initTable(JTable table) {

		TableColumnModel tcm = table.getColumnModel();
		// tcm.getColumn(COL_SIGTYPE)
		// .setCellRenderer(new ComboCellRenderer(types));
		tcm.getColumn(COL_SIGTYPE).setCellEditor(new ComboCellEditor(types));
	}

	private void refreshActionPerformed(ActionEvent e) {
		refresh();
	}

	public void refresh() {
		try {
			_refreshDevices();
			_refreshSignals();
			setDeviceConfig();
		} catch (Exception e) {
			GuiUtil.showError("NI Exception", e);
		} catch (UnsatisfiedLinkError r) {
			GuiUtil.showError("NI Error", r);
		}
	}

	public void _refreshDevices() throws IOException {

		PlatformUtil.loadLibrary("PISTA");

		String sr = RpUtil.getParam(dc, "rate");
		if (sr != null) {
			sampleRate.setSelectedItem(sr);
		}
		String tc = RpUtil.getParam(dc, "terminalConfig");
		if (tc != null) {
			terminalConfig.setSelectedItem(tc);
		}
		
		deviceSelection.setModel(new DefaultComboBoxModel<>(new String[] {
				"Dev1",
				"Dev2"
			}));
		
		String dev = RpUtil.getParam(dc, "deviceId");
		if (dev != null) {
			deviceSelection.setSelectedItem(dev);
		}
	}

	public void _refreshSignals() throws IOException {
		// TableModelFixer fixer = (TableModelFixer) signalTable.getModel();
		DefaultTableModel model = (DefaultTableModel) signalTable.getModel(); // fixer.getShadowedModel();
		model.setRowCount(0);

		RpDevice dev = new RpDevice();
		System.err.println("must set dev name, hardcoded to imp731");
		dev.setDriverName("imp731");
		AdapterInterface 	driver = new PistaAdapter(dev);
		DeviceConfiguration cap;
		cap = driver.getStaticCapabilities();
		// String[] ports = DaqSystem.getLocal().getPhysicalChannels();
		RpStream s = RpUtil.getStreamFromName(cap.getStreams(), StreamID.WAVEFORM.getName());
		for (RpMetric desc : (List<? extends RpMetric>) s.getMetric()) {
			boolean ena = false;
			model.addRow(new Object[] { "?", ena, desc.getName(), "", types[0] });
		}

	}

	// public DeviceConfiguration getDeviceProfile() {
	// TableModel model = signalTable.getModel();
	//
	// if (dc == null) {
	// if( useBase ) {
	// dc = (NIDAQConfiguration) NIDAQmxBaseDriver.createConfigInstance();
	// } else {
	// dc = (NIDAQConfiguration) NIDAQmxDriver.createConfigInstance();
	// }
	// } else {
	// dc.reset();
	// }
	//
	// dc.setName("National Instruments");
	// for (int row = 0; row < model.getRowCount(); row++) {
	// Boolean b = (Boolean) model.getValueAt(row, COL_ENABLED);
	// String p = (String) model.getValueAt(row, COL_PORT);
	// String n = (String) model.getValueAt(row, COL_SIGNAME);
	// String t = (String) model.getValueAt(row, COL_SIGTYPE);
	//
	// int dataRate = 500;
	// if (b) {
	//
	// if( t.equals(types[0])) {
	// WaveformDescription wave = new WaveformDescription(p, n, n,
	// dataRate, dataRate / 2, "mV");
	// dc.addWaveform(wave);
	// } else if (t.equals(types[1])) {
	// MetricDescription metric = new MetricDescription(p, n, n, "mV");
	// dc.addMetrics(metric);
	// } else {
	// assert( false ) : "UNKNOWN NI SIG TYPE";
	// System.err.println( "UNKNOWN NI SIG TYPE");
	// }
	//
	// }
	// }
	//
	// return dc;
	// }

	public void setDeviceConfig() {

		List<? extends RpMetric> waves = RpUtil.getMetrics(dc, StreamID.WAVEFORM);
		if (waves != null) {

			DefaultTableModel model = (DefaultTableModel) signalTable.getModel();
			for (RpMetric wave : waves) {
				int row = findRow(model, wave.getLocation());
				if (row < 0) {
					// ??? what now
					System.err.println("COULD NOT FIND SIGNAL: " + wave.getLocation());
				} else {
					model.setValueAt(Boolean.TRUE, row, COL_ENABLED);
					model.setValueAt(wave.getName(), row, COL_SIGNAME);
					model.setValueAt(types[0], row, COL_SIGTYPE);
				}
			}
		}

		// MetricDescription[] metrics = dc.getMetrics();
		// if (metrics != null) {
		//
		// DefaultTableModel model = (DefaultTableModel) signalTable
		// .getModel();
		// for (MetricDescription metric : metrics) {
		// int row = findRow(model, metric.getLocation());
		// if (row < 0) {
		// // ??? what now
		// System.err.println("COULD NOT FIND SIGNAL: "
		// + metric.getLocation());
		// } else {
		// model.setValueAt(Boolean.TRUE, row, COL_ENABLED);
		// model.setValueAt(metric.getName(), row, COL_SIGNAME);
		// model.setValueAt(types[1], row, COL_SIGTYPE);
		// }
		// }
		// }
	}

	private int findRow(DefaultTableModel model, Object location) {

		String loc = (String) location;

		int row = -1;

		for (int idx = 0; idx < model.getRowCount(); idx++) {
			String port = (String) model.getValueAt(idx, COL_PORT);
			if (loc.equals(port)) {
				// we found our signal
				row = idx;
				break;
			}
		}

		return row;
	}

	private void deviceSelectionActionPerformed(ActionEvent e) {
		GuiUtil.showMessage("NI: device selected...so refresh");
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		scrollPane1 = new JScrollPane();
		signalTable = new JTable();
		panel1 = new JPanel();
		label3 = new JLabel();
		deviceSelection = new JComboBox();
		label1 = new JLabel();
		sampleRate = new JComboBox<>();
		label2 = new JLabel();
		terminalConfig = new JComboBox<>();
		refresh = new JButton();

		//======== this ========
		setLayout(new FormLayout(
			"[160dlu,default]:grow, $lcgap, default",
			"fill:default:grow"));

		//======== scrollPane1 ========
		{

			//---- signalTable ----
			signalTable.setModel(new DefaultTableModel(
				new Object[][] {
					{null, true, null, null, null},
					{null, null, null, null, null},
				},
				new String[] {
					null, "Enabled", "IO Point", "Signal Name", "Signal Type"
				}
			) {
				Class<?>[] columnTypes = new Class<?>[] {
					Object.class, Boolean.class, Object.class, Object.class, Object.class
				};
				boolean[] columnEditable = new boolean[] {
					false, true, false, true, true
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
				TableColumnModel cm = signalTable.getColumnModel();
				cm.getColumn(0).setMinWidth(1);
				cm.getColumn(0).setMaxWidth(1);
				cm.getColumn(0).setPreferredWidth(1);
				cm.getColumn(1).setPreferredWidth(50);
				cm.getColumn(2).setPreferredWidth(100);
				cm.getColumn(3).setPreferredWidth(200);
			}
			signalTable.setPreferredScrollableViewportSize(new Dimension(250, 200));
			scrollPane1.setViewportView(signalTable);
		}
		add(scrollPane1, CC.xy(1, 1));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"right:default, $lcgap, default",
				"[12dlu,default], 3*($lgap, default), $lgap, default:grow, $lgap, default"));

			//---- label3 ----
			label3.setText("Device:");
			panel1.add(label3, CC.xy(1, 1));

			//---- deviceSelection ----
			deviceSelection.addActionListener(e -> deviceSelectionActionPerformed(e));
			panel1.add(deviceSelection, CC.xy(3, 1));

			//---- label1 ----
			label1.setText("Rate:");
			panel1.add(label1, CC.xy(1, 3));

			//---- sampleRate ----
			sampleRate.setModel(new DefaultComboBoxModel<>(new String[] {
				"200",
				"500"
			}));
			panel1.add(sampleRate, CC.xy(3, 3));

			//---- label2 ----
			label2.setText("Terminal:");
			panel1.add(label2, CC.xy(1, 5));

			//---- terminalConfig ----
			terminalConfig.setModel(new DefaultComboBoxModel<>(new String[] {
				"Diff",
				"NRSE",
				"RSE",
				"Pseudo",
				"Default"
			}));
			panel1.add(terminalConfig, CC.xy(3, 5));

			//---- refresh ----
			refresh.setText("Refresh");
			refresh.addActionListener(e -> refreshActionPerformed(e));
			panel1.add(refresh, CC.xy(3, 11));
		}
		add(panel1, CC.xy(3, 1));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JScrollPane scrollPane1;
	private JTable signalTable;
	private JPanel panel1;
	private JLabel label3;
	private JComboBox deviceSelection;
	private JLabel label1;
	private JComboBox<String> sampleRate;
	private JLabel label2;
	private JComboBox<String> terminalConfig;
	private JButton refresh;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	protected void panelToModel() {
		DefaultTableModel model = (DefaultTableModel) signalTable.getModel();
		if (dc == null) {
			dc = new RpDevice();
		} else {
			RpUtil.resetDC(dc);
		}

		// ? dc.setDeviceClass( driver.getClass().getCanonicalName() );
		dc.setConnectionType(RpConnType.DA_QMX);

		String srate = (String) sampleRate.getSelectedItem();
		int rate = Integer.parseInt(srate);

		RpLinearUnit mV = new RpLinearUnit(1.0, 0, "mV");

		for (int row = 0; row < model.getRowCount(); row++) {
			Object o = model.getValueAt(row, COL_OBJECT);
			Boolean b = (Boolean) model.getValueAt(row, COL_ENABLED);
			Boolean v = b; // (Boolean) model.getValueAt(row, COL_VISIBLE);
			String p = (String) model.getValueAt(row, COL_PORT);
			String n = (String) model.getValueAt(row, COL_SIGNAME);

			if (n == null) {
				n = p;
			} else {
				n = n.trim();
				if (n.length() == 0) {
					n = p;
				}
			}
			if (b) {
				//				if (o instanceof WaveformDescription) {
				RpMetric wave = RpUtil.createRpMetric(p, p, n, rate, rate / 2, mV);
				

				RpStream s = RpUtil.getStreamFromName(dc.getStreams(), StreamID.WAVEFORM.getName());
				if( s == null ) {
					s = new RpStream();
					dc.getStreams().add(s);
				}
				s.getMetric().add(wave);
				//				} else if (o instanceof RpMetric) {
				//					RpMetric metric = (RpMetric) o;
				//					dc.getMetrics().add(metric);
				//				} else {
				//					assert (false) : "Unknown signal description type.";
				//				}
			}
		}

		StringStringMap params = dc.getParam();
		if( params == null ) {
			params = new StringStringMap();
			dc.setParam( params );
		}
		params.put("rate", "" + rate);
		params.put("terminalConfig", "" + terminalConfig.getSelectedItem());
		dc.setConnectionValue("DAQmx");
		dc.setModelName((String) "NIDaq-mx"); // hardwareModel.getSelectedItem());
		dc.setName((String) "NIDaq");
	}

	@Override
	public boolean next() {
		// try {
		// driver.disconnect();
		// } catch (Exception e) {
		// // catch any exception and ignore
		// }

		panelToModel();

		wizard.popPageUntil("Hardware Setup");

		return true;
	}

	@Override
	public boolean finish() {
		return true;
	}

	@Override
	public void previous() {
		// TODO Auto-generated method stub

	}

}
