/*
 * Created by JFormDesigner on Thu May 26 13:06:34 CDT 2011
 */

package idea.analysis;

import icuInterface.RpUtil;
import idea.message.StreamID;
import idea.schema.rp.RpAnalysis;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpHardware;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpStudy;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;
import java.util.Map;

import javax.swing.ComboBoxModel;
import javax.swing.DefaultComboBoxModel;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JPanel;

import idea.GuiUtil;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.DefaultComponentFactory;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class MultiSignalDetectionSetupPanel extends JPanel {
	private RpAnalysis analysis;
	private RpStudy study;

	public MultiSignalDetectionSetupPanel(RpStudy study, RpAnalysis anal) {
		initComponents();

		this.study = study;
		this.analysis = anal;

		refresh();
	}

	private void refresh() {
		RpHardware hw = study.getHardware().get(0);
		List<RpDevice> devs = hw.getDevices();
		DefaultComboBoxModel dev1_model = new DefaultComboBoxModel();
		DefaultComboBoxModel dev2_model = new DefaultComboBoxModel();
		DefaultComboBoxModel dev3_model = new DefaultComboBoxModel();
		DefaultComboBoxModel dev4_model = new DefaultComboBoxModel();
		for (RpDevice dev : devs) {
			dev1_model.addElement(new DevWrapper(dev));
			dev2_model.addElement(new DevWrapper(dev));
			dev3_model.addElement(new DevWrapper(dev));
			dev4_model.addElement(new DevWrapper(dev));
		}

		device.setModel(dev1_model);
		device2.setModel(dev2_model);
		device3.setModel(dev3_model);
		device4.setModel(dev4_model);

		Map<String, String> params = analysis.getParam();
		setSelector(params, "DEV", device);
		setSelector(params, "SIG1", signal); // historical reasons...obsolete
		setSelector(params, "DEV", device2);
		setSelector(params, "SIG2", signal2); // historical reasons...obsolete
		setSelector(params, "DEV", device3);
		setSelector(params, "SIG3", signal3); // historical reasons...obsolete
		setSelector(params, "DEV", device4);
		setSelector(params, "SIG4", signal4); // historical reasons...obsolete

	}

	private void setSelector(Map<String, String> params, String key, JComboBox selector) {
		String save_value = params.get(key);
		if (save_value == null) {
			return;
		}

		ComboBoxModel model = selector.getModel();
		Object selector_value = null;
		for (int i = 0; i < model.getSize(); i++) {
			Object wrapper = model.getElementAt(i);
			if (wrapper instanceof WfWrapper) {
				WfWrapper w = (WfWrapper) wrapper;
				RpMetric wave = w.getWave();
				selector_value = wave.getLocation();
			} else if (wrapper instanceof DevWrapper) {
				DevWrapper w = (DevWrapper) wrapper;
				RpDevice dev = w.getDevice();
				selector_value = dev.getName();
			} else {
				// a common String...used for detection algorithm
				selector_value = wrapper;
			}

			if (save_value.equals(selector_value)) {
				selector.setSelectedItem(wrapper);
				break;
			}
		}
		return;
	}

	private void okActionPerformed(ActionEvent e) {

		String a_name = analysis.getName();
		if (a_name == null) {
			a_name = "untitled";
		}
		int pos = a_name.indexOf(':');
		if (pos > 0) {
			a_name = a_name.substring(0, pos);
		}

		analysis.setName(a_name);

		save();
		cancelActionPerformed(null);
	}

	private void save() {
		Map<String, String> params = analysis.getParam();
		saveParam(params, "DEV1", device.getSelectedItem());
		saveParam(params, "SIG_DEV1", device.getSelectedItem()); // historical
		// reasons...obsolete
		saveParam(params, "SIG1", signal.getSelectedItem()); // historical
		// reasons...obsolete
		saveParam(params, "signal", signal.getSelectedItem());

		saveParam(params, "DEV2", device2.getSelectedItem());
		saveParam(params, "SIG_DEV2", device2.getSelectedItem()); // historical
		// reasons...obsolete
		saveParam(params, "SIG2", signal2.getSelectedItem()); // historical
		// reasons...obsolete
		saveParam(params, "signal2", signal2.getSelectedItem());

		saveParam(params, "DEV3", device3.getSelectedItem());
		saveParam(params, "SIG_DEV3", device3.getSelectedItem()); // historical
		// reasons...obsolete
		saveParam(params, "SIG3", signal3.getSelectedItem()); // historical
		// reasons...obsolete
		saveParam(params, "signal3", signal3.getSelectedItem());

		saveParam(params, "DEV4", device4.getSelectedItem());
		saveParam(params, "SIG_DEV4", device4.getSelectedItem()); // historical
		// reasons...obsolete
		saveParam(params, "SIG4", signal4.getSelectedItem()); // historical
		// reasons...obsolete
		saveParam(params, "signal4", signal4.getSelectedItem());
	}

	private void saveParam(Map<String, String> params, String key, Object wrapper) {
		String value = null;
		if (wrapper instanceof WfWrapper) {
			WfWrapper w = (WfWrapper) wrapper;
			RpMetric wave = w.getWave();
			value = wave.getLocation();
		} else if (wrapper instanceof DevWrapper) {
			DevWrapper w = (DevWrapper) wrapper;
			RpDevice dev = w.getDevice();
			value = dev.getName();
		} else {
			value = (String) wrapper; // should be a string...used for detection algorithm
		}

		params.put(key, value);
	}

	private void cancelActionPerformed(ActionEvent e) {
		GuiUtil.closeDialog(this);
	}

	private void deviceActionPerformed(ActionEvent e) {
		DevWrapper wrapper = (DevWrapper) device.getSelectedItem();
		RpDevice intf = wrapper.getDevice();

		if (intf == null) {
			return;
		}
		List<? extends RpMetric> waves = RpUtil.getMetrics(intf, StreamID.WAVEFORM);
		if (waves == null) {
			return;
		}

		DefaultComboBoxModel model = new DefaultComboBoxModel();

		for (RpMetric wave : waves) {
			model.addElement(new WfWrapper(wave));
		}
		signal.setModel(model);
	}

	private void device2ActionPerformed(ActionEvent e) {
		DevWrapper wrapper2 = (DevWrapper) device2.getSelectedItem();
		RpDevice intf2 = wrapper2.getDevice();

		if (intf2 == null) {
			return;
		}
		List<? extends RpMetric> waves2 = RpUtil.getMetrics(intf2, StreamID.WAVEFORM);
		if (waves2 == null) {
			return;
		}

		DefaultComboBoxModel model2 = new DefaultComboBoxModel();

		for (RpMetric wave : waves2) {
			model2.addElement(new WfWrapper(wave));
		}
		signal2.setModel(model2);
	}

	private void device3ActionPerformed(ActionEvent e) {
		DevWrapper wrapper3 = (DevWrapper) device3.getSelectedItem();
		RpDevice intf3 = wrapper3.getDevice();

		if (intf3 == null) {
			return;
		}
		List<? extends RpMetric> waves3 = RpUtil.getMetrics(intf3, StreamID.WAVEFORM);
		if (waves3 == null) {
			return;
		}

		DefaultComboBoxModel model3 = new DefaultComboBoxModel();

		for (RpMetric wave : waves3) {
			model3.addElement(new WfWrapper(wave));
		}
		signal3.setModel(model3);
	}

	private void device4ActionPerformed(ActionEvent e) {
		DevWrapper wrapper4 = (DevWrapper) device4.getSelectedItem();
		RpDevice intf4 = wrapper4.getDevice();

		if (intf4 == null) {
			return;
		}
		List<? extends RpMetric> waves4 = RpUtil.getMetrics(intf4, StreamID.WAVEFORM);
		if (waves4 == null) {
			return;
		}

		DefaultComboBoxModel model4 = new DefaultComboBoxModel();

		for (RpMetric wave : waves4) {
			model4.addElement(new WfWrapper(wave));
		}
		signal4.setModel(model4);
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		separator1 = compFactory.createSeparator("Multiwaveform Detection Setup");
		panel1 = new JPanel();
		label2 = new JLabel();
		device = new JComboBox();
		label3 = new JLabel();
		signal = new JComboBox();
		label4 = new JLabel();
		device2 = new JComboBox();
		label5 = new JLabel();
		signal2 = new JComboBox();
		label6 = new JLabel();
		device3 = new JComboBox();
		label7 = new JLabel();
		signal3 = new JComboBox();
		label8 = new JLabel();
		device4 = new JComboBox();
		label9 = new JLabel();
		signal4 = new JComboBox();
		buttonPanel = new JPanel();
		ok = new JButton();
		cancel = new JButton();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout("default:grow", "2*(default, $lgap), default:grow, $lgap, default"));
		add(separator1, cc.xy(1, 1));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout("right:[100dlu,default], $lcgap, [100dlu,default]",
					"[12dlu,default], 12*($lgap, default)"));

			//---- label2 ----
			label2.setText("Source Device:");
			panel1.add(label2, cc.xy(1, 3));

			//---- device ----
			device.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					deviceActionPerformed(e);
				}
			});
			panel1.add(device, cc.xy(3, 3));

			//---- label3 ----
			label3.setText("Source Signal:");
			panel1.add(label3, cc.xy(1, 5));
			panel1.add(signal, cc.xy(3, 5));

			//---- label4 ----
			label4.setText("Source Device:");
			panel1.add(label4, cc.xy(1, 9));

			//---- device2 ----
			device2.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					deviceActionPerformed(e);
					device2ActionPerformed(e);
				}
			});
			panel1.add(device2, cc.xy(3, 9));

			//---- label5 ----
			label5.setText("Source Signal:");
			panel1.add(label5, cc.xy(1, 11));
			panel1.add(signal2, cc.xy(3, 11));

			//---- label6 ----
			label6.setText("Source Device:");
			panel1.add(label6, cc.xy(1, 15));

			//---- device3 ----
			device3.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					deviceActionPerformed(e);
					device3ActionPerformed(e);
				}
			});
			panel1.add(device3, cc.xy(3, 15));

			//---- label7 ----
			label7.setText("Source Signal:");
			panel1.add(label7, cc.xy(1, 17));
			panel1.add(signal3, cc.xy(3, 17));

			//---- label8 ----
			label8.setText("Source Device:");
			panel1.add(label8, cc.xy(1, 21));

			//---- device4 ----
			device4.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					deviceActionPerformed(e);
					device4ActionPerformed(e);
				}
			});
			panel1.add(device4, cc.xy(3, 21));

			//---- label9 ----
			label9.setText("Source Signal:");
			panel1.add(label9, cc.xy(1, 23));
			panel1.add(signal4, cc.xy(3, 23));
		}
		add(panel1, cc.xywh(1, 3, 1, 3));

		//======== buttonPanel ========
		{
			buttonPanel.setLayout(new FormLayout("default:grow, 2*($lcgap, [50dlu,default])", "default"));

			//---- ok ----
			ok.setText("Ok");
			ok.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					okActionPerformed(e);
				}
			});
			buttonPanel.add(ok, cc.xy(3, 1));

			//---- cancel ----
			cancel.setText("Cancel");
			cancel.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					cancelActionPerformed(e);
				}
			});
			buttonPanel.add(cancel, cc.xy(5, 1));
		}
		add(buttonPanel, cc.xy(1, 7));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JComponent separator1;
	private JPanel panel1;
	private JLabel label2;
	private JComboBox device;
	private JLabel label3;
	private JComboBox signal;
	private JLabel label4;
	private JComboBox device2;
	private JLabel label5;
	private JComboBox signal2;
	private JLabel label6;
	private JComboBox device3;
	private JLabel label7;
	private JComboBox signal3;
	private JLabel label8;
	private JComboBox device4;
	private JLabel label9;
	private JComboBox signal4;
	private JPanel buttonPanel;
	private JButton ok;
	private JButton cancel;
	// JFormDesigner - End of variables declaration //GEN-END:variables
}
