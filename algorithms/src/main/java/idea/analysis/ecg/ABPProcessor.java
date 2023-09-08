package idea.analysis.ecg;

import idea.conf.DeviceCapabilities;
import idea.conf.DeviceConfiguration;
import idea.intf.AbstractStreamProducer;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.PersistentItem;

import java.util.Collections;
import java.util.Comparator;
import java.util.LinkedList;

import idea.analysis.event.ABPBlock;

class GreaterThan implements Comparator<Double> {
	@Override
	public int compare(Double d0, Double d1) {

		return d1.compareTo(d0);
	}
}

class LessThan implements Comparator<Double> {
	@Override
	public int compare(Double d0, Double d1) {

		return d0.compareTo(d1);
	}
}

public class ABPProcessor extends AbstractStreamProducer implements
		StreamConsumer {

	private double[] dat = new double[3]; // last three measurements
	private double[] avg = new double[3]; // last three averages to determine
											// local max/min

	private LinkedList<Double> systolic = new LinkedList<Double>();
	private LinkedList<Double> diastolic = new LinkedList<Double>();

	private double tmpSystolic = 0.0;
	private double tmpDiastolic = 0.0;

	Comparator<Double> greatestOrder;
	Comparator<Double> leastOrder;
	
	private static DeviceCapabilities caps;
	static {
		caps = new DeviceCapabilities(ABPProcessor.class);
		caps.addStream(StreamID.MEASUREMENT, ABPBlock.class );
	}
	

	public ABPProcessor(int sampleHz) {
		// this.sampleHz = sampleHz;

		greatestOrder = new GreaterThan();
		leastOrder = new LessThan();
	}

	public void tempMeasurement(double[] abp, int start, int end, int topn) {
		systolic = new LinkedList<Double>();
		diastolic = new LinkedList<Double>();

		if (end == 0) {
			end++; // i is never ==0 on loop
		}
		int loop_count = 0;
		double last = abp[start];
		for (int i = start; i != end; i++) {
			loop_count++;

			if (loop_count > 10000) {
				System.err.println("abpProcessor is loopy?");
				System.exit(0);
			}

			if (i == abp.length) {
				i = 0;
			}
			double v = abp[i];

			if (v == last) {
				continue; // unique values!
			}
			last = v;

			dat[2] = dat[1];
			dat[1] = dat[0];
			dat[0] = v;

			if (loop_count < 3) {
				continue;
			}

			avg[2] = avg[1];
			avg[1] = avg[0];
			avg[0] = 0.25 * dat[0] + 0.5 * dat[1] + 0.25 * dat[2]; // a little
																	// filter

			if (avg[1] > avg[0] && avg[1] > avg[2]) {
				// we have a local max at avg[1], record systolic
				systolic.add(avg[1]);
			}
			if (avg[1] < avg[0] && avg[1] < avg[2]) {
				// we have a local max at avg[1], record diastolic
				diastolic.add(avg[1]);
			}
		}

		// IComparer reverseDouble = new IComparer<double>() {
		// int Compare(double x, double y){
		// return y.CompareTo(x);
		// }
		// };

		tmpSystolic = 0.0;
		if (systolic.size() > 0) {
			Collections.sort(systolic, greatestOrder);

			double cutoff = systolic.get(0) * 0.8;
			double tot = 0;
			double count = 0;
			for (int i = 0; i < topn && i < systolic.size(); i++) {
				if (systolic.get(i) > cutoff) {
					tot += systolic.get(i);
					count++;
				}
			}

			tmpSystolic = (tot / count);
		}

		tmpDiastolic = 0.0;
		if (diastolic.size() > 0) {
			Collections.sort(diastolic, leastOrder);

			double cutoff = diastolic.get(0) * 1.2;
			double tot = 0;
			double count = 0;
			for (int i = 0; i < topn && i < diastolic.size(); i++) {
				if (diastolic.get(i) < cutoff) {
					tot += diastolic.get(i);
					count++;
				}
			}
			tmpDiastolic = (tot / count);
		}

	}

	public void addMeasurement(double v) {
		/*
		 * dat[2] = dat[1]; dat[1] = dat[0]; dat[0] = v;
		 * 
		 * avg[2] = avg[1]; avg[1] = avg[0]; avg[0] = 0.25 * dat[0] + 0.5 *
		 * dat[1] + 0.25 * dat[2]; // a little filter
		 * 
		 * if (avg[1] > avg[0] && avg[1] > avg[2]) { // we have a local max at
		 * avg[1], record systolic systolic.Add( avg[1]); systolicDrop.Add(
		 * currSystolic); currSystolic = 0; } if (avg[1] < avg[0] && avg[1] <
		 * avg[2]) { // we have a local max at avg[1], record diastolic
		 * diastolic.Add( avg[1]); diastolicDrop.Add( currDiastolic);
		 * currDiastolic = 0; }
		 * 
		 * currSystolic++; currDiastolic++;
		 * 
		 * // cheat //int d = systolicDrop[0]; //d--; //if( d <= 0 )
		 * headSystolic--; headDiastolic--;
		 * 
		 * //if (headSystolic <= 0 && systolic.Count() > 0 ) { // headSystolic =
		 * systolicDrop[0]; // systolic.RemoveAt(0); //
		 * systolicDrop.RemoveAt(0); //} //if (headDiastolic <= 0 &&
		 * diastolic.Count() > 0 ) { // headDiastolic = diastolicDrop[0]; //
		 * diastolic.RemoveAt(0); // diastolicDrop.RemoveAt(0); // }
		 */
	}

	public double getSystolic() {

		return tmpSystolic;

		/*
		 * if( systolic.Count() < 5 ) { return 0; // not enough data }
		 * 
		 * double m = systolic[0];
		 * 
		 * for (int i = 0; i < systolic.Count(); i++) { if (systolic[i] > m) m =
		 * systolic[i]; }
		 * 
		 * int count = 0; double cutoff = m * 0.9; double tot = 0.0; foreach
		 * (double val in systolic ) { if ( val > cutoff) { count++; tot += val;
		 * } }
		 * 
		 * return (tot / count);
		 */
	}

	public double getDiastolic() {

		return tmpDiastolic;

		/*
		 * if (diastolic.Count() < 5) { return 0; // not enough data }
		 * 
		 * double m = diastolic[0];
		 * 
		 * for (int i = 0; i < diastolic.Count(); i++) { if (diastolic[i] < m) m
		 * = diastolic[i]; }
		 * 
		 * int count = 0; double cutoff = m * 1.2; double tot = 0.0; foreach
		 * (double val in diastolic) { if (val < cutoff) { count++; tot += val;
		 * } }
		 * 
		 * return (tot / count);
		 */
	}


	@Override
	public DeviceCapabilities getStaticCapabilities() {
		return caps;
	}

	@Override
	public DeviceConfiguration getConfiguration() {
		return getStaticCapabilities();
	}

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {
		// TODO Auto-generated method stub
		
	}

}
