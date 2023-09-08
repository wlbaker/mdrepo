package idea.qrsdet;

import icuInterface.PlatformUtil;
import idea.schema.rp.RpDevice;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.LinkedList;

import lombok.extern.slf4j.Slf4j;

@Slf4j
public class DetectorQrs2 extends AbstractDetector {
    boolean inited = false;
    protected int MS25;
    protected int MS1500;
	private int sampleRate;

	static {
		try {
			PlatformUtil.loadLibrary("qrs2");
			log.info("---qrs2 library loaded.");

		} catch (UnsatisfiedLinkError e) {
			log.error("Unable to load qrs2", e);
		}
	}
	
	@Override
	public RpDevice getConfiguration() {
		// TODO Auto-generated method stub
		return super.getConfiguration();
	}

    public DetectorQrs2( int sampleRate) {
    	setSampleRate( sampleRate );

    	getConfiguration().setName("QRS2");
    }
    
    @Override
	public void setSampleRate( int sampleRate ) {
    	this.sampleRate = sampleRate;
    	
        initQrsDetector();

        double MS_PER_SAMPLE = ((double)1000 / (double)sampleRate);
        MS25 = ((int)(25 / MS_PER_SAMPLE + 0.5));
        MS1500 = ((int)(1500 / MS_PER_SAMPLE));

    }

    @Override
	public int getSampleRate() {
    	return sampleRate;
    }

    private void initDLL() {

    }

    private int _getValue(int datum) {
        if (inited == false) {
            initDLL();
        }

        int bt, bm;
        int delay = Qrs2JNI.addDatum(datum); // BeatDetectAndClassify(datum, out bt, out bm);

        int threshold = 1;
        if (delay > threshold) {
            fireBeatDetection(-1, 0, -1, leadId, 3);
        }

        return delay;
    }


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


    // delegate BeatNotification(int rri, int rel_pos);

    public void initQrsDetector() {

    	Qrs2JNI.ResetBDAC();

        currentMaxR = Integer.MIN_VALUE;

        gv_firstBeat = true;
        reset();
    }

    private void reset() {
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
    

    LinkedList<Integer> gv_ii = new LinkedList<Integer>();  // must go in the init block

	public int getValue(int pending, int datum, Date tStamp) {

		// currTimeStamp = tStamp;
		return getValue(pending, datum);

    }

    @Override
    public int getValue(int pending, int datum) {

		// currTimeStamp = timeStamp;

        int threshold = 1;
        int delay = _getValue( datum );

        last10Pts[last10Index++] = datum;
        last10Index %= 10;

        if (polarity == 0) {
            // determine polarity
        } else if (polarity < 0 ) {
            datum = -datum;
        }
        abs_pos++;

        if (prev_r == Integer.MIN_VALUE) {
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
                int interval = r_pos - last_r_pos;
                if (interval > MS25) {
                    gv_ii.add(r_pos - last_r_pos);

                    long r_timestamp= startTime + (r_pos * 1000L) / sampleRate;
    				{
    						Date dt = new Date(startTime);
    						SimpleDateFormat fmt = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
    						log.debug( "QRS2* start=" + fmt.format(dt) + " rel=" + fmt.format(r_timestamp));
    				}

                    fireRWaveDetection(-relative_rpos, r_pos - last_r_pos, currentMaxR, leadId, 5, r_timestamp);
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

    
    @Override
	public void setInitialTime(long startTime) {
		super.setInitialTime(startTime);
		reset();
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
	}

}