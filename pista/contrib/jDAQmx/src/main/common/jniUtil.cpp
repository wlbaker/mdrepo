/*
 * jniUtil.cpp
 *
 *  Created on: Oct 10, 2009
 *      Author: bbaker
 */

#include <stdio.h>
#include <jni.h>
#include <NIDAQmxBase.h>
#include "jniUtil.h"

#include <iostream>

using namespace std;

/*
 int valueOfEnum( JNIEnv *env, jobject jobj ) {
 jint v = env->GetIntField( o, "v");

 return v;
 }
 */

void *getCallbackHandle2(JNIEnv *env, jobject jobj) {
	jclass cls = env->GetObjectClass(jobj);
	jfieldID fid = env->GetFieldID(cls, "_callbackHandle", "J");
	jlong var = env->GetLongField(jobj, fid);

	return (void *) var;
}

TaskHandle getTaskHandle(JNIEnv *env, jobject jobj) {
	jclass cls = env->GetObjectClass(jobj);
	jfieldID fid = env->GetFieldID(cls, "_taskHandle", "J");
	jlong var = env->GetLongField(jobj, fid);

	return (TaskHandle) var;
}

TaskHandle getTaskHandleFromTaskField(JNIEnv *env, jobject jobj) {
	jclass cls = env->GetObjectClass(jobj);
	jfieldID fid = env->GetFieldID(cls, "_task", "Lni/DAQcommon/Task;");

	jobject var = env->GetObjectField(jobj, fid);

	return getTaskHandle( env, var );
}

int getIntField(JNIEnv *env, jobject jobj, const char *fieldName) {
	jclass cls = env->GetObjectClass(jobj);
	jfieldID fid = env->GetFieldID(cls, fieldName, "I");
	jint var = env->GetIntField(jobj, fid);

	return var;
}

jobject getObjField(JNIEnv *env, jobject jobj, const char *fieldName, const char *sig) {
	jclass cls = env->GetObjectClass(jobj);
	jfieldID fid = env->GetFieldID(cls, fieldName, sig);
	jobject var = NULL;
	if( fid != 0 ) {
		var = env->GetObjectField(jobj, fid);
	}

	// cout << "getObjField class: " << cls << " fid: " << fid << " var: " << var << endl;

	return var;
}

jstring getChannelName(JNIEnv *env, jobject jobj) {
	jclass cls = env->GetObjectClass(jobj);
	jfieldID fid = env->GetFieldID(cls, "_channelName", "Ljava/lang/String");
	jstring var = (jstring) env->GetObjectField(jobj, fid);

	return var;
}

int throwDaqError(JNIEnv *env, const char *errBuff) {
	fprintf( stderr, "ERR in channel creation: %s", errBuff );

	jclass cls = env->FindClass("ni/DAQcommon/DaqException");

	if (cls == NULL) {
		/* Unable to find the exception class, give up. */
		return -2;
	}

	env->ThrowNew(cls, errBuff );

	/* free the local ref */
	env->DeleteLocalRef(cls);

	return -1;
}
