package idea.qrsdet;

public class FilterMark {

    protected int SAMPLE_RATE;	/* Sample rate in Hz. */
    protected double MS_PER_SAMPLE;
    
    protected int DERIV_LENGTH;
    protected int LPBUFFER_LGTH;
    protected int HPBUFFER_LGTH;
    // protected int PRE_BLANK;
    // protected int MIN_PEAK_AMP;// Prevents detections of peaks smaller than 150 uV.		
    protected int WINDOW_WIDTH;	// Moving window integration width.
    // filter delays plus 200 ms blanking delay
    // protected int FILTER_DELAY;
    // protected int DER_DELAY;

    protected long y1, y2, y, sum;
    protected int ptr, ptrH, derI1, derI2, ptr3;
    protected int[] data;
    protected int[] dataH;
    protected int[] derBuff;
    protected int[] derBuff2;
    protected int[] data3;

    public FilterMark(int sr) {
        SAMPLE_RATE = sr;	/* Sample rate in Hz. */
        MS_PER_SAMPLE = ((double)1000 / (double)SAMPLE_RATE);
        int MS10 = ((int)(10 / MS_PER_SAMPLE + 0.5));
        int MS25 = ((int)(25 / MS_PER_SAMPLE + 0.5));
        int MS80 = ((int)(80 / MS_PER_SAMPLE + 0.5));
        int MS125 = ((int)(125 / MS_PER_SAMPLE + 0.5));

        DERIV_LENGTH = MS10;
        LPBUFFER_LGTH = (2 * MS25);
        HPBUFFER_LGTH = MS125;
        // PRE_BLANK = MS195;
        // MIN_PEAK_AMP = 7; // Prevents detections of peaks smaller than 150 uV.		
        WINDOW_WIDTH = MS80;			// Moving window integration width.
        // filter delays plus 200 ms blanking delay
        // FILTER_DELAY = (int)(((double)DERIV_LENGTH / 2) + ((double)LPBUFFER_LGTH / 2 - 1) + (((double)HPBUFFER_LGTH - 1) / 2) + PRE_BLANK);
        // DER_DELAY = WINDOW_WIDTH + FILTER_DELAY + MS100;
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
    /*****************************************************************************
    *  deriv1 and deriv2 implement derivative approximations represented by
    *  the difference equation:
    *
    *	y[n] = x[n] - x[n - 10ms]
    *
    *  Filter delay is DERIV_LENGTH/2
    *****************************************************************************/
    public int deriv1(int x, int init) {

    	if( derBuff == null || derBuff.length == 0 ) {
    		return 0;       // wlb: 06012010
    	}
 
        int y;
        if (init != 0) {
            for (derI1 = 0; derI1 < DERIV_LENGTH; ++derI1)
                derBuff[derI1] = 0;
            derI1 = 0;
            return (0);
        }
        y = x - derBuff[derI1];
        derBuff[derI1] = x;
        if (++derI1 == DERIV_LENGTH)
            derI1 = 0;
        return (y);
    }


    public int deriv2(int x, int init) {

    	if( derBuff2 == null || derBuff2.length == 0 ) {
    		return 0;       // wlb: 06012010
    	}
    	
        int y;
        if (init != 0) {
            for (derI2 = 0; derI2 < DERIV_LENGTH; ++derI2)
                derBuff2[derI2] = 0;
            derI2 = 0;
            return 0;
        }
        y = x - derBuff2[derI2];
        derBuff2[derI2] = x;
        if (++derI2 == DERIV_LENGTH)
            derI2 = 0;
        return (y);
    }


    /*****************************************************************************
    * mvwint() implements a moving window integrator.  Actually, mvwint() averages
    * the signal values over the last WINDOW_WIDTH samples.
    *****************************************************************************/
    public int mvwint(int datum, int init) {

        int output;
        if (init != 0) {
            for (ptr3 = 0; ptr3 < WINDOW_WIDTH; ++ptr3)
                data3[ptr3] = 0;
            sum = 0;
            ptr3 = 0;
        }
        sum += datum;
        sum -= data3[ptr3];
        data3[ptr3] = datum;
        if (++ptr3 == WINDOW_WIDTH)
            ptr3 = 0;
        if ((sum / WINDOW_WIDTH) > 32000)
            output = 32000;
        else
            output = (int)(sum / WINDOW_WIDTH);
        return (output);
    }

    public void initFilter() {
        y1 = 0; y2 = 0;
        data = new int[LPBUFFER_LGTH];
        ptr = 0;
        y = 0;
        dataH = new int[HPBUFFER_LGTH];
        ptrH = 0;
        derBuff = new int[DERIV_LENGTH];
        derI1 = 0;
        derBuff2 = new int[DERIV_LENGTH];
        derI2 = 0;
        sum = 0;
        data3 = new int[WINDOW_WIDTH];
        ptr3 = 0;
        hpfilt(0, 1);		// Initialize filters.
        lpfilt(0, 1);
        mvwint(0, 1);
        deriv1(0, 1);
        deriv2(0, 1);
    }

    public int getValue(int datum) {
        int fdatum;
        fdatum = lpfilt(datum, 0);		// Low pass filter data.
        fdatum = hpfilt(fdatum, 0);	// High pass filter data.
        fdatum = deriv2(fdatum, 0);	// Take the derivative.
        fdatum = Math.abs(fdatum);				// Take the absolute value.
        fdatum = mvwint(fdatum, 0);	// Average over an 80 ms window .
        return (fdatum);
    } // end of getValue
}
