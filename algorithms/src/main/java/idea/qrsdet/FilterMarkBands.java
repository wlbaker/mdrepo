package idea.qrsdet;

public class FilterMarkBands extends FilterMark {

    /*  See DetectorFilterBanksOnly.java
     * 
     *  Subband 1 variables: 
     *    SUB1BUFFER_LGTH, ptrSb1, dataSb1
     *    (derived from LPBUFFER_LGTH, HPBUFFER_LGTH, ptr, ptrH, data, dataH
     *  Subband 2 variables:
     *    SUB2BUFFER_LGTH, ptrSb2, dataSb2
     *  Subband 3 variables:
     *    SUB3BUFFER_LGTH, ptrSb3, dataSb3
     * 
     */
    
    // protected int SUB1BUFFER_LGTH;
    // protected int ptrSb1;
	
	protected int SUB2BUFFER_LGTH;
	protected int ptrSb2;
	protected long z1, z2;
    protected int[] dataSb2;

	protected int SUB3BUFFER_LGTH;
	protected int ptrSb3;
    protected int[] dataSb3;
    
    protected int ptrMWI1, ptrMWI2,ptrMWI3;
    protected long sum1, sum2, sum3;
    protected int[] dataMWI1, dataMWI2, dataMWI3;
    
    
    public FilterMarkBands(int sr) {

    	super(sr);
    	
        SUB2BUFFER_LGTH = super.LPBUFFER_LGTH;
        SUB3BUFFER_LGTH = super.HPBUFFER_LGTH;
        
        initFilterBands();
    }


    /*************************************************************************
    *  hpfiltSb2() implements the digital filter represented by the difference
    *  equation:
    *
    * 	y[n] = -2*y[n-1] - y[n-2] + x[n] + 2*x[t-24 ms] + x[t-48 ms]
    *
    *	Note that the filter delay is (SUB2BUFFER_LGTH/2)-1
    *
    **************************************************************************/


    public int hpfiltSb2(int datum, int init) {

        long z0;
        int output1, halfPtr;
        if (init != 0) {
            for (ptrSb2 = 0; ptrSb2 < SUB2BUFFER_LGTH; ++ptrSb2)
                dataSb2[ptrSb2] = 0;
            z1 = z2 = 0;
            ptrSb2 = 0;
        }
        halfPtr = ptrSb2 - (SUB2BUFFER_LGTH / 2);	// Use halfPtr to index
        if (halfPtr < 0)							// to x[n-6].
            halfPtr += SUB2BUFFER_LGTH;

        z0 = -1*(z1 << 1) - z2 + datum + (dataSb2[halfPtr] << 1) + dataSb2[ptrSb2];
        z2 = z1;
        z1 = z0;
        output1 = (int)(z0 / ((SUB2BUFFER_LGTH * SUB2BUFFER_LGTH) / 4));
        dataSb2[ptrSb2] = datum;			// Stick most recent sample into
        if (++ptrSb2 == SUB2BUFFER_LGTH)	// the circular buffer and update
            ptrSb2 = 0;					// the buffer pointer.

        return (output1);
    }

    /******************************************************************************
     *  hpfiltSb3() implements the high pass filter represented by the following
     *  difference equation:
     *
     *	y[n] = y[n-1] + x[n] - x[n-128 ms]
     *	z[n] = x[n-64 ms] - y[n] ;
     *
     *  Filter delay is (HPBUFFER_LGTH-1)/2
     ******************************************************************************/
     public int hpfiltSb3(int datum, int init) {

         int z, halfPtr;
         if (init != 0) {
             for (ptrSb3 = 0; ptrSb3 < SUB3BUFFER_LGTH; ++ptrSb3)
                 dataSb3[ptrSb3] = 0;
             ptrSb3 = 0;
             y = 0;
         }
         y += datum - dataSb3[ptrSb3];
         halfPtr = ptrSb3 - (SUB3BUFFER_LGTH / 2);
         if (halfPtr < 0)
             halfPtr += SUB3BUFFER_LGTH;
         z = (int)(dataSb3[halfPtr] - (y / SUB3BUFFER_LGTH));
         dataSb3[ptrSb3] = datum;
         if (++ptrSb3 == SUB3BUFFER_LGTH)
             ptrSb3 = 0;
         return (z);
     }
    
    /*****************************************************************************
     * mwi1() implements a moving window integrator.  Actually, mwi1() averages
     * the signal values over the last WINDOW_WIDTH Feature 1 samples.
     *****************************************************************************/
     public int mwi1(int datum, int init) {

         int output1;
         if (init != 0) {
             for (ptrMWI1 = 0; ptrMWI1 < WINDOW_WIDTH; ++ptrMWI1)
                 dataMWI1[ptrMWI1] = 0;
             sum1 = 0;
             ptrMWI1 = 0;
         }
         sum1 += datum;
         sum1 -= dataMWI1[ptrMWI1];
         dataMWI1[ptrMWI1] = datum;
         if (++ptrMWI1 == WINDOW_WIDTH)
             ptrMWI1 = 0;
         if ((sum1 / WINDOW_WIDTH) > 32000)
             output1 = 32000;
         else
             output1 = (int)(sum1 / WINDOW_WIDTH);
         return (output1);
     }
    
     /*****************************************************************************
      * mwi2() implements a moving window integrator.  Actually, mwi2() averages
      * the signal values over the last WINDOW_WIDTH Feature 2 samples.
      *****************************************************************************/
      public int mwi2(int datum, int init) {

          int output2;
          if (init != 0) {
              for (ptrMWI2 = 0; ptrMWI2 < WINDOW_WIDTH; ++ptrMWI2)
                  dataMWI2[ptrMWI2] = 0;
              sum2 = 0;
              ptrMWI2 = 0;
          }
          sum2 += datum;
          sum2 -= dataMWI2[ptrMWI2];
          dataMWI2[ptrMWI2] = datum;
          if (++ptrMWI2 == WINDOW_WIDTH)
              ptrMWI2 = 0;
          if ((sum2 / WINDOW_WIDTH) > 32000)
              output2 = 32000;
          else
              output2 = (int)(sum2 / WINDOW_WIDTH);
          return (output2);
      }

      /*****************************************************************************
       * mwi3() implements a moving window integrator.  Actually, mwi3() averages
       * the signal values over the last WINDOW_WIDTH Feature 3 samples.
       *****************************************************************************/
       public int mwi3(int datum, int init) {

           int output3;
           if (init != 0) {
               for (ptrMWI3 = 0; ptrMWI3 < WINDOW_WIDTH; ++ptrMWI3)
                   dataMWI3[ptrMWI3] = 0;
               sum3 = 0;
               ptrMWI3 = 0;
           }
           sum3 += datum;
           sum3 -= dataMWI3[ptrMWI3];
           dataMWI3[ptrMWI3] = datum;
           if (++ptrMWI3 == WINDOW_WIDTH)
               ptrMWI3 = 0;
           if ((sum3 / WINDOW_WIDTH) > 32000)
               output3 = 32000;
           else
               output3 = (int)(sum3 / WINDOW_WIDTH);
           return (output3);
       }
      
    public void initFilterBands() {
        super.initFilter();
        
        y1 = 0; y2 = 0;
        dataSb2 = new int[SUB2BUFFER_LGTH];
        ptrSb2 = 0;
        
        hpfiltSb2(0, 1);		// Initialize filters.

        dataSb3 = new int[SUB3BUFFER_LGTH];
        ptrSb3 = 0;
        
        hpfiltSb3(0, 1);
        
        sum1 = 0;
        dataMWI1 = new int[WINDOW_WIDTH];
        ptrMWI1 = 0;

        mwi1(0, 1);
        
        sum2 = 0;
        dataMWI2 = new int[WINDOW_WIDTH];
        ptrMWI2 = 0;
        
        mwi2(0, 1);
        
        sum3 = 0;
        dataMWI3 = new int[WINDOW_WIDTH];
        ptrMWI3 = 0;
        
        mwi3(0, 1);
    }

    @Override
	public int getValue(int datum) {
    	int fdatum;
    	fdatum = super.getValue(datum);

        return (fdatum);
    } // end of getValue
}
