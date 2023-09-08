/*
 * Created by JFormDesigner on Fri Jan 14 08:21:46 CST 2011
 */

package idea.tsoffline.event_editor;

import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.util.Date;
import java.util.Enumeration;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.ListIterator;
import java.util.Map;
import java.util.Vector;

import javax.swing.JButton;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JPopupMenu;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumn;
import javax.swing.table.TableColumnModel;
import javax.swing.table.TableModel;

import org.piccolo2d.PLayer;
import org.piccolo2d.PNode;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.layout.FormLayout;

import idea.model.PersistentItem;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpUnit;
import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;
import idea.gui.ExcelAdapter;
import idea.gui.TableSorter;
import idea.ts.TsoAnnotationEntryType;
import idea.tsoffline.AppFrame;
import idea.tsoffline.AppModel;
import idea.tsoffline.HPSplitableLayer;
import idea.tsoffline.canvas.TsBaseCanvas;
import idea.tsoffline.model.DerivedUtil;

/**
 * @author User #2
 */
@Slf4j
@SuppressWarnings("serial")
public class FeatureListPanel extends JPanel {
	private HPSplitableLayer info;
	private TableSorter sorter;
	private static final int OBJ_COL = 0; // original object...not changed until
											// OK
	private static final int DT_COL = 1;
	private static final int RELTM_COL = 2;
	private static final int CODE_COL = 4;
	private static final int VAL_COL = 5;

	boolean intercepts = false;

	int[] col_widths;
	private TsBaseCanvas canvas;

	public FeatureListPanel(TsBaseCanvas canvas, HPSplitableLayer info, boolean editable, boolean intercepts) {
		initComponents();

		this.info = info;
		this.intercepts = intercepts;
		this.canvas = canvas;

		int n = table.getColumnCount();
		col_widths = new int[n];
		for (int i = 0; i < n; i++) {
			TableColumn col = table.getColumnModel().getColumn(i);
			col_widths[i] = col.getPreferredWidth();
		}

		populate();

		ExcelAdapter adapter = new ExcelAdapter(table);
		JMenuItem delete_item = new JMenuItem("Delete");
		delete_item.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				deleteSelectedRows();
			}
		});

		adapter.getPopupMenu().add(new JPopupMenu.Separator());
		adapter.getPopupMenu().add(delete_item);

		table.getSelectionModel().addListSelectionListener(new ListSelectionListener() {

			@Override
			public void valueChanged(ListSelectionEvent e) {
				if (e.getValueIsAdjusting()) { // TMI
					return;
				}
				int row = table.getSelectedRow();
				Date dt = null;
				if (row >= 0) {
					PNode node = (PNode) sorter.getValueAt(row, OBJ_COL);

					// a default value, that probably doesnt make any sense
					dt = (Date) new Date((long) (1000 * node.getX()));

					Object it = node.getAttribute("item");
					if (it instanceof PersistentItem) {
						PersistentItem item = (PersistentItem) it;
						dt = item.getTm();
					} else if (it instanceof TsoAnnotationEntryType) {
						TsoAnnotationEntryType item = (TsoAnnotationEntryType) it;
						dt = item.getTm();
					}
				}

				boolean editable = (row >= 0);

				edit.setEnabled(editable);
				delete.setEnabled(editable);

				putClientProperty("selected_dt", dt);
			}
		});

		importFeatures.setText("Import " + info.getName());

		create.setEnabled(true);
		edit.setEnabled(false); // not ready
		delete.setEnabled(false); // not ready

		create.setVisible(editable);
		edit.setVisible(editable);
		delete.setVisible(editable);
	}

	protected void deleteSelectedRows() {
		int[] rows = table.getSelectedRows();
		if (rows == null || rows.length == 0) {
			return;
		}

		PLayer layer = info;
		for (int idx = rows.length - 1; idx >= 0; idx--) {
			PNode node = (PNode) table.getValueAt(rows[idx], OBJ_COL);
			layer.removeChild(node);
		}

		populate();
	}

	private void initTable(TableModel model) {
		table.setAutoCreateColumnsFromModel(true);

		sorter = new TableSorter(model) {

			@Override
			public Class getColumnClass(int column) {

				if (column == DT_COL) {
					return Date.class;
				} else if (column == RELTM_COL) {
					return Double.class;
				}

				if (intercepts && column > CODE_COL) {
					return Double.class;
				}
				return super.getColumnClass(column);
			}

		};
		table.setAutoCreateColumnsFromModel(true);
		table.setModel(sorter);
		sorter.setTableHeader(table.getTableHeader());
	}

	public void formatTable() {

		DoubleCellRenderer dbl_renderer = new DoubleCellRenderer();
		DateCellRenderer dt_renderer = new DateCellRenderer("dd-MMM-yyyy HH:mm:ss");

		TableColumn zero = table.getColumnModel().getColumn(0);
		zero.setMinWidth(0);
		zero.setMaxWidth(0);

		for (int col_idx = 0; col_idx < table.getColumnCount(); col_idx++) {
			TableColumn col = table.getColumnModel().getColumn(col_idx);
			if (col_idx == DT_COL) {
				col.setCellRenderer(dt_renderer);
			} else if (col_idx == CODE_COL) {
				// ignore this col
			} else {
				col.setCellRenderer(dbl_renderer);
				col.setMinWidth(60);
			}

			if (col_idx < col_widths.length) {
				col.setPreferredWidth(col_widths[col_idx]);
			} else {
				// col.setPreferredWidth( 40 );
			}
		}

	}

	private void populate() {
		DefaultTableModel model = new DefaultTableModel(
				new String[] { "O", "Date", "Time (s)", "Seq", info.getName(), "Value" }, 0) {
			@Override
			public boolean isCellEditable(int rowIndex, int columnIndex) {
				return false;
			}

		};
		model.setRowCount(0);

		addAnnotations(model, info);
		// addFeatureInterceptInfo(model, info.getLayer(), info);

		if (intercepts) {
			populateIntercepts(model);
		}

		initTable(model);
		formatTable();
	}

	private void populateIntercepts(DefaultTableModel model) {
		for (HPSplitableLayer sig_data : canvas.getSigs()) {
			if (sig_data != null) {
				addFeatureInterceptInfo(model, sig_data);
			}
		}
	}

	/*
	 * RELTM_COL is the time of the R-wave, regardless of lead_lag
	 */

	public void populateSegmentedLayer(PNode layer, double lead_lag) {

		DefaultTableModel model = (DefaultTableModel) sorter.getTableModel();

		if (layer == null) {
			return;
		}

		@SuppressWarnings("unchecked")
		ListIterator<PNode> ii = layer.getChildrenIterator();
		PNode node = ii.next();

		outer: for (int next_row = 1; next_row < model.getRowCount(); next_row++) {
			int curr_row = next_row - 1;
			Double relTm = (Double) model.getValueAt(next_row, RELTM_COL);
			relTm += lead_lag;

			if (node.getX() > relTm) {
				continue;
			}

			do {
				populateAttributes(layer.getName(), model, curr_row, node);
				if (ii.hasNext() == false) {
					break outer;
				}
				node = ii.next();
			} while (node.getX() < relTm);
		}

	}

	private void populateAttributes(String layer_name, DefaultTableModel model, int curr_row, PNode node) {
		int dest_col;

		String code = (String) node.getAttribute("txt");
		if (code == null || code.length() == 0) {
			code = layer_name;
		}
		// int dest_col = findOrMakeColumn( model, code );
		// model.setValueAt(code, curr_row, dest_col);

		dest_col = findOrMakeColumn(model, code + "(tm)");
		model.setValueAt(node.getX(), curr_row, dest_col);

		dest_col = findOrMakeColumn(model, code);
		model.setValueAt(node.getY(), curr_row, dest_col);

		Enumeration ii = node.getClientPropertyKeysEnumeration();
		while (ii != null && ii.hasMoreElements()) {
			String key = (String) ii.nextElement();

			if ("txt".equals(key)) {
				continue;
			} else if ("item".equals(key)) {
				continue;
			} else if (key.startsWith("@")) {
				continue;
			}

			Object value = node.getAttribute(key);

			dest_col = findOrMakeColumn(model, key);
			model.setValueAt(value, curr_row, dest_col);

		}

	}

	private int findOrMakeColumn(DefaultTableModel model, String name) {
		for (int i = model.getColumnCount() - 1; i >= 0; i--) {
			String col_name = model.getColumnName(i);
			if (name.equals(col_name)) {
				return i;
			}
		}

		model.addColumn(name);

		return model.getColumnCount() - 1;
	}

	private void addAnnotations(DefaultTableModel model, HPSplitableLayer anno_layer) {

		int seq = 0;
		ListIterator<PNode> it = anno_layer.getChildrenIterator();
		while (it != null && it.hasNext()) {
			PNode node = it.next();
			double tm = node.getX();

			Date dt = null;
			Object item = node.getAttribute("item");
			if (item == null) {
				log.error("NO ITEM!!!!");
			} else if (item instanceof PersistentItem) {
				dt = ((PersistentItem) item).getTm();
			} else if (item instanceof TsoAnnotationEntryType) {
				dt = ((TsoAnnotationEntryType) item).getTm();
			}
			String message = (String) node.getAttribute("txt");

			Vector<Object> v = new Vector<Object>();
			v.add(node);
			v.add(dt);
			v.add(tm);
			v.add(++seq);

			if (message == null) {
				message = "?";
			}
			v.add(message);
			v.add(node.getY());

			Enumeration<?> keys = node.getClientPropertyKeysEnumeration();
			while (keys.hasMoreElements()) {
				String columnName = (String) keys.nextElement();
				if (columnName == null) {
					// ignore
					log.error("INTERNAL ERROR: null key name in node properties");
				} else if ("item".equals(columnName)) {
					// ignore
				} else if ("txt".equals(columnName)) {
					// ignore
				} else if (columnName.startsWith("@")) {
					// ignore
					System.out.println(columnName + "=" + node.getAttribute(columnName));
				} else {
					Object note = node.getAttribute(columnName);
					if (note instanceof double[]) {
						double[] arr = (double[]) note;
						int idx = 1;
						for (double d : arr) {
							addValueToVector(model, v, columnName + "[" + idx + "]", d);
							idx++;
						}

					} else if (note instanceof Map) {
						Map map = (Map) note;
						for (Object key : map.keySet()) {
							addValueToVector(model, v, columnName + "[" + key + "]", map.get(key));
						}
					} else {
						addValueToVector(model, v, columnName, note);
					}
				}
			}

			model.addRow(v);
		}
	}

	private void addValueToVector(DefaultTableModel model, Vector<Object> v, String columnName, Object note) {
		int col = model.findColumn(columnName);
		if (col < 0) {
			col = model.getColumnCount();
			model.addColumn(columnName);
		}
		while (v.size() <= col) {
			v.add(null);
		}
		v.set(col, note);
	}

	private void createActionPerformed(ActionEvent e) {
		Date start_dt = AppModel.getTimelineModel().getStartTime();

		TsoAnnotationEntryType it = new TsoAnnotationEntryType();
		it.setTm(start_dt); // an inital value
		it.setCode(info.getName());

		SingleEventPanel p = new SingleEventPanel(canvas, it);

		GuiUtil.doDialog("Create Event", AppFrame.getInstance(), p, null);

		if (p.isOk()) {
			AppModel.addAnnotation(info, it, true);
			populate();
		}
	}

	private void deleteActionPerformed(ActionEvent e) {
		int row = table.getSelectedRow();
		if (row >= 0) {
			int ok = GuiUtil.showConfirmDialog("Are you sure you want to delete item [" + row + "] ?", "Delete event",
					JOptionPane.OK_CANCEL_OPTION);
			if (ok == JOptionPane.OK_OPTION) {
				PNode node = (PNode) table.getValueAt(row, OBJ_COL);
				AppModel.removeAnnotation(info, node);
				populate();
			}
		}
	}

	private void editActionPerformed(ActionEvent e) {

		int row = table.getSelectedRow();
		Date dt = null;
		if (row >= 0) {
			PNode node = (PNode) table.getValueAt(row, OBJ_COL);
			TsoAnnotationEntryType it = (TsoAnnotationEntryType) node.getAttribute("item");

			SingleEventPanel p = new SingleEventPanel(canvas, it);

			GuiUtil.doDialog("Edit Event", AppFrame.getInstance(), p, null);
			if (p.isOk()) {
				info.addAttribute("modified", true);
				AppModel.setDirty(true);
				node.addAttribute("txt", it.getCode());
			}

			populate();
		}
	}

	private void addFeatureInterceptInfo(DefaultTableModel model, PLayer sig_layer) {

		// ListIterator<PNode> it = anno_layer.getChildrenIterator();
		// while (it != null && it.hasNext()) {
		// PNode node = it.next();
		RpMetric sig = (RpMetric) sig_layer.getAttribute("sig");

		int col = model.getColumnCount();
		model.addColumn(sig.getAlias());

		List<PNode> nodes = sig_layer.getChildrenReference();
		Iterator<PNode> iit = nodes.iterator();
		if (iit.hasNext() == false) {
			return;
		}

		RpUnit unit = null;
		if (sig != null) {
			unit = sig.getUnit();
		}

		PNode next = iit.next();
		PNode prev = null;
		for (int row = 0; row < model.getRowCount(); row++) {

			PNode fiducial_node = (PNode) model.getValueAt(row, OBJ_COL);
			double tm = fiducial_node.getX();

			PNode layer_node = null;
			if (next == null) {

			} else {
				do {
					// System.out.println(sig.getAlias() + " row=" + row + "
					// search starting at node=" + next.getX() );

					double x = next.getX();
					if (x > tm) {
						layer_node = prev;
						break;
					}
					prev = next;
					next = iit.hasNext() ? iit.next() : null;
				} while (next != null);
			}

			// Double data_y = DerivedUtil.getValueAtPoint(sig_layer, nodes,
			// tm);
			Double data_y = DerivedUtil.getValueAtPoint(layer_node, tm, unit);
			// System.out.println(sig.getAlias() + " row=" + row + " tm=" + tm +
			// " data_y=" + data_y );
			model.setValueAt(data_y, row, col);
		}

	}

	private void importFeaturesActionPerformed(ActionEvent e) {
		try {
			_importAnnotationsActionPerformed();
		} catch (IOException e1) {
			GuiUtil.showError("Importing Annotations", e1);
		}
	}

	private void _importAnnotationsActionPerformed() throws IOException {
		List<HPSplitableLayer> annos = canvas.getAnnotationModel();

		GuiUtil.showMessage("FIXME Feature Importer not ready...");

		// TableSorter sorter = (TableSorter) table.getModel();
		// DefaultTableModel model = (DefaultTableModel)sorter.getTableModel();
		// while ((item = (Annotation) anno.next()) != null) {
		// addOneRowToModel(model, null, sevt);
		// }

		// if OK, add them to the existing annotation set
		LinkedList<PLayer> new_features = null; // AppModel.getAnnotationModel();
		if (new_features == null) {
			return; // no annotations
		}

		// and sort
		// Collections.sort(features);
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		scrollPane1 = new JScrollPane();
		table = new JTable();
		panel1 = new JPanel();
		importFeatures = new JButton();
		create = new JButton();
		edit = new JButton();
		delete = new JButton();

		// ======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout("default:grow", "fill:default:grow, $lgap, default"));

		// ======== scrollPane1 ========
		{
			scrollPane1.setPreferredSize(new Dimension(854, 439));

			// ---- table ----
			table.setModel(new DefaultTableModel(
					new Object[][] { { null, null, null, null, null }, { null, null, null, null, null }, },
					new String[] { null, "Date", "Time", "Seq", "Description" }) {
				Class<?>[] columnTypes = new Class<?>[] { Object.class, Date.class, Double.class, Integer.class,
						Object.class };
				boolean[] columnEditable = new boolean[] { false, false, false, false, false };

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
				TableColumnModel cm = table.getColumnModel();
				cm.getColumn(0).setResizable(false);
				cm.getColumn(0).setMinWidth(1);
				cm.getColumn(0).setMaxWidth(1);
				cm.getColumn(0).setPreferredWidth(1);
				cm.getColumn(1).setPreferredWidth(140);
				cm.getColumn(2).setPreferredWidth(80);
				cm.getColumn(4).setPreferredWidth(300);
			}
			table.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
			scrollPane1.setViewportView(table);
		}
		add(scrollPane1, CC.xy(1, 1));

		// ======== panel1 ========
		{
			panel1.setLayout(new FormLayout("default, $lcgap, default:grow, 3*($lcgap, [40dlu,default])", "default"));

			// ---- importFeatures ----
			importFeatures.setText("Import Features");
			importFeatures.addActionListener(e -> importFeaturesActionPerformed(e));
			panel1.add(importFeatures, CC.xy(1, 1));

			// ---- create ----
			create.setText("New");
			create.addActionListener(e -> createActionPerformed(e));
			panel1.add(create, CC.xy(5, 1));

			// ---- edit ----
			edit.setText("Edit");
			edit.addActionListener(e -> editActionPerformed(e));
			panel1.add(edit, CC.xy(7, 1));

			// ---- delete ----
			delete.setText("Delete");
			delete.addActionListener(e -> deleteActionPerformed(e));
			panel1.add(delete, CC.xy(9, 1));
		}
		add(panel1, CC.xy(1, 3));
		// JFormDesigner - End of component initialization
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JScrollPane scrollPane1;
	private JTable table;
	private JPanel panel1;
	private JButton importFeatures;
	private JButton create;
	private JButton edit;
	private JButton delete;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	public int getRowCount() {
		return table.getRowCount();
	}
}
