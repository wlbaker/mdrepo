package idea.buffer;

public class CircularDoubleBuffer { // implements Iterable<T> {
	private int insertPos;
	private boolean forward;

	private double[] buf;
	private int sampleSize;

	public CircularDoubleBuffer( int siz, boolean forward) {
		buf = new double[siz];
		this.forward = forward;
	}

	public CircularDoubleBuffer( double [] dat, boolean forward) {
		buf = dat;
		this.sampleSize = dat.length;
		this.forward = forward;
	}

	public void addData(double[] dat) {
		synchronized (buf) {
			for (double pt : dat) {
				buf[insertPos++] = pt;
				insertPos %= buf.length;
			}
			if (sampleSize < buf.length) {
				sampleSize += dat.length;
				if (sampleSize > buf.length)
					sampleSize = buf.length;
			}
		}
	}

	public void addData(int pt) {
		synchronized (buf) {
			buf[insertPos++] = pt;
			insertPos %= buf.length;
			sampleSize++;
			if (sampleSize > buf.length)
				sampleSize = buf.length;
		}
	}

	public int getSampleCount() {
		return sampleSize;
	}

	public int length() {
		return buf.length;
	}

	/*
	@Override
	public Iterator<T> iterator() {
		// TODO Auto-generated method stub
		return Arrays.asList(a);
	}
	*/

	public double get(int pos) {
		double val;
		synchronized (buf) {
			int offset;
			if (forward) {
				offset = insertPos - sampleSize + pos;
			} else {
				// reverse
				offset = insertPos - pos - 1; // the insertPos is actually 1
												// past the data end
			}
			offset %= buf.length;
			if (offset < 0)
				offset += buf.length;
			val = buf[offset];
		}
		return val;
	}

	public double[] asDoubles() {
		double [] data = new double[sampleSize];
		
		for (int idx = 0; idx < sampleSize; idx++ ) {
			data[idx] = get(idx);
		}

		return data;
	}

	public int[] asInts() {
		int [] data = new int[sampleSize];
		
		for (int idx = 0; idx < sampleSize; idx++ ) {
			data[idx] = (int) get(idx);
		}

		return data;
	}

}
