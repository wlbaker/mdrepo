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
import javax.swing.JTextField;

import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;
import idea.analysis.event.BeatBlock;
import idea.analysis.event.EntropyBlock;
import idea.analysis.event.MSEBlock;
import idea.chart.SignalChart;
import idea.chart.SignalPanel;
import idea.qrsdet.AbstractDetector;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

/**
 * @author User #2
 */
@Slf4j
@SuppressWarnings("serial")
public class MultiSignalEntropyAnalysisPanel extends JPanel implements AnalysisPanelInterface, StreamConsumer {

	NumberFormat df1 = new DecimalFormat("0.#");
	NumberFormat df2 = new DecimalFormat("0.00");

	String lloc1, lloc2, lloc3, lloc4;

	AbstractDetector detector;
	EntropyFilter ent;
	MultiscaleEntropyProcessor mse;
	
	protected int tick;
	private HRVProcessor hrv;

	public MultiSignalEntropyAnalysisPanel(StreamProducer[] producers, RpAnalysis analConfs) {
		initComponents();

		textPanel.setEditable(false);

		// saentSignalPanel.setVisible( false );
		// mseSignalPanel.setVisible( false );
		// qSignalPanel.setVisible( false );
		// sdSignalPanel.setVisible( false );

		rriMetricPanel.setFormat(df1);
		entMetricPanel.setFormat(df2);
		qMetricPanel.setFormat(df2);
		
		hrvMetricPanel.setFormat( df2 );
		hrv2MetricPanel.setFormat( df2 );

		rriMetricPanel.setUpperValue((Number)null);
		entMetricPanel.clear();
		qMetricPanel.clear();

		// this.conf = analConfs;
		buildPanel(analConfs); // general case...do nothing for this panel

		StreamConsumer[] consumers = new StreamConsumer[2];
		consumers[0] = qSignalPanel;

		labelGraphs();
		wireProducersAndConsumers(producers, consumers, analConfs);
	}

	private void labelGraphs() {
		// rriSignalPanel.setYAxisLabel("RRI");
		// mseSignalPanel.setYAxisLabel("MSE 2/3");
		// saentSignalPanel.setYAxisLabel("SaEnt");
		// qSignalPanel.setYAxisLabel("Q");
		// sdSignalPanel.setYAxisLabel("SD");
	}

	private void wireProducersAndConsumers(StreamProducer[] producers, StreamConsumer[] consumers, RpAnalysis anal) {
		StringStringMap params = anal.getParam();

		if (producers == null || producers.length == 0) {
			System.err.println("NO SIGNAL PRODUCERS");
			// assert( false ) : "No signal producers for analysis.";
			return;
		}

		/*
		 * wire devices output to QRS detector
		 */
		String sourceName1 = params.get( "SIG_DEV1");

		StreamProducer producer1 = getNamedDevice(producers, sourceName1, false);
		if( producer1 == null ) {
			producer1 = getNamedDevice(producers, sourceName1 + "_0", false);
		}
		if( producer1 == null ) {
			log.error("CONFIG ERROR: signal producer does not exist: {}", sourceName1 );
			return;
		}
		if (producer1 == null) {
			System.err.println("NULL PRODUCER in EntropyAnalysisPanel wire: requested producer: " + sourceName1);
			System.err.println("Available producers: ");
			getNamedDevice(producers, sourceName1, true);
			return;
		}
		RpDevice dc1 = producer1.getConfiguration();

		lloc1 = params.get( "SIG1");
		RpMetric wf_desc1 = RpUtil.getMetricFromStreamID(dc1, StreamID.WAVEFORM, lloc1);
		assert (wf_desc1 != null) : "CONFIG ERROR: requested SIG signal not available";

		String sourceName2 = params.get( "SIG_DEV1");

		StreamProducer producer2 = getNamedDevice(producers, sourceName2, false);
		if( producer2 == null ) {
			producer2 = getNamedDevice(producers, sourceName2 + "_0", false);
		}
		if( producer2 == null ) {
			log.error("CONFIG ERROR: signal producer does not exist: {}", sourceName2 );
			return;
		}
		if (producer2 == null) {
			System.err.println("NULL PRODUCER in EntropyAnalysisPanel wire: requested producer: " + sourceName2);
			System.err.println("Available producers: ");
			getNamedDevice(producers, sourceName2, true);
			return;
		}
		RpDevice dc2 = producer2.getConfiguration();

		lloc2 = params.get( "SIG2");
		RpMetric wf_desc2 = RpUtil.getMetricFromStreamID(dc2, StreamID.WAVEFORM, lloc2);
		assert (wf_desc2 != null) : "CONFIG ERROR: requested SIG signal not available";

		String sourceName3 = params.get( "SIG_DEV3");

		StreamProducer producer3 = getNamedDevice(producers, sourceName3, false);
		if( producer3 == null ) {
			producer3 = getNamedDevice(producers, sourceName3 + "_0", false);
		}
		if( producer3 == null ) {
			log.error("CONFIG ERROR: signal producer does not exist: {}", sourceName3 );
			return;
		}
		if (producer3 == null) {
			System.err.println("NULL PRODUCER in EntropyAnalysisPanel wire: requested producer: " + sourceName3);
			System.err.println("Available producers: ");
			getNamedDevice(producers, sourceName3, true);
			return;
		}
		RpDevice dc3 = producer3.getConfiguration();

		lloc3 = params.get( "SIG3");
		RpMetric wf_desc3 = RpUtil.getMetricFromStreamID(dc3, StreamID.WAVEFORM, lloc3);
		assert (wf_desc3 != null) : "CONFIG ERROR: requested SIG signal not available";

		String sourceName4 = params.get( "SIG_DEV4");

		StreamProducer producer4 = getNamedDevice(producers, sourceName4, false);
		if( producer4 == null ) {
			producer4 = getNamedDevice(producers, sourceName4 + "_0", false);
		}
		if( producer4 == null ) {
			log.error("CONFIG ERROR: signal producer does not exist: {}", sourceName4 );
			return;
		}
		if (producer4 == null) {
			System.err.println("NULL PRODUCER in EntropyAnalysisPanel wire: requested producer: " + sourceName4);
			System.err.println("Available producers: ");
			getNamedDevice(producers, sourceName4, true);
			return;
		}
		RpDevice dc4 = producer4.getConfiguration();

		lloc4 = params.get( "SIG4");
		RpMetric wf_desc4 = RpUtil.getMetricFromStreamID(dc4, StreamID.WAVEFORM, lloc4);
		assert (wf_desc4 != null) : "CONFIG ERROR: requested SIG signal not available";



		GuiUtil.showMessage("FIXME: Code cleanup needed for multi-detector analysis -- MULTIW code");
		// detector = DetectorFactory.createDetector("MULTIW", wf_desc1, wf_desc2, wf_desc3, wf_desc4);
		// detector = DetectorFactory.createDetector("AESOP", wf_desc1);
		// detector = new DetectorFusion(wf_desc1.getSampleRate(), "1234");
		// detector = new DetectorMultiParameters(wf_desc1.getSampleRate(), "1234", "1234", wf_desc1, wf_desc2, wf_desc3, wf_desc4);
		// detector = new DetectorMultiParameters(wf_desc1.getSampleRate(), "1234", "1234", lloc1, lloc2, lloc3, lloc4);

		if (detector != null) {
			detector.addStreamListener(StreamID.MEASUREMENT, this);
		}

		if (detector == null) {
			GuiUtil.showMessage("DETECTOR COULD NOT BE CREATED");
			return;
		}

		producer1.addStreamListener(StreamID.WAVEFORM, detector);
		producer1.addStreamListener(StreamID.ALARM, detector);
		producer1.addStreamListener(StreamID.CONNECTION, detector);
		producer2.addStreamListener(StreamID.WAVEFORM, detector);
		producer2.addStreamListener(StreamID.ALARM, detector);
		producer2.addStreamListener(StreamID.CONNECTION, detector);
		producer3.addStreamListener(StreamID.WAVEFORM, detector);
		producer3.addStreamListener(StreamID.ALARM, detector);
		producer3.addStreamListener(StreamID.CONNECTION, detector);
		producer4.addStreamListener(StreamID.WAVEFORM, detector);
		producer4.addStreamListener(StreamID.ALARM, detector);
		producer4.addStreamListener(StreamID.CONNECTION, detector);
		Object logDir = params.get( "logDir");
		if( logDir != null ) {
			detector.setLogDir( logDir.toString() );
		}

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

			hrv = new HRVProcessor( //
					200, // 200 hz from Drager
					200*120, // 200 hz for 120 secs....2 min window
					1024  // resample size...pretty much fixed
					);
			
			detector.addStreamListener(StreamID.MEASUREMENT, hrv);
			hrv.addStreamListener(StreamID.MEASUREMENT, new UpdateNumericField(hrvMetricPanel, 0, "HF"));
			hrv.addStreamListener(StreamID.MEASUREMENT, new UpdateNumericField(hrvMetricPanel, 1, "LF"));
			hrv.addStreamListener(StreamID.MEASUREMENT, new UpdateNumericField(hrv2MetricPanel, 0, "HF_LF"));
			hrv.addStreamListener(StreamID.MEASUREMENT, new UpdateNumericField(hrv2MetricPanel, 1, "LF_HF"));
			
			hrv.addStreamListener(StreamID.ALARM, hfSignalPanel);

			hfSignalPanel.getChart().setAxisMode(SignalChart.XAxisMode.POINT);
			hfSignalPanel.getChart().addNumerics("HF", Color.YELLOW, 1, SignalChart.POINT_STYLE);
			hrv.addStreamListener(StreamID.MEASUREMENT, hfSignalPanel);
			
			lfSignalPanel.getChart().setAxisMode(SignalChart.XAxisMode.POINT);
			lfSignalPanel.getChart().addNumerics("LF", Color.YELLOW, 1, SignalChart.POINT_STYLE);
			hrv.addStreamListener(StreamID.MEASUREMENT, lfSignalPanel);
			
			hflfSignalPanel.getChart().setAxisMode(SignalChart.XAxisMode.POINT);
			hflfSignalPanel.getChart().addNumerics("LF_HF", Color.YELLOW, 1, SignalChart.POINT_STYLE);
			hrv.addStreamListener(StreamID.MEASUREMENT, hflfSignalPanel);
			
			lfhfSignalPanel.getChart().setAxisMode(SignalChart.XAxisMode.POINT);
			lfhfSignalPanel.getChart().addNumerics("HF_LF", Color.YELLOW, 1, SignalChart.POINT_STYLE);
			hrv.addStreamListener(StreamID.MEASUREMENT, lfhfSignalPanel);
			
			hrvMetricPanel.setUpperTitle("hf");
			hrvMetricPanel.setLowerTitle("lf");
			hrv2MetricPanel.setUpperTitle("hf_lf");
			hrv2MetricPanel.setLowerTitle("lf_hf");
			ent = new EntropyFilter(200, 6, 2);
			ent.setRecalcPeriod( 10000 );
			detector.addStreamListener(StreamID.MEASUREMENT, ent);
			detector.addStreamListener(StreamID.MEASUREMENT, new UpdateNumericField(rriMetricPanel, 1,
					BeatBlock.MS_INTERVAL_LOC));

			entMetricPanel.setUpperTitle("-");
			rriMetricPanel.setLowerTitle("rri");
			
			detector.addStreamListener(StreamID.MEASUREMENT, this );
			log.error("Assuming entropy in hundredths!");
			ent.addStreamListener(StreamID.MEASUREMENT, new UpdateNumericField(entMetricPanel, 0, "sampent"));
			ent.addStreamListener(StreamID.MEASUREMENT, new UpdateNumericField(qMetricPanel, 0, "q"));
			ent.addStreamListener(StreamID.MEASUREMENT, new UpdateNumericField(qMetricPanel, 1, "stddev"));

			qMetricPanel.setUpperTitle("q");
			qMetricPanel.setLowerTitle("stddev");
			
			mse = new MultiscaleEntropyProcessor(800, 6, 2);
			mse.setRecalcPeriod( 10000 );
			detector.addStreamListener(StreamID.MEASUREMENT, mse);
			mse.addStreamListener(StreamID.MEASUREMENT, new UpdateNumericField(entMetricPanel, 1,
					MSEBlock.MSECOMPLEXITY_LOC));
			mse.addStreamListener(StreamID.ALARM, mseSignalPanel);
			
			entMetricPanel.setUpperTitle("sampen");
			entMetricPanel.setLowerTitle("mse");

			/*
			 * wire entropy output to saent, quadratic entropy, stddev charts
			 */
			saentSignalPanel.getChart().setAxisMode(SignalChart.XAxisMode.POINT);
			saentSignalPanel.getChart().addNumerics(EntropyBlock.SAMPENT_LOC, Color.YELLOW, 1, SignalChart.POINT_STYLE);
			ent.addStreamListener(StreamID.MEASUREMENT, saentSignalPanel);
			ent.addStreamListener(StreamID.ALARM, saentSignalPanel);

			sdSignalPanel.getChart().setAxisMode(SignalChart.XAxisMode.POINT);
			sdSignalPanel.getChart().addNumerics(EntropyBlock.STDDEV_LOC, Color.YELLOW, 1, SignalChart.POINT_STYLE);
			ent.addStreamListener(StreamID.MEASUREMENT, sdSignalPanel);

			qSignalPanel.getChart().setAxisMode(SignalChart.XAxisMode.POINT);
			qSignalPanel.getChart().addNumerics(EntropyBlock.Q_LOC, Color.YELLOW, 1, SignalChart.POINT_STYLE);
			ent.addStreamListener(StreamID.MEASUREMENT, qSignalPanel);

			mseSignalPanel.getChart().setAxisMode(SignalChart.XAxisMode.POINT);
			mseSignalPanel.getChart().addNumerics("CPLX", MSEBlock.MSECOMPLEXITY_LOC, Color.WHITE, 1, SignalChart.POINT_STYLE);
			mseSignalPanel.getChart().addNumerics("MSE2", MSEBlock.MSE2_LOC, Color.YELLOW, 1, SignalChart.POINT_STYLE);
			mseSignalPanel.getChart().addNumerics("MSE3", MSEBlock.MSE3_LOC, Color.GREEN, 1, SignalChart.POINT_STYLE);
			mseSignalPanel.getChart().addNumerics("MSE4", MSEBlock.MSE4_LOC, Color.RED, 1, SignalChart.POINT_STYLE);
			mseSignalPanel.showLegend( true );
			mse.addStreamListener(StreamID.MEASUREMENT, mseSignalPanel);
			
		}
	}

	private StreamProducer getNamedDevice(StreamProducer[] producers, String sourceName, boolean verbose) {
		if (producers == null) {
			return null;
		}
		if (sourceName == null) {
			System.err.println("MultiSignalEntropyAnalysisPanel: source not specified");
			return null;
		}
		StreamProducer source = null;
		for (StreamProducer intf : producers) {
			RpDevice dc = intf.getConfiguration();
			if (verbose)
				System.err.println("name: " + dc.getName());
			if (dc != null && sourceName.equals(dc.getName())) {
				source = intf;
				break;
			}
			if (intf instanceof MultiplexInterface) {
				MultiplexInterface mintf = (MultiplexInterface) intf;
				if (verbose)
					System.err.println("subinterface begin****");
				source = getNamedDevice(mintf.getSubInterfaces(), sourceName, verbose);
				if (verbose)
					System.err.println("subinterface end****");
			}

			if (source != null) {
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
		textPanel = new JTextField();
		entMetricPanel = new TwoValuePanel();
		saentSignalPanel = new SignalPanel();
		mseSignalPanel = new SignalPanel();
		qMetricPanel = new TwoValuePanel();
		qSignalPanel = new SignalPanel();
		sdSignalPanel = new SignalPanel();
		hrvMetricPanel = new TwoValuePanel();
		hfSignalPanel = new SignalPanel();
		lfSignalPanel = new SignalPanel();
		hrv2MetricPanel = new TwoValuePanel();
		hflfSignalPanel = new SignalPanel();
		lfhfSignalPanel = new SignalPanel();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setLayout(new FormLayout(
			"[80dlu,default], 2*($lcgap, default:grow), $lcgap, default",
			"fill:[50dlu,default], $lgap, default, 2*($lgap, fill:[50dlu,default]), 2*($lgap, fill:default)"));
		add(rriMetricPanel, cc.xy(1, 1));

		//---- rriSignalPanel ----
		rriSignalPanel.setName("rri");
		rriSignalPanel.setScaleMinRange(100.0);
		add(rriSignalPanel, cc.xywh(3, 1, 3, 1));

		//---- textPanel ----
		textPanel.setText("Signal:  ");
		textPanel.setBackground(Color.black);
		textPanel.setForeground(Color.white);
		add(textPanel, cc.xy(1, 3));
		add(entMetricPanel, cc.xy(1, 5));

		//---- saentSignalPanel ----
		saentSignalPanel.setName("saent");
		saentSignalPanel.setScaleMaxY(3.0);
		saentSignalPanel.setScaleMinY(0.0);
		add(saentSignalPanel, cc.xy(3, 5));

		//---- mseSignalPanel ----
		mseSignalPanel.setName("mse");
		mseSignalPanel.setScaleMinY(0.0);
		mseSignalPanel.setScaleMaxY(10.0);
		add(mseSignalPanel, cc.xy(5, 5));
		add(qMetricPanel, cc.xy(1, 7));

		//---- qSignalPanel ----
		qSignalPanel.setName("q");
		qSignalPanel.setScaleMinY(0.0);
		qSignalPanel.setScaleMaxY(6.0);
		add(qSignalPanel, cc.xy(3, 7));

		//---- sdSignalPanel ----
		sdSignalPanel.setName("sd");
		sdSignalPanel.setScaleMinY(0.0);
		sdSignalPanel.setScaleMaxY(30.0);
		add(sdSignalPanel, cc.xy(5, 7));
		add(hrvMetricPanel, cc.xy(1, 9));

		//---- hfSignalPanel ----
		hfSignalPanel.setName("saent");
		hfSignalPanel.setScaleMaxY(50000.0);
		hfSignalPanel.setScaleMinY(0.0);
		add(hfSignalPanel, cc.xy(3, 9));

		//---- lfSignalPanel ----
		lfSignalPanel.setName("saent");
		lfSignalPanel.setScaleMaxY(50000.0);
		lfSignalPanel.setScaleMinY(0.0);
		add(lfSignalPanel, cc.xy(5, 9));
		add(hrv2MetricPanel, cc.xy(1, 11));

		//---- hflfSignalPanel ----
		hflfSignalPanel.setName("saent");
		hflfSignalPanel.setScaleMaxY(3.0);
		hflfSignalPanel.setScaleMinY(0.0);
		add(hflfSignalPanel, cc.xy(3, 11));

		//---- lfhfSignalPanel ----
		lfhfSignalPanel.setName("saent");
		lfhfSignalPanel.setScaleMaxY(3.0);
		lfhfSignalPanel.setScaleMinY(0.0);
		add(lfhfSignalPanel, cc.xy(5, 11));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private TwoValuePanel rriMetricPanel;
	private SignalPanel rriSignalPanel;
	private JTextField textPanel;
	private TwoValuePanel entMetricPanel;
	private SignalPanel saentSignalPanel;
	private SignalPanel mseSignalPanel;
	private TwoValuePanel qMetricPanel;
	private SignalPanel qSignalPanel;
	private SignalPanel sdSignalPanel;
	private TwoValuePanel hrvMetricPanel;
	private SignalPanel hfSignalPanel;
	private SignalPanel lfSignalPanel;
	private TwoValuePanel hrv2MetricPanel;
	private SignalPanel hflfSignalPanel;
	private SignalPanel lfhfSignalPanel;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	@Override
	public void clear() {
		rriMetricPanel.clear();
		rriSignalPanel.clear();
		entMetricPanel.clear();
		qMetricPanel.clear();
		entMetricPanel.clear();
		mseSignalPanel.clear();
		qSignalPanel.clear();
		sdSignalPanel.clear();
		
		hrv.reset();
		ent.reset();
		mse.reset();
	}

	@Override
	public void autoscale() {
		// TODO Auto-generated method stub
		
	}

	@Override
	public StreamProducer [] getSignalProducers() {
		StreamProducer [] producers = new StreamProducer[] { ent, mse, detector };
		return producers;
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

		if (item instanceof BeatBlock) {

			BeatBlock block = (BeatBlock) item;

			int leadId = block.getLead_id();

			switch (leadId) {
			case 0:
				textPanel.setText("Signal:  " + lloc1);
				break;
			case 1:
				textPanel.setText("Signal:  " + lloc2);
				break;
			case 2:
				textPanel.setText("Signal:  " + lloc3);
				break;
			case 3:
				textPanel.setText("Signal:  " + lloc3);
				break;
			default:
				textPanel.setText("Signal:  Unknown");
				System.err.println("LeadId NOT VALID. Unknown Signal");
				break;
			}
		}
	}

}
