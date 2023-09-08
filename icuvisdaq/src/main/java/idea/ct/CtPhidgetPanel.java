/*
 * Created by JFormDesigner on Mon Oct 05 13:52:41 CDT 2009
 */

package idea.ct;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Vector;

import javax.swing.DefaultComboBoxModel;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFormattedTextField;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.SwingUtilities;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;
import com.phidgets.BridgePhidget;
import com.phidgets.Manager;
import com.phidgets.Phidget;
import com.phidgets.PhidgetException;
import com.phidgets.event.AttachEvent;
import com.phidgets.event.AttachListener;
import com.phidgets.event.BridgeDataEvent;
import com.phidgets.event.BridgeDataListener;
import com.phidgets.event.DetachEvent;
import com.phidgets.event.DetachListener;

import icuInterface.ConnectionStatus;
import idea.intf.AdapterInterface;
import idea.schema.rp.RpConnType;
import idea.schema.rp.RpDevice;
import idea.schema.rp.StringStringMap;
import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;

/**
 * @author User #2
 */
@Slf4j
@SuppressWarnings("serial")
public class CtPhidgetPanel extends JPanel implements CtInterface, BridgeDataListener, AttachListener, DetachListener {

	String[] types = { "Waveform", "Numeric" };

	private BridgePhidget bridge;
	private Manager phidgetManager;
	private AttachListener bridgeAttachListener;

	public CtPhidgetPanel() {

		initComponents();

		refresh();
		
		bridgeAttachListener = new AttachListener() {

			@Override
			public void attached(AttachEvent arg0) {
				log.warn("FIXME: maybe now I can get inputs: {}", arg0 );
			}
		};
	}

	@Override
	public void init(RpDevice dev) throws PhidgetException {
		initPhidgetManager();
	}
	
	private void initPhidgetManager() throws PhidgetException {

		phidgetManager = new Manager();
		phidgetManager.addAttachListener(this);
		phidgetManager.addDetachListener(this);
		phidgetManager.open();

		updatePhidgetsList();
	}

	public void refresh() {
		try {
			refreshCombos();
		} catch (Exception e) {
			GuiUtil.showError("Phidget Exception", e);
		} catch (UnsatisfiedLinkError r) {
			GuiUtil.showError("Phidget Error", r);
		}
	}

	private void refreshCombos() throws PhidgetException {

		DefaultComboBoxModel<Integer> model = new DefaultComboBoxModel<Integer>();
		model.addElement(BridgePhidget.PHIDGET_BRIDGE_GAIN_1);
		model.addElement(BridgePhidget.PHIDGET_BRIDGE_GAIN_8);
		model.addElement(BridgePhidget.PHIDGET_BRIDGE_GAIN_16);
		model.addElement(BridgePhidget.PHIDGET_BRIDGE_GAIN_32);
		model.addElement(BridgePhidget.PHIDGET_BRIDGE_GAIN_64);
		model.addElement(BridgePhidget.PHIDGET_BRIDGE_GAIN_128);
		gain.setModel(model);

		model = new DefaultComboBoxModel<Integer>();
		model.addElement(8);
		model.addElement(16);
		model.addElement(40);
		model.addElement(100);
		model.addElement(250);
		model.addElement(500);
		model.addElement(1000);
		sampleRate.setModel(model);

	}

	private void calibrateActionPerformed(ActionEvent e) {
		// TODO add your code here
	}

	private void deviceActionPerformed(ActionEvent e) {
		try {
			Object item = device.getSelectedItem();
			if (item != null) {
				int serNo = Integer.parseInt(item.toString());
				_deviceActionPerformed(serNo);
			}
		} catch (PhidgetException e1) {
			GuiUtil.showError("Phidge Error", e1);
		}
	}

	private void _deviceActionPerformed(int serNo) throws PhidgetException {
		synchronized (device) {
			Object item = device.getSelectedItem();
			if (bridge != null) {
				bridge.close();
				bridge = null;
			}
			if (item != null) {

				if (bridge != null) {
					bridge.removeAttachListener(bridgeAttachListener);
				}

				bridge = new BridgePhidget();
				bridge.addBridgeDataListener(this);
				bridge.addAttachListener(bridgeAttachListener);

				bridge.open(serNo);

			}
		}

	}

	private void zeroActionPerformed(ActionEvent e) {
		if (bridge == null) {
			return;
		}

		// bridge.
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		panel1 = new JPanel();
		label5 = new JLabel();
		device = new JComboBox();
		label1 = new JLabel();
		sampleRate = new JComboBox<>();
		label2 = new JLabel();
		gain = new JComboBox<>();
		label3 = new JLabel();
		slope = new JFormattedTextField();
		label4 = new JLabel();
		offset = new JFormattedTextField();
		zero = new JButton();
		calibrate = new JButton();
		label6 = new JLabel();
		textField1 = new JTextField();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setBorder(Borders.DLU2);
		setLayout(new FormLayout("default:grow", "fill:default:grow"));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout("right:[58dlu,default]:grow, $lcgap, default:grow",
					"5*(default, $lgap), default:grow, 3*($lgap, default)"));

			//---- label5 ----
			label5.setText("Device ID:");
			panel1.add(label5, cc.xy(1, 1));
			panel1.add(device, cc.xy(3, 1));

			//---- label1 ----
			label1.setText("Data Rate (ms):");
			panel1.add(label1, cc.xy(1, 3));
			panel1.add(sampleRate, cc.xy(3, 3));

			//---- label2 ----
			label2.setText("Gain:");
			panel1.add(label2, cc.xy(1, 5));
			panel1.add(gain, cc.xy(3, 5));

			//---- label3 ----
			label3.setText("Slope:");
			panel1.add(label3, cc.xy(1, 7));

			//---- slope ----
			slope.setEnabled(false);
			panel1.add(slope, cc.xy(3, 7));

			//---- label4 ----
			label4.setText("Offset:");
			panel1.add(label4, cc.xy(1, 9));

			//---- offset ----
			offset.setEnabled(false);
			panel1.add(offset, cc.xy(3, 9));

			//---- zero ----
			zero.setText("Zero");
			zero.setEnabled(false);
			zero.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					zeroActionPerformed(e);
				}
			});
			panel1.add(zero, cc.xy(3, 13));

			//---- calibrate ----
			calibrate.setText("Calibrate");
			calibrate.setEnabled(false);
			calibrate.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					calibrateActionPerformed(e);
				}
			});
			panel1.add(calibrate, cc.xy(3, 15));

			//---- label6 ----
			label6.setText("Weight:");
			panel1.add(label6, cc.xy(1, 17));

			//---- textField1 ----
			textField1.setEnabled(false);
			panel1.add(textField1, cc.xy(3, 17));
		}
		add(panel1, cc.xy(1, 1));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JPanel panel1;
	private JLabel label5;
	private JComboBox device;
	private JLabel label1;
	private JComboBox<Integer> sampleRate;
	private JLabel label2;
	private JComboBox<Integer> gain;
	private JLabel label3;
	private JFormattedTextField slope;
	private JLabel label4;
	private JFormattedTextField offset;
	private JButton zero;
	private JButton calibrate;
	private JLabel label6;
	private JTextField textField1;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	@Override
	public void panelToModel(RpDevice dc ) {


			// ? dc.setDeviceClass( driver.getClass().getCanonicalName() );
		dc.setConnectionType(RpConnType.PHIDGET);

		StringStringMap params = dc.getParam();
		if( params == null ) {
			params = new StringStringMap();
			dc.setParam(params);
		}
		params.put("gain", "" + gain.getSelectedItem() );
		params.put("rate", "" + sampleRate.getSelectedItem() );

		String serNo = (String) device.getSelectedItem();
		params.put("serNo", serNo );
		dc.setConnectionValue("");
		if (device.getSelectedIndex() >= 0) {
			dc.setConnectionValue(serNo);
		}
	}

	@Override
	public void release() {
		try {
			if (bridge != null) {
				log.debug("closing bridge");
				bridge.removeAttachListener(bridgeAttachListener);

				bridge.close();
				bridge = null;
			}
			if (phidgetManager != null) {
				log.debug("closing manager");
				phidgetManager.removeAttachListener(this);
				phidgetManager.removeDetachListener(this);
				phidgetManager.close();
				phidgetManager = null;
			}
		} catch (PhidgetException e) {
			GuiUtil.showError("Phidget error.", e);
		}

		return;
	}

	@Override
	public void bridgeData(BridgeDataEvent bde) {

		log.warn("FIXME: got bridge data event -- populate view");

	}

	@Override
	public void attached(AttachEvent arg0) {
		log.info("got attach for phidget: {}", arg0.getSource());

		updatePhidgetsList();
	}

	@Override
	public void detached(DetachEvent arg0) {
		log.info("got detach for phidget: {}", arg0);
		updatePhidgetsList();
	}

	private void updatePhidgetsList() {
		SwingUtilities.invokeLater(new Runnable() {

			@Override
			public void run() {
				try {
					_updatePhidgetsList();
				} catch (PhidgetException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}

			}
		});
	}

	private void _updatePhidgetsList() throws PhidgetException {
		DefaultComboBoxModel model = new DefaultComboBoxModel();

		Vector<Phidget> phidgets;
		phidgets = phidgetManager.getPhidgets();

		if (phidgets != null && phidgets.size() > 0) {
			for (Phidget phid : phidgets) {
				model.addElement("" + phid.getSerialNumber());
			}
		}

		device.setModel(model);
		deviceActionPerformed(null); // select the first item

	}


	@Override
	public void handleConnectionEvent(RpDevice conf, AdapterInterface driver, ConnectionStatus status) {
		// TODO Auto-generated method stub
		
	}


}
