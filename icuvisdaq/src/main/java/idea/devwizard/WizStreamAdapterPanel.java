/*
 * Created by JFormDesigner on Mon Oct 05 13:52:41 CDT 2009
 */

package idea.devwizard;

import java.awt.CardLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.io.IOException;
import java.text.DecimalFormat;
import java.util.Arrays;
import java.util.List;

import javax.swing.DefaultComboBoxModel;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;
import javax.swing.JTable;
import javax.swing.JTextField;
import javax.swing.SwingUtilities;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumnModel;
import javax.swing.table.TableModel;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.layout.FormLayout;

import icuInterface.RpUtil;
import icuInterface.events.CapabilitiesEvent;
import icuInterface.events.ConnectionItem;
import idea.conf.CompositeDescription;
import idea.conf.DeviceCapabilities;
import idea.conf.DeviceConfiguration;
import idea.conf.DeviceFactory;
import idea.connections.SerialConnection;
import idea.intf.AdapterInterface;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.PersistentItem;
import idea.schema.rp.RpConnType;
import idea.schema.rp.RpConnection;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpStream;
import idea.schema.rp.RpUnit;
import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;
import idea.ct.CtApiMCCUL;
import idea.ct.CtEthernetPanel;
import idea.ct.CtInfinityPanel;
import idea.ct.CtIntellivuePanel;
import idea.ct.CtInterface;
import idea.ct.CtLabjackPanel;
import idea.ct.CtNonePanel;
import idea.ct.CtPhidgetPanel;
import idea.ct.CtSerialPanel;
import idea.gui.ColorRenderer;
import idea.gui.WizardMasterInterface;
import idea.gui.WizardPanelInterface;

/**
 * @author User #2
 */
@Slf4j
@SuppressWarnings("serial")
public class WizStreamAdapterPanel extends JPanel
		implements WizardPanelInterface, StreamConsumer, PropertyChangeListener {

	public static final int COL_OOBJECT = 0;
	public static final int COL_ENABLED = 1;
	private static final int COL_LOCATION = 2;
	private static final int COL_CODE = 3;
	private static final int COL_SIGNAME = 4;
	private static final int COL_FREQ = 5;
	private static final int COL_UNIT = 6;

	private AdapterInterface driver;
	// private AbstractStreamProducer driver;

	private DecimalFormat df2 = new DecimalFormat("0%");
	private RpDevice conf;

	private WizardMasterInterface wizard;
	private boolean is_open = false;

	CtInterface cti;
	protected boolean editable_checkbox;

	CtApiMCCUL mccul;

	public WizStreamAdapterPanel(WizardMasterInterface wizard, RpDevice conf) {
		initComponents();
		this.wizard = wizard;
		statusMessage.setText("");
		bandwidthMessage.setText("");

		driver = DeviceFactory.createDriver(conf.getDeviceClass(), conf);

		this.conf = conf;

		String dname = null;
		if (conf != null) {
			dname = conf.getName();
		}
		if (dname == null) {
			dname = "Unknown";
		}
		deviceName.setText(dname);

		intfCombo.setVisible(false);
		intfLabel.setVisible(false);

		// creates ct-interfaces
		// -- sets editor enable flag used in refresh
		init(driver.getStaticCapabilities());

		refresh(); // creates signal tables

		if (mccul != null) {
			// must be called after the table is created to
			// (1) update the gui with the config settings
			// (2) update the signal table with the frequency selected
			mccul.refresh(conf);
		}

		refreshButton.setEnabled(true);

		intfComboActionPerformed(null);
	}

	private void init(RpDevice caps) {
		intfCombo.removeAll();
		if (caps instanceof DeviceConfiguration) {
			DeviceCapabilities ccaps = (DeviceCapabilities) caps;
			RpConnection[] intfs = ccaps.getConnections();

			intfCombo.setVisible(intfs != null && intfs.length > 1);
			intfLabel.setVisible(intfs != null && intfs.length > 1);
			if (intfs != null) {
				for (RpConnection intf : intfs) {
					intfCombo.addItem(intf); // .getTyp().name());
					addInterfacePanel(intf, conf);
				}
			}
		}

	}

	private void addInterfacePanel(RpConnection intf, RpDevice dc) {
		editable_checkbox = true;
		JPanel connectionPanel;
		if (intf.getTyp() == RpConnType.RS_232) {
			SerialConnection serial = (SerialConnection) intf;
			connectionPanel = new CtSerialPanel();

			log.warn("FIXME: bandwidth update not ready");
		} else if (intf.getTyp() == RpConnType.DA_QMX) {
			connectionPanel = new CtSerialPanel();
		} else if (intf.getTyp() == RpConnType.DA_QMX_BASE) {
			connectionPanel = new CtSerialPanel();
		} else if (intf.getTyp() == RpConnType.PHIDGET) {
			connectionPanel = new CtPhidgetPanel();
		} else if (intf.getTyp() == RpConnType.ETHERNET) {
			connectionPanel = new CtEthernetPanel();
		} else if (intf.getTyp() == RpConnType.INTELLIVUE) {
			connectionPanel = new CtIntellivuePanel();
		} else if (intf.getTyp() == RpConnType.MCCUL) {
			mccul = new CtApiMCCUL();
			connectionPanel = mccul;
			connectionPanel.addPropertyChangeListener(this);
			editable_checkbox = false;
		} else if (intf.getTyp() == RpConnType.LAB_JACK) {
			connectionPanel = new CtLabjackPanel();
		} else if (intf.getTyp() == RpConnType.INFINITY) {
			CtInfinityPanel inf = new CtInfinityPanel();
			connectionPanel = inf;
		} else if (intf.getTyp() == RpConnType.NONE) {
			connectionPanel = new CtNonePanel(); // empty
		} else {
			log.warn("Interface not specified.  Defaulting to serial.");
			connectionPanel = new CtSerialPanel();
		}
		contentPanel.add(connectionPanel, intf.getTyp().name());
	}

	public void enableRefresh() {

		refreshButton.setEnabled(true);

	}

	public JTable getTableAt(int idx) {
		if (idx < 0) {
			idx = tabber.getSelectedIndex();
		}
		JTable table = null;
		JScrollPane scroller = (JScrollPane) tabber.getComponentAt(idx);
		if (scroller != null) {
			table = (JTable) scroller.getViewport().getView();
		}

		return table;
	}

	public JTable getTableForStream(StreamID sid) {
		JTable ret = null;
		JTable table;

		for (int idx = 0; idx < tabber.getTabCount(); idx++) {
			JScrollPane scroller = (JScrollPane) tabber.getComponentAt(idx);
			if (scroller != null) {
				table = (JTable) scroller.getViewport().getView();
				Object tsid = table.getClientProperty("streamID");
				if (sid.equals(tsid)) {
					ret = table;
					break;
				}
			}
		}

		return ret;
	}

	@Override
	public void refresh() {
		if (driver != null) {

			// put it on the GUI thread
			try {
				if (SwingUtilities.isEventDispatchThread()) {
					refresh((DeviceCapabilities) driver.getStaticCapabilities());
				} else {
					SwingUtilities.invokeAndWait(new Runnable() {

						@Override
						public void run() {
							refresh((DeviceCapabilities) driver.getStaticCapabilities());

						}
					});
				}
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}

	public void refresh(DeviceCapabilities caps) {
		// move to the GUI thread
		if (SwingUtilities.isEventDispatchThread()) {
			_refresh(caps);
		} else {
			Runnable r = new Runnable() {
				@Override
				public void run() {
					_refresh(caps);
				}
			};
			SwingUtilities.invokeLater(r);
		}
	}

	public void _refresh(DeviceCapabilities caps) {

		removeAllTabs();
		try {

			if (caps != null) {
				List<RpStream> streams = caps.getStreams();
				if (streams != null) {
					for (RpStream stream : streams) {
						List<RpMetric> metrics = stream.getMetric();
						String name = stream.getName();
						String model = stream.getModel();
						if (model == null) {
							Class<?> cl = stream.getPIClass();
							if (cl != null) {
								model = cl.getName();
							}
						}
						addModelTab(name, model, StreamID.fromName(name), metrics);
					}
				}

				String[] models = caps.getModels();

				hardwareModel.setVisible(models != null);
				modelLabel.setVisible(models != null);

				if (models == null) {
					hardwareModel.setModel(new DefaultComboBoxModel()); // ensures
																		// empty
																		// set
				} else {
					hardwareModel.setModel(new DefaultComboBoxModel(models));
				}

			}
		} catch (Exception e) {
			GuiUtil.showError("Error device config.", e);
		}

	}

	private void removeAllTabs() {
		for (int i = tabber.getTabCount() - 1; i >= 0; i--) {
			JTable table = getTableAt(i);
			DefaultTableModel model = (DefaultTableModel) table.getModel();
			model.setRowCount(0);
			tabber.removeTabAt(i);
		}

	}

	private void addModelTab(String tab_name, String streamModel, StreamID sid, List<RpMetric> metrics) {
		JTable signalTable = createSignalTable();
		signalTable.putClientProperty("streamID", sid);
		DefaultTableModel tableModel = (DefaultTableModel) signalTable.getModel();
		if (tableModel == null) {
			log.error("unexpected null table model.");
			return;
		}

		refreshMetrics(tableModel, streamModel, sid, metrics);

		JScrollPane scrollPane1 = new JScrollPane();
		scrollPane1.setPreferredSize(new Dimension(454, 223));
		scrollPane1.setViewportView(signalTable);
		GuiUtil.initTable(signalTable, true);

		tabber.addTab(tab_name, scrollPane1);
	}

	private JTable createSignalTable() {

		JTable signalTable = new JTable();

		// ---- signalTable ----
		signalTable.setModel(new DefaultTableModel(new Object[][] {}, //
				new String[] { null, "Enabled", "Dev", "Code", "Signal Name", "Freq", "Unit" } //
		) {
			Class<?>[] columnTypes = new Class<?>[] { Object.class, Boolean.class, Object.class, Object.class,
					Object.class, Object.class, Object.class };
			boolean[] columnEditable = new boolean[] { false, editable_checkbox, false, false, false, false, false };

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
			cm.getColumn(0).setResizable(false);
			cm.getColumn(1).setPreferredWidth(50);
			cm.getColumn(2).setPreferredWidth(50);
			cm.getColumn(3).setPreferredWidth(70);
			cm.getColumn(4).setPreferredWidth(180);
			cm.getColumn(5).setPreferredWidth(60);
			cm.getColumn(6).setPreferredWidth(60);
		}

		ColorRenderer colorRenderer = new ColorRenderer(signalTable, signalTable.getDefaultRenderer(Object.class));
		colorRenderer.addRenderer(Boolean.class, signalTable.getDefaultRenderer(Boolean.class));
		signalTable.setDefaultRenderer(Boolean.class, colorRenderer);

		return signalTable;
	}

	private void refreshMetrics(DefaultTableModel tableModel, String streamModel, StreamID sid,
			List<RpMetric> metrics) {
		if (metrics == null) {
			return;
		}
		RpStream stream = findOrCreate(conf.getStreams(), sid, streamModel);
		for (RpMetric mdesc : metrics) {

			boolean selected = (conf == null) ? false : RpUtil.hasMetric(stream.getMetric(), mdesc);

			String loc = fix_subscripts(mdesc.getLocation().toString());
			String code = fix_subscripts(mdesc.getCode());
			String name = fix_subscripts(mdesc.getName());
			String freq = "";

			if (mdesc instanceof CompositeDescription) {
				CompositeDescription comp = (CompositeDescription) mdesc;
				if (name == null || name.length() == 0) {
					name = getNameFromDescriptions(comp.getSamplesPerPacket(), comp.getMetrics());
				}
			}

			Integer rate = mdesc.getSampleRate();
			if (rate != null && rate > 1) {
				freq = rate + " Hz";
			}

			String unitName = null;
			RpUnit unit = mdesc.getUnit();
			if (unit != null) {
				unitName = unit.getUnitName();
			}

			if (unitName == null || unitName.length() == 0) {
				unitName = "[NONE]";
			}
			tableModel.addRow(new Object[] { mdesc, selected, loc, code, name, freq, unitName });
		}
	}

	private String getNameFromDescriptions(int count, RpMetric[] metrics) {
		if (metrics == null) {
			return null;
		}
		StringBuffer buf = new StringBuffer();
		if (count > 1) {
			buf.append("[");
			buf.append(count);
			buf.append("]: ");
		}

		boolean first = true;
		for (RpMetric metric : metrics) {
			if (first) {
				first = false;
			} else {
				buf.append(", ");
			}
			String code = metric.getCode();
			if (code == null || code.length() == 0) {
				code = metric.getLocation();
			}
			buf.append(code);
		}
		return buf.toString();
	}

	private String fix_subscripts(String s) {
		if (s != null) {
            // FIXME: UTF8 not being correctly observed...but not using the hp-agilent either
            // FIXME: Should probably require the drivers to provide UTF8 descriptions, then this wouldnt be an issue
            /* BTW: this won't work any more regardless...removed non UTF8 chars
			char ch_gbar = 287; // hp-agilent
			if (s.indexOf('') >= 0 || s.indexOf('') >= 0 || s.indexOf(ch_gbar) >= 0) {
				s = s.replaceAll("", "<sub>2</sub>");
				s = s.replaceAll("", "<sub>2</sub>");
				s = s.replaceAll("" + ch_gbar, "<sub>2</sub>");
				s = "<html>" + s;
			}
            */
		}
		return s;
	}

	protected void panelToModel() {
		if (conf == null) {
			conf = new RpDevice();
		} else {
			RpUtil.resetDC(conf);
		}

		conf.setModelName((String) hardwareModel.getSelectedItem());
		if (cti != null) {
			cti.panelToModel(conf);
		}

		List<RpStream> dc_streams = conf.getStreams();
		for (int idx = 0; idx < tabber.getTabCount(); idx++) {
			JTable signalTable = getTableAt(idx);
			DefaultTableModel model = (DefaultTableModel) signalTable.getModel();

			StreamID sid = (StreamID) signalTable.getClientProperty("streamID");

			RpStream stream = findOrCreate(dc_streams, sid, null); // this
																	// should be
																	// FIND only
			for (int row = 0; row < model.getRowCount(); row++) {
				Object o = model.getValueAt(row, COL_OOBJECT);
				Boolean b = (Boolean) model.getValueAt(row, COL_ENABLED);
				// String p = (String) model.getValueAt(row, COL_LOCATION);
				String n = (String) model.getValueAt(row, COL_SIGNAME);

				if (b) {
					stream.getMetric().add((RpMetric) o);
				}
			}
		}

		String name = deviceName.getText().trim();
		if (name.length() > 0) {
			conf.setName(name);
		}
	}

	private RpStream findOrCreate(List<RpStream> rp_streams, StreamID sid, String piModel) {
		RpStream found = null;
		for (RpStream s : rp_streams) {
			if (s.getName().equals(sid.getName())) {
				found = s;
				break;
			}
		}
		if (found == null) {
			found = new RpStream();
			found.setName(sid.getName());
			found.setModel(piModel);
			rp_streams.add(found);
		}
		return found;
	}

	private void selectAllActionPerformed(ActionEvent e) {
		selectMetrics(true);
	}

	private void deselectAllActionPerformed(ActionEvent e) {
		selectMetrics(false);
	}

	private void selectMetrics(boolean b) {
		JTable signalTable = getTableAt(-1);
		DefaultTableModel model = (DefaultTableModel) signalTable.getModel();

		for (int row = 0; row < model.getRowCount(); row++) {
			Object o = model.getValueAt(row, COL_OOBJECT);
			model.setValueAt(b, row, COL_ENABLED);
		}
	}

	private void refreshButtonActionPerformed(ActionEvent e) {

		refreshButton.setEnabled(false);

		// conf = DeviceFactory.createConfig(driver.getClass());

		panelToModel();

		try {
			driver.disconnect();
		} catch (Exception ex) {
			// catch any exception and ignore
		}
		driver = DeviceFactory.createDriver(conf);

		driver.addStreamListener(null, this); // retrieve all events

		try {
			driver.connect();
		} catch (IOException e1) {
			statusMessage.setText("<html>ERR: " + e1.getMessage());
			refreshButton.setEnabled(true); // try again
		}

		is_open = true;
		Runnable r = new Runnable() {

			@Override
			public void run() {

				while (is_open) {
					try {
						Thread.sleep(1000);
						driver.tick();
					} catch (InterruptedException e) {
						break;
					}
				}

			}
		};

		Thread th = new Thread(r);
		th.start();
	}

	private void hardwareModelActionPerformed(ActionEvent e) {
		String model = (String) hardwareModel.getSelectedItem();
		if (model != null) {
			deviceName.setText(model);
		}
	}

	private void intfComboActionPerformed(ActionEvent e) {

		if (cti != null) {
			cti.release();
		}

		RpConnection item = (RpConnection) intfCombo.getSelectedItem();
		if (item == null) {
			return; // no available interfaces
		}
		String name = item.getTyp().name();
		CardLayout card = (CardLayout) contentPanel.getLayout();
		card.show(contentPanel, (String) name);

		/*
		 * FIXME: When JRE7 is obsoleted, replace with METHOD REFERENCE
		 * 
		 * CtInterface::init
		 */
		try {
			cti = null;
			for (Component comp : contentPanel.getComponents()) {
				if (comp.isVisible()) {
					cti = (CtInterface) comp;
					break;
				}
			}

			if (cti != null) {
				cti.init(null);
			}
		} catch (Exception ex) {
			throw new RuntimeException("CtInterface init error", ex);
		}

	}

	/*
	 * Utility functions that are no longer found in the DeviceConfiguration
	 * class...now RpDevice
	 */

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		deviceNamePanel = new JPanel();
		label1 = new JLabel();
		deviceName = new JTextField();
		tabber = new JTabbedPane();
		panel1 = new JPanel();
		headerPanel = new JPanel();
		modelLabel = new JLabel();
		hardwareModel = new JComboBox<>();
		intfLabel = new JLabel();
		intfCombo = new JComboBox<>();
		contentPanel = new JPanel();
		statusMessage = new JLabel();
		bandwidthMessage = new JLabel();
		refreshButton = new JButton();
		panel2 = new JPanel();
		selectAll = new JButton();
		deselectAll = new JButton();

		// ======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout("[200dlu,default]:grow, $lcgap, 110dlu",
				"default, $lgap, fill:default:grow, $rgap, default"));

		// ======== deviceNamePanel ========
		{
			deviceNamePanel.setLayout(new FormLayout("default, $lcgap, [150dlu,default], $lcgap, default", "default"));

			// ---- label1 ----
			label1.setText("Device Name:");
			deviceNamePanel.add(label1, CC.xy(1, 1));
			deviceNamePanel.add(deviceName, CC.xy(3, 1));
		}
		add(deviceNamePanel, CC.xy(1, 1));

		// ======== tabber ========
		{
			tabber.setMinimumSize(new Dimension(187, 78));
			tabber.setPreferredSize(new Dimension(187, 78));
		}
		add(tabber, CC.xy(1, 3));

		// ======== panel1 ========
		{
			panel1.setLayout(new FormLayout("default:grow",
					"[12dlu,default], $lgap, default, $lgap, fill:default:grow, 3*($lgap, default)"));

			// ======== headerPanel ========
			{
				headerPanel.setLayout(new FormLayout("default, $lcgap, default:grow", "default, $lgap, default"));

				// ---- modelLabel ----
				modelLabel.setText("Model:");
				headerPanel.add(modelLabel, CC.xy(1, 1));

				// ---- hardwareModel ----
				hardwareModel
						.setModel(new DefaultComboBoxModel<>(new String[] { "Evita 4", "Evita 2 dura", "Evita XL" }));
				hardwareModel.addActionListener(e -> hardwareModelActionPerformed(e));
				headerPanel.add(hardwareModel, CC.xy(3, 1));

				// ---- intfLabel ----
				intfLabel.setText("Interface:");
				headerPanel.add(intfLabel, CC.xy(1, 3));

				// ---- intfCombo ----
				intfCombo.addActionListener(e -> intfComboActionPerformed(e));
				headerPanel.add(intfCombo, CC.xy(3, 3));
			}
			panel1.add(headerPanel, CC.xy(1, 3));

			// ======== contentPanel ========
			{
				contentPanel.setLayout(new CardLayout());
			}
			panel1.add(contentPanel, CC.xy(1, 5));

			// ---- statusMessage ----
			statusMessage.setText("??status");
			panel1.add(statusMessage, CC.xy(1, 7));

			// ---- bandwidthMessage ----
			bandwidthMessage.setText("??bandwidth");
			panel1.add(bandwidthMessage, CC.xy(1, 9));

			// ---- refreshButton ----
			refreshButton.setText("Test / Refresh");
			refreshButton.addActionListener(e -> refreshButtonActionPerformed(e));
			panel1.add(refreshButton, CC.xy(1, 11));
		}
		add(panel1, CC.xy(3, 3));

		// ======== panel2 ========
		{
			panel2.setLayout(new FormLayout("2*([60dlu,default], $lcgap), default", "default"));

			// ---- selectAll ----
			selectAll.setText("Select All");
			selectAll.addActionListener(e -> selectAllActionPerformed(e));
			panel2.add(selectAll, CC.xy(1, 1));

			// ---- deselectAll ----
			deselectAll.setText("Deselect All");
			deselectAll.addActionListener(e -> deselectAllActionPerformed(e));
			panel2.add(deselectAll, CC.xy(3, 1));
		}
		add(panel2, CC.xy(1, 5));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JPanel deviceNamePanel;
	private JLabel label1;
	private JTextField deviceName;
	private JTabbedPane tabber;
	private JPanel panel1;
	private JPanel headerPanel;
	private JLabel modelLabel;
	private JComboBox<String> hardwareModel;
	private JLabel intfLabel;
	private JComboBox<RpConnection> intfCombo;
	private JPanel contentPanel;
	private JLabel statusMessage;
	private JLabel bandwidthMessage;
	private JButton refreshButton;
	private JPanel panel2;
	private JButton selectAll;
	private JButton deselectAll;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	@Override
	public void previous() {
		try {
			driver.disconnect();
		} catch (Exception e) {
			// catch any exception and ignore
		}
	}

	@Override
	public boolean next() {
		this.finish(); // close the port

		panelToModel();

		wizard.popPageUntil("Hardware Setup");

		return true;
	}

	@Override
	public boolean finish() {

		// if the port is open, try to disconnect
		is_open = false;
		try {
			driver.disconnect();
		} catch (Exception e) {
			log.error("error on disconnect", e);
		}

		if (cti != null) {
			cti.release();
		}

		return true;
	}

	public void hideDeviceName() {
		deviceNamePanel.setVisible(false);
	}

	private void updateStreamDisplay(JTable table, PersistentItem item) {
		TableModel model = table.getModel();
		ColorRenderer colorRenderer = (ColorRenderer) table.getDefaultRenderer(Boolean.class);

		RpMetric[] waves = item.getMetrics();
		if (waves != null) {
			for (RpMetric desc : waves) {
				int row = findRow(model, desc.getLocation());
				if (row < 0) {
					log.error("What is row for desc: {}" + desc);
				} else {
					colorRenderer.setCellColor(row, COL_ENABLED, Color.GREEN);
					colorRenderer.setCellColor(row, COL_SIGNAME, Color.GREEN);
				}
			}
		}
	}

	private int findRow(TableModel model, String location) {

		int row = -1;

		for (int idx = 0; idx < model.getRowCount(); idx++) {
			RpMetric m = (RpMetric) model.getValueAt(idx, COL_OOBJECT);

			if (location.equals(m.getLocation())) {
				// we found our signal
				row = idx;
				break;
			}
		}

		return row;
	}

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {
		if (sid == StreamID.CAPABILITIES) {
			CapabilitiesEvent cap = (CapabilitiesEvent) item;
			refresh((DeviceCapabilities) cap.getCapabilities());
		} else if (sid == StreamID.CONNECTION) {
			ConnectionItem conn = (ConnectionItem) item;
			cti.handleConnectionEvent(conf, driver, conn.getStatus());
		} else if (sid == StreamID.ALARM) {
			// ignore
		} else if (sid == StreamID.ANNOTATION) {
			// ignore
		} else if (sid == StreamID.DISPLAY) {
			// ignore
		} else {
			// one of our data streams?
			RpMetric[] metrics = item.getMetrics();
			if (metrics == null) {
				log.error("NO METRICS FOR EVENT: " + sid);
			} else {
				JTable table = getTableForStream(sid);
				if (table == null) {
					log.warn("no table for stream: {}", sid);

					addModelTab(sid.getName(), null, sid, Arrays.asList(metrics));
					table = getTableForStream(sid);
				}

				updateStreamDisplay(table, item);
			}
		}
	}

	@Override
	public void propertyChange(PropertyChangeEvent arg0) {
		String name = arg0.getPropertyName();
		if (CtApiMCCUL.CT_FREQ.equals(name)) {
			JTable table = getTableForStream(StreamID.WAVEFORM);
			DefaultTableModel model = (DefaultTableModel) table.getModel();
			String freq = (String) arg0.getNewValue();
			for (int row = 0; row < model.getRowCount(); row++) {
				model.setValueAt(freq, row, COL_FREQ);
			}
		}
		if (CtApiMCCUL.CT_FIRSTCH.equals(name) || CtApiMCCUL.CT_LASTCH.equals(name)) {
			JTable table = getTableForStream(StreamID.WAVEFORM);
			CtApiMCCUL cp = (CtApiMCCUL) arg0.getSource();
			int firstch = ((CtApiMCCUL) cp).getFirstChannel();
			int lastch = ((CtApiMCCUL) cp).getLastChannel();
			DefaultTableModel model = (DefaultTableModel) table.getModel();
			String freq = (String) arg0.getNewValue();
			for (int row = 0; row < model.getRowCount(); row++) {
				model.setValueAt(row >= firstch && row <= lastch, row, COL_ENABLED);
			}
		}
	}

}
