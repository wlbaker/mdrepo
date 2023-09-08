/*
 * Created by JFormDesigner on Mon Oct 05 13:52:41 CDT 2009
 */

package idea.ct;

import java.awt.Dimension;
import java.awt.event.ActionEvent;

import javax.swing.DefaultComboBoxModel;
import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;

import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.layout.FormLayout;

import icuInterface.ConnectionStatus;
import icuInterface.RpUtil;
import icuInterface.events.CapabilitiesEvent;
import icuInterface.events.ConnectionItem;
import idea.conf.DeviceCapabilities;
import idea.conf.DeviceConfiguration;
import idea.intf.AdapterInterface;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.PersistentItem;
import idea.schema.rp.RpConnType;
import idea.schema.rp.RpDevice;
import lombok.extern.slf4j.Slf4j;

/**
 * @author User #2
 */
@Slf4j
@SuppressWarnings("serial")
public class CtApiMCCUL extends JPanel implements CtInterface, StreamConsumer {

	public final static String CT_FREQ = "CT_FREQ";
	public final static String CT_FIRSTCH = "CT_FIRSTCH";
	public final static String CT_LASTCH = "CT_LASTCH";
	
	public CtApiMCCUL() {
		initComponents();

	}

	private void _refresh(final DeviceCapabilities caps) {
		// put it on the GUI thread
		try {
			if (SwingUtilities.isEventDispatchThread()) {
				refresh(caps);
			} else {
				SwingUtilities.invokeAndWait(new Runnable() {

					@Override
					public void run() {
						refresh(caps);
					}
				});
			}
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public void refresh(RpDevice dc) {

		if (dc != null) {
			gain.setSelectedItem(RpUtil.getParam(dc, "gain"));
			hzz.setSelectedItem(RpUtil.getParam(dc, "hzz"));
			firstCh.setSelectedItem(RpUtil.getParam(dc, "low-chan"));
			lastCh.setSelectedItem(RpUtil.getParam(dc, "high-chan"));
		}
		
		hzzActionPerformed( null );
		lastChActionPerformed(null);
		firstChActionPerformed(null);

	}

	private void hzzActionPerformed(ActionEvent e) {
		this.putClientProperty( CT_FREQ, hzz.getSelectedItem() );
	}

	private void lastChActionPerformed(ActionEvent e) {
		this.putClientProperty( CT_FIRSTCH, firstCh.getSelectedItem() );
	}

	private void firstChActionPerformed(ActionEvent e) {
		this.putClientProperty( CT_LASTCH, lastCh.getSelectedItem() );
	}

	/*
	 * Utility functions that are no longer found in the DeviceConfiguration
	 * class...now RpDevice
	 */

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		panel1 = new JPanel();
		label2 = new JLabel();
		firstCh = new JComboBox<>();
		label3 = new JLabel();
		lastCh = new JComboBox<>();
		label4 = new JLabel();
		hzz = new JComboBox<>();
		label1 = new JLabel();
		gain = new JComboBox<>();
		statusMessage = new JLabel();

		//======== this ========
		setLayout(new FormLayout(
			"default:grow",
			"fill:default:grow"));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"right:[30dlu,default]:grow, $lcgap, [30dlu,default]",
				"[12dlu,default], 4*($lgap, default), $lgap, default:grow, $lgap, default"));

			//---- label2 ----
			label2.setText("First Channel:");
			panel1.add(label2, CC.xy(1, 3));

			//---- firstCh ----
			firstCh.setMinimumSize(new Dimension(28, 28));
			firstCh.setModel(new DefaultComboBoxModel<>(new String[] {
				"0",
				"1",
				"2",
				"3",
				"4",
				"5",
				"6",
				"7",
				"8",
				"9",
				"10",
				"11",
				"12",
				"13",
				"14",
				"15"
			}));
			firstCh.addActionListener(e -> firstChActionPerformed(e));
			panel1.add(firstCh, CC.xy(3, 3));

			//---- label3 ----
			label3.setText("Last Channel:");
			panel1.add(label3, CC.xy(1, 5));

			//---- lastCh ----
			lastCh.setMinimumSize(new Dimension(28, 28));
			lastCh.setModel(new DefaultComboBoxModel<>(new String[] {
				"0",
				"1",
				"2",
				"3",
				"4",
				"5",
				"6",
				"7",
				"8",
				"9",
				"10",
				"11",
				"12",
				"13",
				"14",
				"15"
			}));
			lastCh.addActionListener(e -> lastChActionPerformed(e));
			panel1.add(lastCh, CC.xy(3, 5));

			//---- label4 ----
			label4.setText("Frequency:");
			panel1.add(label4, CC.xy(1, 7));

			//---- hzz ----
			hzz.setMinimumSize(new Dimension(28, 28));
			hzz.setModel(new DefaultComboBoxModel<>(new String[] {
				"50",
				"100",
				"250",
				"500"
			}));
			hzz.addActionListener(e -> hzzActionPerformed(e));
			panel1.add(hzz, CC.xy(3, 7));

			//---- label1 ----
			label1.setText("Gain:");
			panel1.add(label1, CC.xy(1, 9));

			//---- gain ----
			gain.setModel(new DefaultComboBoxModel<>(new String[] {
				"1",
				"10",
				"50",
				"100",
				"500",
				"1000"
			}));
			panel1.add(gain, CC.xy(3, 9));

			//---- statusMessage ----
			statusMessage.setText("??status");
			panel1.add(statusMessage, CC.xywh(1, 13, 3, 1));
		}
		add(panel1, CC.xy(1, 1));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JPanel panel1;
	private JLabel label2;
	private JComboBox<String> firstCh;
	private JLabel label3;
	private JComboBox<String> lastCh;
	private JLabel label4;
	private JComboBox<String> hzz;
	private JLabel label1;
	private JComboBox<String> gain;
	private JLabel statusMessage;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {

		if (sid == StreamID.CAPABILITIES) {
			// 24 June 2014: Intellivue devices send multiple CAPS messages
			DeviceConfiguration caps = ((CapabilitiesEvent) item).getCapabilities();
			_refresh((DeviceCapabilities) caps); // put refresh on the GUI
													// thread
		}
		if (sid == StreamID.CONNECTION) {
			ConnectionItem e = (ConnectionItem) item;
			ConnectionStatus status = e.getStatus();
			log.error("FIXME: probably need something here");
		}
	}

	@Override
	public void init(RpDevice dev) throws Exception {
		// TODO Auto-generated method stub

	}

	@Override
	public void release() {
		// TODO Auto-generated method stub

	}

	@Override
	public void panelToModel(RpDevice dev) {
		dev.setConnectionType(RpConnType.MCCUL);
		RpUtil.setParam(dev, "gain", (String) gain.getSelectedItem());
		RpUtil.setParam(dev, "hzz", (String) hzz.getSelectedItem());
		RpUtil.setParam(dev, "low-chan", (String) firstCh.getSelectedItem());
		RpUtil.setParam(dev, "high-chan", (String) lastCh.getSelectedItem());
	}

	@Override
	public void handleConnectionEvent(RpDevice conf, AdapterInterface driver, ConnectionStatus status) {
		// TODO Auto-generated method stub

	}

	public int getFirstChannel() {
		String ch = (String) firstCh.getSelectedItem();
		if( ch == null ) return 0;
		
		return Integer.parseInt(ch);
	}

	public int getLastChannel() {
		String ch = (String) lastCh.getSelectedItem();
		if( ch == null ) return 0;
		
		return Integer.parseInt(ch);
	}

}
