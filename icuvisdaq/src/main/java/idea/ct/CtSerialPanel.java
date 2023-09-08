/*
 * Created by JFormDesigner on Mon Oct 05 13:52:41 CDT 2009
 */

package idea.ct;

import java.awt.event.ActionEvent;
import java.io.IOException;
import java.text.DecimalFormat;
import java.util.LinkedList;

import javax.swing.DefaultComboBoxModel;
import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.table.TableModel;

import com.fazecast.jSerialComm.SerialPort;
import com.jgoodies.forms.factories.CC;
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
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.schema.rp.RpConnType;
import idea.schema.rp.RpConnection;
import idea.schema.rp.RpDevice;
import idea.schema.rp.StringStringMap;
import lombok.extern.slf4j.Slf4j;
import idea.devwizard.WizStreamAdapterPanel;

/**
 * @author User #2
 */
@Slf4j
@SuppressWarnings("serial")
public class CtSerialPanel extends JPanel implements CtInterface, StreamConsumer {

	private DecimalFormat df2 = new DecimalFormat("0%");

	private boolean is_connecting = false;
	private boolean signalevent_recursing = false;

	LinkedList<String> untriedPorts = null;

	public CtSerialPanel() {
		initComponents();
		setStatusMessage("");
	}

	public void hideCommSetup() {
		commParms.setVisible(false);
		portLabel.setVisible(false);
		ports.setVisible(false);
	}


	public void panelToModel(RpDevice dc) {

		dc.setConnectionType(RpConnType.RS_232);

		String portName = (String) ports.getSelectedItem();
		IntfUtil.setParam(dc, "port", portName);

		dc.setConnectionValue(portName);
	}

	private void refresh(ActionEvent e) {

		untriedPorts = null;
		String portName = (String) ports.getSelectedItem();
		if (portName == "Auto") {
			untriedPorts = new LinkedList<String>();
			for (int idx = 0; idx < ports.getItemCount(); idx++) {
				String port = (String) ports.getItemAt(idx);
				if (port.equals("Auto")) {
					// ignore
				} else {
					untriedPorts.add(port);
				}
			}
			if (untriedPorts.size() == 0) {
				statusMessage.setText("No serial ports available.");
				return;
			}
			portName = untriedPorts.removeFirst();
		}
		statusMessage.setText("Port: " + portName);
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
		ports = new JComboBox();
		commParms = new JComboBox();
		statusMessage = new JLabel();

		//======== this ========
		setLayout(new FormLayout(
			"default:grow",
			"fill:default:grow"));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"right:[20dlu,default]:grow, $lcgap, [50dlu,default]",
				"2*(default, $lgap), default:grow, $lgap, default"));

			//---- portLabel ----
			portLabel.setText("Port:");
			panel1.add(portLabel, CC.xy(1, 1));
			panel1.add(ports, CC.xy(3, 1));
			panel1.add(commParms, CC.xy(3, 3));

			//---- statusMessage ----
			statusMessage.setText("??status");
			panel1.add(statusMessage, CC.xywh(1, 7, 3, 1));
		}
		add(panel1, CC.xy(1, 1));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JPanel panel1;
	private JLabel portLabel;
	private JComboBox ports;
	private JComboBox commParms;
	private JLabel statusMessage;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	public void setStatusMessage(String message) {
		this.statusMessage.setText(message);
	}

	private void updateBandwidth(TableModel model) {

		int tot = model.getRowCount();

		int wf_count = 0;
		int numerics_count = 0;

		int bandwidth = 0;
		int tot_bandwidth = 19200;

		for (int row = 0; row < tot; row++) {
			Object o = model.getValueAt(row, WizStreamAdapterPanel.COL_OOBJECT);
			Boolean enabled = (Boolean) model.getValueAt(row, WizStreamAdapterPanel.COL_ENABLED);
			if (enabled != null && enabled) {
				// FIXME: calculate bandwidth of pipe
//				if (o instanceof Metric) {
//					WaveformDescription desc = (WaveformDescription) o;
//					int sampleRate = desc.getSampleRate();
//					bandwidth += 2 * sampleRate;
//					wf_count++;
//				} else {
//					numerics_count++;
//				}
			}
		}

		String bandwidthMessage = "";
		if (wf_count > 0) {
			if (numerics_count > 0) {
				bandwidth += 100 + numerics_count * 4;
			}
			bandwidth += 100; // record header size
			bandwidth *= 9; // bytes-to-baud

			double pct = ((double) bandwidth) / tot_bandwidth;
			bandwidthMessage = "<html>Bandwidth: " + df2.format(pct);
			if (pct > 1.0) {
				bandwidthMessage += "<br>OVER LIMIT";
			}
		}

		setStatusMessage(bandwidthMessage);
	}

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {

		if (sid == StreamID.CAPABILITIES) {
			// 24 June 2014: Intellivue devices send multiple CAPS messages 
			DeviceConfiguration caps = ((CapabilitiesEvent) item).getCapabilities();
			log.error("FIXME: refresh( caps); // put refresh on the GUI thread");
		}
		if (sid == StreamID.CONNECTION) {
			ConnectionItem e = (ConnectionItem) item;
			ConnectionStatus status = e.getStatus();
			log.error("FIXME: probably need something here");
		}
	}

	@Override
	public void handleConnectionEvent(RpDevice conf, AdapterInterface driver, ConnectionStatus status) {
		StringStringMap params = conf.getParam();
		String port = params.get("port");
		
		statusMessage.setText(port + " " + status.toString());
		if (status == ConnectionStatus.NOT_CONNECTED) {
			System.out.println("check next port!");
			try {
				signalevent_recursing = true;
				driver.disconnect();
				signalevent_recursing = false;
			} catch (IOException e1) {
				// can probably ignore this
				e1.printStackTrace();
			}
			if (untriedPorts != null && untriedPorts.size() > 0) {
				String untried_port = untriedPorts.removeFirst();
				statusMessage.setText("Next port: " + port);
				log.info("checking next port: " + port);
				params.put("port", untried_port );
				try {
					driver.connect();
				} catch (IOException e1) {
					// WARNING: cannot ignore this!!!
					e1.printStackTrace();
				}
			} else {
				log.info("no more ports to try");
				is_connecting = false;
			}
		}

		if (status == ConnectionStatus.CONNECTED ) {
			log.error("STOP TRYING TO CONNECT");
			is_connecting = false; // we found the port!
		}
	}

	@Override
	public void init(RpDevice dc ) {
		if (dc != null) {

			commParms.removeAll();
			if (dc instanceof DeviceCapabilities) {
				DeviceCapabilities ccaps = (DeviceCapabilities) dc;
				RpConnection[] intfs = ccaps.getConnections();
				if (intfs != null) {
					for (RpConnection intf : intfs) {
						commParms.addItem(intf);
					}

				}
			}

		}

		if (dc == null) {
			ports.setEnabled(false);
		} else {
			String portName = dc.getConnectionValue();
			if (portName != null) {
				ports.setSelectedItem(portName);
			}
		}

		DefaultComboBoxModel cbmodel = (DefaultComboBoxModel) ports.getModel();
		cbmodel.removeAllElements();
//
		// RXTX
		//
//		Enumeration<?> portList = CommPortIdentifier.getPortIdentifiers();
//		while (portList.hasMoreElements()) {
//			CommPortIdentifier portId = (CommPortIdentifier) portList.nextElement();
//			if (portId.getPortType() == CommPortIdentifier.PORT_SERIAL) {
//				cbmodel.addElement(portId.getName());
//			}
//		}
		for( SerialPort port : SerialPort.getCommPorts() ) {
			cbmodel.addElement(port.getDescriptivePortName());
		}
		cbmodel.addElement("Auto");

		if (dc != null) {
			String port_value = dc.getConnectionValue();
			ports.setSelectedItem(port_value);
		}
	}
	

	@Override
	public void release() {
		// TODO Auto-generated method stub
		
	}


}
