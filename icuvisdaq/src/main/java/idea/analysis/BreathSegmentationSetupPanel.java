/*
 * Created by JFormDesigner on Tue May 17 17:53:13 CDT 2011
 */

package idea.analysis;


import icuInterface.RpUtil;
import idea.message.StreamID;
import idea.schema.rp.RpAnalysis;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpHardware;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpStudy;
import idea.schema.rp.StringStringMap;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.text.DecimalFormat;
import java.text.NumberFormat;
import java.util.List;

import javax.swing.ComboBoxModel;
import javax.swing.DefaultComboBoxModel;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JComboBox;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

import org.jdesktop.beansbinding.AutoBinding.UpdateStrategy;
import org.jdesktop.beansbinding.BeanProperty;
import org.jdesktop.beansbinding.BindingGroup;
import org.jdesktop.beansbinding.Bindings;

import idea.GuiUtil;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.DefaultComponentFactory;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

/**
 * @author User #2
 */


@SuppressWarnings("serial")
public class BreathSegmentationSetupPanel extends JPanel {

	NumberFormat df1 = new DecimalFormat("0.#");
	private RpAnalysis analysis;

	public BreathSegmentationSetupPanel(RpStudy study, RpAnalysis anal) {
		initComponents();

		this.analysis = anal;
		refresh(study);
		
		 StringStringMap params = analysis.getParam();

		String rawFileName = params.get( "raw");
		if( rawFileName == null ) {
			rawOutputCheckbox.setSelected( true );
			rawOutputFile.setText("c:/tmp/sbco2_raw.txt");
		} else if ("NONE".equals(rawFileName)) {
			rawOutputCheckbox.setSelected( false );
			rawOutputFile.setText("");
		} else {
			rawOutputCheckbox.setSelected( true );
			rawOutputFile.setText(rawFileName);
		}
	}

	private void refresh(RpStudy study) {
		RpHardware hw = study.getHardware().get(0);
		List<RpDevice> devs = hw.getDevices();
		DefaultComboBoxModel dev1_model = new DefaultComboBoxModel();
		DefaultComboBoxModel dev2_model = new DefaultComboBoxModel();
		for (RpDevice dev : devs) {
			dev1_model.addElement(new DevWrapper(dev));
			dev2_model.addElement(new DevWrapper(dev));
		}

		gasDeviceSelector.setModel(dev1_model);
		numericsDeviceSelector.setModel(dev2_model);
	}

	private void numdeviceSelectorActionPerformed(ActionEvent e) {
		DevWrapper wrapper = (DevWrapper) numericsDeviceSelector.getSelectedItem();
		RpDevice intf = wrapper.getDevice();

		if (intf == null) {
			return;
		}
		List<? extends RpMetric> metrics = RpUtil.getMetrics(intf, StreamID.MEASUREMENT);
		if (metrics == null) {
			return;
		}

		Object[] items = new Object[metrics.size()];

		int i = 0;
		for (RpMetric wave : metrics) {
			items[i++] = new WfWrapper(wave);
		}

		prepareSelector(complianceSelector, items, "C");
		prepareSelector(resistanceSelector, items, "R");
		prepareSelector(respRateSelector, items, "RR");
		prepareSelector(tvSelector, items, "TV");
		prepareSelector(fio2Selector, items, "FIO2");
		prepareSelector(peepSelector, items, "PEEP");
		prepareSelector(etco2Selector, items, "ETCO2");

	}

	private void _deviceSelectorActionPerformed(ActionEvent e) throws IOException {
		DevWrapper wrapper = (DevWrapper) gasDeviceSelector.getSelectedItem();
		RpDevice intf = wrapper.getDevice();
		if (intf == null) {
			return;
		}

		List<? extends RpMetric> waves = RpUtil.getMetrics(intf, StreamID.WAVEFORM);
		Object[] items = new Object[waves.size()];
		int i = 0;
		for (RpMetric wave : waves) {
			items[i++] = new WfWrapper(wave);
		}

		prepareSelector(flowSelector, items, "FLOW");
		prepareSelector(co2Selector, items, "CO2");
		prepareSelector(awpSelector, items, "PAW");

		if (awpSelector.getSelectedIndex() < 0) {
			autoselect(awpSelector, "AIRWAY");
		}
	}

	private void prepareSelector(JComboBox cb, Object[] items, String key) {
		cb.setModel(new DefaultComboBoxModel(items));
		cb.setName(key);
		autoselect(cb, key);
	}

	private void autoselect(JComboBox combo, String patt) {
		ComboBoxModel model = combo.getModel();
		for (int i = 0; i < model.getSize(); i++) {
			String title = model.getElementAt(i).toString().toUpperCase();
			if (title.indexOf(patt) >= 0) {
				combo.setSelectedIndex(i);
				return;
			}
		}
		combo.setSelectedIndex(-1);
	}

	private void okActionPerformed(ActionEvent e) {
		StringStringMap params = analysis.getParam();
		saveParam(params, "NDEV", numericsDeviceSelector.getSelectedItem());
		saveParam(params, "C", complianceSelector.getSelectedItem());
		saveParam(params, "R", resistanceSelector.getSelectedItem());
		saveParam(params, "RR", respRateSelector.getSelectedItem());
		saveParam(params, "TV", tvSelector.getSelectedItem());
		saveParam(params, "FIO2", fio2Selector.getSelectedItem());
		saveParam(params, "PEEP", peepSelector.getSelectedItem());
		saveParam(params, "ETCO2", etco2Selector.getSelectedItem());

		saveParam(params, "DEV", gasDeviceSelector.getSelectedItem());
		saveParam(params, "FLOW", flowSelector.getSelectedItem());
		saveParam(params, "CO2", co2Selector.getSelectedItem());
		saveParam(params, "PAW", awpSelector.getSelectedItem());
		
		if( rawOutputCheckbox.isSelected() ) {
			params.put( "raw", rawOutputFile.getText());
		} else {
			params.put( "raw", "NONE");
		}
		cancelActionPerformed(null);
	}

	private void saveParam(StringStringMap params, String key, Object wrapper) {
		if( wrapper == null ) {
			return; // nothing to save
		}
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
			assert (false) : "Unexpected item in combo: " + key + "/" + wrapper;
		}

		params.put(key, value);
	}

	private void cancelActionPerformed(ActionEvent e) {
		GuiUtil.closeDialog(this);
	}

	private void deviceSelectorActionPerformed(ActionEvent e) {
		try {
			_deviceSelectorActionPerformed(e);
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		separator2 = compFactory.createSeparator("Numerics Device");
		panel2 = new JPanel();
		label1 = new JLabel();
		numericsDeviceSelector = new JComboBox();
		label3 = new JLabel();
		complianceSelector = new JComboBox();
		label4 = new JLabel();
		resistanceSelector = new JComboBox();
		label11 = new JLabel();
		respRateSelector = new JComboBox();
		label12 = new JLabel();
		tvSelector = new JComboBox();
		label5 = new JLabel();
		fio2Selector = new JComboBox();
		label6 = new JLabel();
		peepSelector = new JComboBox();
		label2 = new JLabel();
		etco2Selector = new JComboBox();
		separator1 = compFactory.createSeparator("Air/CO2 Device");
		panel3 = new JPanel();
		label7 = new JLabel();
		gasDeviceSelector = new JComboBox();
		label8 = new JLabel();
		flowSelector = new JComboBox();
		label9 = new JLabel();
		co2Selector = new JComboBox();
		label10 = new JLabel();
		awpSelector = new JComboBox();
		panel4 = new JPanel();
		rawOutputCheckbox = new JCheckBox();
		rawOutputFile = new JTextField();
		panel1 = new JPanel();
		ok = new JButton();
		cancel = new JButton();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout(
			"default:grow",
			"4*(default, $lgap), [30dlu,default]:grow, $lgap, default"));
		add(separator2, cc.xy(1, 1));

		//======== panel2 ========
		{
			panel2.setLayout(new FormLayout(
				"default, $lcgap, right:[60dlu,default], $lcgap, [100dlu,default], $lcgap, default, $lcgap, right:[70dlu,default], $lcgap, [100dlu,default]",
				"8*(default, $lgap), default"));

			//---- label1 ----
			label1.setText("Device:");
			panel2.add(label1, cc.xy(3, 3));

			//---- numericsDeviceSelector ----
			numericsDeviceSelector.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					numdeviceSelectorActionPerformed(e);
				}
			});
			panel2.add(numericsDeviceSelector, cc.xy(5, 3));

			//---- label3 ----
			label3.setText("Compliance:");
			panel2.add(label3, cc.xy(9, 3));
			panel2.add(complianceSelector, cc.xy(11, 3));

			//---- label4 ----
			label4.setText("Resistance:");
			panel2.add(label4, cc.xy(9, 5));
			panel2.add(resistanceSelector, cc.xy(11, 5));

			//---- label11 ----
			label11.setText("Respiratory Rate:");
			panel2.add(label11, cc.xy(9, 7));
			panel2.add(respRateSelector, cc.xy(11, 7));

			//---- label12 ----
			label12.setText("Tidal Volume:");
			panel2.add(label12, cc.xy(9, 9));
			panel2.add(tvSelector, cc.xy(11, 9));

			//---- label5 ----
			label5.setText("FIO2:");
			panel2.add(label5, cc.xy(9, 11));
			panel2.add(fio2Selector, cc.xy(11, 11));

			//---- label6 ----
			label6.setText("PEEP:");
			panel2.add(label6, cc.xy(9, 13));
			panel2.add(peepSelector, cc.xy(11, 13));

			//---- label2 ----
			label2.setText("EtCO2:");
			panel2.add(label2, cc.xy(9, 15));
			panel2.add(etco2Selector, cc.xy(11, 15));
		}
		add(panel2, cc.xy(1, 3));
		add(separator1, cc.xy(1, 5));

		//======== panel3 ========
		{
			panel3.setLayout(new FormLayout(
				"default, $lcgap, right:[60dlu,default], $lcgap, [100dlu,pref], $lcgap, default, $lcgap, right:[70dlu,default], $lcgap, [100dlu,default], $lcgap, right:[30dlu,default]",
				"3*(default, $lgap), default"));

			//---- label7 ----
			label7.setText("Device:");
			panel3.add(label7, cc.xy(3, 3));

			//---- gasDeviceSelector ----
			gasDeviceSelector.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					deviceSelectorActionPerformed(e);
				}
			});
			panel3.add(gasDeviceSelector, cc.xy(5, 3));

			//---- label8 ----
			label8.setText("Flow:");
			panel3.add(label8, cc.xy(9, 3));
			panel3.add(flowSelector, cc.xy(11, 3));

			//---- label9 ----
			label9.setText("CO2:");
			panel3.add(label9, cc.xy(9, 5));
			panel3.add(co2Selector, cc.xy(11, 5));

			//---- label10 ----
			label10.setText("AWP:");
			panel3.add(label10, cc.xy(9, 7));
			panel3.add(awpSelector, cc.xy(11, 7));
		}
		add(panel3, cc.xy(1, 7));

		//======== panel4 ========
		{
			panel4.setLayout(new FormLayout(
				"default, $lcgap, [220dlu,default], $lcgap, default",
				"default"));

			//---- rawOutputCheckbox ----
			rawOutputCheckbox.setText("Raw Output:");
			panel4.add(rawOutputCheckbox, cc.xy(1, 1));
			panel4.add(rawOutputFile, cc.xy(3, 1));
		}
		add(panel4, cc.xy(1, 9));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"default:grow, 2*($lcgap, [50dlu,default])",
				"default"));

			//---- ok ----
			ok.setText("Ok");
			ok.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					okActionPerformed(e);
				}
			});
			panel1.add(ok, cc.xy(3, 1));

			//---- cancel ----
			cancel.setText("Cancel");
			cancel.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					cancelActionPerformed(e);
				}
			});
			panel1.add(cancel, cc.xy(5, 1));
		}
		add(panel1, cc.xy(1, 11));

		//---- bindings ----
		bindingGroup = new BindingGroup();
		bindingGroup.addBinding(Bindings.createAutoBinding(UpdateStrategy.READ,
			rawOutputCheckbox, BeanProperty.create("selected"),
			rawOutputFile, BeanProperty.create("enabled")));
		bindingGroup.bind();
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JComponent separator2;
	private JPanel panel2;
	private JLabel label1;
	private JComboBox numericsDeviceSelector;
	private JLabel label3;
	private JComboBox complianceSelector;
	private JLabel label4;
	private JComboBox resistanceSelector;
	private JLabel label11;
	private JComboBox respRateSelector;
	private JLabel label12;
	private JComboBox tvSelector;
	private JLabel label5;
	private JComboBox fio2Selector;
	private JLabel label6;
	private JComboBox peepSelector;
	private JLabel label2;
	private JComboBox etco2Selector;
	private JComponent separator1;
	private JPanel panel3;
	private JLabel label7;
	private JComboBox gasDeviceSelector;
	private JLabel label8;
	private JComboBox flowSelector;
	private JLabel label9;
	private JComboBox co2Selector;
	private JLabel label10;
	private JComboBox awpSelector;
	private JPanel panel4;
	private JCheckBox rawOutputCheckbox;
	private JTextField rawOutputFile;
	private JPanel panel1;
	private JButton ok;
	private JButton cancel;
	private BindingGroup bindingGroup;
	// JFormDesigner - End of variables declaration //GEN-END:variables

}
