/*
 * Created by JFormDesigner on Tue Jul 28 12:10:36 CDT 2015
 */

package idea.display.editor;

import icuInterface.RpUtil;
import idea.display.BandLayout;
import idea.display.DisplayUtil;
import idea.display.InstrumentDisplayInterface;
import idea.display.WaveformData;
import idea.message.StreamID;
import idea.model.DisplayConfig;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpLinearUnit;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpStream;
import idea.schema.rp.RpUnit;

import java.awt.AlphaComposite;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics2D;
import java.awt.Insets;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.BufferedImage;
import java.util.Arrays;
import java.util.List;

import javax.swing.AbstractButton;
import javax.swing.BorderFactory;
import javax.swing.ButtonGroup;
import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.JToggleButton;
import javax.swing.UIManager;
import javax.swing.event.TableModelEvent;
import javax.swing.event.TableModelListener;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumn;
import javax.swing.table.TableColumnModel;

import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;
import idea.gui.RpMetricTableCellRenderer;

import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.layout.FormLayout;

class Stats {

	public static float max(float[] x) {
		float max = x[0];
		for (float v : x) {
			if (v > max) {
				max = v;
			}
		}
		return max;
	}

	public static float min(float[] pp) {
		float min = pp[0];
		for (int i = 1; i < pp.length; i++) {
			if (pp[i] < min) {
				min = pp[i];
			}
		}
		return min;
	}

}

/**
 * @author User #1
 */
@SuppressWarnings("serial")
@Slf4j
public class BandEditorPanel extends JPanel implements TableModelListener {
	protected static final int SETUP_COL = 0;
	private static final int METRIC_COL = 1;
	protected static final int VIS_COL = 2;
	private static final int MAX_COL = 3;
	private static final int MIN_COL = 4;
	private static final int COLOR_COL = 5;

	private InstrumentDisplayInterface form;
	private DisplayConfig display;
	private JToggleButton[] bandSelector = new JToggleButton[8];

	private List<RpMetric> metrics;
	private BandLayout current_band;

	public BandEditorPanel(InstrumentDisplayInterface form) {

		this.form = form;
		initComponents();

		display = form.getDisplay();
		RpDevice conf = form.getCapabilities();

		RpStream stream = RpUtil.getStream(conf, StreamID.WAVEFORM);
		if (stream == null) {
			return;
		}
		metrics = stream.getMetric();
		if (metrics == null) {
			return;
		}

		this.setBackground(Color.DARK_GRAY);

		ButtonGroup group = new ButtonGroup();
		for (int idx = 0; idx < bandSelector.length; idx++) {
			String t = "Band " + (idx + 1);

			JToggleButton button = createBandSelectorLabel(t, idx);
			button.setBounds(0, 70 * idx, 20, 70);
			bandSelectorPanel.add(button);
			bandSelector[idx] = button;
			group.add(button);
		}
		bandSelector[0].setSelected(true);

		bandNameLabel.setText("");

		initTable();
	}

	private void initTable() {
		TableColumn col = table1.getColumnModel().getColumn(COLOR_COL);
		GuiUtil.initColorColumn(col, DisplayUtil.getColors());

		col = table1.getColumnModel().getColumn(METRIC_COL);
		col.setCellRenderer(new RpMetricTableCellRenderer());

		DefaultTableModel model = (DefaultTableModel) table1.getModel();
		model.addTableModelListener(this);

	}

	public void refresh() {
		display = form.getDisplay();
		List<BandLayout> bands = display.getBands();

		if (bands != null) {
			int idx = 0;
			for (JToggleButton toggle : bandSelector) {
				toggle.setVisible(idx < bands.size());
				if (idx == 0) {
					toggle.setSelected(true);
					displaySelectedBandData(0);
				}
				idx++;
			}
		}

	}

	private void displaySelectedBandData(int idx) {

		List<BandLayout> bands = display.getBands();

		if (bands != null) {
			if (idx < 0) {
				current_band = null;
				bandNameLabel.setText("[NONE]");
			} else {
				current_band = bands.get(idx);
				bandNameLabel.setText("Band " + (idx + 1));
			}

			refreshTable(current_band, metrics);
		}
	}

	// Create and set up a colored label.
	private JToggleButton createBandSelectorLabel(String t, int i) {
		Icon icon = textToIcon(t);
		JToggleButton button = new JToggleButton(icon);
		button.setVerticalAlignment(JLabel.CENTER);
		button.setHorizontalAlignment(JLabel.CENTER);
		button.setOpaque(true);
		button.putClientProperty("BAND_IDX", i);
		// label.setForeground(Color.black);
		button.setBorder(BorderFactory.createLineBorder(Color.black));

		button.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				AbstractButton btn = (AbstractButton) e.getSource();
				Integer idx = (Integer) btn.getClientProperty("BAND_IDX");
				displaySelectedBandData(idx);
			}
		});

		return button;
	}

	private Icon textToIcon(String text) {
		BufferedImage buffImage = new BufferedImage(20, 50, BufferedImage.TYPE_INT_ARGB);

		Graphics2D g2 = buffImage.createGraphics();

		// clear
		g2.setComposite(AlphaComposite.getInstance(AlphaComposite.CLEAR));
		g2.fillRect(0, 0, 256, 256);

		// reset composite
		g2.setComposite(AlphaComposite.getInstance(AlphaComposite.SRC_OVER));
		// draw
		// g2.setPaint(Color.RED);
		// g2.setFont(new Font("Serif", Font.PLAIN, 13));
		g2.setFont(UIManager.getDefaults().getFont("TabbedPane.font"));
		g2.setColor(Color.white);
		g2.rotate(Math.PI / 2);
		g2.drawString(text, 4, -4);
		g2.dispose();

		ImageIcon icon = new ImageIcon(buffImage);
		return icon;
	}

	private void refreshTable(BandLayout band, List<RpMetric> metrics) {

		if (table1.isEditing())
			table1.getCellEditor().stopCellEditing();

		DefaultTableModel model = (DefaultTableModel) table1.getModel();
		model.setRowCount(0);

		if (band == null || metrics == null) {
			return;
		}

		for (RpMetric metric : metrics) {

			WaveformData wave = DisplayUtil.getBandSignal(band, metric);
			if (wave == null) {
				model.addRow(new Object[] { wave, metric, false, null, null, null });
			} else {
				RpUnit unit = metric.getUnit();
				if (unit == null) {
					unit = RpLinearUnit.unit;
				}
				model.addRow(new Object[] { wave, metric, //
						true, // vis
						unit.transform(wave.getRangeMax()), // max
						unit.transform(wave.getRangeMin()), // max
						DisplayUtil.getColorFromDrager(wave.getWaveColor()) } //
				);
			}
		}

	}

	@Override
	public void tableChanged(TableModelEvent tme) {
		if (tme.getType() == TableModelEvent.UPDATE) {
			int row_num = tme.getFirstRow();
			int col_num = tme.getColumn();
			Object val = table1.getValueAt(row_num, col_num);

			RpMetric metric = (RpMetric) table1.getValueAt(row_num, METRIC_COL);
			if (metric == null) {
				log.error("cannot update null metric");
				return;
			}
			WaveformData wave = (WaveformData) table1.getValueAt(row_num, SETUP_COL);

			if (col_num == COLOR_COL) {
				if (wave != null) {
					Color color = (Color) val;
					wave.setWaveColor(DisplayUtil.getDragerFromColor(color));
					System.err.println("DEBUG WAVE=" + System.identityHashCode(wave) + " COLOR=" + color);
				}
			} else if (col_num == VIS_COL) {
				Boolean vis = (Boolean) val;

				if (vis) {
					WaveformData setup = buildWaveformSetup(metric);
					Color color = (Color) table1.getValueAt(row_num, COLOR_COL);
					setup.setWaveColor(DisplayUtil.getDragerFromColor(color));

					table1.setValueAt(setup, row_num, SETUP_COL); // triggers a
																	// recursive
																	// call
					current_band.addWaveform(setup);
				} else {
					current_band.removeWaveform(metric.getLocation());
				}
				form.setDisplay(display, true, true);
			} else if (col_num == MAX_COL || col_num == MIN_COL) {
				RpUnit unit = metric.getUnit();
				if (unit == null) {
					unit = RpLinearUnit.unit;
				}
				Double d = (Double) table1.getValueAt(row_num, col_num);
				if (d != null && wave != null) {
					short sval = (short) unit.inverse(d);
					System.out.println("MINMAX UNIT=" + unit + " INVERSE: " + sval);
					if (col_num == MAX_COL)
						wave.setRangeMax(sval);
					if (col_num == MIN_COL)
						wave.setRangeMin(sval);
				}
			}
		}
	}

	private WaveformData buildWaveformSetup(RpMetric metric) {
		WaveformData wf = new WaveformData();
		wf.setLoc(metric.getLocation());
		wf.setWaveColor((byte) 4);
		wf.setRangeMin((short) -200);
		wf.setRangeMax((short) 200);
		wf.setWaveSampleRate((short) 100);
		return wf;
	}

	private void resizeActionPerformed(ActionEvent e) {

		DefaultTableModel model = (DefaultTableModel) table1.getModel();

		float[] arr = new float[10000];
		for (int row = 0; row < model.getRowCount(); row++) {
			boolean vis = (Boolean) model.getValueAt(row, VIS_COL);
			if (!vis) {
				continue;
			}
			RpMetric m = (RpMetric) model.getValueAt(row, METRIC_COL);
			if (m == null) {
				log.error("Unexpected null metric.");
				continue;
			}
			form.getDisplayData(m.getLocation(), arr);

			double max = Stats.max(arr);
			double min = Stats.min(arr);

			RpUnit unit = m.getUnit(); // convert to user units
			if (unit != null) {
				max = unit.transform((int) max);
				min = unit.transform((int) min);
			}
			if (max == min) {
				max++;
				min--;
			}

			double range = max - min;
			double margin = 0.15 * range;

			model.setValueAt(max + margin, row, MAX_COL);
			model.setValueAt(min - margin, row, MIN_COL);
		}
		// form.setDisplay(display);
	}

	private void removeBandActionPerformed(ActionEvent e) {
		display.getBands().remove(current_band);
		refresh();
		displaySelectedBandData(0);
		form.setDisplay(display, true, true);
	}

	private void insertBandActionPerformed(ActionEvent e) {
		display.addBand(new BandLayout((byte) 0, (byte) 0));
		int idx = display.getNumBands();
		refresh();
		displaySelectedBandData(idx - 1);
		form.setDisplay(display, true, true);
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		panel1 = new JPanel();
		label1 = new JLabel();
		bandNameLabel = new JLabel();
		resize = new JButton();
		insertBand = new JButton();
		removeBand = new JButton();
		bandSelectorPanel = new JPanel();
		scrollPane1 = new JScrollPane();
		table1 = new JTable();

		// ======== this ========
		setLayout(new FormLayout("default:grow, $lcgap, 20px",
				"default, $lgap, default, $rgap, default, $lgap, fill:default:grow"));

		// ======== panel1 ========
		{
			panel1.setLayout(new FormLayout("default, $lcgap, default:grow, 2*($lcgap, default), default", "default"));

			// ---- label1 ----
			label1.setText("  Editing:");
			panel1.add(label1, CC.xy(1, 1));

			// ---- bandNameLabel ----
			bandNameLabel.setText("text");
			panel1.add(bandNameLabel, CC.xy(3, 1));

			// ---- resize ----
			resize.setToolTipText("Resize waveforms to fit the display.");
			resize.setIcon(new ImageIcon(getClass().getResource("/idea/image/select_all.png")));
			resize.setMaximumSize(new Dimension(32, 32));
			resize.setMinimumSize(new Dimension(32, 32));
			resize.setPreferredSize(new Dimension(32, 32));
			resize.addActionListener(e -> resizeActionPerformed(e));
			panel1.add(resize, CC.xy(5, 1));

			// ---- insertBand ----
			insertBand.setToolTipText("Insert a new waveform band");
			insertBand.setIcon(new ImageIcon(getClass().getResource("/idea/image/process_add.png")));
			insertBand.setMaximumSize(new Dimension(32, 32));
			insertBand.setMinimumSize(new Dimension(32, 32));
			insertBand.setPreferredSize(new Dimension(32, 32));
			insertBand.addActionListener(e -> insertBandActionPerformed(e));
			panel1.add(insertBand, CC.xy(7, 1));

			// ---- removeBand ----
			removeBand.setToolTipText("Delete current waveform band");
			removeBand.setIcon(new ImageIcon(getClass().getResource("/idea/image/process_remove.png")));
			removeBand.setMaximumSize(new Dimension(32, 32));
			removeBand.setMinimumSize(new Dimension(32, 32));
			removeBand.setPreferredSize(new Dimension(32, 32));
			removeBand.addActionListener(e -> removeBandActionPerformed(e));
			panel1.add(removeBand, CC.xy(8, 1));
		}
		add(panel1, CC.xy(1, 3));

		// ======== bandSelectorPanel ========
		{
			bandSelectorPanel.setLayout(null);

			{ // compute preferred size
				Dimension preferredSize = new Dimension();
				for (int i = 0; i < bandSelectorPanel.getComponentCount(); i++) {
					Rectangle bounds = bandSelectorPanel.getComponent(i).getBounds();
					preferredSize.width = Math.max(bounds.x + bounds.width, preferredSize.width);
					preferredSize.height = Math.max(bounds.y + bounds.height, preferredSize.height);
				}
				Insets insets = bandSelectorPanel.getInsets();
				preferredSize.width += insets.right;
				preferredSize.height += insets.bottom;
				bandSelectorPanel.setMinimumSize(preferredSize);
				bandSelectorPanel.setPreferredSize(preferredSize);
			}
		}
		add(bandSelectorPanel, CC.xy(3, 7));

		// ======== scrollPane1 ========
		{
			scrollPane1.setPreferredSize(new Dimension(150, 40));

			// ---- table1 ----
			table1.setModel(new DefaultTableModel(
					new Object[][] { { null, null, true, null, null, null }, { null, null, true, null, null, null }, },
					new String[] { "O", "Sig", "Vis", "Max", "Min", "Color" }) {
				Class<?>[] columnTypes = new Class<?>[] { Object.class, Object.class, Boolean.class, Double.class,
						Double.class, Object.class };
				boolean[] columnEditable = new boolean[] { false, false, true, true, true, true };

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
				cm.getColumn(0).setResizable(false);
				cm.getColumn(0).setMinWidth(1);
				cm.getColumn(0).setMaxWidth(1);
				cm.getColumn(0).setPreferredWidth(1);
				cm.getColumn(2).setPreferredWidth(26);
				cm.getColumn(3).setPreferredWidth(50);
				cm.getColumn(4).setPreferredWidth(50);
				cm.getColumn(5).setPreferredWidth(40);
			}
			scrollPane1.setViewportView(table1);
		}
		add(scrollPane1, CC.xy(1, 7));
		// JFormDesigner - End of component initialization
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JPanel panel1;
	private JLabel label1;
	private JLabel bandNameLabel;
	private JButton resize;
	private JButton insertBand;
	private JButton removeBand;
	private JPanel bandSelectorPanel;
	private JScrollPane scrollPane1;
	private JTable table1;
	// JFormDesigner - End of variables declaration //GEN-END:variables
}
