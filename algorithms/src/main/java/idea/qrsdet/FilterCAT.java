package idea.qrsdet;

public class FilterCAT {

    protected int LPBUFFER_LGTH;
    protected int HPBUFFER_LGTH;
    // protected int PRE_BLANK;
    // protected int MIN_PEAK_AMP;// Prevents detections of peaks smaller than 150 uV.		
    protected int WINDOW_WIDTH;	// Moving window integration width.
    // filter delays plus 200 ms blanking delay
    // protected int FILTER_DELAY;
    // protected int DER_DELAY;

    protected long y1, y2, y;
    protected int ptr, ptrH;
    protected int[] data;
    protected int[] dataH;

    protected int LP60BUFFER_LGTH;
    protected int LP35BUFFER_LGTH;
    protected int LP25BUFFER_LGTH;

    protected int lp60ptr;
    protected int lp35ptr;
    protected int lp25ptr;
    
    protected int[] lp60_data;
    protected int[] lp35_data;
    protected int[] lp25_data;

    public FilterCAT(int sr) {

        int SAMPLE_RATE = sr;	/* Sample rate in Hz. */
        double MS_PER_SAMPLE = ((double)1000 / (double)SAMPLE_RATE);
        int MS25 = ((int)(25 / MS_PER_SAMPLE + 0.5));
        int MS125 = ((int)(125 / MS_PER_SAMPLE + 0.5));

        LPBUFFER_LGTH = (2 * MS25);
        HPBUFFER_LGTH = MS125;

        LP60BUFFER_LGTH = sr/60;
        LP35BUFFER_LGTH = sr/35;
        LP25BUFFER_LGTH = sr/25;

        initFilter();
    }


    /*************************************************************************
     *  lpfilt() implements the digital filter represented by the difference
     *  equation:
     *
     * 	y[n] = 2*y[n-1] - y[n-2] + x[n] - 2*x[t-24 ms] + x[t-48 ms]
     *
     *	Note that the filter delay is (LPBUFFER_LGTH/2)-1
     *
     **************************************************************************/

     public int lpfilt(int datum, int init) {

         long y0;
         int output, halfPtr;
         if (init > 0) {
             for (ptr = 0; ptr < LPBUFFER_LGTH; ++ptr)
                 data[ptr] = 0;
             y1 = y2 = 0;
             ptr = 0;
         }
         halfPtr = ptr - (LPBUFFER_LGTH / 2);	// Use halfPtr to index
         if (halfPtr < 0)							// to x[n-6].
             halfPtr += LPBUFFER_LGTH;

         y0 = (y1 << 1) - y2 + datum - (data[halfPtr] << 1) + data[ptr];
         y2 = y1;
         y1 = y0;
         output = (int)(y0 / ((LPBUFFER_LGTH * LPBUFFER_LGTH) / 4));
         data[ptr] = datum;			// Stick most recent sample into
         if (++ptr == LPBUFFER_LGTH)	// the circular buffer and update
             ptr = 0;					// the buffer pointer.

         return (output);
     }

     /******************************************************************************
     *  hpfilt() implements the high pass filter represented by the following
     *  difference equation:
     *
     *	y[n] = y[n-1] + x[n] - x[n-128 ms]
     *	z[n] = x[n-64 ms] - y[n] ;
     *
     *  Filter delay is (HPBUFFER_LGTH-1)/2
     ******************************************************************************/

     public int hpfilt(int datum, int init) {

         int z, halfPtr;
         if (init != 0) {
             for (ptrH = 0; ptrH < HPBUFFER_LGTH; ++ptrH)
                 dataH[ptrH] = 0;
             ptrH = 0;
             y = 0;
         }
         y += datum - dataH[ptrH];
         halfPtr = ptrH - (HPBUFFER_LGTH / 2);
         if (halfPtr < 0)
             halfPtr += HPBUFFER_LGTH;
         z = (int)(dataH[halfPtr] - (y / HPBUFFER_LGTH));
         dataH[ptrH] = datum;
         if (++ptrH == HPBUFFER_LGTH)
             ptrH = 0;
         return (z);
     }


    /*************************************************************************
    *  lp60filt() moving average Bessel
    *
    **************************************************************************/


    public int lp60filt(int datum) {

        int sum = 0;
        for (int i=0; i < LP60BUFFER_LGTH;i++) {
            sum += lp60_data[lp60ptr];
        }

        lp60_data[lp60ptr++] = datum;			// Stick most recent sample into
        lp60ptr %= LP60BUFFER_LGTH;

        return sum / LP60BUFFER_LGTH;
    }

    public int lp35filt(int datum) {

        int sum = 0;
        for (int i=0; i < LP35BUFFER_LGTH;i++) {
            sum += lp35_data[lp35ptr];
        }

        lp35_data[lp35ptr++] = datum;			// Stick most recent sample into
        lp35ptr %= LP35BUFFER_LGTH;

        return sum / LP35BUFFER_LGTH;
    }

    public int lp25filt(int datum) {


        
        int sum = 0;
        for (int i=0; i < LP25BUFFER_LGTH;i++) {
            sum += lp25_data[lp25ptr];
        }

        lp25_data[lp25ptr++] = datum;			// Stick most recent sample into
        lp25ptr %= LP25BUFFER_LGTH;

        return sum / LP25BUFFER_LGTH;
    }

    public void initFilter() {
        y1 = 0; y2 = 0;
        data = new int[LPBUFFER_LGTH];
        ptr = 0;
        y = 0;
        dataH = new int[HPBUFFER_LGTH];
        ptrH = 0;
        hpfilt(0, 1);		// Initialize filters.
        lpfilt(0, 1);

        lp60_data = new int[LP60BUFFER_LGTH];
        lp35_data = new int[LP35BUFFER_LGTH];
        lp25_data = new int[LP25BUFFER_LGTH];
        
        lp60ptr = 0;
        lp35ptr = 0;
        lp25ptr = 0;        
    }

    public int getValue(int datum) {
        //int fdatum;
		datum = lpfilt(datum, 0);
		datum = hpfilt(datum, 0);

        datum = lp60filt(datum);		// Low pass filter data.
        datum = lp35filt(datum);		// Low pass filter data.
        datum = lp25filt(datum);		// Low pass filter data.
        return (datum);
    } // end of getValue


	public int getSignalShift() {
		// WARNING: LP25BUFFER_LGTH added twice!
		// ...expecting a call to lp25filt after getValue() for addition of multiple leads
		// you really have to watch this closely....
		// ... really, I need a filter on each lead
		// ... array of filters
		return (HPBUFFER_LGTH + LPBUFFER_LGTH + LP60BUFFER_LGTH + LP35BUFFER_LGTH + LP25BUFFER_LGTH + LP25BUFFER_LGTH) / 2;
	}
}
