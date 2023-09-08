/*
 * Created by JFormDesigner on Mon Oct 05 13:52:41 CDT 2009
 */

package idea.ct;

import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.SwingUtilities;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import icuInterface.ConnectionStatus;
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
public class CtEthernetPanel extends JPanel implements CtInterface, StreamConsumer {


	public CtEthernetPanel( ) {
		initComponents();

	}

	public void hideCommSetup() {
		commParms.setVisible(false);
		portLabel.setVisible(false);
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

	public void refresh(DeviceConfiguration dc) {



		if (dc != null) {
			String port_value = dc.getConnectionValue();
		}
	}


	/*
	 * Utility functions that are no longer found in the DeviceConfiguration
	 * class...now RpDevice
	 */

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		panel1 = new JPanel();
		portLabel = new JLabel();
		address = new JTextField();
		commParms = new JComboBox();
		statusMessage = new JLabel();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setLayout(new FormLayout("default:grow", "fill:default:grow"));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout("right:[30dlu,default]:grow, $lcgap, [50dlu,default]",
					"[12dlu,default], 2*($lgap, default), $lgap, default:grow, $lgap, default"));

			//---- portLabel ----
			portLabel.setText("Address:");
			panel1.add(portLabel, cc.xy(1, 3));
			panel1.add(address, cc.xy(3, 3));
			panel1.add(commParms, cc.xy(3, 5));

			//---- statusMessage ----
			statusMessage.setText("??status");
			panel1.add(statusMessage, cc.xywh(1, 9, 3, 1));
		}
		add(panel1, cc.xy(1, 1));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JPanel panel1;
	private JLabel portLabel;
	private JTextField address;
	private JComboBox commParms;
	private JLabel statusMessage;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {

		if (sid == StreamID.CAPABILITIES) {
			// 24 June 2014: Intellivue devices send multiple CAPS messages 
			DeviceConfiguration caps = ((CapabilitiesEvent) item).getCapabilities();
			_refresh((DeviceCapabilities) caps);  // put refresh on the GUI thread
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
			dev.setConnectionType(RpConnType.ETHERNET);
			dev.setConnectionValue(address.getText());
	}

	@Override
	public void handleConnectionEvent(RpDevice conf, AdapterInterface driver, ConnectionStatus status) {
		// TODO Auto-generated method stub
		
	}


}
