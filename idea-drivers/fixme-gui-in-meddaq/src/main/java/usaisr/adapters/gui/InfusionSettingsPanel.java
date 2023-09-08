/*
 * Created by JFormDesigner on Wed Jul 21 12:07:43 CDT 2010
 */

package idea.adapters.gui;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.LinkedList;
import java.util.List;

import javax.swing.DefaultComboBoxModel;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JComboBox;
import javax.swing.JFormattedTextField;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSeparator;
import javax.swing.SwingConstants;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.layout.FormLayout;

import icuInterface.message.AbstractItem;
import icuInterface.message.NumericItem;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.IntfUtil;
import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;
import idea.gui.CustomizedDocument;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpStream;

/**
 * @author User #2
 */
@Slf4j
@SuppressWarnings("serial")
public class InfusionSettingsPanel extends JPanel {
	private StreamProducer driver;
	private String pumpId;
	
	public InfusionSettingsPanel( StreamProducer driver, String pumpId ) {
		initComponents();

		this.driver = driver;
		this.pumpId = pumpId;
		
		DefaultComboBoxModel model = new DefaultComboBoxModel();
		model.addElement("On");
		model.addElement("Off");
		infuse.setModel( model );
		
		rate.setFormatterFactory( GuiUtil.getIntegerFormatterFactory() );
		vtbi.setFormatterFactory( GuiUtil.getIntegerFormatterFactory() );
		prepareDocs();
	}
	
	private void prepareDocs() {
		CustomizedDocument doc = new CustomizedDocument();
		doc.setMaxChars( 8 );
		doc.setNumeric( true );
		
		rate.setDocument( doc );
		
		doc = new CustomizedDocument();
		doc.setMaxChars( 8 );
		doc.setNumeric( true );
		
		vtbi.setDocument( doc );
	}

	private void applyActionPerformed(ActionEvent e) {
		
		try {
			LinkedList<AbstractItem> settings = new LinkedList<AbstractItem>();
			RpStream s = IntfUtil.getStream( driver.getStaticCapabilities(), StreamID.SETTINGS );
			
			for( RpMetric md : (List<? extends RpMetric>)s.getMetric() ) {
				String varName = (String)md.getLocation();
				if( varName.startsWith(pumpId)) {
					varName = varName.substring(1);
					if( varName.equals("RATE")) {
						addNumericSetting( settings, md, rate );
					} else if (varName.equals("VTBI")) {
						addNumericSetting( settings, md, vtbi );
					} else if (varName.equals("ZERO")) {
						NumericItem item = new NumericItem(md);
						boolean doZero = zeroCheckbox.isSelected();
						item.setValue( (doZero) ? 1 : 0 );
						settings.add( item );
					} else if (varName.equals("INFUSE")) {
						
						int val = 0;
						String s_val = (String) infuse.getSelectedItem();
						if( s_val.equals("On")) {
							val = 1;
						}
						NumericItem item = new NumericItem(md);
						item.setValue( val );
						settings.add( item );
					}
				}
			}
			AbstractItem[] vals = new AbstractItem[ settings.size() ];
			vals = settings.toArray( vals );
			log.error("FIXME: stub driver.requestSettingsUpdate( vals );");
			cancelActionPerformed( null );
		} catch (Exception e1) {
			GuiUtil.showError("Applying infusion settings", e1);
		}
	}

	private void addNumericSetting(LinkedList<AbstractItem> settings, RpMetric md, JFormattedTextField f) {
		String t = f.getText();
		if( t != null ) {
			t = t.trim();
		}
		
		if( t != null & t.length() > 0 ) {
			NumericItem item = new NumericItem(md);
			item.setValue( (Number) f.getValue() );
			settings.add( item );
		}
	}

	private void cancelActionPerformed(ActionEvent e) {
		GuiUtil.closeDialog( this );
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		panel2 = new JPanel();
		label1 = new JLabel();
		rate = new JFormattedTextField();
		label3 = new JLabel();
		vtbi = new JFormattedTextField();
		label2 = new JLabel();
		zeroCheckbox = new JCheckBox();
		label4 = new JLabel();
		infuse = new JComboBox();
		separator1 = new JSeparator();
		panel1 = new JPanel();
		apply = new JButton();
		cancel = new JButton();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout("default:grow",
				"12dlu, $lgap, default:grow, 2*($lgap, default), $lgap, default:grow, 2*($lgap, default)"));

		//======== panel2 ========
		{
			panel2.setLayout(new FormLayout("default:grow, $lcgap, right:default, $lcgap, 60dlu, $lcgap, default:grow",
					"3*(default, $lgap), default"));

			//---- label1 ----
			label1.setText("Rate:");
			panel2.add(label1, CC.xy(3, 1));

			//---- rate ----
			rate.setHorizontalAlignment(SwingConstants.TRAILING);
			panel2.add(rate, CC.xy(5, 1));

			//---- label3 ----
			label3.setText("Volume to be Infused:");
			panel2.add(label3, CC.xy(3, 3));

			//---- vtbi ----
			vtbi.setHorizontalAlignment(SwingConstants.TRAILING);
			panel2.add(vtbi, CC.xy(5, 3));

			//---- label2 ----
			label2.setText("Zero Total Volume:");
			panel2.add(label2, CC.xy(3, 5));

			//---- zeroCheckbox ----
			zeroCheckbox.setText("Yes");
			panel2.add(zeroCheckbox, CC.xy(5, 5));

			//---- label4 ----
			label4.setText("Infusion:");
			panel2.add(label4, CC.xy(3, 7));
			panel2.add(infuse, CC.xy(5, 7));
		}
		add(panel2, CC.xy(1, 5));
		add(separator1, CC.xy(1, 11));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout("default:grow, 2*($lcgap, [50dlu,default])", "default"));

			//---- apply ----
			apply.setText("Apply");
			apply.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					applyActionPerformed(e);
				}
			});
			panel1.add(apply, CC.xy(3, 1));

			//---- cancel ----
			cancel.setText("Cancel");
			cancel.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					cancelActionPerformed(e);
				}
			});
			panel1.add(cancel, CC.xy(5, 1));
		}
		add(panel1, CC.xy(1, 13));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	private JPanel panel2;
	private JLabel label1;
	private JFormattedTextField rate;
	private JLabel label3;
	private JFormattedTextField vtbi;
	private JLabel label2;
	private JCheckBox zeroCheckbox;
	private JLabel label4;
	private JComboBox infuse;
	private JSeparator separator1;
	private JPanel panel1;
	private JButton apply;
	private JButton cancel;
	// JFormDesigner - End of variables declaration  //GEN-END:variables
}
