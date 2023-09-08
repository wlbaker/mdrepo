/*
 * Created by JFormDesigner on Wed May 11 09:20:51 CDT 2011
 */

package idea.gui.wizard;

import java.io.IOException;
import java.util.Collection;
import java.util.LinkedList;
import java.util.List;

import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.ListSelectionModel;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumnModel;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import idea.schema.rp.RpConnType;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpHardware;
import idea.schema.rp.RpStudy;
import lombok.Data;
import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;
import idea.gui.WizardPanelInterface;
import idea.repository.RepositoryInterface;

/**
 * @author User #2
 */
@Slf4j
@SuppressWarnings("serial")
public class DeviceSelectionPanel extends JPanel implements
		WizardPanelInterface, ListSelectionListener {
	private static final int OBJECT_COL = 0;

	@Data
	public class DSR {
		RepositoryInterface repo;
		RpDevice device;
		String studyId;
		String devName;
		RpConnType connType;
		String connValue;
	}

	DSR rss = null;

	public DeviceSelectionPanel() {
		this(ListSelectionModel.SINGLE_SELECTION);
	}

	public DeviceSelectionPanel(int selectionType) {
		initComponents();

		refresh();

		ListSelectionModel selectionModel = table1.getSelectionModel();
		selectionModel.setSelectionMode(selectionType);
		selectionModel.addListSelectionListener(this);

	}

	@Override
	public void valueChanged(ListSelectionEvent e) {
		if (e.getValueIsAdjusting()) {
			// ignore
		} else {
			int rows = table1.getSelectedRowCount();

			// wizard.enableNext( rows > 0);
		}

	}

	public void refresh() {
		DefaultTableModel model = (DefaultTableModel) table1.getModel();
		model.setRowCount(0);
		
		log.error("FIXME: device registration not ready");
//		RepositoryInterface[] repos = RepositoryFactory.getRegisteredDevices();
//		for (RepositoryInterface repo : repos) {
//			try {
//				addRepoSubjects(model, repo);
//			} catch (Exception e) {
//				e.printStackTrace();
//			}
//		}
	}

	private void addRepoSubjects(DefaultTableModel model,
			RepositoryInterface repo) throws Exception {
		List<RpStudy> studies = repo.getStudyList(null);
		if (studies == null) {
			return;
		}

		for (RpStudy study : studies) {
			if (study == null) {
				continue;
			}
			List<RpHardware> hws = study.getHardware();
			RpHardware hw = hws.get(0);
			for (RpDevice dev : hw.getDevices()) {
				DSR rss = new DSR();
				rss.repo = repo;
				rss.device = dev;
				rss.studyId = study.getIdentifier();
				rss.devName = dev.getName();
				rss.connType = dev.getConnectionType();
				rss.connValue = dev.getConnectionValue();
				model.addRow(new Object[] { rss, repo.getName(), rss.devName });
			}
		}

	}

	@Override
	public boolean finish() {
		try {
			if (save()) {
				return true;
			}
		} catch (Exception e) {
			GuiUtil.showError("Error saving repository info", e);
		}
		return false;
	}

	@Override
	public boolean next() {

		boolean ok = false;
		try {
			ok = save();
		} catch (Exception e) {
			GuiUtil.showError("Error getting repository info", e);
		}

		return ok;
	}

	private boolean save() throws IOException {
		boolean ok = false;
		int sel = table1.getSelectedRow();

		if (sel >= 0) {
			DefaultTableModel model = (DefaultTableModel) table1.getModel();

			Object o = model.getValueAt(sel, OBJECT_COL);
			rss = (DSR) o;

			ok = true;
		}
		;

		return ok;
	}

	@Override
	public void previous() {
		// TODO Auto-generated method stub

	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		scrollPane1 = new JScrollPane();
		table1 = new JTable();
		CellConstraints cc = new CellConstraints();

		// ======== this ========
		setLayout(new FormLayout("default:grow",
				"default, $lgap, fill:default:grow, $lgap, default"));

		// ======== scrollPane1 ========
		{

			// ---- table1 ----
			table1.setModel(new DefaultTableModel(new Object[][] {
					{ null, null, null, null }, { null, null, null, null }, },
					new String[] { "O", "Area", "Device", "Date" }) {
				boolean[] columnEditable = new boolean[] { false, false, false,
						false };

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
				cm.getColumn(1).setPreferredWidth(120);
				cm.getColumn(2).setPreferredWidth(120);
				cm.getColumn(3).setPreferredWidth(80);
			}
			scrollPane1.setViewportView(table1);
		}
		add(scrollPane1, cc.xy(1, 3));
		// JFormDesigner - End of component initialization
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JScrollPane scrollPane1;
	private JTable table1;

	// JFormDesigner - End of variables declaration //GEN-END:variables

	public String getConnection() {

		return rss.device.getConnectionValue();
	}

	public Collection<DSR> getDevices() {
		List<DSR> s = null;

		int[] rows = table1.getSelectedRows();
		if (rows != null && rows.length > 0) {
			s = new LinkedList<DSR>();
			for (int row : rows) {
				DSR dsr = (DSR) table1.getValueAt(row, OBJECT_COL);
				s.add(dsr);
			}
		}

		return s;
	}
}
