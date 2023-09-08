#include "jDAQmxBase.h"
#include "jniUtil.h"

#include "ni_DAQmxBase_BaseDaqStream.h"

using namespace std;

JNIEXPORT void JNICALL Java_ni_DAQmxBase_BaseDaqStream_configureInputBuffer
  (JNIEnv *env, jobject obj, jlong siz) {

	cout << "getting task handle" << endl;
	cout.flush();

	TaskHandle taskHandle = getTaskHandleFromTaskField( env, obj );

	cout << "config inputbuf: " << taskHandle << " size: " << siz << endl;
	cout.flush();

	DAQmxBaseCfgInputBuffer( taskHandle, siz );


}

/*
 * Class:     ni_DAQcommon_DaqStream
 * Method:    configureOutputBuffer
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_ni_DAQmxBase_BaseDaqStream_configureOutputBuffer
  (JNIEnv *env, jobject obj, jlong siz) {

	TaskHandle taskHandle = getTaskHandleFromTaskField( env, obj );

	cout << "NOT IMPLEMENTED config putputbuf: " << taskHandle << " size: " << siz << endl;
	cout.flush();

	// DAQmxBaseCfgOutputBuffer( taskHandle, siz );


}
