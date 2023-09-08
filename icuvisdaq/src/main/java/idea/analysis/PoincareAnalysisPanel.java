/*
 * Created by JFormDesigner on Mon Mar 08 10:06:06 CST 2010
 */

package idea.analysis;

import icuInterface.RpUtil;
import idea.display.simple.TwoValuePanel;
import idea.intf.MultiplexInterface;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.schema.rp.RpAnalysis;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpMetric;
import idea.schema.rp.StringStringMap;

import java.awt.Color;
import java.text.DecimalFormat;
import java.text.NumberFormat;

import javax.swing.JPanel;

import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;
import idea.analysis.event.BeatBlock;
import idea.analysis.event.PoincareBlock;
import idea.chart.SignalChart;
import idea.chart.SignalPanel;
import idea.qrsdet.AbstractDetector;
import idea.qrsdet.DetectorFactory;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
@Slf4j
public class PoincareAnalysisPanel extends JPanel {

	// NumberFormat df1 = new DecimalFormat( "0.#");
	NumberFormat df2 = new DecimalFormat( "0.##");
	NumberFormat df3 = new DecimalFormat( "0.###");
	
	PoincareProcessor pplot;
	
	public PoincareAnalysisPanel(StreamProducer[] producers, RpAnalysis analConfs) {
		initComponents();
	
		rriMetricPanel.setFormat( df3 );
		sd12MetricPanel.setFormat( df2 );
		sdrrsdMetricPanel.setFormat( df2 );
		
		// this.conf = analConfs;
		buildPanel(analConfs); // general case...do nothing for this panel

		StreamConsumer[] consumers = new StreamConsumer[2];
		consumers[0] = sd1SignalPanel;

		labelGraphs();
		wireProducersAndConsumers(producers, consumers, analConfs );
	}

	private void labelGraphs() {
		// rriSignalPanel.setYAxisLabel("RRI");
		// sd1SignalPanel.setYAxisLabel("SD1");
		// sd2SignalPanel.setYAxisLabel("SD2");
		// sdrrSignalPanel.setYAxisLabel("SDRR");
		// sdsdSignalPanel.setYAxisLabel("SDSD");
	}

	private void wireProducersAndConsumers(StreamProducer[] producers, StreamConsumer[] consumers, RpAnalysis anal) {
		StringStringMap params = anal.getParam();
		
		if( producers == null || producers.length == 0 ) {
			log.error( "NO SIGNAL PRODUCERS");
			// assert( false ) : "No signal producers for analysis.";
			return;
		}

		String detector_param =params.get( "detector");
		if( detector_param == null ) {
			assert( detector_param != null ) : "CONFIG ERROR: detector not available";
			log.error( "NO DETECTOR --> NO ANALYSIS");
			return;
		}
		
		/*
		 * wire device0 output to QRS detector
		 */
		String sourceName = params.get( "DEV");
				
		StreamProducer producer = getNamedDevice( producers, sourceName );
		assert( producer != null ) : "CONFIG ERROR: signal producer does not exist";
		if( producer == null ) {
			System.err.println( "PoincareAnalysisPanel PRODUCER DOES NOT EXIST: " + sourceName );
			return;
		}
		RpDevice dc = producer.getConfiguration();

		String loc = params.get( "signal");
		RpMetric wf = RpUtil.getMetricFromStreamID(dc, StreamID.WAVEFORM, loc);
		assert( wf != null ) : "CONFIG ERROR: requested ECG signal not available";
		
		String detector_name = detector_param.toString();
		
		AbstractDetector detector = DetectorFactory.createDetector( detector_name, wf );
		
		
		if( detector == null ){
			GuiUtil.showMessage("DETECTOR NOT FOUND: " + detector_name );
			return;
		}

		producer.addStreamListener(StreamID.WAVEFORM, detector);

		/*
		 * wire qrs detector output to RRI signal chart
		 */

		rriSignalPanel.getChart().setAxisMode(SignalChart.XAxisMode.POINT);
		rriSignalPanel.getChart().addNumerics(BeatBlock.SAMPLE_INTERVAL_LOC, Color.YELLOW, 1, SignalChart.POINT_STYLE);
		detector.addStreamListener(StreamID.MEASUREMENT, rriSignalPanel);
		// detector.addEventListener( StreamID.ALARM, rriSignalPanel );

		/*
		 * wire qrs detector output to entropy processsor
		 */

		boolean do_all = true;

		if (do_all) {
			
			 pplot = new PoincareProcessor(200);
			detector.addStreamListener(StreamID.MEASUREMENT, pplot);
			detector.addStreamListener(StreamID.MEASUREMENT, new UpdateNumericField(rriMetricPanel, 0, BeatBlock.SAMPLE_INTERVAL_LOC, 1.0) );
			pplot.addStreamListener(StreamID.MEASUREMENT, new UpdateNumericField(rriMetricPanel, 1, "sdratio", 1.0) );
			pplot.addStreamListener(StreamID.MEASUREMENT, new UpdateNumericField(sd12MetricPanel, 0, "sd1", 1.0) );
			pplot.addStreamListener(StreamID.MEASUREMENT, new UpdateNumericField(sd12MetricPanel, 1, "sd2", 1.0) );
			pplot.addStreamListener(StreamID.MEASUREMENT, new UpdateNumericField(sdrrsdMetricPanel, 0, "sdrr", 1.0) );
			pplot.addStreamListener(StreamID.MEASUREMENT, new UpdateNumericField(sdrrsdMetricPanel, 1, "sdsd", 1.0) );

			/*
			 * wire poincare output to respective charts
			 */

			sdratioSignalPanel.getChart().setAxisMode(SignalChart.XAxisMode.POINT);
			sdratioSignalPanel.getChart().addNumerics(PoincareBlock.SDRATIO_LOC, Color.YELLOW, 1, SignalChart.POINT_STYLE);
			pplot.addStreamListener(StreamID.MEASUREMENT, sdratioSignalPanel);

			sd1SignalPanel.getChart().setAxisMode(SignalChart.XAxisMode.POINT);
			sd1SignalPanel.getChart().addNumerics(PoincareBlock.SD1_LOC, Color.YELLOW, 1, SignalChart.POINT_STYLE);
			pplot.addStreamListener(StreamID.MEASUREMENT, sd1SignalPanel);
			pplot.addStreamListener(StreamID.ALARM, sd1SignalPanel);

			sd2SignalPanel.getChart().setAxisMode(SignalChart.XAxisMode.POINT);
			sd2SignalPanel.getChart().addNumerics(PoincareBlock.SD2_LOC, Color.YELLOW, 1, SignalChart.POINT_STYLE);
			pplot.addStreamListener(StreamID.MEASUREMENT, sd2SignalPanel);

			sdrrSignalPanel.getChart().setAxisMode(SignalChart.XAxisMode.POINT);
			sdrrSignalPanel.getChart().addNumerics(PoincareBlock.SDRR_LOC, Color.YELLOW, 1, SignalChart.POINT_STYLE);
			pplot.addStreamListener(StreamID.MEASUREMENT, sdrrSignalPanel);

			sdsdSignalPanel.getChart().setAxisMode(SignalChart.XAxisMode.POINT);
			sdsdSignalPanel.getChart().addNumerics(PoincareBlock.SDSD_LOC, Color.YELLOW, 1, SignalChart.POINT_STYLE);
			pplot.addStreamListener(StreamID.MEASUREMENT, sdsdSignalPanel);
		}
	}

	private StreamProducer getNamedDevice(StreamProducer[] producers, String sourceName) {
		if( producers == null ) {
			return null;
		}
		StreamProducer source = null;
		for( StreamProducer intf : producers ) {
			RpDevice dc = intf.getConfiguration();
			if( dc != null && sourceName.equals(dc.getName()) ) {
				source = intf;
				break;
			}
			if( intf instanceof MultiplexInterface ) {
				MultiplexInterface mintf = (MultiplexInterface) intf;
				source = getNamedDevice( mintf.getSubInterfaces(), sourceName );
			}
			
			if( source != null ) {
				break;
			}
		}
		
		return source;
	}

	private void buildPanel(RpAnalysis analConfs) {
		// this will be filled in for the general case
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		rriMetricPanel = new TwoValuePanel();
		rriSignalPanel = new SignalPanel();
		sdratioSignalPanel = new SignalPanel();
		sd12MetricPanel = new TwoValuePanel();
		sd1SignalPanel = new SignalPanel();
		sd2SignalPanel = new SignalPanel();
		sdrrsdMetricPanel = new TwoValuePanel();
		sdrrSignalPanel = new SignalPanel();
		sdsdSignalPanel = new SignalPanel();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setLayout(new FormLayout(
			"[80dlu,default], 2*($lcgap, default:grow), $lcgap, default",
			"3*(fill:[50dlu,default], $lgap), default"));

		//---- rriMetricPanel ----
		rriMetricPanel.setUpperTitle("RRI");
		rriMetricPanel.setLowerTitle(" SD1/SD2");
		add(rriMetricPanel, cc.xy(1, 1));

		//---- rriSignalPanel ----
		rriSignalPanel.setName("rri");
		add(rriSignalPanel, cc.xy(3, 1));

		//---- sdratioSignalPanel ----
		sdratioSignalPanel.setName("sdratio");
		add(sdratioSignalPanel, cc.xy(5, 1));

		//---- sd12MetricPanel ----
		sd12MetricPanel.setLowerTitle("SD2");
		sd12MetricPanel.setUpperTitle("SD1");
		add(sd12MetricPanel, cc.xy(1, 3));

		//---- sd1SignalPanel ----
		sd1SignalPanel.setName("sd1t");
		add(sd1SignalPanel, cc.xy(3, 3));

		//---- sd2SignalPanel ----
		sd2SignalPanel.setName("sd2");
		add(sd2SignalPanel, cc.xy(5, 3));

		//---- sdrrsdMetricPanel ----
		sdrrsdMetricPanel.setLowerTitle("SDSD");
		sdrrsdMetricPanel.setUpperTitle("SDRR");
		add(sdrrsdMetricPanel, cc.xy(1, 5));

		//---- sdrrSignalPanel ----
		sdrrSignalPanel.setName("sdrr");
		add(sdrrSignalPanel, cc.xy(3, 5));

		//---- sdsdSignalPanel ----
		sdsdSignalPanel.setName("sdsd");
		add(sdsdSignalPanel, cc.xy(5, 5));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private TwoValuePanel rriMetricPanel;
	private SignalPanel rriSignalPanel;
	private SignalPanel sdratioSignalPanel;
	private TwoValuePanel sd12MetricPanel;
	private SignalPanel sd1SignalPanel;
	private SignalPanel sd2SignalPanel;
	private TwoValuePanel sdrrsdMetricPanel;
	private SignalPanel sdrrSignalPanel;
	private SignalPanel sdsdSignalPanel;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	public StreamProducer [] getSignalProducers() {
		StreamProducer[] producers = new StreamProducer [] { pplot } ;
		return producers;
	}
}
