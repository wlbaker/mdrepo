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
import idea.model.PersistentItem;
import idea.model.dev.CriticoreMeasurement;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpStream;
import idea.schema.rp.RpUnit;
import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;

/**
 * @author User #2
 */
@Slf4j
@SuppressWarnings("serial")
public class BardUrimeterPanel extends JPanel implements StreamConsumer, RefreshablePanel {

	private static final int BARD_HISTORY_JOBID = 182; // THIS WILL NOT WORK...consider two bard panels!!!

	private static final int HISTORY_IN_HOURS = 24;

	private static final int BARWIDTH_MINUTES = 10;

	CombinedRateVolumeChart chart;
	int currHour = 0;

	private String deviceName;

	private RpDevice conf;

	private StreamProducer driver;

	public BardUrimeterPanel(StreamProducer ddriver, RpDevice conf) {
		initComponents();

		this.conf = conf;
		this.driver = ddriver;
		deviceName = conf.getName();

		chart = initChart("BARD Urimeter: " + deviceName);

		ChartPanel p0 = new ChartPanel(chart.getChart());
		p0.setPreferredSize(new Dimension(100, 200));
		chart1Panel.add(p0, BorderLayout.CENTER);

		XYPlot volumePlot = chart.getVolumePlot();
		volumePlot.getRangeAxis().setUpperBound(2100.0);
		volumePlot.getRangeAxis().setLowerBound(0);
		volumePlot.getRangeAxis().setAutoRange(false);

		// add a second dataset and renderer...

		XYPlot ratePlot = chart.getRatePlot();
		ratePlot.getRangeAxis().setUpperBound(100.0);
		ratePlot.getRangeAxis().setLowerBound(0);
		ratePlot.getRangeAxis().setAutoRange(false);

		if (conf != null) {
			RpStream stream = RpUtil.getStream(conf, StreamID.MEASUREMENT);
			String port = RpUtil.getConnectionPort(conf);
			String model = conf.getModelName();
			if (model == null || model.startsWith("?")) {
				model = "Criticore";
			}
			modelLabel.setText("Model: " + model);
			if (port == null) {
				port = "Disconnected";
			}
			portLabel.setText("Port: " + port);

			setUOM(uomUO, RpUtil.getMetricFromStream(stream, CriticoreMeasurement.BARD_UO));
			setUOM(uomRate, RpUtil.getMetricFromStream(stream, CriticoreMeasurement.BARD_RATE));
			setUOM(uomVol, RpUtil.getMetricFromStream(stream, CriticoreMeasurement.BARD_VOL));
			setUOM(uomPrior, RpUtil.getMetricFromStream(stream, CriticoreMeasurement.BARD_PVOL));
		}
		reset(driver);

	}

	@Override
	public void reset(StreamProducer driver) {
		driver.addStreamListener(StreamID.MEASUREMENT, this);
		driver.addStreamListener(StreamID.CONNECTION, this);
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

		log.debug("got event: {}", item);
		try {
			_signalEvent(jobID, source, sid, item);
		} catch (Exception e) {
			log.error("signal exception", e);
			GuiUtil.showError("Bard Error", e);
		}
	}

	private void _signalEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {
		if (sid == StreamID.MEASUREMENT) {
			CriticoreMeasurement block = (CriticoreMeasurement) item;

			if (jobID == BARD_HISTORY_JOBID) {
				// don't update numerics values for history events
			} else {
				currentTime.setText(_t(block.getCurrentTime()));
				urineOutput.setText(_t(block.getCurrentOutput()));
				urineRate.setText(_t(block.getRatePerHour()));
				totalVolume.setText(_t(block.getTotalVolume()));
				priorOutput.setText(_t(block.getPriorOutput()));
				priorTime.setText(_t(block.getPriorTime()));
			}
			if (log.isDebugEnabled()) {
				log.debug("block tm=" + block.getTm());
				log.debug("block curr_tm=" + block.getCurrentTime());
				log.debug("block uo=" + block.getTotalVolume());
			}
			/*
			 * round date to 5-min marker
			 */
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

			Integer rate = block.getRatePerHour();
			Integer vol = block.getTotalVolume();

			int series = 0;
			if (min > (60 - BARWIDTH_MINUTES))
				series = 1;

			chart.add10MinData(series, dt, rate, vol);

		} else if (sid == StreamID.CONNECTION) {
			ConnectionItem ce = (ConnectionItem) item;
			if (ce.getStatus() == ConnectionStatus.NOT_CONNECTED) {
				clear();
			}
		}
	}

	private String _t(Object val) {
		String rt_val = "";
		if( val != null ) {
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
		panel2 = new JPanel();
		label2 = new JLabel();
		currentTime = new JLabel();
		label4 = new JLabel();
		urineOutput = new JLabel();
		uomUO = new JLabel();
		label5 = new JLabel();
		urineRate = new JLabel();
		uomRate = new JLabel();
		label8 = new JLabel();
		totalVolume = new JLabel();
		uomVol = new JLabel();
		label10 = new JLabel();
		priorOutput = new JLabel();
		uomPrior = new JLabel();
		label12 = new JLabel();
		priorTime = new JLabel();
		modelLabel = new JLabel();
		portLabel = new JLabel();
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
			panel1.setLayout(new FormLayout("default:grow", "default, $lgap, top:default:grow, 2*($lgap, default)"));

			//======== panel2 ========
			{
				panel2.setLayout(new FormLayout("default:grow, $lcgap, [30dlu,default], $lcgap, 20dlu",
						"5*(default, $lgap), [22dlu,default], $lgap, default, $lgap, default:grow, $lgap, default"));

				//---- label2 ----
				label2.setText("Current Time:");
				label2.setHorizontalAlignment(SwingConstants.RIGHT);
				panel2.add(label2, cc.xy(1, 3));

				//---- currentTime ----
				currentTime.setText("---");
				currentTime.setHorizontalAlignment(SwingConstants.RIGHT);
				panel2.add(currentTime, cc.xy(3, 3));

				//---- label4 ----
				label4.setText("Urine Output:");
				label4.setHorizontalAlignment(SwingConstants.RIGHT);
				panel2.add(label4, cc.xy(1, 5));

				//---- urineOutput ----
				urineOutput.setText("---");
				urineOutput.setHorizontalAlignment(SwingConstants.RIGHT);
				panel2.add(urineOutput, cc.xy(3, 5));

				//---- uomUO ----
				uomUO.setText("uo");
				panel2.add(uomUO, cc.xy(5, 5));

				//---- label5 ----
				label5.setText("Urine Rate:");
				label5.setHorizontalAlignment(SwingConstants.RIGHT);
				panel2.add(label5, cc.xy(1, 7));

				//---- urineRate ----
				urineRate.setText("---");
				urineRate.setHorizontalAlignment(SwingConstants.RIGHT);
				panel2.add(urineRate, cc.xy(3, 7));

				//---- uomRate ----
				uomRate.setText("ur");
				panel2.add(uomRate, cc.xy(5, 7));

				//---- label8 ----
				label8.setText("Total Volume:");
				label8.setHorizontalAlignment(SwingConstants.RIGHT);
				panel2.add(label8, cc.xy(1, 9));

				//---- totalVolume ----
				totalVolume.setText("---");
				totalVolume.setHorizontalAlignment(SwingConstants.RIGHT);
				panel2.add(totalVolume, cc.xy(3, 9));

				//---- uomVol ----
				uomVol.setText("tv");
				panel2.add(uomVol, cc.xy(5, 9));

				//---- label10 ----
				label10.setText("Prior Hour Output:");
				label10.setHorizontalAlignment(SwingConstants.RIGHT);
				panel2.add(label10, cc.xy(1, 13));

				//---- priorOutput ----
				priorOutput.setText("---");
				priorOutput.setHorizontalAlignment(SwingConstants.RIGHT);
				panel2.add(priorOutput, cc.xy(3, 13));

				//---- uomPrior ----
				uomPrior.setText("puo");
				panel2.add(uomPrior, cc.xy(5, 13));

				//---- label12 ----
				label12.setText("Prior Time:");
				label12.setHorizontalAlignment(SwingConstants.RIGHT);
				panel2.add(label12, cc.xy(1, 15));

				//---- priorTime ----
				priorTime.setText("---");
				priorTime.setHorizontalAlignment(SwingConstants.RIGHT);
				panel2.add(priorTime, cc.xy(3, 15));
			}
			panel1.add(panel2, cc.xy(1, 3));

			//---- modelLabel ----
			modelLabel.setText("Model:");
			modelLabel.setHorizontalAlignment(SwingConstants.RIGHT);
			panel1.add(modelLabel, cc.xy(1, 5));

			//---- portLabel ----
			portLabel.setText("COM???");
			portLabel.setHorizontalAlignment(SwingConstants.RIGHT);
			panel1.add(portLabel, cc.xy(1, 7));
		}
		add(panel1, cc.xy(3, 3));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JPanel chart1Panel;
	private JPanel panel1;
	private JPanel panel2;
	private JLabel label2;
	private JLabel currentTime;
	private JLabel label4;
	private JLabel urineOutput;
	private JLabel uomUO;
	private JLabel label5;
	private JLabel urineRate;
	private JLabel uomRate;
	private JLabel label8;
	private JLabel totalVolume;
	private JLabel uomVol;
	private JLabel label10;
	private JLabel priorOutput;
	private JLabel uomPrior;
	private JLabel label12;
	private JLabel priorTime;
	private JLabel modelLabel;
	private JLabel portLabel;

	// JFormDesigner - End of variables declaration //GEN-END:variables

	@Override
	public void refresh(IDEAClient idea, Date dt) {
		log.debug("attempting to retrieve historical data");

		chart.clear();
		Calendar cal = Calendar.getInstance();
		if (dt != null) {
			cal.setTime(dt);
		}
		cal.add(Calendar.HOUR, -HISTORY_IN_HOURS);
		Date dtStart = cal.getTime();
		Date dtEnd = dt;

		IDEATransferInterface req = idea.createTransferRequest(BARD_HISTORY_JOBID, dtStart, dtEnd, conf, 10 * 60 * 1000);
		req.addStreamListener(StreamID.MEASUREMENT, this);
		try {
			req.connect();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	@Override
	public void update() {
		chart.update();
	}

	@Override
	public void clear() {
		currentTime.setText("---");
		urineOutput.setText("---");
		urineRate.setText("---");
		totalVolume.setText("---");
		priorOutput.setText("---");
		priorTime.setText("---");
	}

}
