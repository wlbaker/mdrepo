package idea;

import java.util.Arrays;

import lombok.extern.slf4j.Slf4j;
import idea.buffer.CircularIntBuffer;
import idea.buffer.SignalBuffer;

@Slf4j
public class Stats {

	// http://en.wikipedia.org/wiki/Median_absolute_deviation
	static public double mad(int[] rri) {
		int mm = median(rri);
		int[] rri2d = new int[ rri.length ];
		for( int i = 0; i < rri2d.length; i++ ) {
			rri2d[i] = Math.abs(rri[i] - mm);
		}
		
		// FIXME: MAD not ready...tested
		// MAD = median( |Xi - medianj(Xj)| )
		log.error("FIXME: mean average deviation not tested");
		return median(rri2d);
	}
	
	static public double sd(int[] rri) {
		double sum = 0.0, sum2 = 0.0, sd;
		int j;

		int tot = rri.length;
		for (j = 0; j < tot; j++) {
			double u_val = rri[j];
			sum += u_val;
			sum2 += u_val * u_val;
		}
		sd = Math.sqrt((sum2 - sum * sum / tot) / (tot - 1));
		return sd;
	}

	static public double sd(double[] rri) {
		double sum = 0.0, sum2 = 0.0, sd;
		int j;

		int tot = rri.length;
		for (j = 0; j < tot; j++) {
			double u_val = rri[j];
			sum += u_val;
			sum2 += u_val * u_val;
		}
		sd = Math.sqrt((sum2 - sum * sum / tot) / (tot - 1));
		return sd;
	}

	static public double getStandardDeviation(CircularIntBuffer signal) {

		double mean = 0.0;
		Number standardDev = null;
		double variance = 0;

		int tot = signal.getSampleCount();
		for (int i = 0; i < tot; ++i) {
			mean += signal.get(i); // rwaves[i];
		}
		mean /= tot;

		for (int i = 0; i < tot; ++i) {
			variance += Math.pow(signal.get(i) - mean, 2.0);
		}
		variance /= (tot - 1);

		standardDev = Math.sqrt(variance);

		return standardDev.doubleValue();

	}

	static public double getStandardDeviation(SignalBuffer<? extends Number> signal) {

		double mean = 0.0;
		Number standardDev = null;
		double variance = 0;

		int tot = signal.getSampleCount();
		for (int i = 0; i < tot; ++i) {
			mean += signal.get(i).doubleValue(); // rwaves[i];
		}
		mean /= tot;

		for (int i = 0; i < tot; ++i) {
			variance += Math.pow(signal.get(i).doubleValue() - mean, 2.0);
		}
		variance /= (tot - 1);

		standardDev = Math.sqrt(variance);

		return standardDev.doubleValue();

	}

	public static int median(int[] sig) {
		if( sig.length == 0 ) {
			return 0;
		}
		int[] copy = Arrays.copyOf(sig, sig.length);
		Arrays.sort(copy);
		int idx = copy.length / 2;
		return sig[idx];
	}

	public static double median(double[] sig) {
		if( sig.length == 0 ) {
			return Double.NaN;
		}
		double[] copy = Arrays.copyOf(sig, sig.length);
		Arrays.sort(copy);
		int idx = copy.length / 2;
		return sig[idx];
	}

	public static double medianAbsoluteDeviation(int[] sig) {
		double m = median(sig);
		double[] sig_diff = new double[sig.length];
		for (int i = 0; i < sig.length; i++) {
			sig_diff[i] = Math.abs(sig[i] - m);
		}
		Arrays.sort(sig_diff);
		return 1.4826 * sig_diff[sig.length / 2];
	}

	public static double mean(double[] sig) {
		double tot = 0.0;

		int len = sig.length;
		for (int i = 0; i < len; i++) {
			tot += sig[i];
		}

		return tot / len;
	}

	public static float mean(float[] sig) {
		float tot = 0.0f;

		int len = sig.length;
		for (int i = 0; i < len; i++) {
			tot += sig[i];
		}

		return tot / len;
	}

	public static double rmssd(double[] sig) {
		double tot = 0;
		for (int i = 0; i < sig.length - 1; i++) {
			double diff = sig[i] - sig[i + 1];
			tot += (diff * diff);
		}
		double rmssd = Math.sqrt(tot / (sig.length - 1));

		return rmssd;
	}

	public static double rmssd(int[] sig) {
		double tot = 0;
		for (int i = 0; i < sig.length - 1; i++) {
			double diff = sig[i] - sig[i + 1];
			tot += (diff * diff);
		}
		double rmssd = Math.sqrt(tot / (sig.length - 1));

		return rmssd;
	}
	
	public static double sum(double[] x) {
		double tot = 0.0;
		for (double v : x) {
			tot += v;
		}
		return tot;
	}

	public static double max(double[] x) {
		double max = x[0];
		for (double v : x) {
			if (v > max) {
				max = v;
			}
		}
		return max;
	}

	public static float max(float[] x) {
		float max = x[0];
		for (float v : x) {
			if (v > max) {
				max = v;
			}
		}
		return max;
	}

	public static Number max(SignalBuffer<? extends Number> x) {
		Number max = x.get(0);
		for (int idx = 1; idx < x.getSampleCount() ; idx++) {
			Number v = x.get(idx);
			if (v.doubleValue() > max.doubleValue()) {
				max = v;
			}
		}
		return max;
	}

	public static double min(double[] pp) {
		double min = pp[0];
		for (int i = 1; i < pp.length ; i++) {
			if (pp[i] < min) {
				min = pp[i];
			}
		}
		return min;
	}

	public static float min(float[] pp) {
		float min = pp[0];
		for (int i = 1; i < pp.length ; i++) {
			if (pp[i] < min) {
				min = pp[i];
			}
		}
		return min;
	}

	public static double var(double[] vals) {
		double variance = 0;
		double mean = mean( vals );

		int tot = vals.length;
		
		for (int i = 0; i < tot; i++) {
			variance += Math.pow(vals[i] - mean, 2.0);
		}
		variance /= (tot - 1);
		
		return variance;
	}
}
