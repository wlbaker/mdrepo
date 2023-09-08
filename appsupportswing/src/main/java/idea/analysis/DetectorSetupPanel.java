/*
 * Created by JFormDesigner on Thu May 26 13:06:34 CDT 2011
 */

package idea.analysis;

import java.awt.event.ActionEvent;
import java.util.List;
import java.util.Map;

import javax.swing.ComboBoxModel;
import javax.swing.DefaultComboBoxModel;
import javax.swing.JComboBox;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JPanel;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.factories.DefaultComponentFactory;
import com.jgoodies.forms.layout.FormLayout;

import icuInterface.RpUtil;
import idea.message.StreamID;
import idea.schema.rp.RpAnalysis;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpHardware;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpStudy;
import idea.schema.rp.StringStringMap;
import idea.ConfigurationInfo;
import idea.gui.WizardMasterInterface;
import idea.gui.WizardPanelInterface;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class DetectorSetupPanel extends JPanel implements WizardPanelInterface {
	private RpAnalysis analysis;
	private RpStudy study;

	public DetectorSetupPanel(WizardMasterInterface intf, RpStudy study, RpAnalysis anal) {
		initComponents();

		this.study = study;
		this.analysis = anal;

		refresh();
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


	private void save() {
		Map<String, String> params = analysis.getParam();
		saveParam(params, "dev", device.getSelectedItem());
		saveParam(params, "stream", StreamID.WAVEFORM.getName());
		saveParam(params, "signal", signal.getSelectedItem());
		saveParam(params, "detector", algorithm.getSelectedItem());

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

	@Override
	public void refresh() {

		populateSignals( device );
		deviceActionPerformed(null);
		algorithm.setModel(new DefaultComboBoxModel(ConfigurationInfo.getDetectorList()));

		StringStringMap params = analysis.getParam();
		if( params == null ) {
			params = new StringStringMap();
			analysis.setParam( params );
		}
		setSelector(params, "dev", device);
		setSelector(params, "signal", signal);
		setSelector(params, "detector", algorithm);
	}

	protected void populateSignals(JComboBox device) {
		DefaultComboBoxModel dev1_model = new DefaultComboBoxModel();
		if (study != null && study.getHardware() != null) {
			RpHardware hw = study.getHardware().get(0);
			if (hw != null) {
				List<RpDevice> devs = hw.getDevices();
				for (RpDevice dev : devs) {
					List streams = dev.getStreams();
					if( streams == null || streams.size() == 0 ) {
						// ignore
					} else {
						dev1_model.addElement(new DevWrapper(dev));
					}
				}
			}
		}

		device.setModel(dev1_model);
	}


	@Override
	public void previous() {
		// TODO Auto-generated method stub
		
	}

	@Override
	public boolean next() {
		String a_name = analysis.getName();
		if (a_name == null) {
			a_name = "untitled";
		}
		int pos = a_name.indexOf(':');
		if (pos > 0) {
			a_name = a_name.substring(0, pos);
		}

		a_name = a_name + ": " + algorithm.getSelectedItem();
		analysis.setName(a_name);

		save();
		return true;
	}

	@Override
	public boolean finish() {
		return next();
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		separator1 = compFactory.createSeparator("Detector Setup");
		panel1 = new JPanel();
		label2 = new JLabel();
		device = new JComboBox();
		label3 = new JLabel();
		signal = new JComboBox();
		label1 = new JLabel();
		algorithm = new JComboBox();
		buttonPanel = new JPanel();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout(
			"default:grow",
			"2*(default, $lgap), default:grow, $lgap, default"));
		add(separator1, CC.xy(1, 1));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"right:[100dlu,default], $lcgap, [100dlu,default]",
				"[12dlu,default], 5*($lgap, default)"));

			//---- label2 ----
			label2.setText("Source Device:");
			panel1.add(label2, CC.xy(1, 3));

			//---- device ----
			device.addActionListener(e -> deviceActionPerformed(e));
			panel1.add(device, CC.xy(3, 3));

			//---- label3 ----
			label3.setText("Source Signal:");
			panel1.add(label3, CC.xy(1, 5));
			panel1.add(signal, CC.xy(3, 5));

			//---- label1 ----
			label1.setText("Detection Algorithm:");
			panel1.add(label1, CC.xy(1, 9));
			panel1.add(algorithm, CC.xy(3, 9));
		}
		add(panel1, CC.xy(1, 3));

		//======== buttonPanel ========
		{
			buttonPanel.setLayout(new FormLayout(
				"default:grow, 2*($lcgap, [50dlu,default])",
				""));
		}
		add(buttonPanel, CC.xy(1, 7));
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
	private JLabel label1;
	private JComboBox algorithm;
	private JPanel buttonPanel;
	// JFormDesigner - End of variables declaration //GEN-END:variables

}
