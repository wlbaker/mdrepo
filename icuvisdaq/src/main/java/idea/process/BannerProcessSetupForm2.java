/*
 * Created by JFormDesigner on Wed May 18 09:00:01 CDT 2011
 */

package idea.process;

import icuInterface.RpUtil;
import idea.conf.DeviceConfiguration;
import idea.conf.DeviceFactory;
import idea.intf.AdapterInterface;
import idea.intf.StreamProducer;
import idea.schema.rp.RpAnalysis;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpHardware;
import idea.schema.rp.RpStudy;
import idea.schema.rp.StringStringMap;

import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import javax.script.ScriptEngine;
import javax.script.ScriptException;
import javax.swing.DefaultComboBoxModel;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;
import javax.swing.JTextArea;

import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;
import idea.JavascriptUtil;
import idea.meddaq.AppModel;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.DefaultComponentFactory;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

/**
 * @author User #2
 */
@Slf4j
@SuppressWarnings("serial")
public class BannerProcessSetupForm2 extends JPanel {

	private RpAnalysis analysis;
	// private RpHardware hw;

	ScriptEngine engine;

	private StreamProducer[] devs;

	public BannerProcessSetupForm2(StreamProducer[] producers, RpAnalysis anal) {
		initComponents();
		this.analysis = anal;
		this.devs = producers;

		resetActionPerformed(null);

		// hw = study.getHardware().get(0);
		refreshTriggers();
		refreshDestinations();
		modelToPanel(anal);
	}

	private void refreshDestinations() {
		DefaultComboBoxModel model = new DefaultComboBoxModel();

		// List<RpDevice> devs = hw.getDevices();
		for (StreamProducer dev : devs) {
			RpDevice conf = dev.getConfiguration();
			if (conf != null) {
				model.addElement(conf);
			}
		}

		destPort.setModel(model);
	}

	private void refreshTriggers() {
		DefaultComboBoxModel model = new DefaultComboBoxModel();

		for (StreamProducer dev : devs) {
			RpDevice conf = dev.getConfiguration();
			if( conf != null ) {
				model.addElement(conf.getName());
			}
		}

		sourceDev1.setModel(model);
	}

	private void cancelActionPerformed(ActionEvent e) {
		GuiUtil.closeDialog(this);
	}

	private void okActionPerformed(ActionEvent e) {
		panelToModel();
		cancelActionPerformed(null);
	}

	private void panelToModel() {
		StringStringMap params = analysis.getParam();

		if (params == null) {
			params = new StringStringMap();
			analysis.setParam(params);
		}
		while (params.size() > 0) {
			params.remove(0);
		}

		if (sourceDev1.getSelectedItem() != null) {
			params.put("listen1", (String) sourceDev1.getSelectedItem());
		}

		if (destPort.getSelectedItem() != null) {
			params.put("dest", (String) destPort.getSelectedItem());
		}

		params.put("startup_script", connectScriptArea.getText());

		params.put("trigger_script", dataScriptArea.getText());

		params.put("timeout_script", disconnectScriptArea.getText());

		params.put("alarm_script", alarmScriptArea.getText());
		params.put("tick_script", tickScriptArea.getText());
	}

	private void modelToPanel(RpAnalysis anal) {
		Map<String, String> params = anal.getParam();
		if (params == null) {
			// nothing here yet
			return;
		}
		for (String key : params.keySet()) {

			String val = (String) params.get(key);
			if ("trigger_script".equals(key)) {
				dataScriptArea.setText(val);
			} else if ("timeout_script".equals(key)) {
				disconnectScriptArea.setText(val);
			} else if ("startup_script".equals(key)) {
				connectScriptArea.setText(val);
			} else if ("alarm_script".equals(key)) {
				alarmScriptArea.setText(val);
			} else if ("tick_script".equals(key)) {
				tickScriptArea.setText(val);
			} else if ("listen1".equals(key)) {
				sourceDev1.setSelectedItem(val);
			} else if ("dest".equals(key)) {
				destPort.setSelectedItem(val);
			} else {
				log.error("SCRIPT SETUP PARAMETER UNKNOWN: {}", key);
			}

		}

	}

	private void testActionPerformed(ActionEvent e) {
		try {
			_testActionPerformed(e);
			GuiUtil.showMessage("Script complete.");
		} catch (Exception ex) {
			GuiUtil.showError("Script Test", ex);
		}
	}

	/*
	 * 
	 * var cev = dest.getEvent( ConnectionEvent ); var nev = dest.getEvent( NumericsEvent );
	 * 
	 * dest.setDisplayMessage( "IDE2A", "" + nev );
	 * 
	 */
	private void _testActionPerformed(ActionEvent e) throws IOException, ScriptException {

		GuiUtil.showMessage("TODO: interface with serial discovery service");

		StreamProducer dest = null; // SerialDiscoveryService.getDevice((String) destPort.getSelectedItem());
		AdapterInterface ai = null;
		if (dest == null) {
			RpDevice trigger = getDevice((String) sourceDev1.getSelectedItem());
			RpDevice rpdest = getDevice((String) destPort.getSelectedItem());

			DeviceConfiguration conf = RpUtil.createDeviceConfiguration(rpdest, false);
			dest = DeviceFactory.createDriver(conf);
			if (dest == null) {
				GuiUtil.showMessage("Could not find driver: " + conf.getDeviceClass());
				return;
			}

			if (dest instanceof AdapterInterface) {
				ai = (AdapterInterface) dest;
				ai.connect();
				try {
					Thread.sleep(1000);
				} catch (InterruptedException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
				ai.tick();
			}
		}

		try {

			engine.put("dest", dest);

			int idx = tabber.getSelectedIndex();
			String s = "";
			if (idx == 0) {
				s = connectScriptArea.getText();
			} else if (idx == 1) {
				s = dataScriptArea.getText();
			} else if (idx == 2) {
				s = alarmScriptArea.getText();
			} else if (idx == 3) {
				s = disconnectScriptArea.getText();
			}
			engine.eval(s);

			if (ai != null) {
				for (int i = 0; i < 3; i++) {
					try {
						Thread.sleep(1000);
					} catch (InterruptedException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
					ai.tick();
				}
			}

		} finally {

			if (ai != null) {
				ai.disconnect();
			}
		}

	}

	private RpDevice getDevice(String selectedItem) {
		// List<RpDevice> devs = hw.getDevices();
		for (StreamProducer dev : devs) {
			RpDevice conf = dev.getConfiguration();
			
			if (conf != null && selectedItem.equals(conf.getName())) {
				return conf;
			}
		}
		return null;
	}

	private void resetActionPerformed(ActionEvent e) {
		engine = JavascriptUtil.initEngine();
		AppModel app = AppModel.getInstance();
		engine.put("app", app);

	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		separator2 = compFactory.createSeparator("Source and Destination");
		panel1 = new JPanel();
		label2 = new JLabel();
		sourceDev1 = new JComboBox();
		label1 = new JLabel();
		destPort = new JComboBox();
		label3 = new JLabel();
		comboBox1 = new JComboBox();
		label4 = new JLabel();
		separator1 = compFactory.createSeparator("Action");
		tabber = new JTabbedPane();
		panel3 = new JPanel();
		scrollPane3 = new JScrollPane();
		connectScriptArea = new JTextArea();
		panel4 = new JPanel();
		scrollPane1 = new JScrollPane();
		dataScriptArea = new JTextArea();
		panel5 = new JPanel();
		scrollPane2 = new JScrollPane();
		alarmScriptArea = new JTextArea();
		panel6 = new JPanel();
		scrollPane4 = new JScrollPane();
		disconnectScriptArea = new JTextArea();
		scrollPane5 = new JScrollPane();
		tickScriptArea = new JTextArea();
		panel2 = new JPanel();
		cancel = new JButton();
		reset = new JButton();
		test = new JButton();
		ok = new JButton();
		CellConstraints cc = new CellConstraints();

		// ======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout("[250dlu,default]:grow",
				"3*(default, $lgap), fill:[60dlu,default,200dlu]:grow, $lgap, default"));
		add(separator2, cc.xy(1, 1));

		// ======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
					"default, $lcgap, right:default, $lcgap, [50dlu,default], $lcgap, [20dlu,default], $lcgap, default:grow",
					"4*(default, $lgap), default"));

			// ---- label2 ----
			label2.setText("Trigger:");
			panel1.add(label2, cc.xy(3, 3));
			panel1.add(sourceDev1, cc.xywh(5, 3, 3, 1));

			// ---- label1 ----
			label1.setText("Destination:");
			panel1.add(label1, cc.xy(3, 5));
			panel1.add(destPort, cc.xywh(5, 5, 3, 1));

			// ---- label3 ----
			label3.setText("Timeout:");
			panel1.add(label3, cc.xy(3, 7));
			panel1.add(comboBox1, cc.xy(5, 7));

			// ---- label4 ----
			label4.setText("Timeout occurs when data not received from trigger device.");
			panel1.add(label4, cc.xy(9, 7));
		}
		add(panel1, cc.xy(1, 3));
		add(separator1, cc.xy(1, 5));

		// ======== tabber ========
		{

			// ======== panel3 ========
			{
				panel3.setLayout(new BorderLayout());

				// ======== scrollPane3 ========
				{

					// ---- connectScriptArea ----
					connectScriptArea.setText("dest.sendKey( \"I\" );");
					scrollPane3.setViewportView(connectScriptArea);
				}
				panel3.add(scrollPane3, BorderLayout.CENTER);
			}
			tabber.addTab("On Connection", panel3);

			// ======== panel4 ========
			{
				panel4.setLayout(new BorderLayout());

				// ======== scrollPane1 ========
				{

					// ---- dataScriptArea ----
					dataScriptArea.setText(
							"hr = getDeviceValue( \"Drager\", \"hr\" ) dest.setDisplayMessage( \"IDEA\", \"HR: \" + hr )");
					scrollPane1.setViewportView(dataScriptArea);
				}
				panel4.add(scrollPane1, BorderLayout.CENTER);
			}
			tabber.addTab("On Data", panel4);

			// ======== panel5 ========
			{
				panel5.setLayout(new BorderLayout());

				// ======== scrollPane2 ========
				{
					scrollPane2.setViewportView(alarmScriptArea);
				}
				panel5.add(scrollPane2, BorderLayout.CENTER);
			}
			tabber.addTab("On Alarm", panel5);

			// ======== panel6 ========
			{
				panel6.setLayout(new BorderLayout());

				// ======== scrollPane4 ========
				{
					scrollPane4.setViewportView(disconnectScriptArea);
				}
				panel6.add(scrollPane4, BorderLayout.CENTER);
			}
			tabber.addTab("On Disconnect", panel6);

			// ======== scrollPane5 ========
			{
				scrollPane5.setViewportView(tickScriptArea);
			}
			tabber.addTab("On Tick", scrollPane5);

		}
		add(tabber, cc.xy(1, 7));

		// ======== panel2 ========
		{
			panel2.setLayout(new FormLayout("default:grow, 4*($lcgap, [50dlu,default])", "default"));

			// ---- cancel ----
			cancel.setText("Cancel");
			cancel.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					cancelActionPerformed(e);
				}
			});
			panel2.add(cancel, cc.xy(3, 1));

			// ---- reset ----
			reset.setText("Reset");
			reset.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					resetActionPerformed(e);
				}
			});
			panel2.add(reset, cc.xy(5, 1));

			// ---- test ----
			test.setText("Run");
			test.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					testActionPerformed(e);
				}
			});
			panel2.add(test, cc.xy(7, 1));

			// ---- ok ----
			ok.setText("Ok");
			ok.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					okActionPerformed(e);
				}
			});
			panel2.add(ok, cc.xy(9, 1));
		}
		add(panel2, cc.xy(1, 9));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JComponent separator2;
	private JPanel panel1;
	private JLabel label2;
	private JComboBox sourceDev1;
	private JLabel label1;
	private JComboBox destPort;
	private JLabel label3;
	private JComboBox comboBox1;
	private JLabel label4;
	private JComponent separator1;
	private JTabbedPane tabber;
	private JPanel panel3;
	private JScrollPane scrollPane3;
	private JTextArea connectScriptArea;
	private JPanel panel4;
	private JScrollPane scrollPane1;
	private JTextArea dataScriptArea;
	private JPanel panel5;
	private JScrollPane scrollPane2;
	private JTextArea alarmScriptArea;
	private JPanel panel6;
	private JScrollPane scrollPane4;
	private JTextArea disconnectScriptArea;
	private JScrollPane scrollPane5;
	private JTextArea tickScriptArea;
	private JPanel panel2;
	private JButton cancel;
	private JButton reset;
	private JButton test;
	private JButton ok;
	// JFormDesigner - End of variables declaration //GEN-END:variables
}
