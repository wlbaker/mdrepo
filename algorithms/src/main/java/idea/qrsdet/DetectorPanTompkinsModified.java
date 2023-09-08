package idea.qrsdet;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

    public class DetectorPanTompkinsModified extends DetectorPanTompkins {

        @Override
		public String toString() {
			return "PTmod" + super.toString();
		}

		private double CHECK_AMP_THRESHOLD = 0.50;

        // public Qrsdet2 detector;
        public long currentFileIndex;
        public long numReplacements;
        public ArrayList<Integer> myRpositions;
        public int currentWindow;
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
        private int recentAvg = 0;


        // delegate BeatNotification(int rri, int rel_pos);

        @Override
		public void initQrsDetector() {
            super.initQrsDetector();

            currentMaxR = Integer.MIN_VALUE;

            gv_firstBeat = true;
            rrInt = 0;
            abs_pos = 0;
            relative_rpos = 0;

            lastThreeIndex = 0;
            polarity = 0;
        }

        /**********************************************************************
            processBufferForR takes a pointer to an circular array of ints with bufferSize
            number of elements.  process all the bufferSize elements starting at position
            Assume the stats array has been initialized and return values in each 
            of the appropriate position of stats
 
         Correcting for missing beat by averageing the previous last three beats
         a missing beat is one that 
        ***********************************************************************/
        

        List<Integer> gv_ii = new LinkedList<Integer>();  // must go in the init block


		public int getValue(int pending, int datum, long tStamp) {

    		return getValue(pending, datum);

        }


        @Override
		public int getValue(int pending, int datum) {

            int threshold = 1;
            int delay = super.getValue(pending, datum );

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

            // if we are spinning our wheels, assume amplitude is screwed up
            if ( !gv_firstBeat && (abs_pos - last_r_pos > 3*MS1500) ) {
                gv_firstBeat = true;  // reset amplitudes
            }

            /*
             * supplement a: avg amplitude filter
             */

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
                    if (sampleRate == 360) r_pos -= MS10;
                    if (sampleRate == 200) r_pos += MS10/2;

                    int interval = r_pos - last_r_pos;
                    if (interval > MS25) {

                        gv_ii.add(r_pos - last_r_pos);

                        long r_timestamp= startTime + (r_pos * 1000L) / sampleRate;
                        fireRWaveDetection(-relative_rpos, r_pos - last_r_pos, currentMaxR, leadId, 0, r_timestamp);
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

        /* function adds missing rrints 
            handles this beat by beat following these rules:
            maintain recent avg of non adjusted beats (3 beats) handles error checking
            if nth beat is normal defined by within 15% of previous beat and recentAvg
                report n-1 beat
            if nth beat is < 15% of  recentAvg         ignore for now testing previous beat
                adjust n+1 beat by nth beat to handle inadvertant beat detection
                move ahead last beat to this spot for the next reporting
            if nth beat is > 15% of previous beat 
                try to find multiplication factor (mf)
                    loop mf++ until recentAvg*mf + 15% > nth beat  means out of range 
                mf--  put in last possible correct range
                if resonable mf
                    report n-1 beat
                    report mf-1 beats (defined as beat n / mf)
                    set beat n ast beat n / mf (for next interval)
                else
                    adjust n+1 beat by nth beat to handle inadvertant beat detection
                    move ahead last beat to this spot for the next reporting
				
                    codes describe what happens to originally inputted data.  they
                    are (o)riginal detected beat, (s)kipped beat, (d)ivided, and (c)ombined beat
        */

        private void addMissingRwaves(List<Integer> data, List<Integer> toReturn2, char[] returnCodes, int count) {
            int toReturnIndex;
            toReturnIndex = 0;
            int index = 0;
            int skipped = 0;
            double threshold = 0.2;  // percent change

            while (index < (count-1) && !inRange(data.get(index))) {
                returnCodes[index] = 'z';
                skipped += data.get(index);
                index++;
            } // while loop to find first inRange r interval	
            lastThreeIndex = 1;
            lastThreeIntervals[0] = data.get(index);
            lastThreeIntervals[1] = data.get(index);
            lastThreeIntervals[2] = data.get(index);
            
            recentAvg = lastThreeIntervals[0];

            if (skipped > 0) {
                toReturn2.add(skipped);
                skipped = 0;
            }

            boolean skipping = false;
            int nextInterval = 0;
            while (index < count) {

                if (skipping) {
                    // ignore recent average, sync up to feasibility again
                    if (inRange(data.get(index))) {
                        // add accumulated skip
                        toReturn2.add(nextInterval);
                        nextInterval = 0;
                    } else {
                        returnCodes[index] = 's';
                        nextInterval += data.get(index);
                        index++;
                        continue;
                    }
                }

                nextInterval += data.get(index);

                if ( !skipping && nextInterval < (recentAvg - (recentAvg * threshold))) {
                    // found a extra beat		
                    returnCodes[index] = 'c';

                } else if ( !skipping && nextInterval > (recentAvg + (recentAvg * threshold))) {
                    // might have found a missing beat
                    int mf = 2;
                    // set limit for mf to prevent the same reported beat over several interprolated beats
                    while (mf < 5 && nextInterval > (recentAvg * mf + recentAvg * threshold)) {
                        mf++;
                    }

                    if (mf < 5) {	 // found a resonably small beat try to resolve the missing beat
                        if ((nextInterval < (recentAvg * mf + recentAvg * threshold)) && (nextInterval > (recentAvg * mf - recentAvg * threshold))) {
                            // found a missing beat with this mf*beat value
                            int tot = 0;
                            returnCodes[index] = 'd';
                            for (int i = 0; i < mf - 1; i++) {

                                int val = nextInterval / mf;  // a simple division discards the remainder
                                tot += val;
                                toReturn2.add( val );

                            }
                            toReturn2.add( nextInterval - tot );  // catch the remaind in the last element
                            nextInterval = 0;

                        } else {
                            // small enough value, but no reasonable mf is found.  add to next beat and try again
                            returnCodes[index] = 'c';
                        }
                    } else {
                        returnCodes[index] = 's';

                        skipping = true;
                    }
                } else {
                    // found a reasonble interval
                    skipping = false;

                    toReturn2.add(nextInterval);
                    returnCodes[index] = 'o';

                    lastThreeIntervals[lastThreeIndex] = data.get(index); // NOT data[index];
                    lastThreeIndex = (lastThreeIndex+1) % 3;

                    recentAvg = 0;
                    for (int j = 0; j < 3; j++) {
                        recentAvg += lastThreeIntervals[j];
                    }
                    recentAvg /= 3;

                    nextInterval = 0;    // change only after it is stored in lastThree
                }

                index++;
            }

            count = toReturnIndex;
        }

        public DetectorPanTompkinsModified() {
        	// invoke default parent constructor
        }
        
        public DetectorPanTompkinsModified(int sampleRate) {
        	super(sampleRate);
        	setSampleRate( sampleRate );
        }
        
        @Override
		public void setSampleRate(int sampleRate) {
        	super.setSampleRate(sampleRate );

            initQrsDetector();
        }

        @Override
    	public void restartDetector() {
    		startTime = 0;
    		nextBlockTime = 0;
    		startTimeInitialized = false;

            currentMaxR = Integer.MIN_VALUE;

            gv_firstBeat = true;
            rrInt = 0;
            abs_pos = 0;
            relative_rpos = 0;

            lastThreeIndex = 0;
            polarity = 0;

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