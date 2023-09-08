#include "NIFuncs.h"
#include <jni.h>
#include "NIDaqJ.h"
#include "jniUtil.h"

#include "ni_DAQmx_MxAnalogMultiChannelWriter.h"

#define DAQmxErrChk(functionCall) if( DAQmxFailed(error=(functionCall)) ) goto Error; else

using namespace std;

#ifdef HAVE_WRITE_CALLBACKS
int32 CVICALLBACK niEveryNCallback(TaskHandle taskHandle,
		int32 everyNsamplesEventType, uInt32 nSamples, void *callbackData);

int32 CVICALLBACK niDoneCallback(TaskHandle taskHandle, int32 status,
		void *callbackData);

struct callbackData {
	TaskHandle taskHandle;
	jmethodID callbackMID;
	int32 n_read;

	float64 *buffer;
	jobject cached_obj;
	JNIEnv *cached_env;
	int event_thread_id;
	int32 arraySize;
	int error;
	char errBuff[2048];
};
#endif

static void explainClass(JNIEnv *env, jobject jobj) {

	const char *name = NULL;
	jstring str = NULL;
	jclass cls = NULL;

	if (jobj != NULL) {
		cls = env->GetObjectClass(jobj);
		jmethodID mid = env->GetMethodID(cls, "toString",
				"()Ljava/lang/String;");

		str = (jstring) env->CallObjectMethod(cls, mid);
		name = env->GetStringUTFChars(str, 0);
	}

	cout << " explaining: " << cls << endl;
	cout << "       name: " << name << endl;

	if (name != NULL) {
		env->ReleaseStringUTFChars(str, name);
	}
}

extern "C" JNIEXPORT jdoubleArray JNICALL Java_ni_DAQmx_MxAnalogMultiChannelWriter_writeSingleSample(
		JNIEnv *env, jobject jobj) {

	int32 error = 0;
	uInt32 nchannels = 0;

	jdoubleArray cod = NULL;

	jobject stream = getObjField(env, jobj, "stream",
			"Lni/DAQcommon/DaqStream;");

	TaskHandle taskHandle = getTaskHandle(env, stream);

	DAQmxErrChk (DAQmxGetTaskNumChans( taskHandle, &nchannels ) )

	if (nchannels > 0) {

		int32 n_write = 250 / nchannels;  // ERROR: get length of java array
		int32 n_written = 0;  // num samples written to buffer

		cod = env->NewDoubleArray( nchannels );

		jdouble * arr = env->GetDoubleArrayElements( cod, NULL );

		arr[0] = 123;
		float64 *data = (float64 *)arr;
		DAQmxErrChk (DAQmxWriteAnalogF64(taskHandle,n_write,true,10.0,DAQmx_Val_GroupByChannel,data, &n_written,NULL));

		env->ReleaseDoubleArrayElements( cod, arr, 0 ); // hmmm

	}

	Error:
	if( DAQmxFailed(error) ) {
		char errBuff[1024] = {'\0'};

		DAQmxGetExtendedErrorInfo(errBuff, sizeof( errBuff) );

		throwDaqError( env, errBuff );
	}

	return cod;
}

#ifdef HAVE_WRITE_CALLBACKS

extern "C" JNIEXPORT jobject JNICALL Java_ni_DAQmx_MxAnalogMultiChannelReader_beginWriteWaveform(
		JNIEnv *jniEnv, jobject jobj, jint samplesPerChannel,
		jobject callbackObject, jobject task) {

	int32 error = 0;

	uInt32 nchannels = 0;

	callbackData *cbdata = new callbackData();

	cbdata->cached_obj = jniEnv->NewGlobalRef(callbackObject);
	//	explainClass( jniEnv, callbackObject );
	//	explainClass( jniEnv, cbdata->cached_obj );

	cbdata->taskHandle = getTaskHandle(jniEnv, task);
	DAQmxErrChk (DAQmxGetTaskNumChans(cbdata->taskHandle, &nchannels ) )
;	cbdata->arraySize = samplesPerChannel * nchannels;
	cbdata->buffer = new float64[cbdata->arraySize]; // TODO: *nchannels
	cbdata->event_thread_id = -1;
	cbdata->error = 0;

	cout << "reading task: " << cbdata->taskHandle << endl;
	cout << "samples per channel: " << samplesPerChannel << endl;
	cout.flush();

	DAQmxErrChk (DAQmxRegisterEveryNSamplesEvent( cbdata->taskHandle,DAQmx_Val_Acquired_Into_Buffer,samplesPerChannel,0,niEveryNCallback,cbdata));
	DAQmxErrChk (DAQmxRegisterDoneEvent(cbdata->taskHandle,0,niDoneCallback,cbdata));

	DAQmxErrChk (DAQmxStartTask(cbdata->taskHandle));

	Error:
	if( DAQmxFailed(error) ) {

		DAQmxGetExtendedErrorInfo(cbdata->errBuff, sizeof( cbdata->errBuff) );

		throwDaqError( jniEnv, cbdata->errBuff );
	}

	return NULL;

}

extern "C" JNIEXPORT jobjectArray JNICALL Java_ni_DAQmx_MxAnalogMultiChannelReader_endReadWaveform(
		JNIEnv *env, jobject jobj, jobject asyncResult) {

	callbackData *cbdata =
			(callbackData *) getCallbackHandle2(env, asyncResult);

	jobjectArray cod = NULL;
	int32 error = 0;

	if (cbdata->error != 0) {
		error = cbdata->error;
		goto Error;
	}

	uInt32 nchannels = 0;
	DAQmxErrChk (DAQmxGetTaskNumChans(cbdata->taskHandle, &nchannels ))
;
	// create an array of waveforms
	jclass cls = global_analogwaveform; // env->FindClass( "ni/DAQcommon/AnalogWaveform" );
	cod = env->NewObjectArray( nchannels, cls, NULL);

	// get the constructor and data field identifiers
	jmethodID ctr_mid = env->GetMethodID( cls, "<init>", "(I)V");
	jfieldID fid = env->GetFieldID( cls, "data", "[D");

	float64 *buffer = cbdata->buffer;
	for( jsize idx = 0; idx < nchannels; idx++) {
		jobject waveform = env->AllocObject( cls );
		// call constructor with argument
		env->CallVoidMethod( waveform, ctr_mid, cbdata->n_read );

		jdoubleArray var = (jdoubleArray)env->GetObjectField( waveform, fid);
		env->SetDoubleArrayRegion( var, 0, cbdata->n_read, buffer);
		buffer += cbdata->n_read;        // one channel after another

		env->SetObjectArrayElement(cod, idx, waveform);
	}

	Error:

	if( DAQmxFailed(error) ) {
		DAQmxGetExtendedErrorInfo(cbdata->errBuff,sizeof( cbdata->errBuff));
		/*********************************************/
		// DAQmx Stop Code
		/*********************************************/
		//DAQmxStopTask(taskHandle);
		//DAQmxClearTask(taskHandle);

		throwDaqError( env, cbdata->errBuff );
	}

	return cod;
}

int32 CVICALLBACK niEveryNCallback(TaskHandle taskHandle,
		int32 everyNsamplesEventType, uInt32 nSamples, void *cbptr) {

	int32 nSamplesPerChan = nSamples; // TODO: need clarification over what this parameter stands for

	callbackData *cbdata = (callbackData *) cbptr;
	JNIEnv *env = cbdata->cached_env;
	int32 error = 0;

	/*********************************************/
	// DAQmx Read Code
	/*********************************************/
	uInt32 nchannels = 0;
	DAQmxErrChk (DAQmxGetTaskNumChans(cbdata->taskHandle, &nchannels ))
;	DAQmxErrChk (DAQmxReadAnalogF64(cbdata->taskHandle,nSamplesPerChan,10.0,DAQmx_Val_GroupByChannel,cbdata->buffer, cbdata->arraySize,&cbdata->n_read,NULL));

	if( cbdata->n_read>0 ) {

		if( cbdata->event_thread_id != GetCurrentThreadId() ) {

			cbdata->event_thread_id = GetCurrentThreadId();
			cached_jvm->AttachCurrentThread( (void **)&cbdata->cached_env, NULL);

			env = cbdata->cached_env;

			jclass clzz = global_asynccallback; // env->FindClass( "ni/DAQcommon/AsyncCallback");
			cbdata->callbackMID = env->GetMethodID( clzz, "asyncCallback", "(Lni/DAQcommon/IAsyncResult;)V");

			// explainClass( env, cbdata->cached_obj );

			if( cbdata->callbackMID == NULL ) {
				cerr << " FATAL ERROR: callback method not found" << endl;
				cerr.flush();
			}

			// env->DeleteLocalRef(clzz);

		}

		if ( cbdata->callbackMID != NULL) {

			jclass cls = global_internalasyncresult; // env->FindClass( "ni/DAQmx/InternalAsyncResult" );
			if( cls == NULL ) {
				cerr << " FATAL ERROR: could not find ni/DAQmx/InternalAsyncResult" << endl;
				cerr.flush();
			}
			jobject iar = env->AllocObject( cls );
			if( iar == NULL ) {
				cerr << " FATAL ERROR: could not allocate ni/DAQmx/InternalAsyncResult" << endl;
				cerr.flush();
			}

			jmethodID mid = env->GetMethodID( cls, "<init>", "(J)V" );
			if( mid == NULL ) {
				cerr << " FATAL ERROR: could not init ni/DAQmx/InternalAsyncResult" << endl;
				cerr.flush();
			}

			env->CallVoidMethod( iar, mid, cbdata );
			env->CallVoidMethod( cbdata->cached_obj, cbdata->callbackMID, iar );

			// env->DeleteLocalRef(cls);

		}

	}

	Error:
	if( DAQmxFailed(error) ) {
		DAQmxGetExtendedErrorInfo(cbdata->errBuff,sizeof( cbdata->errBuff));

		/*********************************************/
		// DAQmx Stop Code
		/*********************************************/
		DAQmxStopTask(taskHandle);
		DAQmxClearTask(taskHandle);

		cerr << "DAQmx Error AMCR-1: " << cbdata->errBuff << endl;

		// have to throw an error on a thread that is re-managed
		throwDaqError( env, cbdata->errBuff );

	}
	return 0;
}

int32 CVICALLBACK niDoneCallback(TaskHandle taskHandle, int32 status,
		void *cbptr) {
	// int32 error = 0;

	//	char errBuff[2048] = { '\0' };
	//
	//	DAQmxErrChk (status);
	//	Error:
	//	if( DAQmxFailed(error) ) {
	//		DAQmxGetExtendedErrorInfo(errBuff,2048);
	//		DAQmxClearTask(taskHandle);

	//		callbackData *cbdata = (callbackData *)cbptr;
	//		JNIEnv *env = cbdata->cached_env;
	//		throwDaqError( env, errBuff );
	//	}
	//	return 0;


	callbackData *cbdata = (callbackData *) cbptr;
	JNIEnv *env = cbdata->cached_env;

	cbdata->error = status;
	DAQmxGetExtendedErrorInfo(cbdata->errBuff, 2048);

	if (cbdata->event_thread_id != GetCurrentThreadId()) {

		cbdata->event_thread_id = GetCurrentThreadId();
		cached_jvm->AttachCurrentThread((void **) &cbdata->cached_env, NULL);

		jclass clzz = global_asynccallback; // env->FindClass("ni/DAQcommon/AsyncCallback");
		cbdata->callbackMID = env->GetMethodID(clzz, "asyncCallback",
				"(Lni/DAQcommon/IAsyncResult;)V");
		// env->DeleteLocalRef(clzz);
	}

	if (cbdata->callbackMID != NULL) {

		jclass clzz = global_internalasyncresult; // env->FindClass("ni/DAQmx/InternalAsyncResult");
		jobject iar = env->AllocObject(clzz);
		jmethodID mid = env->GetMethodID(clzz, "<init>", "(J)V");

		env->CallVoidMethod(iar, mid, cbdata);

		env->CallVoidMethod(cbdata->cached_obj, cbdata->callbackMID, iar);

		// env->DeleteLocalRef(clzz);

	}

	return 0;
}

#endif  // HAVE_WRITE_CALLBACKS
