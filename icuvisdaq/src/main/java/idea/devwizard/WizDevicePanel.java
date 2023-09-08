/*
 * Created by JFormDesigner on Tue Oct 06 08:32:44 CDT 2009
 */

package idea.devwizard;

import java.awt.Dimension;
import java.lang.reflect.Constructor;
import java.util.List;

import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumnModel;

import org.pistax.PistaDriver;

import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.layout.FormLayout;

import idea.schema.rp.RpDevice;
import idea.schema.rp.RpHardware;
import idea.GuiUtil;
import idea.gui.WizardMasterInterface;
import idea.gui.WizardPanelInterface;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class WizDevicePanel extends JPanel implements WizardPanelInterface, ListSelectionListener {
	private static final int COL_WIZDAT = 0;
	private static final int COL_WIZCL = 1;
	private static final int COL_DEVNAME = 2;
	private SetupWizardInterface wizard;
	private RpHardware hw;

	public WizDevicePanel(SetupWizardInterface wizard, RpHardware hw) {
		setName("Device Selection");

		initComponents();
		this.wizard = wizard;
		this.hw = hw;

		GuiUtil.initTable(table, true);
		DefaultTableModel model = (DefaultTableModel) table.getModel();
		model.setRowCount(0);

		WizardPanelDatum[] ar = SetupData.getDevices();
		for (WizardPanelDatum datum : ar) {
			model.addRow(new Object[] { datum, "", datum.getName() });
		}

		table.getSelectionModel().addListSelectionListener(this);
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		scrollPane1 = new JScrollPane();
		table = new JTable();

		// ======== this ========
		setLayout(new FormLayout("[150dlu,default]:grow, $lcgap, default", "fill:default:grow, $lgap, default"));

		// ======== scrollPane1 ========
		{
			scrollPane1.setPreferredSize(new Dimension(252, 121));

			// ---- table ----
			table.setModel(new DefaultTableModel(new Object[][] { { null, null, null }, { null, null, null }, },
					new String[] { "O", null, "Device" }) {
				boolean[] columnEditable = new boolean[] { false, false, false };

				@Override
				public boolean isCellEditable(int rowIndex, int columnIndex) {
					return columnEditable[columnIndex];
				}
			});
			{
				TableColumnModel cm = table.getColumnModel();
				cm.getColumn(0).setResizable(false);
				cm.getColumn(0).setMinWidth(1);
				cm.getColumn(0).setMaxWidth(1);
				cm.getColumn(0).setPreferredWidth(1);
				cm.getColumn(1).setResizable(false);
				cm.getColumn(1).setMinWidth(1);
				cm.getColumn(1).setMaxWidth(1);
				cm.getColumn(1).setPreferredWidth(1);
				cm.getColumn(2).setPreferredWidth(260);
			}
			scrollPane1.setViewportView(table);
		}
		add(scrollPane1, CC.xy(1, 1));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JScrollPane scrollPane1;
	private JTable table;

	// JFormDesigner - End of variables declaration //GEN-END:variables

	@Override
	public boolean next() {
		String dev_name = null;
		Class<?> wiz_clazz = null;
		Class<?> dev_clazz = null;
		PistaDriver pista_driver = null;
		
		WizardPanelDatum wiz_datum = null;

		int idx = table.getSelectedRow();
		DefaultTableModel model = (DefaultTableModel) table.getModel();

		if (idx >= 0) {
			wiz_datum = (WizardPanelDatum) model.getValueAt(idx, COL_WIZDAT);
			dev_name = (String) model.getValueAt(idx, COL_DEVNAME);
			
			wiz_clazz = wiz_datum.getWizCl();
			dev_clazz = wiz_datum.getDevCl();
			pista_driver = wiz_datum.getPistaDriver();
		}
		

		if (wiz_clazz != null) {

			RpDevice dev = new RpDevice();
			dev.setDeviceClass(dev_clazz.getCanonicalName());
			dev.setName(dev_name);
			if( pista_driver != null ) {
				dev.setModelName(pista_driver.name() );
			}

			List<RpDevice> devs = hw.getDevices();
			devs.add(dev);

			// LOOK FOR ANOTHER COPY OF THIS AS PUSH_SELECTION
			try {
				Constructor<?> mid = wiz_clazz.getConstructor(WizardMasterInterface.class, RpDevice.class);
				Object[] args = new Object[] { wizard, dev };
				// args[0] = null;
				JPanel panel = (JPanel) mid.newInstance(args);
				panel.setName("Signal Selection");

				wizard.pushPage(panel);
			} catch (Exception ex) {
				throw new RuntimeException(ex);
			}

		}

		return true;
	}

	@Override
	public void refresh() {
		wizard.enableNext(false);
	}

	@Override
	public boolean finish() {
		return true;
	}

	@Override
	public void valueChanged(ListSelectionEvent e) {
		int row = table.getSelectedRow();

		wizard.enableNext(row >= 0);
	}

	@Override
	public void previous() {
		// TODO Auto-generated method stub

	}

}
