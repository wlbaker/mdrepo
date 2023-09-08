/*
 * NIFuncs.h
 *
 *  Created on: Oct 7, 2009
 *      Author: bbaker
 */

#ifndef NIFUNCS_H_
#define NIFUNCS_H_

#include <iostream>
#include <list>

#include <windows.h>
#include <NIDAQmx.h>

int ni_getDevices( std::list<std::string> &L );
int ni_getDevicePorts(std::list<std::string> &L, const char *dev);

#define DAQmxErrChk(functionCall) if( DAQmxFailed(error=(functionCall)) ) goto Error; else

#endif /* NIFUNCS_H_ */
