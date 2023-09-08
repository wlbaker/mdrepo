/*
 * Created by JFormDesigner on Fri Jul 23 16:16:40 CDT 2010
 */

package idea.tsoffline.canvas;

import java.awt.Color;
import java.awt.Component;
import java.awt.event.ActionEvent;
import java.util.Comparator;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.Set;
import java.util.TreeSet;

import javax.swing.AbstractCellEditor;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import javax.swing.event.TableModelEvent;
import javax.swing.event.TableModelListener;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableCellEditor;
import javax.swing.table.TableCellRenderer;
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
import idea.gui.WizardMasterInterface;
import idea.gui.WizardPanelInterface;
import idea.tsoffline.AppModel;
import idea.tsoffline.ColorManager;
import idea.tsoffline.HPSplitableLayer;
import idea.tsoffline.TimeseriesType;
import idea.tsoffline.model.FormulaOp;
import idea.tsoffline.model.FormulaSignal;

class MmixedRenderer extends JLabel implements TableCellRenderer {
	LinkedList<TableCellRenderer> rendererList = new LinkedList<TableCellRenderer>();
	LinkedList<Class<?>> rendererType = new LinkedList<Class<?>>();

	public MmixedRenderer() {
		setOpaque(true);
		setHorizontalAlignment(LEFT);
		setVerticalAlignment(CENTER);
	}

	public Component getTableCellRendererComponent(JTable table, Object value, boolean isSelected, boolean hasFocus,
			int row, int column) {
		Class cl = null;
		TableCellRenderer rn = null;

		if (value != null) {
			Iterator<TableCellRenderer> rnii = rendererList.iterator();
			Iterator<Class<?>> clii = rendererType.iterator();
			while (clii.hasNext()) {
				cl = clii.next();
				TableCellRenderer t_rn = rnii.next();

				if (cl.isAssignableFrom(value.getClass())) {
					rn = t_rn;
					break;
				}
			}
		}

		Component result;
		if (rn == null) {
			// rn = defaultRenderer;
			result = (Component) value;
		} else {

			result = rn.getTableCellRendererComponent(table, value, isSelected, hasFocus, row, column);

			// need this value from table, not model
			// boolean editable = table.isCellEditable(row, column);
		}

		return result;
	}

	public void addRenderer(Class<?> cl, TableCellRenderer r) {
		if (r != null) {
			// ??
			rendererList.addFirst(r);
			rendererType.addFirst(cl);
		}
	}

}

@SuppressWarnings("serial")
class FormulaCellEditor extends AbstractCellEditor implements TableCellEditor {

	SimpleFormulaEditorPanel editor;

	public FormulaCellEditor() {
		this(null);
	}

	public FormulaCellEditor(Set<HPSplitableLayer> sigs) {
		super();
		editor = new SimpleFormulaEditorPanel(sigs);
	}

	public void setSignals(Set<HPSplitableLayer> sigs) {
		editor.setSignals(sigs);
	}

	@Override
	public Component getTableCellEditorComponent(JTable table, Object value, boolean isSelected, int row, int column) {

		editor.setFormula((FormulaSignal) value);
		return editor;
	}

	@Override
	public Object getCellEditorValue() {
		return editor.getFormulaSignal();
	}

}

/**
 * @author User #2
 */
@Slf4j
@SuppressWarnings("serial")
public class TimeseriesPropertiesPanel extends JPanel
		implements ListSelectionListener, TableModelListener, WizardPanelInterface {
	private static final int OBJECT_COL = 0;
	private static final int LOC_COL = 1;
	private static final int ALIAS_COL = 2;
	private static final int VIS_COL = 3;
	private static final int COLOR_COL = 4;
	private static final int DETAIL_COL = 5;
	private TsPSwingCanvas canvas;
	private WizardMasterInterface wiz;
	Set<HPSplitableLayer> sorted_sigs;
	private MmixedRenderer mixedRenderer;
	private FormulaCellEditor formulaEditor;

	// FIXME: Put somewhere else!!!

	public TimeseriesPropertiesPanel(TsPSwingCanvas canvas) {
		createTable1();
		initComponents();

		table1.getSelectionModel().addListSelectionListener(this);
		delete.setEnabled(false);
		duplicate.setEnabled(false);

		this.canvas = canvas;

		initTable();
		refresh();
	}

	private void createTable1() {
		table1 = new JTable() {

			@Override
			public boolean isCellEditable(int row, int column) {

				boolean editable = super.isCellEditable(row, column);
				if (column == DETAIL_COL) {
					Object val = table1.getValueAt(row, column);
					editable = val instanceof FormulaSignal;
				}
				return editable;
			}

		};

	}

	public TimeseriesPropertiesPanel(WizardMasterInterface wiz) {
		this((TsPSwingCanvas) null);
		this.wiz = wiz;

		ok.setEnabled(false);
		ok.setVisible(false);
		cancel.setEnabled(false);
		cancel.setVisible(false);
	}

	private void initTable() {
		final DefaultTableModel model = (DefaultTableModel) table1.getModel();

		model.addTableModelListener(this);

		TableColumn col = table1.getColumnModel().getColumn(COLOR_COL);
		GuiUtil.initColorColumn(col, ColorManager.getColors());

		// mixedRenderer = new MixedRenderer();
		// mixedRenderer.addRenderer(Component.class, null);
		// mixedRenderer.addRenderer(String.class,
		// table1.getDefaultRenderer(Object.class));

		TableColumn detail_col = table1.getColumnModel().getColumn(DETAIL_COL);
		// detail_col.setCellRenderer( mixedRenderer );
		formulaEditor = new FormulaCellEditor();
		detail_col.setCellEditor(formulaEditor);
	}

	@Override
	public void refresh() {
		DefaultTableModel model = (DefaultTableModel) table1.getModel();
		model.setRowCount(0);

		sorted_sigs = new TreeSet<HPSplitableLayer>(new Comparator<HPSplitableLayer>() {

			@Override
			public int compare(HPSplitableLayer o1, HPSplitableLayer o2) {
				Integer i1 = o1.getLayerSeq();
				Integer i2 = o2.getLayerSeq();

				int comp = i1.compareTo(i2);
				if (comp == 0) {
					String n1 = o1.getAlias();
					String n2 = o2.getAlias();
					comp = n1.compareTo(n2);
				}
				return comp;
			}
		});

		for (HPSplitableLayer layer : canvas.getSigs() ) {
			sorted_sigs.add(layer);
		}

		for (HPSplitableLayer layer : canvas.getAnnotationModel() ) {
			sorted_sigs.add(layer);
		}

//		for (PCamera cam : canvas.getBandCameras()) {
//			List<PLayer> layers = cam.getLayersReference();
//			for (PLayer layer : layers) {
//
//				HPSplitableLayer sig = (HPSplitableLayer) layer;
//				sorted_sigs.add(sig);
//			}
//		}

		for (HPSplitableLayer layer : sorted_sigs) {

			String name = layer.getAlias();

			boolean vis = false;
			if (layer != null) {
				vis = layer.getVisible();
			}

			Object detail = "?";

			switch (layer.getTyp()) {
			case TT_ANNOTATION:
				detail = "Annotation";
				String src = layer.getSource();
				if (src != null) {
					detail += ": " + src;
				}
				break;
			case TT_DATA:
				detail = "Data";
				break;
			case TT_TRACE:
				detail = "Trace";
				break;
			case TT_FORMULA:

				FormulaSignal f = (FormulaSignal) layer.getAttribute("sig");
				detail = f;
				break;
			case TT_SCRIPT:
				detail = "Advanced Formula";
				break;
			default:
				break;

			}
			String code = layer.getCode();
			if (code == null) {
				code = layer.getLocation();
			}
			model.addRow(new Object[] { layer, code, name, vis, layer.getDefaultColor(), detail });
		}

		formulaEditor.setSignals(sorted_sigs);
	}

	@Override
	public void valueChanged(ListSelectionEvent e) {
		if (e.getValueIsAdjusting()) {
			return;
		}

		int row = table1.getSelectedRow();
		if (row >= 0) {
			DefaultTableModel model = (DefaultTableModel) table1.getModel();
			boolean ena = false;
			Object o = model.getValueAt(row, OBJECT_COL);
			if (o != null) {
				ena = (o instanceof HPSplitableLayer);
			}
			delete.setEnabled(ena);
			duplicate.setEnabled(ena);
		}
	}

	private void apply() {
		if (table1.isEditing()) {
			TableCellEditor editor = table1.getCellEditor();
			editor.stopCellEditing(); // commit edited values
		}
		DefaultTableModel model = (DefaultTableModel) table1.getModel();
		for (int row = 0; row < model.getRowCount(); row++) {
			boolean vis = (Boolean) model.getValueAt(row, VIS_COL);
			Color color = (Color) model.getValueAt(row, COLOR_COL);

			Object o = model.getValueAt(row, OBJECT_COL);

			HPSplitableLayer sig = (HPSplitableLayer) o;
			if (sig == null) {
				// this happens with newly created formulas
				sig = (HPSplitableLayer) model.getValueAt(row, DETAIL_COL);
			}

			sig.setDefaultColor(color);
			if (canvas.getActiveLayer() == null) {
				log.warn("previously applied only to annotation layers");
				// color changes on annotations always happen immediately
				// color changes if not active layer...immediate
				sig.setPaint(color);
			}

			// this happens if you "fix" the names
			String alias = (String) model.getValueAt(row, ALIAS_COL);
			sig.setName(alias);

			if (sig.getTyp() == TimeseriesType.TT_FORMULA) {
				FormulaSignal formula = (FormulaSignal) model.getValueAt(row, DETAIL_COL);
				AppModel.createFormulaSignal(canvas, alias, color, formula);
			}
			sig.setVisible(vis);
			sig.setName(alias);

		}

	}

	private void okActionPerformed(ActionEvent e) {
		apply();
		cancelActionPerformed(null);
	}

	private void cancelActionPerformed(ActionEvent e) {
		GuiUtil.closeDialog(this);
	}

	private void deleteActionPerformed(ActionEvent e) {
		DefaultTableModel model = (DefaultTableModel) table1.getModel();
		int[] rows = table1.getSelectedRows();
		if (rows != null && rows.length > 0) {
			for (int idx = rows.length - 1; idx >= 0; idx--) {
				int row = rows[idx]; // we require decrementing values
				HPSplitableLayer sig = (HPSplitableLayer) model.getValueAt(row, OBJECT_COL);

				if (sig != null) {
					canvas.removeSignalLayer(sig);
					canvas.removeAnnotationLayer(sig.getLocation());
				}
			}

			refresh();
		}
	}

	private void resetLabelsActionPerformed(ActionEvent e) {
		int rows = table1.getRowCount();

		for (int row = 0; row < rows; row++) {
			Object o = table1.getValueAt(row, OBJECT_COL);
			String name = null;
			if (o instanceof HPSplitableLayer) {
				HPSplitableLayer sig = (HPSplitableLayer) o;
				name = sig.getLocation();
			} else if (o instanceof PLayer) {
				// this should no longer happen...obsolete
				PLayer layer = (PLayer) o;
				HPSplitableLayer sig = (HPSplitableLayer) layer.getAttribute("sig");
				name = sig.getLocation();
			} else {
				log.error("Unexpected object in table: {}", o);
			}

			String[][] translation = AppModel.getSubstitutionsModel();
			for (int tr = 0; tr < translation.length; tr++) {
				if (translation[tr][0].equals(name)) {
					name = translation[tr][1];
					if (name != null) {
						table1.setValueAt(name, row, ALIAS_COL);
					} else {
						table1.setValueAt(false, row, VIS_COL);
					}
					break;
				}
			}
		}
	}

	private void addSimpleFormulaActionPerformed(ActionEvent e) {
		DefaultTableModel model = (DefaultTableModel) table1.getModel();

		RpMetric bogus = new RpMetric();
		// Object detail = new SimpleFormulaEditorPanel(sorted_sigs);
		FormulaSignal f = new FormulaSignal(bogus);
		f.sig1 = null;
		f.sig2 = null;
		f.op = FormulaOp.Subtract;
		Object detail = f;
		model.addRow(new Object[] { null, "", "", true, Color.BLUE, detail });
	}

	private void createUIComponents() {
		// TODO: add custom component creation code here
	}

	private void applyActionPerformed(ActionEvent e) {
		// TODO add your code here
	}

	private void duplicateActionPerformed(ActionEvent e) {
		DefaultTableModel model = (DefaultTableModel) table1.getModel();
		int[] rows = table1.getSelectedRows();
		if (rows != null && rows.length > 0) {
			for (int idx = rows.length - 1; idx >= 0; idx--) {
				int row = rows[idx]; // we require decrementing values
				HPSplitableLayer sig = (HPSplitableLayer) model.getValueAt(row, OBJECT_COL);

				if (sig != null) {
					String dup_name = sig.getName() + " (dup)";

					RpMetric bogus = new RpMetric();
					bogus.setCode(sig.getName() + " code");
					FormulaSignal f = new FormulaSignal(bogus);
					f.setName(dup_name);
					f.sig1 = sig.getName();
					f.sig2 = null;
					f.op = FormulaOp.Duplicate;
					Object detail = f;
					model.addRow(new Object[] { f, f.getCode(), dup_name, true, Color.BLUE, detail });

				}
			}

			// refresh();
		}
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		createUIComponents();

		panel2 = new JPanel();
		scrollPane1 = new JScrollPane();
		panel3 = new JPanel();
		upButton = new JButton();
		downButton = new JButton();
		addFilter = new JButton();
		addSimpleFormula = new JButton();
		addAdvancedForumua = new JButton();
		duplicate = new JButton();
		delete = new JButton();
		panel1 = new JPanel();
		resetLabels = new JButton();
		apply = new JButton();
		ok = new JButton();
		cancel = new JButton();

		// ======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout("[450dlu,default]:grow", "fill:default:grow, $lgap, default"));

		// ======== panel2 ========
		{
			panel2.setLayout(new FormLayout("default:grow, $lcgap, default", "fill:default"));

			// ======== scrollPane1 ========
			{

				// ---- table1 ----
				table1.setModel(new DefaultTableModel(
						new Object[][] { { null, null, null, true, null, null },
								{ null, null, null, true, null, null }, },
						new String[] { "O", "Code", "Name", "Visible", "Color", "Details" }) {
					Class<?>[] columnTypes = new Class<?>[] { Object.class, Object.class, Object.class, Boolean.class,
							Object.class, Object.class };

					@Override
					public Class<?> getColumnClass(int columnIndex) {
						return columnTypes[columnIndex];
					}
				});
				{
					TableColumnModel cm = table1.getColumnModel();
					cm.getColumn(0).setMinWidth(1);
					cm.getColumn(0).setMaxWidth(1);
					cm.getColumn(0).setPreferredWidth(1);
					cm.getColumn(2).setPreferredWidth(150);
					cm.getColumn(3).setPreferredWidth(50);
					cm.getColumn(4).setPreferredWidth(40);
					cm.getColumn(5).setPreferredWidth(300);
				}
				scrollPane1.setViewportView(table1);
			}
			panel2.add(scrollPane1, CC.xy(1, 1));

			// ======== panel3 ========
			{
				panel3.setLayout(new FormLayout("[50dlu,default]",
						"2*(default, $lgap), $ugap, 3*($lgap, default), $lgap, 10dlu, 2*($lgap, default), $lgap, default:grow"));

				// ---- upButton ----
				upButton.setText("Up");
				upButton.setEnabled(false);
				panel3.add(upButton, CC.xy(1, 1));

				// ---- downButton ----
				downButton.setText("Down");
				downButton.setEnabled(false);
				panel3.add(downButton, CC.xy(1, 3));

				// ---- addFilter ----
				addFilter.setText("Add Filter");
				addFilter.setEnabled(false);
				panel3.add(addFilter, CC.xy(1, 7));

				// ---- addSimpleFormula ----
				addSimpleFormula.setText("Add Formula");
				addSimpleFormula.addActionListener(e -> addSimpleFormulaActionPerformed(e));
				panel3.add(addSimpleFormula, CC.xy(1, 9));

				// ---- addAdvancedForumua ----
				addAdvancedForumua.setText("Add Adv");
				addAdvancedForumua.setEnabled(false);
				panel3.add(addAdvancedForumua, CC.xy(1, 11));

				// ---- duplicate ----
				duplicate.setText("Duplicate");
				duplicate.addActionListener(e -> duplicateActionPerformed(e));
				panel3.add(duplicate, CC.xy(1, 15));

				// ---- delete ----
				delete.setText("Delete");
				delete.addActionListener(e -> deleteActionPerformed(e));
				panel3.add(delete, CC.xy(1, 17));
			}
			panel2.add(panel3, CC.xy(3, 1));
		}
		add(panel2, CC.xy(1, 1));

		// ======== panel1 ========
		{
			panel1.setLayout(new FormLayout("default, $lcgap, default:grow, 3*($lcgap, [50dlu,default])", "default"));

			// ---- resetLabels ----
			resetLabels.setText("Reset Labels");
			resetLabels.addActionListener(e -> resetLabelsActionPerformed(e));
			panel1.add(resetLabels, CC.xy(1, 1));

			// ---- apply ----
			apply.setText("Apply");
			apply.setEnabled(false);
			apply.addActionListener(e -> applyActionPerformed(e));
			panel1.add(apply, CC.xy(5, 1));

			// ---- ok ----
			ok.setText("Ok");
			ok.addActionListener(e -> okActionPerformed(e));
			panel1.add(ok, CC.xy(7, 1));

			// ---- cancel ----
			cancel.setText("Cancel");
			cancel.addActionListener(e -> cancelActionPerformed(e));
			panel1.add(cancel, CC.xy(9, 1));
		}
		add(panel1, CC.xy(1, 3));
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
	private JButton addFilter;
	private JButton addSimpleFormula;
	private JButton addAdvancedForumua;
	private JButton duplicate;
	private JButton delete;
	private JPanel panel1;
	private JButton resetLabels;
	private JButton apply;
	private JButton ok;
	private JButton cancel;
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
		PLayer layer = null;
		if (o == null) {
			// this happens when editing new column...no object yet
			// probably a formula
			return;
		} else if (o instanceof HPSplitableLayer) {
			HPSplitableLayer sig = (HPSplitableLayer) o;
			layer = sig;
		} else if (o instanceof PLayer) {
			// obsolete
			layer = (PLayer) o;
		} else {
			log.error("Unexpected object in table: {}", o);
		}

		if (col == VIS_COL) {
			if (layer != null) {
				layer.setVisible(vis);
			}
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
		apply();
	}

	@Override
	public boolean next() {
		apply();
		return true;
	}

	@Override
	public boolean finish() {
		apply();
		return true;
	}
}
