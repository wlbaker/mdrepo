package idea.adapters.gui;

import javax.swing.JButton;
import javax.swing.JLabel;

public class PumpInfo {
	String pumpId;
	// XYSeries series;
	// XYSeriesCollection dataset;

	JLabel rate;
	JLabel vtbi;
	JLabel totvol;

	JLabel devStatus;
	JLabel controlStatus;
	JLabel infusionStatus;
	JLabel actionStatus;

	JButton settings;
	// public ChartPanel lblChart;
	// public JFreeChart chart;

	CombinedRateVolumeChart chart;
}
