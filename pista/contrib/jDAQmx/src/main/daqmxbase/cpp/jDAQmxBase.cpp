/*
 * NIDaqJ.cpp
 *
 *  Created on: Oct 5, 2009
 *      Author: bbaker
 */

#include <iostream>
#include <list>

#include <jni.h>

#include "jDAQmxBase.h"

JavaVM *cached_jvm;

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *jvm, void *reserved) {
	cached_jvm = jvm; /* cache the JavaVM pointer */

	/*
	 if ((*jvm)->GetEnv(jvm, (void **)&env, JNI_VERSION_1_2)) {
	 return JNI_ERR; // JNI version not supported
	 }
	 cls = (*env)->FindClass(env, "C");
	 if (cls == NULL) {
	 return JNI_ERR;
	 }
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
	return JNI_VERSION_1_4;
}


