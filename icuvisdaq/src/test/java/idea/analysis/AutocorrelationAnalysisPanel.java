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
import idea.analysis.event.AutocorrelationBlock;
import idea.analysis.event.BeatBlock;
import idea.chart.HistogramChart;
import idea.chart.HistogramPanel;
import idea.chart.SignalChart;
import idea.chart.SignalPanel;
import idea.qrsdet.AbstractDetector;
import idea.qrsdet.DetectorFactory;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

/**
 * @author User #2
 */
@Slf4j
@SuppressWarnings("serial")
public class AutocorrelationAnalysisPanel extends JPanel {

	private static RpAnalysis analysisInfo;
	
	static {
		analysisInfo = new RpAnalysis();
		analysisInfo.setAnalysisClass(AutocorrelationAnalysisPanel.class.getCanonicalName());
		analysisInfo.setName("Autocorrelation Analysis");
	}
	NumberFormat df1 = new DecimalFormat( "0.#");
	NumberFormat df2 = new DecimalFormat( "0.##");
	NumberFormat df3 = new DecimalFormat( "0.###");
	AutocorrelationFilter autocorr;	
	
	public AutocorrelationAnalysisPanel(StreamProducer[] producers, RpAnalysis analConfs) {
		initComponents();
	
		rriMetricPanel.setFormat( df1 );
		sodMetricPanel.setFormat( df3 );
		sdrrsdMetricPanel.setFormat( df2 );

		rriMetricPanel.setUpperValue( null );
		sodMetricPanel.setUpperValue( null );

		// this.conf = analConfs;
		buildPanel(analConfs); // general case...do nothing for this panel

		StreamConsumer[] consumers = new StreamConsumer[2];
		consumers[0] = sodSignalPanel;

		labelGraphs();
		wireProducersAndConsumers(producers, consumers, analConfs );
	}

	private void labelGraphs() {
		// rriSignalPanel.setYAxisLabel("RRI");
		// sodSignalPanel.setYAxisLabel("SD1");
		// histogramPanel.setYAxisLabel("SD2");
		// sdrrSignalPanel.setYAxisLabel("SDRR");
		// sdsdSignalPanel.setYAxisLabel("SDSD");
	}

	private void wireProducersAndConsumers(StreamProducer[] producers, StreamConsumer[] consumers, RpAnalysis anal) {
		StringStringMap params = anal.getParam();
		
		if( producers == null || producers.length == 0 ) {
			log.error("NO SIGNAL PRODUCERS");
			// assert( false ) : "No signal producers for analysis.";
			return;
		}

		String detector_param = params.get( "detector");
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
		if( producer == null ) {
			sourceName = sourceName + "_0";
			producer = getNamedDevice( producers, sourceName );
		}
		assert( producer != null ) : "CONFIG ERROR: signal producer does not exist";
		RpDevice dc = producer.getConfiguration();

		String loc = params.get( "signal");
		RpMetric wf = RpUtil.getMetricFromStreamID(dc, StreamID.MEASUREMENT, loc );
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
		rriSignalPanel.getChart().addNumerics(BeatBlock.MS_INTERVAL_LOC, Color.YELLOW, 1, SignalChart.POINT_STYLE);
		detector.addStreamListener(StreamID.MEASUREMENT, rriSignalPanel);
		// detector.addEventListener( StreamID.ALARM, rriSignalPanel );

		/*
		 * wire qrs detector output to entropy processsor
		 */

		boolean do_all = true;

		if (do_all) {
			
			autocorr = new AutocorrelationFilter(800 + 4);
			detector.addStreamListener(StreamID.MEASUREMENT, autocorr);
			detector.addStreamListener(StreamID.MEASUREMENT, new UpdateNumericField(rriMetricPanel, 1, BeatBlock.MS_INTERVAL_LOC, 1.0) );
			autocorr.addStreamListener(StreamID.MEASUREMENT, new UpdateNumericField(sodMetricPanel, 1, "sod", 1.0) );
			autocorr.addStreamListener(StreamID.MEASUREMENT, new UpdateNumericField(sdrrsdMetricPanel, 0, "sdrr", 1.0) );
			autocorr.addStreamListener(StreamID.MEASUREMENT, new UpdateNumericField(sdrrsdMetricPanel, 1, "sdsd", 1.0) );

			/*
			 * wire poincare output to respective charts
			 */

			sodSignalPanel.getChart().setAxisMode(SignalChart.XAxisMode.POINT);
			sodSignalPanel.getChart().addNumerics(AutocorrelationBlock.SOD_LOC, Color.YELLOW, 1, SignalChart.POINT_STYLE);
			autocorr.addStreamListener(StreamID.MEASUREMENT, sodSignalPanel);
			autocorr.addStreamListener(StreamID.ALARM, sodSignalPanel);

			histogramPanel.getChart().setAxisMode(HistogramChart.XAxisMode.POINT);
			// histogramPanel.getChart().addNumerics(AutocorrelationBlock.SOD_LOC, Color.YELLOW, 1, SignalChart.POINT_STYLE);
			autocorr.addStreamListener(StreamID.WAVEFORM, histogramPanel);

			sdrrSignalPanel.getChart().setAxisMode(SignalChart.XAxisMode.POINT);
			sdrrSignalPanel.getChart().addNumerics(AutocorrelationBlock.SDRR_LOC, Color.YELLOW, 1, SignalChart.POINT_STYLE);
			autocorr.addStreamListener(StreamID.MEASUREMENT, sdrrSignalPanel);

			sdsdSignalPanel.getChart().setAxisMode(SignalChart.XAxisMode.POINT);
			sdsdSignalPanel.getChart().addNumerics(AutocorrelationBlock.SDSD_LOC, Color.YELLOW, 1, SignalChart.POINT_STYLE);
			autocorr.addStreamListener(StreamID.MEASUREMENT, sdsdSignalPanel);
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
		sodMetricPanel = new TwoValuePanel();
		sodSignalPanel = new SignalPanel();
		histogramPanel = new HistogramPanel();
		sdrrsdMetricPanel = new TwoValuePanel();
		sdrrSignalPanel = new SignalPanel();
		sdsdSignalPanel = new SignalPanel();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setLayout(new FormLayout(
			"[80dlu,default], 2*($lcgap, default:grow), $lcgap, default",
			"2*(fill:[50dlu,default], $lgap), fill:[50dlu,default]"));

		//---- rriMetricPanel ----
		rriMetricPanel.setUpperTitle("RRI");
		rriMetricPanel.setLowerTitle(" ");
		add(rriMetricPanel, cc.xy(1, 1));

		//---- rriSignalPanel ----
		rriSignalPanel.setName("rri");
		add(rriSignalPanel, cc.xy(3, 1));

		//---- sodMetricPanel ----
		sodMetricPanel.setLowerTitle(" ");
		sodMetricPanel.setUpperTitle("SOD");
		add(sodMetricPanel, cc.xy(1, 3));

		//---- sodSignalPanel ----
		sodSignalPanel.setName("sod");
		add(sodSignalPanel, cc.xy(3, 3));

		//---- histogramPanel ----
		histogramPanel.setName("sdav");
		add(histogramPanel, cc.xy(5, 3));

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
	private TwoValuePanel sodMetricPanel;
	private SignalPanel sodSignalPanel;
	private HistogramPanel histogramPanel;
	private TwoValuePanel sdrrsdMetricPanel;
	private SignalPanel sdrrSignalPanel;
	private SignalPanel sdsdSignalPanel;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	public StreamProducer [] getSignalProducers() {
		StreamProducer[] producers = new StreamProducer[1];
		producers[1] = autocorr;
		return producers;
	}
}
