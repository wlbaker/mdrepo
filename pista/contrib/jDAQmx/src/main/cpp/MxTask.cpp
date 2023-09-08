/*
 * Task.cpp
 *
 *  Created on: Oct 15, 2009
 *      Author: bbaker
 */

#include "NIFuncs.h"
#include <jni.h>
#include "jniUtil.h"

#include "ni_DAQmx_MxTask.h"

using namespace std;

extern "C" JNIEXPORT jlong JNICALL Java_ni_DAQmx_MxTask_createTask(JNIEnv *jniEnv,
		jobject jobj, jstring taskName ) {

	int32 error = 0;
	TaskHandle taskHandle;

	/*

	//data = jniEnv->NewIntArray (SAMPLES);
	jclass cls = (*jniEnv)->GetObjectClass(jniEnv, jobj);

	jfieldID fid = (*jniEnv)->GetFieldID(jniEnv, cls, "data", "[D");

	jdoubleArray var = (*jniEnv)->GetObjectField(jniEnv, jobj, fid);

	(*jniEnv)->SetDoubleArrayRegion(jniEnv, var, 0, 500, data);
	*/

	/*********************************************/
	// DAQmx Configure Code
	/*********************************************/
	DAQmxErrChk (DAQmxCreateTask("",&taskHandle));

	Error:
	if( DAQmxFailed(error) ) {
		char errBuff[256] = { '\0' };

		DAQmxGetExtendedErrorInfo(errBuff, 256);

		throwDaqError( jniEnv, errBuff );
	}

	return (jlong)taskHandle;
}

extern "C" JNIEXPORT void JNICALL Java_ni_DAQmx_MxTask_start(JNIEnv *jniEnv,
		jobject jobj) {

	int32 error = 0;
	TaskHandle taskHandle = getTaskHandle( jniEnv, jobj );

	/*********************************************/
	// DAQmx Configure Code
	/*********************************************/
	DAQmxErrChk (DAQmxStartTask( taskHandle));

	cout << "starting task" << endl;
	cout.flush();

	Error:
	if( DAQmxFailed(error) ) {
		char errBuff[256] = { '\0' };

		DAQmxGetExtendedErrorInfo(errBuff, 256);

		throwDaqError( jniEnv, errBuff );
	}

	return;
}

extern "C" JNIEXPORT void JNICALL Java_ni_DAQmx_MxTask_stop(JNIEnv *jniEnv,
		jobject jobj) {

	int32 error = 0;
	TaskHandle taskHandle = getTaskHandle( jniEnv, jobj );

	/*********************************************/
	// DAQmx Configure Code
	/*********************************************/
	DAQmxErrChk (DAQmxStopTask( taskHandle));

	Error:
	if( DAQmxFailed(error) ) {
		char errBuff[256] = { '\0' };

		DAQmxGetExtendedErrorInfo(errBuff, 256);

		throwDaqError( jniEnv, errBuff );
	}

	return;
}

extern "C" JNIEXPORT void JNICALL Java_ni_DAQmx_MxTask_dispose
  (JNIEnv *env, jobject jobj) {

}

extern "C" JNIEXPORT void JNICALL Java_ni_DAQmx_MxTask_debug
  (JNIEnv *env, jobject jobj, jobject arg ) {

	cout << "task debug arg: " << arg << endl;
}
