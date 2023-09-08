/*
 * Created by JFormDesigner on Sun Jul 10 11:29:59 CDT 2011
 */

package idea.devwizard;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;

import javax.swing.DefaultComboBoxModel;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

import com.jgoodies.forms.factories.DefaultComponentFactory;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import icuInterface.RpUtil;
import icuInterface.conf.dev.SerialDeviceConfiguration;
import idea.conf.DeviceConfiguration;
import idea.conf.DeviceFactory;
import idea.intf.AdapterInterface;
import idea.intf.DisplayInterface;
import idea.model.IntfUtil;
import idea.schema.rp.RpConnType;
import idea.schema.rp.RpDevice;
import idea.GuiUtil;
import idea.gui.WizardMasterInterface;
import idea.gui.WizardPanelInterface;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class WizAbstractDisplayPanel extends JPanel implements WizardPanelInterface {
	private WizardMasterInterface wizard;
	private RpDevice dc;
	Class<?> devClass;

	public WizAbstractDisplayPanel(WizardMasterInterface wizard, RpDevice dc, Class<?> devClass, String [] models) {
		initComponents();
		this.wizard = wizard;

		this.dc = dc;
		this.devClass = devClass;
		
		refresh();
	}

	@Override
	public void refresh() {
		
		DefaultComboBoxModel model = new DefaultComboBoxModel();

		//rxtx Enumeration<?> portList = CommPortIdentifier.getPortIdentifiers();
		//rxtx while (portList.hasMoreElements()) {
		//rxtx 	CommPortIdentifier portId = (CommPortIdentifier) portList.nextElement();
		//rxtx 	if (portId.getPortType() == CommPortIdentifier.PORT_SERIAL) {
		//rxtx 		model.addElement(portId.getName());
		//rxtx 	}
		//rxtx }
		
		model.addElement("Auto");
		ports.setModel( model );

		if (dc == null) {
			ports.setEnabled(false);
		} else {
			String portName = dc.getConnectionValue();
			if (portName != null) {
				ports.setSelectedItem(portName);
			}
		}


	}

	private void testActionPerformed(ActionEvent e) {
		try {
			_testActionPerformed( line1.getText(), line2.getText() );
		} catch (Exception ex ) {
			GuiUtil.showError("Alpha Test", ex);
		}
	}
	private void _testActionPerformed(String s1, String s2) throws IOException {
		DeviceConfiguration conf = DeviceFactory.createConfig( devClass );
		
		if( conf  instanceof SerialDeviceConfiguration ) {
			((SerialDeviceConfiguration)conf).setPort( (String) ports.getSelectedItem() );
		}
		
		AdapterInterface driver = DeviceFactory.createDriver( conf );
		
		driver.connect();
		
		((DisplayInterface)driver).setDisplayMessage( s1, s2 );
		
		try {
			Thread.sleep(1000); // bad approach
		} catch (InterruptedException e) {
			e.printStackTrace();
		}  
		
		driver.disconnect();

	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		separator1 = compFactory.createSeparator("Alpha Display / Output Device");
		panel1 = new JPanel();
		label2 = new JLabel();
		deviceName = new JTextField();
		label1 = new JLabel();
		ports = new JComboBox();
		label3 = compFactory.createLabel("Line 1 Test Message:");
		line1 = new JTextField();
		label4 = compFactory.createLabel("Line 2 Test Message:");
		line2 = new JTextField();
		test = new JButton();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setLayout(new FormLayout(
			"default:grow",
			"3*(default, $lgap), default"));
		add(separator1, cc.xy(1, 3));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"[50dlu,default], $lcgap, right:default, $lcgap, [150dlu,default], $lcgap, [50dlu,default]",
				"[12dlu,default], $lgap, default, $lgap, [12dlu,default], 4*($lgap, default)"));

			//---- label2 ----
			label2.setText("Device Name:");
			panel1.add(label2, cc.xy(3, 3));
			panel1.add(deviceName, cc.xy(5, 3));

			//---- label1 ----
			label1.setText("Output Port:");
			panel1.add(label1, cc.xy(3, 7));
			panel1.add(ports, cc.xy(5, 7));
			panel1.add(label3, cc.xy(3, 11));

			//---- line1 ----
			line1.setText("IDEA");
			panel1.add(line1, cc.xy(5, 11));
			panel1.add(label4, cc.xy(3, 13));

			//---- line2 ----
			line2.setText("Test Message");
			panel1.add(line2, cc.xy(5, 13));

			//---- test ----
			test.setText("Test");
			test.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					testActionPerformed(e);
				}
			});
			panel1.add(test, cc.xy(7, 13));
		}
		add(panel1, cc.xy(1, 5));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}


	@Override
	public void previous() {
	}

	@Override
	public boolean next() {
		this.finish();  // close the port
		
		panelToModel();

		wizard.popPageUntil("Hardware Setup");
		
		return true;
	}

	private void panelToModel() {
			if (dc == null) {
				dc = new RpDevice();
			} else {
				RpUtil.resetDC(dc);
			}

			// ? dc.setDeviceClass( driver.getClass().getCanonicalName() );
			dc.setConnectionType(RpConnType.RS_232);
	
			String portName = (String) ports.getSelectedItem();
			IntfUtil.setParam(dc, "port", portName);
			dc.setConnectionValue(portName);
			dc.setModelName("AlphaDisplay");
			String name =devClass.getName();
			
			String t = deviceName.getText().trim();
			if (t.length() > 0) {
				name = t;
			}
			dc.setName(name);

	}

	@Override
	public boolean finish() {
		return true;
	}


	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JComponent separator1;
	private JPanel panel1;
	private JLabel label2;
	private JTextField deviceName;
	private JLabel label1;
	private JComboBox ports;
	private JLabel label3;
	private JTextField line1;
	private JLabel label4;
	private JTextField line2;
	private JButton test;
	// JFormDesigner - End of variables declaration  //GEN-END:variables
}
