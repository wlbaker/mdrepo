/*
 * Created by JFormDesigner on Sun Feb 28 12:37:54 CST 2010
 */

package idea.tsoffline.importwiz;

import java.awt.Component;
import java.awt.Dimension;
import java.io.File;
import java.io.IOException;

import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.SwingConstants;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import javax.swing.table.DefaultTableCellRenderer;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableCellRenderer;
import javax.swing.table.TableColumnModel;
import javax.swing.table.TableModel;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.PiDatastreamImporter;
import idea.persistence.PiSubjectImporter;
import idea.persistmanager.PiImporterUtil;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpSubject;
import idea.GuiUtil;
import idea.gui.WizardPanelInterface;
import idea.meddaq.AppSetup;

/**
 * @author User #2
 */

class MyRenderer extends JLabel implements TableCellRenderer {
	   public Component getTableCellRendererComponent(JTable table,
	      Object value, boolean isSelected, boolean hasFocus, int row,
	      int col) {
	      DefaultTableCellRenderer renderer =
	         new DefaultTableCellRenderer();
	      Component c = renderer.getTableCellRendererComponent(table,
	         value, isSelected, hasFocus, row, col);
	      String s = "";
	      if (value instanceof RpMetric) {
	         RpMetric m = (RpMetric)value;
	         s = m.getAlias();
	         c = renderer.getTableCellRendererComponent(table, s,
	            isSelected, hasFocus, row, col);
	         ((JLabel) c).setHorizontalAlignment(SwingConstants.RIGHT);
	      }
	      return c;
	   }
	}

@SuppressWarnings("serial")
public class SignalSelectionPanel extends JPanel implements WizardPanelInterface, ListSelectionListener {

	private static final int OBJECT_COL = 0;

	public SignalSelectionPanel() {
		initComponents();
		setName("Study Selection");

		table1.setDefaultRenderer(RpMetric.class,new MyRenderer());
		table1.getSelectionModel().addListSelectionListener(this);
		refresh();

		ImportWizard wiz = ImportWizard.getInstance();
		wiz.enableFinish(true);
		wiz.enableNext(false);

	}

	@Override
	public void refresh() {

		DefaultTableModel model = (DefaultTableModel) table1.getModel();

		model.setRowCount(0);

		ImportWizard wizard = ImportWizard.getInstance();

		File f = wizard.getImportFile();
		try {
			PiSubjectImporter importer = PiImporterUtil.getImporterFromFile(f);
			importer.connect();
			PiDatastreamImporter[] devs = importer.getDevices();
			for (PiDatastreamImporter dev : devs) {
				_addOneDevice(model, dev);
			}
			importer.disconnect();
		} catch (IOException e) {
			GuiUtil.showError("Importer Error", e);
		}
	}

	private void _addOneDevice(DefaultTableModel model, PiDatastreamImporter dev) {
		for (StreamID sid : dev.getStreams()) {
			Class<? extends PersistentItem> clazz = dev.getModel(sid);
			RpMetric[] metrics = IntfUtil.getMetrics(clazz);
			if (metrics != null) {
				for (RpMetric metric : metrics) {
					model.addRow(new Object[] { metric, false, dev.getName(), metric.getName() });
				}
			}
		}

	}

	public int getProfileCount() {
		DefaultTableModel model = (DefaultTableModel) table1.getModel();
		return model.getRowCount();
	}

	public void clearSelectedProfile() {
		table1.clearSelection();
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		scrollPane1 = new JScrollPane();
		table1 = new JTable();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setLayout(new FormLayout("default:grow", "default, $lgap, fill:default:grow, $lgap, default"));

		//======== scrollPane1 ========
		{
			scrollPane1.setPreferredSize(new Dimension(454, 223));

			//---- table1 ----
			table1.setModel(new DefaultTableModel(new Object[][] { { null, true, null, null }, }, new String[] { "O",
					"Select", "Device", "Signal Name" }) {
				Class<?>[] columnTypes = new Class<?>[] { Object.class, Boolean.class, Object.class, Object.class };
				boolean[] columnEditable = new boolean[] { false, true, false, false };

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
				cm.getColumn(1).setPreferredWidth(100);
				cm.getColumn(2).setPreferredWidth(100);
				cm.getColumn(3).setPreferredWidth(300);
			}
			scrollPane1.setViewportView(table1);
		}
		add(scrollPane1, cc.xy(1, 3));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JScrollPane scrollPane1;
	private JTable table1;

	// JFormDesigner - End of variables declaration //GEN-END:variables

	@Override
	public boolean finish() {

		ImportWizard wizard = ImportWizard.getInstance();
		wizard.enableFinish(false);
		wizard.enableNext(false);

		return true;
	}

	@Override
	public boolean next() {
		boolean ok = false;
		try {
			ImportWizard wizard = ImportWizard.getInstance();

			RpSubject header = new RpSubject();
			wizard.setStudyHeader(header);
			AppSetup.setRpSubject(header);
			GuiUtil.showMessage("INTERNAL ERROR: wizard.pushPage(new DeviceConnectionPanel());");
			ok = true;
		} catch (Exception ex) {
			GuiUtil.showError("Study Selection", ex);
		}
		return ok;

	}

	@Override
	public void valueChanged(ListSelectionEvent e) {
		TableModel model = table1.getModel();

		int count = 0;
		for (int row = 0; row < model.getRowCount(); row++) {
			Boolean selected = (Boolean) model.getValueAt(row, 1);
			if (selected) {
				count++;
			}
		}
		ImportWizard wizard = ImportWizard.getInstance();
		wizard.enableFinish(count > 0);

	}

	@Override
	public void previous() {
		// TODO Auto-generated method stub

	}
}
