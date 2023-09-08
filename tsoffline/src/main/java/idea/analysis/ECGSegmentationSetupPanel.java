/*
 * Created by JFormDesigner on Mon Jun 03 14:14:22 CDT 2019
 */

package idea.analysis;

import java.util.Map;

import javax.swing.DefaultComboBoxModel;
import javax.swing.JComboBox;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumnModel;

import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.factories.DefaultComponentFactory;
import com.jgoodies.forms.layout.FormLayout;

import idea.message.StreamID;
import idea.schema.rp.RpAnalysis;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpStudy;
import lombok.extern.slf4j.Slf4j;
import idea.ConfigurationInfo;
import idea.gui.WizardMasterInterface;
import idea.gui.WizardPanelInterface;
import idea.tsoffline.AppFrame;
import idea.tsoffline.HPSplitableLayer;
import idea.tsoffline.TimeseriesType;
import idea.tsoffline.canvas.TsPSwingCanvas;

/**
 * @author WILLIAM BAKER
 */
@Slf4j
public class ECGSegmentationSetupPanel extends JPanel implements WizardPanelInterface {
	private static final int OBJECT_COL = 0;
	private static final int DESCRIPTION_COL = 1;

	private RpAnalysis analysis;

	public ECGSegmentationSetupPanel(WizardMasterInterface intf, RpStudy study, RpAnalysis anal) {
		initComponents();

		this.analysis = anal;

		algorithm.setModel(new DefaultComboBoxModel(ConfigurationInfo.getDetectorList()));

		refresh();
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		separator1 = compFactory.createSeparator("Method");
		panel1 = new JPanel();
		label1 = new JLabel();
		algorithm = new JComboBox();
		separator2 = compFactory.createSeparator("Signal");
		panel2 = new JPanel();
		scrollPane1 = new JScrollPane();
		table1 = new JTable();

		// ======== this ========
		setLayout(new FormLayout("default:grow", "3*(default, $lgap), fill:default:grow"));
		add(separator1, CC.xy(1, 1));

		// ======== panel1 ========
		{
			panel1.setLayout(new FormLayout("[20dlu,min], $lcgap, default, $lcgap, [100dlu,default]", "default"));

			// ---- label1 ----
			label1.setText("Algorithm:");
			panel1.add(label1, CC.xy(3, 1));
			panel1.add(algorithm, CC.xy(5, 1));
		}
		add(panel1, CC.xy(1, 3));
		add(separator2, CC.xy(1, 5));

		// ======== panel2 ========
		{
			panel2.setLayout(new FormLayout("[20dlu,default], $lcgap, default:grow", "default:grow"));

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
					cm.getColumn(0).setResizable(false);
					cm.getColumn(0).setMinWidth(1);
					cm.getColumn(0).setMaxWidth(1);
					cm.getColumn(0).setPreferredWidth(1);
					cm.getColumn(1).setPreferredWidth(300);
				}
				scrollPane1.setViewportView(table1);
			}
			panel2.add(scrollPane1, CC.xy(3, 1));
		}
		add(panel2, CC.xy(1, 7));
		// JFormDesigner - End of component initialization //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY //GEN-BEGIN:variables
	private JComponent separator1;
	private JPanel panel1;
	private JLabel label1;
	private JComboBox algorithm;
	private JComponent separator2;
	private JPanel panel2;
	private JScrollPane scrollPane1;
	private JTable table1;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	private boolean save() {
		int row = table1.getSelectedRow();
		if (row < 0) {
			return false;
		}

		HPSplitableLayer sig = (HPSplitableLayer) table1.getValueAt(row, OBJECT_COL);

		Map<String, String> params = analysis.getParam();
		saveParam(params, "stream", StreamID.WAVEFORM.getName());

		saveParam(params, "loc", sig.getLocation());
		saveParam(params, "code", sig.getCode());
		saveParam(params, "detector", algorithm.getSelectedItem());

		return true;
	}

	private void saveParam(Map<String, String> params, String key, Object wrapper) {
		String value = null;
		if (wrapper instanceof WfWrapper) {
			WfWrapper w = (WfWrapper) wrapper;
			RpMetric wave = w.getWave();
			value = wave.getLocation();
		} else if (wrapper instanceof DevWrapper) {
			DevWrapper w = (DevWrapper) wrapper;
			RpDevice dev = w.getDevice();
			value = dev.getName();
		} else {
			value = (String) wrapper; // should be a string...used for detection algorithm
		}

		params.put(key, value);
	}

	@Override
	public void refresh() {
		DefaultTableModel model = (DefaultTableModel) table1.getModel();
		model.setRowCount(0);

		TsPSwingCanvas canvas = AppFrame.getInstance().getCanvas();
		HPSplitableLayer[] sigs = canvas.getSigs();
		if (sigs != null) {
			for (HPSplitableLayer sig : sigs) {
				TimeseriesType typ = sig.getTyp();

				// add waveforms
				if (typ == TimeseriesType.TT_DATA || typ == TimeseriesType.TT_FORMULA) {
					String line = sig.getLocation();

					String name = sig.getName();
					if (name == null || name.length() == 0) {
						RpMetric m = sig.getMetric();
						name = m.getCode();
					}
					if (name != null) {
						line = line + ": " + name;
					}
					model.addRow(new Object[] { sig, line });
				}
			}
		}

	}

	@Override
	public void previous() {
		// nothing to do here
	}

	@Override
	public boolean next() {
		boolean ok = save();
		return ok;
	}

	@Override
	public boolean finish() {
		return next();
	}
}
