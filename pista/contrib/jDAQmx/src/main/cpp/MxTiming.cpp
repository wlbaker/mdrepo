/*
 * AIChannel.cpp
 *
 *  Created on: Oct 16, 2009
 *      Author: william.l.baker2
 */

#include "NIFuncs.h"
#include <jni.h>
#include "jniUtil.h"

#include "ni_DAQmx_MxTiming.h"

#define DAQmxErrChk(functionCall) if( DAQmxFailed(error=(functionCall)) ) goto Error; else

using namespace std;


extern "C" JNIEXPORT void JNICALL Java_ni_DAQmx_MxTiming_configureSampleClock(
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


	cout << "cfgclktiming: " << taskHandle << " \"\" rate: " << rate << " activeEdge:" << aeValue << " cont: " << smValue << " perchan=" << samplesPerChannel << endl;
	cout.flush();

	DAQmxErrChk (DAQmxCfgSampClkTiming(taskHandle, "", rate, aeValue, smValue, samplesPerChannel));


    /*DON'T FORGET THIS LINE!!!*/
    if( nativeSignalSource != NULL ) env->ReleaseStringUTFChars( signalSource, nativeSignalSource );

    Error:
	if( DAQmxFailed(error) ) {
		char errBuff[256] = { '\0' };

		DAQmxGetExtendedErrorInfo(errBuff, 256);

		throwDaqError( env, errBuff );
	}

	return;
}

