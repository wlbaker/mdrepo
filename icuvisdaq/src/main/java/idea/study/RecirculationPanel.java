/*
 * Created by JFormDesigner on Mon Dec 24 13:25:53 CST 2012
 */

package idea.study;

import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.schema.rp.RpAnalysis;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpMetric;

import java.awt.Dimension;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumnModel;

import lombok.extern.slf4j.Slf4j;
import idea.analysis.AnalysisPanelInterface;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

/**
 * @author User #1
 */
@SuppressWarnings("serial")
@Slf4j
public class RecirculationPanel extends JPanel implements StreamConsumer,
		AnalysisPanelInterface {

	private static final int LOC_COLUMN = 0;
	private static final int TM_COLUMN = 1;
	private static final int VAL_COLUMN = 3;

	private static final long MAX_AGE_MS = 5000;

	public RecirculationPanel(StreamProducer[] drivers,
			RpAnalysis anal) {
		initComponents();

		ImageIcon image = new ImageIcon(getClass().getResource(
				"/idea/study/RecirculationCircuitry.png"));

		imageArea.setIcon(image);
		imageArea.setBorder(null);

		refresh();

		wire(drivers);
	}

	private void wire(StreamProducer[] drivers) {
		for (StreamProducer d : drivers) {
			RpDevice conf = d.getConfiguration();
			String name = conf.getName();
			log.error("PROCESSING DRIVER: {}", name);
			if (name.startsWith("VIT")) {
				d.addStreamListener(StreamID.MEASUREMENT, this);
			} else if (name.startsWith("Hemolung")) {
				d.addStreamListener(StreamID.MEASUREMENT, this);
			}
		}
	}

	private void refresh() {
		DefaultTableModel model = (DefaultTableModel) table1.getModel();
		model.setRowCount(0);
		Long zero = 0L;
		model.addRow(new Object[] { "BF", zero, "BF", "0" });
		model.addRow(new Object[] { "MTR", zero, "rpm", "0" });
		model.addRow(new Object[] { "O", zero, "DF", "???" });
		model.addRow(new Object[] { "ra_p1", zero, "[1] Press INLET", "0" });
		model.addRow(new Object[] { "rv_p2", zero, "[2] Press PreML", "0" });
		model.addRow(new Object[] { "la_p3", zero, "[3] Press PostML", "0" });
		model.addRow(new Object[] { "lv_p4", zero, "[4] Press OUTLET", "0" });
		model.addRow(new Object[] { "gp1_p5", zero, "[5] Press DIA Pre", "0" });
		model.addRow(new Object[] { "gp2_p6", zero, "[6] Press DIA Post", "0" });
	}

	public StreamProducer[] getSignalProducers() {
		log.error("NOTHING LOGGED!");
		return null;
	}

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {
		if (sid == StreamID.MEASUREMENT) {
			processNumericBlock(item);
		}
	}

	private void processNumericBlock(PersistentItem block) {
		DefaultTableModel model = (DefaultTableModel) table1.getModel();
		long tm = block.getTime();

		for (int row = 0; row < model.getRowCount(); row++) {
			String loc = (String) model.getValueAt(row, LOC_COLUMN);

			RpMetric item = block.getMetric(loc);
			if (item == null) {
				Long last = (Long) model.getValueAt(row, TM_COLUMN);
				if (last instanceof Long && tm - last > MAX_AGE_MS) {
					model.setValueAt("-", row, VAL_COLUMN);
				}
			} else {
				Number val = (Number)IntfUtil.getScaledValue(block, item);
				if (val != null) {
					val = val.intValue();
				}
				model.setValueAt(val, row, VAL_COLUMN);
				model.setValueAt(tm, row, TM_COLUMN);
			}
		}

	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		imageArea = new JButton();
		scrollPane1 = new JScrollPane();
		table1 = new JTable();
		CellConstraints cc = new CellConstraints();

		// ======== this ========
		setLayout(new FormLayout("[450dlu,default]:grow",
				"fill:[200dlu,default], $lgap, fill:[110dlu,default]:grow, $lgap, default"));

		// ---- imageArea ----
		imageArea.setBorder(null);
		add(imageArea, cc.xy(1, 1));

		// ======== scrollPane1 ========
		{
			scrollPane1.setPreferredSize(new Dimension(200, 23));

			// ---- table1 ----
			table1.setModel(new DefaultTableModel(new Object[][] {
					{ null, null, "", null }, { null, null, null, null },
					{ null, null, null, null }, }, new String[] { "O", "tm",
					"Name", "Value" }) {
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
				cm.getColumn(1).setResizable(false);
				cm.getColumn(1).setMinWidth(1);
				cm.getColumn(1).setMaxWidth(1);
				cm.getColumn(1).setPreferredWidth(1);
				cm.getColumn(2).setResizable(false);
				cm.getColumn(2).setPreferredWidth(100);
				cm.getColumn(3).setResizable(false);
				cm.getColumn(3).setPreferredWidth(100);
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
	private JButton imageArea;
	private JScrollPane scrollPane1;
	private JTable table1;

	// JFormDesigner - End of variables declaration //GEN-END:variables

	@Override
	public void clear() {
		// TODO Auto-generated method stub

	}

	@Override
	public void autoscale() {
		// TODO Auto-generated method stub

	}

	@Override
	public void tick() {
		DefaultTableModel model = (DefaultTableModel) table1.getModel();
		long tm = System.currentTimeMillis();

		for (int row = 0; row < model.getRowCount(); row++) {
			Long last = (Long) model.getValueAt(row, TM_COLUMN);
			if (last instanceof Long && tm - last > MAX_AGE_MS) {
				model.setValueAt("-", row, VAL_COLUMN);
			}
		}
	}

}
