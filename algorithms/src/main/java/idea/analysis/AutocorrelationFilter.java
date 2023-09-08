package idea.analysis;

import icuInterface.events.NumericsEvent;
import idea.conf.DeviceCapabilities;
import idea.conf.DeviceConfiguration;
import idea.intf.AbstractStreamProducer;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.Alarm;
import idea.model.PersistentItem;

import java.util.Vector;

import idea.analysis.event.AutocorrelationBlock;
import idea.analysis.event.BeatBlock;
import idea.analysis.event.BeatEvent;
import idea.analysis.event.RWaveEvent;
import idea.buffer.SignalBuffer;

/**
 * This class provides the methods needed to calculate the auto-
 * correlation of R-R distributions (dba similarity of distributions) 
 * using the R-R intervals.
 * 
 * @param SDRR			Standard deviation of RRIs  
 * @param SDSD			Standard deviation of successive RRI differences
 * @param SOD			Autocorrelation/Similarity of distributions
 * @param histogram		Unnormalized histogram of RRIs
 * 
 */

public class AutocorrelationFilter extends AbstractStreamProducer implements
StreamConsumer {

	private final static int TAU = 4; // window shift or time delay

	private static int verbose = 0;

	private int totSamples;

	private SignalBuffer<Integer> rris;
	private SignalBuffer<Integer> rriDiffs;
	private static Histogram prevHistogram, histogram;

	private static int minRRInterval;
	private static int maxRRInterval;
	private int prevMSInterval;

	private int mstime;

	private double SDRR;
	private double SDSD;

	private double SOD;

	public AutocorrelationFilter(int count) {
		totSamples = 0;
		rris = new SignalBuffer<Integer>(count, true);
		rriDiffs = new SignalBuffer<Integer>(count-1, true);

		minRRInterval = 0;
		maxRRInterval = 0;

		prevMSInterval = 0;
		mstime = 0;
	}

	private double getSampleStandardDeviation(SignalBuffer<? extends Number> signal) {

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

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {
		Object event = item;
		
		if (event instanceof RWaveEvent ) {
			NumericsEvent e = (NumericsEvent) event;

			BeatBlock block = (BeatBlock) e.getBlock();

			int interval = block.getMs_interval();
			mstime += interval;

			// Add successive RRI difference
			if (totSamples > 0) {
				rriDiffs.addData(interval - prevMSInterval);
			}

			prevMSInterval = interval;

			rris.addData(interval);

			totSamples++;

			if (rris.getSampleCount() < rris.getBufferSize()) {
				if (verbose > 0) {
					System.out.println("   StatAv progress: "
							+ rris.getSampleCount() + " out of "
							+ rris.getBufferSize());
				}
				Alarm ai = new Alarm("autocorr", Alarm.INFO, 0, "Waiting: "
						+ rris.getSampleCount() + " out of "
						+ rris.getBufferSize(), true);
				fireAlarmEvent(this, ai);
				return;
			}

			SDRR = getSampleStandardDeviation(rris);
			SDSD = getSampleStandardDeviation(rriDiffs);

			// Form histogram of previous window
			minRRInterval = rris.get(0);
			maxRRInterval = rris.get(0);

			for (int i = 0; i < rris.getSampleCount() - TAU; i++) {
				minRRInterval = Math.min(minRRInterval, rris.get(i).intValue());
				maxRRInterval = Math.max(maxRRInterval, rris.get(i).intValue());
			}

			// System.out.println("Min R-R: " + minRRInterval);
			// System.out.println("Max R-R: " + maxRRInterval);

			prevHistogram = new Histogram(maxRRInterval, 0, maxRRInterval + 1);
			// Histogram(maxRRInterval, minRRInterval, maxRRInterval);

			for (int i = 0; i < rris.getSampleCount() - TAU; i++) {
				prevHistogram.add(rris.get(i).doubleValue());
			}

			// Form histogram of next window
			minRRInterval = rris.get(TAU);
			maxRRInterval = rris.get(TAU);

			for (int i = TAU; i < rris.getSampleCount(); i++) {
				minRRInterval = Math.min(minRRInterval, rris.get(i).intValue());
				maxRRInterval = Math.max(maxRRInterval, rris.get(i).intValue());
			}

			// System.out.println("Min R-R: " + minRRInterval);
			// System.out.println("Max R-R: " + maxRRInterval);

			histogram = new Histogram(maxRRInterval, 0, maxRRInterval + 1);
			// Histogram(maxRRInterval, minRRInterval, maxRRInterval);

			for (int i = TAU; i < rris.getSampleCount(); i++) {
				histogram.add(rris.get(i).doubleValue());
			}

			// System.out.println("Sample Count: " + rris.getSampleCount());
			// System.out.println("NumBins: " + fNumBins);
			// System.out.println("Total: " + getTotal());

			// Calculate autocorrelation of R-R distributions
			SOD = 0;
			for (int i = 0; i < Math.min(prevHistogram.getFNumBins(), histogram.getFNumBins()); i++) {
				SOD += 1.0 * 
				prevHistogram.getBinValue(i)/prevHistogram.getTotal() * 
				histogram.getBinValue(i)/histogram.getTotal();
			}

			AutocorrelationBlock autocorrBlock = new AutocorrelationBlock();

			autocorrBlock.setSDRR(SDRR);
			autocorrBlock.setSDSD(SDSD);
			autocorrBlock.setSOD(SOD);

			fireStreamEvent(0, this, StreamID.MEASUREMENT, autocorrBlock);

			// Prepare new waveform
			int[] bins = new int[histogram.getFNumBins()];

			for (int i = 0; i < histogram.getFNumBins(); i++) bins[i] = histogram.getBinValue(i);

			
			PersistentItem wb = null;
			// FIXME: not upgraded from WaveformBlock
//			WaveformItem wi = new WaveformItem(
//					new WaveformDescription("0", "histogram", "histogram", 1, histogram.getFNumBins(), RpLinearUnit.unit), 
//					bins, 1);
//
//			WaveformBlock wb = new WaveformBlock(new Date().getTime());
//			wb.add(wi);
//			wb.setSource( this );

			fireStreamEvent(0, this, StreamID.WAVEFORM, wb);

		} else if (event instanceof BeatEvent ) {
			// ignoring beat event
		} else if (sid == StreamID.MEASUREMENT) {
		} else if (sid == StreamID.WAVEFORM) {
			// ignore
		}

	}
}


class Histogram {

	private Vector<Integer> binIndices;
	private Vector<Integer> fBins;

	private int fNumBins;
	private int fUnderflows;
	private int fOverflows;

	private double fLo;
	private double fHi;
	private double fRange;

	/** The constructor will create an array of a given
	 * number of bins. The range of the histogram given
	 * by the upper and lower limit values.
	 **/
	public Histogram (int numBins, double lo, double hi) {
		// Check for bad range values.
		// Could throw an exception but will just
		// use default values;
		if (hi < lo) {
			lo = 0.0;
			hi = 1.0;
		}
		if (numBins <= 0) numBins = 1;
		fNumBins = numBins;
		binIndices = new Vector<Integer>(fNumBins);
		fBins = new Vector<Integer>(fNumBins);

		for (int i = 0; i < fNumBins; i++) {
			binIndices.add(Integer.valueOf(i));
			fBins.add(Integer.valueOf(0)); 
		}

		fLo = lo;
		fHi = hi;
		fRange = fHi - fLo;
	}


	/** Get the low end of the range. **/
	public double getLo ()
	{ return fLo; }


	/** Get the high end of the range.**/
	public double getHi ()
	{ return fHi; }


	/** Get the number of entries in the largest bin. **/
	public int getMax () {
		int max = 0;
		for (int i=0; i < fNumBins;i++)
			if (max < fBins.get(i).intValue()) max = fBins.get(i).intValue();
		return max;
	}


	/**
	 * This method returns a reference to the binIndices.
	 * Note that this means the values of the histogram
	 * could be altered by the caller object.
	 **/
	public Vector<Integer> getBinIndices() {
		return binIndices;
	}


	/**
	 * This method returns a reference to the fBins.
	 * Note that this means the values of the histogram
	 * could be altered by the caller object.
	 **/
	public Vector<Integer> getBins() {
		return fBins;
	}

	/** Get the number of entries in the smallest bin.**/
	public int getMin () {
		int min = getMax ();
		for (int i=0; i < fNumBins; i++)
			if (min > fBins.get(i).intValue()) min = fBins.get(i).intValue();
		return min;
	}


	/** Get the total number of entries not counting
	 * overflows and underflows.
	 **/
	public int getTotal () {
		int total = 0;
		for (int i=0; i < fNumBins; i++)
			total += fBins.get(i).intValue();
		return total;
	}

	/** Get the total number of bins
	 **/
	public int getFNumBins () {
		return fNumBins;
	}

	/**
	 * Add an entry to a bin.
	 * @param x double value added if it is in the range:
	 *   lo <= x < hi
	 **/
	public void add (double x) {
		if (x >= fHi) {
			for (int i = fNumBins; i <= x; i++) {
				binIndices.add(Integer.valueOf(i));
				fBins.add(Integer.valueOf(0)); 
			}
			fHi = x + 1;
			fRange = fHi - fLo;
			fNumBins = (int) x;
		}

		if (x >= fHi) fOverflows++;
		else if (x < fLo) fUnderflows++;
		else {
			double val = x - fLo;

			// Casting to int will round off to lower
			// integer value.
			int bin =  (int) (fNumBins *  (val/fRange) );

			// Increment the corresponding bin.
			fBins.set(bin, fBins.get(bin).intValue() + 1);
		}
	}


	/** Clear the histogram bins and the over and under flows.**/
	public void clear () {
		fBins = new Vector<Integer>(3);
		fOverflows = 0;
		fUnderflows= 0;
	}


	/**
	 * Provide access to the value in the bin element
	 * specified by bin.
	 * Return the underflows if bin value negative,
	 * Return the overflows if bin value more than
	 * the number of bins.
	 **/
	public int getBinIndex (int bin) {
		if (bin < 0)
			return 0;
		else if (bin >= fNumBins)
			return fNumBins;
		else
			return binIndices.get(bin).intValue();
	}


	/**
	 * Provide access to the value in the bin element
	 * specified by bin.
	 * Return the underflows if bin value negative,
	 * Return the overflows if bin value more than
	 * the number of bins.
	 **/
	public int getBinValue (int bin) {
		if (bin < 0)
			return fUnderflows;
		else if (bin >= fNumBins)
			return fOverflows;
		else
			return fBins.get(bin).intValue();
	}


	/**
	 * Get the average and standard deviation of the
	 * distribution of entries.
	 * @return double array
	 **/
	public double [] getStats () {
		int total = 0;

		double wt_total = 0;
		double wt_total2 = 0;
		double [] stat = new double[2];
		double bin_width = fRange/fNumBins;

		for (int i=0; i < fNumBins; i++) {
			total += fBins.get(i).intValue();

			double bin_mid =  (i - 0.5) * bin_width + fLo;
			wt_total  += fBins.get(i).intValue() * bin_mid;
			wt_total2 += fBins.get(i).intValue() * bin_mid * bin_mid;
		}

		if (total > 0) {
			stat[0] = wt_total / total;
			double av2 = wt_total2 / total;
			stat[1] = Math.sqrt (av2 - stat[0] * stat[0]);
		} else {
			stat[0] = 0.0;
			stat[1] = -1.0;
		}

		return stat;
	}// getStats()


	/**
	 * Create the histogram from a user derived array along with the
	 * under and overflow values.
	 * The low and high range values that the histogram
	 * corresponds to must be in passed as well.
	 *
	 * @param userBins array of int values.
	 * @param under number of underflows.
	 * @param over number of overflows.
	 * @param lo value of the lower range limit.
	 * @param hi value of the upper range limit.
	 **/
	public void pack (int [] user_bins,
			int under, int over,
			double lo, double hi) {
		fNumBins = user_bins.length;
		fBins = new Vector<Integer>(fNumBins);
		for (int i = 0; i < fNumBins; i++) {
			fBins.add(user_bins[i]);
		}

		fLo = lo;
		fHi = hi;
		fRange = fHi-fLo;
		fUnderflows = under;
		fOverflows = over;
	}// pack()

}
