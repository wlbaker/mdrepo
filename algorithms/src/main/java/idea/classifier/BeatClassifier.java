package idea.classifier;
/**
 * BeatClassifier.java
 */


public class BeatClassifier extends RhythmChecker {


	public BeatClassifier(int sr) {
		super(sr);
		initializeConstants();
	}


	/** 
	 * This class provides the functions for classifying beats.
	 *  
	 * @see match, rythmchk, classify, rythmchk, analbeat, postclas
	 * 
	 * 
	 * Width constants tied to BEAT_SAMPLE_RATE in bdac
	 * 
	 * Arrays added to track the classifications and RR intervals for the
	 * most recent 8 beats, allowing GetRunCount to become a local function.
	 * RR intervals and classifications are now passed to PostClassify.
	 * 
	 * Determination of a regular dominant rhythm depends upon the number of RR 
	 * intervals classified as UNKNOWN in the last DM_BUFFER_LENGTH beats (180).
	 * More than 60 UNKNOWN intervals equals an irregular rhythm.
	 **/


	// Detection rule parameters

	private static double  MATCH_LIMIT;
	private static double  MATCH_WITH_AMP_LIMIT;
	private static double  PVC_MATCH_WITH_AMP_LIMIT;
	private static double  BL_SHIFT_LIMIT;
	private static double  NEW_TYPE_NOISE_THRESHOLD;
	private static double  NEW_TYPE_HF_NOISE_LIMIT;

	private static double  MATCH_NOISE_THRESHOLD;


	// TempClass classification rule parameters

	private static double  R2_DI_THRESHOLD;
	private static double  R3_WIDTH_THRESHOLD;
	private static double  R7_DI_THRESHOLD;
	private static double  R8_DI_THRESHOLD;
	private static double  R9_DI_THRESHOLD;
	private static double  R10_BC_LIM;
	private static double  R10_DI_THRESHOLD;
	private static double  R11_MIN_WIDTH;
	private static double  R11_WIDTH_BREAK;
	private static double  R11_WIDTH_DIFF1;
	private static double  R11_WIDTH_DIFF2;
	private static double  R11_HF_THRESHOLD;
	private static double  R11_MA_THRESHOLD;
	private static double  R11_BC_LIM;
	private static double  R15_DI_THRESHOLD;
	private static double  R15_WIDTH_THRESHOLD;
	private static double  R16_WIDTH_THRESHOLD;
	private static double  R17_WIDTH_DELTA;
	private static double  R18_DI_THRESHOLD;
	private static double  R19_HF_THRESHOLD;


	/*
	private static int  NOTQRS = 0;	// not-QRS (not a getann/putann code) 
	private static int  NORMAL = 1;	// normal beat 
	private static int  LBBB = 2;		// left bundle branch block beat 
	private static int  RBBB = 3;		// right bundle branch block beat 
	private static int  ABERR = 4;	// aberrated atrial premature beat 
	private static int  PVC = 5;		// premature ventricular contraction 
	private static int  FUSION = 6;	// fusion of ventricular and normal beat 
	private static int  NPC = 7;		// nodal (junctional) premature beat 
	private static int  APC = 8;		// atrial premature contraction 
	private static int  SVPB = 9;		// premature or ectopic supraventricular beat 
	private static int  VESC = 10;	// ventricular escape beat 
	private static int  NESC = 11;	// nodal (junctional) escape beat 
	private static int  PACE = 12;	// paced beat 
	private static int  UNKNOWN = 13;	// unclassifiable beat 
	private static int  NOISE = 14;	// signal quality change 
	private static int  ARFCT = 16;	// isolated QRS-like artifact 
	private static int  STCH = 18;	// ST change 
	private static int  TCH = 19;		// T-wave change 
	private static int  SYSTOLE = 20;	// systole 
	private static int  DIASTOLE = 21;// diastole 
	private static int  NOTE = 22;	// comment annotation 
	private static int  MEASURE = 23;	// measurement annotation 
	private static int  BBB = 25;		// left or right bundle branch block 
	private static int  PACESP = 26;	// non-conducted pacer spike 
	private static int  RHYTHM = 28;	// rhythm change 
	private static int  LEARN = 30;	// learning 
	private static int  FLWAV = 31;	// ventricular flutter wave 
	private static int  VFON = 32;	// start of ventricular flutter/fibrillation 
	private static int  VFOFF = 33;	// end of ventricular flutter/fibrillation 
	private static int  AESC = 34;	// atrial escape beat 
	private static int  SVESC = 35;	// supraventricular escape beat 
	private static int  NAPC = 37;	// non-conducted P-wave (blocked APB) 
	private static int  PFUS = 38;	// fusion of paced and normal beat 
	private static int  PQ = 39;		// PQ junction (beginning of QRS) 
	private static int  JPT = 40;		// J point (end of QRS) 
	private static int  RONT = 41;	// R-on-T premature ventricular contraction 

	// ... annotation codes between RONT+1 and ACMAX inclusive are user-defined

	private static int 	ACMAX = 49;	// value of largest valid annot code (must be < 50) 
	 */

	// private static double matchIndex, mi2;
	// private static int matchType, shiftAdj;


	/***************************************************************************
	 *  Classify() takes a beat buffer, the previous R-R interval, and the present
	 *  noise level estimate and returns a beat classification of NORMAL, PVC, or
	 *  UNKNOWN.  The UNKNOWN classification is only returned.  The beat template
	 *  type that the beat has been matched to is returned through the pointer
	 *  *beatMatch for debugging display.  Passing anything other than 0 in init
	 *  resets the static variables used by Classify.
	 ****************************************************************************/

	public void initializeConstants(){
		MATCH_LIMIT = 1.3;					// Threshold for template matching without amplitude sensitivity.
		MATCH_WITH_AMP_LIMIT = 2.5;			// Threshold for matching index that is amplitude sensitive.
		PVC_MATCH_WITH_AMP_LIMIT = 0.9; 	// Amplitude sensitive limit for matching premature beats.
		BL_SHIFT_LIMIT = 100;				// Threshold for assuming a baseline shift.
		NEW_TYPE_NOISE_THRESHOLD = 18; 		// Above this noise level, do not create new beat types.
		NEW_TYPE_HF_NOISE_LIMIT = 75; 		// Above this noise level, do not create new beat types.

		MATCH_NOISE_THRESHOLD = 0.7;		// Match threshold below which noise indications are ignored.

		R2_DI_THRESHOLD = 1.0;				// Rule 2 dominant similarity index threshold
		R3_WIDTH_THRESHOLD = BEAT_MS90;		// Rule 3 width threshold.
		R7_DI_THRESHOLD = 1.2;				// Rule 7 dominant similarity index threshold
		R8_DI_THRESHOLD = 1.5;				// Rule 8 dominant similarity index threshold
		R9_DI_THRESHOLD = 2.0;				// Rule 9 dominant similarity index threshold
		R10_BC_LIM = 3;						// Rule 10 beat count limit.
		R10_DI_THRESHOLD = 2.5;				// Rule 10 dominant similarity index threshold
		R11_MIN_WIDTH = BEAT_MS110;			// Rule 11 minimum width threshold.
		R11_WIDTH_BREAK = BEAT_MS140;		// Rule 11 width break.
		R11_WIDTH_DIFF1 = BEAT_MS40;		// Rule 11 width difference threshold 1
		R11_WIDTH_DIFF2 = BEAT_MS60;		// Rule 11 width difference threshold 2
		R11_HF_THRESHOLD = 45;				// Rule 11 high frequency noise threshold.
		R11_MA_THRESHOLD = 14;				// Rule 11 motion artifact threshold.
		R11_BC_LIM = 1;						// Rule 11 beat count limit.
		R15_DI_THRESHOLD = 3.5;				// Rule 15 dominant similarity index threshold
		R15_WIDTH_THRESHOLD = BEAT_MS100;	// Rule 15 width threshold.
		R16_WIDTH_THRESHOLD = BEAT_MS100;	// Rule 16 width threshold.
		R17_WIDTH_DELTA = BEAT_MS20;		// Rule 17 difference threshold.
		R18_DI_THRESHOLD = 1.5;				// Rule 18 dominant similarity index threshold.
		R19_HF_THRESHOLD = 75;				// Rule 19 high frequency noise threshold.

		ECG_BUFFER_LENGTH = 1000;			// Accommodate the maximum detection delay.
		BEAT_QUE_LENGTH = 10;				// Length of queue for beats awaiting classification.


		//Global variables

		ECGBuffer = new int[ECG_BUFFER_LENGTH];
		ECGBufferIndex = 0 ;  // Circular data buffer.
		BeatBuffer = new int[BEATLGTH];
		BeatQue = new int[BEAT_QUE_LENGTH];
		BeatQueCount = 0 ;  // Buffer of detection delays.
		RRCount = 0 ;
		InitBeatFlag = 1 ;

		tempBeat = new int[(sampleRate/BEAT_SAMPLE_RATE)*BEATLGTH];

		ResetBDAC();
	}


	private static int  ECG_BUFFER_LENGTH;
	private static int  BEAT_QUE_LENGTH;


	//Global variables

	int[] ECGBuffer;
	int ECGBufferIndex;
	int[] BeatBuffer;
	int[] BeatQue;
	int BeatQueCount;
	int RRCount;
	int InitBeatFlag;

	int[] tempBeat;





	/******************************************************************************
	ResetBDAC() resets static variables required for beat detection and
	classification.
	 *******************************************************************************/

	void ResetBDAC()
	{
		int dummy;
		RRCount = 0 ;
		Classify(0,0,1);
		InitBeatFlag = 1 ;
		BeatQueCount = 0 ;	// Flush the beat queue.
	}


	/*****************************************************************************
	Syntax:
	int BeatDetectAndClassify(int ecgSample, int *beatType, *beatMatch) ;

	Description:
	BeatDetectAndClassify() implements a beat detector and classifier.
	ECG samples are passed into BeatDetectAndClassify() one sample at a
	time.  BeatDetectAndClassify has been designed for a sample rate of
	200 Hz.  When a beat has been detected and classified the detection
	delay is returned and the beat classification is returned through the
	pointer *beatType.  For use in debugging, the number of the template
	that the beat was matched to is returned in via *beatMatch.

	Returns
	BeatDetectAndClassify() returns 0 if no new beat has been detected and
	classified.  If a beat has been classified, BeatDetectAndClassify returns
	the number of samples since the approximate location of the R-wave.

	 ****************************************************************************/

	private static int beatType;

	int BeatDetectAndClassify(int ecgSample, int detectDelay)
	{
		int rr = 0, i, j ;
		int domType ;

		// Store new sample in the circular buffer.

		ECGBuffer[ECGBufferIndex] = ecgSample ;
		if(++ECGBufferIndex == ECG_BUFFER_LENGTH)
			ECGBufferIndex = 0 ;

		// Increment RRInterval count.

		++RRCount ;

		// Increment detection delays for any beats in the que.

		for(i = 0; i < BeatQueCount; ++i)
			++BeatQue[i] ;

		// Run the sample through the QRS detector.

		// detectDelay = QRSDet(ecgSample,0) ;
		if(detectDelay != 0)
		{
			BeatQue[BeatQueCount] = detectDelay ;
			++BeatQueCount ;
		}

		// Return if no beat is ready for classification.

		if((BeatQue[0] < (BEATLGTH-FIDMARK)*(sampleRate/BEAT_SAMPLE_RATE))
				|| (BeatQueCount == 0))
		{
			NoiseCheck(ecgSample,0,rr) ;	// Update noise check buffer
			return 0 ;
		}

		// Otherwise classify the beat at the head of the que.

		rr = RRCount - BeatQue[0] ;	// Calculate the R-to-R interval
		detectDelay = RRCount = BeatQue[0] ;

		// Estimate low frequency noise in the beat.
		// Might want to move this into classify().

		domType = GetDominantType() ;
		if(domType == -1)
		{
			beatBegin = MS250 ;
			beatEnd = MS300;
		}
		else
		{
			beatBegin = (sampleRate/BEAT_SAMPLE_RATE)*(FIDMARK-GetBeatBegin(domType)) ;
			beatEnd = (sampleRate/BEAT_SAMPLE_RATE)*(GetBeatEnd(domType)-FIDMARK) ;
		}
		NoiseEstimate = NoiseCheck(ecgSample,detectDelay,rr) ;

		// Copy the beat from the circular buffer to the beat buffer
		// and reduce the sample rate by averageing pairs of data
		// points.

		j = ECGBufferIndex - detectDelay - (sampleRate/BEAT_SAMPLE_RATE)*FIDMARK ;
		if(j < 0) j += ECG_BUFFER_LENGTH ;

		for(i = 0; i < (sampleRate/BEAT_SAMPLE_RATE)*BEATLGTH; ++i)
		{
			tempBeat[i] = ECGBuffer[j] ;
			if(++j == ECG_BUFFER_LENGTH)
				j = 0 ;
		}

		DownSampleBeat() ;

		// Update the QUE.

		for(i = 0; i < BeatQueCount-1; ++i)
			BeatQue[i] = BeatQue[i+1] ;
		--BeatQueCount ;


		// Skip the first beat.

		if(InitBeatFlag != 0)
		{
			InitBeatFlag = 0 ;
			beatType = 13 ;
			beatMatch = 0 ;
			fidAdj = 0 ;
		}

		// Classify all other beats.

		else
		{
			beatType = Classify(rr,NoiseEstimate,0) ;
			fidAdj *= sampleRate/BEAT_SAMPLE_RATE ;
		}

		// Ignore detection if the classifier decides that this
		// was the trailing edge of a PVC.

		if(beatType == 100)
		{
			RRCount += rr ;
			return(0) ;
		}

		// Limit the fiducial mark adjustment in case of problems with
		// beat onset and offset estimation.

		if(fidAdj > MS80)
			fidAdj = MS80 ;
		else if(fidAdj < -MS80)
			fidAdj = -MS80 ;

		return(detectDelay-fidAdj) ;
	}




	void DownSampleBeat()
	{
		int i ;

		for(i = 0; i < BEATLGTH; ++i)
			BeatBuffer[i] = (tempBeat[i<<1]+tempBeat[(i<<1)+1])>>1 ;
	}


	static int beatMatch;
	static int fidAdj;
	static int morphType;

	static int runCount = 0 ;
	static int lastIsoLevel=0, lastRhythmClass = UNKNOWN, lastBeatWasNew = 0 ;

	/***************************************************************************
	 *  Classify() takes a beat buffer, the previous rr interval, and the present
	 *  noise level estimate and returns a beat classification of NORMAL, PVC, or
	 *  UNKNOWN.  The UNKNOWN classification is only returned.  The beat template
	 *  type that the beat has been matched to is returned through the pointer
	 *  *beatMatch for debugging display.  Passing anything other than 0 in init
	 *  resets the static variables used by Classify.
	 ****************************************************************************/

	int Classify(int rr, int noiseLevel, int init)
	{
		int rhythmClass, beatClass, i, beatWidth, blShift ;
		double domIndex ;
		int domType, domWidth;
		int tempClass ;
		int hfNoise ;

		// If initializing...

		if(init != 0)
		{
			ResetRhythmChk() ;
			ResetMatch() ;
			ResetPostClassify() ;
			runCount = 0 ;
			DomMonitor(0, 0, 0, 0, 1) ;
			return(0) ;
		}

		hfNoise = HFNoiseCheck(BeatBuffer) ;	// Check for muscle noise.
		rhythmClass = RhythmChk(rr) ;			// Check the rhythm.

		// Estimate beat features.

		AnalyzeBeat(BeatBuffer) ;

		blShift = Math.abs(lastIsoLevel-isoLevel) ;
		lastIsoLevel = isoLevel ;

		// Make isoelectric level 0.

		for(i = 0; i < BEATLGTH; ++i)
			BeatBuffer[i] -= isoLevel ;

		// If there was a significant baseline shift since
		// the last beat and the last beat was a new type,
		// delete the new type because it might have resulted
		// from a baseline shift.

		if( (blShift > BL_SHIFT_LIMIT)
				&& (lastBeatWasNew == 1)
				&& (lastRhythmClass == NORMAL)
				&& (rhythmClass == NORMAL) )
			ClearLastNewType() ;

		lastBeatWasNew = 0 ;

		// Find the template that best matches this beat.

		BestMorphMatch(BeatBuffer) ;

		// Disregard noise if the match is good. (New)

		if(matchIndex < MATCH_NOISE_THRESHOLD)
			hfNoise = noiseLevel = blShift = 0 ;

		// Apply a stricter match limit to premature beats.

		if((matchIndex < MATCH_LIMIT) && (rhythmClass == PVC) &&
				(MinimumBeatVariation(morphType) != 0) && (mi2 > PVC_MATCH_WITH_AMP_LIMIT))
		{
			morphType = NewBeatType(BeatBuffer) ;
			lastBeatWasNew = 1 ;
		}

		// Match if within standard match limits.

		else if((matchIndex < MATCH_LIMIT) && (mi2 <= MATCH_WITH_AMP_LIMIT))
			UpdateBeatType(morphType,BeatBuffer,mi2,shiftAdj) ;

		// If the beat isn't noisy but doesn't match, start a new beat.

		else if((blShift < BL_SHIFT_LIMIT) && (noiseLevel < NEW_TYPE_NOISE_THRESHOLD)
				&& (hfNoise < NEW_TYPE_HF_NOISE_LIMIT))
		{
			morphType = NewBeatType(BeatBuffer) ;
			lastBeatWasNew = 1 ;
		}

		// Even if it is a noisy, start new beat if it was an irregular beat.

		else if((lastRhythmClass != NORMAL) || (rhythmClass != NORMAL))
		{
			morphType = NewBeatType(BeatBuffer) ;
			lastBeatWasNew = 1 ;
		}

		// If its noisy and regular, don't waste space starting a new beat.

		else morphType = MAXTYPES ;

		// Update recent rr and type arrays.

		for(i = 7; i > 0; --i)
		{
			RecentRRs[i] = RecentRRs[i-1] ;
			RecentTypes[i] = RecentTypes[i-1] ;
		}
		RecentRRs[0] = rr ;
		RecentTypes[0] = morphType ;

		lastRhythmClass = rhythmClass ;
		lastIsoLevel = isoLevel ;

		// Fetch beat features needed for classification.
		// Get features from average beat if it matched.

		if(morphType != MAXTYPES)
		{
			beatClass = GetBeatClass(morphType) ;
			beatWidth = GetBeatWidth(morphType) ;
			fidAdj = GetBeatCenter(morphType)-FIDMARK ;

			// If the width seems large and there have only been a few
			// beats of this type, use the actual beat for width
			// estimate.

			if((beatWidth > offset-onset) && (GetBeatTypeCount(morphType) <= 4))
			{
				beatWidth = offset-onset ;
				fidAdj = ((offset+onset)/2)-FIDMARK ;
			}
		}

		// If this beat didn't match get beat features directly
		// from this beat.

		else
		{
			beatWidth = offset-onset ;
			beatClass = UNKNOWN ;
			fidAdj = ((offset+onset)/2)-FIDMARK ;
		}

		// Fetch dominant type beat features.

		DomType = domType = DomMonitor(morphType, rhythmClass, beatWidth, rr, 0) ;
		domWidth = GetBeatWidth(domType) ;

		// Compare the beat type, or actual beat to the dominant beat.

		if((morphType != domType) && (morphType != 8))
			domIndex = DomCompare(morphType,domType) ;
		else if(morphType == 8)
			domIndex = DomCompare2(BeatBuffer,domType) ;
		else domIndex = matchIndex ;

		// Update post classificaton of the previous beat.

		PostClassify(RecentTypes, domType, RecentRRs, beatWidth, domIndex, rhythmClass) ;

		// Classify regardless of how the morphology
		// was previously classified.

		tempClass = TempClass(rhythmClass, morphType, beatWidth, domWidth,
				domType, hfNoise, noiseLevel, blShift, domIndex) ;

		// If this morphology has not been classified yet, attempt to classify
		// it.

		if((beatClass == UNKNOWN) && (morphType < MAXTYPES))
		{

			// Classify as normal if there are 6 in a row
			// or at least two in a row that meet rhythm
			// rules for normal.

			runCount = GetRunCount() ;

			// Classify a morphology as NORMAL if it is not too wide, and there
			// are three in a row.  The width criterion prevents ventricular beats
			// from being classified as normal during VTACH (MIT/BIH 205).

			if((runCount >= 3) && (domType != -1) && (beatWidth < domWidth+BEAT_MS20))
				SetBeatClass(morphType,NORMAL) ;

			// If there is no dominant type established yet, classify any type
			// with six in a row as NORMAL.

			else if((runCount >= 6) && (domType == -1))
				SetBeatClass(morphType,NORMAL) ;

			// During bigeminy, classify the premature beats as ventricular if
			// they are not too narrow.

			else if(IsBigeminy() == 1)
			{
				if((rhythmClass == PVC) && (beatWidth > BEAT_MS100))
					SetBeatClass(morphType,PVC) ;
				else if(rhythmClass == NORMAL)
					SetBeatClass(morphType,NORMAL) ;
			}
		}

		// Save morphology type of this beat for next classification.

		beatMatch = morphType ;

		beatClass = GetBeatClass(morphType) ;

		// If the morphology has been previously classified.
		// use that classification.
		//	return(rhythmClass) ;

		if(beatClass != UNKNOWN)
			return(beatClass) ;

		if(CheckPostClass(morphType) == PVC)
			return(PVC) ;

		// Otherwise use the temporary classification.

		return(tempClass) ;
	}

	/**************************************************************************
	 *  HFNoiseCheck() gauges the high frequency (muscle noise) present in the
	 *  beat template.  The high frequency noise level is estimated by highpass
	 *  filtering the beat (y[n] = x[n] - 2*x[n-1] + x[n-2]), averaging the
	 *  highpass filtered signal over five samples, and finding the maximum of
	 *  this averaged highpass filtered signal.  The high frequency noise metric
	 *  is then taken to be the ratio of the maximum averaged highpassed signal
	 *  to the QRS amplitude.
	 **************************************************************************/

	private static int AVELENGTH = BEAT_MS50;

	int HFNoiseCheck(int[] beat)
	{
		int maxNoiseAve = 0, i ;
		int sum=0;
		int[] aveBuff = new int[AVELENGTH];
		int avePtr = 0 ;
		int qrsMax = 0, qrsMin = 0 ;

		// Determine the QRS amplitude.

		for(i = FIDMARK-BEAT_MS70; i < FIDMARK+BEAT_MS80; ++i)
			if(beat[i] > qrsMax)
				qrsMax = beat[i] ;
			else if(beat[i] < qrsMin)
				qrsMin = beat[i] ;

		for(i = 0; i < AVELENGTH; ++i)
			aveBuff[i] = 0 ;

		for(i = FIDMARK-BEAT_MS280; i < FIDMARK+BEAT_MS280; ++i)
		{
			sum -= aveBuff[avePtr] ;
			aveBuff[avePtr] = Math.abs(beat[i] - (beat[i-BEAT_MS10]<<1) + beat[i-2*BEAT_MS10]) ;
			sum += aveBuff[avePtr] ;
			if(++avePtr == AVELENGTH)
				avePtr = 0 ;
			if((i < (FIDMARK - BEAT_MS50)) || (i > (FIDMARK + BEAT_MS110)))
				if(sum > maxNoiseAve)
					maxNoiseAve = sum ;
		}
		if((qrsMax - qrsMin)>=4)
			return((maxNoiseAve * (50/AVELENGTH))/((qrsMax-qrsMin)>>2)) ;
		else return(0) ;
	}

	/************************************************************************
	 *  TempClass() classifies beats based on their beat features, relative
	 *  to the features of the dominant beat and the present noise level.
	 *************************************************************************/

	int TempClass(int rhythmClass, int matchType,
			int beatWidth, int domWidth, int domType,
			int hfNoise, int noiseLevel, int blShift, double domIndex)
	{

		// Rule 1:  If no dominant type has been detected classify all
		// beats as UNKNOWN.

		if(domType < 0)
			return(UNKNOWN) ;

		// Rule 2:  If the dominant rhythm is normal, the dominant
		// beat type doesn't vary much, this beat is premature
		// and looks sufficiently different than the dominant beat
		// classify as PVC.

		if( (MinimumBeatVariation(domType) != 0) && (rhythmClass == PVC)
				&& (domIndex > R2_DI_THRESHOLD) && (GetDomRhythm() == 1))
			return(PVC) ;

		// Rule 3:  If the beat is sufficiently narrow, classify as normal.

		if(beatWidth < R3_WIDTH_THRESHOLD)
			return(NORMAL) ;

		// Rule 5:  If the beat cannot be matched to any previously
		// detected morphology and it is not premature, consider it normal
		// (probably noisy).

		if((matchType == MAXTYPES) && (rhythmClass != PVC)) // == UNKNOWN
			return(NORMAL) ;

		// Rule 6:  If the maximum number of beat types have been stored,
		// this beat is not regular or premature and only one
		// beat of this morphology has been seen, call it normal (probably
		// noisy).

		if((GetTypesCount() == MAXTYPES) && (GetBeatTypeCount(matchType)==1)
				&& (rhythmClass == UNKNOWN))
			return(NORMAL) ;

		// Rule 7:  If this beat looks like the dominant beat and the
		// rhythm is regular, call it normal.

		if((domIndex < R7_DI_THRESHOLD) && (rhythmClass == NORMAL))
			return(NORMAL) ;

		// Rule 8:  If post classification rhythm is normal for this
		// type and its shape is close to the dominant shape, classify
		// as normal.

		if((domIndex < R8_DI_THRESHOLD) && (CheckPCRhythm(matchType) == NORMAL))
			return(NORMAL) ;

		// Rule 9:  If the beat is not premature, it looks similar to the dominant
		// beat type, and the dominant beat type is variable (noisy), classify as
		// normal.

		if((domIndex < R9_DI_THRESHOLD) && (rhythmClass != PVC) && (WideBeatVariation(domType) != 0) )
			return(NORMAL) ;

		// Rule 10:  If this beat is significantly different from the dominant beat
		// there have previously been matching beats, the post rhythm classification
		// of this type is PVC, and the dominant rhythm is regular, classify as PVC.

		if((domIndex > R10_DI_THRESHOLD)
				&& (GetBeatTypeCount(matchType) >= R10_BC_LIM) &&
				(CheckPCRhythm(matchType) == PVC) && (GetDomRhythm() == 1))
			return(PVC) ;

		// Rule 11: if the beat is wide, wider than the dominant beat, doesn't
		// appear to be noisy, and matches a previous type, classify it as
		// a PVC.

		if( (beatWidth >= R11_MIN_WIDTH) &&
				(((beatWidth - domWidth >= R11_WIDTH_DIFF1) && (domWidth < R11_WIDTH_BREAK)) ||
						(beatWidth - domWidth >= R11_WIDTH_DIFF2)) &&
						(hfNoise < R11_HF_THRESHOLD) && (noiseLevel < R11_MA_THRESHOLD) && (blShift < BL_SHIFT_LIMIT) &&
						(matchType < MAXTYPES) && (GetBeatTypeCount(matchType) > R11_BC_LIM))	// Rev 1.1

			return(PVC) ;

		// Rule 12:  If the dominant rhythm is regular and this beat is premature
		// then classify as PVC.

		if((rhythmClass == PVC) && (GetDomRhythm() == 1))
			return(PVC) ;

		// Rule 14:  If the beat is regular and the dominant rhythm is regular
		// call the beat normal.

		if((rhythmClass == NORMAL) && (GetDomRhythm() == 1))
			return(NORMAL) ;

		// By this point, we know that rhythm will not help us, so we
		// have to classify based on width and similarity to the dominant
		// beat type.

		// Rule 15: If the beat is wider than normal, wide on an
		// absolute scale, and significantly different from the
		// dominant beat, call it a PVC.

		if((beatWidth > domWidth) && (domIndex > R15_DI_THRESHOLD) &&
				(beatWidth >= R15_WIDTH_THRESHOLD))
			return(PVC) ;

		// Rule 16:  If the beat is sufficiently narrow, call it normal.

		if(beatWidth < R16_WIDTH_THRESHOLD)
			return(NORMAL) ;

		// Rule 17:  If the beat isn't much wider than the dominant beat
		// call it normal.

		if(beatWidth < domWidth + R17_WIDTH_DELTA)
			return(NORMAL) ;

		// If the beat is noisy but reasonably close to dominant,
		// call it normal.

		// Rule 18:  If the beat is similar to the dominant beat, call it normal.

		if(domIndex < R18_DI_THRESHOLD)
			return(NORMAL) ;

		// If it's noisy don't trust the width.

		// Rule 19:  If the beat is noisy, we can't trust our width estimate
		// and we have no useful rhythm information, so guess normal.

		if(hfNoise > R19_HF_THRESHOLD)
			return(NORMAL) ;

		// Rule 20:  By this point, we have no rhythm information, the beat
		// isn't particularly narrow, the beat isn't particulary similar to
		// the dominant beat, so guess a PVC.

		return(PVC) ;

	}


}









