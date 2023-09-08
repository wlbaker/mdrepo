/*
 * Created by JFormDesigner on Mon Jan 30 13:24:35 CST 2012
 */

package idea.analysis;

import idea.display.simple.TwoValuePanel;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.schema.rp.RpAnalysis;
import idea.schema.rp.RpDevice;

import java.awt.Color;
import java.text.DecimalFormat;
import java.text.NumberFormat;

import javax.swing.JPanel;

import idea.analysis.event.EntropyBlock;
import idea.analysis.event.MSEBlock;
import idea.chart.SignalChart;
import idea.chart.SignalPanel;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class EntropySummaryPanel extends JPanel {
	private TwoValuePanel rriMetricPanel;
	private SignalPanel rriSignalPanel;
	private TwoValuePanel entMetricPanel;
	private SignalPanel saentSignalPanel;
	private SignalPanel mseSignalPanel;
	private TwoValuePanel qMetricPanel;
	
	NumberFormat df2 = new DecimalFormat("0.00");

	public EntropySummaryPanel(RpAnalysis anal) {
		initComponents();
		initMoreComponents();
		
		entMetricPanel.setFormat(df2);
		qMetricPanel.setFormat(df2);

		rriMetricPanel.setUpperValue(null);
		entMetricPanel.clear();
		qMetricPanel.clear();

		saentSignalPanel.autoScale();
		mseSignalPanel.autoScale();
	}

	private void initMoreComponents() {
		rriMetricPanel = new TwoValuePanel();
		rriSignalPanel = new SignalPanel();
		entMetricPanel = new TwoValuePanel();
		saentSignalPanel = new SignalPanel();
		mseSignalPanel = new SignalPanel();
		qMetricPanel = new TwoValuePanel();

		CellConstraints cc = new CellConstraints();

		//======== this ========
//		setLayout(new FormLayout(
//			"[80dlu,default], 2*($lcgap, default:grow), $lcgap, default",
//			"2*(fill:[50dlu,default], $lgap), fill:[50dlu,default]"));

		//---- rriMetricPanel ----
//		rriMetricPanel.setUpperTitle("RRI");
//		rriMetricPanel.setLowerTitle(" ");
//		add(rriMetricPanel, cc.xy(1, 1));

		//---- rriSignalPanel ----
//		rriSignalPanel.setName("rri");
//		rriSignalPanel.setScaleMinRange(100.0);
//		add(rriSignalPanel, cc.xywh(3, 1, 3, 1));

		//---- entMetricPanel ----
		entMetricPanel.setLowerTitle("mse complexity   r=6ms / 800");
		entMetricPanel.setUpperTitle("samp_en   r = 6ms / 200");
		add(entMetricPanel, cc.xy(1, 1));

		//---- saentSignalPanel ----
		saentSignalPanel.setName("saent");
		saentSignalPanel.setScaleMaxY(3.0);
		saentSignalPanel.setScaleMinY(0.0);
		add(saentSignalPanel, cc.xy(3, 1));

		
		//---- mseSignalPanel ----
		mseSignalPanel.setName("mse");
		mseSignalPanel.setScaleMinY(0.0);
		mseSignalPanel.setScaleMaxY(10.0);
		add(mseSignalPanel, cc.xy(5, 1));
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license

		//======== this ========
		setLayout(new FormLayout(
			"[50dlu,default], 3*($lcgap, default:grow), $lcgap, default",
			"fill:[60dlu,default]"));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	// JFormDesigner - End of variables declaration  //GEN-END:variables
	
	
	public StreamProducer[] getSignalProducers() {
		return null;
	}

	public void wire(StreamProducer[] drivers) {
		for( StreamProducer driver : drivers ) {
			RpDevice conf = driver.getConfiguration();
			if( conf != null ) {
				String name = conf.getName();
				if( "EntropyProcessor".equals(name)) {
					wireEntropyProcessor( driver );
				} else if( "MultiscaleEntropyProcessor".equals(name)) {
					wireMultiscaleEntropyProcessor( driver );
				}
			}
		}
	}

	private void wireMultiscaleEntropyProcessor(StreamProducer driver) {
		MultiscaleEntropyProcessor mse = (MultiscaleEntropyProcessor)driver;
		mse.addStreamListener(StreamID.MEASUREMENT, new UpdateNumericField(entMetricPanel, 1,
				MSEBlock.MSECOMPLEXITY_LOC));
		mse.addStreamListener(StreamID.ALARM, mseSignalPanel);
		
		mseSignalPanel.getChart().setAxisMode(SignalChart.XAxisMode.POINT);
		mseSignalPanel.getChart().addNumerics(MSEBlock.MSECOMPLEXITY_LOC, Color.WHITE, 1, SignalChart.POINT_STYLE);
		mseSignalPanel.getChart().addNumerics(MSEBlock.MSE2_LOC, Color.YELLOW, 1, SignalChart.POINT_STYLE);
		mseSignalPanel.getChart().addNumerics(MSEBlock.MSE3_LOC, Color.GREEN, 1, SignalChart.POINT_STYLE);
		mseSignalPanel.getChart().addNumerics(MSEBlock.MSE4_LOC, Color.RED, 1, SignalChart.POINT_STYLE);
		mse.addStreamListener(StreamID.MEASUREMENT, mseSignalPanel);

	}

	private void wireEntropyProcessor(StreamProducer driver) {
		
		EntropyFilter ent = (EntropyFilter) driver;
		ent.addStreamListener(StreamID.MEASUREMENT, new UpdateNumericField(entMetricPanel, 0, "sampent"));
		ent.addStreamListener(StreamID.MEASUREMENT, new UpdateNumericField(qMetricPanel, 0, "q"));
		ent.addStreamListener(StreamID.MEASUREMENT, new UpdateNumericField(qMetricPanel, 1, "stddev"));

		/*
		 * wire entropy output to saent, quadratic entropy, stddev charts
		 */
		saentSignalPanel.getChart().setAxisMode(SignalChart.XAxisMode.POINT);
		saentSignalPanel.getChart().addNumerics(EntropyBlock.SAMPENT_LOC, Color.YELLOW, 1, SignalChart.POINT_STYLE);
		ent.addStreamListener(StreamID.MEASUREMENT, saentSignalPanel);
		ent.addStreamListener(StreamID.ALARM, saentSignalPanel);
	}

}
