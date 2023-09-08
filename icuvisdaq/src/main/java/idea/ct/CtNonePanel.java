/*
 * Created by JFormDesigner on Mon Oct 05 13:52:41 CDT 2009
 */

package idea.ct;

import java.awt.event.ActionEvent;

import javax.swing.JPanel;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.layout.FormLayout;

import icuInterface.ConnectionStatus;
import idea.intf.AdapterInterface;
import idea.schema.rp.RpConnType;
import idea.schema.rp.RpDevice;
import lombok.extern.slf4j.Slf4j;

/**
 * @author User #2
 */
@Slf4j
@SuppressWarnings("serial")
public class CtNonePanel extends JPanel implements CtInterface {

	public CtNonePanel( ) {

		initComponents();
	}


	private void deviceActionPerformed(ActionEvent e) {
	}


	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		panel1 = new JPanel();

		//======== this ========
		setBorder(Borders.DLU2);
		setLayout(new FormLayout(
			"default:grow",
			"fill:default:grow"));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"right:[58dlu,default]:grow, $lcgap, default:grow",
				"[12dlu,default], 3*($lgap, default), $lgap, default:grow"));
		}
		add(panel1, CC.xy(1, 1));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JPanel panel1;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	@Override
	public void panelToModel( RpDevice dc ) {

		// ? dc.setDeviceClass( driver.getClass().getCanonicalName() );
		dc.setConnectionType(RpConnType.NONE);

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
