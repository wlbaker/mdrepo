/*
 * Created by JFormDesigner on Thu Mar 18 15:01:05 CDT 2010
 */

package idea.adapters.gui;

import java.awt.*;
import java.awt.BorderLayout;
import java.awt.Dimension;
import java.io.IOException;
import java.util.Calendar;
import java.util.Date;

import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.SwingConstants;
import javax.swing.border.*;
import javax.swing.border.EmptyBorder;
import com.jgoodies.forms.factories.*;

import org.jfree.chart.ChartPanel;
import org.jfree.chart.plot.XYPlot;
import org.pistax.model.IMP731_breath;
import org.pistax.model.IMP731_status;

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
import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpStream;
import idea.schema.rp.RpUnit;

/**
 * @author User #2
 */
@Slf4j
@SuppressWarnings("serial")
public class NewportHT70Panel extends JPanel implements StreamConsumer, RefreshablePanel {

	private static final int HISTORY_JOBID = 99;
	private static final int HISTORY_IN_HOURS = 24;

	private static final int BARWIDTH_MINUTES = 5;

	CombinedRateVolumeChart chart;
	int currHour = 0;

	private String deviceName;

	private StreamProducer driver;
	private RpDevice conf;

	public NewportHT70Panel(StreamProducer ddriver, RpDevice conf) {
		initComponents();

		this.conf = conf;
		this.driver = ddriver;
		deviceName = conf.getName();

		chart = initChart(deviceName);

		ChartPanel p0 = new ChartPanel(chart.getChart());
		p0.setPreferredSize(new Dimension(100, 200));
		chart1Panel.add(p0, BorderLayout.CENTER);

		XYPlot volumePlot = chart.getVolumePlot();
		volumePlot.getRangeAxis().setUpperBound(800.0);
		volumePlot.getRangeAxis().setLowerBound(0);
		volumePlot.getRangeAxis().setAutoRange(false);

		// add a second dataset and renderer...

		XYPlot ratePlot = chart.getRatePlot();
		ratePlot.getRangeAxis().setUpperBound(30.0);
		ratePlot.getRangeAxis().setLowerBound(0);
		ratePlot.getRangeAxis().setAutoRange(false);

		if (conf != null) {
			RpStream stream = RpUtil.getStream(conf, StreamID.MEASUREMENT);
			String port = RpUtil.getConnectionPort(conf);
			String model = conf.getModelName();

			// setUOM(uomUO, RpUtil.getMetricFromStream(stream, CriticoreMeasurement.BARD_UO));
		}
		reset(driver);

		clear();
	}

	@Override
	public void reset(StreamProducer driver) {
		driver.addStreamListener(StreamID.MEASUREMENT, this);
		driver.addStreamListener(StreamID.SETTINGS, this);
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
			GuiUtil.showError(conf.getName(), e);
		}
	}

	private void _signalEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {
		if (sid == StreamID.SETTINGS) {
			IMP731_status block = (IMP731_status) item;

			if (jobID == HISTORY_JOBID) {
				// don't update numerics values for history events
			} else {
				// currentTime.setText(_t(block.getTm()));
				double dFIO2 = block.getFio2() / 10.0;
				fio2.setText( _t(dFIO2) );
				pip.setText(_t(block.getPhi() ));
				vt.setText(_t(block.getTv() ));
				bpm.setText(_t(block.getBr() ));
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

			int series = 0;
			if (min > (60 - BARWIDTH_MINUTES))
				series = 1;

			double dBR = block.getBr();
			double dTV = block.getTv();
			
			// System.out.println("updating chart: " + dBR + "," + dTV );
			chart.add5MinData(series, dt, dBR, dTV);

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
		chart1Panel = new JPanel();
		panel1 = new JPanel();
		panel3 = new JPanel();
		panel4 = new JPanel();
		label1 = new JLabel();
		fio2 = new JLabel();
		panel5 = new JPanel();
		panel6 = new JPanel();
		label2 = new JLabel();
		pip = new JLabel();
		panel7 = new JPanel();
		panel8 = new JPanel();
		label5 = new JLabel();
		vt = new JLabel();
		panel9 = new JPanel();
		panel10 = new JPanel();
		label7 = new JLabel();
		bpm = new JLabel();

		//======== this ========
		setLayout(new FormLayout(
			"default:grow, $lcgap, [90dlu,default]",
			"fill:default:grow"));

		//======== chart1Panel ========
		{
			chart1Panel.setLayout(new BorderLayout());
		}
		add(chart1Panel, CC.xy(1, 1));

		//======== panel1 ========
		{
			panel1.setBorder(new EmptyBorder(5, 5, 5, 5));
			panel1.setLayout(new FormLayout(
				"default:grow",
				"3*(fill:default:grow, $lgap), fill:default:grow"));

			//======== panel3 ========
			{
				panel3.setBorder(new LineBorder(Color.blue, 2));
				panel3.setLayout(new FormLayout(
					"default:grow",
					"default, $lgap, default"));

				//======== panel4 ========
				{
					panel4.setLayout(new FormLayout(
						"default, $lcgap, default",
						"default"));

					//---- label1 ----
					label1.setText("FiO2");
					panel4.add(label1, CC.xy(1, 1));
				}
				panel3.add(panel4, CC.xy(1, 1));

				//---- fio2 ----
				fio2.setText("<value>");
				fio2.setHorizontalAlignment(SwingConstants.CENTER);
				fio2.setFont(new Font("Dialog", Font.BOLD, 22));
				panel3.add(fio2, CC.xy(1, 3));
			}
			panel1.add(panel3, CC.xy(1, 1));

			//======== panel5 ========
			{
				panel5.setBorder(new LineBorder(Color.blue, 2));
				panel5.setLayout(new FormLayout(
					"default:grow",
					"default, $lgap, default"));

				//======== panel6 ========
				{
					panel6.setLayout(new FormLayout(
						"default, $lcgap, default",
						"default"));

					//---- label2 ----
					label2.setText("PIP");
					panel6.add(label2, CC.xy(1, 1));
				}
				panel5.add(panel6, CC.xy(1, 1));

				//---- pip ----
				pip.setText("<value>");
				pip.setHorizontalAlignment(SwingConstants.CENTER);
				pip.setFont(new Font("Dialog", Font.BOLD, 22));
				panel5.add(pip, CC.xy(1, 3));
			}
			panel1.add(panel5, CC.xy(1, 3));

			//======== panel7 ========
			{
				panel7.setBorder(new LineBorder(Color.blue, 2));
				panel7.setLayout(new FormLayout(
					"default:grow",
					"default, $lgap, default"));

				//======== panel8 ========
				{
					panel8.setLayout(new FormLayout(
						"default, $lcgap, default",
						"default"));

					//---- label5 ----
					label5.setText("Vt");
					panel8.add(label5, CC.xy(1, 1));
				}
				panel7.add(panel8, CC.xy(1, 1));

				//---- vt ----
				vt.setText("<value>");
				vt.setHorizontalAlignment(SwingConstants.CENTER);
				vt.setFont(new Font("Dialog", Font.BOLD, 22));
				panel7.add(vt, CC.xy(1, 3));
			}
			panel1.add(panel7, CC.xy(1, 5));

			//======== panel9 ========
			{
				panel9.setBorder(new LineBorder(Color.blue, 2));
				panel9.setLayout(new FormLayout(
					"default:grow",
					"default, $lgap, default"));

				//======== panel10 ========
				{
					panel10.setLayout(new FormLayout(
						"default, $lcgap, default",
						"default"));

					//---- label7 ----
					label7.setText("BPM");
					panel10.add(label7, CC.xy(1, 1));
				}
				panel9.add(panel10, CC.xy(1, 1));

				//---- bpm ----
				bpm.setText("<value>");
				bpm.setHorizontalAlignment(SwingConstants.CENTER);
				bpm.setFont(new Font("Dialog", Font.BOLD, 22));
				panel9.add(bpm, CC.xy(1, 3));
			}
			panel1.add(panel9, CC.xy(1, 7));
		}
		add(panel1, CC.xy(3, 1));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JPanel chart1Panel;
	private JPanel panel1;
	private JPanel panel3;
	private JPanel panel4;
	private JLabel label1;
	private JLabel fio2;
	private JPanel panel5;
	private JPanel panel6;
	private JLabel label2;
	private JLabel pip;
	private JPanel panel7;
	private JPanel panel8;
	private JLabel label5;
	private JLabel vt;
	private JPanel panel9;
	private JPanel panel10;
	private JLabel label7;
	private JLabel bpm;
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

	}

	@Override
	public void update() {
		chart.update();
	}

	@Override
	public void clear() {
		fio2.setText("---");
		pip.setText("---");
		vt.setText("---");
		bpm.setText("---");
	}

}
