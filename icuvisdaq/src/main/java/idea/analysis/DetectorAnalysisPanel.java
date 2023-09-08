/*
 * Created by JFormDesigner on Mon Mar 08 10:06:06 CST 2010
 */

package idea.analysis;

import icuInterface.RpUtil;
import idea.display.simple.TwoValuePanel;
import idea.intf.MultiplexInterface;
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
public class DetectorAnalysisPanel extends JPanel {

	NumberFormat df1 = new DecimalFormat( "0.#");
	StreamProducer [] producers = new StreamProducer[7];
	
	public DetectorAnalysisPanel(StreamProducer[] producers, RpAnalysis analConfs) {
		initComponents();

//		saentSignalPanel.setVisible( false );
//		mseSignalPanel.setVisible( false );
//		qSignalPanel.setVisible( false );
//		sdSignalPanel.setVisible( false );
		
		aesopMetricPanel.setFormat( df1 );
		pt1_pt2Panel.setFormat( df1 );
		cat_fbPanel.setFormat( df1 );
		cl_mobdPanel.setFormat( df1 );
		
		aesopMetricPanel.setUpperValue( null );
		
		wireProducersAndConsumers(producers, analConfs );
		
		aesopPanel.getChart().showSummary( true );
		pt1Panel.getChart().showSummary( true );
		pt2Panel.getChart().showSummary( true );
		catPanel.getChart().showSummary( true );
		fbPanel.getChart().showSummary( true );
		clPanel.getChart().showSummary( true );
		mobdPanel.getChart().showSummary( true );
	}

	private void wireProducersAndConsumers(StreamProducer[] producers, RpAnalysis anal) {
		StringStringMap params = anal.getParam();
		
		if( producers == null || producers.length == 0 ) {
			System.err.println( "NO SIGNAL PRODUCERS");
			// assert( false ) : "No signal producers for analysis.";
			return;
		}

		/*
		 * wire device0 output to QRS detector
		 */
		String sourceName = params.get( "DEV");
		
		StreamProducer producer = getNamedDevice( producers, sourceName );
		if( producer == null ) {
			producer = getNamedDevice( producers, sourceName + "_0");
		}
		assert( producer != null ) : "CONFIG ERROR: signal producer does not exist";
		if( producer == null ) {
			log.error( "CONFIG ERROR: signal producer does not exist: " + sourceName );
			return;
		}
		
		RpDevice dc = producer.getConfiguration();

		String loc = params.get( "signal");
		RpMetric wf = RpUtil.getMetricFromStreamID(dc, StreamID.WAVEFORM, loc );
		assert( wf != null ) : "CONFIG ERROR: requested ECG signal not available";
		
		
		AbstractDetector detector = wireOneDetector( "AESOP", aesopPanel, producer, wf, aesopMetricPanel, 1, 1.0, 0 );
		detector.addStreamListener(StreamID.MEASUREMENT, new UpdateNumericField(aesopMetricPanel, 0, BeatBlock.DET_ID_LOC, 1) );
		
		wireOneDetector( "PT1", pt1Panel, producer, wf, pt1_pt2Panel, 0, 5.0, 1 );
		wireOneDetector( "PT2", pt2Panel, producer, wf, pt1_pt2Panel, 1, 5.0, 2 );
		wireOneDetector( "CAT", catPanel, producer, wf, cat_fbPanel, 0, 5.0, 3 );
		wireOneDetector( "FB", fbPanel, producer, wf, cat_fbPanel, 1, 5.0, 4 );
		wireOneDetector( "CL", clPanel, producer, wf, cl_mobdPanel, 0, 5.0, 5 );
		wireOneDetector( "MOBD", mobdPanel, producer, wf, cl_mobdPanel, 1, 5.0, 6 );
	}

	private AbstractDetector wireOneDetector(String detector_name, SignalPanel trendPanel, StreamProducer producer, RpMetric wf, TwoValuePanel metricPanel, int mpidx, double mult, int idx ) {
		
		AbstractDetector detector = DetectorFactory.createDetector( detector_name, wf );
		producers[idx++] = detector;
		
		if( detector == null ){
			GuiUtil.showMessage("DETECTOR NOT FOUND: " + detector_name );
			return null;
		}

		trendPanel.setYAxisLabel(detector_name);
		trendPanel.setYLabelRotation( true );
		producer.addStreamListener(StreamID.WAVEFORM, detector);
		producer.addStreamListener(StreamID.ALARM, detector);
		producer.addStreamListener(StreamID.CONNECTION, detector);

		/*
		 * wire qrs detector output to RRI signal chart
		 */

		trendPanel.getChart().setAxisMode(SignalChart.XAxisMode.POINT);
		trendPanel.getChart().addNumerics(BeatBlock.MS_INTERVAL_LOC, Color.YELLOW, 1, SignalChart.POINT_STYLE);
		detector.addStreamListener(StreamID.MEASUREMENT, trendPanel);
		
		detector.addStreamListener(StreamID.MEASUREMENT, new UpdateNumericField(metricPanel, mpidx, BeatBlock.MS_INTERVAL_LOC, 1) );
		// detector.addEventListener(RWaveEvent.class, new UpdateNumericField(metricPanel, mpidx, BeatBlock.SAMPLE_INTERVAL_LOC, mult) );

		return detector;
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

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		aesopMetricPanel = new TwoValuePanel();
		aesopPanel = new SignalPanel();
		pt1_pt2Panel = new TwoValuePanel();
		pt1Panel = new SignalPanel();
		pt2Panel = new SignalPanel();
		cat_fbPanel = new TwoValuePanel();
		catPanel = new SignalPanel();
		fbPanel = new SignalPanel();
		cl_mobdPanel = new TwoValuePanel();
		clPanel = new SignalPanel();
		mobdPanel = new SignalPanel();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setLayout(new FormLayout(
			"[80dlu,default], 2*($lcgap, default:grow), $lcgap, default",
			"3*(fill:[50dlu,default], $lgap), fill:default, $lgap, default"));

		//---- aesopMetricPanel ----
		aesopMetricPanel.setLowerTitle(" AESOP-RRI");
		aesopMetricPanel.setUpperTitle("AESOP-Quality");
		add(aesopMetricPanel, cc.xy(1, 1));

		//---- aesopPanel ----
		aesopPanel.setName("rri");
		aesopPanel.setScaleMinRange(200.0);
		add(aesopPanel, cc.xywh(3, 1, 3, 1));

		//---- pt1_pt2Panel ----
		pt1_pt2Panel.setLowerTitle("RRI-PT2");
		pt1_pt2Panel.setUpperTitle("RRI-PT1");
		add(pt1_pt2Panel, cc.xy(1, 3));

		//---- pt1Panel ----
		pt1Panel.setName("saent");
		pt1Panel.setScaleMinRange(200.0);
		add(pt1Panel, cc.xy(3, 3));

		//---- pt2Panel ----
		pt2Panel.setName("mse");
		pt2Panel.setScaleMinRange(200.0);
		add(pt2Panel, cc.xy(5, 3));

		//---- cat_fbPanel ----
		cat_fbPanel.setLowerTitle("RRI-FB");
		cat_fbPanel.setUpperTitle("RRI-CAT");
		add(cat_fbPanel, cc.xy(1, 5));

		//---- catPanel ----
		catPanel.setName("q");
		catPanel.setScaleMinRange(200.0);
		add(catPanel, cc.xy(3, 5));

		//---- fbPanel ----
		fbPanel.setName("sd");
		fbPanel.setScaleMinRange(200.0);
		add(fbPanel, cc.xy(5, 5));

		//---- cl_mobdPanel ----
		cl_mobdPanel.setLowerTitle("RRI-MOBD");
		cl_mobdPanel.setUpperTitle("RRI-CL");
		add(cl_mobdPanel, cc.xy(1, 7));

		//---- clPanel ----
		clPanel.setName("q");
		clPanel.setScaleMinRange(200.0);
		add(clPanel, cc.xy(3, 7));

		//---- mobdPanel ----
		mobdPanel.setName("q");
		mobdPanel.setScaleMinRange(200.0);
		add(mobdPanel, cc.xy(5, 7));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private TwoValuePanel aesopMetricPanel;
	private SignalPanel aesopPanel;
	private TwoValuePanel pt1_pt2Panel;
	private SignalPanel pt1Panel;
	private SignalPanel pt2Panel;
	private TwoValuePanel cat_fbPanel;
	private SignalPanel catPanel;
	private SignalPanel fbPanel;
	private TwoValuePanel cl_mobdPanel;
	private SignalPanel clPanel;
	private SignalPanel mobdPanel;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	public StreamProducer [] getSignalProducers() {
		return producers;
	}
}
