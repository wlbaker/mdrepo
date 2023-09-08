package idea.buffer;

import lombok.extern.slf4j.Slf4j;

/**
 * Abstract class for managing signal buffers.  CircularBuffer is based on this class.  Buffers can
 * be either LIFO or FIFO based on the "forward" indicator.
 * 
 * @author bbaker
 *
 * @param <T>
 */
@Slf4j
public class SignalBuffer<T extends Number> {
	private int insertPos;
	private boolean forward;

	private T[] buf;
	private int sampleSize;

	@SuppressWarnings("unchecked")
	public SignalBuffer( int siz, boolean forward) {
		buf = (T[]) new Number[siz];
		this.forward = forward;
	}

	public SignalBuffer( T[] dat, boolean forward) {
		buf = dat;
		this.sampleSize = dat.length;
		this.forward = forward;
	}

	public void addData(T[] dat) {
		synchronized (buf) {
			for (T pt : dat) {
				if( pt == null ) {
					log.error( "CANNOT INSERT NULL POINTS!");
				}
				assert( pt != null) : "CANNOT INSERT NULL POINTS";
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

	public void addData(T pt) {
		if( pt == null ) {
			System.err.println( "CANNOT INSERT NULL POINTS!");
		}
		assert( pt != null) : "CANNOT INSERT NULL POINTS";
		synchronized (buf) {
			buf[insertPos++] = pt;
			insertPos %= buf.length;
			sampleSize++;
			if (sampleSize > buf.length)
				sampleSize = buf.length;
		}
	}

	/**
	 * @brief Get the number of samples currently in the buffer.
	 * 
	 * The number of samples will be less than or equal to the buffer size.
	 * 
	 * @return current number of samples
	 */
	public int getSampleCount() {
		return sampleSize;
	}

	/**
	 * @brief Get the buffer size, which is also the maximum number of samples.
	 *
	 * Number of samples will be less than or equal to the buffer size.
	 * 
	 * @return created buffer size
	 */
	public int getBufferSize() {
		return buf.length;
	}

	public T get(int pos) {
		T val;
		synchronized (buf) {
			int offset = getOffset( pos );
			val = buf[offset];
		}
		return val;
	}

	public void clear() {
		insertPos = 0;
		sampleSize = 0;
	}

	public double[] asDoubles() {
		double [] data = new double[sampleSize];
		
		for (int idx = 0; idx < sampleSize; idx++ ) {
			data[idx] = ((Number)get(idx)).doubleValue();
		}

		return data;
	}

	public float[] asFloats() {
		float [] data = new float[sampleSize];
		
		for (int idx = 0; idx < sampleSize; idx++ ) {
			data[idx] = ((Number)get(idx)).floatValue();
		}

		return data;
	}

	public int[] asInts() {
		int [] data = new int[sampleSize];
		
		for (int idx = 0; idx < sampleSize; idx++ ) {
			data[idx] = ((Number)get(idx)).intValue();
		}

		return data;
	}

	public void set(int pos, T val) {
		synchronized (buf) {
			int offset = getOffset( pos );
			buf[offset] = val;
		}
		
	}

	private int getOffset(int pos) {
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
		return offset;
	}

}
