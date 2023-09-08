package idea.qrsdet;

import idea.conf.DeviceCapabilities;

public class DetectorPanTompkins extends AbstractDetector {

    public DetectorPanTompkins() {
    	
    }
    
    public DetectorPanTompkins(int sr) {
    	setSampleRate( sr );
    }
    
    @Override
	public void setSampleRate(int sr) {
        sampleRate = sr;	/* Sample rate in Hz. */
        MS_PER_SAMPLE = ((double)1000 / (double)sampleRate);
        MS10 = ((int)(10 / MS_PER_SAMPLE + 0.5));
        MS25 = ((int)(25 / MS_PER_SAMPLE + 0.5));
        MS80 = ((int)(80 / MS_PER_SAMPLE + 0.5));
        MS95 = ((int)(95 / MS_PER_SAMPLE + 0.5));
        MS100 = ((int)(100 / MS_PER_SAMPLE + 0.5));
        MS125 = ((int)(125 / MS_PER_SAMPLE + 0.5));
        MS150 = ((int)(150 / MS_PER_SAMPLE + 0.5));
        MS195 = ((int)(195 / MS_PER_SAMPLE + 0.5));
        MS220 = ((int)(220 / MS_PER_SAMPLE + 0.5));
        MS360 = ((int)(360 / MS_PER_SAMPLE + 0.5));
        MS1000 = sampleRate;
        MS1500 = ((int)(1500 / MS_PER_SAMPLE));
        DERIV_LENGTH = MS10;
        LPBUFFER_LGTH = (2 * MS25);
        HPBUFFER_LGTH = MS125;
        PRE_BLANK = MS195;
        MIN_PEAK_AMP = 7; // Prevents detections of peaks smaller than 150 uV.		
        WINDOW_WIDTH = MS80;			// Moving window integration width.
        // filter delays plus 200 ms blanking delay
        FILTER_DELAY = (int)(((double)DERIV_LENGTH / 2) + ((double)LPBUFFER_LGTH / 2 - 1) + (((double)HPBUFFER_LGTH - 1) / 2) + PRE_BLANK);
        DER_DELAY = WINDOW_WIDTH + FILTER_DELAY + MS100;
        qpkcnt = 0;
        qrsbuf = new int[8];
        noise = new int[8];
        rrbuf = new int[8];
        rsetBuff = new int[8];
        rsetCount = 0;
        sbpeak = 0;
        sbcount = MS1500;
        QrsDelay = 0;

        DDBuffer = new int[DER_DELAY];	/* Buffer holding derivative data. */
        filter = new FilterMark(sampleRate);
        filter.initFilter();
        initQrsDetector();
    }

    @Override
	public int getSampleRate() {
    	return MS1000;
    }


    protected int sampleRate;	/* Sample rate in Hz. */
    protected double MS_PER_SAMPLE;
    protected int MS10;
    protected int MS25;
    protected int MS80;
    protected int MS95;
    protected int MS100;
    protected int MS125;
    protected int MS150;
    protected int MS195;
    protected int MS220;
    protected int MS360;
    protected int MS1000;
    protected int MS1500;
    protected int DERIV_LENGTH;
    protected int LPBUFFER_LGTH;
    protected int HPBUFFER_LGTH;
    protected int PRE_BLANK;
    protected int MIN_PEAK_AMP;// Prevents detections of peaks smaller than 150 uV.		
    protected int WINDOW_WIDTH;	// Moving window integration width.
    // filter delays plus 200 ms blanking delay
    protected int FILTER_DELAY;
    protected int DER_DELAY;

    protected static long currTimeStamp;

    protected int det_thresh, qpkcnt;
    protected int[] qrsbuf;
    protected int[] noise;
    protected int[] rrbuf;
    protected int[] rsetBuff;
    protected int rsetCount = 0;
    protected int nmean, qmean, rrmean;
    protected int count, sbpeak, sbloc, sbcount;
    protected int maxder, lastmax;
    protected int initBlank, initMax;
    protected int preBlankCnt, tempPeak;
    protected FilterMark filter;
    protected int fdatum, QrsDelay;
    protected int i, newPeak;
    protected int peakmax, peaktimeSinceMax, peaklastDatum;

    final static double TH = 0.3125;

    protected int[] DDBuffer;
    protected int DDPtr;	/* Buffer holding derivative data. */

    // final static int MEMMOVELEN = 7 * sizeof(int);
    final static int MEMMOVECT = 7;

    /**************************************************************
    * peak() takes a datum as input and returns a peak height
    * when the signal returns to half its peak height, or 
    **************************************************************/

    public int Peak(int datum, int init) {

        int pk = 0;

        if (init != 0)
            peakmax = peaktimeSinceMax = 0;

        if (peaktimeSinceMax > 0)
            ++peaktimeSinceMax;

        if ((datum > peaklastDatum) && (datum > peakmax)) {
            peakmax = datum;
            if (peakmax > 2)
                peaktimeSinceMax = 1;
        } else if (datum < (peakmax >> 1)) {
            pk = peakmax;
            peakmax = 0;
            peaktimeSinceMax = 0;
        } else if (peaktimeSinceMax > MS95) {
            pk = peakmax;
            peakmax = 0;
            peaktimeSinceMax = 0;
        }
        peaklastDatum = datum;
        return (pk);
    }

    /********************************************************************
    mean returns the mean of an array of integers.  It uses a slow
    sort algorithm, but these arrays are small, so it hardly matters.
    ********************************************************************/

    public int mean(int[] array, int datnum) {
        long sum;
        int i;

        for (i = 0, sum = 0; i < datnum; ++i)
            sum += array[i];
        sum /= datnum;
        return ((int)sum);
    }

    /****************************************************************************
     thresh() calculates the detection threshold from the qrs mean and noise
     mean estimates.
    ****************************************************************************/

    public static int thresh(int qmean, int nmean) {
        int thrsh, dmed;
        double temp;
        dmed = qmean - nmean;
        /*	thrsh = nmean + (dmed>>2) + (dmed>>3) + (dmed>>4); */
        temp = dmed;
        temp *= TH;
        dmed = (int)temp;
        thrsh = nmean + dmed; /* dmed * THRESHOLD */
        return (thrsh);
    }

    /***********************************************************************
        BLSCheck() reviews data to see if a baseline shift has occurred.
        This is done by looking for both positive and negative slopes of
        roughly the same magnitude in a 220 ms window.
    ***********************************************************************/

    
    public int BLSCheck(int[] dBuf, int dbPtr ) {
    	// int maxder;
    
        int max, min, maxt, mint, t, x;
        max = min = maxt = mint = t = x = 0;

        for (t = 0; t < MS220; ++t) {
            x = dBuf[dbPtr];
            if (x > max) {
                maxt = t;
                max = x;
            } else if (x < min) {
                mint = t;
                min = x;
            }
            if (++dbPtr == DER_DELAY)
                dbPtr = 0;
        }

        maxder = max;
        min = -min;

        /* Possible beat if a maximum and minimum pair are found
            where the interval between them is less than 150 ms. */

        if ((max > (min >> 3)) && (min > (max >> 3)) &&
            (Math.abs(maxt - mint) < MS150))
            return (0);

        else
            return (1);
    }

    //     initi 						/// <summary>
    /// ///////////////////////////////////////////////////////////////
    /// </summary>
    public void initQrsDetector() {

        for (i = 0; i < 8; ++i) {
            noise[i] = 0;	/* Initialize noise buffer */
            rrbuf[i] = MS1000;/* and R-to-R interval buffer. */
        }

        qpkcnt = maxder = lastmax = count = sbpeak = 0;
        initBlank = initMax = preBlankCnt = DDPtr = 0;
        sbcount = MS1500;

        filter.initFilter(); //QRSFilter(0,1) ;	/* initialize filters. */
        Peak(0, 1);
    }

    @Override
	public int getValue(int pending, int datum) {
        int delay = _getValue(datum);

        int threshold = 1;
        if (delay > threshold) {
            fireBeatDetection(-1, 0, -1, leadId, 0);
        }

        return delay;
    }

    /// <summary>
    //main find value
    /// </returns>
    public int _getValue(int datum) {

        int fdatum = 0;
        int QrsDelay = 0;
        int newPeak = 0;
        int aPeak = 0;
        //Console.Write(datum+" ");
        fdatum = filter.getValue(datum);
        //Console.WriteLine(fdatum);
        /* Wait until normal detector is ready before calling early detections. */

        aPeak = Peak(fdatum, 0);
        if (aPeak < MIN_PEAK_AMP)
            aPeak = 0;

        // Hold any peak that is detected for 200 ms
        // in case a bigger one comes along.  There
        // can only be one QRS complex in any 200 ms window.

        newPeak = 0;
        if (aPeak != 0 && !(preBlankCnt != 0)) {        
            // If there has been no peak for 200 ms
            // save this one and start counting.
            tempPeak = aPeak;
            preBlankCnt = PRE_BLANK;         // MS200
        } else if (!(aPeak != 0) && preBlankCnt != 0) { 
            // If we have held onto a peak for
            // 200 ms pass it on for evaluation.
            if (--preBlankCnt == 0)
                newPeak = tempPeak;
        } else if (aPeak != 0) {           
            // If we were holding a peak, but
            // this ones bigger, save it and
            if (aPeak > tempPeak) {          // start counting to 200 ms again.
                tempPeak = aPeak;
                preBlankCnt = PRE_BLANK;     // MS200
            } else if (--preBlankCnt == 0)
                newPeak = tempPeak;
        }

        /* Save derivative of raw signal for T-wave and baseline
           shift discrimination. */

        DDBuffer[DDPtr] = filter.deriv1(datum, 0);
        if (++DDPtr == DER_DELAY)
            DDPtr = 0;

        /* Initialize the qrs peak buffer with the first eight 	*/
        /* local maximum peaks detected.						*/

        if (qpkcnt < 8) {
            ++count;
            if (newPeak > 0) count = WINDOW_WIDTH;
            if (++initBlank == MS1000) {
                initBlank = 0;
                qrsbuf[qpkcnt] = initMax;
                initMax = 0;
                ++qpkcnt;
                if (qpkcnt == 8) {
                    qmean = mean(qrsbuf, 8);
                    nmean = 0;
                    rrmean = MS1000;
                    sbcount = MS1500 + MS150;
                    det_thresh = thresh(qmean, nmean);
                }
            }
            if (newPeak > initMax)
                initMax = newPeak;
        } else	/* Else test for a qrs. */ {
            ++count;
            if (newPeak > 0) {


                /* Check for maximum derivative and matching minima and maxima
                   for T-wave and baseline shift rejection.  Only consider this
                   peak if it doesn't seem to be a base line shift. */

                if (!(BLSCheck(DDBuffer, DDPtr) != 0)) {


                    // Classify the beat as a QRS complex
                    // if the peak is larger than the detection threshold.

                    if (newPeak > det_thresh) {

                        //memmove(&qrsbuf[1], qrsbuf, MEMMOVELEN) ;  // documentation says dest, source, length
                        for (int i = MEMMOVECT; i > 0; i--) {
                            qrsbuf[i] = qrsbuf[i - 1];
                        }


                        qrsbuf[0] = newPeak;
                        qmean = mean(qrsbuf, 8);
                        det_thresh = thresh(qmean, nmean);
                        //memmove(&rrbuf[1], rrbuf, MEMMOVELEN) ;
                        for (int i = MEMMOVECT; i > 0; i--) {
                            rrbuf[i] = rrbuf[i - 1];
                        }
                        rrbuf[0] = count - WINDOW_WIDTH;
                        rrmean = mean(rrbuf, 8);
                        sbcount = rrmean + (rrmean >> 1) + WINDOW_WIDTH;
                        count = WINDOW_WIDTH;

                        sbpeak = 0;

                        lastmax = maxder;
                        maxder = 0;
                        QrsDelay = WINDOW_WIDTH + FILTER_DELAY;
                        initBlank = initMax = rsetCount = 0;
                    }

                    // If a peak isn't a QRS update noise buffer and estimate.
                        // Store the peak for possible search back.
                    else {
                        //memmove(&noise[1],noise,MEMMOVELEN) ;
                        for (int i = MEMMOVECT; i > 0; i--) {
                            noise[i] = noise[i - 1];
                        }
                        noise[0] = newPeak;
                        nmean = mean(noise, 8);
                        det_thresh = thresh(qmean, nmean);

                        // Don't include early peaks (which might be T-waves)
                        // in the search back process.  A T-wave can mask
                        // a small following QRS.

                        if ((newPeak > sbpeak) && ((count - WINDOW_WIDTH) >= MS360)) {
                            sbpeak = newPeak;
                            sbloc = count - WINDOW_WIDTH;
                        }
                    }
                }
            }

            /* Test for search back condition.  If a QRS is found in  */
            /* search back update the QRS buffer and det_thresh.      */

            if ((count > sbcount) && (sbpeak > (det_thresh >> 1))) {
                //memmove(&qrsbuf[1],qrsbuf,MEMMOVELEN) ;
                for (int i = MEMMOVECT; i > 0; i--) {
                    qrsbuf[i] = qrsbuf[i - 1];
                }
                qrsbuf[0] = sbpeak;
                qmean = mean(qrsbuf, 8);
                det_thresh = thresh(qmean, nmean);
                //memmove(&rrbuf[1],rrbuf,MEMMOVELEN) ;
                for (int i = MEMMOVECT; i > 0; i--) {
                    rrbuf[i] = rrbuf[i - 1];
                }
                rrbuf[0] = sbloc;
                rrmean = mean(rrbuf, 8);
                sbcount = rrmean + (rrmean >> 1) + WINDOW_WIDTH;
                QrsDelay = count = count - sbloc;
                QrsDelay += FILTER_DELAY;
                sbpeak = 0;
                lastmax = maxder;
                maxder = 0;

                initBlank = initMax = rsetCount = 0;
            }
        }

        // In the background estimate threshold to replace adaptive threshold
        // if eight seconds elapses without a QRS detection.

        if (qpkcnt == 8) {
            if (++initBlank == MS1000) {
                initBlank = 0;
                rsetBuff[rsetCount] = initMax;
                initMax = 0;
                ++rsetCount;

                // Reset threshold if it has been 8 seconds without
                // a detection.

                if (rsetCount == 8) {
                    for (i = 0; i < 8; ++i) {
                        qrsbuf[i] = rsetBuff[i];
                        noise[i] = 0;
                    }
                    qmean = mean(rsetBuff, 8);
                    nmean = 0;
                    rrmean = MS1000;
                    sbcount = MS1500 + MS150;
                    det_thresh = thresh(qmean, nmean);
                    initBlank = initMax = rsetCount = 0;
                }
            }
            if (newPeak > initMax)
                initMax = newPeak;
        }

        return QrsDelay;
    }

    
//    public void processBufferForR(BufferedDaqChannel<int> ekgBuffer, int position, int bufferSize, List<int> intervals) {
//        initQrsDetector();
//
//        int count = ekgBuffer.getSampleCount();
//
//        if (bufferSize < 800) {
//            return;   // can't do anything until buffer has data
//        }
//
//        int prev_i = 0;
//        int threshold = 1;
//        for (int i = 0; i < count; i++) {
//            int datum = ekgBuffer[i];
//            int y = _getValue(datum);
//
//            if (y > threshold) {
//                int delta = i - prev_i;  // new var for debugging
//                intervals.Add( delta );
//                prev_i = i;
//
//                fireBeatDetection(-1, delta, -1);
//
//            }
//        }
//        dump(intervals, "c:/tmp/results-pt.csv");
//    }

	@Override
	public DeviceCapabilities getStaticCapabilities() {
		DeviceCapabilities caps = super.getStaticCapabilities();
		caps.setName("PT");
		return caps;
	}

	@Override
	public void restartDetector() {
		startTime = 0;
		nextBlockTime = 0;
		startTimeInitialized = false;

        qpkcnt = 0;
        qrsbuf = new int[8];
        noise = new int[8];
        rrbuf = new int[8];
        rsetBuff = new int[8];
        rsetCount = 0;
        sbpeak = 0;
        sbcount = MS1500;
        QrsDelay = 0;

        DDBuffer = new int[DER_DELAY];	/* Buffer holding derivative data. */
	}

}