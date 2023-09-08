#include "NIFuncs.h"

#include <jni.h>

// #include "jDAQmx.h"
#include "jniUtil.h"

// #include "ni_DAQmx_DaqStream.h"

using namespace std;

JNIEXPORT void JNICALL Java_ni_DAQmx_MxDaqStream_configureInputBuffer
  (JNIEnv *env, jobject obj, jlong siz) {

	TaskHandle taskHandle = getTaskHandle( env, obj );

	cout << "config inputbuf: " << taskHandle << " size: " << siz << endl;
	cout.flush();

	DAQmxCfgInputBuffer( taskHandle, siz );

}

/*
 * Class:     ni_DAQcommon_DaqStream
 * Method:    configureOutputBuffer
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_ni_DAQmx_MxDaqStream_configureOutputBuffer
  (JNIEnv *env, jobject obj, jlong siz) {

	TaskHandle taskHandle = getTaskHandle( env, obj );

	cout << "NOT IMPLEMENTED config putputbuf: " << taskHandle << " size: " << siz << endl;
	cout.flush();

	// DAQmxBaseCfgOutputBuffer( taskHandle, siz );


}
