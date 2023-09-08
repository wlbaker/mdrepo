/*
 * Created by JFormDesigner on Wed Jul 06 11:00:55 CDT 2011
 */

package idea.adapters.gui;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import idea.conf.DeviceCapabilities;
import idea.conf.DeviceConfiguration;
import idea.intf.AbstractStreamProducer;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.PersistentItem;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class ManualEntryPanel extends JPanel implements StreamConsumer {
	
	AbstractStreamProducer producer = new AbstractStreamProducer() {

		@Override
		public DeviceCapabilities getStaticCapabilities() {
			// TODO Auto-generated method stub
			return null;
		}

		@Override
		public DeviceConfiguration getConfiguration() {
			// TODO Auto-generated method stub
			return null;
		}

 } ;
			

	public ManualEntryPanel(StreamProducer driver) {
		initComponents();
	}

	private void commitActionPerformed(ActionEvent e) {
		// TODO add your code here
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		panel1 = new JPanel();
		prompt1 = new JLabel();
		field1 = new JTextField();
		prompt2 = new JLabel();
		field2 = new JTextField();
		prompt3 = new JLabel();
		field3 = new JTextField();
		panel2 = new JPanel();
		commit = new JButton();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout(
			"[50dlu,default]:grow",
			"2*(default, $lgap), default:grow, 2*($lgap, default)"));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"right:[50dlu,default], $lcgap, [50dlu,default]",
				"2*(default, $lgap), default"));

			//---- prompt1 ----
			prompt1.setText("Prompt 1:");
			panel1.add(prompt1, cc.xy(1, 1));
			panel1.add(field1, cc.xy(3, 1));

			//---- prompt2 ----
			prompt2.setText("Prompt 2:");
			panel1.add(prompt2, cc.xy(1, 3));
			panel1.add(field2, cc.xy(3, 3));

			//---- prompt3 ----
			prompt3.setText("Prompt 3:");
			panel1.add(prompt3, cc.xy(1, 5));
			panel1.add(field3, cc.xy(3, 5));
		}
		add(panel1, cc.xy(1, 3));

		//======== panel2 ========
		{
			panel2.setLayout(new FormLayout(
				"default, $lcgap, default:grow, $lcgap, default",
				"default"));

			//---- commit ----
			commit.setText("Commit");
			commit.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					commitActionPerformed(e);
				}
			});
			panel2.add(commit, cc.xy(5, 1));
		}
		add(panel2, cc.xy(1, 9));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	private JPanel panel1;
	private JLabel prompt1;
	private JTextField field1;
	private JLabel prompt2;
	private JTextField field2;
	private JLabel prompt3;
	private JTextField field3;
	private JPanel panel2;
	private JButton commit;
	// JFormDesigner - End of variables declaration  //GEN-END:variables


	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {
		System.err.println( "[ManualEntryPanel] signalEvent should not be called?"); // FIXME: need signal handler???
	}
}
