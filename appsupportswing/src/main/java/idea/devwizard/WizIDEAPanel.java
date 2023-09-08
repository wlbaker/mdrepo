/*
 * Created by JFormDesigner on Wed Oct 07 11:45:32 CDT 2009
 */

package idea.devwizard;

import java.awt.Component;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.util.List;

import javax.swing.JButton;
import javax.swing.JFormattedTextField;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTabbedPane;
import javax.swing.SwingUtilities;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import icuInterface.ConnectionStatus;
import icuInterface.RpUtil;
import icuInterface.conf.dev.SocketDeviceConfiguration;
import icuInterface.events.CapabilitiesEvent;
import icuInterface.events.ConnectionItem;
import icuInterface.events.SecurityEvent;
import idea.conf.DeviceCapabilities;
import idea.conf.DeviceConfiguration;
import idea.conf.DeviceFactory;
import idea.intf.IDEAClient;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.PersistentItem;
import idea.schema.rp.RpConnType;
import idea.schema.rp.RpDevice;
import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;
import idea.gui.WizardMasterInterface;
import idea.gui.WizardPanelInterface;

/**
 * @author User #2
 */
@Slf4j
@SuppressWarnings("serial")
public class WizIDEAPanel extends JPanel implements WizardPanelInterface, StreamConsumer {
	private RpDevice dc;
	private StreamProducer driver;
	private WizardMasterInterface wiz;

	public WizIDEAPanel(WizardMasterInterface wiz, RpDevice dev_conf) {
		this.dc = dev_conf;
		this.wiz = wiz;

		initComponents();

		String ip = null;
		if (dev_conf != null) {
			ip = dev_conf.getConnectionValue();
		}
		
		ip = "tcp://127.0.0.1";
		log.error("FIXME: remove hardcoded tcp://127.0.0.1");
		
		if (ip != null) {
			ipAddressField.setText(ip);
		}
		
		authMessage.setText("");
		wiz.enableNext( false );

		// GuiUtil.initTable(signalTable);

		// initTable(signalTable);

	}

	public void refresh() {
		tabber.removeAll();
		
		try {
			connect.setEnabled( false );
			_refresh();
			
		} catch (IOException e) {
			GuiUtil.showError("UDP/IDEA Device", e);
			connect.setEnabled( true );
		}
	}

	private void _refresh() throws IOException {


		SocketDeviceConfiguration conf = new SocketDeviceConfiguration(this.getClass() ); // IDEAClient.createConfigInstance();
		String ip = ipAddressField.getText();
		if (ip == null || ip.length() == 0) {
			// maybe put a message on the screen?
			return;
		}
		authMessage.setText("Connecting: " + ip);
		conf.setHost( ip );
		conf.setDeviceClass("idea.zeromq.subscriber.ZeroMQClient");
		//conf.setPort( IDEAClient.DEFAULT_IDEA_UDP_PORT );
		// conf.setPort( )
		driver = DeviceFactory.createDriver(conf);
		
		if( driver == null ) {
			GuiUtil.showMessage("Could not create interface: " + conf.getDeviceClass() );
			return;
		}

		driver.addStreamListener(StreamID.CONNECTION, this);
		driver.addStreamListener(StreamID.CAPABILITIES, this);
		driver.addStreamListener(StreamID.SECURITY, this );

		((IDEAClient)driver).start();;
		((IDEAClient)driver).requestLogin(0, "userid", "password");
		((IDEAClient)driver).requestCapabilities();
	}

	private void showCapabilities(DeviceConfiguration deviceConfiguration) {
		tabber.removeAll();

		GuiUtil.showMessage("FIXME: show Capabilities in WizIDEAPanel");
//		RpMetric[] metrics = deviceConfiguration.getMetrics();
//		WaveformDescription[] waves = deviceConfiguration.getWaveforms();
//		if ((metrics != null && metrics.length > 0) || (waves != null && waves.length > 0)) {
//
//			// UNEXPECTED, but possible
//			addOneCapability(null, deviceConfiguration);
//		}

		List<RpDevice> subcaps = deviceConfiguration.getDevices();
		if (subcaps != null && subcaps.size() > 0) {
			List<RpDevice> confs = null;

			if (dc != null) {
				confs = dc.getDevices();
			}

			for (int idx = 0; idx < subcaps.size(); idx++) {
				RpDevice subcap = subcaps.get(idx);
				RpDevice conf = null;
				if (confs != null) {
					if (idx < confs.size()) {
						conf = confs.get(idx);
					} else {
						conf = new RpDevice();
						confs.add(conf);
					}
				}
				System.err.println("NEED A BETTER WAY TO MATCH UP CONFS");

				addOneCapability(conf, (DeviceCapabilities) subcap);
			}
		}
	}

	private void addOneCapability(final RpDevice conf, final RpDevice deviceConfiguration) {

		Runnable r = new Runnable() {

			@Override
			public void run() {
				String name = deviceConfiguration.getName();
				if (name == null || name.length() == 0) {
					name = "device";
				}
				if( conf != null ) {
					conf.setName(name);
					conf.setDeviceClass( deviceConfiguration.getDeviceClass() );
					conf.setModelName( deviceConfiguration.getModelName() );
					conf.setDriverName( deviceConfiguration.getDriverName() );
				}
				GuiUtil.showMessage("THIS IS WHY THIS SHOULD BE A STREAMADAPTERPANEL");
				JPanel panel = new JPanel();
				//WizGenericSerialPanel panel = new WizGenericSerialPanel(wiz, conf, null, null);
				//panel.hideCommSetup();
				//panel.hideDeviceName();

				//panel.refresh(deviceConfiguration);
				tabber.add(name, panel);
			}

		};

		try {
			SwingUtilities.invokeAndWait(r);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (InvocationTargetException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	private void connectActionPerformed(ActionEvent e) {
		refresh();
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		panel1 = new JPanel();
		label1 = new JLabel();
		ipAddressField = new JFormattedTextField();
		connect = new JButton();
		tabber = new JTabbedPane();
		authMessage = new JLabel();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setLayout(new FormLayout(
			"default:grow",
			"default, $lgap, fill:default:grow, $lgap, default"));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"default, $lcgap, [150dlu,default], $lcgap, [50dlu,default], $lcgap, default:grow",
				"default"));

			//---- label1 ----
			label1.setText("IP Address:");
			panel1.add(label1, cc.xy(1, 1));
			panel1.add(ipAddressField, cc.xy(3, 1));

			//---- connect ----
			connect.setText("Connect");
			connect.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					connectActionPerformed(e);
				}
			});
			panel1.add(connect, cc.xy(5, 1));
		}
		add(panel1, cc.xy(1, 1));
		add(tabber, cc.xy(1, 3));

		//---- authMessage ----
		authMessage.setText("text");
		add(authMessage, cc.xy(1, 5));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JPanel panel1;
	private JLabel label1;
	private JFormattedTextField ipAddressField;
	private JButton connect;
	private JTabbedPane tabber;
	private JLabel authMessage;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	protected void panelToModel() {
		if (dc == null) {
			dc = new RpDevice();
		} else {
			RpUtil.resetDC(dc);
		}

		// ? dc.setDeviceClass( driver.getClass().getCanonicalName() );
		dc.setConnectionType(RpConnType.ETHERNET);

		GuiUtil.showMessage("FIXME: saving disabled");
		for (int idx = 0; idx < tabber.getTabCount(); idx++) {
			Component comp = tabber.getComponentAt(idx);
//			WizGenericSerialPanel panel = (WizGenericSerialPanel) comp;
//			panel.panelToModel();
		}

		dc.setConnectionValue(ipAddressField.getText());
		dc.setName("IDEA");

	}

	@Override
	public boolean next() {

		panelToModel();
		// !! wizard.popPageUntil("Hardware Setup");
		
		return true;

	}

	@Override
	public boolean finish() {
		return true;
	}

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {

		if (driver == null) {
			return; // you could get more than one
					// capability...theoretically...unexpected
		}

		if (sid == StreamID.CAPABILITIES) {
			CapabilitiesEvent cap_event = (CapabilitiesEvent) item;
			showCapabilities(cap_event.getCapabilities());
			GuiUtil.showMessage("FIXME:  no driver.disconnect();");
			authMessage.setText("");
			driver = null;
		} else if( sid == StreamID.SECURITY ) {
			SecurityEvent sec = (SecurityEvent) item;
			if( sec.isAccept() == false ) {
				authMessage.setText("Access denied");
			} else {
				authMessage.setText("Access granted");
			}
		} else if( sid == StreamID.CONNECTION ) {
			ConnectionItem ce = (ConnectionItem) item;
			String m = "Connection: " + ce.getStatus();
			if( ce.getConnectInfo() != null ) {
				m = m + "/" + ce.getConnectInfo();
			}
			authMessage.setText( m );
			if( ce.getStatus() == ConnectionStatus.NOT_CONNECTED ) {
				connect.setEnabled( true );
			}
			
		} else {
			log.error("signal event error: {}", item );
			authMessage.setText("Error: " + item);
		}

	}

	@Override
	public void previous() {
		// TODO Auto-generated method stub

	}


}
