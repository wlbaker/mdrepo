/*
 * Created by JFormDesigner on Fri Jul 23 16:16:40 CDT 2010
 */

package idea.tsoffline.export;

import java.awt.Color;
import java.util.HashMap;
import java.util.LinkedList;

import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.event.TableModelEvent;
import javax.swing.event.TableModelListener;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumn;
import javax.swing.table.TableColumnModel;
import javax.swing.text.MutableAttributeSet;

import org.piccolo2d.PLayer;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.layout.FormLayout;

import idea.schema.rp.RpMetric;
import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;
import idea.gui.WizardPanelInterface;
import idea.tsoffline.AppModel;
import idea.tsoffline.ColorManager;
import idea.tsoffline.HPSplitableLayer;


/**
 * @author User #2
 */
@Slf4j
@SuppressWarnings("serial")
public class ExportRubalMethod extends JPanel implements TableModelListener, WizardPanelInterface {
	private static final int OBJECT_COL = 0;
	private static final int EXPORT_COL = 1;
	private static final int VIS_COL = 2;
	private static final int NAME_COL = 3;
	private static final int COLOR_COL = 4;

	public ExportRubalMethod() {
		initComponents();

		initTable();
		refresh();
	}

	private void initTable() {
		final DefaultTableModel model = (DefaultTableModel) table1.getModel();

		model.addTableModelListener(this);

		TableColumn col = table1.getColumnModel().getColumn(COLOR_COL);
		GuiUtil.initColorColumn(col, ColorManager.getColors());
	}

	@Override
	public void refresh() {
		DefaultTableModel model = (DefaultTableModel) table1.getModel();
		model.setRowCount(0);

		for (HPSplitableLayer sig : AppModel.getSignals()) {
			String name = sig.getName();
			if (name == null || name.length() == 0) {
				name = sig.getLocation();
			}

			model.addRow(new Object[] { sig, sig.getVisible(), sig.getVisible(), name, sig.getDefaultColor() });
		}

	}

	private void apply() {
		DefaultTableModel model = (DefaultTableModel) table1.getModel();
		for (int row = 0; row < model.getRowCount(); row++) {
			boolean vis = (Boolean) model.getValueAt(row, VIS_COL);
			String name = (String) model.getValueAt(row, NAME_COL);
			Color color = (Color) model.getValueAt(row, COLOR_COL);

			Object o = model.getValueAt(row, OBJECT_COL);
			if (o instanceof PLayer) {
				PLayer layer = (PLayer) o;

				RpMetric sig = (RpMetric) layer.getAttribute("sig");
				if (name == null || name.length() == 0) {
					name = sig.getLocation();
				}

				// ? anything to do?
			} else {
				// ??? AnnotationSignal info = (AnnotationSignal) o;

				// ? anything to do
				log.error("Unexpected data container: {}", o);
			}

		}

	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		panel2 = new JPanel();
		scrollPane1 = new JScrollPane();
		table1 = new JTable();
		panel3 = new JPanel();
		upButton = new JButton();
		downButton = new JButton();

		// ======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout("default:grow", "fill:default:grow"));

		// ======== panel2 ========
		{
			panel2.setLayout(new FormLayout("default:grow, $lcgap, default", "fill:default"));

			// ======== scrollPane1 ========
			{

				// ---- table1 ----
				table1.setModel(new DefaultTableModel(
						new Object[][] { { null, true, true, null, null }, { null, true, false, null, null }, },
						new String[] { "O", "Export", "Visible", "Label", "Color" }) {
					Class<?>[] columnTypes = new Class<?>[] { Object.class, Boolean.class, Boolean.class, Object.class,
							Object.class };
					boolean[] columnEditable = new boolean[] { true, true, false, false, false };

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
					cm.getColumn(1).setResizable(false);
					cm.getColumn(1).setPreferredWidth(50);
					cm.getColumn(2).setResizable(false);
					cm.getColumn(2).setPreferredWidth(50);
					cm.getColumn(3).setPreferredWidth(200);
					cm.getColumn(4).setPreferredWidth(80);
				}
				scrollPane1.setViewportView(table1);
			}
			panel2.add(scrollPane1, CC.xy(1, 1));

			// ======== panel3 ========
			{
				panel3.setLayout(new FormLayout("[50dlu,default]",
						"2*(default, $lgap), $ugap, 3*($lgap, default), $lgap, default:grow"));

				// ---- upButton ----
				upButton.setText("Up");
				upButton.setEnabled(false);
				panel3.add(upButton, CC.xy(1, 1));

				// ---- downButton ----
				downButton.setText("Down");
				downButton.setEnabled(false);
				panel3.add(downButton, CC.xy(1, 3));
			}
			panel2.add(panel3, CC.xy(3, 1));
		}
		add(panel2, CC.xy(1, 1));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JPanel panel2;
	private JScrollPane scrollPane1;
	private JTable table1;
	private JPanel panel3;
	private JButton upButton;
	private JButton downButton;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	@Override
	public void tableChanged(TableModelEvent tme) {

		// ignore inserts and deletes
		if (tme.getType() != TableModelEvent.UPDATE) {
			return;
		}
		DefaultTableModel model = (DefaultTableModel) tme.getSource();
		int row = tme.getFirstRow();
		int col = tme.getColumn();
		boolean vis = (boolean) model.getValueAt(row, VIS_COL);
		Color color = (Color) model.getValueAt(row, COLOR_COL);
		Object o = model.getValueAt(row, OBJECT_COL);
		PLayer layer = (PLayer) o;

		if (col == VIS_COL) {
			layer.setVisible(vis);
		}
		if (col == COLOR_COL) {
			MutableAttributeSet props = layer.getClientProperties();
			if (color != null) {
				props.addAttribute("color", color);
				layer.setPaint((Color) color);
			}
		}

	}

	@Override
	public void previous() {
		// TODO Auto-generated method stub

	}

	@Override
	public boolean next() {
		return true;
	}

	@Override
	public boolean finish() {
		// TODO Auto-generated method stub
		return false;
	}

	public HashMap<String, LinkedList<HPSplitableLayer>> getSignals() {
		HashMap<String, LinkedList<HPSplitableLayer>> signals = new HashMap<String, LinkedList<HPSplitableLayer>>();

		DefaultTableModel model = (DefaultTableModel) table1.getModel();
		for (int row = 0; row < model.getRowCount(); row++) {
			boolean exportFlag = (Boolean) model.getValueAt(row, EXPORT_COL);
			if (exportFlag == false) {
				continue;
			}
			Object o = model.getValueAt(row, OBJECT_COL);
			String devName = null;
			HPSplitableLayer sig = null;
			if (o instanceof HPSplitableLayer) {
				sig = (HPSplitableLayer) o;
				devName = (String) sig.getAttribute("dev_name");
			} else {
				log.error("Unknown signal type in export: {}", o.getClass());
			}

			if (sig != null) {
				LinkedList<HPSplitableLayer> list = signals.get(devName);
				if (list == null) {
					list = new LinkedList<HPSplitableLayer>();
					signals.put(devName, list);
				}
				list.add(sig);
			}
		}

		return signals;
	}

}
