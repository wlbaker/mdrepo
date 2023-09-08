/* - BBridgeDataListener -
 * Display the bridge data after a bridge data change
 *
 * Copyright 2011 Phidgets Inc.
 * This work is licensed under the Creative Commons Attribution 2.5 Canada License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by/2.5/ca/
 */
package icuInterface.adapters.phidget;

import javax.swing.JComboBox;
import javax.swing.JTextField;

import com.phidgets.BridgePhidget;
import com.phidgets.event.BridgeDataEvent;
import com.phidgets.event.BridgeDataListener;

public class BBridgeDataListener implements BridgeDataListener {

    private JComboBox bridgeCmb;
    private JTextField bridgeValueTxt;

    public BBridgeDataListener(JComboBox bridgeCmb, JTextField bridgeValueTxt) {
        this.bridgeCmb = bridgeCmb;
        this.bridgeValueTxt = bridgeValueTxt;
    }

    @Override
	public void bridgeData(BridgeDataEvent bde) {
        BridgePhidget fc = (BridgePhidget) bde.getSource();

        if (bde.getIndex() == ((Integer) bridgeCmb.getSelectedItem()).intValue()) {
            bridgeValueTxt.setText(Double.toString(bde.getValue()));
        }
    }
}
