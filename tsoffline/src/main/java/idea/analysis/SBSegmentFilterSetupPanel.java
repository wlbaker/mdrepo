/*
 * Created by JFormDesigner on Sun Feb 08 16:15:43 CST 2015
 */

package idea.analysis;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.util.List;

import javax.swing.ButtonGroup;
import javax.swing.ComboBoxModel;
import javax.swing.DefaultComboBoxModel;
import javax.swing.JComboBox;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JRadioButton;

import org.jdesktop.beansbinding.AutoBinding.UpdateStrategy;
import org.jdesktop.beansbinding.BeanProperty;
import org.jdesktop.beansbinding.BindingGroup;
import org.jdesktop.beansbinding.Bindings;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.DefaultComponentFactory;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import icuInterface.RpUtil;
import idea.schema.rp.RpAnalysis;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpStudy;
import idea.gui.WizardPanelInterface;
import idea.tsoffline.AppModel;
import idea.tsoffline.model.OfflineDevice;
import idea.tsoffline.model.OfflineSignal;
import idea.tsoffline.model.OfflineStream;

/**
 * @author User #1
 */
public class SBSegmentFilterSetupPanel extends JPanel implements WizardPanelInterface {
	private RpAnalysis anal;

	public SBSegmentFilterSetupPanel(RpStudy study, RpAnalysis anal) {
		initComponents();

		this.anal = anal;

		initDevicesCombo();
	}

	private void initDevicesCombo() {
		ComboBoxModel<OfflineDevice> comboModel = new DefaultComboBoxModel<OfflineDevice>(AppModel.getDevicesAsArray());
		sourceDevice.setModel(comboModel);
		sourceDevice.setEnabled(true);
	}

	private void sourceDeviceActionPerformed(ActionEvent e) {
		System.out.println("dev-item action ignored");
	}

	private void sourceDeviceItemStateChanged(ItemEvent e) {
		if (e.getStateChange() == ItemEvent.SELECTED) {

			System.out.println("setting source streams");
			OfflineDevice dev = (OfflineDevice) sourceDevice.getSelectedItem();
			List<OfflineStream> streams = dev.getStreams();
			OfflineStream[] arr = new OfflineStream[streams.size()];
			streams.toArray(arr);
			ComboBoxModel<OfflineStream> comboModel = new DefaultComboBoxModel<OfflineStream>(arr);
			sourceStream.setModel(comboModel);
			sourceStream.setEnabled(true);

			System.out.println("set source streams: " + arr.length);
			for (OfflineStream s : arr) {
				System.out.println("* str: " + s);
			}
		}
	}

	private void sourceStreamActionPerformed(ActionEvent e) {

		System.out.println("setting source sigs");
		OfflineStream stream = (OfflineStream) sourceStream.getSelectedItem();
		List<RpMetric> sigs = stream.getMetric();
		OfflineSignal[] arr = new OfflineSignal[sigs.size()];
		sigs.toArray(arr);
		ComboBoxModel<OfflineSignal> comboModel = new DefaultComboBoxModel<OfflineSignal>(arr);
		sourceSignal.setModel(comboModel);
		sourceSignal.setEnabled(true);

		System.out.println("set source sigs: " + arr.length);
		for (OfflineSignal s : arr) {
			System.out.println("* sig: " + s);
		}
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		separator1 = compFactory.createSeparator("Source Signal");
		panel1 = new JPanel();
		label6 = new JLabel();
		sourceDevice = new JComboBox<>();
		label7 = new JLabel();
		sourceStream = new JComboBox<>();
		label1 = new JLabel();
		sourceSignal = new JComboBox<>();
		separator2 = compFactory.createSeparator("Range");
		panel2 = new JPanel();
		allDataRadio = new JRadioButton();
		eventRangeRadio = new JRadioButton();
		label2 = new JLabel();
		startEvent = new JComboBox();
		label5 = new JLabel();
		endEvent = new JComboBox();
		timeRangeRadio = new JRadioButton();
		label3 = new JLabel();
		label4 = new JLabel();
		sourceSelectionBox4 = new JComboBox();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout("default:grow", "3*(default, $lgap), default"));
		add(separator1, cc.xy(1, 1));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout("30dlu, $lcgap, right:default, $lcgap, [150dlu,default], $lcgap, default",
					"4*(default, $lgap), default"));

			//---- label6 ----
			label6.setText("Source Device:");
			panel1.add(label6, cc.xy(3, 3));

			//---- sourceDevice ----
			sourceDevice.setEnabled(false);
			sourceDevice.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					sourceDeviceActionPerformed(e);
				}
			});
			sourceDevice.addItemListener(new ItemListener() {
				@Override
				public void itemStateChanged(ItemEvent e) {
					sourceDeviceItemStateChanged(e);
				}
			});
			panel1.add(sourceDevice, cc.xy(5, 3));

			//---- label7 ----
			label7.setText("Source Stream:");
			panel1.add(label7, cc.xy(3, 5));

			//---- sourceStream ----
			sourceStream.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					sourceStreamActionPerformed(e);
				}
			});
			panel1.add(sourceStream, cc.xy(5, 5));

			//---- label1 ----
			label1.setText("Source Signal:");
			panel1.add(label1, cc.xy(3, 7));
			panel1.add(sourceSignal, cc.xy(5, 7));
		}
		add(panel1, cc.xy(1, 3));
		add(separator2, cc.xy(1, 5));

		//======== panel2 ========
		{
			panel2.setLayout(new FormLayout(
					"30dlu, $lcgap, default, $lcgap, right:default, $lcgap, [50dlu,default], $lcgap, default",
					"7*(default, $lgap), default"));

			//---- allDataRadio ----
			allDataRadio.setText("All Data");
			panel2.add(allDataRadio, cc.xy(3, 3));

			//---- eventRangeRadio ----
			eventRangeRadio.setText("Event Range");
			panel2.add(eventRangeRadio, cc.xy(3, 5));

			//---- label2 ----
			label2.setText("Start Event:");
			panel2.add(label2, cc.xy(5, 7));
			panel2.add(startEvent, cc.xy(7, 7));

			//---- label5 ----
			label5.setText("End Event:");
			panel2.add(label5, cc.xy(5, 9));
			panel2.add(endEvent, cc.xy(7, 9));

			//---- timeRangeRadio ----
			timeRangeRadio.setText("Time Range");
			panel2.add(timeRangeRadio, cc.xy(3, 11));

			//---- label3 ----
			label3.setText("Start Time:");
			panel2.add(label3, cc.xy(5, 13));

			//---- label4 ----
			label4.setText("End Time:");
			panel2.add(label4, cc.xy(5, 15));
			panel2.add(sourceSelectionBox4, cc.xy(7, 15));
		}
		add(panel2, cc.xy(1, 7));

		//---- buttonGroup1 ----
		ButtonGroup buttonGroup1 = new ButtonGroup();
		buttonGroup1.add(allDataRadio);
		buttonGroup1.add(eventRangeRadio);
		buttonGroup1.add(timeRangeRadio);

		//---- bindings ----
		bindingGroup = new BindingGroup();
		bindingGroup.addBinding(Bindings.createAutoBinding(UpdateStrategy.READ, eventRangeRadio,
				BeanProperty.create("selected"), startEvent, BeanProperty.create("enabled")));
		bindingGroup.addBinding(Bindings.createAutoBinding(UpdateStrategy.READ_WRITE, eventRangeRadio,
				BeanProperty.create("selected"), endEvent, BeanProperty.create("enabled")));
		bindingGroup.bind();
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	private JComponent separator1;
	private JPanel panel1;
	private JLabel label6;
	private JComboBox<OfflineDevice> sourceDevice;
	private JLabel label7;
	private JComboBox<OfflineStream> sourceStream;
	private JLabel label1;
	private JComboBox<OfflineSignal> sourceSignal;
	private JComponent separator2;
	private JPanel panel2;
	private JRadioButton allDataRadio;
	private JRadioButton eventRangeRadio;
	private JLabel label2;
	private JComboBox startEvent;
	private JLabel label5;
	private JComboBox endEvent;
	private JRadioButton timeRangeRadio;
	private JLabel label3;
	private JLabel label4;
	private JComboBox sourceSelectionBox4;
	private BindingGroup bindingGroup;

	// JFormDesigner - End of variables declaration  //GEN-END:variables
	@Override
	public void refresh() {
		// TODO Auto-generated method stub

	}

	@Override
	public void previous() {
		// TODO Auto-generated method stub

	}

	@Override
	public boolean next() {
		OfflineDevice dev = (OfflineDevice) sourceDevice.getSelectedItem();
		OfflineStream stream = (OfflineStream) sourceStream.getSelectedItem();
		OfflineSignal sig = (OfflineSignal) sourceSignal.getSelectedItem();

		boolean ok = (dev != null && stream != null && sig != null);
		if (ok) {
			RpUtil.setParam(anal, "dev", dev.getName());
			RpUtil.setParam(anal, "stream", stream.getSid().getName());
			RpUtil.setParam(anal, "sig", sig.getLocation());

		}
		return ok;
	}

	@Override
	public boolean finish() {
		return next();
	}
}
