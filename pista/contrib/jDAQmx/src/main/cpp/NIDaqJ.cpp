/*
 * NIDaqJ.cpp
 *
 *  Created on: Oct 5, 2009
 *      Author: bbaker
 */

#include <iostream>
#include <list>

#include "NIFuncs.h"

#include <jni.h>

#include "NIDaqJ.h"

JavaVM *cached_jvm;
jclass global_asynccallback;
jclass global_internalasyncresult;
jclass global_analogwaveform;

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *jvm, void *reserved) {
	cached_jvm = jvm; /* cache the JavaVM pointer */

	JNIEnv *env;

	if ( jvm->GetEnv((void **) &env, JNI_VERSION_1_2)) {
		return JNI_ERR; // JNI version not supported
	}
	/*
	 cls = (*env)->FindClass(env, "C");
	 // Use weak global ref to allow C class to be unloaded
	 Class_C = (*env)->NewWeakGlobalRef(env, cls);
	 if (Class_C == NULL) {
	 return JNI_ERR;
	 }
	 // Compute and cache the method ID
	 MID_C_g = (*env)->GetMethodID(env, cls, "g", "()V");
	 if (MID_C_g == NULL) {
	 return JNI_ERR;
	 }
	 */
	jclass cls;

	cls = (jclass)env->FindClass("ni/DAQcommon/AsyncCallback");
	if (cls == NULL) {
		return JNI_ERR;
	}
	global_asynccallback = (jclass)env->NewGlobalRef(cls);

	cls = (jclass)env->FindClass("ni/DAQmx/InternalAsyncResult");
	if (cls == NULL) {
		return JNI_ERR;
	}
	global_internalasyncresult = (jclass)env->NewGlobalRef(cls);

	cls = (jclass)env->FindClass("ni/DAQcommon/AnalogWaveform");
	if (cls == NULL) {
		return JNI_ERR;
	}
	global_analogwaveform = (jclass)env->NewGlobalRef(cls);

	return JNI_VERSION_1_4;
}

