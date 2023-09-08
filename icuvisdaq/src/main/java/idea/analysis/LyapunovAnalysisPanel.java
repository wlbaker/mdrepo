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
import idea.model.PersistentItem;
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


class DebugConsumer implements StreamConsumer  {

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {
		System.out.println( "lya event: " + item );
	}

}

/**
 * @author User #2
 */
@Slf4j
@SuppressWarnings("serial")
public class LyapunovAnalysisPanel extends JPanel implements AnalysisPanelInterface, StreamConsumer {

	NumberFormat df0 = new DecimalFormat( "0");
	NumberFormat df2 = new DecimalFormat( "0.00");
	
	LyaProcessor lya;
	
	public LyapunovAnalysisPanel(StreamProducer[] producers, RpAnalysis analConfs) {
		initComponents();

		rriMetricPanel.setFormat( df0 );
		lyaMetricPanel.setFormat( df2 );
		
		rriMetricPanel.setUpperValue( null );
		
		StreamConsumer[] consumers = new StreamConsumer[1];
		consumers[0] = lyaSignalPanel;

		wireProducersAndConsumers(producers, consumers, analConfs );
		
		rriSignalPanel.getChart().showSummary( true );
	}

	private void wireProducersAndConsumers(StreamProducer[] producers, StreamConsumer[] consumers, RpAnalysis anal) {
		StringStringMap params = anal.getParam();
		
		if( producers == null || producers.length == 0 ) {
			log.error( "NO SIGNAL PRODUCERS");
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
		assert( producer != null ) : "CONFIG ERROR: signal producer does not exist";
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
		rriSignalPanel.getChart().addNumerics(BeatBlock.MS_INTERVAL_LOC, Color.YELLOW, 1, SignalChart.POINT_STYLE);
		detector.addStreamListener(StreamID.MEASUREMENT, rriSignalPanel);
		
		detector.addStreamListener(StreamID.MEASUREMENT, this );

		/*
		 * wire qrs detector output to entropy processsor
		 */

		boolean do_all = true;

		if (do_all) {
			
			int pts = 512;
			int slidingWindow = 50;
			int m = 2;
			int J = 1;
			int W = 10;
			lya = new LyaProcessor( pts, 1.0, slidingWindow, pts / 6, m, W, J, BeatBlock.MS_INTERVAL_LOC );

			detector.addStreamListener(StreamID.MEASUREMENT, lya);
			detector.addStreamListener(StreamID.MEASUREMENT, new UpdateNumericField(rriMetricPanel, 1, BeatBlock.MS_INTERVAL_LOC, 1.0) );
			lya.addStreamListener(StreamID.MEASUREMENT, new UpdateNumericField(lyaMetricPanel, 0, "lya", 1.0) );
			lya.addStreamListener(StreamID.MEASUREMENT, new UpdateNumericField(lyaMetricPanel, 1, "asym", 1.0) );
			// lya.addEventListener( NumericsEvent.class, new DebugConsumer() );
			

			/*
			 * wire entropy output to saent, quadratic entropy, stddev charts
			 */
			lyaSignalPanel.getChart().setAxisMode(SignalChart.XAxisMode.POINT);
			lyaSignalPanel.getChart().addNumerics("lya", Color.YELLOW, 1, SignalChart.POINT_STYLE);
			lya.addStreamListener(StreamID.MEASUREMENT, lyaSignalPanel);
			lya.addStreamListener(StreamID.ALARM, lyaSignalPanel);
			
			asymSignalPanel.getChart().setAxisMode(SignalChart.XAxisMode.POINT);
			asymSignalPanel.getChart().addNumerics("asym", Color.YELLOW, 1, SignalChart.POINT_STYLE);
			lya.addStreamListener(StreamID.MEASUREMENT, asymSignalPanel);

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

	public void clear() {
		rriMetricPanel.clear();
		lyaMetricPanel.clear();
		
		rriSignalPanel.clear();
		lyaSignalPanel.clear();
		asymSignalPanel.clear();
		
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		rriMetricPanel = new TwoValuePanel();
		rriSignalPanel = new SignalPanel();
		lyaMetricPanel = new TwoValuePanel();
		lyaSignalPanel = new SignalPanel();
		asymSignalPanel = new SignalPanel();
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
		rriSignalPanel.setScaleMinRange(400.0);
		rriSignalPanel.setDisplayDataPoints(512);
		add(rriSignalPanel, cc.xywh(3, 1, 3, 1));

		//---- lyaMetricPanel ----
		lyaMetricPanel.setLowerTitle("Asymptote");
		lyaMetricPanel.setUpperTitle("Lyapunov");
		add(lyaMetricPanel, cc.xy(1, 3));

		//---- lyaSignalPanel ----
		lyaSignalPanel.setName("saent");
		lyaSignalPanel.setScaleMinY(0.0);
		lyaSignalPanel.setScaleMaxY(3.0);
		add(lyaSignalPanel, cc.xy(3, 3));

		//---- asymSignalPanel ----
		asymSignalPanel.setName("mse");
		asymSignalPanel.setScaleMinY(0.0);
		asymSignalPanel.setScaleMaxY(3.0);
		add(asymSignalPanel, cc.xy(5, 3));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private TwoValuePanel rriMetricPanel;
	private SignalPanel rriSignalPanel;
	private TwoValuePanel lyaMetricPanel;
	private SignalPanel lyaSignalPanel;
	private SignalPanel asymSignalPanel;
	// JFormDesigner - End of variables declaration //GEN-END:variables
	private int tick;

	public StreamProducer [] getSignalProducers() {
		StreamProducer [] producers = new StreamProducer[1];
		producers[0] = lya;
		return producers;
	}

	@Override
	public void autoscale() {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void tick() {
		tick++;
		if( tick > 20 ) {
			clear();
		}
	}

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {
		tick = 0;
	}


}
