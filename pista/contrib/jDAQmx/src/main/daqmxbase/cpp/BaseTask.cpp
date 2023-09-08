/*
 * Task.cpp
 *
 *  Created on: Oct 15, 2009
 *      Author: bbaker
 */

#include "jDAQmxBase.h"
#include "jniUtil.h"

#include "ni_DAQmxBase_BaseTask.h"

using namespace std;


extern "C" JNIEXPORT jlong JNICALL Java_ni_DAQmxBase_BaseTask_createTask
  (JNIEnv *env, jobject jobj, jstring taskName ) {

	int32 error = 0;
	TaskHandle taskHandle;

	/*********************************************/
	// DAQmx Configure Code
	/*********************************************/
	DAQmxErrChk (DAQmxBaseCreateTask("",&taskHandle));

	cout << "DAQmxBaseCreateTask() --> " << taskHandle << endl;

	Error:

	if( DAQmxFailed(error) ) {
		char errBuff[256] = { '\0' };

		DAQmxBaseGetExtendedErrorInfo(errBuff, 256);

		throwDaqError( env, errBuff );
	}

	return (jlong)taskHandle;
}

extern "C" JNIEXPORT void JNICALL Java_ni_DAQmxBase_BaseTask_start(JNIEnv *env,
		jobject jobj) {

	int32 error = 0;
	TaskHandle taskHandle = getTaskHandle( env, jobj );

	/*********************************************/
	// DAQmx Configure Code
	/*********************************************/
	cout << "DAQmxBaseStartTask (" << taskHandle << ")" << endl;

	DAQmxErrChk (DAQmxBaseStartTask( taskHandle));

	Error:
	if( DAQmxFailed(error) ) {
		char errBuff[256] = { '\0' };

		DAQmxBaseGetExtendedErrorInfo(errBuff, 256);

		throwDaqError( env, errBuff );
	}

	return;
}

extern "C" JNIEXPORT void JNICALL Java_ni_DAQmxBase_BaseTask_stop(JNIEnv *env,
		jobject jobj) {

	int32 error = 0;
	TaskHandle taskHandle = getTaskHandle( env, jobj );

	/*********************************************/
	// DAQmx Configure Code
	/*********************************************/
	DAQmxErrChk (DAQmxBaseStopTask( taskHandle));

	Error:
	if( DAQmxFailed(error) ) {
		char errBuff[256] = { '\0' };

		DAQmxBaseGetExtendedErrorInfo(errBuff, 256);

		throwDaqError( env, errBuff );
	}

	return;
}
