package idea.analysis;

import idea.conf.DeviceCapabilities;
import idea.conf.DeviceConfiguration;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.Alarm;
import idea.model.IntfUtil;
import idea.model.PersistentItem;

import java.util.Date;

import lombok.extern.slf4j.Slf4j;
import idea.analysis.ecg.HRVPoint;
import idea.analysis.event.BeatBlock;
import idea.buffer.SignalBuffer;

@Slf4j
public class HRVProcessor extends AbstractAnalysisProcessor {
	// ? private double sampling_frequency;
	// ? private double sample_period;
	private static DeviceCapabilities caps;

	private int sample_size;

	public int resampling_factor;
	public double resampling_frequency;
	public int resample_size;

	// private ArrayList buffer = new ArrayList(sample_size);

	private double[] res_smooth;
	private double[] res_resampled;
	private double[] res_resampled_real;
	private double[] res_resampled_img;
	public double[] frequencies;

	private SignalBuffer<Integer> rri;

	private boolean did_alarm;

	private long recalc_last;

	private long recalc_period = 5000;

	static {

		caps = new DeviceCapabilities(HRVProcessor.class);

		caps.addStream(StreamID.MEASUREMENT, HRVPoint.class);

		caps.setName("HRV");

	}

	public HRVProcessor(double sampling_frequency, // ie, 182 samples/sec
			int sample_size, // ie, 2 mins --> 182*160=29120 samples
			int resample_size) // used in fft, ie, 1024. must be multiple of 2
	{
		rri = new SignalBuffer<Integer>(200, true);
		this.sample_size = sample_size;

		// ? this.sample_period = 1.0 / sampling_frequency;

		this.resampling_factor = sample_size / resample_size;
		this.resampling_frequency = sampling_frequency / resampling_factor;
		this.resample_size = resample_size;

		this.res_smooth = new double[sample_size];
		this.res_resampled = new double[resample_size];
		this.res_resampled_real = new double[resample_size];
		this.res_resampled_img = new double[resample_size];
		this.frequencies = new double[resample_size / 2];

		// ??? this.tmpData_real = new double[resample_size];
		// ??? this.tmpData_img = new double[resample_size];

	}

	public HRVPoint ComputeHRV(int[] rrIntervals) {

		HRVPoint res = new HRVPoint(this);

		/*
		 * if (rrIntervals.Length < sample_size) { throw new ArgumentOutOfRangeException("Buffer not full"); }
		 */

		// this.smoothRRintervals(rrIntervals);
		this.resampleIrregular(rrIntervals);
		this.rescale();
		this.filterWithHammingWindow();
		this.toComplexArray();
		this.generateFFT();

		this.getFreqMag();
		res.setHF(this.getHRVHF());
		res.setLF(this.getHRVLF());
		res.setHF_LF(this.getHRVHFLF());
		if (res.getHF_LF() != 0) {
			res.setLF_HF(1 / getHRVHFLF());
		}

		return res;
	}

	public void ComputeFFT(int[] signal) {

		// this.smoothRRintervals(rrIntervals);
		this.resampleRegular(signal);
		this.rescale();
		this.filterWithHammingWindow();
		this.toComplexArray();
		this.generateFFT();
		this.getFreqMag();

	}

	private void toComplexArray() {
		for (int i = 0; i < res_resampled_real.length; ++i) {
			// res_resampled_real[i] = 10 * Math.Cos(2 * Math.PI /
			// res_resampled_real.Length * 10.0 * i);
			res_resampled_real[i] = res_resampled[i];
			res_resampled_img[i] = 0.0;
			// outFile.WriteLine(res_resampled_real[i] + "\t" +
			// res_resampled_img[i]);
		}
	}

	private void createRegularSignal(int[] rIntervals) {

		if (rIntervals.length < 1)
			return;

		int timeSpan;
		double delta;
		int ridx = 0; // resample idx
		int iidx = 0; // interval idx

		// first smoothed interval is not interpolated
		while (ridx <= rIntervals[0] && ridx < res_smooth.length) {
			res_smooth[ridx++] = rIntervals[0];
		}

		iidx = 1;
		if (ridx == 0) {
			ridx++; // should never happen, but don't crash either
		}

		while (ridx < sample_size && iidx < rIntervals.length) {

			timeSpan = rIntervals[iidx];
			delta = (rIntervals[iidx] - rIntervals[iidx - 1]) / ((double) timeSpan);
			iidx++;

			for (int j = 0; j < timeSpan && ridx < sample_size; ++j) {
				res_smooth[ridx] = res_smooth[ridx - 1] + delta;
				ridx++;
			}
		}

		// if anything is left...hopefully not...last interval is not
		// interpolated either
		// actually, this is indication that we don't have enough data!
		while (ridx < sample_size) {
			res_smooth[ridx] = res_smooth[ridx - 1];
			ridx++;
		}
	}

	private void resampleIrregular(int[] rIntervals) {

		createRegularSignal(rIntervals);

		double mean;
		double count = 0;

		for (int i = 0; i < res_resampled.length; ++i) {

			count = 0;

			for (int j = 0; j < resampling_factor; ++j) {
				count += res_smooth[i * resampling_factor + j];
			}
			mean = count / resampling_factor;

			res_resampled[i] = mean;
		}
	}

	private void resampleRegular(int[] signal) {

		double step = signal.length / (double) res_resampled.length;

		for (int i = 0; i < res_resampled.length; ++i) {

			int idx = (int) (step * i);
			res_resampled[i] = signal[idx];
		}

	}

	private void rescale() {

		double max = res_resampled[0];
		double min = res_resampled[0];

		for (int i = 1; i < res_resampled.length; ++i) {
			if (res_resampled[i] > max) {
				max = res_resampled[i];
			}

			if (res_resampled[i] < min) {
				min = res_resampled[i];
			}
		}

		double scale = (max + min) / 2;

		for (int i = 0; i < res_resampled.length; ++i) {
			res_resampled[i] = res_resampled[i] - scale;
		}

	}

	private void filterWithHammingWindow() {
		for (int i = 0; i < res_resampled.length; ++i) {
			res_resampled[i] = res_resampled[i]
					* (0.54 - 0.46 * Math.cos(2 * Math.PI * i / (res_resampled.length - 1)));
		}
	}

	private void generateFFT() {
		int n = res_resampled_real.length;
		int nm1 = n - 1;
		int nd2 = n / 2;
		int m = (int) (Math.log10(n) / Math.log10(2));
		int j = nd2;

		int k;
		double tr;
		double ti;
		// bit reversal sort
		for (int i = 1; i <= n - 2; ++i) {
			if (i < j) {
				tr = res_resampled_real[j];
				ti = res_resampled_img[j];

				res_resampled_real[j] = res_resampled_real[i];
				res_resampled_img[j] = res_resampled_img[i];

				res_resampled_real[i] = tr;
				res_resampled_img[i] = ti;
			}
			k = nd2;
			while (k <= j) {
				j -= k;
				k >>= 1;
			}
			j += k;
		}

		int le;
		int le2;
		int jm1;
		int ip;
		double ur;
		double ui;
		double sr;
		double si;
		for (int l = 1; l <= m; ++l) {
			le = (int) Math.pow(2, l);
			le2 = le / 2;
			ur = 1.0;
			ui = 0.0;
			sr = Math.cos(Math.PI / le2);
			si = -Math.sin(Math.PI / le2);
			for (j = 1; j <= le2; ++j) {
				jm1 = j - 1;
				for (int i = jm1; i <= nm1; i += le) {
					ip = i + le2;
					tr = res_resampled_real[ip] * ur - res_resampled_img[ip] * ui;
					ti = res_resampled_real[ip] * ui + res_resampled_img[ip] * ur;
					res_resampled_real[ip] = res_resampled_real[i] - tr;
					res_resampled_img[ip] = res_resampled_img[i] - ti;
					res_resampled_real[i] = res_resampled_real[i] + tr;
					res_resampled_img[i] = res_resampled_img[i] + ti;
				}
				tr = ur;
				ur = tr * sr - ui * si;
				ui = tr * si + ui * sr;
			}

		}

	}

	public void getFreqMag() {

		for (int i = 0; i < frequencies.length; ++i) {
			frequencies[i] = Math
					.sqrt(res_resampled_real[i] * res_resampled_real[i] + res_resampled_img[i] * res_resampled_img[i]);
		}

	}

	public double getHRVLF() {
		// low frequency components for HRV go from 0.05 to 0.15 Hz
		int index_low = (int) (0.04 * (frequencies.length) / resampling_frequency) + 1;
		int index_med = (int) (0.15 * (frequencies.length) / resampling_frequency) + 1;

		double sum_lf = 0.0;
		for (int i = index_low; i <= index_med; ++i) {
			sum_lf += Math.sqrt(frequencies[i] * frequencies[i] / resample_size);
		}

		return sum_lf;
	}

	public double getHRVHF() {
		// high frequency components for HRV go from 0.15 to 0.4 Hz
		int index_med = (int) (0.15 * (frequencies.length) / resampling_frequency) + 1;
		int index_high = (int) (0.4 * (frequencies.length) / resampling_frequency) + 1;

		double sum_hf = 0.0;
		for (int i = index_med; i <= index_high; ++i) {
			sum_hf += Math.sqrt(frequencies[i] * frequencies[i] / resample_size);
		}

		return sum_hf;
	}

	public double getHRVHFLF() {
		double lf = this.getHRVLF();
		double hf = this.getHRVHF();

		if (lf == 0.0)
			return 0.0;
		else
			return hf / lf;
	}

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {
		try {
			_signalEvent(jobID, source, sid, item);
		} catch (Exception ee) {
			log.error("signalevent err", ee);
		}
	}

	public void _signalEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {
		if (item instanceof BeatBlock) {

			BeatBlock block = (BeatBlock) item;
			// since r in ms, use rri in ms!
			int val = block.getMs_interval();

			addOneRWave(IntfUtil.getTime(block), val);
		}
	}

	public void addOneRWave(long tm, int val) {

		// {
		// System.out.print("ent* ");
		// Date dt = new Date(tm);
		// SimpleDateFormat fmt = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		// System.out.println(fmt.format(dt));
		// }
		rri.addData(val);

		if (rri.getSampleCount() < rri.getBufferSize()) {
			did_alarm = true;
			Alarm ai = new Alarm("hrven", Alarm.INFO, 0,
					"Waiting: " + rri.getSampleCount() + " out of " + rri.getBufferSize(), true);
			ai.setTm(new Date(tm));
			fireAlarmEvent(this, ai);
			return;
		}

		boolean process_flag;
		if (recalc_period <= 0 || recalc_last == 0) {
			process_flag = true;
		} else {
			process_flag = (tm - recalc_last > recalc_period);
		}

		if (process_flag) {
			if (did_alarm) {
				Alarm ai = new Alarm("hrven", Alarm.CLEAR, 0, "", true);
				ai.setTm(new Date(tm));
				fireAlarmEvent(this, ai);
			}
			recalc_last = tm;
			int[] rris = rri.asInts();
			HRVPoint block = ComputeHRV(rris);
			block.setTm(new Date(tm));

			// NumericBlock b = new NumericBlock(block);
			fireStreamEvent(0, this, StreamID.MEASUREMENT, block);
		}
	}

	@Override
	public DeviceConfiguration getConfiguration() {
		return caps;
	}

	@Override
	public DeviceCapabilities getStaticCapabilities() {
		return caps;
	}

	@Override
	void reset() {
		if (rri != null) {
			rri.clear();
		}
	}

}
