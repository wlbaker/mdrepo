/*
 * Created by JFormDesigner on Mon Oct 05 13:52:41 CDT 2009
 */

package idea.ct;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.DefaultComboBoxModel;
import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JPanel;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import icuInterface.ConnectionStatus;
import idea.intf.AdapterInterface;
import idea.schema.rp.RpConnType;
import idea.schema.rp.RpDevice;
import idea.schema.rp.StringStringMap;
import lombok.extern.slf4j.Slf4j;

/**
 * @author User #2
 */
@Slf4j
@SuppressWarnings("serial")
public class CtLabjackPanel extends JPanel implements CtInterface {

	String[] types = { "Waveform", "Numeric" };

	public CtLabjackPanel( ) {

		initComponents();
	}


	private void deviceActionPerformed(ActionEvent e) {
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
		gain = new JComboBox();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setBorder(Borders.DLU2);
		setLayout(new FormLayout("default:grow", "fill:default:grow"));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout("right:[58dlu,default]:grow, $lcgap, default:grow",
					"[12dlu,default], 3*($lgap, default), $lgap, default:grow"));

			//---- label5 ----
			label5.setText("Device:");
			panel1.add(label5, cc.xy(1, 1));

			//---- device ----
			device.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					deviceActionPerformed(e);
				}
			});
			panel1.add(device, cc.xy(3, 1));

			//---- label1 ----
			label1.setText("Sample Rate (Hz):");
			panel1.add(label1, cc.xy(1, 3));

			//---- sampleRate ----
			sampleRate.setModel(new DefaultComboBoxModel<>(new String[] { "200", "500" }));
			panel1.add(sampleRate, cc.xy(3, 3));

			//---- label2 ----
			label2.setText("Gain:");
			panel1.add(label2, cc.xy(1, 5));
			panel1.add(gain, cc.xy(3, 5));
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
	private JComboBox<String> sampleRate;
	private JLabel label2;
	private JComboBox gain;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	@Override
	public void panelToModel( RpDevice dc ) {

		// ? dc.setDeviceClass( driver.getClass().getCanonicalName() );
		dc.setConnectionType(RpConnType.LAB_JACK);

		StringStringMap params = dc.getParam();
		//params.put("rate", "" + rate);
		//params.put("gain", "" + gain);
		//dc.setConnectionValue("Phidget");
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
	public void handleConnectionEvent(RpDevice conf, AdapterInterface driver, ConnectionStatus status) {
		// TODO Auto-generated method stub
		
	}

}
