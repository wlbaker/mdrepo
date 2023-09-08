/*
 * Created by JFormDesigner on Mon Oct 05 13:52:41 CDT 2009
 */

package idea.ct;

import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.JTextField;
import javax.swing.SwingUtilities;
import javax.swing.table.DefaultTableModel;

import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.factories.DefaultComponentFactory;
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
public class CtIntellivuePanel extends JPanel implements CtInterface, StreamConsumer {


	public CtIntellivuePanel( ) {
		initComponents();

		DefaultTableModel model = (DefaultTableModel) deviceList.getModel();
		model.setRowCount( 0 );
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


	protected void panelToModel(DeviceConfiguration dc) {

		dc.setConnectionType(RpConnType.ETHERNET);

		dc.setConnectionValue(address.getText());
	}

	/*
	 * Utility functions that are no longer found in the DeviceConfiguration
	 * class...now RpDevice
	 */

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		panel1 = new JPanel();
		separator1 = compFactory.createSeparator("Intellivue");
		panel2 = new JPanel();
		portLabel = new JLabel();
		address = new JTextField();
		panel3 = new JPanel();
		scan = new JButton();
		test = new JButton();
		scrollPane1 = new JScrollPane();
		deviceList = new JTable();
		statusMessage = new JLabel();

		//======== this ========
		setLayout(new FormLayout(
			"default:grow",
			"fill:default:grow"));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"[50dlu,default]:grow",
				"[12dlu,default], $lgap, top:default, $lgap, default, $lgap, default:grow, $lgap, default"));
			panel1.add(separator1, CC.xy(1, 1));

			//======== panel2 ========
			{
				panel2.setLayout(new FormLayout(
					"default, $lcgap, default:grow",
					"default, $lgap, top:[12dlu,default]"));

				//---- portLabel ----
				portLabel.setText("Address:");
				panel2.add(portLabel, CC.xy(1, 1));
				panel2.add(address, CC.xy(3, 1));
			}
			panel1.add(panel2, CC.xy(1, 3));

			//======== panel3 ========
			{
				panel3.setLayout(new FormLayout(
					"default, $lcgap, default",
					"default"));

				//---- scan ----
				scan.setText("Discover");
				panel3.add(scan, CC.xy(1, 1));

				//---- test ----
				test.setText("Test");
				panel3.add(test, CC.xy(3, 1));
			}
			panel1.add(panel3, CC.xy(1, 5));

			//======== scrollPane1 ========
			{
				scrollPane1.setViewportView(deviceList);
			}
			panel1.add(scrollPane1, CC.xy(1, 7));

			//---- statusMessage ----
			statusMessage.setText("??status");
			panel1.add(statusMessage, CC.xy(1, 9));
		}
		add(panel1, CC.xy(1, 1));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JPanel panel1;
	private JComponent separator1;
	private JPanel panel2;
	private JLabel portLabel;
	private JTextField address;
	private JPanel panel3;
	private JButton scan;
	private JButton test;
	private JScrollPane scrollPane1;
	private JTable deviceList;
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
		dev.setConnectionType( RpConnType.INTELLIVUE );
		dev.setConnectionValue( address.getText() );
	}

	@Override
	public void handleConnectionEvent(RpDevice conf, AdapterInterface driver, ConnectionStatus status) {
		// TODO Auto-generated method stub
		
	}


}
