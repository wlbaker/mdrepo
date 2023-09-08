/* - BDetachListener -
 * Clear all the fields and disable all the controls
 *
 * Copyright 2011 Phidgets Inc.
 * This work is licensed under the Creative Commons Attribution 2.5 Canada License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by/2.5/ca/
 */
package icuInterface.adapters.phidget;

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
import com.phidgets.event.DetachEvent;
import com.phidgets.event.DetachListener;

public class BDetachListener implements DetachListener {

    private JFrame appFrame;
    private JPanel bridgeDataPanel;
    private JComboBox bridgeCmb;
    private JComboBox gainCmb;
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

    public BDetachListener(JFrame appFrame, JPanel bridgeDataPanel, JComboBox bridgeCmb, JComboBox gainCmb, JTextField attachedTxt, JTextArea nameTxt,
            JTextField serialTxt, JTextField versionTxt, JTextField numBridgesTxt, JCheckBox enableChk, JTextField bridgeValueTxt, JSlider dataRateSld,
            JTextField dataRateTxt) {
        this.appFrame = appFrame;
        this.bridgeDataPanel = bridgeDataPanel;
        this.bridgeCmb = bridgeCmb;
        this.gainCmb = gainCmb;

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
	public void detached(DetachEvent de) {
        try {
            BridgePhidget detached = (BridgePhidget) de.getSource();
            attachedTxt.setText(Boolean.toString(detached.isAttached()));
            nameTxt.setText("");
            serialTxt.setText("");
            versionTxt.setText("");
            numBridgesTxt.setText("");

            enableChk.setSelected(false);
            enableChk.setVisible(false);
            enableChk.setEnabled(false);

            bridgeValueTxt.setText("");
            bridgeValueTxt.setVisible(false);
            bridgeValueTxt.setEnabled(false);

            dataRateSld.setVisible(false);
            dataRateSld.setEnabled(false);
            dataRateTxt.setText("");
            dataRateTxt.setVisible(false);
            dataRateTxt.setEnabled(false);

            bridgeCmb.setEnabled(false);
            bridgeCmb.removeAllItems();

            gainCmb.setEnabled(false);
            gainCmb.removeAllItems();

            bridgeDataPanel.setVisible(false);

            appFrame.setSize(357, 295);

        } catch (PhidgetException ex) {
            JOptionPane.showMessageDialog(appFrame, ex.getDescription(), "Phidget error " + ex.getErrorNumber(), JOptionPane.ERROR_MESSAGE);
        }
    }
}
