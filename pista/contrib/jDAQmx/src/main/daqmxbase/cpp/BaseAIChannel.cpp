/*
 * AIChannel.cpp
 *
 *  Created on: Oct 16, 2009
 *      Author: william.l.baker2
 */

#include "jDAQmxBase.h"
#include "jniUtil.h"

#include "ni_DAQmxBase_BaseAIChannel.h"

#define DAQmxErrChk(functionCall) if( DAQmxFailed(error=(functionCall)) ) goto Error; else

using namespace std;

extern "C" JNIEXPORT jlong JNICALL Java_ni_DAQmxBase_BaseAIChannel_createVoltageChannel(
		JNIEnv *env, jobject jobj, jlong th, jstring physicalChannelName,
		jstring assignedChannelName, jobject terminalConfiguration,
		jdouble minValue, jdouble maxValue, jobject units) {
	int error = 0;
	TaskHandle taskHandle = (TaskHandle) th;

	int tcValue = getIntField(env, terminalConfiguration, "v");
	int unitValue = getIntField(env, units, "v");

	const char *nativePhysicalChannel = env->GetStringUTFChars(
			physicalChannelName, 0);
	const char *nativeAssignedChannel = (assignedChannelName == NULL) ? NULL
			: env->GetStringUTFChars(assignedChannelName, 0);

	cout << "DAQmxBaseCreateAIVoltageChan( taskHandle, " << nativePhysicalChannel << ","
	     << nativeAssignedChannel << ","
		 << DAQmx_Val_Cfg_Default << ","
		 << minValue << ","
		 << maxValue << ","
		 << unitValue
		 << endl;

	DAQmxErrChk (DAQmxBaseCreateAIVoltageChan(taskHandle,
					nativePhysicalChannel,
					nativeAssignedChannel,
					DAQmx_Val_Cfg_Default, // tcValue,
					minValue,
					maxValue,
					unitValue,
					NULL));

	if( nativePhysicalChannel != NULL ) env->ReleaseStringUTFChars( physicalChannelName, nativePhysicalChannel);
	if( nativeAssignedChannel != NULL ) env->ReleaseStringUTFChars( assignedChannelName, nativeAssignedChannel);

	Error:

	if( DAQmxFailed(error) ) {
		char errBuff[256] = { '\0' };

		DAQmxBaseGetExtendedErrorInfo(errBuff, 256);

		throwDaqError( env, errBuff );
	}

	return error;
}

