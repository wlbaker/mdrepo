/*
 * Created by JFormDesigner on Thu Mar 18 15:01:05 CDT 2010
 */

package idea.adapters.gui;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.io.IOException;
import java.util.Calendar;
import java.util.Date;

import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.SwingConstants;
import javax.swing.border.EmptyBorder;

import org.jfree.chart.ChartPanel;
import org.jfree.chart.plot.XYPlot;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import icuInterface.ConnectionStatus;
import icuInterface.RpUtil;
import icuInterface.events.ConnectionItem;
import idea.display.RefreshablePanel;
import idea.intf.IDEAClient;
import idea.intf.IDEATransferInterface;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.model.dev.KangarooResult;
import lombok.extern.slf4j.Slf4j;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpStream;
import idea.schema.rp.RpUnit;

/**
 * @author User #2
 */
@Slf4j
@SuppressWarnings("serial")
public class CovidienKangarooEPumpPanel extends JPanel implements StreamConsumer, RefreshablePanel {

	private static final int EPUMP_HISTORY_JOB = 163; // THIS WILL NOT WORK...consider two cco panels!!!
	private static final int HISTORY_IN_HOURS = 24;

	private static final int BARWIDTH_MINUTES = 10;

	CombinedRateVolumeChart chart;
	int currHour = 0;
	private RpDevice conf;
	private int alt;
	private ChartPanel p0;
	private static int debug_req = 0;

	public CovidienKangarooEPumpPanel(StreamProducer driver, RpDevice conf) {
		initComponents();
		this.conf = conf;

		makeChart();

		if (conf != null) {
			modelLabel.setText("Model: " + conf.getModelName());
			statusMessage.setText("Port: " + RpUtil.getConnectionPort(conf));
		}

		RpStream stream = RpUtil.getStream(conf, StreamID.MEASUREMENT);
		setUOM(uomFeedRate, IntfUtil.getMetricByLoc(stream, KangarooResult.FEED_RATE));
		setUOM(uomFeedTotal, IntfUtil.getMetricByLoc(stream, KangarooResult.FEED_TOTAL));
		setUOM(uomFeedVTBD, IntfUtil.getMetricByLoc(stream, KangarooResult.FEED_VTBD));
		// setUOM( uomFeedRemaining,
		// conf.getMetricDescription(KangarooDataBlock.FEED_REMAINING));

		setUOM(uomBolusRate, IntfUtil.getMetricByLoc(stream, KangarooResult.FEED_RATE));
		setUOM(uomBolusTotal, IntfUtil.getMetricByLoc(stream, KangarooResult.FEED_TOTAL));
		setUOM(uomBolusIVL, IntfUtil.getMetricByLoc(stream, KangarooResult.BOLUS_IVL));

		setUOM(uomFlushVol, IntfUtil.getMetricByLoc(stream, KangarooResult.FLUSH_TOTAL));
		setUOM(uomFlushFreq, IntfUtil.getMetricByLoc(stream, KangarooResult.FLUSH_IVL));

		reset(driver);
	}

	@Override
	public void reset(StreamProducer driver) {
		driver.addStreamListener(null, this);
	}

	private void makeChart() {
		if (p0 != null) {
			chart1Panel.remove(p0);
		}
		chart = initChart("Covidien Kangaroo ePump");
		chart.debug = log.isDebugEnabled();

		// portLabel.setText( "??BARD??" );

		p0 = new ChartPanel(chart.getChart());
		p0.setPreferredSize(new Dimension(100, 200));
		chart1Panel.add(p0, BorderLayout.CENTER);

		XYPlot volumePlot = chart.getVolumePlot();
		volumePlot.getRangeAxis().setUpperBound(4100.0);
		volumePlot.getRangeAxis().setLowerBound(0);
		volumePlot.getRangeAxis().setAutoRange(false);

		// add a second dataset and renderer...

		XYPlot ratePlot = chart.getRatePlot();
		ratePlot.getRangeAxis().setUpperBound(100.0);
		ratePlot.getRangeAxis().setLowerBound(0);
		ratePlot.getRangeAxis().setAutoRange(false);
	}

	@Override
	public void refresh(IDEAClient idea, Date dt) {

		// makeChart();
		chart.clear();

		Calendar cal = Calendar.getInstance();
		if (dt != null) {
			cal.setTime(dt);
		}
		cal.add(Calendar.HOUR, -HISTORY_IN_HOURS);
		Date dtStart = cal.getTime();
		Date dtEnd = dt;

		debug_req = 0;
		log.debug("retrieve from {} to {}", dtStart, dtEnd);
		IDEATransferInterface req = idea.createTransferRequest(EPUMP_HISTORY_JOB, dtStart, dtEnd, conf, 10 * 60 * 1000);
		req.addStreamListener(StreamID.MEASUREMENT, this);
		try {
			req.connect();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	private void setUOM(JLabel uom, RpMetric md) {
		RpUnit unit = (md == null) ? null : md.getUnit();
		uom.setVisible(unit != null);
		uom.setText((unit == null) ? "" : unit.getUnitName());
	}

	private static CombinedRateVolumeChart initChart(String title) {
		CombinedRateVolumeChart chart = new CombinedRateVolumeChart(); // createChart(info);

		chart.getChart().setTitle(title);
		chart.getChart().removeLegend();

		chart.setDomainInMinutes(HISTORY_IN_HOURS * 60);
		return chart;
	}

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {

		try {
			_signalEvent(jobID, source, sid, item);
		} catch (Exception e) {
			log.error("Covidien Kangaroo Error", e);
		}
	}

	private void _signalEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {

		// log.debug("event: {}", event );

		if (sid == StreamID.MEASUREMENT) {
			KangarooResult block = (KangarooResult) item;

			setStatus(block.getPumpStatus());

			if (jobID == EPUMP_HISTORY_JOB) {
				// don't update numerics values for history events
			} else {
				feedRate.setText(_t(block.getFeedRate()));
				feedTOTAL.setText(_t(block.getFeedTotal()));
				feedVTBD.setText(_t(block.getFeedVTBD()));

				flushVol.setText(_t(block.getFlushVTBD()));
				flushFreq.setText(_t(block.getFlushIVL()));

				bolusRate.setText(_t(block.getFeedRate()));
				bolusTotal.setText(_t(block.getFeedVTBD()));
				bolusInterval.setText(_t(block.getBolusIVL()));
				if (alt == 0) {
					bolusesFedLabel.setText("Boluses Fed:");
					bolusesFedOUM.setText("");
					bolusNum.setText(_t(block.getFeedTotal()));
					alt = 1;
				} else {
					bolusesFedLabel.setText("Bolus Flush:");
					bolusesFedOUM.setText("ml");
					bolusNum.setText(_t(block.getFlushTotal()));
					alt = 0;
				}
			}

			Date dt = new Date(block.getTime());
			Calendar cal = Calendar.getInstance();
			cal.setTime(dt);
			cal.set(Calendar.SECOND, 0);
			cal.set(Calendar.MILLISECOND, 0);
			int unroundedMinutes = cal.get(Calendar.MINUTE);
			int mod = unroundedMinutes % BARWIDTH_MINUTES;
			int min = unroundedMinutes + (BARWIDTH_MINUTES - mod);

			cal.set(Calendar.MINUTE, min);
			dt = cal.getTime();

			Integer rate = block.getFeedRate();
			Integer vol = block.getFeedTotal();

			int series = 0;
			if (min > (60 - BARWIDTH_MINUTES))
				series = 1;

			if (log.isDebugEnabled() && debug_req < 10) {
				debug_req++;
				log.debug(" [" + source + "] --> chart " + chart.hashCode() + ": {} at {}", vol, dt);
			}

			chart.add10MinData(series, dt, rate, vol);

		} else if (sid == StreamID.CONNECTION) {
			ConnectionItem ce = (ConnectionItem) item;
			statusMessage.setText(ce.getConnectInfo());
			if (ce.getStatus() == ConnectionStatus.NOT_CONNECTED) {
				clear();
			}
		}
	}

	private final static int RUNNING_MASK = 0x0001;
	private final static int BOLUSMODE_MASK = 0x0002;
	private final static int KTO_MASK = 0x0020;
	private final static int ACPOWER_MASK = 0x0200;
	private final static int CHARGING_MASK = 0x0400;

	private void setStatus(Integer status_value) {

		int status;
		if (status_value == null) {
			bolusPanel.setVisible(false);
			feedPanel.setVisible(false);
			flushPanel.setVisible(false);
			modeLabel.setText("[OFFLINE]");
			statusLabel.setText("");

			return;
		} else {
			status = status_value.intValue();
		}
		if ((status & RUNNING_MASK) == 0) {
			modeLabel.setText("Not Running");
		} else {
			modeLabel.setText("Running"); //: 0x" + Integer.toHexString(status) );
			if ((status & BOLUSMODE_MASK) == BOLUSMODE_MASK) {
				if ((status & KTO_MASK) == KTO_MASK) {
					statusLabel.setText("KTO/Resume");
					showBolusFields(true);
				} else {
					statusLabel.setText("Intermittent");
					showBolusFields(true);
				}
			} else {
				statusLabel.setText("Continuous");
				if ((status & KTO_MASK) == KTO_MASK) {
					statusLabel.setText("KTO/Continuous");
					showBolusFields(true);
				}
				showBolusFields(false);
			}
		}

	}

	private void showBolusFields(boolean b) {
		bolusPanel.setVisible(b);
		feedPanel.setVisible(!b);
	}

	private String _t(Object val) {
		String rt_val = "";
		if (val == null) {
			rt_val = "?";
		} else if (val instanceof Number) {
			Number value = (Number) val;
			rt_val = value.toString();
		} else {
			rt_val = val.toString();
		}
		return rt_val;
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		chart1Panel = new JPanel();
		panel1 = new JPanel();
		modeLabel = new JLabel();
		statusLabel = new JLabel();
		feedPanel = new JPanel();
		label2 = new JLabel();
		feedRate = new JLabel();
		uomFeedRate = new JLabel();
		label1 = new JLabel();
		feedTOTAL = new JLabel();
		uomFeedTotal = new JLabel();
		label3 = new JLabel();
		feedVTBD = new JLabel();
		uomFeedVTBD = new JLabel();
		bolusPanel = new JPanel();
		label4 = new JLabel();
		bolusRate = new JLabel();
		uomBolusRate = new JLabel();
		label6 = new JLabel();
		bolusTotal = new JLabel();
		uomBolusTotal = new JLabel();
		label7 = new JLabel();
		bolusInterval = new JLabel();
		uomBolusIVL = new JLabel();
		bolusesFedLabel = new JLabel();
		bolusNum = new JLabel();
		bolusesFedOUM = new JLabel();
		flushPanel = new JPanel();
		label5 = new JLabel();
		flushVol = new JLabel();
		uomFlushVol = new JLabel();
		label8 = new JLabel();
		flushFreq = new JLabel();
		uomFlushFreq = new JLabel();
		modelLabel = new JLabel();
		statusMessage = new JLabel();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setLayout(new FormLayout("default:grow, $lcgap, [90dlu,default]", "default, $lgap, fill:default:grow"));

		//======== chart1Panel ========
		{
			chart1Panel.setLayout(new BorderLayout());
		}
		add(chart1Panel, cc.xy(1, 3));

		//======== panel1 ========
		{
			panel1.setBorder(new EmptyBorder(5, 5, 5, 5));
			panel1.setLayout(new FormLayout("default:grow",
					"3*(default, $lgap), top:default, $lgap, fill:default:grow, 2*($lgap, default)"));

			//---- modeLabel ----
			modeLabel.setText("Running/Stopped");
			modeLabel.setFont(modeLabel.getFont().deriveFont(modeLabel.getFont().getSize() + 11f));
			modeLabel.setHorizontalAlignment(SwingConstants.CENTER);
			panel1.add(modeLabel, cc.xy(1, 1));

			//---- statusLabel ----
			statusLabel.setText("continuous/intermittent");
			statusLabel.setHorizontalAlignment(SwingConstants.CENTER);
			panel1.add(statusLabel, cc.xy(1, 3));

			//======== feedPanel ========
			{
				feedPanel.setLayout(new FormLayout("[50dlu,default], $lcgap, [30dlu,default], $lcgap, 20dlu",
						"3*(default, $lgap), default"));

				//---- label2 ----
				label2.setText("Feed Rate:");
				label2.setHorizontalAlignment(SwingConstants.RIGHT);
				feedPanel.add(label2, cc.xy(1, 3));

				//---- feedRate ----
				feedRate.setText("---");
				feedRate.setHorizontalAlignment(SwingConstants.RIGHT);
				feedPanel.add(feedRate, cc.xy(3, 3));

				//---- uomFeedRate ----
				uomFeedRate.setText("fr");
				feedPanel.add(uomFeedRate, cc.xy(5, 3));

				//---- label1 ----
				label1.setText("Feed Total:");
				label1.setHorizontalAlignment(SwingConstants.TRAILING);
				feedPanel.add(label1, cc.xy(1, 5));

				//---- feedTOTAL ----
				feedTOTAL.setText("---");
				feedTOTAL.setHorizontalAlignment(SwingConstants.RIGHT);
				feedPanel.add(feedTOTAL, cc.xy(3, 5));

				//---- uomFeedTotal ----
				uomFeedTotal.setText("ft");
				feedPanel.add(uomFeedTotal, cc.xy(5, 5));

				//---- label3 ----
				label3.setText("Feed VTBD:");
				label3.setHorizontalAlignment(SwingConstants.TRAILING);
				feedPanel.add(label3, cc.xy(1, 7));

				//---- feedVTBD ----
				feedVTBD.setText("---");
				feedVTBD.setHorizontalAlignment(SwingConstants.RIGHT);
				feedPanel.add(feedVTBD, cc.xy(3, 7));

				//---- uomFeedVTBD ----
				uomFeedVTBD.setText("ftbd");
				feedPanel.add(uomFeedVTBD, cc.xy(5, 7));
			}
			panel1.add(feedPanel, cc.xy(1, 5));

			//======== bolusPanel ========
			{
				bolusPanel.setLayout(new FormLayout("[50dlu,default]:grow, $lcgap, [30dlu,default], $lcgap, 20dlu",
						"5*(default, $lgap), default"));

				//---- label4 ----
				label4.setText("Bolus Rate:");
				label4.setHorizontalAlignment(SwingConstants.RIGHT);
				bolusPanel.add(label4, cc.xy(1, 3));

				//---- bolusRate ----
				bolusRate.setText("---");
				bolusRate.setHorizontalAlignment(SwingConstants.RIGHT);
				bolusPanel.add(bolusRate, cc.xy(3, 3));

				//---- uomBolusRate ----
				uomBolusRate.setText("fr");
				bolusPanel.add(uomBolusRate, cc.xy(5, 3));

				//---- label6 ----
				label6.setText("Bolus:");
				label6.setHorizontalAlignment(SwingConstants.RIGHT);
				bolusPanel.add(label6, cc.xy(1, 5));

				//---- bolusTotal ----
				bolusTotal.setText("---");
				bolusTotal.setHorizontalAlignment(SwingConstants.RIGHT);
				bolusPanel.add(bolusTotal, cc.xy(3, 5));

				//---- uomBolusTotal ----
				uomBolusTotal.setText("fr");
				bolusPanel.add(uomBolusTotal, cc.xy(5, 5));

				//---- label7 ----
				label7.setText("Bolus Interval:");
				label7.setHorizontalAlignment(SwingConstants.RIGHT);
				bolusPanel.add(label7, cc.xy(1, 7));

				//---- bolusInterval ----
				bolusInterval.setText("---");
				bolusInterval.setHorizontalAlignment(SwingConstants.RIGHT);
				bolusPanel.add(bolusInterval, cc.xy(3, 7));

				//---- uomBolusIVL ----
				uomBolusIVL.setText("fr");
				bolusPanel.add(uomBolusIVL, cc.xy(5, 7));

				//---- bolusesFedLabel ----
				bolusesFedLabel.setText("Boluses Fed:");
				bolusesFedLabel.setHorizontalAlignment(SwingConstants.RIGHT);
				bolusPanel.add(bolusesFedLabel, cc.xy(1, 9));

				//---- bolusNum ----
				bolusNum.setText("---");
				bolusNum.setHorizontalAlignment(SwingConstants.RIGHT);
				bolusPanel.add(bolusNum, cc.xy(3, 9));

				//---- bolusesFedOUM ----
				bolusesFedOUM.setText("fr");
				bolusPanel.add(bolusesFedOUM, cc.xy(5, 9));
			}
			panel1.add(bolusPanel, cc.xy(1, 7));

			//======== flushPanel ========
			{
				flushPanel.setLayout(new FormLayout("[50dlu,default], $lcgap, [30dlu,default], $lcgap, 20dlu",
						"3*(default, $lgap), default:grow"));

				//---- label5 ----
				label5.setText("Flush Vol:");
				label5.setHorizontalAlignment(SwingConstants.RIGHT);
				flushPanel.add(label5, cc.xy(1, 3));

				//---- flushVol ----
				flushVol.setText("---");
				flushVol.setHorizontalAlignment(SwingConstants.RIGHT);
				flushPanel.add(flushVol, cc.xy(3, 3));

				//---- uomFlushVol ----
				uomFlushVol.setText("ur");
				flushPanel.add(uomFlushVol, cc.xy(5, 3));

				//---- label8 ----
				label8.setText("Flush Freq:");
				label8.setHorizontalAlignment(SwingConstants.RIGHT);
				flushPanel.add(label8, cc.xy(1, 5));

				//---- flushFreq ----
				flushFreq.setText("---");
				flushFreq.setHorizontalAlignment(SwingConstants.RIGHT);
				flushPanel.add(flushFreq, cc.xy(3, 5));

				//---- uomFlushFreq ----
				uomFlushFreq.setText("tv");
				flushPanel.add(uomFlushFreq, cc.xy(5, 5));
			}
			panel1.add(flushPanel, cc.xy(1, 9));

			//---- modelLabel ----
			modelLabel.setText("Model:");
			modelLabel.setHorizontalAlignment(SwingConstants.RIGHT);
			panel1.add(modelLabel, cc.xy(1, 11));

			//---- statusMessage ----
			statusMessage.setText("COM???");
			statusMessage.setHorizontalAlignment(SwingConstants.RIGHT);
			panel1.add(statusMessage, cc.xy(1, 13));
		}
		add(panel1, cc.xy(3, 3));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JPanel chart1Panel;
	private JPanel panel1;
	private JLabel modeLabel;
	private JLabel statusLabel;
	private JPanel feedPanel;
	private JLabel label2;
	private JLabel feedRate;
	private JLabel uomFeedRate;
	private JLabel label1;
	private JLabel feedTOTAL;
	private JLabel uomFeedTotal;
	private JLabel label3;
	private JLabel feedVTBD;
	private JLabel uomFeedVTBD;
	private JPanel bolusPanel;
	private JLabel label4;
	private JLabel bolusRate;
	private JLabel uomBolusRate;
	private JLabel label6;
	private JLabel bolusTotal;
	private JLabel uomBolusTotal;
	private JLabel label7;
	private JLabel bolusInterval;
	private JLabel uomBolusIVL;
	private JLabel bolusesFedLabel;
	private JLabel bolusNum;
	private JLabel bolusesFedOUM;
	private JPanel flushPanel;
	private JLabel label5;
	private JLabel flushVol;
	private JLabel uomFlushVol;
	private JLabel label8;
	private JLabel flushFreq;
	private JLabel uomFlushFreq;
	private JLabel modelLabel;
	private JLabel statusMessage;

	// JFormDesigner - End of variables declaration //GEN-END:variables

	@Override
	public void update() {
		chart.update();
	}

	@Override
	public void clear() {
		feedRate.setText("---");
		feedTOTAL.setText("---");
		feedVTBD.setText("---");

		flushVol.setText("---");
		flushFreq.setText("---");

		bolusRate.setText("---");
		bolusTotal.setText("---");
		bolusInterval.setText("---");
	}

}
