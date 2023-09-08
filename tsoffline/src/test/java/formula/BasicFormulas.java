package formula;

import java.awt.Color;

import org.piccolo2d.extras.util.LineShape;
import org.piccolo2d.extras.util.XYArray;

import idea.schema.rp.RpMetric;
import idea.tsoffline.HPPathLayer;
import idea.tsoffline.HPSplitableLayer;
import idea.tsoffline.canvas.HPPath;
import idea.tsoffline.model.DerivedUtil;

public class BasicFormulas {

	public static void main(String[] args) {

		HPSplitableLayer a_src;
		HPSplitableLayer dest;
		
		
		HPPathLayer src_path;
		HPPathLayer dest_path ;

		{
			src_path = new HPPathLayer(null, null, "sourceLayer");
			RpMetric m = new RpMetric();
			m.setSampleRate(500);

			a_src = new HPSplitableLayer(m);
			a_src.addChild(src_path);
			a_src.setPaint(Color.BLUE);
		}

		{
			dest_path = new HPPathLayer(null, null, "destLayer");
			RpMetric m = new RpMetric();
			m.setSampleRate(500);

			dest = new HPSplitableLayer(m);
			dest.addChild(dest_path);
			dest.setPaint(Color.BLUE);
		}

		int pkt_len = 20;
		double dpkt_len = pkt_len;

		double[] xy0 = new double[(pkt_len + 1) * 2];
		int pos = 0;
		for (int i = 0; i < pkt_len; i++) {
			xy0[pos++] = i / dpkt_len;
			xy0[pos++] = 1;
		}

		double[] xy1 = new double[(pkt_len + 1) * 2];
		pos = 0;
		for (int i = 0; i < pkt_len; i++) {
			xy1[pos++] = 1 + i / dpkt_len;
			xy1[pos++] = i;
		}

		double[] xy2 = new double[(pkt_len + 1) * 2];
		pos = 0;
		for (int i = 0; i < pkt_len; i++) {
			xy2[pos++] = 2 + i / dpkt_len;
			xy2[pos++] = i % 5;
		}

		double[] xy3 = new double[(pkt_len + 1) * 2];
		pos = 0;
		for (int i = 0; i < pkt_len; i++) {
			xy3[pos++] = 3 + i / dpkt_len;
			xy3[pos++] = 100 * Math.sin(3.1515 * i / dpkt_len);
		}

		// fix the dangling end of xy3
		xy3[pos] = xy3[pos - 2];
		pos++;
		xy3[pos] = xy3[pos - 2];

		// tie together the dangling ends of the other packets
		for (int i = 0; i <= 1; i++) {
			xy0[2 * pkt_len + i] = xy1[i];
			xy1[2 * pkt_len + i] = xy2[i];
			xy2[2 * pkt_len + i] = xy3[i];
		}

		HPPath child0 = new HPPath(new LineShape(new XYArray(xy0)), null, a_src.getMetric());
		HPPath child1 = new HPPath(new LineShape(new XYArray(xy1)), null, a_src.getMetric());
		HPPath child2 = new HPPath(new LineShape(new XYArray(xy2)), null, a_src.getMetric());
		HPPath child3 = new HPPath(new LineShape(new XYArray(xy3)), null, a_src.getMetric());

		System.out.println("***** Two Children");
		src_path.addChild(child0);
		src_path.addChild(child1);
		a_src.dump();

		System.out.println("Two Children + DERIVATIVE " );
		DerivedUtil.derivative(dest, a_src);
		dest.dump();

		src_path.removeAllChildren();

		// System.out.println("***** One Child -- zero tm");
		// layer.addChild(child0);
		// layer.dump();
		// System.out.println("One Child -- zero tm + FILTER" + npoint_filter);
		// layer.applyFilter(npoint_filter);
		// layer.dump();

	}

}
