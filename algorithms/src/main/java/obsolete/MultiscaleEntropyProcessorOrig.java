package obsolete;

import idea.conf.DeviceCapabilities;
import idea.intf.AbstractStreamProducer;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.Alarm;
import idea.model.PersistentItem;
import idea.analysis.EntropyFilter;
import idea.analysis.event.BeatBlock;
import idea.analysis.event.MSEBlock;
import idea.analysis.event.MetricsBlock;
import idea.analysis.event.RWaveEvent;
import idea.buffer.SignalBuffer;



public class MultiscaleEntropyProcessorOrig extends AbstractStreamProducer implements StreamConsumer {

	private static int verbose = 0;
	
	private final static int M_MAX = 10; /* maximum value of the parameter m */
	private final static int R_STEP_MAX = 10; /*
											 * maximum number of different r
											 * values
											 */

	/* Global variables */
	private double[][] SE = new double[R_STEP_MAX][M_MAX];
	private double r_min, r_max, r_step;
	private int c, m_min, m_max, m_step;

	private SignalBuffer<Integer> rri;


	public double process( int scale) {

		double r, sd;

		/* Initialize variables. */
		m_min = 2;
		m_max = 2;
		m_step = 1;
		r_min = -0.15;
		r_max = -0.15;
		r_step = 0.05;
		c = 0;

		/* Memory allocation. */
		double[] y = new double[rri.getSampleCount() / scale ];

		/* Process a single data file. */

		/* Calculate standard deviation. */
		// 12JAN12 wlb: sd = StandardDeviation();

		/* Perform the coarse-graining procedure. */
		CoarseGraining(scale, y);

		/* Calculate SampEn for each scale and each r value. */
		c = 0;
		// 12JAN12 wlb : Use the refrence EntropyProcessor algorithm!
		double entropy = -1; 
		entropy = EntropyFilter.SaEn( y, 6, m_min);
		/*
		 *  12JAN12 wlb : SampleEntropy(rfactor, scale, y, rri.getSampleCount());
		for (r = r_min; r <= r_max; r += r_step) {
			double rfactor = r;
			if( r < 0 ) {
				rfactor = - r*sd;
			}
			c++;
		}
		 */

		/* Print results. */
		// PrintResults(scale);

		return entropy;
		// 12JAN12 wlb : return SE[0][m_min];
	}

	private double StandardDeviation() {
		double sum = 0.0, sum2 = 0.0, sd;
		int j;

		int tot = rri.getSampleCount();
		for (j = 0; j < tot; j++) {
			int u_val = rri.get( j );
			sum += u_val;
			sum2 += u_val * u_val;
		}
		sd = Math.sqrt((sum2 - sum * sum / tot) / (tot - 1));
		return (sd);
	}

	private void CoarseGraining(int j,  double[] y) {
		int i, k;
		
		int tot = rri.getSampleCount();
		for (i = 0; i < tot / j; i++) {
			y[i] = 0;
			for (k = 0; k < j; k++)
				y[i] += rri.get( i * j + k);
			y[i] /= j;
		}
	}

	private void SampleEntropy(double r_new, int scale, double[] y, int tot) {
		int i, k, l, nlin_j;
		int[] cont = new int[M_MAX + 1];

		nlin_j = (tot / scale) - m_max;

		for (i = 0; i < M_MAX; i++)
			cont[i] = 0;

		for (i = 0; i < nlin_j; ++i) {
			for (l = i + 1; l < nlin_j; ++l) { /* self-matches are not counted */
				k = 0;
				while (k < m_max && Math.abs(y[i + k] - y[l + k]) <= r_new)
					cont[++k]++;
				if (k == m_max && Math.abs(y[i + m_max] - y[l + m_max]) <= r_new)
					cont[m_max + 1]++;
			}
		}

		for (i = 1; i <= m_max; i++) {
			if (cont[i + 1] == 0 || cont[i] == 0)
				SE[c][i] = -Math.log((double) 1 / ((nlin_j) * (nlin_j - 1)));
			else
				SE[c][i] = -Math.log((double) cont[i + 1] / cont[i]);
		}
	}

	void PrintResults(int scale) {
		int m, k;

		System.out.print("\n");
		for (m = m_min; m <= m_max; m += m_step)
			for (k = 0; k < c; k++) {
				System.out.format("\nm = %d,  r = %.3f\n\n", m, r_min + k * r_step);

				System.out.format("scale %d\t", scale);
				System.out.format("%.3f\t", SE[k][m]);
				System.out.print("\n");

			}
	}

	/* ********************************************************************************
	 * 
	 * BAD PRACTICE...this is really two classes in one
	 * 
	 * 
	 * **************************************************************************
	 * *****
	 */

	public MultiscaleEntropyProcessorOrig() {
		this(200, 0.15, 2);
	}

	public MultiscaleEntropyProcessorOrig(int count, double rfactor, int maxEpoch) {
		rri = new SignalBuffer<Integer>(count, true);
		
		assert( false ) : "This code is hacked for specific purposes and should not be used.";
		System.err.println( "[MultiscaleEntropyProcessorOrig] Specific purposes not for general MSE use." );

	}

	public void setRRI( SignalBuffer<Integer> rri ) {
		this.rri = rri;
	}
	
	public void addData( int [] vals ) {
		System.err.println("FIXME: THIS IS A BAD SOLUTION FOR A LIMITATION OF GENERICS!");
		
		Integer [] i_vals = new Integer[vals.length];
		for( int i = 0; i < vals.length ; i++ ) {
			i_vals[i] = vals[i];
		}
		rri.addData( i_vals );
	}
	
	public void addData( double [] vals ) {
		System.err.println("FIXME: THIS IS A BAD SOLUTION FOR A LIMITATION OF GENERICS!");
		
		Integer [] i_vals = new Integer[vals.length];
		for( int i = 0; i < vals.length ; i++ ) {
			i_vals[i] = (int)vals[i];
		}
		rri.addData( i_vals );
	}
	
	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {

		if (item instanceof RWaveEvent) {

			BeatBlock inblock = (BeatBlock)item;
			int val = inblock.getMs_interval();
			rri.addData(val);

			if (rri.getSampleCount() < rri.getBufferSize()) {
				if( verbose > 0 ) {
				System.out.println("   mse progress: " + rri.getSampleCount() + " out of " + rri.getBufferSize());
				}
				Alarm ai = new Alarm("mse", Alarm.INFO, 0, "Waiting: " + rri.getSampleCount() + " out of " + rri.getBufferSize(), true);
				ai.setTime( item.getTime() );
				fireAlarmEvent(this, ai);
				return;
			}


			double mse2 = process( 2 );
			double mse3 = process( 3 );
			double mse4 = process( 4 );
			double mse5 = process( 5 );
//			if (rfactor < 0) {
//				saEntropy = EntropyProcessor.SaEn(rri, -rfactor, maxEpoch);
//			} else {
//				saEntropy = EntropyProcessor.SaEn(rri, sd * rfactor, maxEpoch);
//			}

			MSEBlock block = new MSEBlock( );

			block.setMSE2((int) (mse2*100));
			block.setMSE3((int) (mse3*100));
			block.setMSE4((int) (mse4*100));
			block.setMSE5((int) (mse5*100));

			fireStreamEvent(0,this,StreamID.MEASUREMENT, block);

		}
	}
	
	@Override
	public DeviceCapabilities getStaticCapabilities() {
		DeviceCapabilities caps = new DeviceCapabilities(this.getClass());
		caps.addStream( StreamID.MEASUREMENT, MetricsBlock.class );
		return caps;	
	}
}
