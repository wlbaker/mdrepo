/*
 * Created by JFormDesigner on Wed May 16 11:30:11 CDT 2012
 */

package idea.adapters.gui;

import java.io.IOException;
import java.util.Calendar;
import java.util.Date;

import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;

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
import idea.model.dev.PlumA3Measurement;
import idea.schema.rp.RpDevice;
import lombok.extern.slf4j.Slf4j;

// BETA2: FIXME: Known issue: Data remains on the screen if one pump is still on.
// BETA2: FIXME: Should support the two-channel settings per pump of the PlumA
// BETA2: FIXME: In history recall, only INFUSOR-1 of the three infusors showed a graph / values 

/**
 * @author User #2
 */
@Slf4j
@SuppressWarnings("serial")
public class MultiChannelInfusionPump extends JPanel implements StreamConsumer, RefreshablePanel {

	private static int INFPUMP_HISTORY_JOB = 273; // THIS WILL NOT WORK...consider two cco panels!!!
	private static final int HISTORY_IN_HOURS = 4;

	private static final int BARWIDTH_MINUTES = 5;

	private int nChannels;
	InfusionVerticalPanel[] infs;
	private RpDevice conf;
	private Date dtEnd;

	public MultiChannelInfusionPump(StreamProducer driver, RpDevice conf2, int nChannels) {
		initComponents();

		this.nChannels = nChannels;
		initChannels(nChannels);
		this.conf = conf2;

		if (conf2 == null) {
			portLabel.setText("");
		} else {
			portLabel.setText("" + RpUtil.getConnectionPort(conf) );
			String name = conf2.getName();
			
			if( name.endsWith("1")) {
				INFPUMP_HISTORY_JOB++;
			} else if( name.endsWith("2")) {
				INFPUMP_HISTORY_JOB += 2;
			}
			log.error("FIXME BETA2: fix job id allocations: {}", INFPUMP_HISTORY_JOB );
		}

		reset( driver );
	}
	
	@Override
	public void reset(StreamProducer driver) {
		driver.addStreamListener(StreamID.MEASUREMENT, this);
		driver.addStreamListener(StreamID.CONNECTION, this);
		
		log.error("requesting events from: {}", driver.getConfiguration().getName() );

	}

	@Override
	public void refresh(IDEAClient idea, Date dt) {
		log.debug("retrieve historical data");

		for (InfusionVerticalPanel inf : infs) {
			inf.clear();
			inf.clearHistory();
		}

		Calendar cal = Calendar.getInstance();
		if (dt != null) {
			cal.setTime(dt);
		}
		cal.add(Calendar.HOUR, -HISTORY_IN_HOURS);
		Date dtStart = cal.getTime();
		dtEnd = dt;

		IDEATransferInterface req = idea.createTransferRequest(INFPUMP_HISTORY_JOB, dtStart, dtEnd, conf, 60 * 1000);
		req.addStreamListener(StreamID.MEASUREMENT, this);
		try {
			req.connect();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	private void initChannels(int cnt) {
		String colFormat = "";
		if (cnt > 1) {
			colFormat = (cnt - 1) + "*(default:grow, $lcgap), ";
		}
		colFormat += "default:grow";

		setLayout(new FormLayout(colFormat, "fill:default:grow, 2*($lgap, default)"));

		CellConstraints cc = new CellConstraints();
		int col = 1;
		infs = new InfusionVerticalPanel[cnt];
		for (int i = 0; i < cnt; i++) {
			InfusionVerticalPanel panel = new InfusionVerticalPanel("" + (i + 1));
			add(panel, cc.xy(col, 1));
			col += 2;
			infs[i] = panel;
		}

	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		label1 = new JLabel();
		button1 = new JButton();
		portLabel = new JLabel();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setLayout(new FormLayout("2*(default:grow, $lcgap), default:grow", "fill:default:grow, 2*($lgap, default)"));

		//---- label1 ----
		label1.setText("text");
		add(label1, cc.xy(1, 1));

		//---- button1 ----
		button1.setText("text");
		add(button1, cc.xy(3, 1));

		//---- portLabel ----
		portLabel.setText("Port:");
		add(portLabel, cc.xy(1, 3));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JLabel label1;
	private JButton button1;
	private JLabel portLabel;

	// JFormDesigner - End of variables declaration  //GEN-END:variables

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {

		if (sid == StreamID.ALARM) {
			System.out.println("got alarm: " + item);
		} else if (sid == StreamID.CONNECTION) {
			// ignore

			ConnectionItem ce = (ConnectionItem) item;
			if (ce.getStatus() == ConnectionStatus.NOT_CONNECTED) {
				for (InfusionVerticalPanel inf : infs) {
					inf.clear();
				}
			}

		} else if (sid == StreamID.MEASUREMENT) {

			PlumA3Measurement m = (PlumA3Measurement) item;

			Integer id_n = m.getIdNo();

			if (id_n == null) {
				for (InfusionVerticalPanel inf : infs) {
					inf.clear();
				}
			} else {
				id_n--;
				if (id_n >= infs.length) {
					log.error("INVALID INF ID: {}", id_n);
				} else {

					boolean showNumerics = true;
					InfusionVerticalPanel inf = infs[id_n];
					if ( jobID == INFPUMP_HISTORY_JOB && dtEnd != null ) { 
						long ms = dtEnd.getTime() -  item.getTime();
						showNumerics = ( ms < 5 * 60 * 1000 );
					} else if (jobID == INFPUMP_HISTORY_JOB && dtEnd == null ) {
						showNumerics = false;
					}
					
					if( showNumerics ) {
						inf.setRate(m.getRate1A());
						inf.setVTBD(m.getVtbd1a());
						inf.setVTOT(m.getVtot1a());
						inf.setDrugName(m.getDrugName());
						inf.setStatus(m.getSta());
					}

					Date dt = item.getTm();
					inf.addChart(dt, m.getRate1A(), m.getVtot1a() );
				}
			}
		} else {
			log.error("unexpected event: {}/{}", sid, item);
		}
	}

	@Override
	public void update() {
		for (InfusionVerticalPanel inf : infs) {
			inf.update();
		}
	}

	@Override
	public void clear() {
		for (InfusionVerticalPanel inf : infs) {
			inf.clear();
		}
	}
}
