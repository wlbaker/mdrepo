/*
 * Created by JFormDesigner on Thu Mar 18 15:01:05 CDT 2010
 */

package idea.adapters.gui;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Insets;
import java.awt.Rectangle;
import java.util.List;

import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import icuInterface.RpUtil;
import icuInterface.events.ConnectionItem;
import icuInterface.message.AbstractItem;
import icuInterface.message.NumericItem;
import idea.display.CardioStrip;
import idea.display.ChartRefresher;
import idea.display.simple.SingleValuePanel;
import idea.intf.DataTyp;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpStream;
import idea.schema.rp.RpUnit;

/**
 * @author User #2
 */
@Slf4j
@SuppressWarnings("serial")
public class VentilatorPanel extends JPanel implements StreamConsumer {

	int currHour = 0;
	private RpMetric paw_desc;
	private RpMetric flow_desc;
	private CardioStrip paw_strip;
	private CardioStrip flow_strip;
	private int[] volumeValues;

	private CircleGraph cgPAW;
	private CircleGraph cgFLOW;
	private int tot_volume;
	private ChartRefresher refresher;
	private SingleValuePanel[] valuePanels;
	private int verbose = 2;

	public VentilatorPanel(StreamProducer driver, RpDevice conf) {
		initComponents();

		RpStream stream = null;
		if (conf != null) {
			stream = RpUtil.getStream(conf, StreamID.WAVEFORM);
		}
		if (stream != null) {
			paw_desc = IntfUtil.getMetricByLoc(stream, "0x00");
			flow_desc = IntfUtil.getMetricByLoc(stream, "0x01");

			paw_strip = new CardioStrip();
			paw_strip.addWaveformDescription(paw_desc, Color.YELLOW, 1.0, 1.0, true);

			flow_strip = new CardioStrip();
			flow_strip.addWaveformDescription(flow_desc, Color.YELLOW, 1.0, 1.0, true);

			CellConstraints cc = new CellConstraints();
			panel1.add(paw_strip, cc.xy(3, 1));
			panel1.add(flow_strip, cc.xy(3, 3));
		}

		refresher = ChartRefresher.getInstance();
		refresher.addChart(paw_strip);
		refresher.addChart(flow_strip);

		stream = RpUtil.getStream(conf, StreamID.MEASUREMENT);
		if (stream != null) {
			JPanel metrics_panel = buildMetricsPanel(stream.getMetric());
			valuesContainer.add(metrics_panel, BorderLayout.CENTER);
		}
	}

	public JPanel buildMetricsPanel(List<RpMetric> list) {
		if (list == null || list.size() == 0) {
			return null;
		}
		int values_count = list.size();

		JPanel p = new JPanel();
		CellConstraints cc = new CellConstraints();

		int n_width = 7;

		// int row_count = (values_count + n_width - 1 ) / n_width;
		int col_count = Math.min(6, values_count);

		p.setLayout(new FormLayout(col_count + "*([60dlu,default], $lcgap), default",
				col_count + "*(default, $lgap), default"));

		valuePanels = new SingleValuePanel[values_count];
		int col = 0;
		int row = 0;
		for (int idx = 0; idx < values_count; idx++) {
			SingleValuePanel svp = new SingleValuePanel();

			RpMetric md = list.get(idx);
			svp.setName(md.getLocation());
			svp.clear();
			svp.setUnits(md.getUnitName());

			String code = md.getCode();
			if (code == null) {
				code = md.getLocation().toString();
			}
			svp.setCode(code);

			valuePanels[idx] = svp;

			if (row > 6)
				break; // BLIND ERROR

			p.add(valuePanels[idx], cc.xy(2 * col + 1, 2 * row + 1)); // skip
			// related-gap
			// row
			col++; // skip related-gap col
			if (col >= n_width) {
				row++;
				col = 0;
			}
		}

		return p;
	}

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {

		try {
			_signalEvent(jobID, source, sid, item);
		} catch (Exception e) {
			GuiUtil.showError("[VentilatorPanel] Display error.", e);
		}
	}

	private void _signalEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {

		if (item == null) {
			// FIXME: clear!
			return;
		}
		if (sid == StreamID.WAVEFORM) {
			int[] paw = (int[]) IntfUtil.getRawValue(item, paw_desc); // "PAW")
			int[] flow = (int[]) IntfUtil.getRawValue(item, flow_desc);

			long start_ms = item.getTime();
			if (paw != null) {
				paw_strip.addWaveformItem(start_ms, paw_desc, paw);
			}
			if (flow != null) {
				flow_strip.addWaveformItem(start_ms, flow_desc, flow);
			}

			if (volumeValues == null) {
				volumeValues = new int[paw.length];
			}

			assert (paw.length == flow.length) : "PAW AND FLOW ARRAYS MUST BE EQUAL LENGTH";

			int[] pawValues = paw;
			if (flow != null && pawValues != null) {
				int[] flowValues = flow;
				for (int i = 0; i < flowValues.length; i++) {
					flowValues[i] = flowValues[i] - 2048; // ZERO center the
															// values
					pawValues[i] = pawValues[i] - 2048;
					tot_volume = tot_volume + flowValues[i];
					if (tot_volume < 0) {
						tot_volume = 0;
					}
					volumeValues[i] = tot_volume / 126; // samples per
														// second...scale vol

				}
			}
			if (pawValues != null) {
				cgPAW.addPath(pawValues, volumeValues);
			}
			cgPAW.repaint();
			cgFLOW.repaint();

		} else if (sid == StreamID.MEASUREMENT) {
			numericsEvent(source, item);

		} else if (sid == StreamID.CONNECTION) {
			ConnectionItem ce = (ConnectionItem) item;
			// portLabel.setText(ce.getPortName());
		}
	}

	private void numericsEvent(Object source, PersistentItem block) {

		if (valuePanels == null) {
			return; // nothing to display here
		}
		if (block == null) {
			log.error("unexpected message: no data <block> from device");
			return;
		}
		RpMetric[] items = IntfUtil.getMetrics(block);

		if (items == null) {
			return; // nothing to process...should probably never be sent
		}

		for (RpMetric desc : items) {
			String name = desc.getLocation().toString();
			boolean found = false;
			for (SingleValuePanel p : valuePanels) {
				if (p == null) {
					// this can happen if you have more parameters selected than
					// can be displayed
					if (verbose > 1) {
						System.err.println("[VentilatorPanel] INTERNAL ERROR: null panel!");
					}
				} else if (name.equals(p.getName())) {
					RpUnit unit = desc.getUnit();

					String val = null;
					if (desc.getSubtyp() == DataTyp.STRING_TYP) {
						p.setValue("" + IntfUtil.getRawValue(block, desc));
					} else {
						p.setValue("" + IntfUtil.getScaledValue(block, desc));
					}
					found = true;
					break;
				}
			}
			if (!found && verbose > 0) {
				System.out.println("item not found: " + name);
			}
		}
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		chart1Panel = new JPanel();
		panel1 = new JPanel();
		pawVsVolume = cgPAW = new CircleGraph("VOL", "PAW");
		flowVsVolume = cgFLOW = new CircleGraph("VOL", "Flow");
		valuesContainer = new JPanel();
		CellConstraints cc = new CellConstraints();

		// ======== this ========
		setLayout(new FormLayout("default:grow", "fill:default:grow"));

		// ======== chart1Panel ========
		{
			chart1Panel.setLayout(new FormLayout("default:grow", "fill:default, fill:default:grow"));

			// ======== panel1 ========
			{
				panel1.setBorder(new EmptyBorder(5, 5, 5, 5));
				panel1.setLayout(new FormLayout("[120dlu,default], $rgap, default:grow",
						"fill:[120dlu,default], $lgap, fill:[120dlu,default]"));

				// ======== pawVsVolume ========
				{
					pawVsVolume.setLayout(null);

					{ // compute preferred size
						Dimension preferredSize = new Dimension();
						for (int i = 0; i < pawVsVolume.getComponentCount(); i++) {
							Rectangle bounds = pawVsVolume.getComponent(i).getBounds();
							preferredSize.width = Math.max(bounds.x + bounds.width, preferredSize.width);
							preferredSize.height = Math.max(bounds.y + bounds.height, preferredSize.height);
						}
						Insets insets = pawVsVolume.getInsets();
						preferredSize.width += insets.right;
						preferredSize.height += insets.bottom;
						pawVsVolume.setMinimumSize(preferredSize);
						pawVsVolume.setPreferredSize(preferredSize);
					}
				}
				panel1.add(pawVsVolume, cc.xy(1, 1));

				// ======== flowVsVolume ========
				{
					flowVsVolume.setLayout(null);

					{ // compute preferred size
						Dimension preferredSize = new Dimension();
						for (int i = 0; i < flowVsVolume.getComponentCount(); i++) {
							Rectangle bounds = flowVsVolume.getComponent(i).getBounds();
							preferredSize.width = Math.max(bounds.x + bounds.width, preferredSize.width);
							preferredSize.height = Math.max(bounds.y + bounds.height, preferredSize.height);
						}
						Insets insets = flowVsVolume.getInsets();
						preferredSize.width += insets.right;
						preferredSize.height += insets.bottom;
						flowVsVolume.setMinimumSize(preferredSize);
						flowVsVolume.setPreferredSize(preferredSize);
					}
				}
				panel1.add(flowVsVolume, cc.xy(1, 3));
			}
			chart1Panel.add(panel1, cc.xy(1, 1));

			// ======== valuesContainer ========
			{
				valuesContainer.setLayout(new BorderLayout());
			}
			chart1Panel.add(valuesContainer, cc.xy(1, 2));
		}
		add(chart1Panel, cc.xy(1, 1));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JPanel chart1Panel;
	private JPanel panel1;
	private JPanel pawVsVolume;
	private JPanel flowVsVolume;
	private JPanel valuesContainer;
	// JFormDesigner - End of variables declaration //GEN-END:variables

}
