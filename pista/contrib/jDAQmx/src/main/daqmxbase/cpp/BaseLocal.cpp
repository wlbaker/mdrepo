/*
 * Local.cpp
 *
 *  Created on: Oct 10, 2009
 *      Author: bbaker
 */

#include "NIFuncs.h"

#include <jni.h>
#include "ni_DAQmxBase_BaseLocal.h"

using namespace std;

#ifdef USE_VISA_ZZ
#include "visa.h"
#endif


JNIEXPORT void JNICALL Java_ni_DAQmxBase_BaseLocal__1init(JNIEnv *, jobject) {


}

#define HARDCODED_AI_COUNT 16

extern "C" JNIEXPORT jobjectArray JNICALL Java_ni_DAQmxBase_BaseLocal_getPhysicalChannels(
		JNIEnv *env, jobject jobj) {

	/*
	 list<string> D;
	 list<string> L;

	 string d1("Dev1");
	 string d1ai1( "Dev1/ai1" );
	 // ni_getDevices( D );
	 D.push_back( d1 );

	 for( list<string>::const_iterator cii = D.begin(); cii != D.end(); cii++ ) {
	 cout << (*cii).c_str() << endl;
	 cout.flush() ;
	 // ni_getDevicePorts(L, (*cii).c_str() );
	 L.push_back( d1ai1 );
	 }
	 */

	jclass clazz = env->FindClass("java/lang/String");
	if (clazz == NULL) {
		return NULL;
	}

	// jobjectArray arr = env->NewObjectArray(L.size(), clazz, env->NewStringUTF(""));

	jobjectArray arr = env->NewObjectArray(HARDCODED_AI_COUNT, clazz, env->NewStringUTF(""));

	int n = 0;
	//for (list<string>::const_iterator cii = L.begin(); cii != L.end(); cii++) {
	//	env->SetObjectArrayElement(arr, n++, env->NewStringUTF( (*cii).c_str() ));
	//}

	for( int i = 0 ; i < HARDCODED_AI_COUNT ; i++ ) {
		char buf[16];
		sprintf( buf, "Dev1/ai%d", i );
		env->SetObjectArrayElement(arr, n++, env->NewStringUTF(buf));
	}

	return arr;

}

