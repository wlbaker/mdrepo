/*
 * Task.cpp
 *
 *  Created on: Oct 15, 2009
 *      Author: bbaker
 */

#include "jDAQmxBase.h"
#include "jniUtil.h"

#include "ni_DAQmxBase_Test.h"

using namespace std;


extern "C" JNIEXPORT jlong JNICALL Java_ni_DAQmxBase_Test_test0(JNIEnv *env,
		jobject jobj) {

	int32 error = 0;
	TaskHandle taskHandle;

	/*********************************************/
	// DAQmx Configure Code
	/*********************************************/
	DAQmxErrChk (DAQmxBaseCreateTask("",&taskHandle));

	cout << "DAQmxBaseCreateTask() --> " << taskHandle << endl;

	/*********************************************/
	// DAQmx Configure Code
	/*********************************************/
	cout << "DAQmxBaseStartTask (" << taskHandle << ")" << endl;

	DAQmxErrChk (DAQmxBaseStartTask( taskHandle));

	/*********************************************/
	// DAQmx Configure Code
	/*********************************************/
	DAQmxErrChk (DAQmxBaseStopTask( taskHandle));

	Error:
	if( DAQmxFailed(error) ) {
		char errBuff[256] = { '\0' };

		DAQmxBaseGetExtendedErrorInfo(errBuff, 256);

		throwDaqError( env, errBuff );
	}

	return error;
}


extern "C" JNIEXPORT jlong JNICALL Java_ni_DAQmxBase_Test_test1(JNIEnv *env,
		jobject jobj) {
    // Task parameters
    int32       error = 0;
    TaskHandle  taskHandle = 0;
    char        errBuff[2048]={'\0'};
    int32       i,j;
    time_t      startTime;
    bool32      done=0;

    // Channel parameters
    char        chan[] = "Dev1/ai0, Dev1/ai1";
    float64     min = -10.0;
    float64     max = 10.0;

    // Timing parameters
    char        clockSource[] = "OnboardClock";
    uInt64      samplesPerChan = 200;
    float64     sampleRate = 500.0;

    // Data read parameters
    #define     bufferSize (uInt32)1000
    float64     data[bufferSize * 2];
    int32       pointsToRead = bufferSize;
    int32       pointsRead;
    float64     timeout = 10.0;
    int32       totalRead = 0;
    int         ii = 0;


    printf("zPress Ctrl-C to exit  Creating task\n");
    DAQmxErrChk (DAQmxBaseCreateTask("",&taskHandle));
    printf( " ... creating voltage chan for task: %x\n", taskHandle );

    printf( "DAQmxBaseCreateAIVoltageChan( %x, \"%s\", \"%s\", %x, %f, %f, %d, %x)\n", taskHandle,chan,"",DAQmx_Val_Cfg_Default,min,max,DAQmx_Val_Volts,NULL);
    DAQmxErrChk (DAQmxBaseCreateAIVoltageChan(taskHandle,chan,"",DAQmx_Val_Cfg_Default,min,max,DAQmx_Val_Volts,NULL));
    printf( " ... cfg samp clk timing\n");

    printf( "DAQmxBaseCfgSampClkTiming( %x, \"%s\", %f, %x, %x, %d\n", taskHandle,clockSource, sampleRate, DAQmx_Val_Rising, DAQmx_Val_ContSamps, samplesPerChan );
    DAQmxErrChk (DAQmxBaseCfgSampClkTiming(taskHandle,clockSource,sampleRate,DAQmx_Val_Rising,DAQmx_Val_ContSamps,samplesPerChan));

    printf( " ... cfg input buffer\n");
    printf( " DAQmxBaseCfgInputBuffer( %x, %d )\n", taskHandle, 200000 );
    DAQmxErrChk (DAQmxBaseCfgInputBuffer(taskHandle,200000)); //use a 100,000 sample DMA buffer

    printf( " DAQmxBaseStartTask( %x )\n", taskHandle );
    DAQmxErrChk (DAQmxBaseStartTask(taskHandle));

    // The loop will quit after 10 seconds

    for( ii = 0 ; ii < 3 ; ii++ ) {
        printf( "DAQmxBaseReadAnalogF64( %x, %d, %f, %x, %s, %d, NULL\n", taskHandle,pointsToRead, timeout, DAQmx_Val_GroupByScanNumber, "?", pointsRead );
        DAQmxErrChk (DAQmxBaseReadAnalogF64(taskHandle,pointsToRead,timeout,DAQmx_Val_GroupByScanNumber,data,bufferSize*2,&pointsRead,NULL));
        totalRead += pointsRead;
        printf("Acquired %d samples. Total %d\n",pointsRead,totalRead);
        // Just print out the first 10 points of the last data read
        for (i = 0; i < 5; ++i)
            printf ("data0[%d] = %f\tdata1[%d] = %f\n",i,data[2*i],i,data[2*i+1]);

    }
    printf("\nAcquired %d total samples.\n",totalRead);

Error:
    if( DAQmxFailed(error) )
        DAQmxBaseGetExtendedErrorInfo(errBuff,2048);
    if(taskHandle != 0) {
        DAQmxBaseStopTask (taskHandle);
        DAQmxBaseClearTask (taskHandle);
    }
    if( DAQmxFailed(error) )
		printf ("DAQmxBase Error %d: %s\n", error, errBuff);
    return 0;
}

extern "C" JNIEXPORT jlong JNICALL Java_ni_DAQmxBase_Test_test2(JNIEnv *env,
		jobject jobj) {

	// Java_ni_DAQmxBase_Task
}

