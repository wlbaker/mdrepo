/*
 * Created by JFormDesigner on Tue May 17 17:53:13 CDT 2011
 */

package idea.analysis;

import icuInterface.RpUtil;
import idea.Stats;
import idea.display.simple.TwoValuePanel;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.PersistentItem;
import idea.schema.rp.RpAnalysis;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpLinearUnit;
import idea.schema.rp.RpMetric;
import idea.schema.rp.StringStringMap;

import java.awt.Color;
import java.awt.Font;
import java.text.DecimalFormat;
import java.text.NumberFormat;
import java.util.ArrayList;

import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.SwingConstants;

import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;
import idea.Stats;
import idea.analysis.event.SBCO2Block;
import idea.chart.SignalChart;
import idea.chart.SignalPanel;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

/**
 * @author User #2
 */

@Slf4j
@SuppressWarnings("serial")
public class IBIBreathSegmentationAnalysisPanel extends JPanel implements StreamConsumer {
	private RpMetric flow_desc;
	private RpMetric awp_desc;

	private SBSegmentFilter segmenter;
	private StreamProducer [] producers = new StreamProducer[1];

	private final static NumberFormat df0 = new DecimalFormat("0");
	private final static NumberFormat df2 = new DecimalFormat("0.00");

	TwoValuePanel ibiMetricPanel;
	SignalPanel ibiTrendPanel;
	private RpAnalysis analysis;

	ArrayList<Integer> values;
	int count = 0;
	private String devName;

	public IBIBreathSegmentationAnalysisPanel(RpAnalysis anal) {
		initComponents();
		initMoreComponents();

		values = new ArrayList<Integer>();
		this.analysis = anal;

		segmenter = new SBSegmentFilter();
		producers[0] = segmenter;
		
		segmenter.addStreamListener(StreamID.MEASUREMENT, new StreamConsumer() {

			@Override
			public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {
				SBCO2Block block = (SBCO2Block)item;
				showSegmentedBreath(block);
			}

			private void showSegmentedBreath(SBCO2Block block) {
				int value = block.getIbi();
					values.add(value);
					count++;
					ibiMetricPanel.setLowerValue(count);

					if ( count > 20) {
						double[] signal = new double[values.size()];
						for (int i = 0; i < values.size(); i++) {
							signal[i] = values.get(i);
						}
						double sd = Stats.sd(signal);

						sdLabel.setText(df0.format(sd));
						// if (count > 100) {
							values.remove(0);
							double ent = EntropyFilter.SaEn(signal, sd * 0.15 + 3, 2);
							sampenLabel.setText(df2.format(ent));
							if( values.size() < 99 ) {
								sampenLabel.setForeground( Color.RED );
							} else {
								sampenLabel.setForeground( Color.WHITE );
							}
						// }
					}
			}

		});

		segmenter.addStreamListener(StreamID.MEASUREMENT, ibiTrendPanel);
		segmenter.addStreamListener(StreamID.MEASUREMENT, ibiMetricPanel);

		ibiTrendPanel.putClientProperty("debug", true);
		ibiTrendPanel.setScaleMinY( 0.0 );
		ibiTrendPanel.setScaleMaxY( 15.0 );

		ibiTrendPanel.getChart().addNumerics(SBCO2Block.IBI_LOC, Color.YELLOW, 1, SignalChart.POINT_STYLE);
		// ibiTrendPanel.getChart().addNumerics(SBCO2Block.EXH_LOC, Color.CYAN, 1, SignalChart.POINT_STYLE);
		ibiMetricPanel.setUpperLoc(SBCO2Block.IBI_LOC);
		// ibiMetricPanel.setLowerLoc(SBCO2Block.EXH_LOC);

		sampenLabel.setText(" ");
		sdLabel.setText(" ");
	}

	public StreamProducer [] getSignalProducers() {
		return producers;
	}

	public void wire(StreamProducer[] drivers) {
		  StringStringMap params = analysis.getParam();
		 devName = params.get("DEV");

		RpDevice conf = null;
		StreamProducer driver = findDev(devName, drivers);
		if (driver != null) {
			conf = driver.getConfiguration();
		}

		log.error( "Invalid driver name or no config: {} conf: {}", devName, conf );
		if (conf == null) {
			return;
		}

		// ok
		driver.addStreamListener(StreamID.WAVEFORM, segmenter);

		String flow_param = params.get( "FLOW");
		flow_desc = RpUtil.getMetricFromStreamID(conf, StreamID.WAVEFORM, flow_param);

		String paw_param = params.get( "PAW");
		awp_desc = RpUtil.getMetricFromStreamID(conf, StreamID.WAVEFORM, paw_param);

		if( flow_desc == null || awp_desc == null ) {
			GuiUtil.showMessage("Could not find signal for flow [" + flow_param + "] or paw [" + paw_param + "]" );
		} else {
			initSegmenter();
		}
	}

	private StreamProducer findDev(String devName, StreamProducer[] drivers) {
		StreamProducer ai = null;
		for (StreamProducer driver : drivers) {
			if (devName.equals(driver.getConfiguration().getName())) {
				ai = driver;
				break;
			}
		}
		return ai;
	}

	private void initMoreComponents() {
		CellConstraints cc = new CellConstraints();

		ibiMetricPanel = new TwoValuePanel();
		ibiMetricPanel.setFormat(df2);
		ibiMetricPanel.setUpperTitle("IBI");
		ibiMetricPanel.setLowerTitle("Count");
		trendsPanel.add(ibiMetricPanel, cc.xy(1, 1));

		ibiTrendPanel = new SignalPanel();
		ibiTrendPanel.setName("ibi");
		ibiTrendPanel.setScaleMinRange(600.0);
		ibiTrendPanel.setScaleMinY(0.0);
		ibiTrendPanel.setYAxisLabel("ibi");
		ibiTrendPanel.setYLabelRotation(true);
		ibiTrendPanel.getChart().setAxisMode(SignalChart.XAxisMode.POINT);
		trendsPanel.add(ibiTrendPanel, cc.xy(3, 1));

	}

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {
		if (flow_desc == null) {
			return;
		}
		if (!(sid == StreamID.WAVEFORM)) {
			return;
		}
		segmenter.addWaveform(item);
	}

	private void initSegmenter() {
		// LinearUnit tenths_mmHg = new LinearUnit(0.1, 0, "mmHg");
		RpLinearUnit cmH2O_to_mmHg = new RpLinearUnit(0.7355924, 0, "mmHg");
		RpLinearUnit mbar_to_mmHg = new RpLinearUnit(0.750061683, 0, "mmHg");
		// LinearUnit tenths_mbar_to_mmHg = new LinearUnit(0.0750061683, 0, "mmHg");
		RpLinearUnit tenths_Lmin = new RpLinearUnit(0.1, 0, "L/min");
		RpLinearUnit evitaFlow_Lmin = new RpLinearUnit(0.1, 0, "L/min");

		RpLinearUnit flowUnit = null;
		RpLinearUnit awpUnit = null;

		if( devName == null ) {
			log.error("devname cannot be null for ibi analysis panel");
			devName.startsWith("unkonwn");  // throw a null point exception
		}
		if (devName.startsWith("Cosmo")) {
			flowUnit = tenths_Lmin;
			awpUnit = cmH2O_to_mmHg;
			segmenter.setFlowThreshold(100);
		} else if (devName.startsWith("NM3") || devName.startsWith("Philips")) {
			flowUnit = tenths_Lmin;
			awpUnit = cmH2O_to_mmHg;
			segmenter.setFlowThreshold(100);
		} else if (devName.startsWith("Evita") || devName.startsWith("V")) {
			flowUnit = evitaFlow_Lmin;
			awpUnit = mbar_to_mmHg;
			segmenter.setFlowThreshold(400);
		} else {
			log.error("Conversion factor unknown for device: " + devName);
			flowUnit = evitaFlow_Lmin;
			awpUnit = mbar_to_mmHg;
		}
		segmenter.setSourceFlow(flow_desc.getLocation(), flowUnit);
		segmenter.setSourceAWP(awp_desc.getLocation(), awpUnit);
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		panel4 = new JPanel();
		trendsPanel = new JPanel();
		numericsPanel = new JPanel();
		label3 = new JLabel();
		label2 = new JLabel();
		sdLabel = new JLabel();
		sampenLabel = new JLabel();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout(
			"default:grow",
			"fill:default:grow, $lgap, default"));

		//======== panel4 ========
		{
			panel4.setLayout(new FormLayout(
				"default:grow",
				"fill:default:grow"));

			//======== trendsPanel ========
			{
				trendsPanel.setLayout(new FormLayout(
					"[50dlu,default], $rgap, [150dlu,default]:grow",
					"fill:[120dlu,default], $lgap, fill:default:grow"));
			}
			panel4.add(trendsPanel, cc.xy(1, 1));
		}
		add(panel4, cc.xy(1, 1));

		//======== numericsPanel ========
		{
			numericsPanel.setLayout(new FormLayout(
				"default:grow, 2*($lcgap, [50dlu,default])",
				"default, fill:60dlu"));

			//---- label3 ----
			label3.setText("SD");
			numericsPanel.add(label3, cc.xy(3, 1));

			//---- label2 ----
			label2.setText("Fractal Index");
			numericsPanel.add(label2, cc.xy(5, 1));

			//---- sdLabel ----
			sdLabel.setText("text");
			sdLabel.setHorizontalAlignment(SwingConstants.TRAILING);
			sdLabel.setFont(new Font("Tahoma", Font.PLAIN, 30));
			sdLabel.setForeground(Color.white);
			numericsPanel.add(sdLabel, cc.xy(3, 2));

			//---- sampenLabel ----
			sampenLabel.setText("text");
			sampenLabel.setHorizontalAlignment(SwingConstants.TRAILING);
			sampenLabel.setFont(new Font("Tahoma", Font.PLAIN, 30));
			sampenLabel.setForeground(Color.white);
			numericsPanel.add(sampenLabel, cc.xy(5, 2));
		}
		add(numericsPanel, cc.xy(1, 3));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JPanel panel4;
	private JPanel trendsPanel;
	private JPanel numericsPanel;
	private JLabel label3;
	private JLabel label2;
	private JLabel sdLabel;
	private JLabel sampenLabel;
	// JFormDesigner - End of variables declaration //GEN-END:variables

}
