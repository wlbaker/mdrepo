/*
 * Created by JFormDesigner on Fri Jul 23 16:16:40 CDT 2010
 */

package idea.tsoffline.wiz;

import java.util.Enumeration;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.TreeSet;

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

import org.piccolo2d.PNode;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.layout.FormLayout;

import idea.message.StreamID;
import lombok.Getter;
import lombok.Setter;
import lombok.extern.slf4j.Slf4j;
import idea.gui.WizardMasterInterface;
import idea.gui.WizardPanelInterface;
import idea.tsoffline.AppUtil;
import idea.tsoffline.TimeseriesType;
import idea.tsoffline.model.OfflineSignal;

/**
 * @author User #2
 */
@Slf4j
@SuppressWarnings("serial")
public class FeatureSelectionPanel extends JPanel implements ListSelectionListener, WizardPanelInterface {
	private static final int OBJECT_COL = 0;
	private static final int NAME_COL = 1;

	private WizardMasterInterface wiz;
	OfflineSignal marker_sig = null;
	String key = "selection";

	@Getter
	@Setter
	private boolean multiLineSelect = true;

	public FeatureSelectionPanel(WizardMasterInterface wiz, List<String> opts) {
		initComponents();
		table1.getSelectionModel().addListSelectionListener(this);
		this.wiz = wiz;


		userMessage.setText("");
		if (opts != null) {
			Iterator<String> it = opts.iterator();
			it.next(); // ignore SIGNAL
			while (it.hasNext()) {
				String tok = it.next();
				if( marker_sig == null ) {
					marker_sig = (OfflineSignal) AppUtil.getParam("SIGNAL", tok );
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
		boolean has_selection = (multiLineSelect) ? (selectedCount > 0) : (selectedCount == 1);

		wiz.enableNext(has_selection);

	}

	@Override
	public void refresh() {

		DefaultTableModel model = (DefaultTableModel) table1.getModel();
		model.setRowCount(0);
		
		if( marker_sig == null ) {
			return;
		}

		Iterator<PNode> it = marker_sig.getNodes().iterator();
		Object last_selected = AppUtil.getParam("FEATURE", key);
		int selected_idx = -1;

		TreeSet<String> tree = new TreeSet<>();
		
		while ( it.hasNext() ) {
			PNode node = it.next();
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

				if( tree.contains( key)) {
					// ignore
				} else {
					tree.add(key);
					Object value = node.getAttribute(key);
					if( value instanceof Map ) {
						Map map = (Map)value;
						for( Object key2 : map.keySet() ) {
							String ent = "{" + key + "}/" + key2;
							model.addRow( new Object[] { ent, ent} );
						}
					} else {
						model.addRow( new Object[] { key, key} );
					}
				}

			}
		}

		wiz.enableNext(false); // until something is selected
		if (selected_idx >= 0) {
			table1.setRowSelectionInterval(selected_idx, selected_idx);
		}

	}

	private StreamID getSID(OfflineSignal sig) {
		StreamID sid = null;
		if (sig.getTyp() == TimeseriesType.TT_ANNOTATION) {
			sid = StreamID.MEASUREMENT;
		} else if (sig.getTyp() == TimeseriesType.TT_DATA) {
			sid = StreamID.WAVEFORM;
		} else if (sig.getTyp() == TimeseriesType.TT_FORMULA) {
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
	// JFormDesigner - End of variables declaration //GEN-END:variables

	@Override
	public void previous() {
	}

	@Override
	public boolean next() {
		String[] sigs = getSelectedFeatures();
		if (sigs == null) {
			// fail
		} else if (multiLineSelect == false) {
			AppUtil.setParam("FEATURE", key, sigs[0]);
		} else {
			AppUtil.setParam("FEATURE", key, sigs);
		}
		return (sigs != null);
	}

	@Override
	public boolean finish() {
		return next();
	}

	public String[] getSelectedFeatures() {
		int[] rows = table1.getSelectedRows();
		if (rows == null || rows.length == 0) {
			return null;
		}
		String[] features = new String[rows.length];
		int idx = 0;
		for (int row : rows) {
			features[idx++] = (String) table1.getValueAt(row, OBJECT_COL);
		}
		return features;
	}


}
