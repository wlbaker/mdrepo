/*
 * Created by JFormDesigner on Mon Jun 20 15:50:04 CDT 2011
 */

package idea.adapters.gui;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Enumeration;
import java.util.Hashtable;

import javax.swing.JCheckBox;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JSlider;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;
import com.phidgets.BridgePhidget;
import com.phidgets.PhidgetException;

import icuInterface.adapters.phidget.BAttachListener;
import icuInterface.adapters.phidget.BBridgeDataListener;
import icuInterface.adapters.phidget.BDetachListener;
import icuInterface.adapters.phidget.BErrorListener;

/**
 * @author User #2
 */
public class BridgeForm extends JPanel {
	
    private static String runArgs[];
    private BridgePhidget bridge;
    private Hashtable gainHashTable;
    private BAttachListener attach_listener;
    private BDetachListener detach_listener;
    private BErrorListener error_listener;
    private BBridgeDataListener bridgeData_listener;


	public BridgeForm( JFrame frame ) {
		initComponents();

        this.setSize(357, 295);

        attachedTxt.setText("false");
        bridgeDataPanel.setVisible(false);
        bridgeDataPanel.setEnabled(false);

        bridgeCmb.setVisible(false);
        bridgeCmb.setEnabled(false);
        gainCmb.setVisible(false);
        gainCmb.setEnabled(false);

        gainHashTable = new Hashtable();

        gainHashTable.put(1, BridgePhidget.PHIDGET_BRIDGE_GAIN_1);
        gainHashTable.put(8, BridgePhidget.PHIDGET_BRIDGE_GAIN_8);
        gainHashTable.put(16, BridgePhidget.PHIDGET_BRIDGE_GAIN_16);
        gainHashTable.put(32, BridgePhidget.PHIDGET_BRIDGE_GAIN_32);
        gainHashTable.put(64, BridgePhidget.PHIDGET_BRIDGE_GAIN_64);
        gainHashTable.put(128, BridgePhidget.PHIDGET_BRIDGE_GAIN_128);

        enableChk.setVisible(false);
        enableChk.setEnabled(false);

        bridgeValueTxt.setVisible(false);
        bridgeValueTxt.setEnabled(false);

        dataRateTxt.setVisible(false);
        dataRateTxt.setEnabled(false);
        dataRateSld.setVisible(false);
        dataRateSld.setEnabled(false);

        try {
            bridge = new BridgePhidget();

            attach_listener = new BAttachListener(frame, this.bridgeDataPanel, this.bridgeCmb, this.gainCmb, this.gainHashTable, this.attachedTxt, this.nameTxt,
                    this.serialTxt, this.versionTxt, this.numBridgesTxt, this.enableChk, this.bridgeValueTxt, this.dataRateSld, this.dataRateTxt);

            detach_listener = new BDetachListener(frame, this.bridgeDataPanel, this.bridgeCmb, this.gainCmb, this.attachedTxt, this.nameTxt,
                    this.serialTxt, this.versionTxt, this.numBridgesTxt, this.enableChk, this.bridgeValueTxt, this.dataRateSld, this.dataRateTxt);

            error_listener = new BErrorListener(frame);

            bridgeData_listener = new BBridgeDataListener(this.bridgeCmb, this.bridgeValueTxt);

            bridge.addAttachListener(attach_listener);
            bridge.addDetachListener(detach_listener);
            bridge.addErrorListener(error_listener);
            bridge.addBridgeDataListener(bridgeData_listener);

            //This assumes that if there is a command line argument, it is a serial number
            //and we try to open that specific device. Otherwise, open any device.
            if ((runArgs.length > 1) && (runArgs[1].equals("remote"))) {
                bridge.open(Integer.parseInt(runArgs[0]), null);
            }
            if (runArgs.length > 0) {
                bridge.open(Integer.parseInt(runArgs[0]));
            } else {
                bridge.openAny();
            }

        } catch (PhidgetException ex) {
            JOptionPane.showMessageDialog(this, ex.getDescription(), "Phidget Error" + ex.getErrorNumber(), JOptionPane.ERROR_MESSAGE);
        }

	}

    private void enableChkActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_enableChkActionPerformed
        int index = ((Integer) bridgeCmb.getSelectedItem()).intValue();
        try {
            bridge.setEnabled(((Integer) bridgeCmb.getSelectedItem()).intValue(), enableChk.isSelected());
            try {
                Thread.sleep(80); //allow device time to set enabled state to false
            } catch (InterruptedException ex) {
            }
            if (enableChk.isSelected()) {
                bridgeValueTxt.setEnabled(true);
                gainCmb.setEnabled(true);
                setGainCmb();

                dataRateSld.setEnabled(true);
                dataRateTxt.setText(Integer.toString(bridge.getDataRate()));
            } else {
                bridgeValueTxt.setText("");
                gainCmb.setEnabled(false);
                dataRateSld.setEnabled(false);
                dataRateTxt.setText("");
            }
        } catch (PhidgetException ex) {
            JOptionPane.showMessageDialog(this, ex.getDescription(), "Phidget Error" + ex.getErrorNumber(), JOptionPane.ERROR_MESSAGE);
        }

    }//GEN-LAST:event_enableChkActionPerformed

    private void gainCmbActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_gainCmbActionPerformed
        bridgeValueTxt.setText("");
        int index = ((Integer) bridgeCmb.getSelectedItem()).intValue();
        try {
            if (bridge.isAttached() && bridge.getEnabled(index)) {
                int value = ((Integer) (gainHashTable.get(gainCmb.getSelectedItem())));
                bridge.setGain(index, value);
            }
        } catch (PhidgetException ex) {
            JOptionPane.showMessageDialog(this, ex.getDescription(), "Phidget Error" + ex.getErrorNumber(), JOptionPane.ERROR_MESSAGE);
        }
    }//GEN-LAST:event_gainCmbActionPerformed

    private void dataRateSldStateChanged(javax.swing.event.ChangeEvent evt) {//GEN-FIRST:event_dataRateSldStateChanged
        if (dataRateSld.isEnabled()) {
            try {
                bridge.setDataRate(dataRateSld.getValue() * 8);
                dataRateTxt.setText(Integer.toString(dataRateSld.getValue() * 8));
            } catch (PhidgetException ex) {
            }
        }
    }//GEN-LAST:event_dataRateSldStateChanged

    private void bridgeCmbActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_bridgeCmbActionPerformed
        bridgeValueTxt.setText("");

        int index = ((Integer) bridgeCmb.getSelectedItem()).intValue();

        try {
            if (bridge.isAttached() && bridge.getEnabled(index)) {
                enableChk.setSelected(true);
                gainCmb.setEnabled(true);
                dataRateSld.setEnabled(true);
                dataRateTxt.setText(Integer.toString(bridge.getDataRate()));

                setGainCmb();

            } else {
                enableChk.setSelected(false);
                gainCmb.setEnabled(false);
                dataRateSld.setEnabled(false);
                dataRateTxt.setText("");
            }
        } catch (PhidgetException ex) {
            JOptionPane.showMessageDialog(this, ex.getDescription(), "Phidget Error" + ex.getErrorNumber(), JOptionPane.ERROR_MESSAGE);
        }
    }//GEN-LAST:event_bridgeCmbActionPerformed

    private void setGainCmb() {
        int index = ((Integer) bridgeCmb.getSelectedItem()).intValue();
        Enumeration eKeys = gainHashTable.keys();
        int element;
        try {
            element = bridge.getGain(index);

            while (eKeys.hasMoreElements()) {
                Object currKey = eKeys.nextElement();
                if (((Integer) gainHashTable.get(currKey)).intValue() == element) {
                    gainCmb.setSelectedItem(currKey);
                }
            }
        } catch (PhidgetException ex) {
            JOptionPane.showMessageDialog(this, ex.getDescription(), "Phidget Error" + ex.getErrorNumber(), JOptionPane.ERROR_MESSAGE);
        }
    }

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		panel1 = new JPanel();
		label1 = new JLabel();
		attachedTxt = new JTextField();
		label2 = new JLabel();
		scrollPane1 = new JScrollPane();
		nameTxt = new JTextArea();
		label3 = new JLabel();
		serialTxt = new JTextField();
		label4 = new JLabel();
		versionTxt = new JTextField();
		label5 = new JLabel();
		numBridgesTxt = new JTextField();
		bridgeDataPanel = new JPanel();
		label6 = new JLabel();
		bridgeCmb = new JComboBox();
		label7 = new JLabel();
		gainCmb = new JComboBox();
		enableChk = new JCheckBox();
		bridgeValueTxt = new JTextField();
		dataRateSld = new JSlider();
		dataRateTxt = new JTextField();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setLayout(new FormLayout(
			"default:grow",
			"fill:default:grow, $lgap, fill:default:grow"));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"default, $lcgap, default:grow",
				"4*(default, $lgap), default"));

			//---- label1 ----
			label1.setText("Attached:");
			panel1.add(label1, cc.xy(1, 1));
			panel1.add(attachedTxt, cc.xy(3, 1));

			//---- label2 ----
			label2.setText("Name:");
			panel1.add(label2, cc.xy(1, 3));

			//======== scrollPane1 ========
			{
				scrollPane1.setViewportView(nameTxt);
			}
			panel1.add(scrollPane1, cc.xy(3, 3));

			//---- label3 ----
			label3.setText("Serial No:");
			panel1.add(label3, cc.xy(1, 5));
			panel1.add(serialTxt, cc.xy(3, 5));

			//---- label4 ----
			label4.setText("Version:");
			panel1.add(label4, cc.xy(1, 7));
			panel1.add(versionTxt, cc.xy(3, 7));

			//---- label5 ----
			label5.setText("Bridges:");
			panel1.add(label5, cc.xy(1, 9));
			panel1.add(numBridgesTxt, cc.xy(3, 9));
		}
		add(panel1, cc.xy(1, 1));

		//======== bridgeDataPanel ========
		{
			bridgeDataPanel.setLayout(new FormLayout(
				"default, $lcgap, default",
				"5*(default, $lgap), default"));

			//---- label6 ----
			label6.setText("Choose");
			bridgeDataPanel.add(label6, cc.xy(1, 1));

			//---- bridgeCmb ----
			bridgeCmb.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					bridgeCmbActionPerformed(e);
				}
			});
			bridgeDataPanel.add(bridgeCmb, cc.xy(3, 1));

			//---- label7 ----
			label7.setText("Gain");
			bridgeDataPanel.add(label7, cc.xy(1, 3));

			//---- gainCmb ----
			gainCmb.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					gainCmbActionPerformed(e);
				}
			});
			bridgeDataPanel.add(gainCmb, cc.xy(3, 3));

			//---- enableChk ----
			enableChk.setText("Enabled");
			enableChk.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					enableChkActionPerformed(e);
				}
			});
			bridgeDataPanel.add(enableChk, cc.xy(1, 7));
			bridgeDataPanel.add(bridgeValueTxt, cc.xy(3, 7));

			//---- dataRateSld ----
			dataRateSld.addChangeListener(new ChangeListener() {
				@Override
				public void stateChanged(ChangeEvent e) {
					dataRateSldStateChanged(e);
				}
			});
			bridgeDataPanel.add(dataRateSld, cc.xy(1, 11));
			bridgeDataPanel.add(dataRateTxt, cc.xy(3, 11));
		}
		add(bridgeDataPanel, cc.xy(1, 3));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	private JPanel panel1;
	private JLabel label1;
	private JTextField attachedTxt;
	private JLabel label2;
	private JScrollPane scrollPane1;
	private JTextArea nameTxt;
	private JLabel label3;
	private JTextField serialTxt;
	private JLabel label4;
	private JTextField versionTxt;
	private JLabel label5;
	private JTextField numBridgesTxt;
	private JPanel bridgeDataPanel;
	private JLabel label6;
	private JComboBox bridgeCmb;
	private JLabel label7;
	private JComboBox gainCmb;
	private JCheckBox enableChk;
	private JTextField bridgeValueTxt;
	private JSlider dataRateSld;
	private JTextField dataRateTxt;
	// JFormDesigner - End of variables declaration  //GEN-END:variables


	public static void main(String [] args) {
        runArgs = args;

		JFrame frame = new JFrame();
		
		frame.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );
		frame.setContentPane( new BridgeForm(frame) );
		frame.pack();
		frame.setVisible( true );
	}
}
