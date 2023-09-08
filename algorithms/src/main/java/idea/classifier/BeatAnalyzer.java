package idea.classifier;
/**
 * BeatAnalyzer.java
 */



public class BeatAnalyzer {


	public BeatAnalyzer(int sr) {
		setSampleRate( sr );
	}


	// Constant variables

	protected static final int  NORMAL = 1;	/* normal beat */
	protected static final int  PVC = 5;	/* premature ventricular contraction */
	protected static final int  UNKNOWN = 13;	/* unclassifiable beat */


	protected static int sampleRate;	// Sample rate in Hz.
	protected static double MS_PER_SAMPLE;
	protected static int MS10;
	protected static int MS25;
	protected static int MS50;
	protected static int MS80;
	protected static int MS95;
	protected static int MS100;
	protected static int MS125;
	protected static int MS150;
	protected static int MS195;
	protected static int MS220;
	protected static int MS250;
	protected static int MS300;
	protected static int MS360;
	protected static int MS1000;
	protected static int MS1500;
	protected static int DERIV_LENGTH;
	protected static int LPBUFFER_LGTH;
	protected static int HPBUFFER_LGTH;
	protected static int PRE_BLANK;
	protected static int MIN_PEAK_AMP;	// Prevents detections of peaks smaller than 150 uV.		
	protected static int WINDOW_WIDTH;	// Moving window integration width.
	protected static int FILTER_DELAY;  // Filter delays plus 200 ms blanking delay
	protected static int DER_DELAY;


	protected static int   BEAT_SAMPLE_RATE;	// Originally, assumed to be 100 Hz.
	private static double  BEAT_MS_PER_SAMPLE;

	protected static int  BEAT_MS10;
	protected static int  BEAT_MS20;
	protected static int  BEAT_MS40;
	protected static int  BEAT_MS50;
	protected static int  BEAT_MS60;
	protected static int  BEAT_MS70;
	protected static int  BEAT_MS80;
	protected static int  BEAT_MS90;
	protected static int  BEAT_MS100;
	protected static int  BEAT_MS110;
	protected static int  BEAT_MS130;
	protected static int  BEAT_MS140;
	protected static int  BEAT_MS150;
	protected static int  BEAT_MS250;
	protected static int  BEAT_MS280;
	protected static int  BEAT_MS300;
	protected static int  BEAT_MS350;
	protected static int  BEAT_MS400;
	protected static int  BEAT_MS1000;

	protected static int  BEATLGTH;
	protected static int  MAXTYPES = 8;
	protected static int  FIDMARK;


	protected static int ISO_LENGTH1;
	protected static int ISO_LENGTH2;
	protected static int ISO_LIMIT;


	/*****************************************************************************
	BeatAnalyzer contains functions for determining the QRS onset, QRS offset,
  	beat onset, beat offset, polarity, and isoelectric level for a beat.

  	Revisions:
	4/16: Modified to prevent isoStart from being set to less than ISO_LENGTH1-1
   	5/13/2002: Time related constants are tied to BEAT_SAMPLE_RATE in bdac.h.

	 *****************************************************************************/


	public void setSampleRate(int sr) {

		sampleRate = sr;	/* Sample rate in Hz. */
		MS_PER_SAMPLE = ((double)1000 / (double)sampleRate);
		MS10 = ((int)(10 / MS_PER_SAMPLE + 0.5));
		MS25 = ((int)(25 / MS_PER_SAMPLE + 0.5));
		MS50 = ((int)(50 / MS_PER_SAMPLE + 0.5));
		MS80 = ((int)(80 / MS_PER_SAMPLE + 0.5));
		MS95 = ((int)(95 / MS_PER_SAMPLE + 0.5));
		MS100 = ((int)(100 / MS_PER_SAMPLE + 0.5));
		MS125 = ((int)(125 / MS_PER_SAMPLE + 0.5));
		MS150 = ((int)(150 / MS_PER_SAMPLE + 0.5));
		MS195 = ((int)(195 / MS_PER_SAMPLE + 0.5));
		MS220 = ((int)(220 / MS_PER_SAMPLE + 0.5));
		MS250 = ((int)(250 / MS_PER_SAMPLE + 0.5));
		MS250 = ((int)(300 / MS_PER_SAMPLE + 0.5));
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


		BEAT_SAMPLE_RATE = sr;
		BEAT_MS_PER_SAMPLE = ( (double) 1000/ (double) BEAT_SAMPLE_RATE);

		BEAT_MS10 = ((int) (10/BEAT_MS_PER_SAMPLE + 0.5));
		BEAT_MS20 = ((int) (20/BEAT_MS_PER_SAMPLE + 0.5));
		BEAT_MS40 = ((int) (40/BEAT_MS_PER_SAMPLE + 0.5));
		BEAT_MS50 = ((int) (50/BEAT_MS_PER_SAMPLE + 0.5));
		BEAT_MS60 = ((int) (60/BEAT_MS_PER_SAMPLE + 0.5));
		BEAT_MS70 = ((int) (70/BEAT_MS_PER_SAMPLE + 0.5));
		BEAT_MS80 = ((int) (80/BEAT_MS_PER_SAMPLE + 0.5));
		BEAT_MS90 = ((int) (90/BEAT_MS_PER_SAMPLE + 0.5));
		BEAT_MS100 = ((int) (100/BEAT_MS_PER_SAMPLE + 0.5));
		BEAT_MS110 = ((int) (110/BEAT_MS_PER_SAMPLE + 0.5));
		BEAT_MS130 = ((int) (130/BEAT_MS_PER_SAMPLE + 0.5));
		BEAT_MS140 = ((int) (140/BEAT_MS_PER_SAMPLE + 0.5));
		BEAT_MS150 = ((int) (150/BEAT_MS_PER_SAMPLE + 0.5));
		BEAT_MS250 = ((int) (250/BEAT_MS_PER_SAMPLE + 0.5));
		BEAT_MS280 = ((int) (280/BEAT_MS_PER_SAMPLE + 0.5));
		BEAT_MS300 = ((int) (300/BEAT_MS_PER_SAMPLE + 0.5));
		BEAT_MS350 = ((int) (350/BEAT_MS_PER_SAMPLE + 0.5));
		BEAT_MS400 = ((int) (400/BEAT_MS_PER_SAMPLE + 0.5));
		BEAT_MS1000 = BEAT_SAMPLE_RATE;

		BEATLGTH = BEAT_MS1000;
		MAXTYPES = 8;
		FIDMARK = BEAT_MS400;


		ISO_LENGTH1 = BEAT_MS50;
		ISO_LENGTH2 = BEAT_MS80;
		ISO_LIMIT = 20;


		INF_CHK_N = BEAT_MS40;

		NB_LENGTH	= MS1500;
		NS_LENGTH	= MS50;

		NoiseBuffer = new int[NB_LENGTH];
		NBPtr = 0 ;
	}

	public int getSampleRate() {
		return MS1000;
	}


	/****************************************************************
	IsoCheck determines whether the amplitudes of a run
	of data fall within a sufficiently small amplitude that
	the run can be considered isoelectric.
	 *****************************************************************/

	public int IsoCheck(int[] data, int idx, int isoLength)
	{
		int i, max, min ;

		for(i = idx+1, max=min = data[idx]; i < isoLength; ++i)
		{
			if(data[i] > max)
				max = data[i] ;
			else if(data[i] < min)
				min = data[i] ;
		}

		if(max - min < ISO_LIMIT)
			return(1) ;
		return(0) ;
	}

	/**********************************************************************
	AnalyzeBeat takes a beat buffer as input and returns (via pointers)
	estimates of the QRS onset, QRS offset, polarity, isoelectric level
	beat beginning (P-wave onset), and beat ending (T-wave offset).
	Analyze Beat assumes that the beat has been sampled at 100 Hz, is
	BEATLGTH long, and has an R-wave location of roughly FIDMARK.

	Note that beatBegin is the number of samples before FIDMARK that
	the beat begins and beatEnd is the number of samples after the
	FIDMARK that the beat ends.
	 ************************************************************************/

	protected static int INF_CHK_N;

	protected static int onset;
	protected static int offset;
	protected static int isoLevel;
	protected static int beatBegin;
	protected static int beatEnd;
	protected static int amp;

	void AnalyzeBeat(int[] beat)
	{
		int maxSlope = 0, maxSlopeI, minSlope = 0, minSlopeI  ;
		int maxV, minV ;
		int isoStart, isoEnd ;
		int slope, i ;

		// Search back from the fiducial mark to find the isoelectric
		// region preceeding the QRS complex.

		for(i = FIDMARK-ISO_LENGTH2; (i > 0) && (IsoCheck(beat, i, ISO_LENGTH2) == 0); --i) ;

		// If the first search didn't turn up any isoelectric region, look for
		// a shorter isoelectric region.

		if(i == 0)
		{
			for(i = FIDMARK-ISO_LENGTH1; (i > 0) && (IsoCheck(beat, i, ISO_LENGTH1) == 0); --i) ;
			isoStart = i + (ISO_LENGTH1 - 1) ;
		}
		else isoStart = i + (ISO_LENGTH2 - 1) ;

		// Search forward from the R-wave to find an isoelectric region following
		// the QRS complex.

		for(i = FIDMARK; (i < BEATLGTH) && (IsoCheck(beat, i, ISO_LENGTH1) == 0); ++i) ;
		isoEnd = i ;

		// Find the maximum and minimum slopes on the
		// QRS complex.

		i = FIDMARK-BEAT_MS150 ;
		maxSlope = maxSlope = beat[i] - beat[i-1] ;
		maxSlopeI = minSlopeI = i ;

		for(; i < FIDMARK+BEAT_MS150; ++i)
		{
			slope = beat[i] - beat[i-1] ;
			if(slope > maxSlope)
			{
				maxSlope = slope ;
				maxSlopeI = i ;
			}
			else if(slope < minSlope)
			{
				minSlope = slope ;
				minSlopeI = i ;
			}
		}

		// Use the smallest of max or min slope for search parameters.

		if(maxSlope > -minSlope)
			maxSlope = -minSlope ;
		else minSlope = -maxSlope ;

		if(maxSlopeI < minSlopeI)
		{

			// Search back from the maximum slope point for the QRS onset.

			for(i = maxSlopeI;
			(i > 0) && ((beat[i]-beat[i-1]) > (maxSlope >> 2)); --i) ;
			onset = i-1 ;

			// Check to see if this was just a brief inflection.

			for(; (i > onset-INF_CHK_N) && ((beat[i]-beat[i-1]) <= (maxSlope >>2)); --i) ;
			if(i > onset-INF_CHK_N)
			{
				for(;(i > 0) && ((beat[i]-beat[i-1]) > (maxSlope >> 2)); --i) ;
				onset = i-1 ;
			}
			i = onset+1 ;

			// Check to see if a large negative slope follows an inflection.
			// If so, extend the onset a little more.

			for(;(i > onset-INF_CHK_N) && ((beat[i-1]-beat[i]) < (maxSlope>>2)); --i);
			if(i > onset-INF_CHK_N)
			{
				for(; (i > 0) && ((beat[i-1]-beat[i]) > (maxSlope>>2)); --i) ;
				onset = i-1 ;
			}

			// Search forward from minimum slope point for QRS offset.

			for(i = minSlopeI;
			(i < BEATLGTH) && ((beat[i] - beat[i-1]) < (minSlope >>2)); ++i);
			offset = i ;

			// Make sure this wasn't just an inflection.

			for(; (i < offset+INF_CHK_N) && ((beat[i]-beat[i-1]) >= (minSlope>>2)); ++i) ;
			if(i < offset+INF_CHK_N)
			{
				for(;(i < BEATLGTH) && ((beat[i]-beat[i-1]) < (minSlope >>2)); ++i) ;
				offset = i ;
			}
			i = offset ;

			// Check to see if there is a significant upslope following
			// the end of the down slope.

			for(;(i < offset+BEAT_MS40) && ((beat[i-1]-beat[i]) > (minSlope>>2)); ++i);
			if(i < offset+BEAT_MS40)
			{
				for(; (i < BEATLGTH) && ((beat[i-1]-beat[i]) < (minSlope>>2)); ++i) ;
				offset = i ;

				// One more search motivated by PVC shape in 123.

				for(; (i < offset+BEAT_MS60) && (beat[i]-beat[i-1] > (minSlope>>2)); ++i) ;
				if(i < offset + BEAT_MS60)
				{
					for(;(i < BEATLGTH) && (beat[i]-beat[i-1] < (minSlope>>2)); ++i) ;
					offset = i ;
				}
			}
		}

		else
		{

			// Search back from the minimum slope point for the QRS onset.

			for(i = minSlopeI;
			(i > 0) && ((beat[i]-beat[i-1]) < (minSlope >> 2)); --i) ;
			onset = i-1 ;

			// Check to see if this was just a brief inflection.

			for(; (i > onset-INF_CHK_N) && ((beat[i]-beat[i-1]) >= (minSlope>>2)); --i) ;
			if(i > onset-INF_CHK_N)
			{
				for(; (i > 0) && ((beat[i]-beat[i-1]) < (minSlope>>2));--i) ;
				onset = i-1 ;
			}
			i = onset+1 ;

			// Check for significant positive slope after a turning point.

			for(;(i > onset-INF_CHK_N) && ((beat[i-1]-beat[i]) > (minSlope>>2)); --i);
			if(i > onset-INF_CHK_N)
			{
				for(; (i > 0) && ((beat[i-1]-beat[i]) < (minSlope>>2)); --i) ;
				onset = i-1 ;
			}

			// Search forward from maximum slope point for QRS offset.

			for(i = maxSlopeI;
			(i < BEATLGTH) && ((beat[i] - beat[i-1]) > (maxSlope >>2)); ++i) ;
			offset = i ;

			// Check to see if this was just a brief inflection.

			for(; (i < offset+INF_CHK_N) && ((beat[i] - beat[i-1]) <= (maxSlope >> 2)); ++i) ;
			if(i < offset+INF_CHK_N)
			{
				for(;(i < BEATLGTH) && ((beat[i] - beat[i-1]) > (maxSlope >>2)); ++i) ;
				offset = i ;
			}
			i = offset ;

			// Check to see if there is a significant downslope following
			// the end of the up slope.

			for(;(i < offset+BEAT_MS40) && ((beat[i-1]-beat[i]) < (maxSlope>>2)); ++i);
			if(i < offset+BEAT_MS40)
			{
				for(; (i < BEATLGTH) && ((beat[i-1]-beat[i]) > (maxSlope>>2)); ++i) ;
				offset = i ;
			}
		}

		// If the estimate of the beginning of the isoelectric level was
		// at the beginning of the beat, use the slope based QRS onset point
		// as the iso electric point.

		if((isoStart == ISO_LENGTH1-1)&& (onset > isoStart)) //  4/19 
			isoStart = onset ;

		// Otherwise, if the isoelectric start and the slope based points
		// are close, use the isoelectric start point.

		else if(onset-isoStart < BEAT_MS50)
			onset = isoStart ;

		// If the isoelectric end and the slope based QRS offset are close
		// use the isoelectic based point.

		if(isoEnd - offset < BEAT_MS50)
			offset = isoEnd ;

		isoLevel = beat[isoStart] ;


		// Find the maximum and minimum values in the QRS.

		for(i = onset, maxV = minV = beat[onset]; i < offset; ++i)
			if(beat[i] > maxV)
				maxV = beat[i] ;
			else if(beat[i] < minV)
				minV = beat[i] ;

		// If the offset is significantly below the onset and the offset is
		// on a negative slope, add the next up slope to the width.

		if((beat[onset]-beat[offset] > ((maxV-minV)>>2)+((maxV-minV)>>3)))
		{

			// Find the maximum slope between the finish and the end of the buffer.

			for(i = maxSlopeI = offset, maxSlope = beat[offset] - beat[offset-1];
			(i < offset+BEAT_MS100) && (i < BEATLGTH); ++i)
			{
				slope = beat[i]-beat[i-1] ;
				if(slope > maxSlope)
				{
					maxSlope = slope ;
					maxSlopeI = i ;
				}
			}

			// Find the new offset.

			if(maxSlope > 0)
			{
				for(i = maxSlopeI;
				(i < BEATLGTH) && (beat[i]-beat[i-1] > (maxSlope>>1)); ++i) ;
				offset = i ;
			}
		}

		// Determine beginning and ending of the beat.
		// Search for an isoelectric region that precedes the R-wave.
		// by at least 250 ms.

		for(i = FIDMARK-BEAT_MS250;
		(i >= BEAT_MS80) && (IsoCheck(beat, i-BEAT_MS80, BEAT_MS80) == 0); --i) ;
		beatBegin = i ;

		// If there was an isoelectric section at 250 ms before the
		// R-wave, search forward for the isoelectric region closest
		// to the R-wave.  But leave at least 50 ms between beat begin
		// and onset, or else normal beat onset is within PVC QRS complexes.
		// that screws up noise estimation.

		if(beatBegin == FIDMARK-BEAT_MS250)
		{
			for(; (i < onset-BEAT_MS50) &&
			(IsoCheck(beat, i-BEAT_MS80, BEAT_MS80) == 1); ++i) ;
			beatBegin = i-1 ;
		}

		// Rev 1.1
		else if(beatBegin == BEAT_MS80 - 1)
		{
			for(; (i < onset) && (IsoCheck(beat, i-BEAT_MS80, BEAT_MS80) == 0); ++i);
			if(i < onset)
			{
				for(; (i < onset) && (IsoCheck(beat, i-BEAT_MS80, BEAT_MS80) == 1); ++i) ;
				if(i < onset)
					beatBegin = i-1 ;
			}
		}

		// Search for the end of the beat as the first isoelectric
		// segment that follows the beat by at least 300 ms.

		for(i = FIDMARK+BEAT_MS300;
		(i < BEATLGTH) && (IsoCheck(beat, i, BEAT_MS80) == 0); ++i) ;
		beatEnd = i ;

		// If the signal was isoelectric at 300 ms. search backwards.
		/*	if(beatEnd == FIDMARK+30)
		{
		for(; (i > offset) && (IsoCheck(beat, i, 8) != 0); --i) ;
		 beatEnd = i ;
		}
		 */
		// Calculate beat amplitude.

		maxV=minV=beat[onset] ;
		for(i = onset; i < offset; ++i)
			if(beat[i] > maxV)
				maxV = beat[i] ;
			else if(beat[i] < minV)
				minV = beat[i] ;
		amp = maxV-minV ;

	}


	protected static int  NB_LENGTH	= MS1500;
	protected static int  NS_LENGTH	= MS50;

	protected static int[] NoiseBuffer;
	protected static int NBPtr;
	protected static int NoiseEstimate;

	/************************************************************************
		GetNoiseEstimate() allows external access the present noise estimate.
		this function is only used for debugging.
	 *************************************************************************/

	int GetNoiseEstimate()
	{
		return(NoiseEstimate) ;
	}

	/***********************************************************************
		NoiseCheck() must be called for every sample of data.  The data is
		stored in a circular buffer to facilitate noise analysis.  When a
		beat is detected NoiseCheck() is passed the sample delay since the
		R-wave of the beat occurred (delay), the RR interval between this
		beat and the next most recent beat, the estimated offset from the
		R-wave to the beginning of the beat (beatBegin), and the estimated
		offset from the R-wave to the end of the beat.

		NoiseCheck() estimates the noise in the beat by the maximum and
		minimum signal values in either a window from the end of the
		previous beat to the beginning of the present beat, or a 250 ms
		window preceding the present beat, which ever is shorter.

		NoiseCheck() returns ratio of the signal variation in the window
		between beats to the length of the window between the beats.  If
		the heart rate is too high and the beat durations are too long,
		NoiseCheck() returns 0.

	 ***********************************************************************/

	int NoiseCheck(int datum, int delay, int RR)
	{
		int ptr, i;
		int ncStart, ncEnd, ncMax, ncMin ;
		double noiseIndex ;

		NoiseBuffer[NBPtr] = datum ;
		if(++NBPtr == NB_LENGTH)
			NBPtr = 0 ;

		// Check for noise in region that is 300 ms following
		// last R-wave and 250 ms preceding present R-wave.

		ncStart = delay+RR-beatEnd ;	// Calculate offset to end of previous beat.
		ncEnd = delay+beatBegin ;		// Calculate offset to beginning of this beat.
		if(ncStart > ncEnd + MS250)
			ncStart = ncEnd + MS250 ;


		// Estimate noise if delay indicates a beat has been detected,
		// the delay is not to long for the data buffer, and there is
		// some space between the end of the last beat and the beginning
		// of this beat.

		if((delay != 0) && (ncStart < NB_LENGTH) && (ncStart > ncEnd))
		{

			ptr = NBPtr - ncStart ;	// Find index to end of last beat in
			if(ptr < 0)					// the circular buffer.
				ptr += NB_LENGTH ;

			// Find the maximum and minimum values in the
			// isoelectric region between beats.

			ncMax = ncMin = NoiseBuffer[ptr] ;
			for(i = 0; i < ncStart-ncEnd; ++i)
			{
				if(NoiseBuffer[ptr] > ncMax)
					ncMax = NoiseBuffer[ptr] ;
				else if(NoiseBuffer[ptr] < ncMin)
					ncMin = NoiseBuffer[ptr] ;
				if(++ptr == NB_LENGTH)
					ptr = 0 ;
			}

			// The noise index is the ratio of the signal variation
			// over the isoelectric window length, scaled by 10.

			noiseIndex = (ncMax-ncMin) ;
			noiseIndex /= (ncStart-ncEnd) ;
			NoiseEstimate = (int) (noiseIndex * 10);
		}
		else
			NoiseEstimate = 0 ;
		return(NoiseEstimate) ;
	}



}