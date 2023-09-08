/*
 * AIChannel.cpp
 *
 *  Created on: Oct 16, 2009
 *      Author: william.l.baker2
 */

#include "jDAQmxBase.h"
#include "jniUtil.h"

#include "ni_DAQmxBase_BaseTiming.h"

#define DAQmxErrChk(functionCall) if( DAQmxFailed(error=(functionCall)) ) goto Error; else

using namespace std;


extern "C" JNIEXPORT void JNICALL Java_ni_DAQmxBase_BaseTiming_configureSampleClock(
		JNIEnv *env, jobject jobj,
		jstring signalSource,
		jdouble rate, jobject activeEdge, jobject sampleMode, jint samplesPerChannel )
{
	int error = 0;
	TaskHandle taskHandle = getTaskHandle( env, jobj );

	int aeValue = getIntField( env, activeEdge, "v");
	int smValue = getIntField( env, sampleMode, "v");  // DAQmx_Val_ContSamps = 10123

	const char *nativeSignalSource = env->GetStringUTFChars( signalSource, 0);

	     /*Do something with the nativeString*/

	aeValue = DAQmx_Val_Rising;
	smValue = DAQmx_Val_ContSamps;
	char *clock = "OnboardClock";
	cout << "DAQmxBaseCfgSampClkTiming( " << taskHandle << ", \"<< clock << \", " << rate << ", " << aeValue << ", " << smValue << ", " << samplesPerChannel << ")" << endl;

	DAQmxErrChk (DAQmxBaseCfgSampClkTiming(taskHandle, clock, rate, aeValue, smValue, samplesPerChannel));


    /*DON'T FORGET THIS LINE!!!*/
    if( nativeSignalSource != NULL ) env->ReleaseStringUTFChars( signalSource, nativeSignalSource );

    return;
	Error:
		// Java_idea_ni_IsrNi_niEndTask( jniEnv, jobj );
		return;
}

