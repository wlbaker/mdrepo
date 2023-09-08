package org.sittingbull.gt.util;

import java.text.DecimalFormat;

public class Label {
	public double min, max, step, score;

	public String toString() {
		DecimalFormat df = new DecimalFormat("00.00");
		String s = "(Score: " + df.format(score) + ") ";
		for (double x = min; x <= max; x = x + step) {
			s += df.format(x) + "\t";
		}
		return s;
	}
}

