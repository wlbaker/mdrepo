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
import idea.analysis.event.DetrendedFluctuationBlock;
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
public class DetrendedFluctuationAnalysisPanel extends JPanel {

	NumberFormat df1 = new DecimalFormat( "0.#");
	NumberFormat df3 = new DecimalFormat( "0.###");
	
	DetrendedFluctuationProcessor dfa;
	
	public DetrendedFluctuationAnalysisPanel(StreamProducer[] producers, RpAnalysis analConfs) {
		initComponents();
	
		rriMetricPanel.setFormat( df1 );
		alphaMetricPanel.setFormat( df3 );
		alpha12MetricPanel.setFormat( df3 );

		rriMetricPanel.setUpperValue( null );
		alphaMetricPanel.setUpperValue( null );

		// this.conf = analConfs;
		buildPanel(analConfs); // general case...do nothing for this panel

		StreamConsumer[] consumers = new StreamConsumer[2];
		consumers[0] = alphaPanel;

		labelGraphs();
		wireProducersAndConsumers(producers, consumers, analConfs );
	}

	private void labelGraphs() {
		// rriSignalPanel.setYAxisLabel("RRI");
		// alphaPanel.setYAxisLabel("ALPHA");
		// alpha1Panel.setYAxisLabel("ALPHA1");
		// alpha2Panel.setYAxisLabel("ALPHA2");
	}

	private void wireProducersAndConsumers(StreamProducer[] producers, StreamConsumer[] consumers, RpAnalysis anal) {
		 StringStringMap params = anal.getParam();
		
		if( producers == null || producers.length == 0 ) {
			log.error( "NO SIGNAL PRODUCERS");
			// assert( false ) : "No signal producers for analysis.";
			return;
		}

		Object detector_param = params.get( "detector");
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
			producer = getNamedDevice( producers, sourceName + "_0" );
		}
		assert( producer != null ) : "CONFIG ERROR: signal producer does not exist";
		if( producer == null ) {
			log.error( "signal producer does not exist: " + sourceName );
			return;
		}
		RpDevice dc = producer.getConfiguration();

		String loc = params.get( "signal");
		
		RpMetric wf = RpUtil.getMetricFromStreamID(dc, StreamID.WAVEFORM, loc );
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
			
			dfa = new DetrendedFluctuationProcessor(800);
			// DetrendedFluctuationProcessor dfa = new DetrendedFluctuationProcessor(106083);
			detector.addStreamListener(StreamID.MEASUREMENT, dfa);
			detector.addStreamListener(StreamID.MEASUREMENT, new UpdateNumericField(rriMetricPanel, 1, BeatBlock.SAMPLE_INTERVAL_LOC, 1.0) );
			// dfa.addEventListener( NumericsEvent.class, new UpdateNumericField(rriMetricPanel, 1, "", 1.0) );
			// dfa.addEventListener( NumericsEvent.class, new UpdateNumericField(alphaMetricPanel, 0, "", 1.0) );
			dfa.addStreamListener(StreamID.MEASUREMENT, new UpdateNumericField(alphaMetricPanel, 1, "alpha", 1.0) );
			dfa.addStreamListener(StreamID.MEASUREMENT, new UpdateNumericField(alpha12MetricPanel, 0, "alpha1", 1.0) );
			dfa.addStreamListener(StreamID.MEASUREMENT, new UpdateNumericField(alpha12MetricPanel, 1, "alpha2", 1.0) );

			/*
			 * wire poincare output to respective charts
			 */

			alphaPanel.getChart().setAxisMode(SignalChart.XAxisMode.POINT);
			alphaPanel.getChart().addNumerics(DetrendedFluctuationBlock.ALPHA_LOC, Color.YELLOW, 1, SignalChart.POINT_STYLE);
			dfa.addStreamListener(StreamID.MEASUREMENT, alphaPanel);
			dfa.addStreamListener(StreamID.ALARM, alphaPanel);

			// poincarePlotPanel.getChart().setAxisMode(SignalChart.XAxisMode.POINT);
			// poincarePlotPanel.getChart().addNumerics(PoincareBlock.SD2_LOC, Color.YELLOW, 1, SignalChart.POINT_STYLE);
			// dfa.addEventListener(NumericsEvent.class, poincarePlotPanel);

			alpha1Panel.getChart().setAxisMode(SignalChart.XAxisMode.POINT);
			alpha1Panel.getChart().addNumerics(DetrendedFluctuationBlock.ALPHA1_LOC, Color.YELLOW, 1, SignalChart.POINT_STYLE);
			dfa.addStreamListener(StreamID.MEASUREMENT, alpha1Panel);

			alpha2Panel.getChart().setAxisMode(SignalChart.XAxisMode.POINT);
			alpha2Panel.getChart().addNumerics(DetrendedFluctuationBlock.ALPHA2_LOC, Color.YELLOW, 1, SignalChart.POINT_STYLE);
			dfa.addStreamListener(StreamID.MEASUREMENT, alpha2Panel);
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
		alphaMetricPanel = new TwoValuePanel();
		alphaPanel = new SignalPanel();
		alpha12MetricPanel = new TwoValuePanel();
		alpha1Panel = new SignalPanel();
		alpha2Panel = new SignalPanel();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setLayout(new FormLayout(
			"[80dlu,default], 2*($lcgap, default:grow), $lcgap, default",
			"3*(fill:[50dlu,default], $lgap), default"));

		//---- rriMetricPanel ----
		rriMetricPanel.setUpperTitle("RRI");
		rriMetricPanel.setLowerTitle(" ");
		add(rriMetricPanel, cc.xy(1, 1));

		//---- rriSignalPanel ----
		rriSignalPanel.setName("rri");
		rriSignalPanel.setScaleMinRange(400.0);
		add(rriSignalPanel, cc.xy(3, 1));

		//---- alphaMetricPanel ----
		alphaMetricPanel.setUpperTitle("Alpha");
		alphaMetricPanel.setLowerTitle(" ");
		add(alphaMetricPanel, cc.xy(1, 3));

		//---- alphaPanel ----
		alphaPanel.setName("alpha");
		add(alphaPanel, cc.xy(3, 3));

		//---- alpha12MetricPanel ----
		alpha12MetricPanel.setLowerTitle("Alpha2");
		alpha12MetricPanel.setUpperTitle("Alpha1");
		add(alpha12MetricPanel, cc.xy(1, 5));

		//---- alpha1Panel ----
		alpha1Panel.setName("alpha1");
		add(alpha1Panel, cc.xy(3, 5));

		//---- alpha2Panel ----
		alpha2Panel.setName("alpha2");
		add(alpha2Panel, cc.xy(5, 5));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private TwoValuePanel rriMetricPanel;
	private SignalPanel rriSignalPanel;
	private TwoValuePanel alphaMetricPanel;
	private SignalPanel alphaPanel;
	private TwoValuePanel alpha12MetricPanel;
	private SignalPanel alpha1Panel;
	private SignalPanel alpha2Panel;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	public StreamProducer [] getSignalProducer() {
		StreamProducer[] producers = new StreamProducer [] { dfa } ;

		return producers;
	}
}
