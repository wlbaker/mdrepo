#include "jDAQmxBase.h"
#include "jniUtil.h"

#include "ni_DAQmxBase_BaseAnalogMultiChannelReader.h"

#define DAQmxErrChk(functionCall) if( DAQmxFailed(error=(functionCall)) ) goto Error; else

using namespace std;

extern "C" JNIEXPORT jobjectArray JNICALL Java_ni_DAQmxBase_BaseAnalogMultiChannelReader_readWaveform(JNIEnv *env, jobject obj, jint samplesPerChannel, jint nchannels ) {

	jobjectArray cod = NULL;

	int32 error = 0;

	TaskHandle taskHandle = getTaskHandleFromTaskField( env, obj );

	// create an array of waveforms
	jclass cls = env->FindClass( "ni/DAQcommon/AnalogWaveform" );
	jmethodID mid = env->GetMethodID( cls, "<init>", "(I)V");
	jfieldID fid = env->GetFieldID( cls, "data", "[D");

	cod = env->NewObjectArray( nchannels, cls, NULL);

	jlong n_read = samplesPerChannel;

	for( jsize idx = 0; idx < nchannels; idx++) {
		float64 timeout = 10.00;
		int32 pointsRead = -1;

		// call constructor with argument
		jobject waveform = env->AllocObject( cls );
		env->CallVoidMethod( waveform, mid, n_read );

		float64 *buffer = new float64[ samplesPerChannel ];

        DAQmxErrChk (DAQmxBaseReadAnalogF64(taskHandle,
        		samplesPerChannel,
        		timeout,
        		DAQmx_Val_GroupByChannel, // GroupByScanNumber,
        		buffer,
        		samplesPerChannel,
        		&pointsRead,NULL)
        		);

        if( pointsRead < 0 ) {
            cout << "error reading points! tot read: " << pointsRead << endl;

            cod = NULL;
        	break;
        }

		// env->SetIntArrayRegion( ?? );
		env->SetObjectArrayElement(cod, idx, waveform);

		// jdoubleArray var = env->GetObjectField( waveform, fid);
		jdoubleArray var = (jdoubleArray)env->GetObjectField( waveform, fid);

		env->SetDoubleArrayRegion( var, 0, n_read, (double *)buffer);
	}


	Error:
	if( DAQmxFailed(error) ) {
		char errBuff[1024] = {'\0'};

		DAQmxBaseGetExtendedErrorInfo(errBuff, sizeof( errBuff) );

		throwDaqError( env, errBuff );
	}

	return cod;
}

extern "C" JNIEXPORT jdoubleArray JNICALL Java_ni_DAQmxBase_BaseAnalogMultiChannelReader_readSingleSample(
		JNIEnv *env, jobject jobj) {

	int32 error = 0;
	uInt32 nchannels = 0;

	jdoubleArray cod = NULL;

	jobject stream = getObjField(env, jobj, "stream",
			"Lni/DAQcommon/DaqStream;");

	TaskHandle taskHandle = getTaskHandle(env, stream);

	nchannels = 1;

	/*
	{
		jclass cls = env->GetObjectClass(jobj);
	    jmethodID mid = env->GetMethodID(cls, "getStream",
			"()Lni/DAQcommon/DaqStream;");

		jclass cls = env->Get
			    jmethodID mid = env->GetMethodID(cls, "getNumberOfInputChannels",
					"()I");

				nchannels = (jint) env->CallObjectMethod(jobj, mid);
	}
	*/

	cerr << "FIXME: need number of channels " << nchannels << endl;;
	// DAQmxErrChk (DAQmxBaseGetTaskNumChans( taskHandle, &nchannels ) )

	if (nchannels > 0) {

		int32 read = 0;

		// DAQmxErrChk (DAQmxStartTask( taskHandle) );
		cod = env->NewDoubleArray( nchannels );

		jdouble * arr = env->GetDoubleArrayElements( cod, NULL );

		float64 *data = (float64 *)arr;
		DAQmxErrChk (DAQmxBaseReadAnalogF64(taskHandle,1,10.0,DAQmx_Val_GroupByChannel,data,nchannels, &read,NULL));

		env->ReleaseDoubleArrayElements( cod, arr, 0 ); // hmmm

		// DAQmxErrChk (DAQmxStopTask( taskHandle) );
		cout << "read=" << read << endl;
	}

	Error:
	if( DAQmxFailed(error) ) {
		char errBuff[1024] = {'\0'};

		DAQmxBaseGetExtendedErrorInfo(errBuff, sizeof( errBuff) );

		throwDaqError( env, errBuff );
	}

	return cod;
}

