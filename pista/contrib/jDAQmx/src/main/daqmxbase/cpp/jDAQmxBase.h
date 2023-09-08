/*
 * NIDaqJ.h
 *
 *  Created on: Oct 5, 2009
 *      Author: bbaker
 */

#ifndef NIDAQJ_H_
#define NIDAQJ_H_

#include <iostream>
#include <list>

#include <jni.h>
// #include <windows.h>
#include <NIDAQmxBase.h>

#define DAQmxErrChk(functionCall) if( DAQmxFailed(error=(functionCall)) ) goto Error; else


extern JavaVM *cached_jvm;


#endif /* NIDAQJ_H_ */
