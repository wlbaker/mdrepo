/*
 * Created by JFormDesigner on Wed Feb 15 14:16:24 CST 2017
 */

package idea.tsoffline.wiz;

import java.util.Iterator;
import java.util.List;

import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.factories.DefaultComponentFactory;
import com.jgoodies.forms.layout.FormLayout;

import idea.PrefUtil;
import idea.gui.WizardPanelInterface;
import idea.tsoffline.AppUtil;
import idea.tsoffline.vizwiz.VizWizard;

/**
 * @author User #1
 */
public class PromoptDescriptionPanel extends JPanel implements WizardPanelInterface {

	JLabel[] label;
	JTextField[] txt;

	public PromoptDescriptionPanel(VizWizard vizWizard, List<String> args) {
		initComponents();

		label = new JLabel[] { label1, label2, label3, label4, label5, label6 };
		txt = new JTextField[] { textField1, textField2, textField3, textField4, textField5, textField6 };

		for (int i = 0; i < label.length; i++) {
			label[i].setText("");
			txt[i].setText("");
			label[i].setVisible(false);
			txt[i].setVisible(false);
		}

		int idx = 0;
		Iterator<String> it = args.iterator();
		it.next(); // ignore RESULT
		while (it.hasNext()) {
			String tok = it.next();
			label[idx].setText(tok);
			label[idx].setVisible(true);
			
			txt[idx].setVisible(true);
			txt[idx].putClientProperty("key", tok);
			String hist = PrefUtil.getUserPref("PROMPT." + tok, null);
			if( hist != null ) {
				txt[idx].setText(hist);
			}
			idx++;
		}

	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		title = compFactory.createSeparator("Destination");
		content = new JPanel();
		label1 = new JLabel();
		textField1 = new JTextField();
		label2 = new JLabel();
		textField2 = new JTextField();
		label3 = new JLabel();
		textField3 = new JTextField();
		label4 = new JLabel();
		textField4 = new JTextField();
		label5 = new JLabel();
		textField5 = new JTextField();
		label6 = new JLabel();
		textField6 = new JTextField();

		// ======== this ========
		setLayout(new FormLayout("20dlu, $lcgap, default:grow", "2*(default, $lgap), default"));
		add(title, CC.xywh(1, 1, 3, 1));

		// ======== content ========
		{
			content.setLayout(new FormLayout("default, $lcgap, default:grow", "5*(default, $lgap), default"));

			// ---- label1 ----
			label1.setText("text");
			content.add(label1, CC.xy(1, 1));
			content.add(textField1, CC.xy(3, 1));

			// ---- label2 ----
			label2.setText("text");
			content.add(label2, CC.xy(1, 3));
			content.add(textField2, CC.xy(3, 3));

			// ---- label3 ----
			label3.setText("text");
			content.add(label3, CC.xy(1, 5));
			content.add(textField3, CC.xy(3, 5));

			// ---- label4 ----
			label4.setText("text");
			content.add(label4, CC.xy(1, 7));
			content.add(textField4, CC.xy(3, 7));

			// ---- label5 ----
			label5.setText("text");
			content.add(label5, CC.xy(1, 9));
			content.add(textField5, CC.xy(3, 9));

			// ---- label6 ----
			label6.setText("text");
			content.add(label6, CC.xy(1, 11));
			content.add(textField6, CC.xy(3, 11));
		}
		add(content, CC.xy(3, 3));
		// JFormDesigner - End of component initialization
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JComponent title;
	private JPanel content;
	private JLabel label1;
	private JTextField textField1;
	private JLabel label2;
	private JTextField textField2;
	private JLabel label3;
	private JTextField textField3;
	private JLabel label4;
	private JTextField textField4;
	private JLabel label5;
	private JTextField textField5;
	private JLabel label6;
	private JTextField textField6;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	@Override
	public void refresh() {
		// TODO Auto-generated method stub

	}

	@Override
	public void previous() {
	}

	@Override
	public boolean next() {
		for (JTextField t : txt) {
			if (t.isVisible()) {
				String key = (String) t.getClientProperty("key");
				AppUtil.setParam("PROMPT", key, t.getText());
				PrefUtil.saveUserPref("PROMPT." + key, t.getText() );
			}
		}
		return true;
	}

	@Override
	public boolean finish() {
		return next();
	}

}
