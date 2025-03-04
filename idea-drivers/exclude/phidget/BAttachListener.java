/* - BAttachListener -
 * populate the fields and controls
 *
 * Copyright 2011 Phidgets Inc.
 * This work is licensed under the Creative Commons Attribution 2.5 Canada License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by/2.5/ca/
 */
package icuInterface.adapters.phidget;

import java.util.Hashtable;
import java.util.TreeSet;

import javax.swing.JCheckBox;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JSlider;
import javax.swing.JTextArea;
import javax.swing.JTextField;

import com.phidgets.BridgePhidget;
import com.phidgets.PhidgetException;
import com.phidgets.event.AttachEvent;
import com.phidgets.event.AttachListener;

public class BAttachListener implements AttachListener {

    private JFrame appFrame;
    private JPanel bridgeDataPanel;
    private JComboBox bridgeCmb;
    private JComboBox gainCmb;
    private Hashtable gains;
    private JTextField attachedTxt;
    private JTextArea nameTxt;
    private JTextField serialTxt;
    private JTextField versionTxt;
    private JTextField numBridgesTxt;
    private JCheckBox enableChk;
    private JTextField bridgeValueTxt;
    private JSlider dataRateSld;
    private JTextField dataRateTxt;
    private JTextField timeTxt;
    private JTextField frequencyTxt;
    private JTextField totalCountTxt;
    private JTextField totalTimeTxt;

    public BAttachListener(JFrame appFrame, JPanel bridgeDataPanel, JComboBox bridgeCmb, JComboBox gainCmb, Hashtable gains, JTextField attachedTxt, JTextArea nameTxt,
            JTextField serialTxt, JTextField versionTxt, JTextField numBridgesTxt, JCheckBox enableChk, JTextField bridgeValueTxt, JSlider dataRateSld,
            JTextField dataRateTxt) {
        this.appFrame = appFrame;
        this.bridgeDataPanel = bridgeDataPanel;
        this.bridgeCmb = bridgeCmb;
        this.gainCmb = gainCmb;
        this.gains = gains;
        this.attachedTxt = attachedTxt;
        this.nameTxt = nameTxt;
        this.serialTxt = serialTxt;
        this.versionTxt = versionTxt;
        this.numBridgesTxt = numBridgesTxt;
        this.enableChk = enableChk;
        this.bridgeValueTxt = bridgeValueTxt;
        this.dataRateSld = dataRateSld;
        this.dataRateTxt = dataRateTxt;
    }

	@Override
	public void attached(AttachEvent an) {
        try {
            int i;
            appFrame.setSize(357, 480);

            BridgePhidget attached = (BridgePhidget) an.getSource();
            attachedTxt.setText(Boolean.toString(attached.isAttached()));
            nameTxt.setText(attached.getDeviceName());
            serialTxt.setText(Integer.toString(attached.getSerialNumber()));
            versionTxt.setText(Integer.toString(attached.getDeviceVersion()));
            numBridgesTxt.setText(Integer.toString(attached.getInputCount()));

            bridgeDataPanel.setEnabled(true);
            bridgeDataPanel.setVisible(true);

            bridgeCmb.setEnabled(true);
            bridgeCmb.setVisible(true);

            for (i = 0; i < attached.getInputCount(); i++) {
                bridgeCmb.addItem(new Integer(i));
            }

            gainCmb.setEnabled(true);
            gainCmb.setVisible(true);

            TreeSet<Integer> sortedKeys = new TreeSet<Integer>(gains.keySet());
            for (Integer sortedKey : sortedKeys) {
                gainCmb.addItem(sortedKey);
            }

            enableChk.setEnabled(true);
            enableChk.setVisible(true);

            bridgeValueTxt.setEnabled(true);
            bridgeValueTxt.setVisible(true);

            dataRateTxt.setEnabled(true);
            dataRateTxt.setVisible(true);
            dataRateSld.setEnabled(true);
            dataRateSld.setVisible(true);
            dataRateSld.setMinimum(attached.getDataRateMax() / 8);
            dataRateSld.setMaximum(attached.getDataRateMin() / 8);

            enableChk.setSelected(attached.getEnabled(0));
            if (enableChk.isSelected()) {

                dataRateSld.setValue(attached.getDataRate() / 8);
                dataRateTxt.setText(Integer.toString(attached.getDataRate()));

            } else {
                gainCmb.setEnabled(false);
                dataRateSld.setEnabled(false);
            }
        } catch (PhidgetException ex) {
            JOptionPane.showMessageDialog(appFrame, ex.getDescription(), "Phidget error " + ex.getErrorNumber(), JOptionPane.ERROR_MESSAGE);
        }
    }
}
