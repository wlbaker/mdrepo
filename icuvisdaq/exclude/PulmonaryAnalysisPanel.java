/*
 * Created by JFormDesigner on Tue Oct 18 12:58:28 CDT 2011
 */

package idea.analysis;


import idea.display.simple.TwoValuePanel;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.PersistentItem;

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
public class PulmonaryAnalysisPanel extends JPanel {
	private final static NumberFormat df1 = new DecimalFormat("0.#");
	private final static NumberFormat df3 = new DecimalFormat("0.000");
	
	private SBCO2 segmenter;
	private TwoValuePanel shuntMetricPanel;
	private SignalPanel shuntTrendPanel;
	
	public PulmonaryAnalysisPanel() {
		initComponents();
		
		initMoreComponents();
		
		segmenter = new SBCO2();
		segmenter.addStreamListener(StreamID.MEASUREMENT, new StreamConsumer() {

			@Override
			public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {
				SBCO2Block block = (SBCO2Block)item;
				showSegmentedBreath(block);
			}

		});

		map.setFormatterFactory(GuiUtil.getNumberFormatterFactory() );
	}

	protected void showSegmentedBreath(SBCO2Block block) {
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

	private void CaO2MouseClicked(MouseEvent e) {
		// TODO add your code here
	}
	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
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
		paco2 = new JFormattedTextField();
		label5 = new JLabel();
		pao2 = new JFormattedTextField();
		label4 = new JLabel();
		sao2 = new JFormattedTextField();
		label6 = new JLabel();
		pvo2 = new JFormattedTextField();
		label17 = new JLabel();
		pvo3 = new JFormattedTextField();
		separator2 = compFactory.createSeparator("Respirator");
		panel2 = new JPanel();
		label99 = new JLabel();
		peco2 = new JFormattedTextField();
		label8 = new JLabel();
		fio2 = new JFormattedTextField();
		label98 = new JLabel();
		petco2 = new JFormattedTextField();
		label15 = new JLabel();
		rq = new JFormattedTextField();
		label29 = new JLabel();
		petco3 = new JFormattedTextField();
		label22 = new JLabel();
		peep = new JFormattedTextField();
		label30 = new JLabel();
		formattedTextField12 = new JFormattedTextField();
		label32 = new JLabel();
		formattedTextField10 = new JFormattedTextField();
		label31 = new JLabel();
		formattedTextField13 = new JFormattedTextField();
		label33 = new JLabel();
		formattedTextField11 = new JFormattedTextField();
		separator3 = new JSeparator();
		panel5 = new JPanel();
		label18 = new JLabel();
		label19 = new JLabel();
		label20 = new JLabel();
		label21 = new JLabel();
		separator4 = compFactory.createSeparator("Results");
		panel6 = new JPanel();
		label9 = new JLabel();
		label11 = new JLabel();
		CaO2 = new JLabel();
		label28 = new JLabel();
		label10 = new JLabel();
		label12 = new JLabel();
		label16 = new JLabel();
		label14 = new JLabel();
		label13 = new JLabel();
		valuesPanel = new JPanel();
		signalChart2 = new SignalChart();
		signalChart3 = new SignalChart();
		signalChart4 = new SignalChart();
		CellConstraints cc = new CellConstraints();

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
			panel1.add(trendsPanel, cc.xy(1, 1));

			//---- separator1 ----
			separator1.setOrientation(SwingConstants.VERTICAL);
			panel1.add(separator1, cc.xywh(3, 1, 1, 3));

			//======== panel3 ========
			{
				panel3.setLayout(new FormLayout(
					"default:grow",
					"7*(default, $lgap), top:default:grow, 2*($lgap, default)"));
				panel3.add(separator5, cc.xy(1, 1));

				//======== panel7 ========
				{
					panel7.setLayout(new FormLayout(
						"right:default:grow, $lcgap, [30dlu,default], $lcgap, right:[30dlu,default], $lcgap, [30dlu,default]",
						"2*(default, $lgap), default"));

					//---- label26 ----
					label26.setText("HR:");
					panel7.add(label26, cc.xy(1, 1));
					panel7.add(hr, cc.xy(3, 1));

					//---- label24 ----
					label24.setText("CO:");
					panel7.add(label24, cc.xy(5, 1));
					panel7.add(co, cc.xy(7, 1));

					//---- label27 ----
					label27.setText("MAP:");
					panel7.add(label27, cc.xy(1, 3));
					panel7.add(map, cc.xy(3, 3));

					//---- label25 ----
					label25.setText("PAWP:");
					label25.setToolTipText("Pulmonary Arterial Occlusion Pressure / Pulmonary Wedge Pressure");
					panel7.add(label25, cc.xy(5, 3));
					panel7.add(formattedTextField9, cc.xy(7, 3));

					//---- label23 ----
					label23.setText("CVP:");
					panel7.add(label23, cc.xy(1, 5));
					panel7.add(cvp, cc.xy(3, 5));
				}
				panel3.add(panel7, cc.xy(1, 3));
				panel3.add(separator6, cc.xy(1, 5));

				//======== panel8 ========
				{
					panel8.setLayout(new FormLayout(
						"right:default:grow, $lcgap, [30dlu,default], $lcgap, right:[30dlu,default], $lcgap, [30dlu,default]",
						"4*(default, $lgap), default"));

					//---- label7 ----
					label7.setText("Hb:");
					panel8.add(label7, cc.xy(1, 1));
					panel8.add(hb, cc.xy(3, 1));

					//---- label1 ----
					label1.setText("<html>P<sub>a</sub>CO<sub>2</sub>:");
					panel8.add(label1, cc.xy(5, 1));
					panel8.add(paco2, cc.xy(7, 1));

					//---- label5 ----
					label5.setText("<html>P<sub>a</sub>O<sub>2</sub>:");
					panel8.add(label5, cc.xy(1, 3));
					panel8.add(pao2, cc.xy(3, 3));

					//---- label4 ----
					label4.setText("<html>S<sub>a</sub>O<sub>2</sub>:");
					panel8.add(label4, cc.xy(1, 5));
					panel8.add(sao2, cc.xy(3, 5));

					//---- label6 ----
					label6.setText("<html>P<sub>v</sub>O<sub>2</sub>:");
					panel8.add(label6, cc.xy(1, 7));
					panel8.add(pvo2, cc.xy(3, 7));

					//---- label17 ----
					label17.setText("<html>S<sub>v</sub>O<sub>2</sub>:");
					panel8.add(label17, cc.xy(1, 9));
					panel8.add(pvo3, cc.xy(3, 9));
				}
				panel3.add(panel8, cc.xy(1, 7));
				panel3.add(separator2, cc.xy(1, 9));

				//======== panel2 ========
				{
					panel2.setLayout(new FormLayout(
						"right:[40dlu,default]:grow, $lcgap, [30dlu,default], $lcgap, right:[30dlu,default], $lcgap, [30dlu,default]",
						"4*(default, $lgap), default"));

					//---- label99 ----
					label99.setText("<html>P<sub>e</sub>CO<sub>2</sub>:");
					panel2.add(label99, cc.xy(1, 1));
					panel2.add(peco2, cc.xy(3, 1));

					//---- label8 ----
					label8.setText("<html>FiO<sub>2</sub>:");
					panel2.add(label8, cc.xy(5, 1));
					panel2.add(fio2, cc.xy(7, 1));

					//---- label98 ----
					label98.setText("<html>P<sub>ET</sub>CO<sub>2</sub>:");
					panel2.add(label98, cc.xy(1, 3));
					panel2.add(petco2, cc.xy(3, 3));

					//---- label15 ----
					label15.setText("RQ:");
					panel2.add(label15, cc.xy(5, 3));

					//---- rq ----
					rq.setText("0.8");
					rq.setEditable(false);
					panel2.add(rq, cc.xy(7, 3));

					//---- label29 ----
					label29.setText("PLAT:");
					panel2.add(label29, cc.xy(1, 5));
					panel2.add(petco3, cc.xy(3, 5));

					//---- label22 ----
					label22.setText("PEEP:");
					panel2.add(label22, cc.xy(5, 5));
					panel2.add(peep, cc.xy(7, 5));

					//---- label30 ----
					label30.setText("<html>PES<sub>ee</sub>");
					panel2.add(label30, cc.xy(1, 7));
					panel2.add(formattedTextField12, cc.xy(3, 7));

					//---- label32 ----
					label32.setText("TV:");
					panel2.add(label32, cc.xy(5, 7));
					panel2.add(formattedTextField10, cc.xy(7, 7));

					//---- label31 ----
					label31.setText("<html>PES<sub>plat</sub>");
					panel2.add(label31, cc.xy(1, 9));
					panel2.add(formattedTextField13, cc.xy(3, 9));

					//---- label33 ----
					label33.setText("<html>MAP<sub>aw</sub>:");
					panel2.add(label33, cc.xy(5, 9));
					panel2.add(formattedTextField11, cc.xy(7, 9));
				}
				panel3.add(panel2, cc.xy(1, 11));
				panel3.add(separator3, cc.xy(1, 13));

				//======== panel5 ========
				{
					panel5.setLayout(new FormLayout(
						"right:default:grow, $lcgap, [30dlu,default], $lcgap, right:[30dlu,default], $lcgap, [30dlu,default]",
						"2*(default, $lgap), default"));

					//---- label18 ----
					label18.setText("<html>&Delta<nbr>V:");
					panel5.add(label18, cc.xy(1, 1));

					//---- label19 ----
					label19.setText("<html>&Delta<nbr>Paw:");
					panel5.add(label19, cc.xy(5, 1));

					//---- label20 ----
					label20.setText("<html>&Delta<nbr>Pes:");
					panel5.add(label20, cc.xy(5, 3));

					//---- label21 ----
					label21.setText("<html>&Delta<nbr>Pl:");
					panel5.add(label21, cc.xy(5, 5));
				}
				panel3.add(panel5, cc.xy(1, 15));
				panel3.add(separator4, cc.xy(1, 17));

				//======== panel6 ========
				{
					panel6.setLayout(new FormLayout(
						"right:[20dlu,default], $lcgap, [20dlu,default], $lcgap, right:default, $lcgap, [20dlu,default], $lcgap, right:20dlu, $lcgap, [20dlu,default]",
						"3*(default, $lgap), default"));

					//---- label9 ----
					label9.setText("<html>V<sub>d</sub>:");
					panel6.add(label9, cc.xy(1, 1));

					//---- label11 ----
					label11.setText("<html>C<sub>a</sub>O<sub>2</sub>:");
					panel6.add(label11, cc.xy(5, 1));

					//---- CaO2 ----
					CaO2.setText("text");
					CaO2.setForeground(Color.blue);
					CaO2.setHorizontalAlignment(SwingConstants.TRAILING);
					CaO2.setToolTipText("<html>C<sub>a</sub>O<sub>2</sub>: One t many");
					CaO2.addMouseListener(new MouseAdapter() {
						@Override
						public void mouseClicked(MouseEvent e) {
							CaO2MouseClicked(e);
						}
					});
					panel6.add(CaO2, cc.xy(7, 1));

					//---- label28 ----
					label28.setText("SV:");
					panel6.add(label28, cc.xy(9, 1));

					//---- label10 ----
					label10.setText("<html>V<sub>T</sub>:");
					panel6.add(label10, cc.xy(1, 3));

					//---- label12 ----
					label12.setText("<html>C<sub>v</sub>O<sub>2</sub>:");
					panel6.add(label12, cc.xy(5, 3));

					//---- label16 ----
					label16.setText("OI:");
					panel6.add(label16, cc.xy(9, 3));

					//---- label14 ----
					label14.setText("<html>P<sub>A</sub>O<sub>2</sub>:");
					panel6.add(label14, cc.xy(1, 5));

					//---- label13 ----
					label13.setText("<html>C<sub>c</sub>O<sub>2</sub>:");
					panel6.add(label13, cc.xy(5, 5));
				}
				panel3.add(panel6, cc.xy(1, 19));
			}
			panel1.add(panel3, cc.xywh(4, 1, 1, 3));

			//======== valuesPanel ========
			{
				valuesPanel.setLayout(new FormLayout(
					"3*([50dlu,default], $lcgap), [50dlu,default]",
					"fill:[50dlu,default]"));
				valuesPanel.add(signalChart2, cc.xy(1, 1));
				valuesPanel.add(signalChart3, cc.xy(3, 1));
				valuesPanel.add(signalChart4, cc.xy(7, 1));
			}
			panel1.add(valuesPanel, cc.xy(1, 3));
		}
		add(panel1, cc.xy(1, 1));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
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
	private JFormattedTextField paco2;
	private JLabel label5;
	private JFormattedTextField pao2;
	private JLabel label4;
	private JFormattedTextField sao2;
	private JLabel label6;
	private JFormattedTextField pvo2;
	private JLabel label17;
	private JFormattedTextField pvo3;
	private JComponent separator2;
	private JPanel panel2;
	private JLabel label99;
	private JFormattedTextField peco2;
	private JLabel label8;
	private JFormattedTextField fio2;
	private JLabel label98;
	private JFormattedTextField petco2;
	private JLabel label15;
	private JFormattedTextField rq;
	private JLabel label29;
	private JFormattedTextField petco3;
	private JLabel label22;
	private JFormattedTextField peep;
	private JLabel label30;
	private JFormattedTextField formattedTextField12;
	private JLabel label32;
	private JFormattedTextField formattedTextField10;
	private JLabel label31;
	private JFormattedTextField formattedTextField13;
	private JLabel label33;
	private JFormattedTextField formattedTextField11;
	private JSeparator separator3;
	private JPanel panel5;
	private JLabel label18;
	private JLabel label19;
	private JLabel label20;
	private JLabel label21;
	private JComponent separator4;
	private JPanel panel6;
	private JLabel label9;
	private JLabel label11;
	private JLabel CaO2;
	private JLabel label28;
	private JLabel label10;
	private JLabel label12;
	private JLabel label16;
	private JLabel label14;
	private JLabel label13;
	private JPanel valuesPanel;
	private SignalChart signalChart2;
	private SignalChart signalChart3;
	private SignalChart signalChart4;
	// JFormDesigner - End of variables declaration  //GEN-END:variables

}
