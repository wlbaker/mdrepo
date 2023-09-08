/*
 * Created by JFormDesigner on Fri Jul 23 16:16:40 CDT 2010
 */

package idea.tsoffline.wiz;

import java.util.Iterator;
import java.util.List;

import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.SwingConstants;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.JTableHeader;
import javax.swing.table.TableColumn;
import javax.swing.table.TableColumnModel;

import org.piccolo2d.PLayer;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.layout.FormLayout;

import idea.message.StreamID;
import idea.schema.rp.RpMetric;
import lombok.Getter;
import lombok.Setter;
import lombok.extern.slf4j.Slf4j;
import idea.gui.WizardMasterInterface;
import idea.gui.WizardPanelInterface;
import idea.tsoffline.AppUtil;
import idea.tsoffline.HPSplitableLayer;
import idea.tsoffline.TimeseriesType;
import idea.tsoffline.canvas.TsPSwingCanvas;

/**
 * @author User #2
 */
@Slf4j
@SuppressWarnings("serial")
public class SignalSelectionPanel extends JPanel implements ListSelectionListener, WizardPanelInterface {
	private static final int OBJECT_COL = 0;
	private static final int NAME_COL = 1;

	private WizardMasterInterface wiz;
	private StreamID sid;
	private RpMetric activeSig;
	String key = "selection";

	@Getter
	@Setter
	private boolean multiLineSelect;

	private boolean optional;

	public SignalSelectionPanel(WizardMasterInterface wiz, TsPSwingCanvas canvas, List<String> opts) {
		initComponents();

		table1.getSelectionModel().addListSelectionListener(this);

		this.wiz = wiz;
		this.canvas = canvas;

		userMessage.setText("");
		if (opts != null) {
			Iterator<String> it = opts.iterator();
			it.next(); // ignore SIGNAL
			while (it.hasNext()) {
				String tok = it.next();
				if (tok.equals("WAVEFORM")) {
					sid = StreamID.WAVEFORM;
				} else if (tok.equals("MEASUREMENT")) {
					sid = StreamID.MEASUREMENT;
				} else if (tok.equals("ANNOTATION")) {
					sid = StreamID.ANNOTATION;
				} else if (tok.equals("OPTIONAL")) {
					optional = true;
				} else if (tok.equals("MULTISELECT")) {
					multiLineSelect = true;
				} else {
					table1.setAutoCreateColumnsFromModel(false);

					// hmm...this isnt working...maybe substance l&f issue?
					JTableHeader th = table1.getTableHeader();
					TableColumnModel tcm = th.getColumnModel();
					TableColumn tc = tcm.getColumn(NAME_COL); // column 0 is
																// invisible
					tc.setHeaderValue(tok);
					th.repaint();
					userMessage.setText(tok);
					key = tok;
				}
			}
		}

		refresh();
	}

	@Override
	public void valueChanged(ListSelectionEvent e) {
		int selectedCount = table1.getSelectedRowCount();
		if (optional) {
			wiz.enableNext(true);
		} else {
			boolean has_selection = (multiLineSelect) ? (selectedCount > 0) : (selectedCount == 1);
			wiz.enableNext(has_selection);
		}

	}

	@Override
	public void refresh() {
		DefaultTableModel model = (DefaultTableModel) table1.getModel();
		model.setRowCount(0);

		if (optional) {
			model.addRow(new Object[] { null, "[None]" });
		}

		Object last_selected = AppUtil.getParam("SIGNAL", key);
		int selected_idx = -1;
		HPSplitableLayer[] data_layers = null;
		if( sid == StreamID.ANNOTATION ) {
			data_layers = canvas.getAnnotations();
			sid = null;
		} else {
			data_layers = canvas.getSigs();
		}
		for (HPSplitableLayer layer : data_layers) {
			if (layer == null) {
				continue; // only show data that has been loaded
			}

			RpMetric sig = layer.getMetric();
			String name = sig.getName();
			if (name == null || name.length() == 0) {
				name = sig.getLocation();
			}

			if (sid != null) {
				StreamID this_sid = getSID(layer.getTyp());
				if (this_sid != sid)
					continue;
			}

			model.addRow(new Object[] { layer, name });
			if (sig == activeSig) {
				selected_idx = model.getRowCount() - 1;
			}
			if (activeSig == null && sig == last_selected) {
				selected_idx = model.getRowCount() - 1;
			}
		}

		wiz.enableNext(false); // until something is selected
		if (selected_idx >= 0) {
			table1.setRowSelectionInterval(selected_idx, selected_idx);
		}

	}

	private StreamID getSID(TimeseriesType typ) {
		StreamID sid = null;
		if (typ == TimeseriesType.TT_ANNOTATION) {
			sid = StreamID.MEASUREMENT;
		} else if (typ == TimeseriesType.TT_DATA) {
			sid = StreamID.WAVEFORM;
		} else if (typ == TimeseriesType.TT_FORMULA) {
			sid = StreamID.WAVEFORM;
		}
		return sid;
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		panel2 = new JPanel();
		scrollPane1 = new JScrollPane();
		table1 = new JTable();
		userMessage = new JLabel();

		// ======== this ========
		setBorder(Borders.DLU2);
		setLayout(new FormLayout("default:grow", "fill:default:grow"));

		// ======== panel2 ========
		{
			panel2.setLayout(new FormLayout("default:grow, 8dlu", "fill:default:grow, $rgap, default"));

			// ======== scrollPane1 ========
			{

				// ---- table1 ----
				table1.setModel(new DefaultTableModel(new Object[][] { { null, null }, { null, null }, },
						new String[] { "O", "Signal" }) {
					boolean[] columnEditable = new boolean[] { false, false };

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
					cm.getColumn(1).setPreferredWidth(200);
				}
				scrollPane1.setViewportView(table1);
			}
			panel2.add(scrollPane1, CC.xy(1, 1));

			// ---- userMessage ----
			userMessage.setText("text");
			userMessage.setHorizontalAlignment(SwingConstants.TRAILING);
			panel2.add(userMessage, CC.xy(1, 3));
		}
		add(panel2, CC.xy(1, 1));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JPanel panel2;
	private JScrollPane scrollPane1;
	private JTable table1;
	private JLabel userMessage;
	private TsPSwingCanvas canvas;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	@Override
	public void previous() {
	}

	@Override
	public boolean next() {
		PLayer[] layers = getSelectedDataLayers();
		if (layers == null || layers.length == 0) {
			// fail
			if (optional) {
				return true;
			}
		} else if (multiLineSelect == false) {
			AppUtil.setParam("SIGNAL", key, layers[0]);
		} else {
			AppUtil.setParam("SIGNAL", key, layers);
		}
		return (layers != null);
	}

	@Override
	public boolean finish() {
		return next();
	}

	public PLayer[] getSelectedDataLayers() {
		int[] rows = table1.getSelectedRows();
		if (rows == null || rows.length == 0) {
			return null;
		}
		PLayer[] layers = new PLayer[rows.length];
		int idx = 0;
		for (int row : rows) {
			layers[idx++] = (PLayer) table1.getValueAt(row, OBJECT_COL);
		}
		return layers;
	}

	public void setSelectedSignal(RpMetric sig) {
		activeSig = sig;
		refresh();
	}

}
