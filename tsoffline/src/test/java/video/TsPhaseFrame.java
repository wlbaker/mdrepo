package video;

import java.awt.Dimension;

import javax.swing.JFrame;

import idea.intf.DataTyp;
import idea.schema.rp.RpMetric;
import idea.tsoffline.video.TsPhaseControlPanel;

public class TsPhaseFrame {

	private static double[][] xx;
	private static double[][] yy;


	static void createAnimationData() {
		int pkt_len=100;
		
		xx = new double[100][pkt_len];
		yy = new double[100][pkt_len];

		double t = 0.0;
		double dx = 0.0;

		for (int row = 0; row < 100; row++) {
			for (int col = 0; col < pkt_len; col++) {
				xx[row][col] = 200 * Math.sin(t) + dx + 50;
				yy[row][col] = 2000 * Math.sin(2 * t) + 1000;
				t += 0.01;
			}
			dx += 0.5;
		}
	}


	public static void main(String[] args) {

		TsPhaseControlPanel pcp = new TsPhaseControlPanel();
		
		createAnimationData();
		
		RpMetric sigInfo = new RpMetric("LOC", "CODE", "NAME", null, DataTyp.DOUBLE_ARR_TYP);
		sigInfo.setSampleRate(200);
		
		pcp.setDisplaySignal(sigInfo);
		pcp.setDataPackets( 0L, null, xx, yy);
		
		JFrame f = new JFrame("Piccolo Phase");
		f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		f.add(pcp);
		f.setMinimumSize(new Dimension(800, 500));
		f.pack();
		f.setVisible(true);

	}


}
