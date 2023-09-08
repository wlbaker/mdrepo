/*
 * Created by JFormDesigner on Mon Oct 05 13:52:14 CDT 2009
 */

package idea.devwizard;

import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.util.List;

import javax.swing.DefaultComboBoxModel;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.JTextField;
import javax.swing.event.TableModelEvent;
import javax.swing.event.TableModelListener;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumnModel;
import javax.swing.table.TableModel;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import icuInterface.RpUtil;
import icuInterface.conf.dev.SocketDeviceConfiguration;
import icuInterface.events.CapabilitiesEvent;
import idea.conf.DeviceCapabilities;
import idea.conf.DeviceConfiguration;
import idea.conf.DeviceFactory;
import idea.display.BandLayout;
import idea.display.FieldData;
import idea.display.ParameterLayout;
import idea.display.WaveformData;
import idea.driver.intellivue.IntellivueDriver;
import idea.intf.AdapterInterface;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.DisplayConfig;
import idea.model.PersistentItem;
import idea.schema.rp.RpConnType;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpStream;
import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;
import idea.gui.ColorRenderer;
import idea.gui.WizardMasterInterface;
import idea.gui.WizardPanelInterface;

/**
 * @author User #2
 */
@Slf4j
@SuppressWarnings("serial")
public class WizRefreshablePanel extends JPanel implements WizardPanelInterface, StreamConsumer, TableModelListener {
	private static final int COL_OBJ = 0;
	private static final int COL_ENABLED = 1;
	private static final int COL_VISIBLE = 2;
	private static final int COL_PORT = 3;
	private static final int COL_SIGNAME = 4;

	// private SocketDeviceConfiguration dc;
	private RpDevice rp_conf;
	private AdapterInterface driver;
	private ColorRenderer colorRenderer;
	private WizardMasterInterface wizard;
	private String driverClassName;
	private boolean is_connecting;

	public WizRefreshablePanel(WizardMasterInterface wizard, RpDevice dev_conf, String driverClassName) {
		initComponents();
		this.wizard = wizard;
		this.rp_conf = dev_conf;
		this.driverClassName = driverClassName;

		refresh();

		colorRenderer = new ColorRenderer(signalTable, signalTable.getDefaultRenderer(Object.class));
		colorRenderer.addRenderer(Boolean.class, signalTable.getDefaultRenderer(Boolean.class));
		// signalTable.setDefaultRenderer(Object.class, colorRenderer);
		signalTable.setDefaultRenderer(Boolean.class, colorRenderer);

		TableModel model = signalTable.getModel();
		model.addTableModelListener(this);

	}

	@Override
	public void refresh() {
		log.warn("FIXME: refresh not ready");
		// TableModelFixer fixer = (TableModelFixer) signalTable.getModel();

		AdapterInterface driver;
		driver = DeviceFactory.createDriver(driverClassName, null);

		DeviceCapabilities cap;
		cap = (DeviceCapabilities) driver.getStaticCapabilities();

		try {
			updateCapabilities(cap);
		} catch (Exception e) {
			log.error("refresh error", e);
		}

		String[] models = cap.getModels();

		hardwareModel.setEnabled(models != null);
		if (models != null) {
			hardwareModel.setModel(new DefaultComboBoxModel(models));
		}

		modelToPanel();
	}

	private void modelToPanel() {

		String connectionValue = rp_conf.getConnectionValue();
		if (connectionValue != null) {
			ipAddress.setText(connectionValue);
		}

		String autoConfig = rp_conf.getParam().get("autoConfig");
		autoSelect.setSelected("true".equals(autoConfig));

		List<? extends RpMetric> waves = RpUtil.getMetrics(rp_conf, StreamID.WAVEFORM);
		if (waves != null) {

			DefaultTableModel model = (DefaultTableModel) signalTable.getModel();
			for (RpMetric wave : waves) {
				int row = findRow(model, wave.getLocation());
				if (row < 0) {
					// ??? what now
					log.error("COULD NOT FIND WAVE: {}", wave.getLocation());
				} else {
					model.setValueAt(Boolean.TRUE, row, COL_ENABLED);
					model.setValueAt(Boolean.TRUE, row, COL_VISIBLE);
					model.setValueAt(wave.getName(), row, COL_SIGNAME);
				}
			}
		}

		List<? extends RpMetric> metrics = RpUtil.getMetrics(rp_conf, StreamID.MEASUREMENT);
		if (metrics != null) {

			DefaultTableModel model = (DefaultTableModel) signalTable.getModel();
			for (RpMetric metric : metrics) {
				int row = findRow(model, metric.getLocation());
				if (row < 0) {
					// ??? what now
					log.error("COULD NOT FIND METRIC: {}", metric.getLocation());
				} else {
					model.setValueAt(Boolean.TRUE, row, COL_ENABLED);
					model.setValueAt(Boolean.TRUE, row, COL_VISIBLE);
					model.setValueAt(metric.getName(), row, COL_SIGNAME);
				}
			}
		}
	}

	private int findRow(DefaultTableModel model, String loc) {

		int row = -1;

		if (loc == null) {
			log.error("CANNOT FIND ROW FOR LOC=NULL");
		} else {
			for (int idx = 0; idx < model.getRowCount(); idx++) {
				RpMetric m = (RpMetric) model.getValueAt(idx, COL_OBJ);

				if (m == null) {
					log.error("NULL METRIC IN TABLE?");
				} else if (loc.equals(m.getLocation())) {
					// we found our signal
					row = idx;
					break;
				}
			}
		}

		return row;
	}

	private void refreshActionPerformed(ActionEvent e) {

		try {
			refresh.setEnabled(false);
			refreshActionConnect(ipAddress.getText());
		} catch (IOException e1) {
			GuiUtil.showError("Device Setup / Refresh", e1);
		}
	}

	private void refreshActionConnect(String addr) throws IOException {

		colorRenderer.clear();

		SocketDeviceConfiguration dconf;

		if (rp_conf != null) {
			rp_conf.setConnectionValue(addr);
			dconf = (SocketDeviceConfiguration) RpUtil.createDeviceConfiguration(rp_conf, false);
		} else {
			dconf = (SocketDeviceConfiguration) DeviceFactory.createConfig(driverClassName);
			dconf.setHost(addr);
		}

		if (driver != null) {
			driver.disconnect();
		}

		driver = DeviceFactory.createDriver(dconf);

		if (driver instanceof IntellivueDriver) {
			// philips gives numerics devents
			driver.addStreamListener(StreamID.MEASUREMENT, this);
		}
		driver.addStreamListener(StreamID.DISPLAY, this);
		driver.addStreamListener(StreamID.CAPABILITIES, this);
		driver.connect();

		is_connecting = true;
		Runnable r = new Runnable() {

			@Override
			public void run() {

				while (is_connecting) {
					int tick = 1;
					try {
						Thread.sleep(1000);
						driver.tick();
						tick++;
						if (tick % 6 == 99) { // 3) {
							driver.requestCapabilities();
						}
					} catch (InterruptedException | IOException e) {
						e.printStackTrace();
					}
				}

				log.warn("DEBUG: refresh ending");
				refresh.setEnabled(true);
			}
		};

		Thread th = new Thread(r);
		th.start();

	}

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {

		if (sid == StreamID.DISPLAY) {
			DisplayConfig conf = (DisplayConfig) item;


			DefaultTableModel model = (DefaultTableModel) signalTable.getModel();

			updateBands(model, conf);

			updatePBoxes(model, conf);

			signalTable.repaint();
		} else if (sid == StreamID.MEASUREMENT) {

			updateSignalsFound(sid, item);

		} else if (sid == StreamID.WAVEFORM) {

			updateSignalsFound(sid, item);
		} else if (sid == StreamID.CAPABILITIES) {
			CapabilitiesEvent ce = (CapabilitiesEvent) item;
			DeviceConfiguration caps = ce.getCapabilities();

			updateCapabilities(caps);
			modelToPanel(); // restore the check marks

		}
	}

	private void updateSignalsFound(StreamID sid, PersistentItem parent) {
		DefaultTableModel model = (DefaultTableModel) signalTable.getModel(); // fixer.getShadowedModel();
			RpMetric[] items = parent.getMetrics();
			if (items != null) {
				for (RpMetric item : items) {
					int row = findRow(model, item.getLocation());
					if (row >= 0) {
						colorRenderer.setCellColor(row, COL_ENABLED, Color.YELLOW);
						colorRenderer.setCellColor(row, COL_SIGNAME, Color.YELLOW);
					}
				}
				signalTable.repaint();
			}
	}

	private void updateCapabilities(DeviceConfiguration caps) {

		StreamID[] sids = new StreamID[] { StreamID.WAVEFORM, StreamID.MEASUREMENT };

		DefaultTableModel model = (DefaultTableModel) signalTable.getModel(); // fixer.getShadowedModel();
		model.setRowCount(0);

		for (StreamID sid : sids) {
			List<RpStream> streams = caps.getStreams();

			for (RpStream stream : streams) {

				for (RpMetric desc : (List<? extends RpMetric>)stream.getMetric()) {
					addOneRow(model, desc, sid);
				}
			}
		}

		if (model.getRowCount() == 0) {
			log.warn("no items added!");
		}
		return;
	}

	private void addOneRow(DefaultTableModel model, RpMetric desc, StreamID sid) {
		boolean ena = false;
		boolean vis = false;
		String s_name = desc.getCode();
		String s_desc = desc.getName();
		if (s_desc == null) {
			s_desc = "";
		}
		if (s_name != null) {
			if (s_name.equals(s_desc)) {
				// don't repeat
			} else {
				// show both
				s_desc = s_name + ": " + s_desc;
			}
		}
		s_name = desc.getLocation();
		model.addRow(new Object[] { desc, ena, vis, s_name, s_desc, sid });
	}

	private void updatePBoxes(DefaultTableModel model, DisplayConfig conf) {
		if (conf == null || conf.getNumPBoxes() == 0) {
			return;
		}

		for (ParameterLayout box : conf.getParameterBoxs() ) {
			FieldData[] params = box.fields;
			if (params != null) {
				for (FieldData param : params) {
					if (param == null) {
						log.error("?Param from driver is null");
						continue;
					}
					String loc = param.getLoc();
					if (loc != null) {
						GuiUtil.showMessage("FIXME: in wizRefresh--at b--next 12 lines");
//						RpMetric desc = caps.getMetricDescription(loc);
//						int row = this.findRow(model, loc);
//						if (row < 0) {
//							addOneRow(model, desc, StreamID.MEASUREMENT);
//							row = model.getRowCount() - 1;
//						}
//						if (row < 0) {
//							log.error("What is row for desc: {}", desc);
//						} else {
//							colorRenderer.setCellColor(row, COL_ENABLED, Color.GREEN);
//							colorRenderer.setCellColor(row, COL_SIGNAME, Color.GREEN);
//						}
					}
				}
			}
		}

	}

	private void updateBands(DefaultTableModel model, DisplayConfig conf) {
		if (conf == null || conf.getNumBands() == 0 ) {
			return;
		}
		for (BandLayout band : conf.getBands() ) {
			if (band.getWaveCount() > 0) {
				for (WaveformData wave :  band.getWaves() ) {
					GuiUtil.showMessage("FIXME: in wizRefresh--at b--next 10 lines");
//					WaveformDescription desc = caps.getWaveformDescription(wave.getLoc());
//					if (desc != null) {
//						int row = this.findRow(model, desc.getLocation());
//						if (row < 0) {
//							addOneRow(model, desc, StreamID.WAVEFORM);
//							row = model.getRowCount() - 1;
//						}
//						if (row < 0) {
//							log.error("What is row for desc: {}", desc);
//						} else {
//							colorRenderer.setCellColor(row, COL_ENABLED, Color.GREEN);
//							colorRenderer.setCellColor(row, COL_SIGNAME, Color.GREEN);
//						}
//					}
				}
			}
		}
	}

	private void panelToModel() {

		RpUtil.resetDC(rp_conf);

		TableModel model = signalTable.getModel();

		String driverName = driverClassName;
		int idx = driverClassName.lastIndexOf(".");
		if (idx > 0) {
			driverName = driverClassName.substring(idx + 1);
		}

		String hwName = (String) hardwareModel.getSelectedItem();
		if (hwName == null) {
			hwName = driverClassName;
		}
		rp_conf.setName(hwName);
		rp_conf.setDriverName(driverName);
		rp_conf.setDeviceClass(driverClassName);
		rp_conf.setConnectionValue(ipAddress.getText());
		rp_conf.setConnectionType(RpConnType.ETHERNET);

		// RpUtil.setParam(dev_conf.getParam(), "autoConfig", "" +
		// autoSelect.isSelected());

		List<? extends RpMetric> waves = RpUtil.getMetrics(rp_conf, StreamID.WAVEFORM);
		List<? extends RpMetric> metrics = RpUtil.getMetrics(rp_conf, StreamID.MEASUREMENT);
		for (int row = 0; row < model.getRowCount(); row++) {
			RpMetric desc = (RpMetric) model.getValueAt(row, COL_OBJ);
			Boolean b = (Boolean) model.getValueAt(row, COL_ENABLED);
			Boolean v = (Boolean) model.getValueAt(row, COL_VISIBLE);
			String p = (String) model.getValueAt(row, COL_PORT);

			int dataRate = 0;
			if (b) {

				GuiUtil.showMessage("FIXME: in wizRefresh--at b--next 6 lines");
//				if (desc instanceof WaveformDescription) {
//					RpMetric wave = RpUtil.createWaveformDescription((WaveformDescription) desc);
//					waves.add(wave);
//				} else {
//					metrics.add(desc);
//				}

			}
		}

		return;
	}

	@Override
	public boolean next() {
		safe_disconnect();
		panelToModel(); // copy GUI information to model

		wizard.popPageUntil("Hardware Setup");

		return true;
	}

	private void safe_disconnect() {
		is_connecting = false;
		if (driver != null) {
			try {
				driver.disconnect();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}

	@Override
	public boolean finish() {
		safe_disconnect();
		return true;
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		panel1 = new JPanel();
		scrollPane1 = new JScrollPane();
		signalTable = new JTable();
		panel2 = new JPanel();
		label1 = new JLabel();
		ipAddress = new JTextField();
		label2 = new JLabel();
		hardwareModel = new JComboBox();
		autoSelect = new JCheckBox();
		refresh = new JButton();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setLayout(new FormLayout("default:grow", "default"));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout("default:grow, $lcgap, default", "fill:default:grow"));

			//======== scrollPane1 ========
			{

				//---- signalTable ----
				signalTable.setModel(new DefaultTableModel(new Object[][] { { null, false, null, null, null, null },
						{ null, null, null, null, null, null }, }, new String[] { null, "Enabled", "Vis", "IO Point",
						"Signal Name", "Signal Type" }) {
					Class<?>[] columnTypes = new Class<?>[] { Object.class, Boolean.class, Boolean.class, Object.class,
							Object.class, Object.class };
					boolean[] columnEditable = new boolean[] { false, true, true, false, true, true };

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
					cm.getColumn(2).setPreferredWidth(50);
					cm.getColumn(3).setPreferredWidth(100);
					cm.getColumn(4).setPreferredWidth(200);
				}
				scrollPane1.setViewportView(signalTable);
			}
			panel1.add(scrollPane1, cc.xy(1, 1));

			//======== panel2 ========
			{
				panel2.setLayout(new FormLayout("right:default, $lcgap, [70dlu,default]",
						"2*(default, $lgap), default:grow, 2*($lgap, default)"));

				//---- label1 ----
				label1.setText("IP Address:");
				panel2.add(label1, cc.xy(1, 1));
				panel2.add(ipAddress, cc.xy(3, 1));

				//---- label2 ----
				label2.setText("Model:");
				panel2.add(label2, cc.xy(1, 3));
				panel2.add(hardwareModel, cc.xy(3, 3));

				//---- autoSelect ----
				autoSelect.setText("Auto select");
				panel2.add(autoSelect, cc.xy(3, 7));

				//---- refresh ----
				refresh.setText("Refresh");
				refresh.addActionListener(new ActionListener() {
					@Override
					public void actionPerformed(ActionEvent e) {
						refreshActionPerformed(e);
					}
				});
				panel2.add(refresh, cc.xy(3, 9));
			}
			panel1.add(panel2, cc.xy(3, 1));
		}
		add(panel1, cc.xy(1, 1));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JPanel panel1;
	private JScrollPane scrollPane1;
	private JTable signalTable;
	private JPanel panel2;
	private JLabel label1;
	private JTextField ipAddress;
	private JLabel label2;
	private JComboBox hardwareModel;
	private JCheckBox autoSelect;
	private JButton refresh;

	// JFormDesigner - End of variables declaration //GEN-END:variables

	@Override
	public void previous() {
		// TODO Auto-generated method stub

	}

	@Override
	public void tableChanged(TableModelEvent tme) {
		log.debug("table changed: {}", tme.getType());
		if (tme.getType() == TableModelEvent.UPDATE) {
			TableModel model = signalTable.getModel();
			int row = tme.getFirstRow();
			Boolean viz = (Boolean) model.getValueAt(row, COL_VISIBLE);
			if (viz) {
				Boolean ena = (Boolean) model.getValueAt(row, COL_ENABLED);
				if (!ena) {
					ena = true;
					model.setValueAt(ena, row, COL_ENABLED);
				}
			}
		}
	}

}
