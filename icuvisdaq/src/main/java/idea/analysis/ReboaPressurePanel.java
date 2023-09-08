/*
 * Created by JFormDesigner on Tue Oct 18 12:58:28 CDT 2011
 */

package idea.analysis;


import com.jgoodies.forms.factories.*;
import idea.display.simple.TwoValuePanel;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.PersistentItem;
import idea.schema.rp.RpAnalysis;

import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.text.DecimalFormat;
import java.text.NumberFormat;

import javax.swing.JComponent;
import javax.swing.JFormattedTextField;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSeparator;
import javax.swing.SwingConstants;

import idea.GuiUtil;
import idea.analysis.event.SBCO2Block;
import idea.analysis.ventilator.SBCO2;
import idea.chart.SignalChart;
import idea.chart.SignalPanel;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.DefaultComponentFactory;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class ReboaPressurePanel extends JPanel {
	private final static NumberFormat df1 = new DecimalFormat("0.#");
	private final static NumberFormat df3 = new DecimalFormat("0.000");
	
	private static final RpAnalysis analysisInfo;
	static { 
		analysisInfo = new RpAnalysis();
		analysisInfo.setName("Reboa Pressure Analysis");
		analysisInfo.setAnalysisClass( ReboaPressurePanel.class.getCanonicalName() );
		// analysisInfo.
	}
	
	private TwoValuePanel shuntMetricPanel;
	private SignalPanel shuntTrendPanel;
	
	public ReboaPressurePanel(StreamProducer producer, RpAnalysis analysis) {
		initComponents();
		
		initMoreComponents();
		
		map.setFormatterFactory(GuiUtil.getNumberFormatterFactory() );
	}

	private void initMoreComponents() {
		CellConstraints cc = new CellConstraints();

		shuntMetricPanel = new TwoValuePanel();
		shuntMetricPanel.setFormat(df1);
		shuntMetricPanel.setUpperTitle("<html>Q<sub>s</sub>/Q<sub>t</sub>");
		shuntMetricPanel.setLowerTitle("<html>Q<sub>s</sub>/Q<sub>t</sub>  EST");
		trendsPanel.add(shuntMetricPanel, cc.xy(1, 1));

		shuntTrendPanel = new SignalPanel();
		shuntTrendPanel.setName("ibi");
		shuntTrendPanel.setScaleMinRange(100.0);
		shuntTrendPanel.setScaleMinY(0.0);
		shuntTrendPanel.setYAxisLabel("ibi");
		shuntTrendPanel.setYLabelRotation(true);
		shuntTrendPanel.getChart().setAxisMode(SignalChart.XAxisMode.POINT);
		trendsPanel.add(shuntTrendPanel, cc.xy(3, 1));

	}

	private void computeActionPerformed(ActionEvent e) {
		// TODO add your code here
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		panel1 = new JPanel();
		trendsPanel = new JPanel();
		separator1 = new JSeparator();
		panel3 = new JPanel();
		separator5 = compFactory.createSeparator("Hemodynamics");
		panel7 = new JPanel();
		label26 = new JLabel();
		hr = new JFormattedTextField();
		label24 = new JLabel();
		co = new JFormattedTextField();
		label27 = new JLabel();
		map = new JFormattedTextField();
		label25 = new JLabel();
		formattedTextField9 = new JFormattedTextField();
		label23 = new JLabel();
		cvp = new JFormattedTextField();
		separator6 = compFactory.createSeparator("Blood Gasses");
		panel8 = new JPanel();
		label7 = new JLabel();
		hb = new JFormattedTextField();
		label1 = new JLabel();
		label5 = new JLabel();
		pao2 = new JFormattedTextField();
		label2 = new JLabel();
		separator3 = new JSeparator();
		valuesPanel = new JPanel();
		signalChart2 = new SignalChart();
		signalChart3 = new SignalChart();
		signalChart4 = new SignalChart();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout(
			"[150dlu,default]:grow",
			"fill:default:grow"));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"default:grow, $lcgap, center:8dlu, [160dlu,default]",
				"fill:default:grow, $rgap, default"));

			//======== trendsPanel ========
			{
				trendsPanel.setLayout(new FormLayout(
					"[50dlu,default], $lcgap, default:grow",
					"fill:[50dlu,default], 2*($lgap, default)"));
			}
			panel1.add(trendsPanel, CC.xy(1, 1));

			//---- separator1 ----
			separator1.setOrientation(SwingConstants.VERTICAL);
			panel1.add(separator1, CC.xywh(3, 1, 1, 3));

			//======== panel3 ========
			{
				panel3.setLayout(new FormLayout(
					"default:grow",
					"7*(default, $lgap), top:default:grow, 2*($lgap, default)"));
				panel3.add(separator5, CC.xy(1, 1));

				//======== panel7 ========
				{
					panel7.setLayout(new FormLayout(
						"right:default:grow, $lcgap, [30dlu,default], $lcgap, right:[30dlu,default], $lcgap, [30dlu,default]",
						"2*(default, $lgap), default"));

					//---- label26 ----
					label26.setText("HR:");
					panel7.add(label26, CC.xy(1, 1));
					panel7.add(hr, CC.xy(3, 1));

					//---- label24 ----
					label24.setText("CO:");
					panel7.add(label24, CC.xy(5, 1));
					panel7.add(co, CC.xy(7, 1));

					//---- label27 ----
					label27.setText("MAP:");
					panel7.add(label27, CC.xy(1, 3));
					panel7.add(map, CC.xy(3, 3));

					//---- label25 ----
					label25.setText("PAWP:");
					label25.setToolTipText("Pulmonary Arterial Occlusion Pressure / Pulmonary Wedge Pressure");
					panel7.add(label25, CC.xy(5, 3));
					panel7.add(formattedTextField9, CC.xy(7, 3));

					//---- label23 ----
					label23.setText("CVP:");
					panel7.add(label23, CC.xy(1, 5));
					panel7.add(cvp, CC.xy(3, 5));
				}
				panel3.add(panel7, CC.xy(1, 3));
				panel3.add(separator6, CC.xy(1, 5));

				//======== panel8 ========
				{
					panel8.setLayout(new FormLayout(
						"right:[40dlu,default], $lcgap, [30dlu,default], $lcgap, right:[30dlu,default]:grow",
						"default, $lgap, default"));

					//---- label7 ----
					label7.setText("GP1:");
					panel8.add(label7, CC.xy(1, 1));
					panel8.add(hb, CC.xy(3, 1));

					//---- label1 ----
					label1.setText("Above Balloon");
					panel8.add(label1, CC.xy(5, 1));

					//---- label5 ----
					label5.setText("GP2:");
					panel8.add(label5, CC.xy(1, 3));
					panel8.add(pao2, CC.xy(3, 3));

					//---- label2 ----
					label2.setText("Below Balloon");
					panel8.add(label2, CC.xy(5, 3));
				}
				panel3.add(panel8, CC.xy(1, 7));
				panel3.add(separator3, CC.xy(1, 13));
			}
			panel1.add(panel3, CC.xywh(4, 1, 1, 3));

			//======== valuesPanel ========
			{
				valuesPanel.setLayout(new FormLayout(
					"3*([50dlu,default], $lcgap), [50dlu,default]",
					"fill:[50dlu,default]"));
				valuesPanel.add(signalChart2, CC.xy(1, 1));
				valuesPanel.add(signalChart3, CC.xy(3, 1));
				valuesPanel.add(signalChart4, CC.xy(7, 1));
			}
			panel1.add(valuesPanel, CC.xy(1, 3));
		}
		add(panel1, CC.xy(1, 1));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	private JPanel panel1;
	private JPanel trendsPanel;
	private JSeparator separator1;
	private JPanel panel3;
	private JComponent separator5;
	private JPanel panel7;
	private JLabel label26;
	private JFormattedTextField hr;
	private JLabel label24;
	private JFormattedTextField co;
	private JLabel label27;
	private JFormattedTextField map;
	private JLabel label25;
	private JFormattedTextField formattedTextField9;
	private JLabel label23;
	private JFormattedTextField cvp;
	private JComponent separator6;
	private JPanel panel8;
	private JLabel label7;
	private JFormattedTextField hb;
	private JLabel label1;
	private JLabel label5;
	private JFormattedTextField pao2;
	private JLabel label2;
	private JSeparator separator3;
	private JPanel valuesPanel;
	private SignalChart signalChart2;
	private SignalChart signalChart3;
	private SignalChart signalChart4;
	// JFormDesigner - End of variables declaration  //GEN-END:variables

}
