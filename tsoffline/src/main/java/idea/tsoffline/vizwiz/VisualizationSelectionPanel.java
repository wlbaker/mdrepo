/*
 * Created by JFormDesigner on Tue Jan 11 14:40:16 CST 2011
 */

package idea.tsoffline.vizwiz;

import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumnModel;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import idea.schema.rp.RpAnalysis;
import idea.analysis.AttractorAnalysisPanel;
import idea.gui.WizardMasterInterface;
import idea.gui.WizardPanelInterface;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class VisualizationSelectionPanel extends JPanel implements WizardPanelInterface, ListSelectionListener {

	private static final int OBJECT_COL = 0;
	private WizardMasterInterface wiz;

	public VisualizationSelectionPanel(WizardMasterInterface wiz ) {
		initComponents();
		setName("Analysis Selection");

		this.wiz = wiz;
		wiz.enableNext(false);
		wiz.enableFinish(false);

		initTable();
	}

	private void initTable() {
		DefaultTableModel model = (DefaultTableModel) table.getModel();
		model.setRowCount(0);

		RpAnalysis a = new RpAnalysis();
		a.setName("Standford Visualization");
		a.setAnalysisClass(AttractorAnalysisPanel.class.toString());
		model.addRow(new Object[] { a, a.getName() });

		a = new RpAnalysis();
		a.setName("Recurrence Plot");
		a.setAnalysisClass(AttractorAnalysisPanel.class.toString());
		model.addRow(new Object[] { a, a.getName() });

		table.getSelectionModel().addListSelectionListener(this);
	}

	@Override
	public void valueChanged(ListSelectionEvent e) {
		if (!e.getValueIsAdjusting()) {
			int row = e.getFirstIndex();
			boolean selected = (row >= 0);
			if (!selected) {
				wiz.enableNext(false);
				wiz.enableFinish(false);
			} else {

				Object o = table.getValueAt(row, OBJECT_COL);
				RpAnalysis a = (RpAnalysis) o;
				Class<?> setupClass = getSetupClass(a.getName());

				wiz.enableNext(setupClass != null);
				wiz.enableFinish(setupClass == null);
			}
		}
	}

	private Class<?> getSetupClass(String name) {
		Class<?> setupClass = null;

		if (name.equals("RRI")) {
			setupClass = null;
		}

		return setupClass;
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		scrollPane1 = new JScrollPane();
		table = new JTable();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setLayout(new FormLayout("default:grow", "default, $lgap, fill:default:grow, $lgap, default"));

		//======== scrollPane1 ========
		{

			//---- table ----
			table.setModel(new DefaultTableModel(new Object[][] { { null, null }, { null, null }, }, new String[] {
					"O", "Visualization" }) {
				boolean[] columnEditable = new boolean[] { false, false };

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
				cm.getColumn(1).setPreferredWidth(400);
			}
			scrollPane1.setViewportView(table);
		}
		add(scrollPane1, cc.xy(1, 3));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	private JScrollPane scrollPane1;
	private JTable table;
	private RpAnalysis selectedAnalysis;

	// JFormDesigner - End of variables declaration  //GEN-END:variables

	@Override
	public boolean finish() {

		RpAnalysis a = null;

		int row = table.getSelectedRow();
		if (row >= 0) {
			a = (RpAnalysis) table.getValueAt(row, OBJECT_COL);

		}
		selectedAnalysis = a;
		
		return true;
	}

	@Override
	public boolean next() {
		int row = table.getSelectedRow();

		RpAnalysis a = (RpAnalysis) table.getValueAt(row, OBJECT_COL);
		Class<?> setupClass = getSetupClass(a.getName());

		selectedAnalysis =a;

		return true;
	}

	@Override
	public void previous() {
		// TODO Auto-generated method stub

	}

	@Override
	public void refresh() {
		// TODO Auto-generated method stub

	}
}
