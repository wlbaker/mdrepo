/*
 * AIChannel.cpp
 *
 *  Created on: Oct 16, 2009
 *      Author: william.l.baker2
 */

#include "NIFuncs.h"
#include <jni.h>
#include "jniUtil.h"

#include "ni_DAQmx_MxAOChannel.h"

#define DAQmxErrChk(functionCall) if( DAQmxFailed(error=(functionCall)) ) goto Error; else

using namespace std;

extern "C" JNIEXPORT jlong JNICALL Java_ni_DAQmx_MxAOChannel_createVoltageChannel(
		JNIEnv *env, jobject jobj,
		jlong th, jstring physicalChannelName, jstring assignedChannelName,
		// jobject terminalConfiguration,
		jdouble minValue, jdouble maxValue, jobject units)
{
	int error = 0;
	TaskHandle taskHandle = (TaskHandle)th;

	// int tcValue = getIntField( env, terminalConfiguration, "v");
	int unitValue = getIntField( env, units, "v");

	const char *nativePhysicalChannel = env->GetStringUTFChars( physicalChannelName, 0);
	const char *nativeAssignedChannel = ( assignedChannelName == NULL ) ? NULL : env->GetStringUTFChars( assignedChannelName, 0);

	     /*Do something with the nativeString*/


	DAQmxErrChk (DAQmxCreateAOVoltageChan(taskHandle,
			nativePhysicalChannel,
			nativeAssignedChannel,
			// tcValue,
			minValue,
			maxValue,
			unitValue,
			NULL));

    /*DON'T FORGET THIS LINE!!!*/
    if( nativePhysicalChannel != NULL ) env->ReleaseStringUTFChars( physicalChannelName, nativePhysicalChannel);
    if( nativeAssignedChannel != NULL ) env->ReleaseStringUTFChars( assignedChannelName, nativeAssignedChannel);

    return 0;
	Error:
		// Java_idea_ni_IsrNi_niEndTask( jniEnv, jobj );
		return -1;
}

/*

extern "C" JNIEXPORT jdouble JNICALL Java_ni_DAQmx_MxAOChannel_getAccelerationDecibelReference(JNIEnv *env, jobject jobj) {

	jstring channelName = getChannelName( env, jobj );
	const char *nativeChannelName = env->GetStringUTFChars( channelName, 0);

	float64 val;
	DAQmxGetAOAcceldBRef( getTaskHandle( env, jobj ), nativeChannelName, &val );

    if( nativeChannelName != NULL ) env->ReleaseStringUTFChars( channelName, nativeChannelName );

	return val;
}

extern "C" JNIEXPORT void JNICALL Java_ni_DAQmx_MxAIChannel_setAccelerationDecibelReference(JNIEnv *env, jobject jobj, jdouble dval ) {

	jstring channelName = getChannelName( env, jobj );
	const char *nativeChannelName = env->GetStringUTFChars( channelName, 0);

	float64 val = dval;
	DAQmxSetAOAcceldBRef( getTaskHandle( env, jobj ), nativeChannelName, val);

    if( nativeChannelName != NULL ) env->ReleaseStringUTFChars( channelName, nativeChannelName );

	//? int32 __CFUNC DAQmxResetAIAcceldBRef(TaskHandle taskHandle, const char channel[]);
	return;
}
*/


