/*
 * Local.cpp
 *
 *  Created on: Oct 10, 2009
 *      Author: bbaker
 */

#include "NIFuncs.h"

#include <jni.h>

using namespace std;

extern "C" JNIEXPORT jobjectArray JNICALL Java_ni_DAQmx_MxLocal_getPhysicalChannels(JNIEnv *env, jobject jobj) {

	list<string> D;
	list<string> L;

	ni_getDevices( D );

	for( list<string>::const_iterator cii = D.begin(); cii != D.end(); cii++ ) {
		cout << (*cii).c_str() << endl;
		cout.flush() ;
		ni_getDevicePorts(L, (*cii).c_str() );
	}

	jclass clazz = env->FindClass("java/lang/String");
	if (clazz == NULL) {
		return NULL;
	}

	jobjectArray arr = env->NewObjectArray(L.size(), clazz, env->NewStringUTF(""));

	int n = 0;
	for (list<string>::const_iterator cii = L.begin(); cii != L.end(); cii++) {
		env->SetObjectArrayElement(arr, n++, env->NewStringUTF( (*cii).c_str() ));
	}

	return arr;

}

