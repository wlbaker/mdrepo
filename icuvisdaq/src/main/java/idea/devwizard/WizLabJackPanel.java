/*
 * Created by JFormDesigner on Mon Oct 05 13:52:41 CDT 2009
 */

package idea.devwizard;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
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

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import icuInterface.RpUtil;
import idea.conf.DeviceConfiguration;
import idea.driver.LabJackDriver;
import idea.intf.AdapterInterface;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.schema.rp.RpConnType;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpStream;
import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;
import idea.gui.ComboCellEditor;
import idea.gui.WizardMasterInterface;
import idea.gui.WizardPanelInterface;

/**
 * @author User #2
 */
@Slf4j
@SuppressWarnings("serial")
public class WizLabJackPanel extends JPanel implements WizardPanelInterface {

	private static final int COL_OBJ = 0;
	private static final int COL_ENABLED = 1;
	private static final int COL_PORT = 2;
	private static final int COL_SIGNAME = 3;
	private static final int COL_SIGTYPE = 4;

	String[] types = { "Waveform", "Numeric" };

	// private LabJackConfiguration dc;
	private RpDevice dev_conf;
	private WizardMasterInterface wizard;

	public WizLabJackPanel(WizardMasterInterface wizard, RpDevice dev_conf) {
		initComponents();

		this.wizard = wizard;
		this.dev_conf = dev_conf;

		GuiUtil.initTable(signalTable, true);

		initTable(signalTable);
		refresh();

	}

	private void initTable(JTable table) {

		// signalTable.setAutoCreateColumnsFromModel(false);
		// signalTable.setModel( new_model );

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
			_refresh();
		} catch (IOException e) {
			GuiUtil.showError("LabJack", e);
		}
	}

	public void _refresh() throws IOException {

		// TableModelFixer fixer = (TableModelFixer) signalTable.getModel();
		DefaultTableModel model = (DefaultTableModel) signalTable.getModel(); // fixer.getShadowedModel();
		model.setRowCount(0);

		AdapterInterface driver;
		driver = new LabJackDriver(null);

		DeviceConfiguration cap;
		cap = driver.getStaticCapabilities();
		// String[] ports = DaqSystem.getLocal().getPhysicalChannels();
		RpStream stream = IntfUtil.getStream( cap, StreamID.WAVEFORM);
		for (RpMetric desc : (List<? extends RpMetric>)stream.getMetric()) {
			boolean ena = false;
			model.addRow(new Object[] { desc, ena, desc.getName(), "", types[0] });
		}

		modelToPanel();
	}

	private void panelToModel() {

		RpUtil.resetDC(dev_conf);

		TableModel model = signalTable.getModel();

		dev_conf.setName("LabJack");
		dev_conf.setDriverName("LabJack");
		dev_conf.setDeviceClass(LabJackDriver.class.getCanonicalName());
		dev_conf.setConnectionType(RpConnType.NONE);

		List<? extends RpMetric> waves = RpUtil.getMetrics(dev_conf, StreamID.WAVEFORM);
		List<? extends RpMetric> metrics = RpUtil.getMetrics(dev_conf, StreamID.MEASUREMENT); // dev_conf.getMetrics();
		for (int row = 0; row < model.getRowCount(); row++) {
			RpMetric desc = (RpMetric) model.getValueAt(row, COL_OBJ);
			Boolean b = (Boolean) model.getValueAt(row, COL_ENABLED);
			String p = (String) model.getValueAt(row, COL_PORT);

			int dataRate = 500;
			if (b) {

				log.error("FIXME: do we want to support metrics here?");
				//if (desc instanceof WaveformDescription) {
					RpUtil.addMetric(dev_conf, StreamID.WAVEFORM, desc);
				//} else {
				//	RpUtil.addMetric(dev_conf, StreamID.MEASUREMENT, desc);
				//}

			}
		}

		return;
	}

	public void modelToPanel() {

		List<? extends RpMetric> waves = RpUtil.getMetrics(dev_conf, StreamID.WAVEFORM);
		if (waves != null) {

			DefaultTableModel model = (DefaultTableModel) signalTable.getModel();
			for (RpMetric wave : waves) {
				int row = findRow(model, wave.getLocation());
				if (row < 0) {
					// ??? what now
					log.error("COULD NOT FIND SIGNAL: ", wave.getLocation());
				} else {
					model.setValueAt(Boolean.TRUE, row, COL_ENABLED);
					model.setValueAt(wave.getName(), row, COL_SIGNAME);
					model.setValueAt(types[0], row, COL_SIGTYPE);
				}
			}
		}

		List<? extends RpMetric> metrics = RpUtil.getMetrics(dev_conf, StreamID.MEASUREMENT);
		if (metrics != null) {

			DefaultTableModel model = (DefaultTableModel) signalTable.getModel();
			for (RpMetric metric : metrics) {
				int row = findRow(model, metric.getLocation());
				if (row < 0) {
					// ??? what now
					System.err.println("COULD NOT FIND SIGNAL: " + metric.getLocation());
				} else {
					model.setValueAt(Boolean.TRUE, row, COL_ENABLED);
					model.setValueAt(metric.getName(), row, COL_SIGNAME);
					model.setValueAt(types[1], row, COL_SIGTYPE);
				}
			}
		}
	}

	private int findRow(DefaultTableModel model, Object location) {

		int row = -1;

		for (int idx = 0; idx < model.getRowCount(); idx++) {
			RpMetric wave = (RpMetric) model.getValueAt(idx, COL_OBJ);

			if (location.equals(wave.getLocation())) {
				// we found our signal
				row = idx;
				break;
			}
		}

		return row;
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		scrollPane1 = new JScrollPane();
		signalTable = new JTable();
		panel1 = new JPanel();
		label1 = new JLabel();
		sampleRate = new JComboBox();
		refresh = new JButton();
		CellConstraints cc = new CellConstraints();

		// ======== this ========
		setLayout(new FormLayout("[250dlu,default], $lcgap, default", "fill:default"));

		// ======== scrollPane1 ========
		{

			// ---- signalTable ----
			signalTable.setModel(new DefaultTableModel(new Object[][] { { null, true, null, null, null },
					{ null, null, null, null, null }, }, new String[] { null, "Enabled", "IO Point", "Signal Name",
					"Signal Type" }) {
				Class[] columnTypes = new Class[] { Object.class, Boolean.class, Object.class, Object.class,
						Object.class };
				boolean[] columnEditable = new boolean[] { false, true, false, true, true };

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
			scrollPane1.setViewportView(signalTable);
		}
		add(scrollPane1, cc.xy(1, 1));

		// ======== panel1 ========
		{
			panel1.setLayout(new FormLayout("default, $lcgap, default",
					"[12dlu,default], $lgap, default, $lgap, default:grow, $lgap, default"));

			// ---- label1 ----
			label1.setText("Sample Rate:");
			panel1.add(label1, cc.xy(1, 3));

			// ---- sampleRate ----
			sampleRate.setModel(new DefaultComboBoxModel(new String[] { "200", "500" }));
			sampleRate.setSelectedIndex(1);
			panel1.add(sampleRate, cc.xy(3, 3));

			// ---- refresh ----
			refresh.setText("Refresh");
			refresh.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					refreshActionPerformed(e);
				}
			});
			panel1.add(refresh, cc.xy(3, 7));
		}
		add(panel1, cc.xy(3, 1));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JScrollPane scrollPane1;
	private JTable signalTable;
	private JPanel panel1;
	private JLabel label1;
	private JComboBox sampleRate;
	private JButton refresh;

	// JFormDesigner - End of variables declaration //GEN-END:variables

	@Override
	public boolean next() {
		panelToModel(); // copy GUI information to model

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
