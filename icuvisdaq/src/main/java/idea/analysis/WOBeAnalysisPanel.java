/*
 * Created by JFormDesigner on Thu Sep 12 12:40:59 CDT 2013
 */

package idea.analysis;

import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.PersistentItem;
import idea.schema.rp.RpAnalysis;

import java.awt.BorderLayout;

import javax.swing.JLabel;
import javax.swing.JPanel;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

/**
 * @author User #1
 */
public class WOBeAnalysisPanel extends JPanel implements AnalysisPanelInterface, StreamConsumer {
	public WOBeAnalysisPanel(StreamProducer[] producers, RpAnalysis analConfs) {
		initComponents();
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		panel1 = new JPanel();
		breathPanel = new JPanel();
		trendPanel = new JPanel();
		panel2 = new JPanel();
		label1 = new JLabel();
		label2 = new JLabel();
		label3 = new JLabel();
		label4 = new JLabel();
		label5 = new JLabel();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setLayout(new FormLayout(
			"default:grow",
			"fill:[50dlu,default], 2*($lgap, fill:default)"));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"default:grow, $lcgap, default:grow",
				"fill:default:grow"));

			//======== breathPanel ========
			{
				breathPanel.setLayout(new BorderLayout());
			}
			panel1.add(breathPanel, cc.xy(1, 1));

			//======== trendPanel ========
			{
				trendPanel.setLayout(new BorderLayout());
			}
			panel1.add(trendPanel, cc.xy(3, 1));
		}
		add(panel1, cc.xy(1, 1));

		//======== panel2 ========
		{
			panel2.setLayout(new FormLayout(
				"right:[50dlu,default], 3*($lcgap, default)",
				"6*(default, $lgap), default"));

			//---- label1 ----
			label1.setText("Pmax");
			panel2.add(label1, cc.xy(1, 1));

			//---- label2 ----
			label2.setText("Pmin");
			panel2.add(label2, cc.xy(1, 3));

			//---- label3 ----
			label3.setText("P0.1");
			panel2.add(label3, cc.xy(1, 7));

			//---- label4 ----
			label4.setText("PArea");
			panel2.add(label4, cc.xy(1, 9));

			//---- label5 ----
			label5.setText("m3");
			panel2.add(label5, cc.xy(1, 13));
		}
		add(panel2, cc.xy(1, 3));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JPanel panel1;
	private JPanel breathPanel;
	private JPanel trendPanel;
	private JPanel panel2;
	private JLabel label1;
	private JLabel label2;
	private JLabel label3;
	private JLabel label4;
	private JLabel label5;
	// JFormDesigner - End of variables declaration  //GEN-END:variables
	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void clear() {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void autoscale() {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void tick() {
		// TODO Auto-generated method stub
		
	}

	@Override
	public StreamProducer[] getSignalProducers() {
		StreamProducer [] producers = null; // new SignalProducer[] { ent, mse, detector, hrv };
		return producers;
	}
}
