/*
 * Created by JFormDesigner on Thu Jan 13 14:40:00 CST 2011
 */

package idea.tsoffline.derivsigwiz;

import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.FocusAdapter;
import java.awt.event.FocusEvent;
import java.util.List;

import javax.swing.DefaultComboBoxModel;
import javax.swing.JComboBox;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JPanel;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.DefaultComponentFactory;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;
import com.toedter.calendar.JDateChooser;

import idea.GuiUtil;
import idea.gui.WizardPanelInterface;
import idea.tsoffline.AppModel;
import idea.tsoffline.HPSplitableLayer;
import idea.tsoffline.model.DerivedParamsBase;
import idea.tsoffline.model.OfflineDevice;
import idea.tsoffline.model.OfflineSignal;
import idea.tsoffline.model.OfflineStream;
import idea.tsoffline.persist.EventItem;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class DerivedDetailPanel extends JPanel implements WizardPanelInterface, ParameterProvider {
	private ParameterProvider sub_component;
	public DerivedDetailPanel(HPSplitableLayer sourceSignal, JPanel sub_component) {
		initComponents();

		setName("Analysis Selection");

		DerivedSigWizard wiz = DerivedSigWizard.getInstance();
		wiz.enableNext(false);
		wiz.enableFinish(true);

		startTimeChooser.setDateFormatString("MM/dd/yyyy HH:mm:ss");
		endTimeChooser.setDateFormatString("MM/dd/yyyy HH:mm:ss");

		EventItem[] events = null; 
		GuiUtil.showMessage("FIXME: removed events = AppModel.getPaddedEvents();");

		if (events == null) {
			startEvent.setEnabled(false);
			stopEvent.setEnabled(false);
		} else {
			startEvent.setModel(new DefaultComboBoxModel(events));
			stopEvent.setModel(new DefaultComboBoxModel(events));
		}

		if (sub_component != null) {
			filler.add(sub_component, BorderLayout.CENTER);
		}
		this.sub_component = (ParameterProvider) sub_component;

		populateDevices();
	}

	public void setSourceSignal(HPSplitableLayer sourceSignal) {
		DefaultComboBoxModel model = (DefaultComboBoxModel) deviceCombo.getModel();
		for( int i = 0; i < model.getSize(); i++ ) {
			OfflineDevice dev = (OfflineDevice) model.getElementAt( i );
			List<OfflineStream> childs = dev.getStreams();
			if( childs != null ) {
				GuiUtil.showMessage("FIXME: this is not right...source signal vs source stream");
				if( childs.contains( sourceSignal )) {
					deviceCombo.setSelectedIndex( i );
					break;
				}
			}
		}
		
	}
	
	private void populateDevices() {

		OfflineDevice[] devs = AppModel.getDevicesAsArray();
		deviceCombo.setModel(new DefaultComboBoxModel(devs));

		populateSignals();
	}

	private void populateSignals() {
		List<HPSplitableLayer> streams = null;

		HPSplitableLayer offlineDev = (HPSplitableLayer) deviceCombo.getSelectedItem();
		if (offlineDev != null) {
			//streams = offlineDev.getStreams();
		}

		
		GuiUtil.showMessage("FIXME: set signal in combos");
//		if (signals == null) {
//			signalCombo.setModel( new DefaultComboBoxModel() );
//			signal2Combo.setModel( new DefaultComboBoxModel() );
//		} else {
//			OfflineSignal [] sig_ar = new OfflineSignal[signals.size()];
//			signals.toArray( sig_ar );
//			signalCombo.setModel( new DefaultComboBoxModel( sig_ar ) );
//			signal2Combo.setModel( new DefaultComboBoxModel( sig_ar ) );
//		}
	}

	private void startTimeChooserFocusLost(FocusEvent e) {
		// TODO add your code here
	}

	private void deviceComboActionPerformed(ActionEvent e) {
		populateSignals();
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		separator1 = compFactory.createSeparator("Signal");
		panel1 = new JPanel();
		label4 = new JLabel();
		deviceCombo = new JComboBox();
		signal1Label = new JLabel();
		signalCombo = new JComboBox();
		signal2Label = new JLabel();
		signal2Combo = new JComboBox();
		label1 = new JLabel();
		startEvent = new JComboBox();
		label8 = new JLabel();
		startTimeChooser = new JDateChooser();
		label3 = new JLabel();
		stopEvent = new JComboBox();
		label9 = new JLabel();
		endTimeChooser = new JDateChooser();
		filler = new JPanel();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout(
			"default:grow",
			"default, $lgap, fill:default, $lgap, fill:default:grow"));
		add(separator1, cc.xy(1, 1));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"default, $lcgap, right:default, $lcgap, [120dlu,default], $lcgap, right:default, $lcgap, [120dlu,default]",
				"$ugap, 2*($lgap, default), $ugap, $lgap, default, $lgap, 15dlu, $lgap, $ugap"));

			//---- label4 ----
			label4.setText("Device:");
			panel1.add(label4, cc.xy(3, 3));

			//---- deviceCombo ----
			deviceCombo.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					deviceComboActionPerformed(e);
				}
			});
			panel1.add(deviceCombo, cc.xy(5, 3));

			//---- signal1Label ----
			signal1Label.setText("Signal:");
			panel1.add(signal1Label, cc.xy(7, 3));
			panel1.add(signalCombo, cc.xy(9, 3));

			//---- signal2Label ----
			signal2Label.setText("Signal 2:");
			panel1.add(signal2Label, cc.xy(7, 5));
			panel1.add(signal2Combo, cc.xy(9, 5));

			//---- label1 ----
			label1.setText("Start Event:");
			panel1.add(label1, cc.xy(3, 8));
			panel1.add(startEvent, cc.xy(5, 8));

			//---- label8 ----
			label8.setText("Start Time:");
			panel1.add(label8, cc.xy(7, 8));

			//---- startTimeChooser ----
			startTimeChooser.setDateFormatString("MM/dd/yyyy HH:mm:ss");
			startTimeChooser.addFocusListener(new FocusAdapter() {
				@Override
				public void focusLost(FocusEvent e) {
					startTimeChooserFocusLost(e);
				}
			});
			panel1.add(startTimeChooser, cc.xy(9, 8));

			//---- label3 ----
			label3.setText("Stop Event:");
			panel1.add(label3, cc.xy(3, 10));
			panel1.add(stopEvent, cc.xy(5, 10));

			//---- label9 ----
			label9.setText("Stop Time:");
			panel1.add(label9, cc.xy(7, 10));

			//---- endTimeChooser ----
			endTimeChooser.setDateFormatString("MM/dd/yyyy HH:mm:ss");
			panel1.add(endTimeChooser, cc.xy(9, 10));
		}
		add(panel1, cc.xy(1, 3));

		//======== filler ========
		{
			filler.setLayout(new BorderLayout());
		}
		add(filler, cc.xy(1, 5));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JComponent separator1;
	private JPanel panel1;
	private JLabel label4;
	private JComboBox deviceCombo;
	private JLabel signal1Label;
	private JComboBox signalCombo;
	private JLabel signal2Label;
	private JComboBox signal2Combo;
	private JLabel label1;
	private JComboBox startEvent;
	private JLabel label8;
	private JDateChooser startTimeChooser;
	private JLabel label3;
	private JComboBox stopEvent;
	private JLabel label9;
	private JDateChooser endTimeChooser;
	private JPanel filler;
	// JFormDesigner - End of variables declaration  //GEN-END:variables

	@Override
	public boolean finish() {
		DerivedSigWizard wiz = DerivedSigWizard.getInstance();
		
		return true;
	}

	@Override
	public boolean next() {
		return true;

	}

	@Override
	public void previous() {
		//		AnalWizard wiz = AnalWizard.getInstance();
		//		wiz.enableNext( false );
		//		wiz.enableFinish( true );
	}

	@Override
	public void refresh() {
		// TODO Auto-generated method stub

	}

	@Override
	public DerivedParamsBase getParameters() {
		DerivedParamsBase params = sub_component.getParameters();
		if( params == null ) {
			params = new DerivedParamsBase();
		}
		
		params.setDevice( (OfflineDevice) deviceCombo.getSelectedItem() );
		params.setSignal1( (OfflineSignal) signalCombo.getSelectedItem() );
		params.setSignal2( (OfflineSignal) signal2Combo.getSelectedItem() );
		
		return params;
	}

	public void setSignal1Label(String t) {
		if( t == null ) {
			signal1Label.setVisible( false );
			signalCombo.setVisible( false );
		} else {
			signal1Label.setVisible( true );
			signalCombo.setVisible( true );
			signal1Label.setText(t);
		}
	}

	public void setSignal2Label(String t) {
		if( t == null ) {
			signal2Label.setVisible( false );
			signal2Combo.setVisible( false );
		} else {
			signal2Label.setVisible( true );
			signal2Combo.setVisible( true );
			signal2Label.setText(t);
		}
	}

	
}
