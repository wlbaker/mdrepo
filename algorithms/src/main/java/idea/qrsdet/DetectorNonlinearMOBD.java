package idea.qrsdet;

import java.util.Date;
import java.util.LinkedList;
import java.util.List;

public class DetectorNonlinearMOBD extends AbstractDetector {

	/**
	 *  The major differences between this algorithm and the algorithm 
	 *  implemented in DetectorPanTompkinsModified.java include the following:
	 *  
	 *   1. Only low-pass and high-pass filters applied to the data
	 *   2. Buffer of past three waveform samples used to compute 
	 *      sign-consistent product
	 *   3. Product compared to threshold
	 *   4. Products stored in QRS and noise buffers
	 *   
	 *  This algorithm employs the strengths of the Modified Pan-Tompkins 
	 *  algorithm, including filters and the search-back technique for peaks/thresholds. 
	 */
	
	
    /* Variables duplicated from DetectorPanTompkins.java */
	
    private int sampleRate;	/* Sample rate in Hz. */
    private double MS_PER_SAMPLE;
    private int MS10;
    private int MS25;
    private int MS80;
    private int MS95;
    private int MS100;
    private int MS125;
    private int MS150;
    private int MS195;
    private int MS220;
    private int MS360;
    private int MS1000;
    private int MS1500;
    private int DERIV_LENGTH;
    private int LPBUFFER_LGTH;
    private int HPBUFFER_LGTH;
    private int PRE_BLANK;
    private int MIN_PEAK_AMP;// Prevents detections of peaks smaller than 150 uV.		
    private int WINDOW_WIDTH;	// Moving window integration width.
    // filter delays plus 200 ms blanking delay
    private int FILTER_DELAY;
    private int DER_DELAY;

    private int det_thresh, qpkcnt;
    private int[] qrsbuf;
    private int[] noise;
    private int[] rrbuf;
    private int[] rsetBuff;
    private int rsetCount = 0;
    private int nmean, qmean, rrmean;
    private int count, sbpeak, sbloc, sbcount;
    int maxder, lastmax;
    private int initBlank, initMax;
    private int preBlankCnt, tempPeak;
    private FilterMark filter;
    int fdatum, QrsDelay;
    int i, newPeak;
    private int peakmax, peaktimeSinceMax, peaklastDatum;

    // final static double TH = 0.3125;
    final static double TH = 0.05;//0.3125;

    private int[] DDBuffer;
    private int DDPtr;	/* Buffer holding derivative data. */

    // final static int MEMMOVELEN = 7 * sizeof(int);
    final static int MEMMOVECT = 7;

    /* Variables duplicated from DetectorPanTompkinsModified.java */
    
    // private double CHECK_AMP_THRESHOLD = 0.50;
    private double CHECK_AMP_THRESHOLD = 0.50;
    
    private int polarity;
    double[] lastThreeAmplitutes = new double[3];
    int[] lastThreeIntervals = new int[3]; // the last three intervals	 fourth is temp holder
    int[] last10Pts = new int[10];
    int last10Index = 0;

    int lastThreeIndex = 0;

    int currentMaxR;
    int rrInt;
    int abs_pos;
    int relative_rpos;
    int prev_r = Integer.MIN_VALUE;

    boolean gv_firstBeat;
    private int last_r_pos = 0;
    // private int recentAvg = 0;
    
    
    /* Variables unique to DetectorNonlinearMOBD.java */
    
    int[] last5Diffs = new int[5];
    
    int prod = 0;
    
    
    
	public DetectorNonlinearMOBD(int sr) {
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
        // MIN_PEAK_AMP = 7; // Prevents detections of peaks smaller than 150 uV.
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
        
        for (int i = 0; i < 5; i++)
        	last5Diffs[i] = 0;
        
        prod = 0;
    }
    
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
        temp = dmed;
        temp *= TH;
        dmed = (int)temp;
        thrsh = nmean + dmed;

        /*
        temp = .15 * (qmean);

        final double MIN_THRESHOLD = 0;
        if (temp < MIN_THRESHOLD) { 
        	temp = MIN_THRESHOLD;
        }
        */
        
        thrsh = (int) temp;
        
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

    
    public void initQrsDetector() {

        /* Copy from initQrsDetector() of DetectorPanTompkins.java */
    	
        for (i = 0; i < 8; ++i) {
            noise[i] = 0;	/* Initialize noise buffer */
            rrbuf[i] = MS1000;/* and R-to-R interval buffer. */
        }

        qpkcnt = maxder = lastmax = count = sbpeak = 0;
        initBlank = initMax = preBlankCnt;
        sbcount = MS1500;

        filter.initFilter(); //QRSFilter(0,1) ;	/* initialize filters. */
        Peak(0, 1);
        

        /* Copy from initQrsDetector() of DetectorPanTompkinsModified.java */
        
        currentMaxR = Integer.MIN_VALUE;
        
        gv_firstBeat = true;
        rrInt = 0;
        abs_pos = 0;
        relative_rpos = 0;

        lastThreeIndex = 0;
        polarity = 0;
    }

    /// <summary>
    //main find value
    /// </returns>
    public int _getValue(int datum) {

        int fdatum = 0;
        int QrsDelay = 0;
        int newPeak = 0;
        int aPeak = 0;

        // int prod = 0;
        
        // fdatum = filter.getValue(datum);
        
        /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
         * Only perform low-pass and high-pass filtering
         *!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/  
        
        fdatum = filter.lpfilt(datum, 0);
        fdatum = filter.hpfilt(fdatum, 0);
        
        // fdatum = filter.deriv2(fdatum, 0);
        // fdatum = Math.abs(fdatum);
        // fdatum = filter.mvwint(fdatum, 0);

        for (int i = 0; i < 5 - 1; i++)
        	last5Diffs[i] = last5Diffs[i+1];
        last5Diffs[4] = fdatum - last5Diffs[3];
        
        /* Check for sign consistency */ 
        //if (( last5Diffs[3] < 0 && last5Diffs[4] < 0 )  
        //		||  ( last5Diffs[3] > 0 && last5Diffs[4] > 0  ) ) {
        //if (( last5Diffs[2] < 0 && last5Diffs[3] < 0 && last5Diffs[4] < 0 ) 
        //		||  ( last5Diffs[2] > 0 && last5Diffs[3] > 0 && last5Diffs[3] > 0 )) {
      	//if (( last5Diffs[1] < 0 && last5Diffs[2] < 0 && last5Diffs[3] < 0 && last5Diffs[4] < 0 ) 
        //   		||  ( last5Diffs[1] > 0 && last5Diffs[2] > 0  && last5Diffs[3] > 0 && last5Diffs[4] > 0 )) {
      	//if (( last5Diffs[0] < 0 && last5Diffs[1] < 0 && last5Diffs[2] < 0 && last5Diffs[3] < 0 && last5Diffs[4] < 0 ) 
        //   		||  ( last5Diffs[0] > 0 && last5Diffs[1] > 0 && last5Diffs[2] > 0  && last5Diffs[3] > 0 && last5Diffs[4] > 0)) {
        	
        	if (sampleRate == 375){
        		//prod = ( last5Diffs[3] * last5Diffs[4] );
        		//prod = ( last5Diffs[2] * last5Diffs[3] * last5Diffs[4] );
        		prod = ( last5Diffs[1] * last5Diffs[2] * last5Diffs[3] * last5Diffs[4] );
        		//prod = ( last5Diffs[0] * last5Diffs[1] * last5Diffs[2] * last5Diffs[3] * last5Diffs[4] );
        	}
        	else if (sampleRate == 500){
        		//prod = ( last5Diffs[3] * last5Diffs[4] );
        		prod = ( last5Diffs[2] * last5Diffs[3] * last5Diffs[4] );
        		//prod = ( last5Diffs[1] * last5Diffs[2] * last5Diffs[3] * last5Diffs[4] );
        		//prod = ( last5Diffs[0] * last5Diffs[1] * last5Diffs[2] * last5Diffs[3] * last5Diffs[4] );
        	}
        	else {
        		if (( last5Diffs[2] < 0 && last5Diffs[3] < 0 && last5Diffs[4] < 0 )
            			||  ( last5Diffs[2] > 0 && last5Diffs[3] > 0 && last5Diffs[4] > 0 )) {
            			prod = (last5Diffs[2] * last5Diffs[3] * last5Diffs[4] );
        		}
        		else {
        			prod = 0;
        		}
        	}
        /*}
        else {
        	prod = 0;
        }*/
        
        /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
         * Save products instead of data points 
         *!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/  
        
        // last10Pts[last10Index++] = prod;
        // last10Index %= 10;
        
        /* Wait until normal detector is ready before calling early detections. */

        aPeak = Peak(prod, 0);
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
    
    List<Integer> gv_ii = new LinkedList<Integer>();  // must go in the init block

	public int getValue(int pending, int datum, Date tStamp) {

		return getValue(pending, datum);

    }

    @Override
	public int getValue(int pending, int datum) {

        int threshold = 1;
    	int delay = _getValue(datum);

        if (delay > threshold) {
            fireBeatDetection(-1, 0, -1, leadId, 3);
        }
      
        /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
         * Save products instead of data points 
         *!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/  
        
        datum = prod;
        
        last10Pts[last10Index++] = datum;
        last10Index %= 10;
        
        if (polarity == 0) {
            // determine polarity
        } else if (polarity < 0 ) {
            datum = -datum;
        }
        abs_pos++;

        if (prev_r == Integer.MIN_VALUE ) {
            prev_r = datum;
            last_r_pos = 0;
        }

        //?? int slope = -(datum - prev_r);
        //?? if (slope > currentMaxR) {
        //??    currentMaxR = slope;
        //??    relative_rpos = 0;
        //?? }

        // assume bad amplitude
        if ( !gv_firstBeat && (abs_pos - last_r_pos > 3*MS1500) ) {
            gv_firstBeat = true;  // reset amplitudes
        }


        if (delay > threshold) {	// found a beat
            if (gv_firstBeat) {
                lastThreeAmplitutes[0] = currentMaxR;
                lastThreeAmplitutes[1] = currentMaxR;
                lastThreeAmplitutes[2] = currentMaxR;
                gv_firstBeat = false;
            }

            if ( checkAndUpdateAmp(lastThreeAmplitutes, currentMaxR)) {
                // found a reasonable currentMaxR as defined by the past n R's
                int r_pos = abs_pos - relative_rpos;
                
                
                /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                // Account for additional delay due to product calculation 2/22/2010
                !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
                // r_pos = r_pos - 1;
                
                int interval = r_pos - last_r_pos;
                if (interval > MS25) {

                    gv_ii.add(r_pos - last_r_pos);

                    long r_timestamp= startTime + (r_pos * 1000L) / sampleRate;
                    fireRWaveDetection(-relative_rpos, r_pos - last_r_pos, currentMaxR, leadId, 2, r_timestamp);
                    
                    last_r_pos = r_pos;
                }

            }
            rrInt = 0;
            currentMaxR = Integer.MIN_VALUE;
            relative_rpos = 0;

        } else {
            relative_rpos++;        // maintains a relative offset to the most probable R
            rrInt++;

            // no beat
           //notslope if ( datum > currentMaxR) { // && (counter - indexLastR > 10) ){
           //notslope     // dont start counting until somewhat past last r detection
           //notslope     currentMaxR = datum;
           //notslope     relative_rpos = 0;
           //notslope }

            // no beat
            int slope = -(datum - prev_r);
            if (slope > currentMaxR) {
                currentMaxR = slope;
                // relative_rpos = 0;

                // find point at which max amplitude actually occurred
                int amppos = 0;
                int ampmax = last10Pts[0];
                for (int i = 0; i < 10; i++) {
                    // select max or min depending if this is a local-max or local-min that we have detected
                    boolean comparison = (slope > 0) ? (last10Pts[i] < ampmax) : (last10Pts[i] > ampmax);
                    if (comparison) {
                        amppos = i;
                        ampmax = last10Pts[i];
                    }
                }

                relative_rpos = (last10Index - amppos + 10) % 10;
            }
        }
        
        prev_r = datum;


        return 0;
    }



    public boolean checkAndUpdateAmp(double[] pastAmps, double thisAmp) {
        // test that thisAmp is within some threshold of the past amps
        // if ok add thisAmp and return true
        // if not ok do not add and return false
        double avg = 0.0;
        for (int i = 0; i < pastAmps.length; i++)
            avg += pastAmps[i];
        avg /= pastAmps.length;

        // wlb -- removed high-side check
        if (thisAmp >= (avg - (avg * CHECK_AMP_THRESHOLD))  ) {
        // if (thisAmp >= (avg - (avg * CHECK_AMP_THRESHOLD)) && thisAmp <= (avg + (2 * avg * CHECK_AMP_THRESHOLD))) {
            pastAmps[0] = pastAmps[1]; pastAmps[1] = pastAmps[2]; pastAmps[2] = thisAmp;
            return true;
        }

        return false;
    }

    public boolean inRange(int rrInt) {
        // returns 0 is rrInt is out of range
        // or 1 if rrInt is in range as determined by physiological resonablness
        // MS1250 corresponds to # samples in 1250 milliseconds  use this as a
        // reasonable appox to 50 beats per minute as a low threshold
        // MS360 upper threshold of 180 beats per minute
        //	if ((rrInt <= MS1250) && (rrInt >= MS360))

        // 333 ms is roughly 180 beats per min  1200 is 50 beats per min

        // try not ms, but rather number of samples
        if ((rrInt <= 1200 * sampleRate / 1000) && (rrInt >= 333 * sampleRate / 1000))
            return true;
        return false;
    }

	@Override
	public int getSampleRate() {
		return sampleRate;
	}

	@Override
	public void restartDetector() {
		startTime = 0;
		nextBlockTime = 0;
		startTimeInitialized = false;

		currentMaxR = 0;
		rrInt = 0;
		abs_pos = 0;
		relative_rpos = 0;
		prev_r = Integer.MIN_VALUE;

		last_r_pos = 0;

		currentMaxR = 0;
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
        
        for (int i = 0; i < 5; i++)
        	last5Diffs[i] = 0;
        
        prod = 0;
	}

}
